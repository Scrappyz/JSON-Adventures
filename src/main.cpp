#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "json.hpp"
#include "os.hpp"

using json = nlohmann::json;
namespace path = os::path;

void writeScenario(const std::string& file, const std::string& name, const std::string& scenario, const std::unordered_map<std::string, std::string>& keywords, bool game_over = false)
{
    json j;
    j["title"] = name;
    j["scenario"] = scenario;
    j["keywords"] = keywords;
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

void play(const std::string& scenario_dir, const std::string& start_scenario)
{
    std::string scenario_file = path::joinPath(scenario_dir, start_scenario);
    json data;
    while(true) {
        std::ifstream f(scenario_file);
        data = json::parse(f);
        f.close();

        std::cout << std::string(data.at("title")) << std::endl;
        std::cout << std::endl;
        std::cout << std::string(data.at("scenario")) << std::endl;
        std::cout << std::endl;

        if(data.at("gameOver")) {
            std::cout << "Game Over" << std::endl;
            break;
        }

        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        std::unordered_map<std::string, std::string> keywords = data.at("keywords");
        if(keywords.count(input) < 1) {
            std::cout << "There is a time and place for everything but not now." << std::endl;
            continue;
        }

        scenario_file = path::joinPath(scenario_dir, appendExtension(data.at("keywords").at(input)));
    }
}

int main()
{
    std::string scenario_dir = path::joinPath(path::sourcePath(), "../../resources/scenarios");
    std::string start_scenario = appendExtension("scenario1");
    play(scenario_dir, start_scenario);
    // std::string scenario_file = appendExtension("scenario2");

    // std::string name = "Making Breakfast";
    // std::string scenario = "You got up and went to the kitchen to make breakfast.";
    // std::unordered_map<std::string, std::string> keywords = {
        
    // };
    // bool game_over = false;
    // writeScenario(path::joinPath(scenario_dir, scenario_file), name, scenario, keywords, game_over);
    return 0;
}