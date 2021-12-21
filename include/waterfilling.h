#ifndef WATERFILLLING_H
#define WATERFILLLING_H

#include "wf_global.h"
#include "params.h"

namespace wf {

    class WaterFilling {
    public:
        static Vec optimize(const Vec& alpha, const Params& p = Params::defaultParams(), Msgs* msgs = nullptr);

        WaterFilling(const Vec& alpha, const Params& p = Params::defaultParams());

        void setParams(const Params& p);

        Vec optimize(Msgs* msgs = nullptr);

    protected:
        // vec optimize_(const vec& alpha, Params p = Params::defaultParams());

    private:
        Vec alpha_;

        Params p_;

        int size_;

        double sum_;

    };

    bool setOK(bool* ok, bool value);
}

#endif // WATERFILLLING_H
