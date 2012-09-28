1;

% Le paso un xlims que es un vector con dos parametros
function [matriz] = rectangle_pattern(amount = 1000, xlims = [-1 1], ylims = [-1 1])
	matriz = rand(amount, 2);

	% Coloca la matriz entre min(xlims) y max(xlims)
	matriz(:, 1) = matriz(:, 1) * (max(xlims) - min(xlims)) + min(xlims);
	matriz(:, 2) = matriz(:, 2) * (max(ylims) - min(ylims)) + min(ylims);

end

function [circle] = circle_pattern(amount = 1000, radio = 1)

	circle = [];

	for k = 1 : amount

		angulo = rand() * (2 * pi);
		radius = rand() * radio;

		xcirc = radius * cos(angulo);
		ycirc = radius * sin(angulo);

		circle = [circle ; xcirc ycirc];

	end

end

function [T] = t_pattern(amount = 1000)

	T_upper = rectangle_pattern(amount/2, [-1 1], [0.5 1]);
	T_lower = rectangle_pattern(amount/2, [-0.25 0.25], [-1 0.5]);

	T = [ T_upper ; T_lower ];

end

A = rectangle_pattern(1000);
B = circle_pattern(1000);
C = t_pattern(1000);

plot(A(:,1), A(:,2), 'or', B(:,1), B(:,2), 'ob', C(:,1), C(:,2), 'om');