#include "waterfilling.h"

wf::Vec wf::WaterFilling::optimize(const wf::Vec& alpha, const Params& p, Msgs* msgs, double* water_level) {
    WaterFilling wf_task(alpha, p);
    return wf_task.optimize(msgs);
}

wf::WaterFilling::WaterFilling(const wf::Vec& alpha, const wf::Params& p) 
    : alpha_(alpha), p_(p), size_(alpha.size()), sum_(0), max_(0) {
    for (const auto& a : alpha) {
        sum_ += a;
        if (a > max_) max_ = a;
    }
}

void wf::WaterFilling::setParams(const wf::Params& p) {
    p_ = p;
}

wf::Vec wf::WaterFilling::optimize(Msgs* msgs, double* water_level) {
    if (size_ == 0) {
        if (msgs) msgs->push_back("WARNING: Empty Input Vector.");
        return Vec();
    }

    double wl_max = (sum_ + 1) / size_; // upper limit of water level
    double wl_min = 1. / size_; // lower limit of water level
    
    auto mid = [&] { return (wl_max + wl_min) / 2; };
    auto waterSum = [&] (double level) {
        double s = 0;
        for (const auto& a : alpha_) s += (level > a ? level - a : 0);
        return s;
    };
    auto diff = [&] (double level) { return waterSum(level) - 1; };

    // iteration using dichotomy
    int iter = 0;
    while (iter++ < p_.ITER_MAX) {
        double diff_ = diff(mid());
        if (abs(diff_) < pow(10, -p_.PRECISION)) break;
        if (diff_ < 0) wl_min = mid(); // update lower limit
        else wl_max = mid(); // update upper limit
    }
    if (iter > p_.ITER_MAX && msgs)
        msgs->push_back("WARNING: Optimization Iteration Limit Reached. "
                        "You can adjust MAX_ITER or PRECISION in Params.");

    Vec ret(size_, 0);
    for (int i = 0; i != size_; i++)
        if (alpha_[i] < wl_min) ret[i] = wl_min - alpha_[i];
    water_level_ = wl_min;
    if (water_level) *water_level = water_level_;
    if (p_.PRINT) print(ret);
    if (p_.PLOT.ENABLE) plot(msgs);
    return ret;
}

bool wf::WaterFilling::plot(Msgs* msgs) {
    Gnuplot gp;

    Str ext = fileExt(p_.PLOT.FILE);
    if (p_.PLOT.WIDTH <= 0) {
        if (ext == "eps" || ext == "pdf") p_.PLOT.WIDTH = 5;
        else p_.PLOT.WIDTH = 500;
    }
    if (p_.PLOT.HEIGHT <= 0) {
        if (ext == "eps" || ext == "pdf") p_.PLOT.HEIGHT = 3;
        else p_.PLOT.HEIGHT = 300;
    }

    Str terminal = toLower(ext);
    if (terminal == "jpg") terminal = "jpeg";
    else if (terminal == "tex") terminal = "tikz";
    Str enhanced = " enhanced\n";
    if (terminal == "tikz") enhanced = "\n";
    gp << "set terminal " + terminal + " size "
          + std::to_string(p_.PLOT.WIDTH) + "," + std::to_string(p_.PLOT.HEIGHT) + enhanced;
    gp << "set output '" + p_.PLOT.FILE + "'\n";

    if (!p_.PLOT.TITLE.empty()) gp << "set title '" << p_.PLOT.TITLE << "'\n";
	gp << "set xtics 1\n";
	gp << "set ytics 1E" + std::to_string((int)std::log10(max_ * 1.05) - 1) + " nomirror tc lt 1\n";
	gp << "set xrange [0.5:" << std::to_string(size_) << ".5]\n";
	gp << "set yrange [0:" << std::to_string(max_ * 1.05) << "]\n";
	gp << "set style fill solid border -1\n";

	Vec data_X {0};
    Vec data_Alpha {0};
    data_X.insert(data_X.begin() + 1, size_, water_level_);
    data_Alpha.insert(data_Alpha.begin() + 1, alpha_.cbegin(), alpha_.cend());

	gp << "plot '-' with boxes notitle lt rgb '" + p_.PLOT.COLOR_LOWER + "',";
	gp << "'-' with boxes notitle lt rgb '" + p_.PLOT.COLOR_UPPER + "'\n";
	gp.send1d(data_X);
	gp.send1d(data_Alpha);
    
    return true;
}
