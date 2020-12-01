# Root file
cmake_minimum_required (VERSION 2.8.12)
project (ORBITALS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# List the subprojects
add_subdirectory (Orbitals)
add_subdirectory (OrbitalsTests)
add_subdirectory (OrbitalsDesktop)

