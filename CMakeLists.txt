cmake_minimum_required (VERSION 3.10.0)

project(TranslucentMPlayer)
									  
cmake_policy(SET CMP0020 OLD)

# Version Number
set (TRANSLUCENTMPLAYER_VERSION_MAJOR 1)
set (TRANSLUCENTMPLAYER_VERSION_MINOR 4)
set (TRANSLUCENTMPLAYER_VERSION_PATCH 0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt6 COMPONENTS Widgets Multimedia)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Multimedia_EXECUTABLE_COMPILE_FLAGS}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CORE_EXTERNAL_LIBS ${CORE_EXTERNAL_LIBS} ${QT_QTTEST_LIBRARY})
endif (CMAKE_BUILD_TYPE MATCHES Debug)

if(DEFINED MINGW)
  configure_file("${PROJECT_SOURCE_DIR}/resources.rc.in" "${PROJECT_BINARY_DIR}/resources.rc")
  configure_file("${PROJECT_SOURCE_DIR}/installer/script.iss.in" "${PROJECT_BINARY_DIR}/script.iss")
  set(CORE_SOURCES ${CORE_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)
  set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -o <OBJECT> -i <SOURCE>")
  enable_language(RC)
endif(DEFINED MINGW)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}          # Generated .h files
  ${CMAKE_CURRENT_BINARY_DIR}  # For wrap/ui files
  ${Qt6Widgets_INCLUDE_DIRS}
  ${Qt6Multimedia_INCLUDE_DIRS}
  )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated -std=c++17 -mwindows")

# Add Qt Resource files
qt6_add_resources(RESOURCES
  rsc/resources.qrc
)

qt6_wrap_ui(CORE_UI
  # .ui for Qt
  ConfigurationDialog.ui
  AboutDialog.ui
  VideoConfigurationDialog.ui
)
	
set (CORE_SOURCES
  # project files
  ${CORE_SOURCES}
  ${RESOURCES}
  ${CORE_MOC}
  ${CORE_UI}
  Main.cpp
  ConfigurationDialog.cpp
  TranslucentMPlayer.cpp
  AboutDialog.cpp
  DesktopWidget.cpp
  PlayerManager.cpp
  VideoConfigurationDialog.cpp
  VolumeWidgetAction.cpp
  ProgressWidgetAction.cpp
  Utils.cpp
)

set(CORE_EXTERNAL_LIBS
  Qt6::Widgets
  Qt6::Multimedia
)
  
add_executable(TranslucentMPlayer ${CORE_SOURCES})
target_link_libraries (TranslucentMPlayer ${CORE_EXTERNAL_LIBS})
