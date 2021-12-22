#ifndef PARAMS_H
#define PARAMS_H

#include "wf_global.h"

namespace wf {
    struct Params {
        Params();

        static Params defaultParams();

        int ITER_MAX = wf::DEFAULT_ITER_MAX;
        double PRECISION = wf::DEFAULT_PRECISION;
        bool PRINT = true;

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
