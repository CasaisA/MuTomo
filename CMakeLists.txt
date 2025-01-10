# Setup the project
cmake_minimum_required(VERSION 2.8.12)
project(MuTomo)

# Find Geant4 package
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Locate sources and headers for this project
MESSAGE( STATUS "Geant4_INCLUDE_DIR:         " ${Geant4_INCLUDE_DIR} )
# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
# Add the executable             
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB data ${PROJECT_SOURCE_DIR}/data/*.dat)

foreach(_data_file ${data})
  file(COPY ${_data_file} DESTINATION ${PROJECT_BINARY_DIR})
endforeach()

add_executable(MuTomo MuTomo.cc ${sources} ${headers})

# Link the executable with Geant4 libraries
target_link_libraries(MuTomo ${Geant4_LIBRARIES})

# Copy any Runtime Scripts to the Build Directory
set(EXAMPLEB1_SCRIPTS
  run.mac
)

foreach(_script ${EXAMPLEB1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()
