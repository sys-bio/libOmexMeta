/**
 * @file local.i
 * @brief Base file
 * @author DEVISER
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 */


%include "std_string.i"
%include "std_wstring.i"

%include "exception.i"
%include <typemaps.i>

%include "enumsimple.swg"


/**
* Renames *::clone() to *::cloneObject().
* In JDK 1.4.2, libcombine's *::clone() methods can't override 
* "Object Java.lang.Object.clone()" because JDK 1.4.2 doesn't
* allow override with different return type. 
*
* (2008-12-07)
* Currently, JDK 1.5 or later, which allows a covariant return type,
* is required for libCombine Java binding, and thus we don't have to use
* this rename directive. However, this directive is still enabled for 
* compatiblity.
*/

%rename(cloneObject) *::clone;

/** 
* Rename XMLNode::equals() to XMLNode::xmlEquals(), otherwise it conflicts with the 
* equals operation defined below
*/
%rename(xmlEquals) XMLNode::equals;
/** 
* Rename ASTNode::getClass() to ASTNode::getClassName(), otherwise it conflicts 
*/
%rename(getClassName) ASTNode::getClass;
%rename(setClassName) ASTNode::setClass;

/**
* Wraps covariant return types of ::clone functions.
*
* Currently, SWIG doesn't allow a covariant return type although
* JDK 1.5 or later supports it.
* Thus, the following directives are required to enable the 
* covariant return type. 
*/

#pragma SWIG nowarn=822

%define COVARIANT_RTYPE_CLONE(_CNAME_)
%typemap(jstype) _CNAME_* _CNAME_::clone  "_CNAME_"
%enddef

COVARIANT_RTYPE_CLONE(Compartment)
COVARIANT_RTYPE_CLONE(CompartmentType)
COVARIANT_RTYPE_CLONE(Constraint)
COVARIANT_RTYPE_CLONE(Delay)
COVARIANT_RTYPE_CLONE(Event)
COVARIANT_RTYPE_CLONE(EventAssignment)
COVARIANT_RTYPE_CLONE(FunctionDefinition)
COVARIANT_RTYPE_CLONE(InitialAssignment)
COVARIANT_RTYPE_CLONE(KineticLaw)
COVARIANT_RTYPE_CLONE(Model)
COVARIANT_RTYPE_CLONE(Parameter)
COVARIANT_RTYPE_CLONE(Priority)
COVARIANT_RTYPE_CLONE(LocalParameter)
COVARIANT_RTYPE_CLONE(Reaction)
COVARIANT_RTYPE_CLONE(Rule)
COVARIANT_RTYPE_CLONE(AlgebraicRule)
COVARIANT_RTYPE_CLONE(AssignmentRule)
COVARIANT_RTYPE_CLONE(RateRule)
COVARIANT_RTYPE_CLONE(Species)
COVARIANT_RTYPE_CLONE(SpeciesReference)
COVARIANT_RTYPE_CLONE(SpeciesType)
COVARIANT_RTYPE_CLONE(StoichiometryMath)
COVARIANT_RTYPE_CLONE(Trigger)
COVARIANT_RTYPE_CLONE(Unit)
COVARIANT_RTYPE_CLONE(UnitDefinition)
COVARIANT_RTYPE_CLONE(ListOf)
COVARIANT_RTYPE_CLONE(ListOfCompartmentTypes)
COVARIANT_RTYPE_CLONE(ListOfCompartments)
COVARIANT_RTYPE_CLONE(ListOfConstraints)
COVARIANT_RTYPE_CLONE(ListOfEventAssignments)
COVARIANT_RTYPE_CLONE(ListOfEvents)
COVARIANT_RTYPE_CLONE(ListOfFunctionDefinitions)
COVARIANT_RTYPE_CLONE(ListOfInitialAssignments)
COVARIANT_RTYPE_CLONE(ListOfParameters)
COVARIANT_RTYPE_CLONE(ListOfLocalParameters)
COVARIANT_RTYPE_CLONE(ListOfReactions)
COVARIANT_RTYPE_CLONE(ListOfRules)
COVARIANT_RTYPE_CLONE(ListOfSpecies)
COVARIANT_RTYPE_CLONE(ListOfSpeciesReferences)
COVARIANT_RTYPE_CLONE(ListOfSpeciesTypes)
COVARIANT_RTYPE_CLONE(ListOfUnitDefinitions)
COVARIANT_RTYPE_CLONE(ListOfUnits)
COVARIANT_RTYPE_CLONE(CaConstructorException)
COVARIANT_RTYPE_CLONE(CaNamespaces)
COVARIANT_RTYPE_CLONE(CaContent)
COVARIANT_RTYPE_CLONE(CaOmexManifest)
COVARIANT_RTYPE_CLONE(CaCrossRef)
COVARIANT_RTYPE_CLONE(CaListOfContents)
COVARIANT_RTYPE_CLONE(CaListOfCrossRefs)



