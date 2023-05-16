#include "ros/ros.h"
#include "exercise_three/addend.h"	

int main(int argc,char **argv){
  //初始化ROS节点
  ros::init(argc, argv, "pub_test");
  // 创建一个节点句柄（NodeHandle）对象nh
  ros::NodeHandle nh;
  // 打印输出日志消息
  ROS_INFO("pub_test node is Ready!");
  // 创建Publisher对象pub,用于向话题/addend发布addend消息
  ros::Publisher pub = nh.advertise<exercise_three::addend>("/addend", 10);
  // 创建了addend的对象msg，并对msg里面的部分成员进行赋值
  exercise_three::addend msg;
  msg.x = 1;
  msg.y = 2;
  msg.z = 3;
  // 创建rate对象,设置频率为10Hz,用于循环发布
  ros::Rate rate(10);
  //循环发布
  while(ros::ok()){
    //打印输出xyz的数值
    ROS_INFO("x = %f, y = %f, z=%f", msg.x , msg.y ,msg.z);
    pub.publish(msg);
    // 按照循环频率延时
    rate.sleep();
  }
  return 0;
}
