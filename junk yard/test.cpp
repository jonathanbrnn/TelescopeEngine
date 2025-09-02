#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

int main() {
    // Create a JSON object
    nlohmann::json j;
    j["name"] = "Jonathan";
    j["age"] = 19;
    j["skills"] = {"beer" "", ""};

    // Write JSON to a file
    std::ofstream outFile("data.json");
    outFile << j.dump(4);
    outFile.close();

    // Read JSON back from the file
    std::ifstream inFile("data.json");
    nlohmann::json j2;
    inFile >> j2;
    inFile.close();

    std::cout << to_string(j2["name"]) << std::endl;      
    std::cout << j2["age"] << std::endl;       

    for (const auto& skill : j2["skills"]) {
        std::cout << skill << std::endl;       
    }

    return 0;
}
