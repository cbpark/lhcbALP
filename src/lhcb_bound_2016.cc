#include <fstream>
#include <iostream>
#include <sstream>
#include "input_data.h"
#include "upper_limit_2016.h"
#include "user_interface.h"

const char appname[] = "lhcb_bound_2016";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <input> <output>\n";
        return 1;
    }

    message(appname, "reading `" + std::string(argv[1]) + "' ...");
    std::ifstream fin(argv[1]);
    if (fin.fail()) { return failToRead(appname, argv[1]); }

    auto upperLimitHist = lhcb::histUpperLimit();

    std::string line;
    std::ofstream fout(argv[2]);
    while (std::getline(fin, line)) {
        double mass, f_a, tau;
        std::istringstream iss(line);
        iss >> mass >> f_a >> tau;
        lhcb::InputData data{mass, f_a, tau};
        fout << data << std::setw(22)
             << lhcb::upperLimit2016(upperLimitHist, data) << '\n';
    }
    message(appname,
            "output has been stored to `" + std::string(argv[2]) + ".");
}
