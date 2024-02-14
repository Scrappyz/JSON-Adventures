#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include "json.hpp"
#include "os.hpp"

using json = nlohmann::json;
namespace path = os::path;

enum Type {
    SCENARIO = 0,
    MESSAGE = 1
};

void writeScenario(const std::string& file, const std::string& name, const std::string& scenario, const std::unordered_map<std::string, std::string>& choices, bool game_over = false)
{
    json j;
    j["title"] = name;
    j["scenario"] = scenario;
    j["choices"] = choices;
    j["gameOver"] = game_over;

    std::ofstream f(file);
    f << j.dump(4);
    f.close();
}

std::string appendExtension(const std::string& file)
{
    if(file.size() < 6) {
        return file + ".json";
    }

    if(file.substr(file.size() - 5, 5) != ".json") {
        return file + ".json";
    }

    return file;
}

std::string toLower(std::string str)
{
    for(int i = 0; i < str.size(); i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = static_cast<char>(static_cast<int>(str[i]) + 32);
        }
    }
    return str;
}

int randomNumber(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(rng);
}

std::vector<std::string> parseChoice(const std::string& choice)
{
    std::vector<std::string> choices;
    std::string temp;
    for(int i = 0; i < choice.size(); i++) {
        if(choice[i] == '|') {
            choices.push_back(temp);
            temp.clear();
            continue;
        }
        temp.push_back(choice[i]);
    }
    if(!temp.empty()) {
        choices.push_back(temp);
    }
    return choices;
}

std::string getChoice(std::string input, const json& choices)
{
    input = toLower(input);
    for(const auto& i : choices.items()) {
        std::vector<std::string> parsed = parseChoice(i.key());
        for(int j = 0; j < parsed.size(); j++) {
            if(input.find(parsed[j]) != std::string::npos) {
                return i.key();
            }
        }
    }
    
    return std::string();
}

bool hasModifiers(const std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& requires)
{
    for(const auto& i : requires) {
        if(modifiers.count(i.first) < 1) {
            return false;
        }

        if(modifiers.at(i.first) < i.second) {
            return false;
        }
    }
    return true;
}

void addModifiers(std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& add)
{
    for(const auto& i : add) {
        modifiers[i.first] += i.second;
    }
}

void subtractModifiers(std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& subtract)
{
    for(const auto& i : subtract) {
        if(modifiers.count(i.first) < 1) {
            continue;
        }

        modifiers[i.first] -= i.second;
        if(modifiers.at(i.first) < 1) {
            modifiers.erase(i.first);
        }
    }
}

void play(const std::string& scenario_dir, const std::string& start_scenario)
{
    std::string scenario_file = path::joinPath(scenario_dir, start_scenario);
    std::unordered_map<std::string, int> modifiers;
    std::unordered_map<std::string, int> tries;
    std::ifstream f;
    json data;

    while(true) {
        f.open(scenario_file);
        data = json::parse(f);
        f.close();

        std::string scenario = data.at("scenario");
        std::cout << scenario << std::endl;
        std::cout << std::endl;

        if(data.at("gameOver")) {
            std::cout << "Game Over" << std::endl;
            break;
        }

        std::vector<std::string> invalids = data.at("invalids");
        std::string input;
        std::string next_scenario;

        while(true) {
            std::cout << "> ";
            std::getline(std::cin, input);

            std::string choice = getChoice(input, data.at("choices"));

            if(choice.empty()) {
                std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
                std::cout << std::endl;
                continue;
            }

            json choice_data = data.at("choices").at(choice);
            int max_tries = 1;

            if(choice_data.contains("tries")) {
                max_tries = choice_data.at("tries");
            }

            if(max_tries >= 0 && tries.count(choice) > 0 && tries.at(choice) >= max_tries) {
                std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
                std::cout << std::endl;
                continue;
            }

            if(choice_data.contains("requires") && !hasModifiers(modifiers, choice_data.at("requires"))) {
                std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
                std::cout << std::endl;
                continue;
            }

            if(choice_data.contains("next")) {
                next_scenario = choice_data.at("next");
            }
            
            if(choice_data.contains("takes")) {
                subtractModifiers(modifiers, choice_data.at("takes"));
            }

            if(choice_data.contains("gives")) {
                addModifiers(modifiers, choice_data.at("gives"));
            }

            bool has_message = choice_data.contains("message");
            if(has_message) {
                std::cout << std::string(choice_data.at("message")) << std::endl;
                std::cout << std::endl;
            }

            tries[choice]++;

            if(!next_scenario.empty()) {
                break;
            }

            if(!has_message) {
                std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
                std::cout << std::endl;
            }
        }

        tries.clear();
        scenario_file = path::joinPath(scenario_dir, appendExtension(next_scenario));
    }
}

int main()
{
    std::string scenario_dir = path::joinPath(path::sourcePath(), "../../resources/stories/School Day/scenarios");
    std::string start_scenario = appendExtension("start");
    play(scenario_dir, start_scenario);
    return 0;
}