#include "sbml.h"

//TODO : REMOVE
void sbml_hello()
{
    std::cout << "Hello from sbml" << std::endl;
}

static void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            cout<<("node type: Element, name: %s\n", cur_node->name)<<endl;
        }
        print_element_names(cur_node->children);
    }
}

void
parseXML(std::string s){

    xmlNode *root_element = NULL;
    const xmlChar * content = (const unsigned  char *)s.c_str();
    xmlDocPtr doc = xmlReadMemory(s.c_str(), s.length(), "noname.xml", NULL, 0);
    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);
    /*free the document */
    xmlFreeDoc(doc);
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}

void
printModel() { std::string mS = "void"; std::cout<<"Usage: Provide SBML file as input parameter"<< std::endl ;}

int printSBMLModel(char* filename){


    SBMLDocument* document = readSBML(filename);

    if (document->getNumErrors() > 0)
    {
        cerr << "Encountered the following SBML errors:" << endl;
        document->printErrors(cerr);
        return 1;
    }



    unsigned int level   = document->getLevel  ();
    unsigned int version = document->getVersion();
    cout << endl
         << " (Level " << level << ", version " << version << ")" << endl;
    Model* model = document->getModel();
    if (model == 0)
    {
        cout << "No model present." << endl;
        return 1;
    }
    cout << "               "
         << (level == 1 ? "name: " : "  id: ")
         << (model->isSetId() ? model->getId() : std::string("(empty)")) << endl;
    if (model->isSetSBOTerm())
        cout << "      model sboTerm: " << model->getSBOTerm() << endl;
    cout << "functionDefinitions: " << model->getNumFunctionDefinitions() << endl;
    cout << "    unitDefinitions: " << model->getNumUnitDefinitions    () << endl;
    cout << "   compartmentTypes: " << model->getNumCompartmentTypes   () << endl;
    cout << "        specieTypes: " << model->getNumSpeciesTypes       () << endl;
    cout << "       compartments: " << model->getNumCompartments       () << endl;
    cout << "            species: " << model->getNumSpecies            () << endl;
    cout << "         parameters: " << model->getNumParameters         () << endl;
    cout << " initialAssignments: " << model->getNumInitialAssignments () << endl;
    cout << "              rules: " << model->getNumRules              () << endl;
    cout << "        constraints: " << model->getNumConstraints        () << endl;
    cout << "          reactions: " << model->getNumReactions          () << endl;
    cout << "             events: " << model->getNumEvents             () << endl;
    cout << endl;
    return 0;
}

void
printModel(char* filename) { std::cout<<filename; std::cout<<printSBMLModel(filename)<<std::endl;}
void
printFunctionDefinition (unsigned int n, const FunctionDefinition* fd)
{
    const ASTNode* math;
    char* formula;
    if ( fd->isSetMath() )
    {
        cout << "FunctionDefinition " << n << ", " << fd->getId();
        math = fd->getMath();
        /* Print function arguments. */
        if (math->getNumChildren() > 1)
        {
            cout << "(" << ( math->getLeftChild() )->getName();
            for (n = 1; n < math->getNumChildren() - 1; ++n)
            {
                cout <<", " << ( math->getChild(n) )->getName();
            }
        }
        cout <<") := ";
        /* Print function body. */
        if (math->getNumChildren() == 0)
        {
            cout << "(no body defined)";
        }
        else
        {
            math    = math->getChild(math->getNumChildren() - 1);
            formula = SBML_formulaToString(math);
            cout << formula << endl;
            free(formula);
        }
    }
}
void
printRuleMath (unsigned int n, const Rule* r)
{
    char* formula;
    if ( r->isSetMath() )
    {
        formula = SBML_formulaToString( r->getMath() );
        if (r->getVariable().length() > 0)
        {
            cout << "Rule " << n << ", formula: "
                 << r->getVariable() << " = " << formula << endl;
        }
        else
        {
            cout << "Rule " << n << ", formula: "
                 << formula << " = 0" << endl;
        }
        free(formula);
    }
}
void
printReactionMath (unsigned int n, const Reaction* r)
{
    char* formula;
    const KineticLaw* kl;
    if (r->isSetKineticLaw())
    {
        kl = r->getKineticLaw();
        if ( kl->isSetMath() )
        {
            formula = SBML_formulaToString( kl->getMath() );
            cout << "Reaction " << n << ", formula: " << formula << endl;
            free(formula);
        }
    }
}
void
printEventAssignmentMath (unsigned int n, const EventAssignment* ea)
{
    std::string variable;
    char* formula;
    if ( ea->isSetMath() )
    {
        variable = ea->getVariable();
        formula  = SBML_formulaToString( ea->getMath() );
        cout <<"  EventAssignment " << n
             << ", trigger: " << variable << " = " << formula << endl;
        free(formula);
    }
}
void
printEventMath (unsigned int n, const Event* e)
{
    char* formula;
    unsigned int i;
    if ( e->isSetDelay() )
    {
        formula = SBML_formulaToString( e->getDelay()->getMath() );
        cout << "Event " << n << " delay: " << formula << endl;
        free(formula);
    }
    if ( e->isSetTrigger() )
    {
        formula = SBML_formulaToString( e->getTrigger()->getMath() );
        cout << "Event " << n << " trigger: " << formula << endl;
        free(formula);
    }
    for (i = 0; i < e->getNumEventAssignments(); ++i)
    {
        printEventAssignmentMath(i + 1, e->getEventAssignment(i));
    }
    cout << endl;
}
void
printMath (const Model* m)
{
    unsigned int  n;
    for (n = 0; n < m->getNumFunctionDefinitions(); ++n)
    {
        printFunctionDefinition(n + 1, m->getFunctionDefinition(n));
    }
    for (n = 0; n < m->getNumRules(); ++n)
    {
        printRuleMath(n + 1, m->getRule(n));
    }
    cout << endl;
    for (n = 0; n < m->getNumReactions(); ++n)
    {
        printReactionMath(n + 1, m->getReaction(n));
    }
    cout << endl;
    for (n = 0; n < m->getNumEvents(); ++n)
    {
        printEventMath(n + 1, m->getEvent(n));
    }
}
int printSBMLMath(char* filename){
    SBMLDocument* document = readSBML(filename);
    if (document->getNumErrors() > 0)
    {
        cerr << "Encountered the following SBML errors:" << endl;
        document->printErrors(cerr);
        return 1;
    }
    Model* model = document->getModel();
    if (model == 0)
    {
        cout << "No model present." << endl;
        return 1;
    }
    printMath(model);
    cout << endl;
    delete document;
    return 0;
}
void printSBMLModelMath(char* filename) { cout<<printSBMLMath(filename)<<std::endl;}

