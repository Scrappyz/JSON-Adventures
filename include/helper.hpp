#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"

void type(const std::string& str, int delay, const std::string& append = "");
std::string toLower(std::string str);
int randomNumber(int min, int max);
std::vector<std::string> parseChoice(const std::string& choice);
std::string getChoice(std::string input, const nlohmann::json& choices);
bool hasModifiers(const std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& requires);
void addModifiers(std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& add);
void subtractModifiers(std::unordered_map<std::string, int>& modifiers, const std::unordered_map<std::string, int>& subtract);
std::string getInvalidMessage(const nlohmann::json& data, const nlohmann::json& choice_invalids, const std::string& type);
std::string scenarioToString(const nlohmann::json& data);