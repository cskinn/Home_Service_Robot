#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include "nav_msgs/Odometry.h"
#include <cmath>


// https://wiki.ros.org/rviz/Tutorials/Markers%3A%20Basic%20Shapes#CA-22105266306fcac63921558ac2a46a5435d4d2f8_45 was used as a reference

ros::Publisher marker_pub;

// stating the pickup and dropoff
double pickup[2] = {4.0, 1.0};
double dropoff[2] = {3.0, -3.0};
double robo_x = 0.0;
double robo_y = 0.0;
bool picked_up = false;
bool dropped_off = false;

void robot_pose(const nav_msgs::Odometry::ConstPtr& msg) {
    // Extract the position and orientation from the odometry message
    robo_x = msg->pose.pose.position.x;
    robo_y = msg->pose.pose.position.y;

}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber odom_sub = n.subscribe("/odom", 10, robot_pose);


    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    while (ros::ok()){
        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        marker.ns = "basic_shapes";
        marker.id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        marker.type = shape;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        //marker.action = visualization_msgs::Marker::ADD;


        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        // initally set at the pickup location
        marker.pose.position.x = pickup[0];
        marker.pose.position.y = pickup[1];
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = 1.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        
        marker.lifetime = ros::Duration();


        ros::spinOnce();

	double pickup_dist = sqrt(pow(robo_x - pickup[0], 2) + pow(robo_y - pickup[1], 2));
	double dropoff_dist = sqrt(pow(robo_x - dropoff[0], 2) + pow(robo_y - dropoff[1], 2));
	// Below was use to test how close the robot was getting to pickup and dropoff for tuning
	//ROS_INFO("pickup_dist: %.2f, dropoff_dist: %.2f", pickup_dist, dropoff_dist);

        

	if (!picked_up && pickup_dist >= 0.75) {
	    marker.action = visualization_msgs::Marker::ADD;
	    marker.pose.position.x = pickup[0];
	    marker.pose.position.y = pickup[1];
	    marker_pub.publish(marker);
	}
	if (!picked_up && pickup_dist < 0.75) {
	    marker.action = visualization_msgs::Marker::DELETE;
	    marker_pub.publish(marker);
	    picked_up = true;
	    sleep(5);
	}
	if (picked_up && !dropped_off && dropoff_dist < 0.8) {
	    marker.action = visualization_msgs::Marker::ADD;
	    marker.pose.position.x = dropoff[0];
	    marker.pose.position.y = dropoff[1];
	    marker_pub.publish(marker);
	    dropped_off = true;
	}



    }
}
