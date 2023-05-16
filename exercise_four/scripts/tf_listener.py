#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped,PoseStamped
from std_msgs.msg import Empty
class TFListen():
    def __init__(self):
        rospy.init_node('tf_listen')
        rospy.loginfo("tf_listen Python demo")

        # 监听tool_link — base_link的最新TF变换
        self.listen_recent()

    def listen_recent(self):
        # 创建一个TF监听器对象listener,监听TF数据并存入tfBuffer
        tfBuffer = tf2_ros.Buffer()
        listener = tf2_ros.TransformListener(tfBuffer)

        # 以10Hz的频率循环获取 base_link到tool_link 的变换
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            try:
                # 查询最新的 base_link - tool_link的TF
                trans = tfBuffer.lookup_transform('base_link', 'tool_link',rospy.Time(0))
            except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
                rate.sleep()
                continue
            rospy.loginfo("translation data x:%f,y:%f,z:%f",trans.transform.translation.x,trans.transform.translation.y,trans.transform.translation.z);
            rospy.loginfo("rotation data x:%f,y:%f,z:%f,w:%f",trans.transform.rotation.x,trans.transform.rotation.y,trans.transform.rotation.z,trans.transform.rotation.w);
            rate.sleep()

if __name__ == '__main__':
    try:
        tf_listen = TFListen()
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("TF Listener is shut down.")
