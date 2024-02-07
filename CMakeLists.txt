cmake_minimum_required(VERSION 3.28.1)
project(fracudal-projecti LANGUAGES CXX CUDA)

find_package(X11)

add_executable(fracudal
			   FractalRender.cpp
			   DisplayScreen.cpp
			   main.cu
		   )

set_target_properties(fracudal 
					  PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

set_property(TARGET fracudal
			 PROPERTY CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(fracudal
	${X11_LIBRARIES}
)
