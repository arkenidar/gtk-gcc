cmake_minimum_required(VERSION 3.22)
project(project-gtk-app LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_executable(project-gtk-app main.c)
target_link_libraries(project-gtk-app PRIVATE PkgConfig::GTK4)
