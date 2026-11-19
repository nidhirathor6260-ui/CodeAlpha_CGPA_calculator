#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QHeaderView>
#include <QFont>
#include <QFrame>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QScrollBar>

// ============================================================
// Constructor: sets up the entire window
// ============================================================
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      currentGPA(0.0),
      gpaCalculated(false)
{
    setWindowTitle("Student CGPA Calculator");
    setMinimumSize(900, 700);
    resize(1050, 760);

    setupUI();      // Build all widgets
    applyStyles();  // Apply modern colors & fonts
}

// ============================================================
// Destructor
// ============================================================
MainWindow::~MainWindow() {}

// ============================================================
// setupUI — arranges all widgets inside the main window
// ============================================================
void MainWindow::setupUI() {

    // ---- Central widget and root layout ----
    QWidget*     centralWidget = new QWidget(this);
    QVBoxLayout* rootLayout    = new QVBoxLayout(centralWidget);
    rootLayout->setSpacing(0);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    // ============================================================
    // HEADER BAR
    // ============================================================
    QWidget*     header       = new QWidget();
    QVBoxLayout* headerLayout = new QVBoxLayout(header);
    header->setObjectName("headerBar");
    headerLayout->setContentsMargins(30, 20, 30, 20);

    QLabel* titleLabel = new QLabel("🎓  Student CGPA Calculator");
    titleLabel->setObjectName("appTitle");
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel* subtitleLabel = new QLabel("Track your courses, calculate GPA, and monitor your overall CGPA");
    subtitleLabel->setObjectName("appSubtitle");
    subtitleLabel->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(titleLabel);
    headerLayout->addWidget(subtitleLabel);
    rootLayout->addWidget(header);

    // ============================================================
    // MAIN CONTENT AREA (scrollable)
    // ============================================================
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("mainScroll");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget*     contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(20);
    contentLayout->setContentsMargins(30, 25, 30, 25);
    scrollArea->setWidget(contentWidget);
    rootLayout->addWidget(scrollArea, 1);

    // ============================================================
    // SECTION 1 — ADD A COURSE
    // ============================================================
    QGroupBox*   inputGroup  = new QGroupBox("➕  Add a Course");
    inputGroup->setObjectName("sectionBox");
    QHBoxLayout* inputLayout = new QHBoxLayout(inputGroup);
    inputLayout->setSpacing(12);
    inputLayout->setContentsMargins(20, 20, 20, 20);

    // Course Name
    QVBoxLayout* nameCol = new QVBoxLayout();
    QLabel*      nameLbl = new QLabel("Course Name");
    nameLbl->setObjectName("fieldLabel");
    courseNameInput = new QLineEdit();
    courseNameInput->setPlaceholderText("e.g.  Data Structures");
    courseNameInput->setObjectName("inputField");
    nameCol->addWidget(nameLbl);
    nameCol->addWidget(courseNameInput);

    // Grade (drop-down)
    QVBoxLayout* gradeCol = new QVBoxLayout();
    QLabel*      gradeLbl = new QLabel("Grade");
    gradeLbl->setObjectName("fieldLabel");
    gradeComboBox = new QComboBox();
    gradeComboBox->setObjectName("inputField");
    // Standard letter grades with GPA equivalents in tooltips
    gradeComboBox->addItem("A+  (4.0)", "A+");
    gradeComboBox->addItem("A   (4.0)", "A");
    gradeComboBox->addItem("A-  (3.7)", "A-");
    gradeComboBox->addItem("B+  (3.3)", "B+");
    gradeComboBox->addItem("B   (3.0)", "B");
    gradeComboBox->addItem("B-  (2.7)", "B-");
    gradeComboBox->addItem("C+  (2.3)", "C+");
    gradeComboBox->addItem("C   (2.0)", "C");
    gradeComboBox->addItem("C-  (1.7)", "C-");
    gradeComboBox->addItem("D+  (1.3)", "D+");
    gradeComboBox->addItem("D   (1.0)", "D");
    gradeComboBox->addItem("F   (0.0)", "F");
    gradeCol->addWidget(gradeLbl);
    gradeCol->addWidget(gradeComboBox);

    // Credit Hours
    QVBoxLayout* creditCol = new QVBoxLayout();
    QLabel*      creditLbl = new QLabel("Credit Hours");
    creditLbl->setObjectName("fieldLabel");
    creditHoursInput = new QLineEdit();
    creditHoursInput->setPlaceholderText("e.g.  3");
    creditHoursInput->setObjectName("inputField");
    creditCol->addWidget(creditLbl);
    creditCol->addWidget(creditHoursInput);

    // Add Course button
    QVBoxLayout* btnCol   = new QVBoxLayout();
    QLabel*      spacerLb = new QLabel("");  // aligns button with inputs
    addCourseBtn = new QPushButton("＋  Add Course");
    addCourseBtn->setObjectName("primaryBtn");
    addCourseBtn->setMinimumHeight(40);
    btnCol->addWidget(spacerLb);
    btnCol->addWidget(addCourseBtn);

    inputLayout->addLayout(nameCol,   3);
    inputLayout->addLayout(gradeCol,  2);
    inputLayout->addLayout(creditCol, 2);
    inputLayout->addLayout(btnCol,    2);
    contentLayout->addWidget(inputGroup);

    // ============================================================
    // SECTION 2 — COURSE TABLE
    // ============================================================
    QGroupBox*   tableGroup  = new QGroupBox("📋  Course List  —  Current Semester");
    tableGroup->setObjectName("sectionBox");
    QVBoxLayout* tableLayout = new QVBoxLayout(tableGroup);
    tableLayout->setContentsMargins(15, 15, 15, 15);

    courseTable = new QTableWidget(0, 5);
    courseTable->setObjectName("courseTable");
    courseTable->setHorizontalHeaderLabels({"#", "Course Name", "Grade", "Credit Hours", "Grade Points"});
    courseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    courseTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    courseTable->setColumnWidth(0, 50);
    courseTable->verticalHeader()->setVisible(false);
    courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // read-only
    courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    courseTable->setAlternatingRowColors(true);
    courseTable->setMinimumHeight(200);

    tableLayout->addWidget(courseTable);
    contentLayout->addWidget(tableGroup);

    // ============================================================
    // SECTION 3 — ACTION BUTTONS ROW
    // ============================================================
    QHBoxLayout* actionRow = new QHBoxLayout();
    actionRow->setSpacing(15);

    calculateGPABtn = new QPushButton("🔢  Calculate GPA");
    calculateGPABtn->setObjectName("successBtn");
    calculateGPABtn->setMinimumHeight(44);

    saveSemesterBtn = new QPushButton("💾  Save Semester");
    saveSemesterBtn->setObjectName("infoBtn");
    saveSemesterBtn->setMinimumHeight(44);

    resetBtn = new QPushButton("🔄  Reset All");
    resetBtn->setObjectName("dangerBtn");
    resetBtn->setMinimumHeight(44);

    actionRow->addWidget(calculateGPABtn);
    actionRow->addWidget(saveSemesterBtn);
    actionRow->addStretch();
    actionRow->addWidget(resetBtn);
    contentLayout->addLayout(actionRow);

    // ============================================================
    // SECTION 4 — RESULTS DISPLAY
    // ============================================================
    QGroupBox*   resultsGroup  = new QGroupBox("📊  Results");
    resultsGroup->setObjectName("sectionBox");
    QHBoxLayout* resultsLayout = new QHBoxLayout(resultsGroup);
    resultsLayout->setSpacing(15);
    resultsLayout->setContentsMargins(20, 20, 20, 20);

    // Helper lambda to create a result card
    auto makeCard = [&](const QString& cardName, const QString& defaultValue,
                        QLabel*& valueLabel) -> QWidget* {
        QWidget*     card   = new QWidget();
        card->setObjectName(cardName);
        QVBoxLayout* layout = new QVBoxLayout(card);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(15, 15, 15, 15);

        QLabel* val = new QLabel(defaultValue);
        val->setObjectName("resultValue");
        val->setAlignment(Qt::AlignCenter);
        valueLabel = val;

        layout->addWidget(val);
        return card;
    };

    // Card 1 — Semester GPA
    QWidget* semCard = new QWidget();
    semCard->setObjectName("resultCard");
    QVBoxLayout* semCardLayout = new QVBoxLayout(semCard);
    semCardLayout->setAlignment(Qt::AlignCenter);
    semCardLayout->setContentsMargins(15, 20, 15, 20);
    QLabel* semLblTitle = new QLabel("Semester GPA");
    semLblTitle->setObjectName("resultTitle");
    semLblTitle->setAlignment(Qt::AlignCenter);
    semGPALabel = new QLabel("—");
    semGPALabel->setObjectName("resultValueGPA");
    semGPALabel->setAlignment(Qt::AlignCenter);
    semCardLayout->addWidget(semLblTitle);
    semCardLayout->addWidget(semGPALabel);

    // Card 2 — Overall CGPA
    QWidget* cgpaCard = new QWidget();
    cgpaCard->setObjectName("resultCardHighlight");
    QVBoxLayout* cgpaCardLayout = new QVBoxLayout(cgpaCard);
    cgpaCardLayout->setAlignment(Qt::AlignCenter);
    cgpaCardLayout->setContentsMargins(15, 20, 15, 20);
    QLabel* cgpaLblTitle = new QLabel("Overall CGPA");
    cgpaLblTitle->setObjectName("resultTitleHL");
    cgpaLblTitle->setAlignment(Qt::AlignCenter);
    cgpaLabel = new QLabel("—");
    cgpaLabel->setObjectName("resultValueCGPA");
    cgpaLabel->setAlignment(Qt::AlignCenter);
    cgpaCardLayout->addWidget(cgpaLblTitle);
    cgpaCardLayout->addWidget(cgpaLabel);

    // Card 3 — Total Credits
    QWidget* credCard = new QWidget();
    credCard->setObjectName("resultCard");
    QVBoxLayout* credCardLayout = new QVBoxLayout(credCard);
    credCardLayout->setAlignment(Qt::AlignCenter);
    credCardLayout->setContentsMargins(15, 20, 15, 20);
    QLabel* credLblTitle = new QLabel("Total Credits (Sem)");
    credLblTitle->setObjectName("resultTitle");
    credLblTitle->setAlignment(Qt::AlignCenter);
    totalCreditsLabel = new QLabel("—");
    totalCreditsLabel->setObjectName("resultValueGPA");
    totalCreditsLabel->setAlignment(Qt::AlignCenter);
    credCardLayout->addWidget(credLblTitle);
    credCardLayout->addWidget(totalCreditsLabel);

    // Card 4 — Semesters Saved
    QWidget* semCntCard = new QWidget();
    semCntCard->setObjectName("resultCard");
    QVBoxLayout* semCntCardLayout = new QVBoxLayout(semCntCard);
    semCntCardLayout->setAlignment(Qt::AlignCenter);
    semCntCardLayout->setContentsMargins(15, 20, 15, 20);
    QLabel* semCntLblTitle = new QLabel("Semesters Saved");
    semCntLblTitle->setObjectName("resultTitle");
    semCntLblTitle->setAlignment(Qt::AlignCenter);
    semesterCountLabel = new QLabel("0");
    semesterCountLabel->setObjectName("resultValueGPA");
    semesterCountLabel->setAlignment(Qt::AlignCenter);
    semCntCardLayout->addWidget(semCntLblTitle);
    semCntCardLayout->addWidget(semesterCountLabel);

    resultsLayout->addWidget(semCard);
    resultsLayout->addWidget(cgpaCard);
    resultsLayout->addWidget(credCard);
    resultsLayout->addWidget(semCntCard);
    contentLayout->addWidget(resultsGroup);

    // ============================================================
    // CONNECT SIGNALS → SLOTS
    // Each button click calls the corresponding slot function.
    // ============================================================
    connect(addCourseBtn,     &QPushButton::clicked, this, &MainWindow::onAddCourseClicked);
    connect(calculateGPABtn,  &QPushButton::clicked, this, &MainWindow::onCalculateGPAClicked);
    connect(saveSemesterBtn,  &QPushButton::clicked, this, &MainWindow::onSaveSemesterClicked);
    connect(resetBtn,         &QPushButton::clicked, this, &MainWindow::onResetClicked);

    // Allow pressing Enter in credit hours field to add course
    connect(creditHoursInput, &QLineEdit::returnPressed, this, &MainWindow::onAddCourseClicked);
}

