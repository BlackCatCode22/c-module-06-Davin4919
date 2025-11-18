//
// Created by davin on 11/6/2025.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Animal.h"
#include "Species.h"

using namespace std;

// Function to load animal names from file
void loadNames(string filename, vector<string>& hyenaNames, vector<string>& lionNames,
               vector<string>& tigerNames, vector<string>& bearNames);

// Function to parse one line from arriving animals file
void parseLine(string line, int& age, string& sex, string& species,
               string& season, string& color, int& weight, string& origin);

// Function to write the zoo report
void writeReport(string filename, vector<Animal>& allAnimals);

int main() {
    // Vectors to store animal names
    vector<string> hyenaNames;
    vector<string> lionNames;
    vector<string> tigerNames;
    vector<string> bearNames;

    // Vector to store all animals
    vector<Animal> allAnimals;

    // Counters for each species
    int hyenaCount = 0;
    int lionCount = 0;
    int tigerCount = 0;
    int bearCount = 0;

    cout << "Starting Zoo Management System..." << endl << endl;

    // Step 1: Load all the animal names
    cout << "Loading animal names..." << endl;
    try {
        loadNames("animalNames.txt", hyenaNames, lionNames, tigerNames, bearNames);
        cout << "Names loaded!" << endl << endl;
    } catch (exception e) {
        cout << "Error loading names file!" << endl;
        return 1;
    }

    // Step 2: Read arriving animals and create animal objects
    cout << "Processing arriving animals..." << endl;

    ifstream inFile("arrivingAnimals.txt");
    if (!inFile) {
        cout << "Error: Cannot open arrivingAnimals.txt" << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // Variables to hold parsed data
        int age, weight;
        string sex, species, season, color, origin;

        // Parse the line
        parseLine(line, age, sex, species, season, color, weight, origin);

        // Create the right type of animal
        Animal newAnimal;

        if (species == "hyena") {
            Hyena h;
            newAnimal = h;
            hyenaCount++;
            newAnimal.setUniqueID(newAnimal.genUniqueID(hyenaCount));

            // Assign a name from the hyena names list
            if (hyenaCount <= hyenaNames.size()) {
                newAnimal.setName(hyenaNames[hyenaCount - 1]);
            }

        } else if (species == "lion") {
            Lion l;
            newAnimal = l;
            lionCount++;
            newAnimal.setUniqueID(newAnimal.genUniqueID(lionCount));

            // Assign a name from the lion names list
            if (lionCount <= lionNames.size()) {
                newAnimal.setName(lionNames[lionCount - 1]);
            }

        } else if (species == "tiger") {
            Tiger t;
            newAnimal = t;
            tigerCount++;
            newAnimal.setUniqueID(newAnimal.genUniqueID(tigerCount));

            // Assign a name from the tiger names list
            if (tigerCount <= tigerNames.size()) {
                newAnimal.setName(tigerNames[tigerCount - 1]);
            }

        } else if (species == "bear") {
            Bear b;
            newAnimal = b;
            bearCount++;
            newAnimal.setUniqueID(newAnimal.genUniqueID(bearCount));

            // Assign a name from the bear names list
            if (bearCount <= bearNames.size()) {
                newAnimal.setName(bearNames[bearCount - 1]);
            }
        }

        // Set all the animal's properties
        newAnimal.setAge(age);
        newAnimal.setSex(sex);
        newAnimal.setBirthSeason(season);
        newAnimal.setColor(color);
        newAnimal.setWeight(weight);
        newAnimal.setOrigin(origin);
        newAnimal.genBirthDay(); // Calculate birthday

        // Add animal to our list
        allAnimals.push_back(newAnimal);
    }

    inFile.close();
    cout << "Processed " << allAnimals.size() << " animals!" << endl << endl;

    // Step 3: Write the report
    cout << "Creating zoo population report..." << endl;
    writeReport("zooPopulation.txt", allAnimals);
    cout << "Report created successfully!" << endl << endl;

    cout << "Zoo Management System Complete!" << endl;

    return 0;
}

