#include "scenario.hpp"

using namespace std;

void Scenario::printKeywords() const
{
    for(const auto& i : keywords) {
        cout << i << endl;
    }
}

void Scenario::printScenario() const
{
    cout << "Id: " << scenario_id.getId() << endl;
    cout << "Title: " << scenario_id.getTitle() << endl;
    cout << scenario << endl;
    cout << "Keywords:" << endl;
    printKeywords();
}