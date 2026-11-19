#ifndef CGPACALCULATOR_H
#define CGPACALCULATOR_H

#include <vector>
#include "course.h"

// ============================================================
// Semester Structure
// Groups a list of courses into one semester.
// ============================================================
struct Semester {
    int semesterNumber;          // e.g., 1, 2, 3 …
    std::vector<Course> courses; // All courses added to this semester
    double gpa;                  // GPA calculated for this semester
};

// ============================================================
// CGPACalculator Class
// Core logic class: manages semesters, computes GPA / CGPA.
// Demonstrates OOP: encapsulation, constructors, member functions.
// ============================================================
class CGPACalculator {
private:
    std::vector<Semester> semesters; // List of all saved semesters

public:
    // Constructor & Destructor
    CGPACalculator();
    ~CGPACalculator();

    // ---- Semester GPA Calculation ----
    // Calculates GPA from a list of courses
    // Formula: GPA = Total Grade Points / Total Credits
    // Returns 0.0 if totalCredits == 0  (prevents division by zero)
    double calculateGPA(const std::vector<Course>& courses) const;

    // ---- CGPA Calculation ----
    // CGPA = Total Grade Points of All Semesters / Total Credits of All Semesters
    double calculateCGPA() const;

    // ---- Semester Management ----
    // Saves a semester (with its GPA) into the internal list
    void addSemester(const std::vector<Course>& courses, double gpa);

    // Returns all saved semesters (read-only)
    const std::vector<Semester>& getSemesters() const;

    // Returns how many semesters have been saved
    int getSemesterCount() const;

    // Clears all semesters (used by the Reset button)
    void reset();
};

#endif // CGPACALCULATOR_H
