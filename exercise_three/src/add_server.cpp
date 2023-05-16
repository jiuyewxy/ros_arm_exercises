#include "ros/ros.h"
#include "exercise_three/CallAdd.h"
// 服务回调函数,req为服务的请求,res为服务的应答
bool add(exercise_three::CallAdd::Request &req, exercise_three::CallAdd::Response &res){
  res.sum = req.addend.x+req.addend.y+req.addend.z;
  ROS_INFO("request: x=%f,y=%f,z=%f",req.addend.x, req.addend.y, req.addend.z);
  ROS_INFO("sending back response: %f",res.sum);
  return true;
}

int main(int argc, char **argv){
  // 初始化ROS节点
  ros::init(argc, argv, "add_server");
  // 创建一个节点句柄（NodeHandle）对象nh
  ros::NodeHandle nh;
  // 创建add_three服务的服务端对象service,服务回调函数add
  ros::ServiceServer service = nh.advertiseService("call_add", add);
  ROS_INFO("add_server is Ready!");
  ros::spin();
  return 0;
}