/**
*
* Wraps covariant return types of ListOfXXX::get functions.
*
*/

%define COVARIANT_RTYPE_LISTOF_GET_REMOVE(_CNAME_)
%typemap(jstype) _CNAME_* ListOf ## _CNAME_ ## s::get  "_CNAME_"
%typemap(jstype) _CNAME_* ListOf ## _CNAME_ ## s::remove  "_CNAME_"
%enddef

COVARIANT_RTYPE_LISTOF_GET_REMOVE(CompartmentType)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Compartment)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(EventAssignment)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Event)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(FunctionDefinition)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(InitialAssignment)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(LocalParameter)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Parameter)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Reaction)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Rule)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(SpeciesType)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(UnitDefinition)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Constraint)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Unit)

// Only ListOfSpecies and ListOfSpeciesReference classes do not 
// match the above macro...
%typemap(jstype) Species* ListOfSpecies::get    "Species"
%typemap(jstype) Species* ListOfSpecies::remove "Species"
%typemap(jstype) SimpleSpeciesReference* ListOfSpeciesReferences::get    "SimpleSpeciesReference"
%typemap(jstype) SimpleSpeciesReference* ListOfSpeciesReferences::remove "SimpleSpeciesReference"


COVARIANT_RTYPE_LISTOF_GET_REMOVE(CaListOfContents)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(CaListOfCrossRefs)

/**
* Wraps the CaConstructorException
*
* The CaConstructorException (C++ class) is wrapped as the 
* CaConstructorException (Java class) which is derived from
* the built-in IllegalArgumentException class which is a subclass
* of RunTimeException.
*
* For example, the exception can be catched in Java code as follows:
*
* ---------------------------------------------
*  try
*  {
*    Model s = new Model(level,version);
*  }
*  catch (CaConstructorException e)
*  {
*     String errmsg = e.getMessage();
*  }
* ---------------------------------------------
*/

%ignore CaConstructorException::CaConstructorException(std::string);

%typemap(javabase) CaConstructorException "java.lang.IllegalArgumentException";
%typemap(javacode) CaConstructorException 
%{
	protected CaConstructorException(long cPtr, boolean cMemoryOwn, String v)
	{
		super(v);
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = cPtr;
	}

	/**
* Exception thrown by libCombine object constructors if something prevents
* the object from being properly created.
*
* An example of what can cause this exception to be thrown is attempting
* to create an Ca component with an invalid Ca Level/Version
* combination.
*/
	public CaConstructorException(String v)
	{
		this(libcombineJNI.new_CaConstructorException__SWIG_0(), true, v);
	}
	%}

%define SEDMLCONSTRUCTOR_EXCEPTION(SBASE_CLASS_NAME)
%javaexception("org.omex.libcombine.CaConstructorException") SBASE_CLASS_NAME
%{
	try {
		$action
	}
	catch (const CaConstructorException &e) {
		jenv->ExceptionClear();
		jclass clazz = jenv->FindClass("org/omex/libcombine/CaConstructorException");
		if (clazz)
		jenv->ThrowNew(clazz, e.what());
		return $null;
	}
	%}
%enddef

