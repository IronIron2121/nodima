#pragma once

#include <map>

class ScaleTransposer{
private:
    // the frequencies of every available scale in Hz
    std::map<std::string, std::map<int, double>> baseScale;
    // every note in the scale relative to C
    std::map<std::string, int> noteIndices;
    // function to transpose chosen scale based on user input
    std::map<int, double> transpose(std::string targetKey, std::string scaleName);


    // available scales. we list them at their values at C4
    std::map<int, double> major;
    std::map<int, double> minor;
    std::map<int, double> blues;
    std::map<int, double> lydian;




public:
    ScaleTransposer();

};
