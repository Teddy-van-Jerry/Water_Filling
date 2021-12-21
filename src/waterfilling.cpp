#include "waterfilling.h"

wf::Vec wf::WaterFilling::optimize(const wf::Vec& alpha, const Params& p, Msgs* msgs) {
    WaterFilling wf_task(alpha, p);
    return wf_task.optimize(msgs);
}

wf::WaterFilling::WaterFilling(const wf::Vec& alpha, const wf::Params& p) 
    : alpha_(alpha), p_(p), size_(alpha.size()), sum_(0) {
        for (const auto& a : alpha) sum_ += a;
    }

void wf::WaterFilling::setParams(const wf::Params& p) {
    p_ = p;
}

wf::Vec wf::WaterFilling::optimize(Msgs* msgs) {
    if (size_ == 0) {
        if (msgs) msgs->push_back("WARNING: Empty Input Vector.");
        return Vec();
    }

    double wl_max = (sum_ + 1) / size_; // upper limit of water level
    double wl_min = sum_ / size_; // lower limit of water level
    
    auto mid = [&] { return (wl_max + wl_min) / 2; };
    auto waterSum = [&] (double level) {
        double s = 0;
        for (const auto& a : alpha_) s += (a > level ? a - level : 0);
        return s;
    };
    auto diff = [&] (double level) { return waterSum(level) - 1; };

    int iter = 0;
    while (iter++ != p_.ITER_MAX) {
        double diff_ = diff(mid());
        if (abs(diff_) < p_.PRECISION) break;
        if (diff_ < 0) wl_min = mid();
        else wl_max = mid();
    }
    if (iter > p_.ITER_MAX && msgs)
        msgs->push_back("WARNING: Optimization Iteration Limit Reached. "
                        "You can adjust MAX_ITER or PRECISION in Params.");

    Vec ret(size_, 0);
    for (int i = 0; i != size_; i++)
        if (alpha_[i] < wl_min) ret[i] = wl_min - alpha_[i];

    return ret;
}

bool wf::WaterFilling::plot(const Vec& x, Msgs* msgs) {
    return true;
}
