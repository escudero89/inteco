1; 

function [ret] = get_uno()
   if (rand > 0.5)
      ret = 1;
   else
      ret = -1;
   endif
endfunction

% Desvio pasarlo en porcentaje
function [ret] = get_desvio(desvio)
   ret = 1 + (rand * desvio - desvio/2) / 100;
endfunction

function [ret] = ask_uno(desvio)
   ret = get_uno() * get_desvio(desvio);
endfunction

% Validacion
function [ret] = validar(a, b, c)
   
   a = sign(a);
   b = sign(b);
   c = sign(c);

   if (a == -1)
      if (b == -1)
         ret = 1;
      else
         ret = c;
      endif
   else 
      if (b == -1)
         ret = b;
      else
         ret = -c;
      endif
   endif      

endfunction

% SCRIPT %

cantidad = 992;
desvio = 10; %

matrix = [-1 -1 -1 1 ; -1 -1 1 1 ; -1 1 -1 -1 ; -1 1 1 1 ; 1 -1 -1 -1 ; 1 -1 1 -1 ; 1 1 -1 1 ; 1 1 1 -1];

for i = 1 : cantidad
   
   datos = [];
   
   for k = 1 : 3 
      datos(k) = ask_uno(desvio);
   endfor
   
   res = validar(datos(1), datos(2), datos(3));
   
   matrix = [ matrix ; datos(1), datos(2), datos(3), res];   

endfor
