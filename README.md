# Shapefinder
Finds and highlights squares in image provided

Install ImageMagick on system before running

Converts image to ppm file using Imagemagick. Looks through image for square/rectangle. Once shape is found, the color of the shape is changed based on flag provided(see ColorNames.h for supported color flags). Built without using opencv or other computer vision software

Running
-------
g++ main.c                                                 
./a.out square.png -o c.ppm -s square -c white

1. -o output file name
2. -s shape (currently only works with rectangles)
3. -c highlight color
