#include "ScaleTransposer.h"
#include <cmath>


ScaleTransposer::ScaleTransposer() {
    this->noteIndices = {
        {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
        {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
    };

    // for PINEAL MODE
    this->availableNotes = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };

    // enumerate the available scales
    this->major = {
        {0, 130.81},  // C3
        {2, 146.83},  // D3
        {4, 164.81},  // E3
        {5, 174.61},  // F3
        {7, 196.00},  // G3
        {9, 220.00},  // A3
        {11, 246.94}  // B3
    };
    this->scaleIndices["Major"] = {0, 2, 4, 5, 7, 9, 11};

    this->minor = {
        {0, 130.81},   // C3
        {2, 146.83},   // D3
        {3, 155.56},   // E_flat_3
        {5, 174.61},   // F3
        {7, 196.00},   // G3
        {8, 207.65},   // A_flat_3
        {10, 233.08}   // B_flat_3
    };
    this->scaleIndices["Minor"] = {0, 2, 3, 5, 7, 8, 10};

    this->lydian = {
        {0, 130.81},  // C3
        {2, 146.83},  // D3
        {4, 164.81},  // E3
        {6, 185.00},  // F_sharp_3
        {7, 196.00},  // G3
        {9, 220.00},  // A3
        {11, 246.94}  // B3
    };
    this->scaleIndices["Lydian"] = {0, 2, 4, 6, 7, 9, 11};


    this->blues = {
        {0, 130.81},   // C3
        {3, 155.56},   // E_flat_3
        {5, 174.61},   // F3
        {6, 185.00},   // F_sharp_3
        {7, 196.00},   // G3
        {10, 233.08}   // B_flat_3
    };
    this->scaleIndices["Blues"] = {0, 3, 5, 6, 7, 10};

    this->hijaz = {
        {0, 130.81},   // C3
        {1, 138.59},   // D_flat_3
        {4, 164.81},   // E3
        {5, 174.61},   // F3
        {7, 196.00},   // G3
        {8, 207.65},   // G_sharp_3
        {10, 233.08},  // B_flat_3
    };
    this->scaleIndices["Hijaz"] = {0, 1, 4, 5, 7, 8, 10};


    this->dorian = {
        {0, 130.81},   // C3
        {2, 146.83},   // D3
        {3, 155.56},   // E_flat_3
        {5, 174.61},   // F3
        {7, 196.00},   // G3
        {9, 220.00},   // A3
        {10, 233.08}   // B_flat_3
    };
    this->scaleIndices["Dorian"] = {0, 2, 3, 5, 7, 9, 10};


    this->phrygian = {
        {0, 130.81},   // C3
        {1, 138.59},   // D_flat_3
        {3, 155.56},   // E_flat_3
        {5, 174.61},   // F3
        {7, 196.00},   // G3
        {8, 207.65},   // A_flat_3
        {10, 233.08}   // B_flat_3
    };
    this->scaleIndices["Phrygian"] = {0, 1, 3, 5, 7, 8, 10};

    this->diminished = {
        {0, 130.81},   // C3
        {1, 138.59},   // C_sharp_3/D_flat_3
        {3, 155.56},   // E_flat_3
        {4, 164.81},   // E3
        {6, 185.00},   // F_sharp_3
        {7, 196.00},   // G3
        {9, 220.00},   // A3
        {10, 233.08}   // B_flat_3
    };
    this->scaleIndices["Diminished"] = {0, 1, 3, 4, 6, 7, 9, 10};



    // stick them in the map
    this->baseScale["Major"] = this->major;
    this->baseScale["Minor"] = this->minor;
    this->baseScale["Lydian"] = this->lydian;
    this->baseScale["Blues"] = this->blues;
    this->baseScale["Hijaz"] = this->hijaz;
    this->baseScale["Dorian"] = this->dorian;
    this->baseScale["Phrygian"] = this->phrygian;
    this->baseScale["Diminished"] = this->phrygian;

    // for PINEAL MODE
    this->availableScales = {
        "Major",
        "Minor",
        "Lydian",
        "Blues",
        "Hijaz",
        "Dorian",
        "Phrygian",
        "Diminished"
    };
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