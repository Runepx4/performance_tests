# performance_tests
Compare performance between C++ and Python in ROS

# Usage
Please run the launch files located in the launch directory. The launch files are divided as follow:

| Publisher | Subscriber | Launch File | 
|:---------:|:----------:|:-----------:|
| Python | Python | `pubPy_subPy.launch`   |
| Python |  C++   | `pubPy_subCpp.launch`  |
|  C++   |  C++   | `pubCpp_subCpp.launch` |
|  C++   | Python | `pubCpp_subPy.launch`  |

Example: `roslaunch performance_tests pubCpp_subCpp.launch`

The launch files will start a publisher, a subscriber, and a rqt_plot window. The rqt window should allready be subscribing to the relevant topics (`/measured_frequency` and `/real_frequency`). Please note that the results are also printed in the console. You may be able to see a performance increase if you close the rqt_plot and just look at the numbers in the console.  

# Results
Based on a Lenovo T430, Core i5, Ubuntu 16.04, 64 Bit, ROS Kinetic. The results were as follows:
* Phyton publisher - Phyton subscriber -> stable up to around 8.000 Hz
* Python publisher - C++ subscriber -> stable up to around 8.000 Hz
* C++ publisher - C++ subscriber -> stable up to around 20.000 Hz
* C++ publisher - Phyton subscriber -> stable up to around 20.000 Hz

Note
----
The code is not fully optimised. It was created with limited time and to be rather simple to understand. It gives a visual idea of the performance difference between C++ and Python.