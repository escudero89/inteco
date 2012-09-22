# "prints_2" "circle" "_retorno_2"
function print_pattern (directorio, nombre, extra, simple = false )

	A = csvread([nombre extra ".csv"]);
	
	if (!simple)
		plot_pattern(A, 5, 5, ["SOM de 25 neuronas, ['" nombre ".csv']"]);
		print([directorio "/" nombre "_multi.png"]);		
	else
		print_pattern_helper(A, nombre);
		print([directorio "/" nombre "_single.png"]);		
	end

endfunction

function print_pattern_helper(A, nombre);

	plot_pattern(A, 25, 1, ["SOM de 25 neuronas unidimensional, ['" nombre ".csv']"]);
	
endfunction
