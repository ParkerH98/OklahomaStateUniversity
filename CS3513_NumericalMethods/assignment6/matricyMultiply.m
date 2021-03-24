function product = matricyMultiply(A, B)
% multiply matricy A and B together

%input: matricies A and B to multiply
%output: product matrix of A * B

[aRowSize, aColSize] = size(A); % gets row and col size for matrix A
[bRowSize, bColSize] = size(B); % gets row and col size for matrix B
    
if (aColSize ~= bRowSize) % checks if col size of A matches row size of B
    error('The column size of matrix A must match the row size of matrix B.');
end
 
product = zeros(aRowSize, bColSize); % creates an empty matrix to store the results in

for i = 1 : aRowSize % loops through the rows of matrix A
    for j = 1 : bColSize % loops through the columns of matrix B
        
        x = dot( A(i,:) , B(:,j)); % dot product of row of A and column of B
        product(i, j) = x; % putting the calculated product into the empty matrix
    end
end

