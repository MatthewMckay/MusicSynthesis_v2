cmake_minimum_required(VERSION 3.2)
project(MusicSynthesis_v2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
SET(BOOST_ROOT /usr/local/Cellar/boost/1.58.0)
find_package(Boost 1.58.0 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    link_directories(/usr/local/lib)
    include_directories(${Boost_INCLUDE_DIRS} /usr/local/include)
    add_library(libxerces-c.dylib SHARED IMPORTED GLOBAL)
    add_executable(MusicSynthesis_v2 ${SOURCE_FILES} XmlDomDocument_T.cpp XmlDomDocument_T.h XmlDomErrorHandler_T.cpp XmlDomErrorHandler_T.h KeySignatureDefault.h KeySignatureDefault.cpp Duration/Note.cpp Duration/Note.h Duration/Rest.cpp Duration/Rest.h Element/Measure.h Fragment.cpp Fragment.h Basis.cpp Basis.h Constants.h Duration/Duration.cpp Duration/Duration.h Processing.cpp Processing.h Duration/Chord.cpp Duration/Chord.h Duration/MeasureRest.h Duration/MultiMeasureRest_T.h Duration/MeasureSpace.h Element/Layer.h Element/Music.h Element/ScoreDefinition.h Element/Section.h Element/StaffDefinition.h Element/Staff.h Duration/TimeFraction.h)
    target_link_libraries(MusicSynthesis_v2 /usr/local/lib/libxerces-c.dylib ${Boost_FILESYSTEM_LIBRARY})
endif()

