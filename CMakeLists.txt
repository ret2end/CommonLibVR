cmake_minimum_required(VERSION 3.19)

option(REX_OPTION_INI "Enables ini config support for REX." OFF)
option(REX_OPTION_JSON "Enables json config support for REX." OFF)
option(REX_OPTION_TOML "Enables toml config support for REX." OFF)
option(SKSE_SUPPORT_XBYAK "Enables trampoline support for Xbyak." OFF)
option(BUILD_SKYRIMVR "Build for Skyrim VR" OFF)
option(SKYRIM_SUPPORT_AE "Enables support for Skyrim AE" OFF)

if (NOT BUILD_SKYRIMVR)
	project(
		CommonLibSSE
		LANGUAGES CXX
	)
else()
	project(
		CommonLibVR
		LANGUAGES CXX
	)
	add_compile_definitions(SKYRIMVR)
endif()

include(GNUInstallDirs)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

find_package(binary_io REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

include(cmake/sourcelist.cmake)

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES ${SOURCES}
)

add_library(
	"${PROJECT_NAME}"
	STATIC
	${SOURCES}
	.clang-format
	CommonLibSSE.natvis
)

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
		WINVER=0x0601	# windows 7, minimum supported version by skyrim special edition
		_WIN32_WINNT=0x0601
		"$<$<BOOL:${REX_OPTION_INI}>:REX_OPTION_INI=1>"
		"$<$<BOOL:${REX_OPTION_JSON}>:REX_OPTION_JSON=1>"
		"$<$<BOOL:${REX_OPTION_TOML}>:REX_OPTION_TOML=1>"
		"$<$<BOOL:${SKSE_SUPPORT_XBYAK}>:SKSE_SUPPORT_XBYAK=1>"
		"$<$<BOOL:${SKYRIM_SUPPORT_AE}>:SKYRIM_SUPPORT_AE=1>"
)

target_compile_features(
	"${PROJECT_NAME}"
	PUBLIC
		cxx_std_23
)

if (MSVC)
	target_compile_options(
		"${PROJECT_NAME}"
		PRIVATE
			# warnings -> errors
			/we4715	# 'function' : not all control paths return a value

			# disable warnings
			/wd4005 # macro redefinition
			/wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
			/wd4200 # nonstandard extension used : zero-sized array in struct/union
			/wd4201 # nonstandard extension used : nameless struct/union
			/wd4265 # 'type': class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
			/wd4266 # 'function' : no override available for virtual member function from base 'type'; function is hidden
			/wd4371 # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
			/wd4514 # 'function' : unreferenced inline function has been removed
			/wd4582 # 'type': constructor is not implicitly called
			/wd4583 # 'type': destructor is not implicitly called
			/wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
			/wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
			/wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
			/wd4710 # 'function' : function not inlined
			/wd4711 # function 'function' selected for inline expansion
			/wd4820 # 'bytes' bytes padding added after construct 'member_name'
			/wd5026 # 'type': move constructor was implicitly defined as deleted
			/wd5027 # 'type': move assignment operator was implicitly defined as deleted
			/wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
			/wd5053 # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
			/wd5204 # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
			/wd5220 # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
	)
endif()

if (NOT BUILD_SKYRIMVR)
	target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
else()
	set(OPENVR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/openvr/headers)
	target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
		"$<BUILD_INTERFACE:${OPENVR_INCLUDE_DIR}>"
	)
endif()


target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		binary_io::binary_io
		spdlog::spdlog
 		Advapi32.lib
		bcrypt.lib
		D3D11.lib
		d3dcompiler.lib
		Dbghelp.lib
		DXGI.lib
		Ole32.lib
		Version.lib
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		include/SKSE/Impl/PCH.h
)

install(
	TARGETS "${PROJECT_NAME}"
	EXPORT "${PROJECT_NAME}-targets"
)

install(
	EXPORT "${PROJECT_NAME}-targets"
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(
	cmake/config.cmake.in
	"${PROJECT_NAME}Config.cmake"
	@ONLY
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
	DIRECTORY
		"include/RE"
		"include/REL"
		"include/REX"
		"include/SKSE"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