SEDMLCONSTRUCTOR_EXCEPTION(CaContent)
SEDMLCONSTRUCTOR_EXCEPTION(CaOmexManifest)
SEDMLCONSTRUCTOR_EXCEPTION(CaCrossRef)
SEDMLCONSTRUCTOR_EXCEPTION(CaListOfContents)
SEDMLCONSTRUCTOR_EXCEPTION(CaListOfCrossRefs)



/**
* Wraps the XMLConstructorException
*
* The XMLConstructorException (C++ class) is wrapped as the 
* XMLConstructorException (Java class) which is derived from
* the built-in IllegalArgumentException class which is a subclass
* of RunTimeException.
*
* For example, the exception can be catched in Java code as follows:
*
* ---------------------------------------------
*  try
*  {
*    Model s = new Model(level,version);
*  }
*  catch (XMLConstructorException e)
*  {
*     String errmsg = e.getMessage();
*  }
* ---------------------------------------------
*/

%typemap(javabase) XMLConstructorException "java.lang.IllegalArgumentException";
%typemap(javacode) XMLConstructorException 
%{
	/*
* To pass the message from an exception to the parent exception class,
* we have to create our own variant of the constructor that takes an
* extra string argument.
*/
	protected XMLConstructorException(long cPtr, boolean cMemoryOwn, String v)
	{
		super(v);
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = cPtr;
	}

	/*
* Next, we define the public constructor to take a string (like all basic
* Java exception class constructors), and invoke our internal special
* constructor with the extra argument.
*/
	public XMLConstructorException(String v)
	{
		this(libcombineJNI.new_XMLConstructorException(), true, v);
	}
	%}

/*
* Finally, to make our string-passing constructor work, we have to disable
* the default constructor created by SWIG in newer versions of SWIG.
*/
%ignore XMLConstructorException(std::string message);

/*
* The following creates a macro used to wrap individual class constructors
* that may throw XMLConstructorException.
*/
%define XMLCONSTRUCTOR_EXCEPTION(SBASE_CLASS_NAME)
%javaexception("org.omex.libcombine.XMLConstructorException") SBASE_CLASS_NAME
%{
	try {
		$action
	}
	catch (const XMLConstructorException &e) {
		jenv->ExceptionClear();
		jclass clazz = jenv->FindClass("org/omex/libcombine/XMLConstructorException");
		if (clazz)
		jenv->ThrowNew(clazz, e.what());
		return $null;
	}
	%}
%enddef


XMLCONSTRUCTOR_EXCEPTION(XMLAttributes)
XMLCONSTRUCTOR_EXCEPTION(XMLError)
XMLCONSTRUCTOR_EXCEPTION(XMLNamespaces)
XMLCONSTRUCTOR_EXCEPTION(XMLNode)
XMLCONSTRUCTOR_EXCEPTION(XMLOutputStream)
XMLCONSTRUCTOR_EXCEPTION(XMLToken)
XMLCONSTRUCTOR_EXCEPTION(XMLTripple)


/**
* Ignores XMLToken::clone() in order to use XMLNode::clone().
* (XMLNode is a derived class of XMLToken)
* In JDK 1.4.2, "XMLNode XMLNode::clone()" can't override 
* "XMLToken XMLToken::clone()" because JDK 1.4.2 doesn't
* allow override with different return type.
*/

//%javamethodmodifiers       XMLToken::clone "private"

/**
* Ignores XMLErrorLog::getError(unsigned int) in order to use
* CaErrorLog::getError(unsigned int).
* (XMLErrorLog is a derived class of CaErrorLog)
* In JDK 1.4.2, "CaError* CaErrorLog::getError(unsigned int)"
* can't override "XMLError* XMLErrorLog::getError(unsigned int)"
* due to the above mentioned reason.
*/

//%javamethodmodifiers       XMLErrorLog::getError "private"

/**
* Turns off object destruction.  For testing purposes only.
*
* FIXME: Disable for the final 3.0 release.
*/
/*
%typemap (javafinalize) SWIGTYPE %{ %}
*/


/**
* Make most libCombine constants (e.g. CaTypecodes) Java compile-time
* constants so they may be used in switch statements.
*/
%include "enumsimple.swg"
%javaconst(1);


