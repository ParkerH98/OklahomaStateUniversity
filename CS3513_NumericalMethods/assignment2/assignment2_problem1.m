format short g;

% clears the current plot if it exists
clf();

% makes x, y, & z vectors
x = 0:pi/40:pi/2;
y = calculateVector(2, 5, x);
z = y.^2;

%stores x, y, & z into a matrix w
w = [x;y;z];

%transposes matrix from 3x21 to 21x3
w = w';

display(w);

% plots the y data
plot(x, y, 'r -. p', 'LineWidth', 1.5, 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'w', 'MarkerSize', 14);

% waits to allow the plotting of an additional plot
hold on;
% plots the z data
plot(x, z, 'b - s', 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'g');

% stops plot waiting
hold off

% adds legend, title, and label to plot
legend('y', 'z');
title('Parker Hague''s Plot - Assignment 2');
xlabel('X Data');
ylabel('Y/Z Data');



