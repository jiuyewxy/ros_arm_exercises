#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import tf2_ros
from  tf_conversions import transformations
from tf2_msgs.msg import TFMessage
from geometry_msgs.msg import TransformStamped,PoseStamped
import math
class TFPublish():
    def __init__(self):
        rospy.init_node('tf_pub')
        rospy.loginfo("tf_pub python demo.")
        # 创建一个TransformStamped对象: base_link — tool_link
        transformStamped = TransformStamped()
        # 设置时间戳
        transformStamped.header.stamp = rospy.Time.now()
        # 设置父坐标系
        transformStamped.header.frame_id = "base_link"
        # 设置子坐标系
        transformStamped.child_frame_id = "tool_link"
        # 设置父坐标系到子坐标系的平移变换
        transformStamped.transform.translation.x = 0.25
        transformStamped.transform.translation.y = 0
        transformStamped.transform.translation.z = 0.75
        yaw =0
        rate = rospy.Rate(20)

        # 节点关闭前一直循环发布
        while not rospy.is_shutdown():
            yaw += 0.02
            # 设置父坐标系到子坐标系的旋转变换(四元数表示)
            q = transformations.quaternion_from_euler(0,0,yaw)
            transformStamped.transform.rotation.x = q[0]
            transformStamped.transform.rotation.y = q[1]
            transformStamped.transform.rotation.z = q[2]
            transformStamped.transform.rotation.w = q[3]
            # 创建一个TF发布对象
            br = tf2_ros.TransformBroadcaster()
            # 广播 base_link — tool_link 的TF
            br.sendTransform(transformStamped)

            # 按照循环频率延时
            rate.sleep()


if __name__ == '__main__':
    try:
        tf_pub = TFPublish()
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("TF publisher is shut down.")
