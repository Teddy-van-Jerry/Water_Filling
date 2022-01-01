/**
 * @file waterfilling.h
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief Water Filling Optimization
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022 Teddy van Jerry
 * 
 */
#ifndef WATERFILLLING_H
#define WATERFILLLING_H

#include "wf_global.h"
#include "params.h"
#include "gnuplot-iostream.h"

namespace wf {

    /**
     * @brief Class for solving water filling optimization problem.
     * 
     */
    class WaterFilling {
    public:

        /**
         * @brief Solve the optimization problem.
         * 
         * @param alpha input alpha vector
         * @param p parameters for the optimization
         * @param msgs ptr of messages
         * @param water_level ptr of water level
         * @return The optimized x vector
         */
        static Vec optimize(const Vec& alpha, const Params& p = Params::defaultParams(),
                            Msgs* msgs = nullptr, double* water_level = nullptr);

        /**
         * @brief Construct a new Water Filling object.
         * 
         * @param alpha input alpha vector
         * @param p parameters for the optimization
         */
        WaterFilling(const Vec& alpha, const Params& p = Params::defaultParams());

        /**
         * @brief Set the parameters for the optimization.
         * 
         * @param p parameters for the optimization
         */
        void setParams(const Params& p);

        /**
         * @brief Solve the optimization problem.
         * 
         * @param msgs ptr of messages
         * @param water_level ptr of water level
         * @return The optimized x vector 
         */
        Vec optimize(Msgs* msgs = nullptr, double* water_level = nullptr);

    protected:
        /**
         * @brief Plot the results.
         * 
         * @param msgs ptr of messages
         * @return true 
         * @return false 
         */
        bool plot(Msgs* msgs = nullptr);

    private:
        Vec alpha_; ///< input alpha vector

        Params p_; ///< parameters for the optimization

        int size_; ///< size of input alpha vector

        double sum_; ///< sum of input alpha vector values

        double max_; ///< max of input alpha vector values

        double water_level_ = 0; ///< water level in optimization

    };
}

#endif // WATERFILLLING_H
