cmake_minimum_required(VERSION 3.28.1)
project(fracudal-project)

find_package(X11)

add_executable(fracudal FractalRender.cpp DisplayScreen.cpp main.cpp)

target_link_libraries(fracudal
	${X11_LIBRARIES}
)
