//
// Created by kwojn on 4/7/2024.
//

#ifndef PROJEKT1_LOGGER_H
#define PROJEKT1_LOGGER_H


#include <fstream>


class Logger {
    class DebugLogger {
    public:
        std::ofstream debugLogFile;

        explicit DebugLogger();
    };
    class InfoLogger {
        DebugLogger& debugLogger;
    public:
        std::ofstream infoLogFile;
        explicit InfoLogger(DebugLogger &debugLogger);
        template<typename T>
        InfoLogger& operator<<(const T& value);
        // Handle std::endl
        InfoLogger& operator<<(std::ostream& (*fun)(std::ostream&));
    };
public:
    DebugLogger debuggerLogger;
    InfoLogger infoLogger;
    std::ofstream &getDebugLogFile();
    InfoLogger &getInfoLogFile();
    Logger();
    ~Logger() {
        debuggerLogger.debugLogFile.flush();
        debuggerLogger.debugLogFile.close();
        infoLogger.infoLogFile.flush();
        infoLogger.infoLogFile.close();
    }
};

template<typename T>
Logger::InfoLogger &Logger::InfoLogger::operator<<(const T &value) {
    this->debugLogger.debugLogFile << value;
    this->infoLogFile << value;
    return *this;
}


static Logger logger;


#endif //PROJEKT1_LOGGER_H