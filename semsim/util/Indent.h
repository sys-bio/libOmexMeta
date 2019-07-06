# ifndef SEMSIM_INDENT_H_
# define SEMSIM_INDENT_H_

# include "semsim/Preproc.h"

namespace semsim {

    /// Simply returns a number of whitespaces
    inline std::string spaces(std::size_t k) {
      return std::string(k,' ');
    }

}

# endif
