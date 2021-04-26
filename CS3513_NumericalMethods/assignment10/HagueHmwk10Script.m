% given
X = [15 45 75 105 135 165 225 255 285 315 345]; 
Y = [3.4 4.7 8.5 11.7 16 18.7 19.7 17.1 12.7 7.7 5.1];

% gets amplitude, mean, and max
[funcMean, funcAmplitude, funcMaxDay, coeffs] = leastSquaresReg(X, Y, 5);


%answers
disp("Mean");
disp(funcMean);

disp("Amplitude");
disp(funcAmplitude);

disp("Max Day");
disp(funcMaxDay);

disp("Coefficients");
disp(coeffs);
