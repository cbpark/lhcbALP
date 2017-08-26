#include "input_data.h"
#include <cmath>
#include <iomanip>
#include <memory>
#include <ostream>
#include "TFile.h"
#include "TH2.h"
#include "upper_limit_2015.h"
#include "upper_limit_2016.h"

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

double upperLimit2015(std::shared_ptr<TFile> file_ex, const InputData &data) {
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

double upperLimit2016(std::shared_ptr<TH2> hist_ex, const InputData &data) {
    const double mass = data.mass(), tau = data.tau();
    const int bin_hist = hist_ex->FindBin(mass, tau);
    const double br_exp = hist_ex->GetBinContent(bin_hist);
    if (br_exp < 1.0e-10) {
        return -1;
    } else {
        return br_exp;
    }
}
}  // namespace lhcb
