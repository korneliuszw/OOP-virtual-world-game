//
// Created by kwojn on 4/7/2024.
//

#pragma once

#include <fstream>
#include <string>
#include <sstream>

class ScrollableList;

class LoggerSystem {
    class DebugLogger {
    public:
        std::ofstream debugLogFile;
        int n = 0;

        explicit DebugLogger();
    };

    class InfoLogger {
        DebugLogger &debugLogger;
        std::stringstream lastLogStream;
        bool flushNext = false;
    public:
        void setScreenOutput(ScrollableList *screenOutput);

    private:
        ScrollableList *screenOutput;
    public:
        int n = 0;
        std::ofstream infoLogFile;

        explicit InfoLogger(DebugLogger &debugLogger);

        template<typename T>
        InfoLogger &operator<<(const T &value);

        // Handle std::endl
        InfoLogger &operator<<(std::ostream &(*fun)(std::ostream &));

        [[nodiscard]] std::string getLastOutput();
    };

    DebugLogger debuggerLogger;
    InfoLogger infoLogger;
public:
    std::ofstream &getDebugLogFile();

    InfoLogger &getInfoLogFile();

    LoggerSystem() : infoLogger(debuggerLogger) {};

    void setScreenOutput(ScrollableList *screenOutput);
};

template<typename T>
LoggerSystem::InfoLogger &LoggerSystem::InfoLogger::operator<<(const T &value) {
    // we want to keep only last line of logs at a time so clear it after we flushed other outputs
    if (flushNext) {
        lastLogStream.str("");
        lastLogStream.clear();
        flushNext = false;
    }
    lastLogStream << value;
    this->debugLogger.debugLogFile << value;
    this->infoLogFile << value;
    return *this;
}

extern LoggerSystem *logger;
