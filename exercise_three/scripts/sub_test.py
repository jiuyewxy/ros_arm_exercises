#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from exercise_three.msg import addend
# 接收到消息后,进入该回调函数
def callback(data):
    sum = data.x +data.y +data.z
    rospy.loginfo(' %.2fm +  %.2fm +%.2fm = %f', data.x, data.y, data.z,sum)


def listener():
    # 初始化节点
    rospy.init_node('topic_sub', anonymous=True)
    # 打印输出日志消息
    rospy.loginfo('topic_sub node is Ready!')
    # 创建/robot_info话题的订阅端,话题的回调处理函数为callback
    rospy.Subscriber('/addend', addend, callback)
    # 循环等待回调函数
    rospy.spin()

if __name__ == '__main__':
    listener()
