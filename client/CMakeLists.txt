if(MSVC)
add_compile_options(
		$<$<CONFIG:>:/MT> 
		$<$<CONFIG:Debug>:/MTd> 
		$<$<CONFIG:Release>:/MT> 
)
endif()

# link_directories("${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/lib/")

# add_compile_options("$<$<NOT:$<CONFIG:Debug>>:/Zi>")
# add_link_options("$<$<NOT:$<CONFIG:Debug>>:/DEBUG>")
# add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
# add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")

file(GLOB sources
    "Lib/imgui/*.cpp"
    "Lib/minhook/*.cpp"
    "Lib/minhook/hde/*.cpp"
	"src/main.cpp"
	"src/utils/*.cpp"
    "src/gui/*.cpp"
    "src/gui/renderer/*.cpp"
    "src/hook/*.cpp"
    "src/hook/hooks/*.cpp"
    "src/module/*.cpp"
    "src/module/modules/*.cpp"
    "src/gui/menus/*.cpp"
    # "src/gui/assets/fonts/*.cpp"
)

add_library(Birb SHARED ${sources})

target_include_directories(Birb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/include/")
target_link_libraries(Birb PRIVATE d3d12.lib dxgi.lib version)