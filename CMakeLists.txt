cmake_minimum_required(VERSION 3.16)

# ── Project metadata ─────────────────────────────────────────
project(CGPA-Calculator VERSION 1.0.0 LANGUAGES CXX)

# ── C++ standard ─────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Qt6 auto-tools ───────────────────────────────────────────
# These tell CMake to automatically run Qt's moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ── Find Qt6 ─────────────────────────────────────────────────
# Make sure Qt6 is installed and CMAKE_PREFIX_PATH points to it.
# Example (Windows): cmake -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64" ..
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# ── Source files ─────────────────────────────────────────────
set(SOURCES
    src/main.cpp
    src/course.cpp
    src/cgpaCalculator.cpp
    src/mainwindow.cpp
)

set(HEADERS
    src/course.h
    src/cgpaCalculator.h
    src/mainwindow.h
)

# ── Executable ───────────────────────────────────────────────
add_executable(CGPACalculator
    ${SOURCES}
    ${HEADERS}
)

# ── Link Qt libraries ─────────────────────────────────────────
target_link_libraries(CGPACalculator PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# ── Include path ─────────────────────────────────────────────
target_include_directories(CGPACalculator PRIVATE src)

# ── Windows: hide the console window in Release builds ────────
if(WIN32)
    set_target_properties(CGPACalculator PROPERTIES
        WIN32_EXECUTABLE $<CONFIG:Release>
    )
endif()
