# IGVC
Spring 2019 IGVC Team code repository

Working features of the provided code:
  * Manual Driving
  * Point Cloud and occupancy grid creation.


When running roscore on initial start up of the robot, execute the commands in found in terminal_export.sh
to set the ros mster url and hostname.


Dependencies
 * Rtabmap
 * realsense2_camera
 * roboteq_driver


To move to robot manualy, run:
 * rosrun automav listener
 * rosrun teleop_twist_keyboard teleop_twist_keyboad.py
  * Follow the instructions on scren for movement
   * Movement has been limited to 4 directions of movement, which can easily be added to 8 directions of movement with "k" being a full stop.
   * The code currently does not use diff_drive controller, which woul allow for full 360 degree range of movement, if that is wanted, set up the movement with diff_drive.
   * In order to implement to speed control that is indicated on the teleop_twist_keyboard.py program, in automav listener, normalize the input from the x_linear and z_angular commands so that when an increase in velocity is selected the normalized values can be within a range of 0 and 1 which can then be multiplied by some predefined constant to give your motor command in the range on -1000 to 1000.
   * You will have to have the terminal with this program running selected in order to move the robot.


In order to run the map generation, run launch_pointcloud_mapping.sh.



**Misc.**
 * The frame rate with the current setup is very low, with around 2-7 fps. This causes the robot, with just the 3d camera, to lose odomerty if it is turned too quickly with a densly populated surrounding environment. This can be fixed be using outside odometry, such as from wheel encoders or by using the odemetry provided by the Realsense T265 that is not currently on the robot but is provided in the bin with its materials.
 * The robot currently does not have the lidar installed, with is also another source on odometry and would be a faster mapping solution, but it is also used for the global planning when using move_base for the movement planning, this can be avoided by just using the rtabmap occupancy grid and having that using for the local planner and not having the global planner at all.
  * This is in no way an optimal method for the robot but it does allow for a quick start to the project so that everyting can be up and running and allows for you to then go in and add more challanging optimzations inf you have never used ros or done robot development before.
 * The motor controller currently is in open_loop speed mode, which is again, not optimal, the optimal being closed-loop position mode, which will allow for more precise movement based off of the readings of the motor controllers.
