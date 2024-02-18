#include <iostream>
#include <fstream>
#include "json.hpp"
#include "os.hpp"
#include "helper.hpp"

using json = nlohmann::json;
namespace path = os::path;

void play(const std::string& scenario_dir, const std::string& start_scenario)
{
    std::string scenario_file = path::joinPath(scenario_dir, start_scenario);
    std::unordered_map<std::string, int> modifiers;
    std::unordered_map<std::string, int> attempts;
    int type_delay = 15;
    bool game_over = false;
    std::ifstream f;
    json data;

    while(!game_over) {
        f.open(scenario_file);
        data = json::parse(f);
        f.close();

        std::string scenario = data.at("scenario");
        type(scenario, type_delay, "\n");
        std::cout << std::endl;

        if(data.contains("gameOver") && data.at("gameOver")) {
            std::cout << "Game Over" << std::endl;
            game_over = true;
            break;
        }

        if(!data.contains("choices") || data.at("choices").empty()) {
            game_over = true;
            break;
        }

        std::vector<std::string> invalids = data.at("invalids");
        std::string input;
        std::string next_scenario;

        while(!game_over) {
            std::cout << "> ";
            std::getline(std::cin, input);

            std::string choice = getChoice(input, data.at("choices"));

            if(choice.empty()) {
                type(invalids[randomNumber(0, invalids.size()-1)], type_delay, "\n");
                std::cout << std::endl;
                continue;
            }

            json choice_data = data.at("choices").at(choice);
            int max_attempts = 1;

            if(choice_data.contains("attempts")) {
                max_attempts = choice_data.at("attempts");
            }

            if(max_attempts >= 0 && attempts.count(choice) > 0 && attempts.at(choice) >= max_attempts) {
                type(getInvalidMessage(data, choice_data, "attempts"), type_delay, "\n");
                std::cout << std::endl;
                continue;
            }

            if(choice_data.contains("require") && !hasModifiers(modifiers, choice_data.at("require"))) {
                type(getInvalidMessage(data, choice_data, "require"), type_delay, "\n");
                std::cout << std::endl;
                continue;
            }

            if(choice_data.contains("next") && !choice_data.at("next").empty()) {
                next_scenario = choice_data.at("next");
            }
            
            if(choice_data.contains("subtract") && !choice_data.at("subtract").empty()) {
                subtractModifiers(modifiers, choice_data.at("subtract"));
            }

            if(choice_data.contains("add") && !choice_data.at("add").empty()) {
                addModifiers(modifiers, choice_data.at("add"));
            }

            bool has_message = choice_data.contains("message");
            if(has_message) {
                type(choice_data.at("message"), type_delay, "\n");
                std::cout << std::endl;
            }

            attempts[choice]++;

            if(choice_data.contains("gameOver") && choice_data.at("gameOver")) {
                std::cout << "Game Over" << std::endl;
                game_over = true;
                break;
            }

            if(!next_scenario.empty()) {
                break;
            }

            if(!has_message) {
                type(getInvalidMessage(data, choice_data, "default"), type_delay, "\n");
                std::cout << std::endl;
            }
        }

        attempts.clear();
        if(!game_over) {
            scenario_file = path::joinPath(scenario_dir, path::appendFileExtension(next_scenario, "json"));
        }
    }
}

int main()
{
    std::string scenario_dir = path::joinPath(path::sourcePath(), "../../resources/stories/School Day/scenarios");
    std::string start_scenario = path::appendFileExtension("start", "json");
    play(scenario_dir, start_scenario);
    return 0;
}