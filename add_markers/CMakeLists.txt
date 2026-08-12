cmake_minimum_required(VERSION 3.0.2)
project(add_markers)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  actionlib
  std_msgs
  geometry_msgs
  move_base_msgs
  visualization_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(add_markers src/add_markers.cpp)
target_link_libraries(add_markers ${catkin_LIBRARIES})
add_dependencies(add_markers ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

