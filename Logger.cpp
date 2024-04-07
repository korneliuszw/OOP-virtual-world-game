//
// Created by kwojn on 4/7/2024.
//

#include "Logger.h"

std::ofstream &Logger::getDebugLogFile() {
    return this->debuggerLogger.debugLogFile;
}

Logger::InfoLogger &Logger::getInfoLogFile()  {
    return this->infoLogger;
}

Logger::Logger(): infoLogger(debuggerLogger) {

}

Logger::InfoLogger::InfoLogger(Logger::DebugLogger &debugLogger) : debugLogger(debugLogger) {
    this->infoLogFile.open("info_log.txt");
}

Logger::InfoLogger &Logger::InfoLogger::operator<<(std::ostream &(*fun)(std::ostream &)) {
    this->debugLogger.debugLogFile.flush();
    this->infoLogFile.flush();
    return *this;
}


Logger::DebugLogger::DebugLogger() {
    this->debugLogFile.open("debug_log.txt");
}