// ============================================================
// applyStyles — Qt Style Sheets (QSS) for a modern look
// ============================================================
void MainWindow::applyStyles() {
    setStyleSheet(R"(
        /* ---- Window Background ---- */
        QMainWindow, QWidget {
            background-color: #F0F4F8;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
            color: #2D3748;
        }

        /* ---- Header Bar ---- */
        #headerBar {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #4F46E5, stop:1 #7C3AED);
            border: none;
        }
        #appTitle {
            font-size: 26px;
            font-weight: 700;
            color: #FFFFFF;
            padding: 4px 0;
        }
        #appSubtitle {
            font-size: 13px;
            color: #C7D2FE;
            padding-bottom: 4px;
        }

        /* ---- Scroll Area ---- */
        #mainScroll {
            border: none;
            background: transparent;
        }
        #mainScroll > QWidget {
            background: transparent;
        }
        QScrollBar:vertical {
            background: #E2E8F0;
            width: 8px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #A0AEC0;
            border-radius: 4px;
        }

        /* ---- Section Group Boxes ---- */
        #sectionBox {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 12px;
            padding: 10px;
            font-weight: 600;
            font-size: 14px;
            color: #4A5568;
        }
        #sectionBox::title {
            subcontrol-origin: margin;
            left: 14px;
            padding: 0 8px;
        }

        /* ---- Labels ---- */
        #fieldLabel {
            font-weight: 600;
            font-size: 12px;
            color: #718096;
            margin-bottom: 2px;
        }

        /* ---- Input Fields ---- */
        #inputField, QLineEdit, QComboBox {
            background-color: #F7FAFC;
            border: 2px solid #E2E8F0;
            border-radius: 8px;
            padding: 8px 12px;
            font-size: 13px;
            color: #2D3748;
            min-height: 20px;
        }
        QLineEdit:focus, QComboBox:focus {
            border-color: #4F46E5;
            background-color: #FFFFFF;
        }
        QComboBox::drop-down {
            border: none;
            width: 24px;
        }
        QComboBox::down-arrow {
            image: none;
            border-left: 5px solid transparent;
            border-right: 5px solid transparent;
            border-top: 6px solid #718096;
            margin-right: 6px;
        }
        QComboBox QAbstractItemView {
            background: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            selection-background-color: #EEF2FF;
            selection-color: #4F46E5;
        }

        /* ---- Buttons ---- */
        QPushButton {
            border-radius: 8px;
            font-weight: 600;
            font-size: 13px;
            padding: 10px 20px;
            border: none;
            cursor: pointer;
        }
        #primaryBtn {
            background-color: #4F46E5;
            color: #FFFFFF;
        }
        #primaryBtn:hover  { background-color: #4338CA; }
        #primaryBtn:pressed{ background-color: #3730A3; }

        #successBtn {
            background-color: #10B981;
            color: #FFFFFF;
        }
        #successBtn:hover  { background-color: #059669; }
        #successBtn:pressed{ background-color: #047857; }

        #infoBtn {
            background-color: #3B82F6;
            color: #FFFFFF;
        }
        #infoBtn:hover  { background-color: #2563EB; }
        #infoBtn:pressed{ background-color: #1D4ED8; }

        #dangerBtn {
            background-color: #EF4444;
            color: #FFFFFF;
        }
        #dangerBtn:hover  { background-color: #DC2626; }
        #dangerBtn:pressed{ background-color: #B91C1C; }

        /* ---- Course Table ---- */
        #courseTable {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            gridline-color: #EDF2F7;
            alternate-background-color: #F7FAFC;
        }
        #courseTable QHeaderView::section {
            background-color: #EEF2FF;
            color: #4F46E5;
            font-weight: 700;
            font-size: 12px;
            padding: 10px 8px;
            border: none;
            border-bottom: 2px solid #C7D2FE;
        }
        #courseTable::item {
            padding: 8px;
            border: none;
        }
        #courseTable::item:selected {
            background-color: #EEF2FF;
            color: #4F46E5;
        }

        /* ---- Result Cards ---- */
        #resultCard {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 12px;
        }
        #resultCardHighlight {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #4F46E5, stop:1 #7C3AED);
            border-radius: 12px;
        }
        #resultTitle {
            font-size: 12px;
            font-weight: 600;
            color: #718096;
            margin-bottom: 6px;
        }
        #resultTitleHL {
            font-size: 12px;
            font-weight: 600;
            color: #C7D2FE;
            margin-bottom: 6px;
        }
        #resultValueGPA {
            font-size: 28px;
            font-weight: 700;
            color: #4F46E5;
        }
        #resultValueCGPA {
            font-size: 32px;
            font-weight: 700;
            color: #FFFFFF;
        }
    )");
}

