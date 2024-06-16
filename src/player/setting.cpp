//
// Created by nader on 6/15/24.
//

#include "setting.h"

Setting & Setting::i() {
    static Setting instance;
    return instance;
}

void Setting::load_from_json_string(const string &json_str){
    try
    {
        json j = json::parse(json_str);

        if (j.contains("formation_name"))
            formation_name = j.at("formation_name").get<std::string>();
    }
    catch (exception &e)
    {
        std::cerr << "Error in parsing json string: " << e.what() << std::endl;
    }
}

void Setting::read_from_file(string file_path){
    if (file_path.find(".json") == string::npos) {
        if (file_path[file_path.size() - 1] == '/')
            file_path = file_path.substr(0, file_path.size() - 1);
        file_path = file_path + "/config.json";
    }
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "File does not exist - '" << file_path << "'" << std::endl;
        return;
    }
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '" << file_path << "'" << std::endl;
        return;
    }
    string json_str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    load_from_json_string(json_str);
}

void Setting::print() {
    std:cout << "formation_name: " << formation_name << std::endl;
}

void Setting::read_from_arguments(int argc, char *argv[]){
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-j") == 0) {
            if (i + 1 < argc) {
                load_from_json_string(argv[i + 1]);
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                read_from_file(argv[i + 1]);
            }
        }
    }
}
