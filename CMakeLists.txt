cmake_minimum_required(VERSION 3.0.0)
project(osgdemo)

find_package(OpenSceneGraph 3.0.0 REQUIRED osg osgViewer osgWidget osgDB
 osgUtil)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

add_executable(osgdemo osgdemo.cpp)
target_link_libraries(osgdemo ${OPENSCENEGRAPH_LIBRARIES})

add_executable(cg3test cg3test.cpp)
target_link_libraries(cg3test ${OPENSCENEGRAPH_LIBRARIES})
