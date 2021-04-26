function [funcMean, funcAmplitude, funcMaxDay, coeffs] = leastSquaresReg(X, Y, order)
% input: X is a vector of x values 
% input: Y is a vector of y values

[XrowSize, XcolSize] = size(X); % lengths of X
sumX = 0;
sumY = 0;
sumX2 = 0;
sumXY = 0;
sumFunc = 0;

for i = 1:XcolSize

sumX = sumX + X(i); % summation of X

sumX2 = sumX2 + (X(i))^2; % summation of X^2

sumY = sumY + Y(i); % summation of Y

sumXY = sumXY + X(i) * Y(i); % summation of XY

end

slope = (XcolSize * sumXY - sumX * sumY)/(XcolSize * sumX2 - (sumX)^2); % Slope of linear regression

intercept = (sumY - slope * sumX)/XcolSize; % Intercept of linear regression


period = 365; %Period is 365 days

func = size(period, 1); % to store values for each day of the year

for i = 1:period

func(i) = slope * i + intercept; % function value at each day of the year

sumFunc = sumFunc + func(i); % summation of func

end
rows = length(X); % rows of matrix

X = X'; % transposes the x vector

M = ones(rows, order + 1); % makes a working matrix of size x by order + 1

for i = order : -1 : 1 % decrements from order to -1
    
    % goes through each column from right to left multiplying 
    % each x value by a power of n where n is from 0 to order
    M(:, i) = M(:, i + 1) .* X;
end
coeffs = (M \ Y'); % inv(M) * yVect' to compute p vector of coefficients if size m + 1
% gets coefficients from regression

funcMean = sumFunc/period; % sum of func / the period to obtain the mean

diff = size(period, 1); % used to calculate amplitude

for i = 1:period

diff(i) = abs(funcMean - func(i)); % difference of the mean and function value

end

adj = 137;
funcAmplitude = max(diff); % the max difference is the amplitude for the function

[temperature, funcMaxDay] = max(func); % gets the day with the max temperature
funcMaxDay = funcMaxDay - adj;
end

