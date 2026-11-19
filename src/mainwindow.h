#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QScrollArea>
#include <vector>
#include "cgpaCalculator.h"

// ============================================================
// MainWindow Class
// The main GUI window of the CGPA Calculator application.
// Inherits from QMainWindow (Qt's top-level window class).
// ============================================================
class MainWindow : public QMainWindow {
    Q_OBJECT  // Required macro for Qt signals & slots

public:
    // Constructor & Destructor
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // ---- Slot functions (called when buttons are clicked) ----
    void onAddCourseClicked();      // Adds a course row to the table
    void onCalculateGPAClicked();   // Calculates and shows Semester GPA
    void onSaveSemesterClicked();   // Saves the current semester
    void onResetClicked();          // Clears everything

private:
    // ---- UI Helper Functions ----
    void setupUI();                 // Builds and arranges all widgets
    void applyStyles();             // Applies modern CSS-like QSS styles
    void updateResultsDisplay();    // Refreshes the GPA / CGPA labels
    void clearCourseInputs();       // Clears the input fields

    // ---- Core calculator object ----
    CGPACalculator calculator;

    // ---- Input Widgets ----
    QLineEdit*    courseNameInput;
    QComboBox*    gradeComboBox;    // Drop-down for letter grade
    QLineEdit*    creditHoursInput;

    // ---- Table to display courses ----
    QTableWidget* courseTable;

    // ---- Result Labels ----
    QLabel* semGPALabel;
    QLabel* cgpaLabel;
    QLabel* totalCreditsLabel;
    QLabel* semesterCountLabel;

    // ---- Buttons ----
    QPushButton* addCourseBtn;
    QPushButton* calculateGPABtn;
    QPushButton* saveSemesterBtn;
    QPushButton* resetBtn;

    // ---- Internal state ----
    std::vector<Course> currentCourses; // Courses in the current semester
    double currentGPA;                  // Last calculated semester GPA
    bool   gpaCalculated;               // True after "Calculate GPA" is pressed

    // Grade mapping: letter grade → GPA points
    double gradeToPoints(const QString& grade) const;
};

#endif // MAINWINDOW_H
