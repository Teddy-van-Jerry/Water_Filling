#include "wf_global.h"

void wf::print(const wf::Vec& v, const wf::Str& s, const wf::Str& end) {
    if (!v.size()) {
        std::cout << end;
    } else {
        for (auto i = v.cbegin(); i != v.cend() - 1; i++) {
            std::cout << *i << s;
        }
        std::cout << *--v.cend() << end;
    }
}