/**
* A bug in Swig prevents these four ASTNode constants being generated
* as Java compile-time constants.  Swig does not parse the following
* enum correctly:
*
*   typedef enum
*   {
*       AST_PLUS    = '+'
*     , AST_MINUS   = '-'
*     , AST_TIMES   = '*'
*     , AST_DIVIDE  = '/'
*     , AST_POWER   = '^'
*
*
* The generated Java code does not like the tick marks (').  To fix
* this, we need to be explicit about (and duplicate) the value of
* the constants here.
*/

%javaconstvalue("'+'") AST_PLUS;
%javaconstvalue("'-'") AST_MINUS;
%javaconstvalue("'*'") AST_TIMES;
%javaconstvalue("'/'") AST_DIVIDE;
%javaconstvalue("'^'") AST_POWER;



/**
* @return the most specific Java object possible for the given CaBase
* object.
*/
%pragma(java) modulecode =
%{
	

	/**
* Internal method.
*
* @internal
*/
	public static CaBase DowncastCaBase(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;

		CaBase sb = new CaBase(cPtr, false);
    switch( sb.getTypeCode() )
    {
    case (int) libcombine.LIB_COMBINE_OMEXMANIFEST:
      return new CaOmexManifest(cPtr, owner);

    case (int) libcombine.LIB_COMBINE_CONTENT:
      return new CaContent(cPtr, owner);

    case (int) libcombine.OMEX_COMBINE_CROSSREF:
      return new CaCrossRef(cPtr, owner);

    case (int) libcombine.OMEX_LIST_OF:
      String name = sb.getElementName();
      if(name.equals("listOf"))
      {
        return new CaListOf(cPtr, owner);
      }
      else if (name == "listOfContents")
      {
         return new CaListOfContents(cPtr, owner);
      }
      else if (name == "listOfCrossRefs")
      {
         return new CaListOfCrossRefs(cPtr, owner);
      }
      
      return new CaListOf(cPtr, owner);        
      
    default:
      return new CaBase(cPtr, owner);
		}      

	}
	%}



/**
* Convert CaBase objects into the most specific object possible.
*/
%typemap("javaout") CaBase*
{
	return libcombine.DowncastCaBase($jnicall, $owner);
}


/**
* getCPtrAndDisown() is like getCPtr() but it also sets the SWIG memory
* ownsership flag to false.
*
* We used to use %typemap(javagetcptr), but this has been deprecated
* in SWIG 1.3.24.  Instead we add getCPtrAndDisown() from the incantation
* below (taken from the SWIG 1.3.24 CHANGES file).
*/

/* Utility macro for manipulating the Java body code method attributes */
%define SWIGJAVA_ATTRIBS(TYPENAME, CTOR_ATTRIB, GETCPTR_ATTRIB)

%typemap(javabody) TYPENAME
%{
	private long swigCPtr;
	protected boolean swigCMemOwn;

	CTOR_ATTRIB $javaclassname(long cPtr, boolean cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = cPtr;
	}

	GETCPTR_ATTRIB static long getCPtr($javaclassname obj)
	{
		return (obj == null) ? 0 : obj.swigCPtr;
	}

	GETCPTR_ATTRIB static long getCPtrAndDisown ($javaclassname obj)
	{
		long ptr = 0;

		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}

		return ptr;
	}
	%}


#if SWIG_VERSION >= 0x020000

%typemap(javabody_derived) TYPENAME
%{
	private long swigCPtr;

	CTOR_ATTRIB $javaclassname(long cPtr, boolean cMemoryOwn)
	{
		super($moduleJNI.$javaclassname_SWIGUpcast(cPtr), cMemoryOwn);
		swigCPtr = cPtr;
	}

	GETCPTR_ATTRIB static long getCPtr($javaclassname obj)
	{
		return (obj == null) ? 0 : obj.swigCPtr;
	}

	GETCPTR_ATTRIB static long getCPtrAndDisown ($javaclassname obj)
	{
		long ptr = 0;

		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}

		return ptr;
	}
	%}

#else

