1;

function [x] = deppest_descent(f_prima, range_min, range_max, tol = 0.01)

  x = range_min + rand * (range_max - range_min)
  
  alfa = 0.003;
  
  while (abs(f_prima(x)) > tol)
      x = -f_prima(x) * alfa + x;
   end

endfunction

function [x] = f_prima_1(x)
   x = -sin(sqrt(abs(x)))-(x^2*cos(sqrt(abs(x))))/(2*abs(x)^(3/2));
   return;
end

function [x] = f_prima_2(x)
   x = 40*cos(5*x)+15*cos(3*x)+1;
   return;
end


min = -512;
max = 512;
disp "Funcion 1"
deppest_descent(@f_prima_1, min, max)

min = 0;
max = 20;
disp "Funcion 2"
deppest_descent(@f_prima_2, min, max)
