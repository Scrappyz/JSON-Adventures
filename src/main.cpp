#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include "json.hpp"
#include "os.hpp"

using json = nlohmann::json;
namespace path = os::path;

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

std::string getNextScenario(std::string input, const std::unordered_map<std::string, std::string>& choices)
{
    input = toLower(input);
    for(const auto i : choices) {
        std::vector<std::string> parsed = parseChoice(i.first);
        for(int j = 0; j < parsed.size(); j++) {
            if(input.find(parsed[j]) != std::string::npos) {
                return i.second;
            }
        }
    }
    return std::string();
}

void play(const std::string& scenario_dir, const std::string& start_scenario)
{
    std::string scenario_file = path::joinPath(scenario_dir, start_scenario);
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

        std::unordered_map<std::string, std::string> choices = data.at("choices");
        std::vector<std::string> excuses = data.at("excuses");
        std::string input;
        std::string next_scenario;

        while(true) {
            std::cout << "> ";
            std::getline(std::cin, input);

            next_scenario = getNextScenario(input, choices);
            if(!next_scenario.empty()) {
                break;
            }
            std::cout << excuses[randomNumber(0, excuses.size()-1)] << std::endl;
            std::cout << std::endl;
        }

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