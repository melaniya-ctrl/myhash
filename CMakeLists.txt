cmake_minimum_required(VERSION 4.4.2)
project(SystemCM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

set(SOURCES main.c ui.c callbacks.c db.c salt.c)

add_executable(cmake_system ${SOURCES})

target_include_directories(cmake_system PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_libraries(cmake_system ${GTK4_LIBRARIES} ${SQLITE3_LIBRARIES})
target_compile_options(cmake_system PRIVATE -Wall -Wextra -g)
