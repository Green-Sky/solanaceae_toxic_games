cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if (OFF)
add_library(toxic_games STATIC
	#./toxic/windows_stripped.h
	#./toxic/misc_tools.h
	#./toxic/misc_tools.c

	./toxic/fake_ncurses.h
	./toxic/toxic_patched_utils.h

	./toxic/game_base.h
	#./toxic/game_base.c
	./toxic/game_base_stripped.c
	./toxic/game_util.h
	./toxic/game_util.c

	#./toxic/game_centipede.h
	#./toxic/game_centipede.c
	./toxic/game_chess.h
	./toxic/game_chess.c
	#./toxic/game_life.h
	#./toxic/game_life.c
	#./toxic/game_snake.h
	#./toxic/game_snake.c
)
endif()

########################################

add_library(solanaceae_toxic_games
	./solanaceae/toxic_games/toxic_games.hpp
	./solanaceae/toxic_games/toxic_games.cpp

	./solanaceae/toxic_games/toxic_game_i.hpp

	./solanaceae/toxic_games/games/chess.hpp
	./solanaceae/toxic_games/games/chess.cpp
)

target_link_libraries(solanaceae_toxic_games PUBLIC
	solanaceae_tox_contacts
)

target_include_directories(solanaceae_toxic_games PUBLIC .)
target_compile_features(solanaceae_toxic_games PUBLIC cxx_std_17)

