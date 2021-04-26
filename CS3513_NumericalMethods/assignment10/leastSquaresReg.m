function [funcMean, funcAmplitude, funcMaxDay] = leastSquaresReg(X, Y)
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