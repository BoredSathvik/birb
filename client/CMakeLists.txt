if(MSVC)
add_compile_options(
		$<$<CONFIG:>:/MT> 
		$<$<CONFIG:Debug>:/MTd> 
		$<$<CONFIG:Release>:/MT> 
)
endif()

link_directories("${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook/_install/lib/")

add_library(Birb SHARED ${sources})

target_sources(Birb PRIVATE
	"main.cpp"
	"Utils/*.cpp"
)

target_include_directories(Birb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook/_install/include/")
target_link_libraries(Birb PRIVATE PolyHook_2 capstone version)