cmake_minimum_required(VERSION 3.11.4 FATAL_ERROR)

# Project Name
set(PROJECT_NAME "crypto_bot")
project(${PROJECT_NAME})

# USEFULL PATHS AND DEFINITIONS
set(TELEGRAM_LIB ${PROJECT_SOURCE_DIR}/externals/tgbot-cpp)
set(JSON_LIB ${PROJECT_SOURCE_DIR}/externals/json)
set(SRC_PATH ${CMAKE_SOURCE_DIR}/src)

# CPP 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(Boost_USE_MULTITHREADED ON)

# JSON LIB
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${JSON_LIB})

# WEB REQUEST LIB
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

# INCLUDE DIRECTORIES
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${TELEGRAM_LIB}/include)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

# FMT Library
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
  

# ADD ALL THE SOURCE AND HEADERS
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
  PRIVATE cpr::cpr /usr/local/lib/libTgBot.a
  PRIVATE fmt
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURL_LIBRARIES}
  -lstdc++fs
)

