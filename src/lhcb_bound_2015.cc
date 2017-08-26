#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "TFile.h"
#include "input_data.h"
#include "upper_limit_2015.h"
#include "user_interface.h"

const char appname[] = "lhcb_bound_2015";
const char exp_result[] = "data/lhcb_2015_036.root";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <input> <output>\n";
        return 1;
    }

    message(appname, "reading `" + std::string(argv[1]) + "' ...");
    std::ifstream fin(argv[1]);
    if (fin.fail()) { return failToRead(appname, argv[1]); }

    if (!file_exists(exp_result)) { return failToRead(appname, exp_result); }
    auto f_ex = std::make_shared<TFile>(exp_result);

    std::string line;
    std::ofstream fout(argv[2]);
    while (std::getline(fin, line)) {
        double mass, f_a, tau;
        std::istringstream iss(line);
        iss >> mass >> f_a >> tau;
        lhcb::InputData data{mass, f_a, tau, lhcb::LimitType::ABS};
        fout << data << std::setw(22) << lhcb::upperLimit2015(f_ex, data)
             << '\n';
    }
    message(appname,
            "output has been stored to `" + std::string(argv[2]) + ".");
}
