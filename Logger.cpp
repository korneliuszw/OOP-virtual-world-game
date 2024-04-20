//
// Created by kwojn on 4/7/2024.
//

#include "Logger.h"
#include "ScrollableList.h"

std::ofstream &LoggerSystem::getDebugLogFile() {
    this->debuggerLogger.debugLogFile << "[" << this->debuggerLogger.n << "] ";
    this->debuggerLogger.n += 1;
    return this->debuggerLogger.debugLogFile;
}

LoggerSystem::InfoLogger &LoggerSystem::getInfoLogFile() {
    this->getDebugLogFile();
    this->infoLogger.infoLogFile << "[" << this->infoLogger.n << "] ";
    this->infoLogger.n += 1;
    return this->infoLogger;
}

void LoggerSystem::setScreenOutput(ScrollableList *screenOutput) {
    this->infoLogger.setScreenOutput(screenOutput);

}

LoggerSystem::InfoLogger::InfoLogger(LoggerSystem::DebugLogger &debugLogger) : debugLogger(debugLogger),
                                                                               infoLogFile("info_log.txt") {
    // reopen the file so it it's content gets cleared
    this->infoLogFile.close();
    this->infoLogFile.open("info_log.txt", std::ios::out | std::ios::app);
}

LoggerSystem::InfoLogger &LoggerSystem::InfoLogger::operator<<(std::ostream &(*fun)(std::ostream &)) {
    this->debugLogger.debugLogFile << std::endl;
    this->infoLogFile << std::endl;
    flushNext = true;
    if (screenOutput)
        screenOutput->append(getLastOutput());
    return *this;
}

std::string LoggerSystem::InfoLogger::getLastOutput() {
    return lastLogStream.str();
}

void LoggerSystem::InfoLogger::setScreenOutput(ScrollableList *screenOutput) {
    InfoLogger::screenOutput = screenOutput;
}


LoggerSystem::DebugLogger::DebugLogger() : debugLogFile("debug_log.txt") {
    this->debugLogFile.close();
    this->debugLogFile.open("debug_log.txt", std::ios::out | std::ios::app);
}

LoggerSystem *logger = new LoggerSystem();