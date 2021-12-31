#include "generator.h"

wf::Generator::Generator() : mt(rd()) {}

wf::Vec wf::Generator::normal(int length, double m, double s) {
    if (length < 0) return Vec();
    Vec v(length);
    for (auto& item : v) item = normal(m, s);
    return v;
}

wf::Vec wf::Generator::uniform(int length, double min, double max) {
    if (length < 0) return Vec();
    Vec v(length);
    for (auto& item : v) item = uniform(min, max);
    return v;
}

bool wf::Generator::saveAs(const Str& file, const Vec& data) const {
    if (file.empty()) return true;
    std::ofstream f(file);
    if (f.is_open()) {
        for (const auto& v : data)
            f << v << ' ';
        f << std::endl;
        f.close();
        return true;
    } else {
        std::cerr << "ERROR: Cannot save file to '" + file + "'.";
        return false;
    }
}

double wf::Generator::normal(double m, double s) {
    std::normal_distribution<double> n(m, s);
    return n(mt);
}

double wf::Generator::uniform(double min, double max) {
    std::uniform_real_distribution<double> u(min, max);
    return u(mt);
}

// norm should be positive
wf::Vec wf::normalize(const Vec& v, double norm, double l) {
    int size_ = v.size();
    if (!size_ || l < 0) return v;
    Vec ret(size_);
    double sum = 0;
    for (const auto& item : v) sum += std::pow(item, l);
    sum = pow(sum, 1 / l);
    if (std::abs(sum) < 1E-8) sum = 1E-8;
    for (int i = 0; i != size_; i++)
        ret[i] = v[i] * norm / sum;
    return ret;
}

wf::Vec wf::abs(const Vec& v) {
    Vec ret = v;
    for (auto& item : ret) item = std::abs(item);
    return ret;
}
