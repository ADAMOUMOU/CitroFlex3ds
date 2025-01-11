/**
 * @file Logging.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex logging system
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>

#define NOLOG false

namespace Debug
{
    /** @brief Logger class for writing debug information to files */
    class Logger
    {
    private:
        const char *filename;
        FILE *file;

    public:
        /** @brief Initialize the logger
         *  @param file Path to the log file
         */
        Logger(const char *file);

        /** @brief Log data with automatic file management
         *  @param data Data to write to log
         *  @return true if writing was successful
         */
        bool Log(char data[]);

        /** @brief Log data without automatic file management. You will have to handle the file opening and closing
         *  manually with OpenFile() and CloseFile() methods but it's faster than Log() method.
         *  @param data Data to write to log
         *  @return true if writing was successful
         *  @note Use with OpenFile() and CloseFile()
         */
        bool LogUnmanaged(char data[]);

        /** @brief Open the log file for unmanaged log */
        void OpenFile();

        /** @brief Close the log file after unmanaged log */
        void CloseFile();

        /** @brief Clean up logger resources */
        ~Logger();
    };

    
} // namespace debug

