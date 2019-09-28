# ifndef SEMSIM_QUERY_QUERY_H_
# define SEMSIM_QUERY_QUERY_H_



namespace semsim {

    /**
     * The base class for all queries in libSemSim.
     */
    class SEMSIM_PUBLIC Query {
      public:
        /// Virtual dtor
        virtual ~Query()

        /**
         * Run the query on a model. The model must be passed in as a
         * reference because the return results will contain element references.
         * @param  model The model to run the query on.
         * @return       The query results.
         */
        virtual QueryResults run(Model& model) const = 0;
    };

    /**
     * An owning pointer for a @ref Query.
     * Automatically uses std::unique_ptr or std::tr1::shared_ptr depending on C++ standard.
     * @see UniquePtr.
     */
    typedef UniquePtr<Query>::type QueryPtr;

}

# endif
