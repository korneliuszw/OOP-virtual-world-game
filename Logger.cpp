//
// Created by kwojn on 4/7/2024.
//

#include "Logger.h"

std::ofstream &Logger::getDebugLogFile() {
    this->debuggerLogger.debugLogFile << "[" << this->debuggerLogger.n << "] ";
    this->debuggerLogger.n+=1;
    return this->debuggerLogger.debugLogFile;
}

Logger::InfoLogger &Logger::getInfoLogFile()  {
    this->getDebugLogFile();
    this->infoLogger.infoLogFile << "[" << this->infoLogger.n << "] ";
    this->infoLogger.n += 1;
    return this->infoLogger;
}

Logger::Logger(): infoLogger(debuggerLogger) {

}

Logger::InfoLogger::InfoLogger(Logger::DebugLogger &debugLogger) : debugLogger(debugLogger) {
    this->infoLogFile.open("info_log.txt");
}

Logger::InfoLogger &Logger::InfoLogger::operator<<(std::ostream &(*fun)(std::ostream &)) {
    this->debugLogger.debugLogFile << std::endl;
    this->infoLogFile << std::endl;
    return *this;
}


Logger::DebugLogger::DebugLogger() {
    this->debugLogFile.open("debug_log.txt");
}
