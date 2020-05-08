#ifndef LIBSEMGEN_ERROR_H
#define LIBSEMGEN_ERROR_H

#include "exception"
#include "iostream"

namespace semsim {
    /// https://stackoverflow.com/questions/8152720/correct-way-to-inherit-from-stdexception
    class Exception : public std::exception {
    public:
        /** Constructor (C strings).
         *  @param message C-style string error message.
         *                 The string contents are copied upon construction.
         *                 Hence, responsibility for deleting the char* lies
         *                 with the caller.
         */
        explicit Exception(const char *message) :
                msg_(message) {
        }

        /** Constructor (C++ STL strings).
         *  @param message The error message.
         */
        explicit Exception(std::string message) :
                msg_(std::move(message)) {}

        /** Destructor.
         * Virtual to allow for subclassing.
         */
        ~Exception() noexcept override = default;

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a const char*. The underlying memory
         *          is in posession of the Exception object. Callers must
         *          not attempt to free the memory.
         */
        const char *what() const noexcept override {
            return msg_.c_str();
        }

    protected:
        /** Error message.
         */
        std::string msg_;
    };

    class NullPointerException : public Exception {
        using Exception::Exception;
    };

    class InappropriateResourceException : public Exception {
        using Exception::Exception;
    };

    class NotImplementedException : public Exception {
        using Exception::Exception;
    };

    class LibRDFException : public Exception {
        using Exception::Exception;
    };
    class ValueException : public Exception {
        using Exception::Exception;
    };

    class AnnotationBuilderException : public Exception {
        using Exception::Exception;
    };

};

#endif //LIBSEMGEN_ERROR_H
