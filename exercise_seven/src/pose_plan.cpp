#include <iostream>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char **argv){
  ros::init(argc, argv, "pose_plan");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  // 创建对象arm连接到xarm规划组
  moveit::planning_interface::MoveGroupInterface arm("xarm");
  // 获取xarm规划组的规划参考坐标系
  std::string planning_frame = arm.getPlanningFrame();
  ROS_INFO_STREAM("Planning frame : "<< planning_frame);
  // 获取末端执行器的link
  std::string eef_link = arm.getEndEffectorLink();
  ROS_INFO_STREAM("End effector link : "<< eef_link);
  // 若allow_replanning()参数为True，则MoveIt!在一次规划失败后进行重新规划
  arm.allowReplanning(true);
  // 设置运动到目标时的位置(单位：米)和姿态的容忍误差(单位：弧度)
  arm.setGoalPositionTolerance(0.02);
  arm.setGoalOrientationTolerance(0.03);
  // 设置一个比例因子以选择性地降低最大关节速度限制，可取值为(0,1]
  arm.setMaxVelocityScalingFactor(0.8);
  // 使用geometry_msgs/PoseStamped消息类型设置机械臂的目标位姿
  geometry_msgs::PoseStamped target_pose;
  target_pose.header.frame_id = planning_frame;
  target_pose.header.stamp = ros::Time::now();
  target_pose.pose.position.x = 0.3;
  target_pose.pose.position.y = -0.3;
  target_pose.pose.position.z = 0.3;
  tf2::Quaternion quaternion;
  quaternion.setRPY(0, 0,-3.1415926/4.0);
  target_pose.pose.orientation.x = quaternion.x();
  target_pose.pose.orientation.y = quaternion.y();
  target_pose.pose.orientation.z = quaternion.z();
  target_pose.pose.orientation.w = quaternion.w();
  // 显示地把开始状态设置为机械臂的当前状态
  arm.setStartStateToCurrentState();
  ROS_INFO("Moving to target_pose ...");
  // 设置目标位姿
  arm.setPoseTarget(target_pose);
  // 使用plan()进行运动规划
  moveit::planning_interface::MoveGroupInterface::Plan plan;
  bool success = (arm.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("moveit_pose_demo", "Visualizing plan 1 (joint space goal) %s", success ? "" : "FAILED");
  // 若规划成功,则使用execute()执行规划出的轨迹
  if(success){
    arm.execute(plan);
  }
  // 获取末端执行器当前的位姿
  geometry_msgs::PoseStamped current_pose = arm.getCurrentPose();

  // 设定新的目标
  ROS_INFO("Moveing to joint-space goal: joint_positions");

  std::vector<double> arm_joint_positions = {-0.9, -1.0, 0.2, 0.9,-0.76, 1.5};
  arm.setJointValueTarget(arm_joint_positions);
  arm.move();

  ROS_INFO("Moving to pose: Home");
  arm.setNamedTarget("Home");
  arm.move();
  ros::shutdown();
  return 0;
}