// ============================================================
// SLOT: onAddCourseClicked
// Validates inputs and adds a course to the table and vector.
// ============================================================
void MainWindow::onAddCourseClicked() {

    // 1. Read inputs
    QString courseName  = courseNameInput->text().trimmed();
    QString gradeKey    = gradeComboBox->currentData().toString(); // e.g. "A+"
    QString creditText  = creditHoursInput->text().trimmed();

    // 2. Validate course name
    if (courseName.isEmpty()) {
        QMessageBox::warning(this, "Missing Input",
                             "⚠️  Please enter a course name.");
        courseNameInput->setFocus();
        return;
    }

    // 3. Validate credit hours (must be a positive number)
    bool ok = false;
    double credits = creditText.toDouble(&ok);
    if (!ok || credits <= 0) {
        QMessageBox::warning(this, "Invalid Credit Hours",
                             "⚠️  Please enter valid credit hours (positive number).");
        creditHoursInput->setFocus();
        return;
    }

    // 4. Convert letter grade → numeric points
    double gradePoints = gradeToPoints(gradeKey);

    // 5. Create a Course object and store it
    Course newCourse(courseName, gradePoints, credits);
    currentCourses.push_back(newCourse);

    // 6. Add a row to the table
    int row = courseTable->rowCount();
    courseTable->insertRow(row);

    auto makeItem = [](const QString& text, Qt::Alignment align = Qt::AlignCenter) {
        QTableWidgetItem* item = new QTableWidgetItem(text);
        item->setTextAlignment(align);
        return item;
    };

    courseTable->setItem(row, 0, makeItem(QString::number(row + 1)));
    courseTable->setItem(row, 1, makeItem(courseName, Qt::AlignLeft | Qt::AlignVCenter));
    courseTable->setItem(row, 2, makeItem(gradeComboBox->currentText().split(" ").first())); // Letter only
    courseTable->setItem(row, 3, makeItem(QString::number(credits, 'f', 1)));
    courseTable->setItem(row, 4, makeItem(QString::number(newCourse.getGradePoints(), 'f', 2)));

    // 7. Clear inputs for next entry
    clearCourseInputs();

    // Reset GPA calculated flag (new course added, need to recalculate)
    gpaCalculated = false;
}

