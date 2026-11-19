#ifndef COURSE_H
#define COURSE_H

#include <QString>

// ============================================================
// Course Class
// Represents a single course with its name, grade, and credits.
// Demonstrates OOP: encapsulation, constructors, and member functions.
// ============================================================
class Course {
private:
    QString name;        // Name of the course
    double  grade;       // Grade obtained (e.g., 4.0, 3.5)
    double  creditHours; // Credit hours for the course

public:
    // Constructor: initializes a course with the given values
    Course(const QString& name, double grade, double creditHours);

    // Destructor (default is fine here, but declared for OOP demonstration)
    ~Course();

    // ---- Getters (read-only access to private members) ----
    QString getName()       const;
    double  getGrade()      const;
    double  getCreditHours() const;

    // Calculate grade points for this course
    // Formula: Grade Points = Grade × Credit Hours
    double getGradePoints() const;
};

#endif // COURSE_H
