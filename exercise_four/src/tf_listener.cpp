#include <ros/ros.h>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
 
 
int main(int argc,char *argv[])
{
    //初始化
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"tf_listen");
    ros::NodeHandle nh;
    //创建一个buffer缓存订阅的数据
    tf2_ros::Buffer buffer;
    //在创建一个监听对象（可以将订阅的数据传入buffer）
    tf2_ros::TransformListener listener(buffer);
    // 以10Hz的频率循环获取 world - base_link 的最新TF变换
    ros::Rate rate(10.0);
    while(nh.ok()){
      geometry_msgs::TransformStamped trans;
      try{
        //trans = tfBuffer.lookupTransform("world", "base_link",ros::Time(0),ros::Duration(3.0));
        // 查询最新的 world - base_link的TF
        trans = buffer.lookupTransform("base_link", "tool_link",ros::Time(0));
      }
      catch (tf2::TransformException &ex) {
        ROS_WARN("%s",ex.what());
        rate.sleep();
        continue;
      }
      ROS_INFO("translation data x:%f,y:%f,z:%f",trans.transform.translation.x,trans.transform.translation.y,trans.transform.translation.z);
      ROS_INFO("rotation data x:%f,y:%f,z:%f,w:%f",trans.transform.rotation.x,trans.transform.rotation.y,trans.transform.rotation.z,trans.transform.rotation.w);
      rate.sleep();
    }
} 