int updateSID (char* filename, char* output, char* oldSId, char* newSId ){

    if (strcmp(oldSId, newSId) == 0)
    {
        cout << "The Ids are identical, renaming stopped." << endl;
        return 1;
    }
    if (!SyntaxChecker::isValidInternalSId(newSId))
    {
        cout << "The new SId '" << newSId
             << "' does not represent a valid SId."
             << endl;
        return 1;
    }
    SBMLDocument* document;
    SBMLReader reader;
#ifdef __BORLANDC__
    unsigned long start, stop;
#else
    unsigned long long start, stop;
#endif

    document = reader.readSBML(filename);

    unsigned int errors = document->getNumErrors(LIBSBML_SEV_ERROR);

    cout << endl;
    cout << "            filename: " << filename              << endl;
    cout << "            error(s): " << errors << endl;
    cout << endl;

    if (errors > 0)
    {
        document->printErrors(cerr);
        delete document;
        return errors;
    }
    // find elements for old id
    SBase* element = document->getElementBySId(oldSId);
    if (element == NULL)
    {
        cout << "Found no element with SId '"
             << oldSId << "'." << endl;
        return 1;
    }

    // found element --> renaming
    element->setId(newSId);
    // update all references to this element
    List *allElements = document->getAllElements();
    for (unsigned int i = 0; i < allElements->getSize(); ++i)
        static_cast<SBase*>(allElements->get(i))->renameSIdRefs(oldSId, newSId);


    // write to file
    writeSBMLToFile(document, output);

    delete document;
    return errors;
}
void updateSpeciesID(char *old_filename, char *new_filename, char *old_sid, char *new_sId){

    try {
        updateSID(old_filename, new_filename, old_sid, new_sId );
        std::cout << " Update Successful " << '\n'<<std::endl;
        std::cout << " Updated SBML file "<< new_filename << " created " << '\n'<<std::endl;
    } catch (int i) {
        std::cout << " Update Failed " << '\n'<<std::endl;
    }
}

