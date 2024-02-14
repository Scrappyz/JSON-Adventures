#include "helper.hpp"
#include <random>

using json = nlohmann::json;

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