// ============================================================
// SLOT: onCalculateGPAClicked
// Calculates the semester GPA from currentCourses.
// ============================================================
void MainWindow::onCalculateGPAClicked() {

    // Guard: need at least one course
    if (currentCourses.empty()) {
        QMessageBox::warning(this, "No Courses",
                             "⚠️  Please add at least one course before calculating GPA.");
        return;
    }

    // Calculate using the core calculator class
    currentGPA = calculator.calculateGPA(currentCourses);
    gpaCalculated = true;

    // Sum total credits for display
    double totalCred = 0.0;
    for (const Course& c : currentCourses) {
        totalCred += c.getCreditHours();
    }

    // Update result labels
    semGPALabel->setText(QString::number(currentGPA, 'f', 2));
    totalCreditsLabel->setText(QString::number(totalCred, 'f', 1));
}

// ============================================================
// SLOT: onSaveSemesterClicked
// Saves the current semester into the calculator and updates CGPA.
// ============================================================
void MainWindow::onSaveSemesterClicked() {

    // Guard: need at least one course
    if (currentCourses.empty()) {
        QMessageBox::warning(this, "No Courses",
                             "⚠️  Please add courses before saving a semester.");
        return;
    }

    // Auto-calculate GPA if not done yet
    if (!gpaCalculated) {
        currentGPA = calculator.calculateGPA(currentCourses);
        gpaCalculated = true;

        double totalCred = 0.0;
        for (const Course& c : currentCourses)
            totalCred += c.getCreditHours();

        semGPALabel->setText(QString::number(currentGPA, 'f', 2));
        totalCreditsLabel->setText(QString::number(totalCred, 'f', 1));
    }

    // Save semester into the calculator
    calculator.addSemester(currentCourses, currentGPA);

    // Update CGPA display
    double cgpa = calculator.calculateCGPA();
    cgpaLabel->setText(QString::number(cgpa, 'f', 2));
    semesterCountLabel->setText(QString::number(calculator.getSemesterCount()));

    // Notify user
    QMessageBox::information(this, "Semester Saved",
        QString("✅  Semester %1 saved successfully!\n"
                "Semester GPA: %2\nOverall CGPA: %3")
        .arg(calculator.getSemesterCount())
        .arg(currentGPA, 0, 'f', 2)
        .arg(cgpa, 0, 'f', 2));

    // Clear the course table and current courses for the next semester
    currentCourses.clear();
    courseTable->setRowCount(0);
    gpaCalculated = false;
    semGPALabel->setText("—");
    totalCreditsLabel->setText("—");
}

