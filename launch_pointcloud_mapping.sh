#!/bin/bash

xterm -hold -e 'roslaunch realsense2_camera rs_camera.launch align_depth:=true' &>/dev/null

xterm -hold -e 'roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start" depth_topic:=/camera/aligned_depth_to_color/image_raw rgb_topic:=/camera/color/image_raw camera_info_topic:=/camera/color/camera_info approx_sync:=false' &>/dev/null

#xterm -hold -e 'rosrun automav listener' 

#xterm -hold -e 'rosrun teleop_twist_keyboard teleop_twist_keyboard.py'
