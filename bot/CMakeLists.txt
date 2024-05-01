cmake_minimum_required(VERSION 3.20)
project(McConnectBot)

set(CMAKE_CXX_STANDARD 23)
set(BOTCRAFT_GAME_VERSION 1.12.2)
set(BOTCRAFT_BUILD_DOC OFF)
#set(BOTCRAFT_OUTPUT_DIR "/home/astatin3/Documents/GitHub/meteorbot/bot/bin/")

add_executable(McConnectBot main.cpp
        CommandClient.cpp
        CommandClient.h)

add_subdirectory(external/Botcraft)

# Find packages
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Link libraries statically (except OpenSSL)
#set(Boost_USE_STATIC_LIBS ON)
#find_package(Boost REQUIRED COMPONENTS system filesystem)

target_link_libraries(McConnectBot PRIVATE
        # Removed paths to static OpenSSL libraries
        botcraft
)

# Set output directory to place the binary
set_target_properties(McConnectBot PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin"
)
