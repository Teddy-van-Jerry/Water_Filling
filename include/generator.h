#ifndef GENERATOR_H
#define GENERATOR_H

#include "wf_global.h"
#include <random>
#include <cmath>

namespace wf {
    class Generator {

    public:
        Generator();

        Vec normal(int length, double m, double s);

        Vec uniform(int length, double min, double max);

    private:

        /**
         * @brief Normal Distribution
         * @details Use C++ random number engine
         * @param m means
         * @param s standard deviation
         * @return the random number
         */
        double normal(double m, double s);

        /**
         * @brief Uniform Distribution
         * @details Use C++ random number engine
         * @param min min
         * @param max max
         * @return the random number
         */
        double uniform(double min, double max);

        std::random_device rd;
        std::mt19937 mt;
    };

    Vec normalize(const Vec& v, double norm, double l = 2);

    Vec abs(const Vec& v);

}

#endif // GENERATOR_H
