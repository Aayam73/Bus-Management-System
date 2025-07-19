cmake_minimum_required(VERSION 3.16)

project(busmanagement LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)      # For .ui files (Qt Designer)
set(CMAKE_AUTOMOC ON)      # For QObject/moc
set(CMAKE_AUTORCC ON)      # For .qrc files

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required Qt modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Quick Qml Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick Qml Sql)

# Add source files (Update this list properly)
add_executable(busmanagement
    main.cpp
    db.cpp
    loginwindow.cpp
    signupwindow.cpp
    startwindow.cpp
    confirmationwindow.cpp
    accountwindow.cpp
    # Add any other .cpp files you use
    # Remove `.cpp` and `db..cpp` — those are incorrect
)

# Optional: include directories if needed
# target_include_directories(busmanagement PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link Qt libraries
target_link_libraries(busmanagement
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Quick
            Qt${QT_VERSION_MAJOR}::Qml
            Qt${QT_VERSION_MAJOR}::Sql
)

# Optional: install target
install(TARGETS busmanagement
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
