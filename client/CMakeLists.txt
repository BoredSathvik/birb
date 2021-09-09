cmake_minimum_required(VERSION 3.21.0)
set(CMAKE_CXX_STANDARD 20)

project(Birb VERSION 1.0)

  
if(MSVC)
add_compile_options(
		$<$<CONFIG:>:/MT> 
		$<$<CONFIG:Debug>:/MTd> 
		$<$<CONFIG:Release>:/MT> 
)
endif()

link_directories("${CMAKE_CURRENT_LIST_DIR}/Libs/MinHook/")

file(GLOB sources
    "src/main.cpp"
	"src/Hook/*.cpp"
	"src/Utils/*.cpp"
	"src/Module/*.cpp"
	"src/Module/Modules/*.cpp"
	"src/sdk/*.cpp"
)

add_library(Birb SHARED ${sources})

target_include_directories(Birb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Libs/MinHook/")
target_link_libraries(Birb PRIVATE MinHook)