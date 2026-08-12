#!/bin/bash

cd ../..

source devel/setup.bash

#Launch the turtlebot world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &

# Wait for a few seconds to ensure the world is loaded
sleep 5

# Launch the gmapping demo
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &

# Wait for a few seconds to ensure gmapping is loaded
sleep 5

# Launch RViz to visualize the map
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

#ROS Run pickup objects
xterm -e "rosrun pick_objects pick_objects" &

