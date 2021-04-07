
% gievn
A = [2 8 10;
     8 4 5;
     10 5 7];
 
 % calculates min and max eigen values
 min = minEigenValue(A, .000001, 100);
 max = maxEigenValue(A, .000001, 100);

 % strings to print
 minString = sprintf('The min eigen value of matrix A is: %f', min);
 maxString = sprintf('The max eigen value of matrix A is: %f', max);
 
 % prints strings
 display(minString);
 display(maxString);