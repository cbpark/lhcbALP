#include "input_data.h"
#include <cmath>
#include <iomanip>
#include <memory>
#include <ostream>
#include "TFile.h"
#include "upper_limit.h"

namespace lhcb {
double exp10(const double x) { return std::pow(10, x); }

// the input data has log10(mass).
double InputData::mass() const { return exp10(mass_); }

// the input data has log10(tau).
double InputData::tau() const { return exp10(tau_); }

std::ostream &operator<<(std::ostream &os, const InputData &data) {
    os << std::left << std::setw(22) << std::setprecision(17) << data.mass_
       << std::setw(22) << data.f_a_ << std::setw(22) << data.tau_;
    return os;
}

double upperLimit(std::shared_ptr<TFile> file_ex, const InputData &data) {
    const double mass = data.mass(), tau = data.tau();
    switch (data.type()) {
    case LimitType::REL:  // upper limit relative to BR(B --> K^* mu+ mu-)
        return upperLimitRelative(file_ex, mass, tau);
    case LimitType::ABS:  // absolute upper limit
        return upperLimitAbsolute(file_ex, mass, tau);
    default:
        return -666;
    }
}
}  // namespace lhcb
