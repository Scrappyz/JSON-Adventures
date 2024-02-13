#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
    std::cout << "hello " << std::endl;
    json j = json::parse(R"(
        {
            "pi": 3.14,
            "happy": true
        }
    )");
    std::ofstream f("file.json");
    f << j;
    f.close();
    return 0;
}