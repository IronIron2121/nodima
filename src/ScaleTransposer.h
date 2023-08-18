#pragma once

#include <iostream>
#include <map>
#include <vector>

class ScaleTransposer{
private:
    // every note in the scale relative to C
    std::map<std::string, int> noteIndices;

    // available scales. we list them from their values at C2
    std::map<int, double> major;
    std::map<int, double> minor;
    std::map<int, double> blues;
    std::map<int, double> lydian;
    std::map<int, double> hijaz;
    std::map<int, double> dorian;
    std::map<int, double> phrygian;
    std::map<int, double> diminished;

public:
    // simple constructor
    ScaleTransposer();

    // returns the frequencies of a scale given a target key and the name of a scale
    std::map<int, double> transpose(std::string targetKey, std::string scaleName);

    // lists of available scales and notes - we're only really using these for pineal mode
    std::vector<std::string> availableScales;
    std::vector<std::string> availableNotes;

    // the frequencies of every available scale in Hz
    std::map<std::string, std::map<int, double>> baseScale;
    std::map<std::string, std::vector<int>> scaleIndices;
};
