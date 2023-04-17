#include <iostream>
#include <fstream>
#include <vector>
#include "scenario.hpp"

using namespace std;

void printScenarios(const vector<Scenario>& scene)
{
    for(int i = 0; i < scene.size(); i++) {
        scene[i].printScenario();
        cout << "================================================" << endl;
    }
}

void loadScenes(vector<Scenario>& v, unordered_map<string, int>& pos)
{
    string temp;
    string path_append;
    #ifdef NDEBUG
        path_append = "";
    #else
        path_append = "../../";
    #endif
    ifstream file(path_append + "resources/scenarios.txt");
    if(file.is_open()) {
        Scenario scene;
        string str;
        while(getline(file, temp)) {
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
                    pos[scene.getScenarioId()] = v.size()-1;
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
            pos[scene.getScenarioId()] = v.size()-1;
        }
        scene = Scenario();
        file.close();
        
        file = ifstream(path_append + "resources/keywords.txt");
        vector<string> ids;
        vector<string> keys;
        while(getline(file, temp)) {
            int i = 0;
            while(temp.back() == ' ') {
                temp.pop_back();
            }
            if(temp.substr(0, 3) == "===") {
                continue;
            }
            if(temp.substr(0, 3) == "id:") {
                i = 3;
                while(i < temp.size() && temp[i] == ' ') {
                    i++;
                }
                while(i < temp.size()) {
                    if(temp[i] == ' ') {
                        i++;
                        continue;
                    } else if(temp[i] == ',') {
                        ids.push_back(str);
                        str.clear();
                    } else {
                        str.push_back(temp[i]);
                    }
                    i++;
                    if(i == temp.size()) {
                        ids.push_back(str);
                        str.clear();
                    }
                }
            } else {
                keys.push_back(temp);
            }
        }
        for(int i = 0; i < ids.size(); i++) {
            for(int j = 0; j < keys.size(); j++) {
                v[pos[ids[i]]].addKeyword(keys[j]);
            }
        }
    } else {
        cout << "[Error] Could not open file" << endl;
    }
    file.close();
}

int main()
{
    unordered_map<string, int> pos; // <id, position> to keep track of scenario position in scenes
    vector<Scenario> scenes;
    loadScenes(scenes, pos);
    printScenarios(scenes);
    return 0;
}