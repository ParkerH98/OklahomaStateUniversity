
%given
x = [3 4 5 7 8 9 11 12];
y = [1.6 3.6 4.4 3.4 2.2 2.8 3.8 4.6];


% coefficients of corre;ation
c  = corrcoef([x' y']);
% caclualtes r from coeff. of corr.
r = c(1,2);
% r squared
r2 = r^2;

% used to create Sr (sum e^2)
e = exp(2);
E = [e e e e e e e e];
res = sum(E);

% standard error
syx  = sqrt((res / (length(x) - 2)));

% displays coefficients
display('Coefficients from x^from order to 0');
nonLinearReg(x, y, 4)

 % strings to print
 r2String = sprintf('The r^2 value is: %f', r2);
 syxString = sprintf('The standard error is: %f', syx);
 
  % prints strings
 display(r2String);
 display(syxString);
 
