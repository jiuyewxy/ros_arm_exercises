#include <ros/ros.h>
#include <exercise_three/addend.h>
//ROS标准msg头文件
#include <std_msgs/Float32.h>

// 接收到消息后,进入该回调函数
void callBack(const boost::shared_ptr<exercise_three::addend const> &msg){
  float sum = msg->x + msg->y +msg->z;
  ROS_INFO("The result:%f",sum);
}

int main(int argc, char **argv){
  // 初始化节点
  ros::init(argc, argv, "sub_test");
  // 创建一个节点句柄（NodeHandle）对象nh
  ros::NodeHandle nh;
  // 打印输出日志消息
  ROS_INFO("topic_sub node is Ready!");  
  // 创建/pub_info话题的Subscriber对象,话题的回调处理函数为callBack
  ros::Subscriber sub = nh.subscribe("addend", 10, callBack);
  // 循环等待回调函数
  ros::spin();
  return 0;
}
