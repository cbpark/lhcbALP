#ifndef LHCB_ALP_SRC_USER_INTERFACE_H_
#define LHCB_ALP_SRC_USER_INTERFACE_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

int failToRead(const std::string &appname, const std::string &fname) {
    std::cerr << appname << ": failed to read `" << fname << "'\n";
    return 1;
}

bool file_exists(const std::string &fname) {
    auto fin = std::make_unique<std::ifstream>(fname);
    if (fin->fail()) { return false; }
    return true;
}

void message(const std::string &appname, const std::string &msg) {
    std::cout << appname << ": " << msg << '\n';
}

#endif  // LHCB_ALP_SRC_USER_INTERFACE_H_
