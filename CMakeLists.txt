cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/HunterGate.cmake)
HunterGate(
    URL  "https://github.com/yadisk-ops/hunter/archive/v0.18.47.2.tar.gz"
    SHA1 "fe0f3a4d337ae08dbea640fd1ebc1e448919fcd3"
    LOCAL
)

project(yadisk-subtract) # this command set PROJECT_NAME to "yadisk-subtract"

set(SUBTRACT_VERSION_MAJOR 0)
set(SUBTRACT_VERSION_MINOR 1)
set(SUBTRACT_VERSION_PATCH 0)
set(SUBTRACT_VERSION ${SUBTRACT_VERSION_MAJOR}.${SUBTRACT_VERSION_MINOR}.${SUBTRACT_VERSION_PATCH})
set(SUBTRACT_VERSION_STRING "v${SUBTRACT_VERSION}")
#SET(PROJECT_NAME "yadisk-subtract")

option(BUILD_TESTS "Build tests" ON)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

hunter_add_package(nlohmann-json)
find_package(nlohmann-json REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*)

add_library(${PROJECT_NAME} ${SOURCES}) # static or shared depends on value BUILD_SHARED_LIBS variable

target_link_libraries(${PROJECT_NAME}
	Boost::filesystem Boost::system
	OpenSSL::SSL OpenSSL::Crypto
	CURL::libcurl
	nlohmann-json::nlohmann-json
)


if(BUILD_TESTS)
enable_testing()
hunter_add_package(Catch)
find_package(Catch CONFIG REQUIRED)
file(GLOB TESTS_${PROJECT_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*/*.cpp)
add_executable(check ${TESTS_${PROJECT_NAME}_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)
target_link_libraries(check ${PROJECT_NAME} Catch::Catch)
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes")
endif()

include(CPackConfig.cmake)
