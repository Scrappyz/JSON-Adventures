#include <gtest/gtest.h>
#include "helper.hpp"

using json = nlohmann::json;

TEST(toLower, lowercase)
{
    EXPECT_EQ(toLower("QuaSi*MoTTO^"), "quasi*motto^");
}

TEST(parseChoice, split)
{
    EXPECT_EQ(parseChoice("wassup|wasabi|potato|shit head"), std::vector<std::string>({"wassup", "wasabi", "potato", "shit head"}));
}

TEST(getChoice, get)
{
    json j = {
        {"wassup", ""},
        {"kill", ""},
        {"hi", ""}
    };
    EXPECT_EQ(getChoice("wassup there", j), "wassup");
    EXPECT_EQ(getChoice("her kill", j), "kill");
}

TEST(getInvalidMessage, working)
{
    json data;
    json choice_data;

    data = json::parse(R"(
        {
            "invalids": [
                "wassup"
            ]
        }
    )");

    choice_data = json::parse(R"(
        {
            "invalids": {
                "failedRequire": "shit",
                "failedAttempt": "hi",
                "default": "kool"
            }
        }
    )");

    EXPECT_EQ(getInvalidMessage(data, choice_data, "failedRequire"), "shit");
    EXPECT_EQ(getInvalidMessage(data, choice_data, "failedAttempt"), "hi");
    EXPECT_EQ(getInvalidMessage(data, json(), "failedRequire"), "wassup");

    data = json::parse(R"(
        {
            "invalids": "wassup"
        }
    )");

    EXPECT_EQ(getInvalidMessage(data, json(), "failedRequire"), "wassup");

    choice_data = json::parse(R"(
        {
            "invalids": {
                "failedRequire": [
                    "shit"
                ],
                "failedAttempt": [
                    "hi"
                ],
                "default": [
                    "kool"
                ]
            }
        }
    )");

    EXPECT_EQ(getInvalidMessage(data, choice_data, "failedRequire"), "shit");
    EXPECT_EQ(getInvalidMessage(data, choice_data, "failedAttempt"), "hi");
}