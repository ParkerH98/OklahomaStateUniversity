function theta = calculateTheta(x, y)
% takes in cartesian coords, (x, y) and returns a theta value in degrees

% the following checks all possible combos of x & y +- 0 and calculates the
% appropriate 
    if x > 0
        
        theta = atan(y ./ x);
        
    elseif x < 0 && y > 0
        
        theta = atan(y ./ x) + pi;
        
    elseif x < 0 && y < 0
        
        theta = atan(y ./ x) - pi;
        
    elseif x < 0 && y == 0
        
        theta = pi;
        
    elseif x == 0 && y > 0
        
        theta = pi ./ 2;
        
    elseif x == 0 && y < 0
        
        theta = -pi .* 2;
        
    elseif x == 0 && y == 0
        
        theta = 0;
        
    elseif x > 0 && y == 0
        
        theta = atan(y ./ x);
    end
    
    theta = theta .* (180 ./ pi);
end