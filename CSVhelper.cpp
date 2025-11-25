// CSVHelper.cpp
#include "CSVHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CSVHelper::save(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    // header row
    file << "ID,FirstName,LastName,GPA,CreditHours,Major\n";

    for (const Student& s : students) {
        file << s.getID() << ","
            << s.getFirstName() << ","
            << s.getLastName() << ","
            << s.getGPA() << ","
            << s.getCreditHours() << ","
            << s.getMajor() << "\n";
    }

    file.close();
}

std::vector<Student> CSVHelper::load(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Student> students;

    if (!file.is_open()) {
        std::cout << "Error opening file for reading.\n";
        return students;
    }

    std::string line;
    std::getline(file, line);  // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;

        int id, creditHours;
        double gpa;
        std::string fname, lname, major;

        std::getline(ss, item, ',');
        id = std::stoi(item);

        std::getline(ss, fname, ',');

        std::getline(ss, lname, ',');

        std::getline(ss, item, ',');
        gpa = std::stod(item);

        std::getline(ss, item, ',');
        creditHours = std::stoi(item);

        std::getline(ss, major, ',');

        students.emplace_back(id, fname, lname, gpa, creditHours, major);
    }

    file.close();
    return students;
}
