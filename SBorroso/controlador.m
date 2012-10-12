1;

function [T_out] = get_tout(length_tt, tref = 22)

   T_out = ones(1, length_tt) * tref + 5 * sign(sin(2 * pi * 1/120 * [1 : length_tt]))  ;

endfunction
 
horas = 3;
tiempo_total = 1 : horas * 360;
length_tt = length(tiempo_total); 

a = ( rand(1, length_tt) < 1/360 );
T_out = get_tout(length_tt);
T_in = [20];

corriente = zeros(1, length_tt);
voltaje = zeros(1, length_tt);

% Constantes de la ecuacion segun la apertura de puerta
k1_a = 0.169;
k1_na = 0.912;
k2_a = 0.831;
k2_na = 0.088;

% Constantes de corriente y voltaje
k3_a = 0.112;
k3_na = 0.604;
k4_a = -0.002;
k4_na = -0.0121;

for n = 2 : length_tt
   
   T_in(n) = \
      (k1_a * a(n) + k1_na * !a(n)) * T_in(n - 1) + \
      (k2_a * a(n) + k2_na * !a(n)) * T_out(n) + \
      (k3_a * a(n) + k3_na * !a(n)) * (corriente(n))^2 + \
      (k4_a * a(n) + k4_na * !a(n)) * voltaje(n);

end

clf;
hold on;
plot(tiempo_total, T_in, 'b');
plot(tiempo_total, T_out, 'r');
stem(tiempo_total, a.*16.5, 'k');

grid;
ylim([16 28]);
hold off;
