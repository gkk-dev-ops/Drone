# CMakeList.txt : CMake project for DronOnWindows, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

project ("DronOnWindows")

find_package(GLUT REQUIRED)

# Add source to this project's executable.
include_directories(inc)

add_executable (main "src/main.cpp" "src/wektor2D.cpp" "src/Scena.cpp" "src/Stozki.cpp" "src/Wzgorze.cpp" "src/Dron.cpp" "src/konkretnaMacierz.cpp" "src/OpenGL_API.cpp" "src/prostopadloscian.cpp" "src/prostopadloscian.cpp" "src/Graniastoslup.cpp" "src/PlaskaPowierzchnia.cpp" "src/Plaskowyz.cpp")
target_link_libraries(main PRIVATE GLUT::GLUT)

# TODO: Add tests and install targets if needed.
