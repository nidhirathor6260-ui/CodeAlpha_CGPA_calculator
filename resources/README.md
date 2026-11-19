# Resources Folder

Place any icon files (.ico, .png) or Qt resource files (.qrc) here.

## Usage Example
To add a window icon, place `icon.ico` in this folder and reference it in CMakeLists.txt:
```cmake
set_target_properties(CGPACalculator PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_ICON_FILE icon.icns
)
```
Then set the icon in `main.cpp`:
```cpp
app.setWindowIcon(QIcon(":/resources/icon.ico"));
```
