1;

function [T_out] = get_temp(length_tt, tref = 20, delta = 10, frec = 1/360)

   T_out = ones(1, length_tt) * tref + delta * sign(sin(2 * pi * frec * [1 : length_tt]))  ;

endfunction

function [y] = defuzzyfication(vReglas, a, c, vu, vl)

   denominador = numerador = 0;

   for k = 1:length(a)
      
      if(a(k) > 0)
         area_trapecio = a(k) * (vl(vReglas(k)) + vu(vReglas(k)));
         numerador += area_trapecio * c(vReglas(k));
         denominador += area_trapecio;   
      end
      
   endfor

   y = numerador / denominador;
   
endfunction

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

% Conjuntos de entrada
function [ treferencia , var_tref_upper , var_tref_lower ] = set_treferencia(tref = 20, paso = 8)

   % Muy Frio, Frio, Medio, Alto, Muy Alto
   treferencia = [ tref - 2 * paso , tref - paso , tref , tref + paso , tref + 2 * paso ];
   var_tref_upper = [ paso/2 2 2 2 paso/2 ];
   var_tref_lower = [ paso paso paso paso paso ];
   
endfunction

### Variables del sistema borroso ###
# Matriz de Reglas
% Columnas:
% MF a MC % Calefactor % Refrigerador
reglas = [
   1 3 1 ; % si mucho frio, calentar mucho y apagar refrigeracion
   2 2 1 ; 
   3 1 1 ; 
   4 1 2 ; 
   5 1 3 ];

% Estos son los conjuntos de salida normalizados de ambos (calef/refrig)
entidades = [ 0 0.5 1 ];
var_ent_upper = [ 1/6 1/6 1/6 ];
var_ent_lower = [ 0.5 0.5 0.5 ];

voltMax = 520;
ampereMax = 0.38; % en base a un voltaje de 380V

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
### Variables de la habitacion ###

horas = 3;
tiempo_total = 1 : horas * 360;
length_tt = length(tiempo_total); 

puerta = ( rand(1, length_tt) < 1/360 );
T_out = get_temp(length_tt);
T_ref = get_temp(length_tt, 21, 1, 1/180);
T_in = [20];
T_in_sin_controlar = T_in;

% Constantes de la ecuacion segun la apertura de puerta
k1_p = 0.169;
k1_np = 0.912;
k2_p = 0.831;
k2_np = 0.088;

% Constantes de corriente y voltaje
k3_p = 0.112;
k3_np = 0.604;
k4_p = -0.002;
k4_np = -0.0121;

for n = 2 : length_tt
   
   [treferencia, var_tref_upper, var_tref_lower] = set_treferencia(T_ref(n), 5);
   
   a = fuzzyfication(T_in(n-1), treferencia, var_tref_upper, var_tref_lower);

   yC = defuzzyfication(reglas(:,2), a, entidades, var_ent_upper, var_ent_lower) * ampereMax;
   yE = defuzzyfication(reglas(:,3), a, entidades, var_ent_upper, var_ent_lower) * voltMax;
   
   T_in_sin_controlar(n) = \
      (k1_p * puerta(n) + k1_np * !puerta(n)) * T_in_sin_controlar(n - 1) + \
      (k2_p * puerta(n) + k2_np * !puerta(n)) * T_out(n);
   
   T_in(n) = \
      (k1_p * puerta(n) + k1_np * !puerta(n)) * T_in(n - 1) + \
      (k2_p * puerta(n) + k2_np * !puerta(n)) * T_out(n) + \
      (k3_p * puerta(n) + k3_np * !puerta(n)) * (yC)^2 + \
      (k4_p * puerta(n) + k4_np * !puerta(n)) * yE;

end


clf;
hold on;
plot(tiempo_total, T_ref, 'y');
plot(tiempo_total, T_in_sin_controlar, 'oc');
plot(tiempo_total, T_in, 'b');
plot(tiempo_total, T_out, 'r');
stem(tiempo_total, puerta.*16.5, 'k');
title("Evolucion del Sistema de Control a traves del tiempo.");
xlabel("tiempo [t * 10seg]");
ylabel("grados [*C]");
grid;
ylim([8 32]);
hold off;
