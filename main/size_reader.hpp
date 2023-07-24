#pragma once

#include <cstdint>
#include <cmath>
#include <sstream>

struct HumanReadable {
    std::uintmax_t size{};

    template <typename Os> friend Os& operator<< (Os& os, HumanReadable hr)
    {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; ++i) {
            mantissa /= 1024.;
        }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        std::stringstream tmp_stream;
        tmp_stream << mantissa << " " << "BKMGTPE"[i];
        if (i != 0) {
            tmp_stream << "B ";
        }
        return os << tmp_stream.str();
    }
};
