function [eval, evect] = maxEigenValue(A, es, maxit)

n = length(A);

evect = ones(n, 1); 
eval = 1; 
iter = 0;
ea = 100;

while(1)
    evalold = eval; % save old value
    evect = A * evect; % determine eigen vector as [A] * {x}
    eval = max(abs(evect)); % determine new eigen value
    evect = evect ./ eval; % normalize eigen vector to eigen value
    iter = iter + 1;
    
    if eval ~= 0
        ea = abs((eval - evalold) / eval) * 100;
    end
    if ea <= es || iter >= maxit
        break
    end
end