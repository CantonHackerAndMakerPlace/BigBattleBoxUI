#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <iostream>
#include <iomanip>
#include <sstream>

constexpr int MILLISECONDS_PER_MINUTES = 60000;
constexpr int MILLISECONDS_PER_SECOND = 1000;

inline QString msToTimeRep(int ms) {
    std::stringstream s;
    auto minutes = std::div(ms, MILLISECONDS_PER_MINUTES);
    auto seconds = std::div(minutes.rem, MILLISECONDS_PER_SECOND);
    if (minutes.quot > 0) {
        s << minutes.quot<< "m ";
    }
    if (seconds.quot > 0) {
        s << std::setfill('0') << std::setw(2) << seconds.quot;
    } else {
        s << "0";
    }
    s << "." <<std::setfill('0') << std::setw(3) << seconds.rem;
    auto temp = s.str();
    return QString(temp.c_str());
}

#endif // UTIL_H
