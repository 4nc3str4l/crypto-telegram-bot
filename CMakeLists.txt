cmake_minimum_required(VERSION 3.11.4 FATAL_ERROR)
include(FetchContent)


# Project Name
set(PROJECT_NAME "crypto_bot")
project(${PROJECT_NAME})

# USEFULL PATHS AND DEFINITIONS
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(SRC_PATH ${CMAKE_SOURCE_DIR}/src)

# CPP 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


#######################################################################
#                           JSON LIB                                  #
#######################################################################
set(JSON_LIB ${PROJECT_SOURCE_DIR}/externals/json)
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${JSON_LIB})

#######################################################################
#                                CPR                                  #
#######################################################################

set(Boost_USE_MULTITHREADED ON)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

# INCLUDE DIRECTORIES
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

#######################################################################
#                                FMT                                  #
#######################################################################
set(FMT_DOC     OFF CACHE INTERNAL "")
set(FMT_TEST    OFF CACHE INTERNAL "")

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG        6.1.2
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
    FetchContent_Populate(fmt)
    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()

#######################################################################
#                              TGBOT                                  #
#######################################################################
FetchContent_Declare(
    tgbot
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
    GIT_TAG        v1.2.1
)

FetchContent_GetProperties(tgbot)
if(NOT tgbot_POPULATED)
    FetchContent_Populate(tgbot)
    add_subdirectory(${tgbot_SOURCE_DIR} ${tgbot_BINARY_DIR})
endif()

#######################################################################
#                               LUA                                   #
#######################################################################

# lua lib
add_library(
    lua STATIC
    externals/lua/lapi.c
    externals/lua/lauxlib.c
    externals/lua/lbaselib.c
    externals/lua/lcode.c
    externals/lua/lcorolib.c
    externals/lua/lctype.c
    externals/lua/ldblib.c
    externals/lua/ldebug.c
    externals/lua/ldo.c
    externals/lua/ldump.c
    externals/lua/lfunc.c
    externals/lua/lgc.c
    externals/lua/linit.c
    externals/lua/liolib.c
    externals/lua/llex.c
    externals/lua/lmathlib.c
    externals/lua/lmem.c
    externals/lua/loadlib.c
    externals/lua/lobject.c
    externals/lua/lopcodes.c
    externals/lua/loslib.c
    externals/lua/lparser.c
    externals/lua/lstate.c
    externals/lua/lstring.c
    externals/lua/lstrlib.c
    externals/lua/ltable.c
    externals/lua/ltablib.c
    externals/lua/ltm.c
    externals/lua/lua.c
    externals/lua/lundump.c
    externals/lua/lutf8lib.c
    externals/lua/lvm.c
    externals/lua/lzio.c
)

#######################################################################
#                              SOL 2                                  #
#######################################################################
set(sol2_single_header, ON)

FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG        v3.2.2
)

FetchContent_GetProperties(sol2)
if(NOT sol2_POPULATED)
    FetchContent_Populate(sol2)
    add_subdirectory(${sol2_SOURCE_DIR} ${sol2_BINARY_DIR})
endif()

#######################################################################
#                             SOURCE                                  #
#######################################################################
file(GLOB src_files
    "src/**.h"
    "src/**.cpp"

    "src/data/**.h"
    "src/data/**.cpp"

    "src/commands/**.h"
    "src/commands/**.cpp"
)

# CREATE THE EXECUTABLE
add_executable(${PROJECT_NAME}
    ${src_files}
)

# LINK THE LIBARRIES
target_link_libraries(${PROJECT_NAME}
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE TgBot
  PRIVATE cpr::cpr
  PRIVATE fmt
  PRIVATE lua
  PRIVATE sol2
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURL_LIBRARIES}
  -lstdc++fs
  -lpthread
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE externals/lua # as of sol2 3.2.2, lua.hpp must be accesible through root include '#include <lua.hpp>'
)

# MOVE THE LUA SOURCE AFTER BUILDING
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E  create_symlink ${CMAKE_SOURCE_DIR}/src/lua_commands ${CMAKE_CURRENT_BINARY_DIR}/lua_commands
)