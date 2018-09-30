# thanks to: https://github.com/Hopson97/SFML-Game-Framework/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.8.2)
project(skeleton)

# configure optimization
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIMIZATION_FLAGS "-O0 -fsanitize=undefined")
    set(IS_DEBUG true)
    message("-- Configuring debug build")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPTIMIZATION_FLAGS "-O3")
    set(IS_DEBUG false)
    message("-- Configuring release build")
endif()

set(CMAKE_CXX_STANDARD 14)

# check if clang or gcc
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang$")
    set(CXX_COMPILER_IS_GNU_OR_CLANG true)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(CXX_COMPILER_IS_GNU_OR_CLANG true)
endif()
if ("${CMAKE_CC_COMPILER_ID}" STREQUAL "Clang")
    set(CC_COMPILER_IS_GNU_OR_CLANG true)
elseif (CMAKE_COMPILER_IS_GNUCC)
    set(CC_COMPILER_IS_GNU_OR_CLANG true)
endif()

# setup compiler flags
if(CC_COMPILER_IS_GNU_OR_CLANG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTIMIZATION_FLAGS}")
endif()
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    endif()
elseif(CXX_COMPILER_IS_GNU_OR_CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Werror")
    # optional: -pedantic -Wconversion -Wall -Wextra
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS}")
    # optional: -march=native (builds with the optimizations available on the build machine (only for local use!))
else()
    message(WARNING "Configuring for unsupported compiler ${CMAKE_CXX_COMPILER_ID}.")
endif()

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(skeleton ${SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED graphics window system audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(skeleton  ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
else()
    message(WARNING "Can't locate SFML.")
endif()

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