// Function to load names from the file
void loadNames(string filename, vector<string>& hyenaNames, vector<string>& lionNames,
               vector<string>& tigerNames, vector<string>& bearNames) {

    ifstream file(filename);
    if (!file) {
        throw exception();
    }

    string line;
    string currentType = "";

    while (getline(file, line)) {
        // Check what type of animal names we're reading
        if (line.find("Hyena Names:") != string::npos) {
            currentType = "hyena";
        } else if (line.find("Lion Names:") != string::npos) {
            currentType = "lion";
        } else if (line.find("Tiger names:") != string::npos) {
            currentType = "tiger";
        } else if (line.find("Bear Names:") != string::npos) {
            currentType = "bear";
        } else if (!line.empty() && currentType != "") {
            // This line has names, parse them
            string name = "";
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    // Remove spaces from the name
                    string trimmedName = "";
                    for (int j = 0; j < name.length(); j++) {
                        if (name[j] != ' ') {
                            trimmedName += name[j];
                        } else if (trimmedName.length() > 0) {
                            trimmedName += name[j];
                        }
                    }

                    // Add name to the right vector
                    if (currentType == "hyena") {
                        hyenaNames.push_back(trimmedName);
                    } else if (currentType == "lion") {
                        lionNames.push_back(trimmedName);
                    } else if (currentType == "tiger") {
                        tigerNames.push_back(trimmedName);
                    } else if (currentType == "bear") {
                        bearNames.push_back(trimmedName);
                    }

                    name = "";
                } else {
                    name += line[i];
                }
            }
            // Don't forget the last name
            if (name.length() > 0) {
                // Trim spaces
                string trimmedName = "";
                for (int j = 0; j < name.length(); j++) {
                    if (name[j] != ' ') {
                        trimmedName += name[j];
                    } else if (trimmedName.length() > 0) {
                        trimmedName += name[j];
                    }
                }

                if (currentType == "hyena") {
                    hyenaNames.push_back(trimmedName);
                } else if (currentType == "lion") {
                    lionNames.push_back(trimmedName);
                } else if (currentType == "tiger") {
                    tigerNames.push_back(trimmedName);
                } else if (currentType == "bear") {
                    bearNames.push_back(trimmedName);
                }
            }
        }
    }

    file.close();
}

// Function to parse one line of animal data
void parseLine(string line, int& age, string& sex, string& species,
               string& season, string& color, int& weight, string& origin) {

    // Find the age (first number)
    age = 0;
    int i = 0;
    while (i < line.length() && (line[i] < '0' || line[i] > '9')) {
        i++;
    }
    while (i < line.length() && line[i] >= '0' && line[i] <= '9') {
        age = age * 10 + (line[i] - '0');
        i++;
    }

    // Find sex (male or female)
    if (line.find("male hyena") != string::npos) {
        sex = "male";
        species = "hyena";
    } else if (line.find("female hyena") != string::npos) {
        sex = "female";
        species = "hyena";
    } else if (line.find("male lion") != string::npos) {
        sex = "male";
        species = "lion";
    } else if (line.find("female lion") != string::npos) {
        sex = "female";
        species = "lion";
    } else if (line.find("male tiger") != string::npos) {
        sex = "male";
        species = "tiger";
    } else if (line.find("female tiger") != string::npos) {
        sex = "female";
        species = "tiger";
    } else if (line.find("male bear") != string::npos) {
        sex = "male";
        species = "bear";
    } else if (line.find("female bear") != string::npos) {
        sex = "female";
        species = "bear";
    }

    // Find birth season
    if (line.find("born in spring") != string::npos) {
        season = "spring";
    } else if (line.find("born in summer") != string::npos) {
        season = "summer";
    } else if (line.find("born in fall") != string::npos) {
        season = "fall";
    } else if (line.find("born in winter") != string::npos) {
        season = "winter";
    } else if (line.find("unknown birth season") != string::npos) {
        season = "unknown";
    }

    // Find color (between season and "color")
    size_t colorStart = line.find("color,");
    if (colorStart == string::npos) {
        colorStart = line.find("season,");
    }

    if (colorStart != string::npos) {
        colorStart += 7; // Move past "season," or "color,"
        while (colorStart < line.length() && line[colorStart] == ' ') {
            colorStart++;
        }

        size_t colorEnd = colorStart;
        while (colorEnd < line.length() && line[colorEnd] != ',') {
            colorEnd++;
        }

        color = line.substr(colorStart, colorEnd - colorStart);

        // Remove " color" from the end if it exists
        if (color.find(" color") != string::npos) {
            color = color.substr(0, color.find(" color"));
        }
    }

    // Find weight (number before "pounds")
    size_t poundsPos = line.find("pounds");
    if (poundsPos != string::npos) {
        i = poundsPos - 1;
        while (i >= 0 && line[i] == ' ') {
            i--;
        }

        string weightStr = "";
        while (i >= 0 && line[i] >= '0' && line[i] <= '9') {
            weightStr = line[i] + weightStr;
            i--;
        }

        weight = 0;
        for (int j = 0; j < weightStr.length(); j++) {
            weight = weight * 10 + (weightStr[j] - '0');
        }
    }

    // Find origin (after "from")
    size_t fromPos = line.find("from");
    if (fromPos != string::npos) {
        origin = line.substr(fromPos + 5);
        // Remove leading spaces
        while (origin.length() > 0 && origin[0] == ' ') {
            origin = origin.substr(1);
        }
    }
}