%typemap(javabody_derived) TYPENAME
%{
	private long swigCPtr;

	CTOR_ATTRIB $javaclassname(long cPtr, boolean cMemoryOwn)
	{
		super($moduleJNI.SWIG$javaclassnameUpcast(cPtr), cMemoryOwn);
		swigCPtr = cPtr;
	}

	GETCPTR_ATTRIB static long getCPtr($javaclassname obj)
	{
		return (obj == null) ? 0 : obj.swigCPtr;
	}

	GETCPTR_ATTRIB static long getCPtrAndDisown ($javaclassname obj)
	{
		long ptr = 0;

		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}

		return ptr;
	}
	%}

#endif

%enddef

/* The default is protected getCPtr, protected constructor */
SWIGJAVA_ATTRIBS(SWIGTYPE, protected, protected)

/* Public getCPtr method, protected constructor */
%define PUBLIC_GETCPTR(TYPENAME)
SWIGJAVA_ATTRIBS(TYPENAME, protected, public)
%enddef

/* Public getCPtr method, public constructor */
%define PUBLIC_BODYMETHODS(TYPENAME)
SWIGJAVA_ATTRIBS(TYPENAME, public, public)
%enddef

/**
*
* Overrides the 'equals' method for CaBase subclasses and other classes
* in libcombine.
*
* By default, 'equals' method ( and '==' operator) for each wrapped class
* object returns 'true' if the given two objects refer to the same 
* *Java proxy object* (not the underlying C++ object). 
* For example, the following code returns 'true'.
*
*   Model m = new Model();
*   m.createReaction();
*   Reaction r1  = m.getReaction(0);
*   Reaction r2 = r1;
*   return r1.equals(r2);  <---- this returns 'true'
*
* On the other hand, the following code returns 'false' in spite of
* the same underlying C++ objects.
*
*   Model m = new Model();
*   m.createReaction();
*   Reaction r1 = m.getReaction(0);
*   Reaction r2 = m.getReaction(0);
*   return r1.equals(r2);  <---- this returns 'false'
*
* The following override changes the behaviour of 'equals' method such that
* returns 'true' if the given two objects refer to the same underlying C++ 
* object (i.e. 'true' is returned in the both above examples).
*
* (Unfortunately, '==' operator can't be overidden in Java.
*  Thus, the underlying C++ objects can't be compared by the '==' operator.)
* 
*/

%define SWIGJAVA_EQUALS(CLASS)
%typemap("javacode") CLASS
%{
	/**
* Equality comparison method for CLASS.
* <p>
* Because the Java methods for libCombine are actually wrappers around code
* implemented in C++ and C, certain operations will not behave as
* expected.  Equality comparison is one such case.  An instance of a
* libCombine object class is actually a <em>proxy object</em>
* wrapping the real underlying C/C++ object.  The normal <code>==</code>
* equality operator in Java will <em>only compare the Java proxy objects</em>,
* not the underlying native object.  The result is almost never what you
* want in practical situations.  Unfortunately, Java does not provide a
* way to override <code>==</code>.
*  <p>
* The alternative that must be followed is to use the
* <code>equals()</code> method.  The <code>equals</code> method on this
* class overrides the default java.lang.Object one, and performs an
* intelligent comparison of instances of objects of this class.  The
* result is an assessment of whether two libCombine Java objects are truly 
* the same underlying native-code objects.
*  <p>
* The use of this method in practice is the same as the use of any other
* Java <code>equals</code> method.  For example,
* <em>a</em><code>.equals(</code><em>b</em><code>)</code> returns
* <code>true</code> if <em>a</em> and <em>b</em> are references to the
* same underlying object.
*
* @param sb a reference to an object to which the current object
* instance will be compared
*
* @return <code>true</code> if <code>sb</code> refers to the same underlying 
* native object as this one, <code>false</code> otherwise
*/
	public boolean equals(Object sb)
	{
		if ( this == sb ) 
		{
			return true;
		}
		return swigCPtr == getCPtr((CLASS)(sb));
	}

	/**
* Returns a hashcode for this CLASS object.
*
* @return a hash code usable by Java methods that need them.
*/
	public int hashCode()
	{
		return (int)(swigCPtr^(swigCPtr>>>32));
	}
	%}
