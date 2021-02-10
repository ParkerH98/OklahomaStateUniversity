function y = calculateVector(a, b, x)
% Takes in arguments a and b as natural numbers and a vector x
% and uses them in the equation and saves the output to y.

y = b .* exp(-a .* x) .* (sin(b .* x)) .* (.012 .* x.^4 - .15 .* x.^3 + .075 .* x.^2 + 2.5 .* x);
end


