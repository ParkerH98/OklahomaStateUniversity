%Part a:

% given
A = [4^2 4 1;
     2^2 2 1;
     7^2 7 1];
 
 % Row-Sum Norm
 infCond = cond(A, inf);
 
 % Part b:
 
 % Spectral
 spCond = cond(A, 2);

 % Frobenius
 froCond = cond(A, 'fro');
 
 % create strings
 infString = sprintf( 'Infinity Condition: %f', infCond);
 spString = sprintf( 'Spectral Condition: %f', spCond);
 froString = sprintf( 'Frobenius Condition: %f', froCond);

 % print answers
 disp('Part a:')
 disp(infString)
 
 disp('Part b:')
 disp(spString)
 disp(froString)
 