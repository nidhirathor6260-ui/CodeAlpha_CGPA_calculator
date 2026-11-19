# 🎓 Student CGPA Calculator

A beginner-friendly **C++ desktop application** built with **Qt 6 Widgets** that lets students track their courses, calculate Semester GPA, and monitor their overall CGPA — all through a clean, modern graphical interface.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| **Add Courses** | Enter course name, letter grade, and credit hours |
| **Grade Scale** | Supports full A+ → F letter grade scale (4.0 system) |
| **GPA Calculation** | Calculates Semester GPA = Total Grade Points / Total Credits |
| **Multi-Semester** | Save multiple semesters and track them all |
| **CGPA Calculation** | Overall CGPA = Cumulative Grade Points / Cumulative Credits |
| **Course Table** | Displays all courses with grades, credits, and grade points |
| **Input Validation** | Prevents empty inputs and division by zero |
| **Reset Button** | Clears all data with one click |
| **Modern GUI** | Clean purple-themed interface with rounded cards and buttons |

---

## 🗂️ Project Structure

```
CGPA-Calculator/
│
├── src/
│   ├── main.cpp            # App entry point
│   ├── course.h/.cpp       # Course class (OOP: encapsulation)
│   ├── cgpaCalculator.h/.cpp # Core GPA/CGPA logic
│   └── mainwindow.h/.cpp   # Qt GUI window
│
├── resources/              # Icons / assets (future use)
├── CMakeLists.txt          # Build configuration
├── .gitignore              # Git exclusion rules
└── README.md               # This file
```

---

## 🧮 Grade Point Scale

| Letter Grade | GPA Points |
|:---:|:---:|
| A+ / A | 4.0 |
| A- | 3.7 |
| B+ | 3.3 |
| B | 3.0 |
| B- | 2.7 |
| C+ | 2.3 |
| C | 2.0 |
| C- | 1.7 |
| D+ | 1.3 |
| D | 1.0 |
| F | 0.0 |

---

## 🛠️ Technologies Used

- **Language:** C++ 17
- **GUI Framework:** Qt 6 (Widgets module)
- **Build System:** CMake 3.16+
- **OOP Concepts:** Encapsulation, Constructors, Destructors, Member Functions
- **STL:** `std::vector` for course/semester storage

---

## ⚙️ Prerequisites

Before building, make sure you have:

- **Qt 6** installed — download from [https://www.qt.io/download-open-source](https://www.qt.io/download-open-source)
- **CMake 3.16+** — download from [https://cmake.org/download](https://cmake.org/download)
- A C++ compiler:
  - Windows: **MSVC** (Visual Studio 2022) or **MinGW**
  - Linux/macOS: **GCC** or **Clang**

---

## 🚀 Build & Run Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/CGPA-Calculator.git
cd CGPA-Calculator
```

### 2. Configure with CMake

**Windows (MSVC / MinGW):**
```bash
cmake -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"
```
> Replace `6.x.x` with your Qt version and `msvc2022_64` with your kit name.

**Linux / macOS:**
```bash
cmake -B build
```

### 3. Build

```bash
cmake --build build --config Release
```

### 4. Run

**Windows:**
```bash
.\build\Release\CGPACalculator.exe
```

**Linux / macOS:**
```bash
./build/CGPACalculator
```

---

## 🖥️ Open in VS Code

1. Install the **CMake Tools** extension in VS Code.
2. Open the `CGPA-Calculator` folder: `File → Open Folder`.
3. Press **Ctrl+Shift+P** → `CMake: Configure`.
4. When prompted, select your compiler kit (MSVC / GCC / Clang).
5. Press **Ctrl+Shift+P** → `CMake: Build`.
6. Press **Ctrl+Shift+P** → `CMake: Run Without Debugging`.

---

## 📸 Sample Usage

1. Enter a course name, e.g., **Data Structures**.
2. Select a grade from the drop-down, e.g., **A (4.0)**.
3. Enter credit hours, e.g., **3**.
4. Click **➕ Add Course** — the course appears in the table.
5. Repeat for all courses.
6. Click **🔢 Calculate GPA** to see your Semester GPA.
7. Click **💾 Save Semester** to store it.
8. Add courses for the next semester and repeat.
9. The **Overall CGPA** updates automatically after each saved semester.

---

## 📐 Formulas Used

```
Grade Points  = Grade Value × Credit Hours
Semester GPA  = Σ(Grade Points) / Σ(Credit Hours)  [current semester]
Overall CGPA  = Σ(All Grade Points) / Σ(All Credit Hours)  [all semesters]
```

---

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue first.

---

## 📄 License

This project is open source under the [MIT License](LICENSE).

---

> Made with ❤️ as a college C++ project.
