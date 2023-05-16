#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from exercise_three.srv import CallAdd, CallAddResponse
# 服务的回调处理函数,req为服务的请求
def server_handle(req):
    res = CallAddResponse()
    # 打印输出req.name
    res.sum = req.addend.x+req.addend.y+req.addend.z;
    rospy.loginfo("request: x=%f,y=%f,z=%f",req.addend.x, req.addend.y, req.addend.z);
    rospy.loginfo("sending back response: %f",res.sum);
    return res

def server():
    # 初始化节点
    rospy.init_node('add_server')
    # 创建call_add服务的服务端server,服务类型SetTargetDetec,服务回调函数server_handle
    server = rospy.Service('call_add', CallAdd, server_handle)
    rospy.loginfo('call_add server is Ready!')
    rospy.spin()

if __name__ == '__main__':
    server()
