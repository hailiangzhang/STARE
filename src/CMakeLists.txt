set (
  STARE_SrcFiles
  ${STARE_SrcFiles}
  BitShiftNameEncoding.C
  EmbeddedLevelNameEncoding.C
  HtmRange.cpp
  HtmRangeIterator.cpp
  HtmRangeMultiLevel.cpp
  HtmRangeMultiLevelIterator.cpp
  Htmio.cpp
  HstmRange.C
  NameEncoding.C
  RangeConvex.cpp
  SkipList.cpp
  SkipListElement.cpp
  SpatialConstraint.cpp
  SpatialDomain.cpp
  SpatialEdge.cpp
  SpatialException.cpp
  SpatialGeneral.C
  SpatialIndex.cpp
  SpatialInterface.cpp
  SpatiallyAdaptiveDataCover.C
  SpatialVector.cpp
  SpatialRotation.C
  STARE.C
  TemporalIndex.cpp
  VarStr.C )

# TODO Trouble with VarStr.hpp# TODO Trouble with VarStr.hpp
# Var.Str.C is a kluge because I don't know how to get CMake to handle the hpp files correctly.
# INTERFACE May be what works: http://stackoverflow.com/questions/5957134/how-to-setup-cmake-to-generate-header-only-projects

add_library( STARE STATIC ${STARE_SrcFiles} )

# Configure the location of directories needed by Boost to compile

if (DEFINED ENV{BOOST_INCLUDEDIR})
  SET (BOOST_INCLUDEDIR $ENV{BOOST_INCLUDEDIR})
  message("BOOST_INCLUDEDIR is $ENV{BOOST_INCLUDEDIR}")
endif()

if (DEFINED ENV{BOOST_LIBRARYDIR})
  SET (BOOST_LIBRARYDIR $ENV{BOOST_LIBRARYDIR})
  message("BOOST_LIBRARYDIR is $ENV{BOOST_LIBRARYDIR}")
endif()

if (DEFINED ENV{Python_LIBRARY_DIR})
  SET (Python_LIBRARY_DIR $ENV{Python_LIBRARY_DIR})
  message("Python_LIBRARY_DIR is $ENV{Python_LIBRARY_DIR}")
else()
  SET (Python_LIBRARY_DIR "/usr/lib/python3.6/site-packages")
endif()

if (DEFINED ENV{BOOST_PYTHON_INCLUDE_DIR})
  SET (BOOST_PYTHON_INCLUDE_DIR $ENV{BOOST_PYTHON_INCLUDE_DIR})
  message("BOOST_PYTHON_INCLUDE_DIR is $ENV{BOOST_PYTHON_INCLUDE_DIR}")
else()
  SET (BOOST_PYTHON_INCLUDE_DIR "/usr/include/python3.6m")
endif()


find_package(Boost)
if(Boost_FOUND)
  message("Boost found.")
  include_directories( "${Boost_INCLUDE_DIRS}" ${BOOST_PYTHON_INCLUDE_DIR}  )
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME OFF)
  find_package(Boost COMPONENTS python3 COMPONENTS numpy3 REQUIRED)

  set( STARE_PYTHON_SrcFiles
        PySTARE.cpp
  )
  add_library( PySTARE SHARED ${STARE_SrcFiles} ${STARE_PYTHON_SrcFiles} )
  set_target_properties( PySTARE PROPERTIES PREFIX "" )
  target_link_libraries( PySTARE ${Boost_LIBRARIES} )
  install(TARGETS PySTARE DESTINATION ${Python_LIBRARY_DIR} )
else()
  message("Boost not found, not creating shared object PySTARE, including python API. Was BOOST_ROOT set?")
endif()