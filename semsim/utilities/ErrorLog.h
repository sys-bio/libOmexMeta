#include <string>
#include <vector>
#include <list>
#include <optional>

namespace semsim {
    namespace utilities {
        class ErrorEntry;
    }
}

namespace semsim {
    namespace utilities {


        /**
         * Class for storing errors that may occur when processing models and associated data
         *
         *
         */
        class ErrorLog {
          private:
            static std::list<ErrorEntry*> errorqueue;
            static PrintWriter* logfilewriter;

            /**
             * Add an error to the error log
             * @param e An error message
             * @param isfatal Whether the error is fatal
             * @param addtologfilewriter Whether to add to this object's PrintWriter
             */
          public:
            static void addError(const std::wstring& e, std::optional<bool>& isfatal, bool addtologfilewriter);

            /** @return The first error in the log */
            static ErrorEntry* getFirstError();

            /** @return Whether any errors have been added to the log */
            static bool hasErrors();

            /**
             * Set the PrintWriter used to output the log
             * @param logger PrintWriter used for output
             */
            static void setLogFile(PrintWriter* logger);

            /** Clear the error log */
            static void flush();

            /** @return List of all errors in the log */
            static std::vector<ErrorEntry*> getAllErrors();

            /** @return Whether any errors in the log are fatal */
            static bool errorsAreFatal();

            /** @return List of all errors in the log (function also clears the error log) */
            static std::vector<ErrorEntry*> getAllErrorsandFlush();

        };

    }
}