// ============================================================
// SLOT: onResetClicked
// Clears everything — courses, table, results, saved semesters.
// ============================================================
void MainWindow::onResetClicked() {

    // Ask for confirmation before wiping all data
    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirm Reset",
                              "⚠️  This will clear all courses and saved semesters.\nAre you sure?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    // Clear everything
    calculator.reset();
    currentCourses.clear();
    gpaCalculated = false;
    currentGPA = 0.0;

    courseTable->setRowCount(0);
    clearCourseInputs();

    semGPALabel->setText("—");
    cgpaLabel->setText("—");
    totalCreditsLabel->setText("—");
    semesterCountLabel->setText("0");
}

// ============================================================
// clearCourseInputs — resets the input fields
// ============================================================
void MainWindow::clearCourseInputs() {
    courseNameInput->clear();
    gradeComboBox->setCurrentIndex(0);
    creditHoursInput->clear();
    courseNameInput->setFocus();
}

// ============================================================
// updateResultsDisplay — refreshes CGPA label
// ============================================================
void MainWindow::updateResultsDisplay() {
    if (calculator.getSemesterCount() > 0) {
        double cgpa = calculator.calculateCGPA();
        cgpaLabel->setText(QString::number(cgpa, 'f', 2));
        semesterCountLabel->setText(QString::number(calculator.getSemesterCount()));
    }
}

// ============================================================
// gradeToPoints — converts a letter grade to its GPA point value
// Standard 4.0 scale
// ============================================================
double MainWindow::gradeToPoints(const QString& grade) const {
    if (grade == "A+" || grade == "A")  return 4.0;
    if (grade == "A-")                  return 3.7;
    if (grade == "B+")                  return 3.3;
    if (grade == "B")                   return 3.0;
    if (grade == "B-")                  return 2.7;
    if (grade == "C+")                  return 2.3;
    if (grade == "C")                   return 2.0;
    if (grade == "C-")                  return 1.7;
    if (grade == "D+")                  return 1.3;
    if (grade == "D")                   return 1.0;
    if (grade == "F")                   return 0.0;
    return 0.0; // Default fallback
}
