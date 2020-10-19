# Add executable here
add_executable (Orbitals-Tests main.cpp)

# Link to the orbitals library
target_link_libraries (Orbitals-Tests LINK_PUBLIC Orbitals)