void printAnnotation(SBase *sb, const string& id = "")
{
    // if (!sb->isSetAnnotation()) return;
    string pid = id;
    if (pid == "" && sb->isSetId())
    {
        pid = sb->getId();
    }

    cout << sb->getElementName() << "  " <<pid << endl;

    cout << sb->getAnnotationString() << endl;

    cout << "Tags : \n" << endl;
    parseXML(sb->getAnnotationString());
    cout << endl;
}
void getSBMLAnnotation(char* filename) {

    unsigned int i,j;
    SBMLDocument* document;
    SBMLReader reader;
    document = reader.readSBML(filename);
    unsigned int errors = document->getNumErrors();
    cout << endl;
    cout << "filename: " << filename << endl;
    cout << endl;
    if(errors > 0)
    {
        document->printErrors(cerr);
        delete document;
        //    return errors;
    }
    /* Model */
    Model* m = document->getModel();
    printAnnotation(m);
    for(i=0; i < m->getNumReactions(); i++)
    {
        Reaction* re = m->getReaction(i);
        printAnnotation(re);
        /* SpeciesReference (Reacatant) */
        for(j=0; j < re->getNumReactants(); j++)
        {
            SpeciesReference* rt = re->getReactant(j);
            if (rt->isSetAnnotation()) cout << "   ";
            printAnnotation(rt, (rt->isSetSpecies() ? rt->getSpecies() : std::string("")) );
        }
        /* SpeciesReference (Product) */
        for(j=0; j < re->getNumProducts(); j++)
        {
            SpeciesReference* rt = re->getProduct(j);
            if (rt->isSetAnnotation()) cout << "   ";
            printAnnotation(rt, (rt->isSetSpecies() ? rt->getSpecies() : std::string("")) );
        }
        /* ModifierSpeciesReference (Modifiers) */
        for(j=0; j < re->getNumModifiers(); j++)
        {
            ModifierSpeciesReference* md = re->getModifier(j);
            if (md->isSetAnnotation()) cout << "   ";
            printAnnotation(md, (md->isSetSpecies() ? md->getSpecies() : std::string("")) );
        }
        /* KineticLaw */
        if(re->isSetKineticLaw())
        {
            KineticLaw* kl = re->getKineticLaw();
            if (kl->isSetAnnotation()) cout << "   ";
            printAnnotation(kl);
            /* Parameter */
            for(j=0; j < kl->getNumParameters(); j++)
            {
                Parameter* pa = kl->getParameter(j);
                if (pa->isSetAnnotation()) cout << "      ";
                printAnnotation(pa);
            }
        }
    }
    /* Species */
    for(i=0; i < m->getNumSpecies(); i++)
    {
        Species* sp = m->getSpecies(i);
        printAnnotation(sp);
    }
    /* Compartments */
    for(i=0; i < m->getNumCompartments(); i++)
    {
        Compartment* sp = m->getCompartment(i);
        printAnnotation(sp);
    }
    /* FunctionDefinition */
    for(i=0; i < m->getNumFunctionDefinitions(); i++)
    {
        FunctionDefinition* sp = m->getFunctionDefinition(i);
        printAnnotation(sp);
    }
    /* UnitDefinition */
    for(i=0; i < m->getNumUnitDefinitions(); i++)
    {
        UnitDefinition* sp = m->getUnitDefinition(i);
        printAnnotation(sp);
    }
    /* Parameter */
    for(i=0; i < m->getNumParameters(); i++)
    {
        Parameter* sp = m->getParameter(i);
        printAnnotation(sp);
    }
    /* Rule */
    for(i=0; i < m->getNumRules(); i++)
    {
        Rule* sp = m->getRule(i);
        printAnnotation(sp);
    }
    /* InitialAssignment */
    for(i=0; i < m->getNumInitialAssignments(); i++)
    {
        InitialAssignment* sp = m->getInitialAssignment(i);
        printAnnotation(sp);
    }
    /* Event */
    for(i=0; i < m->getNumEvents(); i++)
    {
        Event* sp = m->getEvent(i);
        printAnnotation(sp);
        /* Trigger */
        if(sp->isSetTrigger())
        {
            const Trigger* tg = sp->getTrigger();
            if (tg->isSetAnnotation()) cout << "   ";
            printAnnotation(const_cast<Trigger*>(tg));
        }
        /* Delay */
        if(sp->isSetDelay())
        {
            const Delay* dl = sp->getDelay();
            if (dl->isSetAnnotation()) cout << "   ";
            printAnnotation(const_cast<Delay*>(dl));
        }
        /* EventAssignment */
        for(j=0; j < sp->getNumEventAssignments(); j++)
        {
            EventAssignment* ea = sp->getEventAssignment(j);
            if (ea->isSetAnnotation()) cout << "   ";
            printAnnotation(ea);
        }
    }
    /* SpeciesType */
    for(i=0; i < m->getNumSpeciesTypes(); i++)
    {
        SpeciesType* sp = m->getSpeciesType(i);
        printAnnotation(sp);
    }
    /* Constraints */
    for(i=0; i < m->getNumConstraints(); i++)
    {
        Constraint* sp = m->getConstraint(i);
        printAnnotation(sp);
    }
    delete document;
    //   return errors;
}

