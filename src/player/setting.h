//
// Created by nader on 6/15/24.
//

#ifndef HELIOS_BASE_SETTING_H
#define HELIOS_BASE_SETTING_H

#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Setting {
public:
    static Setting & i();

    int version = 0;

    string formation_name = "433-433";

    void find_version(const string &json_string);

    void load_from_json_string(const string &json_string);

    void read_from_file(string file_path);

    void print();

    void read_from_arguments(int argc, char *argv[]);
};


#endif //HELIOS_BASE_SETTING_H
