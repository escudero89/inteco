function print_trapecios(ex, c, vu, vl)

   A = zeros(length(ex), length(c));

   for j = 1:length(ex)
      A(j, :) = fuzzyfication(ex(j), c, vu, vl);
   end

   color = ['r', 'g', 'b', 'c', 'm', 'y', 'k'];
   
   clf;
   hold on;
   for k = 1:length(c)
      
      plot(ex, A(:, k), color(k));
      
   endfor
   grid;
   ylim([-0.1 1.1]);
   hold off;
   
endfunction

% Interpola y obtiene los valores de los trapecios
function [a] = fuzzyfication(x, c, vu, vl)

   for k = 1:length(c)
   
      p1 = c(k) - vl(k);
      p2 = c(k) - vu(k);
      p3 = c(k) + vu(k);
      p4 = c(k) + vl(k);
   
      a(k) = 0;
      
      if (x > p1 & x < p2)
         a(k) = (x - p1) / (p2 - p1);
      
      elseif (x >= p2 & x <= p3)
         a(k) = 1;
         
      elseif (x > p3 & x < p4)
         a(k) = (x - p4) / (p3 - p4);
      
      end
      
   endfor
   
endfunction
