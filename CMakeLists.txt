cmake_minimum_required( VERSION 3.25 )

if(DEFINED CMAKE_OSX_SYSROOT AND NOT EXISTS "${CMAKE_OSX_SYSROOT}")
  unset(CMAKE_OSX_SYSROOT CACHE)
endif()

message( STATUS "Parallel Programming Course (PPC)" )
project(parallel_programming_course)

############################ Scoreboard #############################

message( STATUS "PPC step: Setup scoreboard generator" )
include(cmake/scoreboard.cmake)
add_subdirectory(scoreboard)

########################### Documentation ###########################

message( STATUS "PPC step: Setup documentation generation" )
include(cmake/sphinx.cmake)
add_subdirectory(docs)

if( USE_SCOREBOARD OR USE_DOCS )
    return()
endif()

############################ Configures #############################

message( STATUS "PPC step: First configures" )
include(cmake/configure.cmake)
include(cmake/modes.cmake)
include(cmake/sanitizers.cmake)

################# Parallel programming technologies #################

message( STATUS "PPC step: Setup parallel programming technologies" )
include(cmake/mpi.cmake)
include(cmake/openmp.cmake)
include(cmake/onetbb.cmake)

######################### External projects #########################

message( STATUS "PPC step: Setup external projects" )
include(cmake/gtest.cmake)

############################## Headers ##############################

message( STATUS "PPC step: Setup headers" )
include_directories(3rdparty)
include_directories(modules)
include_directories(tasks)

############################## Modules ##############################

message( STATUS "PPC step: Setup modules" )
add_subdirectory(modules)
add_subdirectory(tasks)
