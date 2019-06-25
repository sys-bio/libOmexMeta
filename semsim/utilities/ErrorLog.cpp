// #include "ErrorLog.h"
//
// namespace semsim {
//     namespace utilities {
//
//         std::list<ErrorEntry*> ErrorLog::errorqueue = new java::util::PriorityQueue<ErrorEntry*>();
//         java::io::PrintWriter* ErrorLog::logfilewriter;
//
//         void ErrorLog::addError(const std::wstring& e, std::optional<bool>& isfatal, bool addtologfilewriter) {
//             ErrorEntry tempVar(e, isfatal);
//             errorqueue.push_back(&tempVar);
//             if (addtologfilewriter) {
//                 logfilewriter->println(e);
//             }
//         }
//
//         ErrorEntry* ErrorLog::getFirstError() {
//             return errorqueue.pop_front();
//         }
//
//         bool ErrorLog::hasErrors() {
//             return !errorqueue.empty();
//         }
//
//         void ErrorLog::setLogFile(PrintWriter* logger) {
//             logfilewriter = logger;
//         }
//
//         void ErrorLog::flush() {
//             errorqueue.clear();
//         }
//
//         std::vector<ErrorEntry*> ErrorLog::getAllErrors() {
//             return std::vector<ErrorEntry*>(errorqueue);
//         }
//
//         bool ErrorLog::errorsAreFatal() {
//             for (auto e : errorqueue) {
//                 if (e->isfatal) {
//                     return true;
//                 }
//             }
//             return false;
//         }
//
//         std::vector<ErrorEntry*> ErrorLog::getAllErrorsandFlush() {
//             std::vector<ErrorEntry*> errors = getAllErrors();
//             flush();
//             return errors;
//         }
//     }
// }
