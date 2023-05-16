#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from exercise_three.msg import addend

def talker():
    # 初始化节点
    rospy.init_node('topic_pub', anonymous=False)
    # 打印输出日志消息
    rospy.loginfo('topic_pub node is Ready!')
    # 创建发布RobotInfo消息到话题/robot_info的句柄(发布端)pub
    pub = rospy.Publisher('/addend', addend, queue_size=10)
    # 创建了addend消息的对象msg,并赋值
    msg = addend()
    msg.x = 1
    msg.y = 3
    msg.z = 2
    # 创建rate对象,设置频率为5Hz,用于循环发布
    rate = rospy.Rate(5)
    # 节点关闭前一直循环发布消息
    while not rospy.is_shutdown():
        # 发布消息
        pub.publish(msg)
        # 按照循环频率延时
        rate.sleep()

if __name__ == '__main__':
    talker()





