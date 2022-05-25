if(MSVC)
add_compile_options(
		$<$<CONFIG:>:/MT> 
		$<$<CONFIG:Debug>:/MTd> 
		$<$<CONFIG:Release>:/MT> 
)
endif()

link_directories("${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/lib/")

file(GLOB sources
    "Lib/imgui/*.cpp"
	"src/main.cpp"
	"src/utils/*.cpp"
    "src/gui/*.cpp"
    "src/gui/renderer/*.cpp"
    "src/hook/*.cpp"
    "src/hook/hooks/*.cpp"
    # "src/gui/dx_framework/*.cpp"
    # "src/gui/dx_framework/imgui/*.cpp"
)

add_library(Birb SHARED ${sources})

target_include_directories(Birb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/include/")
target_link_libraries(Birb PRIVATE d3d12.lib dxgi.lib PolyHook_2 capstone version)