# ifndef SEMSIM_MODEL_H_
# define SEMSIM_MODEL_H_


# include "semsim/Component.h"
# include "semsim/Process.h"

namespace semsim {

    /// The type used to store the collection of @ref Component "Components". Treat as opaque.
    typedef std::vector<ComponentPtr> Components;

    /**
     * A @ref Component is any element of an SBML or CellML model.
     * It can represent an SBML species, reaction, or compartment.
     */
    class  SemsimModel {
    public:

        // Empty ctor
        SemsimModel() = default;

        /// Virtual destructor
        virtual ~SemsimModel() = default;

        /// Copy ctor
        SemsimModel(const SemsimModel &other) {
            for (const auto &component : other.components_) {
                components_.push_back(ComponentPtr(component->clone()));
            }
        }

        /// Move ctor
        SemsimModel(SemsimModel &&other) noexcept : components_(std::move(other.components_)) {}

        /// Add a new component to the model (copy)
        Component *addComponent(const Component &component) {
            components_.push_back(ComponentPtr(new Component(component)));
            return &*components_.back();
        }

        /// Add a new component to the model (copy)
        Process *addComponent(const Process &component) {
            components_.push_back(ComponentPtr(new Process(component)));
            return (Process *) &*components_.back();
        }

        /// Add a new component to the model (move)
        Component *addComponent(Component &&component) {
            components_.emplace_back(new Component(std::move(component)));
            return &*components_.back();
        }

        /// Add a new physical process to the model (move)
        Process *addComponent(Process &&component) {
            components_.emplace_back(new Process(std::move(component)));
            return (Process *) &*components_.back();
        }

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        const Components &getComponents() const {
            return components_;
        }

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        Components &getComponents() {
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
         * to the original SBML or CellML model using a Url.
         * Usually, the RDF will be written to a COMBINE archive
         * along with the model, in which case the @p sbml_base_uri
         * argument should be the relative path to the model file
         * in the COMBINE archive.
         * @param  format        The RDF serialization format. Choices include "rdfxml", "ntriples", "turtle", "trig", "rss-tag-soup", "grddl", "rdfa", "json", and "nquads".
         * @param  sbml_base_uri A Url that points to the original model file. Usually a relative path in a COMBINE archive.
         * @return               A string representation of the RDF for model using the desired RDF serialization format.
         */
        virtual std::string getRDF(Url &sbml_base_uri, const std::string &format) const = 0;

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const {
            std::string result;
            for (const auto &component : components_)
                result += component->humanize() + "\n";
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
        bool hasComponentWithMetaId(const std::string &metaid) const {
            for (const auto &component : components_) {
                if (component->hasMetaId() && component->getMetaId() == metaid)
                    return true;
            }
            return false;
        }

        /**
         * @return @c true if the model has a component with this meta id, false otherwise.
         * @param  metaid The meta id to look for.
         */
        Component &findComponentWithMetaId(const std::string &metaid) {
            for (const auto &component : components_) {
                if (component->hasMetaId() && component->getMetaId() == metaid)
                    return *component;
            }
            throw std::runtime_error("No component with meta id " + metaid);
        }

        /**
         * @return @c true if the model has a component with this meta id, false otherwise.
         * @param  metaid The meta id to look for.
         */
        const Component &findComponentWithMetaId(const std::string &metaid) const {
            for (const auto &component : components_) {
                if (component->hasMetaId() && component->getMetaId() == metaid)
                    return *component;
            }
            throw std::runtime_error("No component with meta id " + metaid);
        }

        bool containsMetaId(const std::string &metaid) const {
            for (const auto &component : components_) {
                if (component->containsMetaId(metaid))
                    return true;
            }
            return false;
        }

    protected:
        // Stores the @ref Component "Components" for this model.
        Components components_;
    };

}

# endif
