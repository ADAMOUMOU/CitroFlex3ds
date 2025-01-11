/**
 * @file Logging.cpp
 * @author ADAMOUMOU
 * @brief CitroFlex logging system implementation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#include "Logging.hpp"

using namespace Debug;


Logger::Logger(const char* file) {
    filename = file;
    fsInit();
}

bool Logger::Log(char data[]) {
    if (NOLOG) { return false; }

    file = fopen(filename, "a");

    size_t dataSize = sizeof(data);
    size_t elementsWritten = fwrite(data, dataSize, sizeof(data) / dataSize, file);

    fclose(file);

    // Check if the writing was successful
    return elementsWritten == sizeof(data) / dataSize;

}

bool Logger::LogUnmanaged(char data[]) {
    if (NOLOG) { return false; }

    size_t dataSize = sizeof(data);
    size_t elementsWritten = fwrite(data, dataSize, sizeof(data) / dataSize, file);

    // Check if the writing was successful
    return elementsWritten == sizeof(data) / dataSize;
}

void Logger::OpenFile() {
    file = fopen(filename, "a");
}

void Logger::CloseFile() {
    fclose(file);
}

Logger::~Logger() {
    fsExit();
}
