# Mathematical model

## Barriers

The barriers (walls) are defined by horizontal and vertical segments.
Horizontal and vertical barriers are kept in separate data structures.

This is useful for many reasons:
- This way, we don't have to store which way they are oriented.
- The operation we will do on them is different. You already know the
implications of that.

They are both defined by 3 doubles. Their position, and their start and end
values. For horizontal barriers, position means their Y value, start and end
means their starting and ending X values. For vertical barriers, this means
their X value, and their starting and ending Y values.


## Barrier files

Barriers are stored in .txt files (for now).

In the first line of the file, there should be 2 integers separated by a space
that tell how many horizontal and vertical lines there will be in the file.

After that, the first n lines will contain the horizontal barriers, the other m
lines will contain the vertical barriers.

For the horizontal lines, the lines consist of 3 decimals. The 1st tells the
barrier's position on the Y axis. The 2nd is the starting X position and the
3rd is the ending X position.

The vertical lines are similar, only the first number tells the position on the
X axis, and the rest tell the starting and end positions on the Y axis.

In code, the start value will be the smaller one and the end will be the higher
one, but this should't be the case in the files. The reader will switch them if
it has to.


## Data structure

The barriers will be stored in two sorted arrays. One for the vertical lines
and one for the horizontal lines. They are sorted based on their position on
their respected axes.


## Scanning

The number of samples returned with a scan is defined in lidar_specs.h and is
360 by default. Each sample has the same origin, as they would do with a lidar.
Each sample is taken an the angle defined by the formula:   
i * 360° / n   where n is the number of samples to take, and i is the index
value of the sample.

For each sample, a line is created, specified by this formula: ay = mx + b.
The line is angled according to the previous formula.

After that, you can search through the horizontal and vertical lines to find
where the lidar would intersect with them. This way you can reduce the number
of segments you have to check by half on average. Then you check the first line
after (or before) the lidar's position and if they don't collide, you check the
next and so on. Whether you check the segments forward or backward depends on
how the lidar's beam is supposed to be oriented. You do this for both the
horizontal and vertical beams.

For vertical lines you get the y coordinate like this:
y = (mx + b) / a    if y is between bounds

For horizontal lines you get the x coordinate like this:
x = (ay - b) / m    if x is between bounds

The first segment to have a common point with the beam will be the one closest
to it and you don't have to search any further.

You do have to do this for both groups of lines and then you have to compare
the results to see which is closer. This is done with euclidean distance. But
this way you will already have the distance, which is the value you will return
as the result of that one beam's scan.

If the beam doesn't meet any lines, and error value will be returned, which is
defined in **lidar_specs.h**