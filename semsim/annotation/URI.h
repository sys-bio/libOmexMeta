# ifndef SEMSIM_URI_H_
# define SEMSIM_URI_H_

# include <string>
# include "semsim/annotation/URI.h"

namespace semsim {

    /**
     * A URI class used in semgen.
     * @param uri_encoding A string encoding of the URI.
     */
    class URI {
      public:
        URI(const std::string& uri_encoding)
            : uri_encoding_(uri_encoding) {}

      protected:
        std::string uri_encoding_;
    };

}

# endif