%enddef

SWIGJAVA_EQUALS(CaBase)
SWIGJAVA_EQUALS(CaReader)
SWIGJAVA_EQUALS(CaWriter)
SWIGJAVA_EQUALS(ASTNode)
SWIGJAVA_EQUALS(CVTerm)
SWIGJAVA_EQUALS(Date)
SWIGJAVA_EQUALS(ModelHistory)
SWIGJAVA_EQUALS(ModelCreator)
SWIGJAVA_EQUALS(XMLNamespaces)
SWIGJAVA_EQUALS(CaNamespaces)
SWIGJAVA_EQUALS(XMLAttributes)
SWIGJAVA_EQUALS(XMLToken)
SWIGJAVA_EQUALS(XMLNode)
SWIGJAVA_EQUALS(XMLTriple)
SWIGJAVA_EQUALS(XMLError)
SWIGJAVA_EQUALS(XMLErrorLog)
SWIGJAVA_EQUALS(XMLOutputStream)

/**
* Part of libCombine methods takeover ownership of passed-in objects, so we need
* to make sure SWIG disowns the object.
* (Most libCombine methods don't takeover ownership since 3.0.0)
*
*/

/**
* takeover ownership
*
* - void CaListOf::appendAndOwn(CaBase* item)
*/
%typemap(javain) CaBase*       item "CaBase.getCPtrAndDisown($javainput)";
%typemap(javain) const CaBase* item "CaBase.getCPtr($javainput)";

/**
* takeover ownership
*
* - void ASTNode::addChild (ASTNode* child)
* - void ASTNode::prependChild (ASTNode* child)
*/
%typemap(javain) ASTNode*       child "ASTNode.getCPtrAndDisown($javainput)";
%typemap(javain) const ASTNode* child "ASTNode.getCPtr($javainput)";

/**
* takeover ownership
*
* - void ASTNode::insertChild (unsigned int n, ASTNode *newChild)
* - void ASTNode::replaceChild(unsigned int n, ASTNode *newChild)
*/
%typemap(javain) ASTNode*       newChild "ASTNode.getCPtrAndDisown($javainput)";
%typemap(javain) const ASTNode* newChild "ASTNode.getCPtr($javainput)";

/**
* takeover ownership
*
* - void ASTNode::addSemanticsAnnotation (XMLNode* sAnnotation);
*/
%typemap(javain) XMLNode*       sAnnotation "XMLNode.getCPtrAndDisown($javainput)";
%typemap(javain) const XMLNode* sAnnotation "XMLNode.getCPtr($javainput)";


/**
* On Windows, a string for filename should be encoded by ANSI CP 
* instead of UTF-8 because file I/O APIs internally used in libCombine 
* requires an ANSI CP encoded string for the given filename.
*  
*  1) CaReader::readOMEX(const std::string& filename)
*  2) readOMEX(const char* filename)
*  3) CaWriter::writeOMEX(CaOmexManifest*, const std::string& filename)
*  4) writeOMEX(CaOmexManifest*, const char* filename)
*/

//
// UTF8 -> ANSI CP (for const std::string& filename)
//
%typemap("in") const std::string& filename (const char* arg_pstr, std::string arg_str) 
%{
	if(!$input) {
		SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null std::string");
		return $null;
	}
	arg_pstr = (char const *)jenv->GetStringUTFChars($input, 0);
	if (!arg_pstr) return $null;
#ifdef WIN32
	char*  mbstr = convertUTF8ToACP(arg_pstr);
	if (!mbstr)
	{
		jenv->ReleaseStringUTFChars($input, arg_pstr);
		return $null;
	}

	arg_str.assign(mbstr);
	delete[] mbstr;
#else
	arg_str.assign(arg_pstr);
#endif
	$1 = &arg_str;
	jenv->ReleaseStringUTFChars($input, arg_pstr);

	%}



