#include "course.h"

// ============================================================
// Course Class Implementation
// ============================================================

// Constructor: sets the course name, grade, and credit hours
Course::Course(const QString& name, double grade, double creditHours)
    : name(name), grade(grade), creditHours(creditHours) {}

// Destructor
Course::~Course() {}

// Returns the course name
QString Course::getName() const {
    return name;
}

// Returns the grade obtained
double Course::getGrade() const {
    return grade;
}

// Returns the credit hours
double Course::getCreditHours() const {
    return creditHours;
}

// Calculates and returns grade points for this course
// Formula: Grade Points = Grade × Credit Hours
double Course::getGradePoints() const {
    return grade * creditHours;
}
