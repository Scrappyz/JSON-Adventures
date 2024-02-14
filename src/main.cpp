#include <iostream>
#include <fstream>
#include "json.hpp"
#include "os.hpp"
#include "helper.hpp"

using json = nlohmann::json;
namespace path = os::path;

// void play(const std::string& scenario_dir, const std::string& start_scenario)
// {
//     std::string scenario_file = path::joinPath(scenario_dir, start_scenario);
//     std::unordered_map<std::string, int> modifiers;
//     std::unordered_map<std::string, int> tries;
//     std::ifstream f;
//     json data;

//     while(true) {
//         f.open(scenario_file);
//         data = json::parse(f);
//         f.close();

//         std::string scenario = data.at("scenario");
//         std::cout << scenario << std::endl;
//         std::cout << std::endl;

//         if(data.at("gameOver")) {
//             std::cout << "Game Over" << std::endl;
//             break;
//         }

//         std::vector<std::string> invalids = data.at("invalids");
//         std::string input;
//         std::string next_scenario;

//         while(true) {
//             std::cout << "> ";
//             std::getline(std::cin, input);

//             std::string choice = getChoice(input, data.at("choices"));

//             if(choice.empty()) {
//                 std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
//                 std::cout << std::endl;
//                 continue;
//             }

//             json choice_data = data.at("choices").at(choice);
//             int max_tries = 1;

//             if(choice_data.contains("tries")) {
//                 max_tries = choice_data.at("tries");
//             }

//             if(max_tries >= 0 && tries.count(choice) > 0 && tries.at(choice) >= max_tries) {
//                 std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
//                 std::cout << std::endl;
//                 continue;
//             }

//             if(choice_data.contains("requires") && !hasModifiers(modifiers, choice_data.at("requires"))) {
//                 std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
//                 std::cout << std::endl;
//                 continue;
//             }

//             if(choice_data.contains("next")) {
//                 next_scenario = choice_data.at("next");
//             }
            
//             if(choice_data.contains("takes")) {
//                 subtractModifiers(modifiers, choice_data.at("takes"));
//             }

//             if(choice_data.contains("gives")) {
//                 addModifiers(modifiers, choice_data.at("gives"));
//             }

//             bool has_message = choice_data.contains("message");
//             if(has_message) {
//                 std::cout << std::string(choice_data.at("message")) << std::endl;
//                 std::cout << std::endl;
//             }

//             tries[choice]++;

//             if(!next_scenario.empty()) {
//                 break;
//             }

//             if(!has_message) {
//                 std::cout << invalids[randomNumber(0, invalids.size()-1)] << std::endl;
//                 std::cout << std::endl;
//             }
//         }

//         tries.clear();
//         scenario_file = path::joinPath(scenario_dir, path::appendFileExtension(next_scenario, "json"));
//     }
// }

int main()
{
    // std::string scenario_dir = path::joinPath(path::sourcePath(), "../../resources/stories/School Day/scenarios");
    // std::string start_scenario = path::appendFileExtension("start", "json");
    // play(scenario_dir, start_scenario);
    std::cout << toLower("This moTHe");
    return 0;
}