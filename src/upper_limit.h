#ifndef LHCB_ALP_SRC_UPPER_LIMIT_H_
#define LHCB_ALP_SRC_UPPER_LIMIT_H_

#include <memory>
#include "TFile.h"

namespace lhcb {
double upperLimitRelative(std::shared_ptr<TFile> file_ex, const double mass,
                          const double tau);

double upperLimitAbsolute(std::shared_ptr<TFile> file_ex, const double mass,
                          const double tau);
}  // namespace lhcb

#endif  // LHCB_ALP_SRC_UPPER_LIMIT_H_
