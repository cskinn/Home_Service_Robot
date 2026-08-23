#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// This will be a function that would get called twice in the main. First for the pickup goal, Second for the dropoff goal.
bool setMoveGoal(MoveBaseClient & ac, double x, double y, double w) {
  // Stating the first goal which is the pick up location
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  // Define a position (x,y) and orientation (w) for the robot to reach - these are args in the function 
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w; // w is the orientation


  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, goal reached!");
  else
    ROS_INFO("Failed to reach goal");

  return ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;


}

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  // stating the pickup and dropoff
  double pickup[2] = {4.0, 1.0};
  double dropoff[2] = {4.0, 4.0};

  ROS_INFO("Initiallizing navigation to pick-up & drop-off zones.."); 

  // Tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5s for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
  ROS_INFO("Waiting for the move_base action server to come up");
  }

  // Set pickup goal
  ROS_INFO("Setting the pickup location...");
  
  if (setMoveGoal(ac, pickup[0], pickup[1], 1.0)) {
  ROS_INFO("Arrived at pickup zone");
  } else {
  ROS_INFO("Failed to reach pickup zone");
  }

  // sleep before next command
  ros::Duration(5.0).sleep();

  // Set return goal
  ROS_INFO("Setting the return location...");

 
  if (setMoveGoal(ac, dropoff[0], dropoff[1], 1.0)) {
  ROS_INFO("Arrived at drop-off zone");
  } else {
  ROS_INFO("Failed to reach drop-off zone");
  }

  return 0;
}
