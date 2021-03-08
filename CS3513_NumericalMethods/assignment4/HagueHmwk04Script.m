
fcd = @(m, cd, t, v) sqrt(9.81 * m / cd) * tanh(sqrt(9.81 * cd / m) * t) - v; %anon. function to calculate drag coefficient

% bungee jumper problem variables
m = 95;
v = 46;
t = 9;
xl = .2;
xu = .5;
Ead = .05;

[root, Ea, ea, n] = bisectnew(@(cd) fcd(m, cd, t, v), xl, xu, Ead); % runs bisectnew function and stores output

display("Drag Coefficient: " + root);