cmake_minimum_required(VERSION 3.4)

set (
  TestSrcFiles
  Test.cpp
  SpatialFailure_test.cpp
  SpatialIndex_test.cpp
  SpatialRotation_test.cpp
  SpatialVector_test.cpp
  STARE_test.cpp
  Test.h 
  )

# SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -I${PROJECT_SOURCE_DIR}/include" )

add_executable(tests ${TestSrcFiles})
target_link_libraries(tests STARE)
target_include_directories(tests PUBLIC ${CUTE_INCLUDE_DIR}/cute)

