cmake_minimum_required(VERSION 3.10)

project(SpaceBreakers
  VERSION 1.0.0
  LANGUAGES CXX
)

set(source_files
  src/Game.cpp
  src/Game_controls.cpp
  src/Game_rendering.cpp
  src/Timer.cpp
  src/entities/Invader.cpp
  src/entities/InvaderGroup.cpp
  src/entities/Player.cpp
  src/entities/Projectile.cpp
  src/main.cpp
)

add_executable(${PROJECT_NAME}
  ${source_files}
)

target_include_directories(${PROJECT_NAME} PRIVATE include /usr/include/SDL2)

find_package(SDL2 REQUIRED)

target_compile_features(${PROJECT_NAME}
  PRIVATE cxx_std_11
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE SDL2 SDL2_mixer SDL2_ttf
)

#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------

include(GNUInstallDirs)

# Targets

get_property(variables DIRECTORY "${CMAKE_CURRENT_LISTS_DIR}" PROPERTY VARIABLES)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION "${PROJECT_NAME}"
)
install(
  DIRECTORY "assets"
  DESTINATION "${PROJECT_NAME}"
)
install(
  FILES LICENSE
  DESTINATION "${PROJECT_NAME}"
)

#-------------------------------------------------------------------------------
# Package
#-------------------------------------------------------------------------------
set(CPACK_GENERATOR "DEB;STGZ;TGZ;TZ")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A small and simple SDL2 crossover")
set(CPACK_PACKAGE_VENDOR "Matthew Rodusek")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_LIST_DIR}/README.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_LIST_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/LICENSE")

# Debian
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Matthew Rodusek")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-2.0.0" "libsdl2-mixer" "libsdl2-ttf")

set(CPACK_STRIP_FILES "${PROJECT_NAME}/${PROJECT_NAME}")
set(CPACK_SOURCE_STRIP_FILES "")
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}/${PROJECT_NAME}")


include(CPack)
