function [eval, evect] = minEigenValue(A, es, maxit)

A = inv(A);
n = length(A);

evect = ones(n, 1); 
eval = 1; 
iter = 0;
ea = 100;

while(1)
    evalold = eval;
    evect = A * evect;
    eval = max(abs(evect));
    evect = evect ./ eval;
    iter = iter + 1;
    
    if eval ~= 0
        ea = abs((eval - evalold) / eval) * 100;
    end
    if ea <= es || iter >= maxit
        break
    end
end

eval = inv(eval);