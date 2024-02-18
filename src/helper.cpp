#include "helper.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using json = nlohmann::json;

void type(const std::string& str, int delay, const std::string& append)
{
    for(const auto& i : str) {
        std::cout << i;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << append;
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

std::string getInvalidMessage(const json& data, const json& choice_data, const std::string& type)
{
    std::vector<std::string> msgs;
    json choice_invalids;
    if(choice_data.contains("invalids")) {
        choice_invalids = choice_data.at("invalids");
    }

    if(!choice_invalids.empty() && choice_invalids.is_array()) {
        msgs = choice_invalids;
        return msgs[randomNumber(0, msgs.size()-1)];
    }

    if(!choice_invalids.empty() && choice_invalids.contains(type) && !choice_invalids.at(type).empty()) {
        msgs = choice_invalids.at(type);
        return msgs[randomNumber(0, msgs.size()-1)];
    }

    if(!choice_invalids.empty() && choice_invalids.contains("default") && !choice_invalids.at("default").empty()) {
        msgs = choice_invalids.at("default");
        return msgs[randomNumber(0, msgs.size()-1)];
    }

    if(data.contains("invalids") && !data.at("invalids").empty()) {
        msgs = data.at("invalids");
        return msgs[randomNumber(0, msgs.size()-1)];
    }

    return std::string();
}