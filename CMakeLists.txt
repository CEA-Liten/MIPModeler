# CMakeList.txt : projet CMake pour MIPModeler
cmake_minimum_required (VERSION 3.23)

# Set cmake modules directories
# (i.e. the those which contain all user-defined FindXXX.cmake files among other things)
set(CMAKE_MODULE_PATH 
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/../CMakeTools
)

# Force out-of-source build
if ("${CMAKE_SOURCE_DIR}" MATCHES "${CMAKE_BINARY_DIR}")
  message (SEND_ERROR "In source building not supported (not recommanded indeed). You need to :
    * cleanup your source directory :  \"rm -rf ./CMakeFiles/ ./CMakeCache.txt\"
    * try configure process again in a new directory
    (e.g. mkdir <anywhere>/build ; cd <anywhere>/build ; cmake ${CMAKE_SOURCE_DIR}) ...")
  return()
endif()

# If not given, turn build type to release mode.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release." FORCE)
endif()

# Some useful macros and functions
include(CMakeTools)

# cmake project name
set(PROJECT_NAME mipmodeler)

# Read user option file, if provided on command line
if(USER_OPTIONS_FILE)
  # Check for tilde in file name (not handled properly by cmake)
  string(FIND ${USER_OPTIONS_FILE} "\~" res)
  if(res EQUAL 0)
    string(REPLACE "\~" "$ENV{HOME}" USER_OPTIONS_FILE ${USER_OPTIONS_FILE})
  endif()
  if(NOT IS_ABSOLUTE ${USER_OPTIONS_FILE})
    get_filename_component(USER_OPTIONS_FILE ${USER_OPTIONS_FILE} REALPATH
      BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
  endif()
  message("\n Load user-defined options set from file ${USER_OPTIONS_FILE}\n")
  # Configure to take into account any change in ${USER_OPTIONS_FILE}
  configure_file(${USER_OPTIONS_FILE} current_options.cmake COPYONLY)
  include(${CMAKE_CURRENT_BINARY_DIR}/current_options.cmake)
else()
  message("\n Load default configuration set from file ${CMAKE_SOURCE_DIR}/cmake/default_options.cmake\n")
  include(default_options)
endif()


# ============= The project =============
# Set project name and project languages
include(ProjectSetup)
project(${PROJECT_NAME} LANGUAGES CXX C  VERSION ${PROJECT_VERSION}) 
set(CMAKE_CXX_STANDARD 11)  # Eigen 3.2.9 uses max C++11 (not compatible C++17)
set(PERSEE_APP ${CMAKE_HOME_DIRECTORY} CACHE INTERNAL "Persee application directory")

# ========= Tests setup =========
if(WITH_TESTING)  
  include(CTest)
  enable_testing()  
endif()


# Common setup
if (EXISTS ${GAMS_ROOT})
    add_subdirectory(${MIPMODELER_HOME}/GAMSModeler)
endif()
add_subdirectory(${MIPMODELER_HOME}/core)    
add_subdirectory(${MIPMODELER_HOME}/ModelerInterface)    
add_subdirectory(${MIPMODELER_HOME}/MIPSolverInterface/MIPSolver)
if (EXISTS ${CPLEX_ROOT})
    add_subdirectory(${MIPMODELER_HOME}/MIPSolverInterface/MIPCpxSolver)
endif()
if (EXISTS ${HIGHS_ROOT})       
    set(HIGHS_DIR ${HIGHS_ROOT}/${CMAKE_BUILD_TYPE}/lib/cmake/highs)
    add_subdirectory(${MIPMODELER_HOME}/MIPSolverInterface/MIPHiGHSSolver)
endif()
add_subdirectory(${MIPMODELER_HOME}/MIPSolverInterface/MIPCbcSolver)
add_subdirectory(${MIPMODELER_HOME}/MIPSolverInterface/MIPClpSolver)

# ============= Package configuration =============
# i.e. what should be generated/configured at install.
set(ConfigPackageLocation cmake)
include(PackageSetup)

# ============= Summary =============
message(STATUS "============================================ Summary ============================================")
message(STATUS "${PROJECT_NAME} version ${PROJECT_VERSION} is now ready for compilation and installation.")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ flags : ${CMAKE_CXX_FLAGS}")
message(STATUS "C Compiler : ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C flags : ${CMAKE_C_FLAGS}")
message(STATUS "Compilation mode is : ${CMAKE_BUILD_TYPE}")
message(STATUS "Code Sources are in : ${CMAKE_SOURCE_DIR}")
message(STATUS "Testing is : ${WITH_TESTING}")
message(STATUS "=================================================================================================\n")
