# Lab 4 - amg284
#### To Correctly Use... 
Run the following commands for ROS setup:  
`source /opt/ros/noetic/setup.bash`  
`source devel/setup.bash`  
 
To get the correct stdr simulator (which is required): `git clone -b noetic-devel https://github.com/cwru-eecs-275/stdr_simulator.git`    
  
Install all dependencies:   
Install rosdep: `sudo apt install python3-rosdep`    
Install missing dependencies: `rosdep install --from-paths src --ignore-src -r -y`    
Update rosdep: `rosdep update`    
Finally, fix permissions for rosdep: `sudo rosdep fix-permissions`    
To initialize rosdep: `sudo rosdep init`     

To Run...
Use to make node runnable: `catkin_make robot_no_crash_node`    
To run: `roslaunch robot_no_crash launch.launch &`    
To use another robot, use: `rqt`    
