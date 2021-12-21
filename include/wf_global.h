#ifndef WF_GLOBAL_H
#define WF_GLOBAL_H

#include <iostream>
#include <vector>
#include <string>

namespace wf {
    using Vec = std::vector<double>;
    using Str = std::string;
    using Msg = Str;
    using Msgs = std::vector<Msg>;

    constexpr int const DEFAULT_ITER_MAX = 1000;
    constexpr double const DEFAULT_PRECISION = 1E-6;

    void print(const Vec& v, const wf::Str& s = ", ", const wf::Str& end = "\n");
}

#endif // WF_GLOBAL_H
