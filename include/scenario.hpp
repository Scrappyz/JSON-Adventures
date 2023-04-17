#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "scenario_id.hpp"

class Scenario {
    private:
        ScenarioId scenario_id;
        std::string scenario;
        std::unordered_set<std::string> keywords;
        //static std::unordered_map<ScenarioId, std::unordered_set<std::pair<int, std::string>>> choices;

        void printKeywords() const;
        //void printConditions();
    public:
        Scenario() : scenario_id(), scenario(), keywords{} {}

        // Getters
        std::string getScenarioId() const
        {
            return scenario_id.getId();
        }
        std::string getScenarioTitle() const 
        {
            return scenario_id.getTitle();
        }
        std::string getScenario() const
        {
            return scenario;
        }
        std::unordered_set<std::string> getKeywords() const
        {
            return keywords;
        }
        // static std::unordered_map<ScenarioId, std::unordered_set<std::pair<int, std::string>>> getChoices()
        // {
        //     return choices;
        // }
        
        // Setters
        void setScenarioId(const std::string& id)
        {
            this->scenario_id.setId(id);
        }
        void setScenarioTitle(const std::string& title)
        {
            this->scenario_id.setTitle(title);
        }
        void setScenario(const std::string& scenario)
        {
            this->scenario = scenario;
        }
        void setKeywords(const std::unordered_set<std::string>& keywords)
        {
            this->keywords = keywords;
        }

        void addKeyword(const std::string& keyword)
        {
            keywords.insert(keyword);
        }
        // void setChoices(const std::unordered_map<ScenarioId, std::unordered_set<std::pair<int, std::string>>>& choices)
        // {
        //     this->choices = choices;
        // }

        // static void addToChoices(const ScenarioId& id, const int& choice);
        // static void addToChoices(const ScenarioId& id, const std::string& choice);

        void printScenario() const;

        struct ScenarioHash {
            std::size_t operator()(const Scenario& s) const 
            {
                return std::hash<std::string>{}(s.scenario_id.getId());
            }
        };

        bool operator==(const Scenario& s) const
        {
            return (this->getScenarioId() == s.getScenarioId());
        }
};