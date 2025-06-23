#================================================================
# cmake utilities to build MIPModeler component
#================================================================
#
# The objective is to call component_setup to create the target <COMPONENT>.
# Before, it's necessary to set:
# 
# - COMPONENT component name
# - <COMPONENT>_DIRS: the list of paths (relative to CMAKE_CURRENT_SOURCE_DIR) that
#   contain source files
# - <COMPONENT>_EXCLUDE_SRCS: the list of files, in <COMPONENT>_DIRS, that must be excluded
#   from build.
# - <COMPONENT>_INTERFACE_INCLUDE_DIRECTORIES: a list of directories
#   to populate the interface of the target for include directories at build time

# Component name (i.e. target name)
set(COMPONENT MIPModeler)
message("-- Set up for ${PROJECT_NAME}_${COMPONENT} library ...\n")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MIPModelerVersion.in ${CMAKE_CURRENT_SOURCE_DIR}/MIPModelerVersion.h @ONLY)
# ------ source directories for current component ------
# What is needed by component to compile ?
# List here all directories that contain sources files for current component.
# Path must be relative to component path (i.e. to CMAKE_CURRENT_SOURCE_DIR)
set(${COMPONENT}_DIRS
 . 
)

# ------ include interface ------
set(${COMPONENT}_INTERFACE_INCLUDE_DIRECTORIES 
    .
    ../ModelerInterface    
)

# -- create/setup component target --
include(ComponentSetup)
create_component(${COMPONENT})

find_package(Qt REQUIRED Core)
if (${USE_GAMS})
    target_link_libraries(${COMPONENT} PRIVATE GAMSModeler)
    target_compile_definitions(${COMPONENT} PRIVATE -DUSE_GAMS)
    find_package(GAMS)
endif()

# -- Eigen to MIPModeler
include(EigenSetup)
target_link_libraries(${COMPONENT} PRIVATE Eigen3::Eigen)

target_link_libraries(${COMPONENT} PRIVATE ModelerInterface)

# ---- Installation ----
# Call component_install_setup(<COMPONENT>)
# to prepare installation of the current target.
#
# Before, it's necessary to set:
# 
# - <COMPONENT>_INSTALL_INTERFACE_INCLUDE_DIRECTORIES with all directories
#    that contain headers files that must be installed.
# 
set(${COMPONENT}_INSTALL_INTERFACE_INCLUDE_DIRECTORIES
  ${${COMPONENT}_DIRS} # All .h are installed
  )

# List header files (in dir above) that must not be installed 
#set(${COMPONENT}_HDRS_EXCLUDE)

component_install_setup(${COMPONENT})



#if(WITH_TESTING)	
#	include(CTestTools)	
	#add_tests(${MIPMODELER_HOME}/test/testTransport 	
	#DEPS MIPModeler)	
#endif()
