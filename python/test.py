#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

seq = ['GREEN,5','YELLOW,1','RED,5'] ##normal
#seq = ['YELLOW,0.8','BLANK,0.8']     ##blink
#seq = ['REDYELLOWGREENLEFTCENTERRIGHT,0.8','BLANK,0.8'] ##test:blink all

def talker():
  pub = rospy.Publisher('tl_state', String, queue_size=10)
  rospy.init_node('tl_sender', anonymous=True)
  r = rospy.Rate(10) # 10hz
  while not rospy.is_shutdown():
    for state in seq:
      tlstate,delay = state.split(',')
      rospy.loginfo(state)
      pub.publish(tlstate)
      rospy.sleep(float(delay))
#      r.sleep()
#      pub.publish(tlstate)
#      rospy.sleep(float(delay)-(1./10))

if __name__ == '__main__':
  try:
    talker()
  except rospy.ROSInterruptException: pass