// Function to write the zoo population report
void writeReport(string filename, vector<Animal>& allAnimals) {
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error: Cannot create " << filename << endl;
        return;
    }

    outFile << "Zoo Population Report" << endl;
    outFile << "=====================" << endl << endl;

    // Write Hyena Habitat
    outFile << "Hyena Habitat:" << endl << endl;
    for (int i = 0; i < allAnimals.size(); i++) {
        if (allAnimals[i].getSpecies() == "hyena") {
            outFile << allAnimals[i].getUniqueID() << "; "
                    << allAnimals[i].getName() << "; "
                    << allAnimals[i].getBirthDate() << "; "
                    << allAnimals[i].getColor() << "; "
                    << allAnimals[i].getSex() << "; "
                    << allAnimals[i].getWeight() << " pounds; from "
                    << allAnimals[i].getOrigin() << "; arrived "
                    << allAnimals[i].getArrivalDate() << endl;
        }
    }
    outFile << endl;

    // Write Lion Habitat
    outFile << "Lion Habitat:" << endl << endl;
    for (int i = 0; i < allAnimals.size(); i++) {
        if (allAnimals[i].getSpecies() == "lion") {
            outFile << allAnimals[i].getUniqueID() << "; "
                    << allAnimals[i].getName() << "; "
                    << allAnimals[i].getBirthDate() << "; "
                    << allAnimals[i].getColor() << "; "
                    << allAnimals[i].getSex() << "; "
                    << allAnimals[i].getWeight() << " pounds; from "
                    << allAnimals[i].getOrigin() << "; arrived "
                    << allAnimals[i].getArrivalDate() << endl;
        }
    }
    outFile << endl;

    // Write Tiger Habitat
    outFile << "Tiger Habitat:" << endl << endl;
    for (int i = 0; i < allAnimals.size(); i++) {
        if (allAnimals[i].getSpecies() == "tiger") {
            outFile << allAnimals[i].getUniqueID() << "; "
                    << allAnimals[i].getName() << "; "
                    << allAnimals[i].getBirthDate() << "; "
                    << allAnimals[i].getColor() << "; "
                    << allAnimals[i].getSex() << "; "
                    << allAnimals[i].getWeight() << " pounds; from "
                    << allAnimals[i].getOrigin() << "; arrived "
                    << allAnimals[i].getArrivalDate() << endl;
        }
    }
    outFile << endl;

    // Write Bear Habitat
    outFile << "Bear Habitat:" << endl << endl;
    for (int i = 0; i < allAnimals.size(); i++) {
        if (allAnimals[i].getSpecies() == "bear") {
            outFile << allAnimals[i].getUniqueID() << "; "
                    << allAnimals[i].getName() << "; "
                    << allAnimals[i].getBirthDate() << "; "
                    << allAnimals[i].getColor() << "; "
                    << allAnimals[i].getSex() << "; "
                    << allAnimals[i].getWeight() << " pounds; from "
                    << allAnimals[i].getOrigin() << "; arrived "
                    << allAnimals[i].getArrivalDate() << endl;
        }
    }

    outFile.close();
}