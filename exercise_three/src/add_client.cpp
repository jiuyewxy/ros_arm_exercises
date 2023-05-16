#include <ros/ros.h>
#include "exercise_three/CallAdd.h"

int main(int argc, char** argv){
  // 初始化ROS节点
  ros::init(argc, argv, "add_client");	

  ROS_INFO("add_client node is Ready!");
  // 创建节点句柄
  ros::NodeHandle nh;
  // add_server服务的服务端启动前，服务的调用一直处于阻塞状态
  ros::service::waitForService("call_add");

  // 创建一个client，请求add_three service, service消息类型是 exercise_three::Calladd
  ros::ServiceClient client = nh.serviceClient<exercise_three::CallAdd>("call_add");

  float x,y,z;
  ros::param::param<float>("~x", x, 1);
  ros::param::param<float>("~y", y, 2);
  ros::param::param<float>("~z", z, 3);


  // 创建exercise_three::Calladd类型的service消息
  exercise_three::CallAdd srv;
  srv.request.addend.x = x;
  srv.request.addend.y = y;
  srv.request.addend.z = z;
  
  ROS_INFO("parameter:x=%f,y=%f,z=%f",srv.request.addend.x,srv.request.addend.y,srv.request.addend.z);

  // 发布service请求，等待加法运算的应答结果
  if (client.call(srv)){
    ROS_INFO("Sum: %f", srv.response.sum);
  }else{
    ROS_ERROR("Failed to call service add_server");
    return 1;
  }
	
  return 0;
};


