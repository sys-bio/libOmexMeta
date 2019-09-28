# ifndef SEMSIM_QUERY_QUERY_RESULTS_H_
# define SEMSIM_QUERY_QUERY_RESULTS_H_



namespace semsim {

    /**
     * Class for storing the results of a query.
     * @c begin and @c end iterators can be used to access
     * elements returned by the query.
     */
    class SEMSIM_PUBLIC QueryResults {
      protected:
        typedef std::vector<Component*> ComponentRefs;
        ComponentRefs refs_;
      public:
        /// Iterator type for the query results.
        typedef ComponentRefs::iterator iterator;

        /// @return An iterator to the beginning of the resutls.
        iterator begin() { return refs_.begin(); }

        /// @return An iterator to the end of the resutls.
        iterator end() { return refs_.end(); }

        /// Const iterator type for the query results.
        typedef ComponentRefs::const_iterator const_iterator;

        /// @return A const iterator to the beginning of the resutls.
        const_iterator begin() const { return refs.begin(); }

        /// @return A const iterator to the beginning of the resutls.
        const_iterator end() const { return refs.end(); }

    };

}

# endif
