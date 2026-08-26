#!/bin/bash

cd ../../..

source devel/setup.bash

#Launch the turtlebot world
xterm -e "roslaunch home_service world.launch" &

# Wait for a few seconds to ensure the world is loaded
sleep 5

# Launch the gmapping demo
xterm -e "roslaunch home_service amcl.launch" &

# Wait for a few seconds to ensure gmapping is loaded
sleep 5

# Launch RViz to visualize the map
xterm -e "roslaunch home_service view_navigation.launch" &
