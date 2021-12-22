/**
 * @file waterfilling.h
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief Water Filling Optimization
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021 Teddy van Jerry
 * 
 */
#ifndef WATERFILLLING_H
#define WATERFILLLING_H

#include "wf_global.h"
#include "params.h"
#include "gnuplot-iostream.h"

namespace wf {

    class WaterFilling {
    public:
        static Vec optimize(const Vec& alpha, const Params& p = Params::defaultParams(),
                            Msgs* msgs = nullptr, double* water_level = nullptr);

        WaterFilling(const Vec& alpha, const Params& p = Params::defaultParams());

        void setParams(const Params& p);

        Vec optimize(Msgs* msgs = nullptr, double* water_level = nullptr);

    protected:
        bool plot(Msgs* msgs = nullptr);

    private:
        Vec alpha_;

        Params p_;

        int size_;

        double sum_;

        double max_;

        double water_level_ = 0;

    };
}

#endif // WATERFILLLING_H
