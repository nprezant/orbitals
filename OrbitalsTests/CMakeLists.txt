# Add executable here
add_executable (OrbitalsTests main.cpp)

# Link to the orbitals library
target_link_libraries (OrbitalsTests LINK_PUBLIC Orbitals)

