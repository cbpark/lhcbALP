#ifndef LHCB_ALP_SRC_INPUT_DATA_H_
#define LHCB_ALP_SRC_INPUT_DATA_H_

#include <memory>
#include <ostream>
#include <string>
#include "TFile.h"
#include "TH2.h"

namespace lhcb {
enum class LimitType { REL = 0, ABS };

class InputData {
private:
    double mass_, tau_;
    double f_a_;
    LimitType type_ = LimitType::ABS;

public:
    InputData() = delete;
    InputData(const double mass, const double f_a, const double tau)
        : mass_(mass), tau_(tau), f_a_(f_a) {}
    InputData(const double mass, const double f_a, const double tau,
              const LimitType type)
        : mass_(mass), tau_(tau), f_a_(f_a), type_(type) {}

    /**
     *  ALP mass in MeV.
     */
    double mass() const;

    /**
     *  Lifetime of ALP in pb.
     */
    double tau() const;

    LimitType type() const { return type_; }

    friend std::ostream &operator<<(std::ostream &os, const InputData &data);
};

double upperLimit2015(std::shared_ptr<TFile> file_ex, const InputData &data);

double upperLimit2016(std::shared_ptr<TH2> hist_ex, const InputData &data);
}  // namespace lhcb

#endif  // LHCB_ALP_SRC_INPUT_DATA_H_
