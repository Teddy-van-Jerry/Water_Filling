/**
 * @file params.h
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief Parameters for Optimization
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022 Teddy van Jerry
 * 
 */

#ifndef PARAMS_H
#define PARAMS_H

#include "wf_global.h"

namespace wf {
    /**
     * @brief Parameters for optimization
     * 
     */
    struct Params {
        Params();

        /**
         * @brief The default parameters.
         * 
         * @return the default parameters 
         */
        static Params defaultParams();

        int ITER_MAX = wf::DEFAULT_ITER_MAX;
        double PRECISION = wf::DEFAULT_PRECISION;
        bool PRINT = true;

        /**
         * @brief Parameters about the plot
         * 
         */
        struct PlotParams {
            bool ENABLE = false;
            Str TITLE;
            Str FILE = "output.png";
            Str COLOR_LOWER = "lemonchiffon";
            Str COLOR_UPPER = "seagreen";
            double WIDTH;  // Default value not given here,
            double HEIGHT; // because it is related to the file type.
        } PLOT;
    };
}

#endif // PARAMS_H
