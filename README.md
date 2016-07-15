# DecisionTree

Some days ago I watched [this lecture](https://www.youtube.com/watch?v=-dCtJjlEEgM) by Nando De Freitas on Decision Trees
so I decided to try my personal implementation of the algorithm (also to learn how to use `cmake`). It supports categorical and continuous
variables as descriptors. The labels are not constrained on two levels only. It does not rely on any external library.

In order to build you can simply access the project root directory and type
    
    mkdir build 
    cd build 
    cmake ..
    make 

For the moment it is only possible to build the trees. I will provide error estimates in the near future.
