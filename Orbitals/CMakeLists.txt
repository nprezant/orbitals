# Create a library called "Orbitals" which includes all the source files
add_library (Orbitals orbitalsystem.cpp orbital.cpp primarybody.cpp classicalorbitalelements.cpp lambert.cpp newtonsmethod.cpp)

# Make sure the compiler can find the include files for this libary
target_include_directories (Orbitals PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
