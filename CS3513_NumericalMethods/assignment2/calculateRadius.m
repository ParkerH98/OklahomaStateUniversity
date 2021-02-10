function radius = calculateRadius(x, y)
% takes in cartesian coords, (x, y) and returns the radius value

radius = sqrt((x.^2) + (y.^2));
end