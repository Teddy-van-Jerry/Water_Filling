#ifndef PARAMS_H
#define PARAMS_H

#include "wf_global.h"

namespace wf {
    struct Params {
        Params();

        static Params defaultParams();

        double ITER_MAX = wf::DEFAULT_ITER_MAX;
        double PRECISION = wf::DEFAULT_PRECISION;

        struct PlotParams {
            bool ENABLE = false;
        } PLOT;
    };
}

#endif // PARAMS_H