# Packing rectangles into the smallest square
This code loads a list of rectangles with different sizes from a single ascii file, and then computes a layout for placing all rectangles insde one square.
1.  The rectangles should not overlap with each other
2.  the square should have the smallest possible area.

The result is the size of the square and the actual placement of all the input rectangles.

## Flow
1.  Read the input file.
2.  Create Rectangle objects.
3.  Run the rectangle packing algorithm on the rectangle objects.
4.  Print out the results.

## Structure of input file
- Each line represents two diagonal coordinates of a rectangle separated by a tab or `\t`. 
- Each pair is separated by a comma, using other symbols will result in an error.
- Example of rectangle coordinates: `0,0  7,9`

## Structure of the expected output
![Screenshot of expected output](https://github.com/NaderKZ/FaroTest/blob/master/sample_output.PNG)

The output lists out 
1.  All the rectangles sorted by the longest length first then width second.
2.  The smallest square measurements that fits all rectangles is displayed.
3.  The final layout of the rectangles inside the square is presented in the form of coordinates

## Basic explanation of the implemented algorithm

- We assume that the smallest square that can fit all rectangles should have an area that is as 
close to the sum of all rectangles together, therefore we take the square root of the sum of 
the area and round it up to the next integer to get the length of each side of the square.

- Then we proceed with placing the sorted rectangles with the longest 
side horizontally starting from the bottom up on the left side of the square. If the rectangle doesnt fit anymore we move	
on to the next rectangle until we have tried all of the rectangles in this orientation at least once. The unplaced rectangles
are carried on to the next section.
        
- Then we place the leftover rectangles with the longest side vertically starting from the bottom up on the right side of the square.
Before finalizing the placement, we check if the new rectangle placement overlaps with an existing one. The unplaced rectangles are carried on to the next section.
          
- Finally we place the leftover rectangles with the longest side horizontally starting from the right side of the square inwards.Before finalizing the placement, 
we check if the new rectangle placement overlaps with an existing one. 

## Paths to most important files
-  The main file can be found in Test/Test/Main.cpp
-  The input samples (SampleX.ascii) can be found in the folder Test/Test/Examples/.
-  The classes headers and implementations can also be found in the folder Test/Test/.
