#!/bin/bash

cd ../../..

source devel/setup.bash

#Launch the home_service robot world
xterm -e "roslaunch home_service world.launch" &

# Wait for a few seconds to ensure the world is loaded
sleep 7

# Launch the gmapping demo
xterm -e "roslaunch home_service amcl.launch" &

# Wait for a few seconds to ensure gmapping is loaded
sleep 7

# Launch RViz to visualize the map
xterm -e "roslaunch home_service view_navigation.launch" &

sleep 7

#ROS Run pickup objects
xterm -e "rosrun add_markers add_markers" &

sleep 5

#ROS Run pickup objects
xterm -e "rosrun pick_objects pick_objects" &



