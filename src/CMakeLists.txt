#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.4)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
#-----------------------------------------------------------------------------
if(POLICY CMP0017)
  cmake_policy(SET CMP0017 OLD)
endif()

#-----------------------------------------------------------------------------
# Module name
#   - Usually identique to the directory name)
#   - You shouldn't call 'project(...)'. See SlicerConfig.cmake for more details.
#-----------------------------------------------------------------------------
set(EXTENSION_NAME ScarSegmenter)

#-----------------------------------------------------------------------------
# Extension metadata
#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.na-mic.org/Wiki/index.php/Projects:AFibSegmentationRegistration#Registration")
set(EXTENSION_CATEGORY "Examples")
set(EXTENSION_ICONURL "http://viewvc.slicer.org/viewvc.cgi/Slicer4/trunk/Extensions/Testing/CLIExtensionTemplate/CLIExtensionTemplate.png?revision=19437&view=co")
set(EXTENSION_STATUS "Beta")
set(EXTENSION_CONTRIBUTORS "LiangJia Zhu (Georgia Tech), Yi Gao (BWH), Josh Cates (Utah), Alan Morris (Utah), Danny Perry (Utah), Greg Gardner (Utah), Rob MacLeod (Utah), Allen Tannenbaum (Boston Univ) ")
set(EXTENSION_DESCRIPTION "This is an module performing the scar segmentation")
set(EXTENSION_SCREENSHOTURLS "http://www.na-mic.org/Wiki/images/2/28/AFibLongitudinalRegistration-txt.png")
set(EXTENSION_ACKNOWLEDGEMENTS "This work was supported by Na-mic, NAC, ...")
set(EXTENSION_MAJOR_VERSION 0)
set(EXTENSION_MINOR_VERSION 1)
set(EXTENSION_PATCH_VERSION 0)


#-----------------------------------------------------------------------------
# Prerequisites
#-----------------------------------------------------------------------------
if(NOT Slicer_SOURCE_DIR)
  find_package(Slicer REQUIRED)

  # Additional C/CXX flags - Should be defined before including Slicer_USE_FILE
  #set(ADDITIONAL_C_FLAGS "" CACHE STRING "Additional ${EXTENSION_NAME} C Flags")
  #set(ADDITIONAL_CXX_FLAGS "" CACHE STRING "Additional ${EXTENSION_NAME} CXX Flags")

  include(${Slicer_USE_FILE})

  set(EXTENSION_DEPENDS NA) # Specified as a space separated list or 'NA' if any
  set(EXTENSION_LICENSE_FILE ${Slicer_LICENSE_FILE})
  set(EXTENSION_README_FILE ${Slicer_README_FILE})
  set(EXTENSION_LICENSE_SHORT_DESCRIPTION ${Slicer_LICENSE_SHORT_DESCRIPTION})

  #include(SlicerEnableExtensionTesting)
endif()

# Configure XML description
configure_file(
  ${EXTENSION_NAME}.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/${EXTENSION_NAME}.xml
  @ONLY
  )

# Configure XML description
configure_file(
  WallSegmenter.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/WallSegmenter.xml
  @ONLY
  )

# Configure XML description
configure_file(
  WallAndScarSegmenter.xml.in
  ${CMAKE_CURRENT_BINARY_DIR}/WallAndScarSegmenter.xml
  @ONLY
  )

# Add module sub libraries
set(cli_module_export_directive "Q_SLICER_QTMODULES_LOADABLEEXTENSIONTEMPLATE_EXPORT")

# Additional includes
#set(cli_module_include_directories)

# Additional source files
#set(cli_module_SRCS)

# Additional Target libraries
set(cli_module_target_libraries ${ITK_LIBRARIES})


# I added these for local headers and libs. (LiangJia Zhu)
#set(headerAndLibDir
#    ${PROJECT_SOURCE_DIR}
#    ${PROJECT_SOURCE_DIR}/lib)
#
#include_directories(${headerAndLibDir})
# I added these for local headers and libs. (LiangJia Zhu). done


#-----------------------------------------------------------------------------
# Build
#-----------------------------------------------------------------------------
slicerMacroBuildCLI(
  NAME ${EXTENSION_NAME}
  #LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${cli_module_target_libraries}
  ADDITIONAL_SRCS
    SFLS.h
    SFLSSegmentor3D.h
    SFLSSegmentor3D.txx
    utilities.hxx
    wallSegmenter3D.h
    wallSegmenter3D.txx
    localChanVeseWallSegmenter3D.h
    localChanVeseWallSegmenter3D.txx
  #INCLUDE_DIRECTORIES ${cli_module_include_directories}
  ADDITIONAL_SRCS ${cli_module_SRCS}
  #EXECUTABLE_ONLY
  )

slicerMacroBuildCLI(
  NAME WallSegmenter
  #LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${cli_module_target_libraries}
  #INCLUDE_DIRECTORIES ${cli_module_include_directories}
  ADDITIONAL_SRCS ${cli_module_SRCS}
  #EXECUTABLE_ONLY
  )

slicerMacroBuildCLI(
  NAME WallAndScarSegmenter
  #LOGO_HEADER ${Slicer_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${cli_module_target_libraries}
  #INCLUDE_DIRECTORIES ${cli_module_include_directories}
  ADDITIONAL_SRCS ${cli_module_SRCS}
  #EXECUTABLE_ONLY
  )

# #-----------------------------------------------------------------------------
# # Testing
# #-----------------------------------------------------------------------------
# if(BUILD_TESTING)
#   add_subdirectory(Testing)
# endif()

#-----------------------------------------------------------------------------
# Generate extension description file '<EXTENSION_NAME>.s4ext'
#-----------------------------------------------------------------------------
#if(NOT Slicer_SOURCE_DIR)
#  include(SlicerFunctionGenerateExtensionDescription)
#  slicerFunctionGenerateExtensionDescription(
#    EXTENSION_NAME ${EXTENSION_NAME}
#    EXTENSION_CATEGORY ${EXTENSION_CATEGORY}
#    EXTENSION_ICONURL ${EXTENSION_ICONURL}
#    EXTENSION_STATUS ${EXTENSION_STATUS}
#   EXTENSION_HOMEPAGE ${EXTENSION_HOMEPAGE}
#    EXTENSION_CONTRIBUTORS ${EXTENSION_CONTRIBUTORS}
#    EXTENSION_DESCRIPTION ${EXTENSION_DESCRIPTION}
#    EXTENSION_SCREENSHOTURLS ${EXTENSION_SCREENSHOTURLS}
#   EXTENSION_DEPENDS ${EXTENSION_DEPENDS}
#    DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR}
#    SLICER_WC_REVISION ${Slicer_WC_REVISION}
#    SLICER_WC_ROOT ${Slicer_WC_ROOT}
#    )
#endif()

# #-----------------------------------------------------------------------------
# # Packaging
# #-----------------------------------------------------------------------------
# if(NOT Slicer_SOURCE_DIR)
#   include(${Slicer_EXTENSION_CPACK})
# endif()

