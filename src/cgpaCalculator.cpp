#include "cgpaCalculator.h"

// ============================================================
// CGPACalculator Class Implementation
// ============================================================

// Constructor
CGPACalculator::CGPACalculator() {}

// Destructor
CGPACalculator::~CGPACalculator() {}

// ---- Calculate Semester GPA ----
// Loops through all courses, sums grade points and credits,
// then divides to find GPA.
double CGPACalculator::calculateGPA(const std::vector<Course>& courses) const {
    double totalGradePoints = 0.0;
    double totalCredits     = 0.0;

    for (const Course& c : courses) {
        totalGradePoints += c.getGradePoints(); // grade × creditHours
        totalCredits     += c.getCreditHours();
    }

    // Guard against division by zero
    if (totalCredits == 0.0) {
        return 0.0;
    }

    return totalGradePoints / totalCredits;
}

// ---- Calculate Overall CGPA ----
// Pools all semesters together and computes a weighted average.
double CGPACalculator::calculateCGPA() const {
    double totalGradePoints = 0.0;
    double totalCredits     = 0.0;

    for (const Semester& sem : semesters) {
        for (const Course& c : sem.courses) {
            totalGradePoints += c.getGradePoints();
            totalCredits     += c.getCreditHours();
        }
    }

    // Guard against division by zero
    if (totalCredits == 0.0) {
        return 0.0;
    }

    return totalGradePoints / totalCredits;
}

// ---- Add a Semester ----
// Creates a Semester struct and pushes it to the semesters vector.
void CGPACalculator::addSemester(const std::vector<Course>& courses, double gpa) {
    Semester sem;
    sem.semesterNumber = static_cast<int>(semesters.size()) + 1;
    sem.courses        = courses;
    sem.gpa            = gpa;
    semesters.push_back(sem);
}

// Returns all saved semesters
const std::vector<Semester>& CGPACalculator::getSemesters() const {
    return semesters;
}

// Returns the number of saved semesters
int CGPACalculator::getSemesterCount() const {
    return static_cast<int>(semesters.size());
}

// Clears all saved semesters (full reset)
void CGPACalculator::reset() {
    semesters.clear();
}
