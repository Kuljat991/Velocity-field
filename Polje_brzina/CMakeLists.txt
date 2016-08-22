project(poljeBrzina)
cmake_minimum_required(VERSION 3.0)


if(UNIX)
    message(STATUS "this is unix")
     if(CMAKE_COMPILER_IS_GNUCXX)
         message(STATUS "this is GCC")
         add_compile_options(-std=c++11)
         add_compile_options(-Wall)
         add_compile_options(-Wextra)
         add_compile_options(-pedantic)
      endif()
elseif(WINDOWS)
    if(MSVC)
        set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} /SUBSYSTEM:WINDOWS /W4")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    elseif(MINGW)
        add_compile_options(-std=c++11)
        add_compile_options(-Wall)
        add_compile_options(-Wextra)
        add_compile_options(-pedantic)
    else()
        message(ERROR "(Not MSVC or GCC)")
    endif()
    # set_target_properties(name_of_my_project PROPERTIES COMPILER_FLAGS "/EHsc")
    message(STATUS "this is windows")
endif()

#### 
# results folder
set(RESULTS_TEMPDATA "${PROJECT_SOURCE_DIR}/../results" CACHE PATH "Location of externals")
get_filename_component(RESULTS_FOLDER ${RESULTS_TEMPDATA} REALPATH)

configure_file (
  "${PROJECT_SOURCE_DIR}/pathconfig.h.in"
  "${PROJECT_BINARY_DIR}/pathconfig.h"
  )
include_directories(${PROJECT_BINARY_DIR})

find_package(Qt5Core)
set(CMAKE_AUTOMOC ON)

find_package(Boost 1.55 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(p01 WIN32 p01.cpp velocity_functions.cpp utility.h ThreadPoint.cpp)
set_property(TARGET p01 PROPERTY CXX_STANDARD 11)
target_link_libraries(p01 Qt5::Core ${Boost_LIBRARIES})
qt5_use_modules( p01 Core)

add_executable(p02 WIN32 p02.cpp velocity_functions.cpp utility.h ThreadPoint.cpp)
set_property(TARGET p02 PROPERTY CXX_STANDARD 11)
target_link_libraries(p02 Qt5::Core ${Boost_LIBRARIES})

qt5_use_modules( p02 Core)

