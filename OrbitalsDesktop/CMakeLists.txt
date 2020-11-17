set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Quick3D REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Quick3D REQUIRED)

# Add library for the orbitals interface and link to the static Orbitals library
add_library(OrbitalsInterface orbitalsinterface.cpp)
target_link_libraries(OrbitalsInterface Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Orbitals)

add_executable(OrbitalsDesktop
    main.cpp
    qml.qrc
    orbitalchangedata.h
    qqmlvector.h
)

target_compile_definitions(OrbitalsDesktop
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(OrbitalsDesktop
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Quick3D OrbitalsInterface)
