
% given
A = [2 8 10;
     8 4 5;
     10 5 7];
 
 % calculates min and max eigen values
 [min, minEvect] = minEigenValue(A, .000001, 100);
 [max, maxEvect] = maxEigenValue(A, .000001, 100);

 % strings to print
 minString = sprintf('The min eigen value of matrix A is: %f', min);
 maxString = sprintf('The max eigen value of matrix A is: %f', max);
 
  % prints strings
 display(minString);
 disp('Corresponding Eigen Vector');
 display(minEvect);
 
 display(maxString);
 disp('Corresponding Eigen Vector');
 display(maxEvect);
 
 disp('Eigen Values');
 eig(A)
 
 
 
 
