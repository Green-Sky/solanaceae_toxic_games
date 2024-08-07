cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(FetchContent)

if (NOT TARGET imgui)
	message("II using FetchContent imgui")
	FetchContent_Declare(imgui
		GIT_REPOSITORY https://github.com/ocornut/imgui.git
		GIT_TAG 8199457 # v1.91.0
		EXCLUDE_FROM_ALL
	)

	FetchContent_GetProperties(imgui)
	if(NOT imgui_POPULATED)
		FetchContent_Populate(imgui)

		add_library(imgui STATIC
			${imgui_SOURCE_DIR}/imgui.h
			${imgui_SOURCE_DIR}/imgui_internal.h

			${imgui_SOURCE_DIR}/imgui.cpp
			${imgui_SOURCE_DIR}/imgui_demo.cpp
			${imgui_SOURCE_DIR}/imgui_draw.cpp
			${imgui_SOURCE_DIR}/imgui_tables.cpp
			${imgui_SOURCE_DIR}/imgui_widgets.cpp
			${imgui_SOURCE_DIR}/imstb_rectpack.h
			${imgui_SOURCE_DIR}/imstb_textedit.h
			${imgui_SOURCE_DIR}/imstb_truetype.h

			${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h
			${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
		)
		target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
		target_compile_features(imgui PUBLIC cxx_std_11)
	endif()
endif()

# TODO: move entt dep into solanaceae_contact
if (NOT TARGET EnTT::EnTT)
	message("II using FetchContent EnTT")
	FetchContent_Declare(EnTT
		GIT_REPOSITORY https://github.com/skypjack/entt.git
		GIT_TAG v3.12.2
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(EnTT)
endif()

if (NOT TARGET solanaceae_contact)
	message("II using FetchContent solanaceae_contact")
	FetchContent_Declare(solanaceae_contact
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_contact.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_contact)
endif()

if (NOT TARGET solanaceae_plugin)
	message("II using FetchContent solanaceae_plugin")
	FetchContent_Declare(solanaceae_plugin
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_plugin.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_plugin)
endif()

if (NOT TARGET solanaceae_toxcore)
	message("II using FetchContent solanaceae_toxcore")
	# set option to interface only? or make default
	FetchContent_Declare(solanaceae_toxcore
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_toxcore.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_toxcore)
endif()

if (NOT TARGET solanaceae_tox_contacts AND NOT TARGET solanaceae_tox_messages)
	message("II using FetchContent solanaceae_tox")
	FetchContent_Declare(solanaceae_tox
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_tox.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_tox)
endif()

