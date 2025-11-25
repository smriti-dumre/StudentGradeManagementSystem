// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int studentID;
    std::string firstName;
    std::string lastName;
    double gpa;
    int creditHours;
    std::string major;

public:
    // Constructors
    Student();
    Student(int id, const std::string& fName, const std::string& lName,
        double gpa, int creditHours, const std::string& major);

    // Getters
    int getID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    double getGPA() const;
    int getCreditHours() const;
    std::string getMajor() const;

    // Setters
    void setFirstName(const std::string& f);
    void setLastName(const std::string& l);
    void setGPA(double g);
    void setCreditHours(int c);
    void setMajor(const std::string& m);

    // Display function
    void print() const;
};

#endif

