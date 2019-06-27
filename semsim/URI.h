# ifndef SEMSIM_URI_H_
# define SEMSIM_URI_H_

# include <string>

namespace semsim {

    /**
     * A URI class used in semgen.
     * @param uri_encoding A string encoding of the URI.
     */
    class URI {
      public:
        URI(const std::string& uri)
            : encoded_uri_(uri) {}

        std::string toString() const {
          return encoded_uri_;
        }

      protected:
        std::string encoded_uri_;
    };

}

# endif
