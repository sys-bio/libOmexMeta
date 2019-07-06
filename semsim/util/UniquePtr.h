# ifndef SEMSIM_UNIQUE_PTR_H_
# define SEMSIM_UNIQUE_PTR_H_

# include "semsim/Preproc.h"

# if __cplusplus >= 201103L
# include <memory>
# else
# include <tr1/memory>
# endif

namespace semsim {

    /**
     * This template is used to switch between the C++ tr1
     * implementation of unique_ptr (in C++03) and
     * the standard implementation in C++11.
     * The contained @p type definition will
     * resolve to tr1::shared_ptr (C++03) or
     * std::unique_ptr (C++11) depending on the current
     * C++ standard being used to compile the source.
     *
     * @code
     * // how to use
     * class MyClass {};
     * UniquePtr<MyClass> ptr = new MyClass();
     * // the type of ptr will be
     * std::unique_ptr<MyClass> in C++11 and
     * std::tr1::shared_ptr<MyClass> in C++03.
     * @endcode
     */
    template <typename T>
    struct UniquePtr {
      # if __cplusplus >= 201103L
        typedef std::unique_ptr<T> type;
      # else
        typedef std::tr1::unique_ptr<T> type;
      # endif
    };

}

# endif