//
// Unicode -> ANSI CP (for const char* filename)
//
%typemap("in")  const char* filename (const char* arg_pstr)
%{
	if ($input) {
		arg_pstr = (char const *)jenv->GetStringUTFChars($input, 0);
		if (!arg_pstr) return $null;
	}
	else
	{
		arg_pstr = 0;
	}
#ifdef WIN32
	$1 = convertUTF8ToACP(arg_pstr);
	if (!$1)
	{
		jenv->ReleaseStringUTFChars($input, (const char*)arg_pstr);
		return $null;
	}
	jenv->ReleaseStringUTFChars($input, (const char*)arg_pstr);
#else
	$1 = (char*)arg_pstr;
#endif
	%}

%typemap("freearg")  const char* filename 
%{
#ifdef WIN32
	delete[] $1;
#else
	if ($1) jenv->ReleaseStringUTFChars($input, (const char*)$1);
#endif
	%}


/**
* Some combinations of platforms and underlying XML parsers *require*
* an absolute path to a filename while others do not.  It's best to
* hide this from the end-user by making CaReader.readOMEX() and
* readOMEX() always compute an absolute path and filename.
*/

%pragma(java) modulecode =
%{
	static String getAbsolutePath(String filename)
	{
		java.io.File file = new java.io.File(filename);
		return file.getAbsolutePath();
	}
	%}

%typemap("javain") const std::string& filename "libcombine.getAbsolutePath($javainput)";
%typemap("javain") const char* filename        "libcombine.getAbsolutePath($javainput)";

/**
* Wraps std::ostream by implementing three simple wrapper classes.
*
* 1) OStream wraps std::cout, std::cerr, and std::clog.
*    The following public final static variables are provied in
*    libcombine class like in C++.
*
*    1. public final static OStream cout;
*    2. public final static OStream cerr;
*    3. public final static OStream clog;
*
* 2) OFStream (derived class of OStream) wraps std::ofstream 
*    with ios_base::cout (default) or ios_base::app flag. 
*
* 3) OStringStream (derived class of OStream) wraps std::ostringstream.
*
* These wrapper classes provide only the minimum functions.
*
* (sample code) -----------------------------------------------------
*
* 1. wraps std::cout
*
*    XMLOutputStream xos = new XMLOutputStream(libcombine.cout);
*
* 2. wraps std::cerr
*
*    CaOmexManifest d = libcombine.readOMEX("foo.xml");
*    if ( d.getNumErrors() > 0) {
*       d.printErrors(libcombine.cerr);
*    }
*
* 3. wraps std::ofstream (write to file "foo.xml")
*
*    OFStream   ofs = new OFStream("foo.xml");
*    CaOmexManifest d = libcombine.readOMEX("foo.xml");
*    CaWriter   w = new CaWriter();
*    w.writeOMEX(d,ofs);
*
* 4. wraps std::ofstream (write to file "foo.xml" with append mode)
*
*    OFStream ofs = new OFStream("foo.xml",true);
*    XMLOutputStream xos = new XMLOutputStream(ofs);
*
* 5. wraps std::ostringstream 
*
*    OStringStream   oss = new OStringStream();
*    XMLOutputStream xos = new XMLOutputStream(oss);
*    ...
*    oss.endl();
*    String s = oss.str();
*
*/

%typemap(jstype) std::ostream& "OStream"
%typemap(javain) std::ostream& "SWIGTYPE_p_std__ostream.getCPtr($javainput.get_ostream())";

%include "OStream.h"

%{
#include "OStream.cpp"
	%}

