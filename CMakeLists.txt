cmake_minimum_required(VERSION 2.8)

include("./gate/cmake/HunterGate.cmake")
HunterGate(
	URL  "https://github.com/designerror/hunter/archive/v0.18.4.20.tar.gz"
	SHA1 "94e3314bfe952db1510ca644d2a8e0b55e9ebc8b"
)

project(yadisk-subtract)

set(SUBTRACT_MAJOR 0)
set(SUBTRACT_VERSION_MINOR 1)
set(SUBTRACT_VERSION_PATCH 0)
set(SUBTRACT_VERSION ${SUBTRACT_VERSION_MAJOR}.${SUBTRACT_VERSION_MINOR}.${SUBTRACT_VERSION_PATCH})
set(SUBTRACT_VERSION_STRING "v${SUBTRACT_VERSION}")
SET(PROJECT_NAME "yadisk-subtract")

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

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	Boost::filesystem Boost::system
	OpenSSL::SSL OpenSSL::Crypto
	CURL::libcurl
	nlohmann-json::nlohmann-json
)