int printAnnotation_helper(char* filename){

    SBMLDocument* document = readSBML(filename);
    unsigned int errors = document->getNumErrors();

    cout<<"Errors : " <<errors<<std::endl;

    /* Model */
    Model* m = document->getModel();
    printAnnotation(m);
    for(int i = 0; i < m->getNumReactions(); i++)
    {
        Reaction* re = m->getReaction(i);
        printAnnotation(re);
        /* SpeciesReference (Reactant) */
        for(unsigned int j = 0; j < re->getNumReactants(); j++)
        {
            SpeciesReference* rt = re->getReactant(j);
            if (rt->isSetAnnotation()) cout << "   ";
            printAnnotation(rt, (rt->isSetSpecies() ? rt->getSpecies() : std::string("")) );
        }
        /* SpeciesReference (Product) */
        for(unsigned int j=0; j < re->getNumProducts(); j++)
        {
            SpeciesReference* rt = re->getProduct(j);
            if (rt->isSetAnnotation()) cout << "   ";
            printAnnotation(rt, (rt->isSetSpecies() ? rt->getSpecies() : std::string("")) );
        }
        /* ModifierSpeciesReference (Modifiers) */
        for(unsigned int j=0; j < re->getNumModifiers(); j++)
        {
            ModifierSpeciesReference* md = re->getModifier(j);
            if (md->isSetAnnotation()) cout << "   ";
            printAnnotation(md, (md->isSetSpecies() ? md->getSpecies() : std::string("")) );
        }
        /* KineticLaw */
        if(re->isSetKineticLaw())
        {
            KineticLaw* kl = re->getKineticLaw();
            if (kl->isSetAnnotation()) cout << "   ";
            printAnnotation(kl);
            /* Parameter */
            for(unsigned int j=0; j < kl->getNumParameters(); j++)
            {
                Parameter* pa = kl->getParameter(j);
                if (pa->isSetAnnotation()) cout << "      ";
                printAnnotation(pa);
            }
        }
    }
    /* Species */
    for(unsigned int i=0; i < m->getNumSpecies(); i++)
    {
        Species* sp = m->getSpecies(i);
        printAnnotation(sp);
    }
    /* Compartments */
    for(unsigned int i=0; i < m->getNumCompartments(); i++)
    {
        Compartment* sp = m->getCompartment(i);
        printAnnotation(sp);
    }
    /* FunctionDefinition */
    for(unsigned int i=0; i < m->getNumFunctionDefinitions(); i++)
    {
        FunctionDefinition* sp = m->getFunctionDefinition(i);
        printAnnotation(sp);
    }
    /* UnitDefinition */
    for(unsigned int i=0; i < m->getNumUnitDefinitions(); i++)
    {
        UnitDefinition* sp = m->getUnitDefinition(i);
        printAnnotation(sp);
    }
    /* Parameter */
    for(unsigned int i=0; i < m->getNumParameters(); i++)
    {
        Parameter* sp = m->getParameter(i);
        printAnnotation(sp);
    }
    /* Rule */
    for(unsigned int i=0; i < m->getNumRules(); i++)
    {
        Rule* sp = m->getRule(i);
        printAnnotation(sp);
    }
    /* InitialAssignment */
    for(unsigned int i=0; i < m->getNumInitialAssignments(); i++)
    {
        InitialAssignment* sp = m->getInitialAssignment(i);
        printAnnotation(sp);
    }
    /* Event */
    for(unsigned int i=0; i < m->getNumEvents(); i++)
    {
        Event* sp = m->getEvent(i);
        printAnnotation(sp);
        /* Trigger */
        if(sp->isSetTrigger())
        {
            const Trigger* tg = sp->getTrigger();
            if (tg->isSetAnnotation()) cout << "   ";
            printAnnotation(const_cast<Trigger*>(tg));
        }
        /* Delay */
        if(sp->isSetDelay())
        {
            const Delay* dl = sp->getDelay();
            if (dl->isSetAnnotation()) cout << "   ";
            printAnnotation(const_cast<Delay*>(dl));
        }
        /* EventAssignment */
        for(unsigned int j=0; j < sp->getNumEventAssignments(); j++)
        {
            EventAssignment* ea = sp->getEventAssignment(j);
            if (ea->isSetAnnotation()) cout << "   ";
            printAnnotation(ea);
        }
    }
    /* SpeciesType */
    for(unsigned int i=0; i < m->getNumSpeciesTypes(); i++)
    {
        SpeciesType* sp = m->getSpeciesType(i);
        printAnnotation(sp);
    }
    /* Constraints */
    for(unsigned int i=0; i < m->getNumConstraints(); i++)
    {
        Constraint* sp = m->getConstraint(i);
        printAnnotation(sp);
    }
    delete document;
}