# Supone que hay dos pesos en cada fila de A
function plot_pattern(A, cant_x, cant_y, titlelabel = "")
#{
0 1 2 
3 4 5
6 7 8

. .
. . 
. .
. .
. .
#}

	clf;
	hold on;

	plot_pattern_helper(A, cant_x, cant_y);

	# Recorremos la matriz A y reasignamos valores
	
	A_col = [];
	
	for j = 1 : cant_x
	
		for k = 1 : cant_y
	
			A_col = [A_col ; A(j + cant_x * (k - 1), :)];
	
		end
	
	end

	plot_pattern_helper(A_col, cant_x, cant_y);
	
	# Ahora ploteo las neuronas
	plot(A(:, 1), A(:, 2), 'xr');
	
	title(titlelabel);
	grid;
	
	hold off;

end

function plot_pattern_helper(A, cant_x, cant_y)

	# Recorremos y unimos hermanos
	
	for k = 1 : cant_y
		
		m_i = cant_x * (k - 1) + 1;
		m_f = cant_x * k;
		
		plot( A( m_i : m_f, 1), A( m_i : m_f, 2), 'b');
		
	end
	
end
