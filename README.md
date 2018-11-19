# Shapefinder
Finds and highlights squares in image provided

Install ImageMagick on system before running

Running
-------
g++ main.c
./a.out square.png -o c.ppm -s square -c white

1. -o output file name
2. -s shape (currently only works with rectangles)
3. -c highlight color
