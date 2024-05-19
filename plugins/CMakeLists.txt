cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(plugin_toxic_games SHARED
	./plugin_toxic_games.cpp
)

set_target_properties(plugin_toxic_games PROPERTIES
	C_VISIBILITY_PRESET hidden
	POSITION_INDEPENDENT_CODE ON
)
target_compile_definitions(plugin_toxic_games PUBLIC ENTT_API_IMPORT)

target_link_libraries(plugin_toxic_games PUBLIC
	solanaceae_plugin
	solanaceae_toxic_games
)

