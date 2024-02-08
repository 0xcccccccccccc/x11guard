cmake_minimum_required(VERSION 3.28)
project(x11guard C)

set(CMAKE_C_STANDARD 11)
link_libraries(X11 dl)

add_library(x11guard SHARED library.c)

install(
        TARGETS x11guard
        LIBRARY DESTINATION lib
)

install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/x11guard-global-hook.sh DESTINATION /etc/profile.d
)