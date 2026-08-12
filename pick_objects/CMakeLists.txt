cmake_minimum_required(VERSION 3.0.2)
project(pick_objects)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  actionlib
  std_msgs
  geometry_msgs
  move_base_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(pick_objects src/pick_objects.cpp)
target_link_libraries(pick_objects ${catkin_LIBRARIES})
add_dependencies(pick_objects ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

