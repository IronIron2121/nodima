#pragma once

#include <iostream>
#include <map>
#include <vector>

class ScaleTransposer{
private:

    // every note in the scale relative to C
    std::map<std::string, int> noteIndices;
    // function to transpose chosen scale based on user input


    // available scales. we list them at their values at C4
    std::map<int, double> major;
    std::map<int, double> minor;
    std::map<int, double> blues;
    std::map<int, double> lydian;
    std::map<int, double> hijaz;
    std::map<int, double> dorian;
    std::map<int, double> phrygian;
    std::map<int, double> diminished;





public:
    ScaleTransposer();
    std::map<int, double> transpose(std::string targetKey, std::string scaleName);
    std::vector<std::string> availableScales;
    std::vector<std::string> availableNotes;
    // the frequencies of every available scale in Hz
    std::map<std::string, std::map<int, double>> baseScale;
    std::map<std::string, std::vector<int>> scaleIndices;



};
