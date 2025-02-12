# Lidar simulator

This is a simulator program for a generic lidar robot. It simulates the
movement of the robot as well as the lidar data. The lidar data is modelled
after the Slamtec RPLidar A1, but is similar to other a lot of other sensor's
data.

## The simulated environment

The walls in the simulated environment are defined by vertical and horizontal
segments (called barriers in code).

By default, 1 packet of lidar data ( called a measurement ) contains 360
samples, but this can be overwritten in **lidar_spechs.h**. Whatever number you
choose, it will always only measure 1 circle. For example, if you set it to
2000, each sample will be at the angle: i * 2000 / 360 degrees where i is the
index of the sample in the measurement.
