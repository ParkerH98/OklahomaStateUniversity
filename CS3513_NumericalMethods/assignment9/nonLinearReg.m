function [p] = nonLinearReg(xVect, yVect, order)

rows = length(xVect); % rows of matrix

xVect = xVect'; % transposes the x vector

M = ones(rows, order + 1); % makes a working matrix of size x by order + 1

for i = order : -1 : 1 % decrements from order to -1
    
    % goes through each column from right to left multiplying 
    % each x value by a power of n where n is from 0 to order
    M(:, i) = M(:, i + 1) .* xVect;
end
p = (M \ yVect'); % inv(M) * yVect' to compute p vector of coefficients if size m + 1

end




