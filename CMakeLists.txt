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
    add_executable(MusicSynthesis_v2 ${SOURCE_FILES} XmlDomDocument.cpp XmlDomDocument.h XmlDomErrorHandler.cpp XmlDomErrorHandler.h Note.cpp Note.h Rest.cpp Rest.h Measure.cpp Measure.h Fragment.cpp Fragment.h Basis.cpp Basis.h Type.cpp Type.h RBTree.h)
    target_link_libraries(MusicSynthesis_v2 /usr/local/lib/libxerces-c.dylib ${Boost_FILESYSTEM_LIBRARY})
endif()

