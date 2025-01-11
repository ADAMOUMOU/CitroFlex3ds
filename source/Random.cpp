/**
 * @file Random.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex random number generation implementation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#include "Random.hpp"
#include <sstream>
#include <iomanip>

namespace Random {
    std::mt19937& GetGenerator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    int Range(int min, int max) {
        std::uniform_int_distribution<> dis(min, max);
        return dis(GetGenerator());
    }

    double Range(double min, double max) {
        std::uniform_real_distribution<> dis(min, max);
        return dis(GetGenerator());
    }

    std::string UUID() {
        static const char hex_chars[] = "0123456789abcdef";
        static std::uniform_int_distribution<> dis(0, 15);
        
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        // 8-4-4-4-12
        for (int i = 0; i < 8; i++) 
            ss << hex_chars[dis(GetGenerator())];
        ss << "-";
        
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 4; i++)
                ss << hex_chars[dis(GetGenerator())];
            ss << "-";
        }
        
        for (int i = 0; i < 12; i++)
            ss << hex_chars[dis(GetGenerator())];

        return ss.str();
    }
} 