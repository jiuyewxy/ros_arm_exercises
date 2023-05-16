#include "ros/ros.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
 
 
int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_broadcaster");
    ros::NodeHandle n;
    //创建发布对象
    static tf2_ros::TransformBroadcaster broadcaster;
    //组织被发布的对象
    geometry_msgs::TransformStamped ts;
    //ts.header.seq=100;
    ts.header.stamp=ros::Time::now();
    ts.header.frame_id="base_link";
    ts.child_frame_id="tool_link";
    //坐标系平移
    ts.transform.translation.x=0.25;
    ts.transform.translation.y=0.0;
    ts.transform.translation.z=0.75;

    double yaw =0;
    //频率20hz
    ros::Rate r(20);
    while(ros::ok())
    {
      //	每次循环偏航角加0.05
      yaw +=0.05;

     tf2::Quaternion qtn;
     qtn.setRPY(0,0,yaw);
     //转换为四元数
     ts.transform.rotation.x=qtn.getX();
     ts.transform.rotation.y=qtn.getY();
     ts.transform.rotation.z=qtn.getZ();
     ts.transform.rotation.w=qtn.getW();

     //发布
     broadcaster.sendTransform(ts);
     r.sleep();
    }
    //broadcaster.sendTransform(ts);
    ros::spin();
}
