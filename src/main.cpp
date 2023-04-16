#include <iostream>
#include <fstream>
#include <vector>
#include "scenario.hpp"

using namespace std;

void printScenarios(const vector<Scenario>& scene)
{
    for(int i = 0; i < scene.size(); i++) {
        cout << "Id: " << scene[i].getScenarioId() << endl;
        cout << "Title: " << scene[i].getScenarioTitle() << endl;
        cout << scene[i].getScenario() << endl;
    }
}

vector<Scenario> loadScenes()
{
    vector<Scenario> v;

    string temp;
    ifstream scenario("resources/scenarios.txt");
    if(scenario.is_open()) {
        Scenario scene;
        string str;
        while(getline(scenario, temp)) {
            int i = 0;
            while(temp.back() == ' ') {
                temp.pop_back();
            }
            if(temp.empty()) {
                str.push_back('\n');
                continue;
            }
            if(temp.substr(0, 3) == "===") {
                if(!str.empty()) {
                    scene.setScenario(str);
                    str.clear();
                    v.push_back(scene);
                    scene = Scenario();
                }
                continue;
            }
            if(temp.substr(0, 3) == "id:") {
                i = 3;
                while(i < temp.size() && temp[i] == ' ') {
                    i++;
                }
                while(i < temp.size()) {
                    str.push_back(temp[i]);
                    i++;
                }
                scene.setScenarioId(str);
                str.clear();
            } else if(temp.substr(0, 6) == "title:") {
                i = 6;
                while(i < temp.size() && temp[i] == ' ') {
                    i++;
                }
                while(i < temp.size()) {
                    str.push_back(temp[i]);
                    i++;
                }
                scene.setScenarioTitle(str);
                str.clear();
            } else {
                while(i < temp.size() && temp[i] == ' ') {
                    i++;
                }
                while(i < temp.size()) {
                    str.push_back(temp[i]);
                    i++;
                }
                str.push_back('\n');
            }
        }
        if(!str.empty()) {
            scene.setScenario(str);
            str.clear();
            v.push_back(scene);
        }
        scene = Scenario();
    } else {
        cout << "[Error] Could not open file" << endl;
    }
    return v;
}

int main()
{
    vector<Scenario> scenes = loadScenes();
    printScenarios(scenes);
    return 0;
}