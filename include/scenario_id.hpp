#pragma once

#include <string>

class ScenarioId {
    private:
        std::string id;
        std::string title;
    public:
        // Getters
        std::string getId() const
        {
            return id;
        }
        std::string getTitle() const
        {
            return title;
        }

        // Setters
        void setId(const std::string& id)
        {
            this->id = id;
        }
        void setTitle(const std::string& title)
        {
            this->title = title;
        }
};
