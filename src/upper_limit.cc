#include "upper_limit.h"
#include <cmath>
#include <cstdio>
#include <memory>
#include "TFile.h"
#include "TGraph.h"
#include "TSpline.h"

namespace lhcb {
/*
 *  mass: mass in MeV
 *  tau:  lifetime in ps
 *  type: 0 = relative, 1 = absolute limits
 *
 *  returns upper limit at 95% CL or -1 if no limit is set where requested
 */
double upperLimit(std::shared_ptr<TFile> file_ex, const double mass,
                  const double tau, const int type) {
    if (mass < 214.0 || mass > 4350.0) { return -1; }
    if (mass > 1000.0 && mass < 1040.0 && tau < 1.0) { return -1; }
    if (mass > 742.0 && mass < 822.0 && tau < 1.0) { return -1; }
    if (mass > 2913.0 && mass < 3211.0) { return -1; }
    if (mass > 3609.0 && mass < 3875.0) { return -1; }

    auto g = std::unique_ptr<TGraph>(
        static_cast<TGraph *>(file_ex->Get("g_masses")));
    // find best mass
    const int n = g->GetN();
    int mmin = -1;
    double min = 1.0e6;
    for (int i = 0; i < n; ++i) {
        const double gx = g->GetX()[i];
        if (std::fabs(mass - gx) < min) {
            min = std::fabs(mass - gx);
            mmin = static_cast<int>(gx);
        }
    }

    char name[100];
    if (type == 0) {
        std::sprintf(name, "rel_ul_spline_%d", mmin);
    } else {
        std::sprintf(name, "abs_ul_spline_%d", mmin);
    }

    auto spl =
        std::unique_ptr<TSpline3>(static_cast<TSpline3 *>(file_ex->Get(name)));
    if (tau < 1000.0) { return spl->Eval(tau); }
    const double ul1000 = spl->Eval(1000);
    return ul1000 / (1 - std::exp(-1000.0 / tau)) * (1 - std::exp(-1));
}

double upperLimitRelative(std::shared_ptr<TFile> file_ex, const double mass,
                          const double tau) {
    return upperLimit(file_ex, mass, tau, 0);
}

double upperLimitAbsolute(std::shared_ptr<TFile> file_ex, const double mass,
                          const double tau) {
    return upperLimit(file_ex, mass, tau, 1);
}
}  // namespace lhcb
