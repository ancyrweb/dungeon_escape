find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(editor main.cpp
        MainWindow.cpp
        MainWindow.hpp)

target_link_libraries(editor PRIVATE Qt6::Core Qt6::Widgets SFML::Graphics shared)
target_include_directories(editor PRIVATE ${CMAKE_SOURCE_DIR}/shared)