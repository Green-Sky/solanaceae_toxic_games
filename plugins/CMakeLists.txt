cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(plugin_toxic_games SHARED
	./plugin_toxic_games.cpp
)

target_link_libraries(plugin_toxic_games PUBLIC
	solanaceae_plugin
	solanaceae_toxic_games
)

