# ifndef SEMSIM_QUERY_CONDITION_H_
# define SEMSIM_QUERY_CONDITION_H_



namespace semsim {

    /**
     * The base class for all conditions in queries.
     */
    class SEMSIM_PUBLIC Condition {
      public:
        /// Virtual dtor
        virtual ~Condition()

        /// @return @c true if the condition matches the given element.
        virtual bool matches(const Component& component) = 0;
    };

    /**
     * An owning pointer for a @ref Condition.
     * Automatically uses std::unique_ptr or std::tr1::shared_ptr depending on C++ standard.
     * @see UniquePtr.
     */
    typedef UniquePtr<Condition>::type ConditionPtr;

}

# endif
