# ifndef SEMSIM_MODEL_H_
# define SEMSIM_MODEL_H_

# include "semsim/Preproc.h"
# include "semsim/Component.h"
# include "semsim/Process.h"

namespace semsim {

    /**
     * A @ref Component is any element of an SBML or CellML model.
     * It can represent an SBML species, reaction, or compartment.
     */
    class SEMSIM_PUBLIC Model {
      public:
        /// The type used to store the collection of @ref Component "Components". Treat as opaque.
        typedef std::vector<ComponentPtr> Components;

        // Empty ctor
        Model() {}

        /// Virtual destructor
        virtual ~Model() {}

        /// Move ctor
        Model(Model&& other)
          : components_(std::move(other.components_)) {}

        /// Add a new component to the model (copy)
        Component* addComponent(const Component& component) {
          components_.push_back(ComponentPtr(new Component(component)));
          return &*components_.back();
        }

        /// Add a new component to the model (copy)
        Process* addComponent(const Process& component) {
          components_.push_back(ComponentPtr(new Process(component)));
          return (Process*)&*components_.back();
        }

        # if __cplusplus >= 201103L
        /// Add a new component to the model (move)
        Component* addComponent(Component&& component) {
          components_.emplace_back(new Component(std::move(component)));
          return &*components_.back();
        }

        /// Add a new physical process to the model (move)
        Process* addComponent(Process&& component) {
          components_.emplace_back(new Process(std::move(component)));
          return (Process*)&*components_.back();
        }
        # endif

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        const Components& getComponents() const {
          return components_;
        }

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        Components& getComponents() {
          return components_;
        }

        /**
         * Get the number of components in the model.
         */
        std::size_t getNumComponents() const {
          return components_.size();
        }

        /**
         * Get the RDF serialization of this model.
         * The serialized RDF will always need to refer back
         * to the original SBML or CellML model using a URI.
         * Usually, the RDF will be written to a COMBINE archive
         * along with the model, in which case the @p sbml_base_uri
         * argument should be the relative path to the model file
         * in the COMBINE archive.
         * @param  format        The RDF serialization format. Choices include "rdfxml", "ntriples", "turtle", "trig", "rss-tag-soup", "grddl", "rdfa", "json", and "nquads".
         * @param  sbml_base_uri A URI that points to the original model file. Usually a relative path in a COMBINE archive.
         * @return               A string representation of the RDF for model using the desired RDF serialization format.
         */
        virtual std::string getRDF(const URI& sbml_base_uri, const std::string& format="rdfxml") const = 0;

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const {
          std::string result;
          for (Components::const_iterator i=components_.begin(); i!= components_.end(); ++i)
            result += (*i)->humanize()+"\n";
          return result;
        }

        /**
         * Return the XML encoding of the attached SBML or CellML model.
         * @return The XML content.
         */
        virtual std::string encodeXML() const = 0;

        /**
         * @return "sbml" if an SBML model, "cellml" if a cellml model.
         */
        virtual std::string getFormat() const = 0;

        /**
         * @return @c true if the model has a component with this meta id, false otherwise.
         * @param  metaid The meta id to look for.
         */
        bool hasComponentWithMetaId(const std::string& metaid) const {
          // std::cerr << "num components: " << components_.size() << "\n";
          for (Components::const_iterator i=components_.begin(); i!=components_.end(); ++i) {
            // if ((*i)->hasMetaId())
              // std::cerr << "meta id of component " << (*i)->getMetaId() << " vs " << metaid << "\n";
            // else
              // std::cerr << "component doesn't have metaid\n";
            if ((*i)->hasMetaId() && (*i)->getMetaId() == metaid)
              return true;
          }
          return false;
        }

        /**
         * @return @c true if the model has a component with this meta id, false otherwise.
         * @param  metaid The meta id to look for.
         */
        Component& findComponentWithMetaId(const std::string& metaid) {
          for (Components::const_iterator i=components_.begin(); i!=components_.end(); ++i) {
            if ((*i)->hasMetaId() && (*i)->getMetaId() == metaid)
              return **i;
          }
          throw std::runtime_error("No component with meta id " + metaid);
        }

        /**
         * @return @c true if the model has a component with this meta id, false otherwise.
         * @param  metaid The meta id to look for.
         */
        const Component& findComponentWithMetaId(const std::string& metaid) const {
          for (Components::const_iterator i=components_.begin(); i!=components_.end(); ++i) {
            if ((*i)->hasMetaId() && (*i)->getMetaId() == metaid)
              return **i;
          }
          throw std::runtime_error("No component with meta id " + metaid);
        }

      protected:
        Model(const Model& other) {}

        // Stores the @ref Component "Components" for this model.
        Components components_;
    };

}

# endif
