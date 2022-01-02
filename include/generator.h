/**
 * @file generator.h
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief Random Data Generator
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022 Teddy van Jerry
 * 
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "wf_global.h"
#include <random>
#include <cmath>
#include <fstream>

namespace wf {
    /**
     * @brief Class for generating random data for optimization.
     * 
     */
    class Generator {

    public:
        Generator();

        /**
         * @brief Create a vector with normal distribution numbers.
         * @details This uses random engine std::mt19937.
         * @param length length of the vector
         * @param m means
         * @param s standard deviation
         * @return the vector with normal distribution
         */
        Vec normal(int length, double m, double s);

        /**
         * @brief Create a vector with uniform distribution numbers.
         * @details This uses random engine std::mt19937.
         * @param length length of the vector
         * @param min min
         * @param max max
         * @return the vector with uniform distribution
         */
        Vec uniform(int length, double min, double max);

        /**
         * @brief Save the data vector to file.
         * 
         * @param file file name
         * @param data data vector
         */
        bool saveAs(const Str& file, const Vec& data) const;

    private:

        /**
         * @brief Normal distribution.
         * @details Use C++ random number engine
         * @param m means
         * @param s standard deviation
         * @return the random number
         */
        double normal(double m, double s);

        /**
         * @brief Uniform distribution.
         * @details Use C++ random number engine
         * @param min min
         * @param max max
         * @return the random number
         */
        double uniform(double min, double max);

        std::random_device rd; ///< random device
        std::mt19937 mt; ///< random engine
    };

    /**
     * @brief Normalize the vector.
     * 
     * @param v vector
     * @param norm norm
     * @param l norm dimension
     * @return the normalized vector
     */
    Vec normalize(const Vec& v, double norm, double l = 2);

    /**
     * @brief Abs the vector.
     * 
     * @param v vector
     * @return the vector after Abs
     */
    Vec abs(const Vec& v);

}

#endif // GENERATOR_H
