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

wf::Str wf::fileExt(const Str& s) {
    return s.substr(s.find_last_of('.') + 1);
}

wf::Vec wf::readFile(const Str& file, bool* ok) {
    std::ifstream f(file);
    if (f) {
        Vec ret;
        Str tmp;
        while (f >> tmp) ret.push_back(std::stod(tmp));
        if (ok) *ok = true;
        return ret;
    } else {
        std::cerr << "ERROR: Cannot read file '" + file + "'" << std::endl;
        if (ok) *ok = false;
        return Vec();
    }
}
