.. _slam_orb_slam2:

How to use in `ORB_SLAM2 <https://github.com/raulmur/ORB_SLAM2>`_
==================================================================


If you wanna run ORB_SLAM2 with MYNT EYE camera, please follow the steps:
-------------------------------------------------------------------------

1. Download `MYNT-EYE-D-SDK <https://github.com/slightech/MYNT-EYE-D-SDK.git>`_ and :ref:`ros_install`.
2. Follow the normal procedure to install ORB_SLAM2.
3. Update ``distortion_parameters`` and ``projection_parameters`` to ``<ORB_SLAM2>/config/mynteye_*.yaml``.
4. Run examples by MYNT® EYE.


Building the nodes for stereo (ROS)
--------------------------------------------

* Add the path including ``Examples/ROS/ORB_SLAM2`` to the ``ROS_PACKAGE_PATH`` environment variable. Open .bashrc file and add at the end the following line. Replace PATH by the folder where you cloned ORB_SLAM2:

.. code-block:: bash

  export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:PATH/ORB_SLAM2/Examples/ROS

* Execute `build_ros.sh`:

.. code-block:: bash

  chmod +x build_ros.sh
  ./build_ros.sh

Stereo_ROS Example
~~~~~~~~~~~~~~~~~~~

  * Reference ``Get camera calibration parameters`` in :ref:`slam_okvis` to get ``distortion_parameters`` and ``projection_parameters`` , and update ``<ORB_SLAM2>/config/mynteye_d_stereo.yaml`` .
  * Launch ORB_SLAM2 ``Stereo_ROS``

Run camera ``mynteye_wrapper_d``

.. code-block:: bash

  cd [path of mynteye-d-sdk]
  make ros
  source ./wrappers/ros/devel/setup.bash
  roslaunch mynteye_wrapper_d mynteye.launch

Open another terminal and run ORB_SLAM2

.. code-block:: bash

  rosrun ORB_SLAM2 mynteye_d_stereo ./Vocabulary/ORBvoc.txt ./config/mynteye_d_stereo.yaml true /mynteye/left/image_mono /mynteye/right/image_mono
