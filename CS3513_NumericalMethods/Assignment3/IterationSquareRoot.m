function solution = IterationSquareRoot(a, errorStopping, maxIterations)
% iteratively find the square root of input value a

% keeps track of current iteration
iteration = 1;

% x sub i term for each iteration
xI = 1;

% starting error approximation value
errorApproximation = 100;

% sets values to default if not specified when calling function
if nargin < 2 || isempty(errorStopping), errorStopping = 0.0001;
end

if nargin < 3 || isempty(maxIterations), maxIterations = 50;
end

% loops and calculates xI -- exits when conditions met
while (1)
    
    % last iteration''s xI value
    solutionOld = xI;
    
    % calculates new xI value for each iteration
    xI = ((xI + (a / xI)) / 2);
    
    % increments iteration
    iteration = iteration + 1;
    
    % recalculates the error approximation when xI is approx. 0
    if xI ~= 0
        errorApproximation = abs((xI - solutionOld) / xI) * 100;
    end
    
    % exits if the approximate error is less than the stoppingError or when
    % the number of iteration has reached the boundry
    if errorApproximation <= errorStopping || iteration >= maxIterations
        break
    end
    
    % returns the result of xI as the solution
    solution = xI;
end
