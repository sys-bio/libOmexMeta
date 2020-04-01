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
        /// Empty constructor
        URI() = default;

        /// Construct from string-encoded URI
        URI(const std::string &uri)
                : encoded_uri_(uri) {}

        /// Construct from a string literal
        URI(const char *uri)
                : encoded_uri_(uri) {}


        /// Construct from string-encoded URI
        explicit URI(std::string &&uri)
                : encoded_uri_(std::move(uri)) {}


        /// Convert to human-readable string
        std::string toString() const {
            return encoded_uri_;
        }

        /// Convert to encoded UTF-8 URI string (possibly different from human-readable string).
        std::string encode() const {
            return encoded_uri_;
        }

        /**
         * Append to the fragment part of the URI.
         * @param  suffix The string to append to the fragment.
         * @return        The new URI.
         */
        URI appendToFrag(const std::string &suffix) const {
            // TODO: URI processing
            return URI(encoded_uri_ + suffix);
        }

        /**
         * Set the fragment part of the URI to the given string
         * and return it as a new URI.
         * @param  suffix The string to append to the fragment.
         * @return        The new URI.
         */
        URI withFrag(const std::string &suffix) const {
            // TODO: URI processing
            return URI(encoded_uri_ + "#" + suffix);
        }

        /// Comparison operator
        bool operator==(const URI &other) const {
            return encoded_uri_ == other.encoded_uri_;
        }

    protected:
        std::string encoded_uri_;
    };

}

# endif
