
% Part: A

% given:
A = [6 -1 ; 12 8 ; -5 4];
B = [4 0 ; .5 2];
C = [2 -2 ; 3 1];

% matrix multiplication
matricyMultiply(A, B)
matricyMultiply(A, C)
matricyMultiply(B, C)
matricyMultiply(C, B)

% these two matricies cannot be multiplied.
% matricyMultiply(B, A)
% matricyMultiply(C, A)

%Part B:
% The remaining matricies cannot be calculated because the col of 
% the first matrix has to match the row of the second matrix. This 
% is because the dot product has to be performed on vectors of the 
% same magnitude.

%Part C:
% Order matters when multiplying matricies. In this example, 
% A * B IS valid, but B * A is NOT valid.