/**
 * @file Random.hpp
 * @author ADAMOUMOU
 * @brief CitroFlex random number generation
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024 ADAMOUMOU
 * This project is released under the MIT License.
 * See the LICENSE file for details.
 */

#pragma once
#include <random>
#include <string>

/**
 * @namespace Random
 * @brief Utility namespace for random number generation
 */
namespace Random {
    /**
     * @brief Generates a random integer in the range [min, max]
     * @param min The minimum value (inclusive)
     * @param max The maximum value (inclusive)
     * @return A random integer between min and max
     */
    int Range(int min, int max);
    
    /**
     * @brief Generates a random floating-point number in the range [min, max]
     * @param min The minimum value (inclusive)
     * @param max The maximum value (inclusive)
     * @return A random float between min and max
     */
    double Range(double min, double max);
    
    /**
     * @brief Generates a random UUID v4
     * @return A string representing the UUID in 8-4-4-4-12 format
     */
    std::string UUID();
    
    /**
     * @brief Gets the random number generator instance
     * @return A reference to the Mersenne Twister generator
     * @note Internal function used by other namespace functions
     */
    std::mt19937& GetGenerator();
}

