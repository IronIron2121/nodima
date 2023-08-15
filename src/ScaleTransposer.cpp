#include "ScaleTransposer.h"
#include <cmath>


ScaleTransposer::ScaleTransposer() {
    this->noteIndices = {
        {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
        {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
    };

    // enumerate the available scales
    this->major = {
        {0, 261.63}, {2, 293.66}, {4, 329.63}, {5, 349.23},
        {7, 392.00}, {9, 440.00}, {11, 493.88}
    };
    this->baseScale["Major"] = this->major;
}

std::map<int, double> ScaleTransposer::transpose(std::string givenKey, std::string scaleName) {
    // empty map to hold our new scale
    std::map<int, double> transposedScale;
    // the difference between our target key and the base key 
    int interval = this->noteIndices[givenKey];

    // for every note in the base scale
    for (const auto& [note, freq] : baseScale[scaleName]) {
        // find the equivalent position in the target scale
        int transposedNote = (note + interval) % 12;
        // use 12th root of 2 to get factor we need to produce the target note
        transposedScale[transposedNote] = freq * std::pow(1.0594631, interval);
    }

    return transposedScale;
}
