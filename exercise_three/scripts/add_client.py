#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from exercise_three.srv import *

def client():
    # 初始化节点
    rospy.init_node('add_client')
    rospy.loginfo('add_client node is Ready!')
    # 在target_detection服务的服务端启动前,服务的调用一直处于阻塞状态
    rospy.wait_for_service("call_add")
    # 创建对象client用来调用target_detection服务
    client = rospy.ServiceProxy('call_add', CallAdd)
    x = rospy.get_param('~x', 1)
    y = rospy.get_param('~y', 2)
    z = rospy.get_param('~z', 3)

    try:
        req = CallAddRequest()
        req.addend.x = x
        req.addend.y = y
        req.addend.z = z
        rospy.loginfo("parameter:x=%f,y=%f,z=%f",req.addend.x,req.addend.y,req.addend.z);

        # 进行服务调用,res保存服务端返回的应答数据
        res = client(req)
        rospy.loginfo("sum: %f",res.sum);

    except rospy.ServiceException as e:
        rospy.logerr("Service call failed: %s"%e)

if __name__ == '__main__':
    client()
