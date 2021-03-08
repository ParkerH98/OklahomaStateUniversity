function [root, Ea, ea, n] = bisectnew(func, xl, xu, Ead, varargin)
% Ea is the approximate absolute error
%ea is the approximate percent relative error

if nargin < 3, error('at leaast 3 input arguments required')
end

test = func(xl, varargin{:})*func(xu, varargin{:});

if test > 0, error('no sign change')
end

if nargin < 4 || isempty(Ead), Ead = 0.000001; % set defualt Ead
end

iter = 0; xr = xl; ea = 100;

n = ceil(log2(1/Ead)); % calculate number of iterations and round up

while(1)
    
    xrold = xr;
    xr = (xl + xu) / 2;
    iter = iter + 1;
    
    if xr ~= 0, ea = abs((xr - xrold) / xr) * 100; %calculate ea
    end
    
    test = func(xl, varargin{:})*func(xr, varargin{:});
    
    % move upper or lower bounds
    if test < 0
        xu = xr;
    elseif test > 0
        xl = xr;
    else
        ea = 0;
    end
    
    %need to fix
    Ea = 1;
    
    % check break conditions
    if ea <= Ead || iter >= n, break, 
    end
end

root = xr; % sets the calculated root
end