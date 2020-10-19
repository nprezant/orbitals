# Add executable here
add_executable (Orbits-Desktop main.cpp)

# Link to the orbitals library
target_link_libraries (Orbits-Desktop LINK_PUBLIC Orbitals)

