# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_

# include <string>

namespace semsim {
    class Resource {
      public:
        Resource(const std::string& uri)
            : uri_(uri) {}
      protected:
        std::string uri_;
    };
}
# endif
