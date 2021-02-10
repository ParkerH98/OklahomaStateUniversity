function [r, theta] = convertToPolar(x, y)
% takes in cartesian coords, (x, y) and returns the the polar coordinate
% equivalent represented by (r, theta) where theta is measured in degrees

% calculates r and theta and stores into variables
r = calculateRadius(x, y);
theta = calculateTheta(x, y);

% prints converted output
fprintf("(%d, %d) --> (r, theta) ~ (%f, %f)\n", x, y, r, theta);
end