%pragma(java) modulecode =
%{
	/**
* Stream handle for low-level C++ standard output stream.
* <p>
* A few libCombine methods accept an argument for indicating where to send
* text string output.  An example is the {@link
* CaOmexManifest#printErrors} method.  However, the methods use C++ style
* streams and not Java stream objects.  The OStream object class in the
* libCombine Java interface provides a wrapper for the underlying C++
* streams.  The present object (cout) is a static final variable that
* can be used directly from your code.  An example use might be
* something like this:
* <p>
* <div class="fragment"><pre class="fragment">
* CaOmexManifest document = libcombine.readOMEX("somefile.xml");
* if (document.getNumErrors() > 0)
* {
*     document.printErrors(libcombine.cout);
*     println("Please correct the above problems first.");
*     System.exit(1);
* }</div>
*
* @see #cerr
* @see #clog
*/
	public final static OStream cout;


	/**
* Stream handle for low-level C++ standard error stream.
* <p>
* A few libCombine methods accept an argument for indicating where to send
* text string output.  An example is the {@link
* CaOmexManifest#printErrors} method.  However, the methods use C++ style
* streams and not Java stream objects.  The OStream object class in the
* libCombine Java interface provides a wrapper for the underlying C++
* streams.  The present object (cerr) is a static final variable that
* can be used directly from your code.  An example use might be
* something like this:
* <p>
* <div class="fragment"><pre class="fragment">
* CaOmexManifest document = libcombine.readOMEX("somefile.xml");
* if (document.getNumErrors() > 0)
* {
*     document.printErrors(libcombine.cerr);
*     println("Please correct the above problems first.");
*     System.exit(1);
* }</div>
* <p>
* By default, most operating systems have have their standard error and
* logging output streams directed to the console/terminal, and this is
* where text messages will be shown.  This can usually be redirected
* elsewhere, although how to do this depends on the specific environment
* where the program is running.
*
* @see #cout
* @see #clog
*/
	public final static OStream cerr;


	/**
* Stream handle for low-level C++ standard logging stream.
* <p>
* A few libCombine methods accept an argument for indicating where to send
* text string output.  An example is the {@link
* CaOmexManifest#printErrors} method.  However, the methods use C++ style
* streams and not Java stream objects.  The OStream object class in the
* libCombine Java interface provides a wrapper for the underlying C++
* streams.  The present object (clog) is a static final variable that
* can be used directly from your code.  An example use might be
* something like this:
* <p>
* <div class="fragment"><pre class="fragment">
* CaOmexManifest document = libcombine.readOMEX("somefile.xml");
* if (document.getNumErrors() > 0)
* {
*     document.printErrors(libcombine.clog);
*     println("Please correct the above problems first.");
*     System.exit(1);
* }</div>
* <p>
* By default, most operating systems have have their standard error and
* logging output streams directed to the console/terminal, and this is
* where text messages will be shown.  This can usually be redirected
* elsewhere, although how to do this depends on the specific environment
* where the program is running.
*
* @see #cout
* @see #cerr
*/
	public final static OStream clog;

	static {
		cout = new OStream(OStream.COUT); 
		cerr = new OStream(OStream.CERR); 
		clog = new OStream(OStream.CLOG); 
	}

	/**
* This private constructor does nothing and never invoked.
* The purpose of this constuctor is to hide a default constructor of this 
* class in javadoc documentation.
*/
	private libcombine() {}

	%}



/**
*  Wraps the following functions by using the corresponding
*  ListWrapper<TYPENAME> class.
*
*  - List* ModelHistory::getListCreators()
*  - List* ModelHistory::getListModifiedDates()
*  - List* CaBase::getCVTerms()
*  - List* CaNamespaces::getSupportedNamespaces()
*
*  ListWrapper<TYPENAME> class is wrapped as TYPENAMEListclass.
*  So, the above functions are wrapped as follows:
*
*  - ModelCreatorList ModelHistory.getListCreators()
*  - DateList         ModelHistory.getListModifiedDates()
*  - CVTermList       CaBase.getCVTerms()
*  - CaNamespacseList CaNamespaces.getSupportedNamespaces()
*
*/

%define LIST_WRAPPER(_FNAME_,_TYPENAME_)
%typemap(jstype)  List* _FNAME_ %{ _TYPENAME_ ## List %}

%typemap(javaout) List* _FNAME_ 
{ 
	long cPtr = $jnicall;
	return (cPtr == 0) ? null : new  _TYPENAME_ ## List(cPtr, true);
}

%typemap(out) List* _FNAME_ 
{
	ListWrapper<_TYPENAME_> *listw = ($1 != 0) ? new ListWrapper<_TYPENAME_>($1) : 0;  
	*( ListWrapper<_TYPENAME_>   **)&$result = listw;
}
%enddef

LIST_WRAPPER(CaBase::getCaListOfAllElements,CaBase)


