//
// Created by nader on 6/15/24.
//

#include "setting.h"

Setting & Setting::i() {
    static Setting instance;
    return instance;
}

void Setting::log(const std::string &message) {
    log_buffer << message;
}

void Setting::print_logs() {
    // add ----- at the beginning and the end of the logs
    log_buffer.str("-------------------------\n" + log_buffer.str() + "-------------------------\n");
    std::cout << log_buffer.str();
}

void Setting::clear_logs() {
    log_buffer.str("");
    log_buffer.clear();
}

void Setting::find_version(const string &json_str){
    try
    {
        json j = json::parse(json_str);

        if (j.contains("version"))
            version = j.at("version").get<int>();
        log("version: " + std::to_string(version) + "\n");
    }
    catch (exception &e)
    {
        log("Error in parsing json string: " + std::string(e.what()) + "\n");
        throw std::invalid_argument("Error in parsing json string");
    }
}

void replaceAll(std::string &str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

string Setting::decode(const std::string &encoding, const std::string &encoded_string) {
    if (encoding == "json") {
        log("json encoding\n");
        return encoded_string;
    }
    else if (encoding == "temp") {
        // replace @qq@ with "
        // replace @q@ with '
        // replace @c@ with ,
        log("temp encoding\n");
        string decoded_string = encoded_string;
        replaceAll(decoded_string, "@qq@", "\"");
        replaceAll(decoded_string, "@q@", "'");
        replaceAll(decoded_string, "@c@", ",");
        return decoded_string;
    }
    else {
        log("Encoding is not supported\n");
        return "json";
    }
}

void Setting::load_from_json_string(const string &json_str, const string &encoding){
    string decoded_json_str = decode(encoding, json_str);
    find_version(decoded_json_str);
    if (version == 1)
    {
        try
        {
            json j = json::parse(decoded_json_str);

            if (j.contains("formation_name")) {
                formation_name = j.at("formation_name").get<std::string>();
                if (std::find(formation_options.begin(), formation_options.end(), formation_name) == formation_options.end()) {
                    log("Formation name is not valid\n");
                    throw std::invalid_argument("Formation name is not valid");
                }
            }
            if (j.contains("offensive_kick_planner_use_direct_pass"))
                offensive_kick_planner_use_direct_pass = j.at("offensive_kick_planner_use_direct_pass").get<bool>();
            if (j.contains("offensive_kick_planner_use_lead_pass"))
                offensive_kick_planner_use_lead_pass = j.at("offensive_kick_planner_use_lead_pass").get<bool>();
            if (j.contains("offensive_kick_planner_use_through_pass"))
                offensive_kick_planner_use_through_pass = j.at("offensive_kick_planner_use_through_pass").get<bool>();
            if (j.contains("offensive_kick_planner_use_cross_pass"))
                offensive_kick_planner_use_cross_pass = j.at("offensive_kick_planner_use_cross_pass").get<bool>();
            if (j.contains("offensive_kick_planner_use_short_dribble"))
                offensive_kick_planner_use_short_dribble = j.at("offensive_kick_planner_use_short_dribble").get<bool>();
            if (j.contains("offensive_kick_planner_use_long_dribble"))
                offensive_kick_planner_use_long_dribble = j.at("offensive_kick_planner_use_long_dribble").get<bool>();
            if (j.contains("offensive_kick_planner_use_sample_shot"))
                offensive_kick_planner_use_sample_shot = j.at("offensive_kick_planner_use_sample_shot").get<bool>();
            if (j.contains("offensive_kick_planner_use_sample_pass"))
                offensive_kick_planner_use_sample_pass = j.at("offensive_kick_planner_use_sample_pass").get<bool>();
            if (j.contains("offensive_kick_planner_use_sample_dribble"))
                offensive_kick_planner_use_sample_dribble = j.at("offensive_kick_planner_use_sample_dribble").get<bool>();
            if (j.contains("moving_save_energy")) {
                moving_save_energy = j.at("moving_save_energy").get<double>();
                if ( moving_save_energy < 0 )
                    moving_save_energy = 0;
                if ( moving_save_energy > 100 )
                    moving_save_energy = 100;
            }
            if (j.contains("pressing")) {
                pressing = j.at("pressing").get<double>();
                if (pressing != 0)
                    pressing = 1;
                if (pressing == 0)
                    pressing = 0;
            }
            if (j.contains("offside_trap")) {
                offside_trap = j.at("offside_trap").get<int>();
                if (offside_trap != 0)
                    offside_trap = 1;
                if (offside_trap == 0)
                    offside_trap = 0;

                log("offside_trap: " + std::to_string(offside_trap) + "\n");
            }

            if (j.contains("aggressiveness")) {
                aggressiveness = j.at("aggressiveness").get<double>();
                if (aggressiveness < 0)
                    aggressiveness = 0;
                if (aggressiveness > 1)
                    aggressiveness = 1;

                log("aggressiveness: " + std::to_string(aggressiveness) + "\n");
            }

            if (j.contains("player_type_ids")) {
                player_type_ids = j.at("player_type_ids").get<vector<int>>();
                if (player_type_ids.size() > 18) {
                    log("player_type_ids size is more than 18\n");
                    throw std::invalid_argument("player_type_ids size is more than 18");
                }
                for (int i = 0; i < player_type_ids.size(); i++) {
                    if (min_type_id == 18){
                        if (player_type_ids[i] < 18)
                        {
                            player_type_ids[i] += 18;
                        }
                    }
                }
                std::string player_type_ids_str = "player_type_ids[0.." + std::to_string(player_type_ids.size() - 1) + "]=[";
                for (size_t i = 0; i < player_type_ids.size(); i++) {
                    player_type_ids_str += std::to_string(player_type_ids[i]);
                    if (i < player_type_ids.size() - 1) {
                        player_type_ids_str += ",";
                    }
                }
                player_type_ids_str += "]";
                log(player_type_ids_str + "\n");
            }
            // check if json contains unsupported keys
            for (auto& el : j.items()) {
                std::string key = el.key();
                if (key != "version" && key != "formation_name" &&
                    key != "offensive_kick_planner_use_direct_pass" &&
                    key != "offensive_kick_planner_use_lead_pass" &&
                    key != "offensive_kick_planner_use_through_pass" &&
                    key != "offensive_kick_planner_use_cross_pass" &&
                    key != "offensive_kick_planner_use_short_dribble" &&
                    key != "offensive_kick_planner_use_long_dribble" &&
                    key != "offensive_kick_planner_use_sample_shot" &&
                    key != "offensive_kick_planner_use_sample_pass" &&
                    key != "offensive_kick_planner_use_sample_dribble" &&
                    key != "moving_save_energy" &&
                    key != "pressing" &&
                    key != "offside_trap" &&
                    key != "aggressiveness" &&
                    key != "player_type_ids") {
                    log("Unsupported key in json: " + key + "\n");
                    throw std::invalid_argument("Unsupported key in json: " + key);
                }
            }
        }
        catch (exception &e)
        {
            log("Error in parsing json values: " + std::string(e.what()) + "\n");
            throw std::invalid_argument("Error in parsing json values");
        }
    }
    else
    {
        log("Version is not supported or it was not found in json\n");
        throw std::invalid_argument("Version is not supported or it was not found in json");
    }
}

void Setting::read_from_file(string file_path, const string &encoding) {
    if (file_path.find(".json") == string::npos) {
        if (file_path[file_path.size() - 1] == '/')
            file_path = file_path.substr(0, file_path.size() - 1);
        file_path = file_path + "/config.json";
    }
    if (!std::filesystem::exists(file_path)) {
        log("File does not exist - '" + file_path + "'\n");
        std::cerr << "File does not exist - '" << file_path << "'" << std::endl;
        return;
    }
    std::ifstream file(file_path);
    if (!file.is_open()) {
        log("Could not open the file - '" + file_path + "'\n");
        std::cerr << "Could not open the file - '" << file_path << "'" << std::endl;
        return;
    }
    string json_str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    load_from_json_string(json_str, encoding);
}

void Setting::print() const {
    // Cast away const to use log() method
    Setting* self = const_cast<Setting*>(this);
    
    self->log("formation_name: " + formation_name + "\n");
    self->log("offensive_kick_planner_use_direct_pass: " + std::to_string(offensive_kick_planner_use_direct_pass) + "\n");
    self->log("offensive_kick_planner_use_lead_pass: " + std::to_string(offensive_kick_planner_use_lead_pass) + "\n");
    self->log("offensive_kick_planner_use_through_pass: " + std::to_string(offensive_kick_planner_use_through_pass) + "\n");
    self->log("offensive_kick_planner_use_cross_pass: " + std::to_string(offensive_kick_planner_use_cross_pass) + "\n");
    self->log("offensive_kick_planner_use_short_dribble: " + std::to_string(offensive_kick_planner_use_short_dribble) + "\n");
    self->log("offensive_kick_planner_use_long_dribble: " + std::to_string(offensive_kick_planner_use_long_dribble) + "\n");
    self->log("offensive_kick_planner_use_sample_shot: " + std::to_string(offensive_kick_planner_use_sample_shot) + "\n");
    self->log("offensive_kick_planner_use_sample_pass: " + std::to_string(offensive_kick_planner_use_sample_pass) + "\n");
    self->log("offensive_kick_planner_use_sample_dribble: " + std::to_string(offensive_kick_planner_use_sample_dribble) + "\n");
    self->log("moving_save_energy: " + std::to_string(moving_save_energy) + "\n");
    self->log("pressing: " + std::to_string(pressing) + "\n");
    self->log("min_type_id: " + std::to_string(min_type_id) + "\n");
    self->log("max_type_id: " + std::to_string(max_type_id) + "\n");
    
    self->print_logs();
}

void Setting::read_from_arguments(int &argc, char **argv){
    // Second pass: process configuration arguments
    try {
        log("Reading from arguments: ");
        for (int i = 0; i < argc; i++) {
            log(argv[i]);
            if (i + 1 < argc) {
                log(" ");
            } else {
                log("\n");
            }
        }
        
        vector<bool> to_remove(argc, false);
        string encoding = "json";
        
        // First pass: find encoding and side
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-e") == 0) {
                if (i + 1 < argc) {
                    encoding = argv[i + 1];
                    to_remove[i] = true;
                    to_remove[i + 1] = true;
                    i++; // Skip next argument
                }
            }
            else if (strcmp(argv[i], "--side") == 0) {
                if (i + 1 < argc) {
                    auto side = argv[i + 1];
                    if (strcmp(side, "left") == 0) {
                        min_type_id = 0;
                        max_type_id = 17;
                    } else if (strcmp(side, "right") == 0) {
                        min_type_id = 18;
                        max_type_id = 35;
                    } else {
                        log("Side is not valid\n");
                    }
                    to_remove[i] = true;
                    to_remove[i + 1] = true;
                    i++; // Skip next argument
                }
            }
        }

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-j") == 0) {
                if (i + 1 < argc) {
                    load_from_json_string(argv[i + 1], encoding);
                    to_remove[i] = true;
                    to_remove[i + 1] = true;
                    i++; // Skip next argument
                }
            } else if (strcmp(argv[i], "-c") == 0) {
                if (i + 1 < argc) {
                    read_from_file(argv[i + 1], encoding);
                    to_remove[i] = true;
                    to_remove[i + 1] = true;
                    i++; // Skip next argument
                }
            }
        }
        
        // Remove processed arguments
        int new_argc = 0;
        for (int i = 0; i < argc; i++) {
            if (!to_remove[i]) {
                argv[new_argc++] = argv[i];
            }
        }
        argc = new_argc;
        
        log("Remaining arguments after Setting parsing: ");
        for (int i = 0; i < argc; i++) {
            log(argv[i]);
            if (i + 1 < argc) {
                log(" ");
            } else {
                log("\n");
            }
        }
        
        print();
    }
    catch (const std::exception &e) {
        log("Exception caught in read_from_arguments: " + std::string(e.what()) + "\n");
        print();
        throw;
    }
}
