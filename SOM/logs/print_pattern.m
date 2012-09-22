# "prints_2" "circle"
function print_pattern (directorio, nombre, simple = false )
	
	if (!simple)
		A = csvread([nombre "_" directorio ".csv"]);
		plot_pattern(A, 5, 5, ["SOM de 25 neuronas, ['" nombre ".csv']"]);
		print([directorio "/" nombre "_multi.png"]);		
	else
		A = csvread([nombre "_" directorio "_single.csv"]);
		plot_pattern(A, 25, 1, ["SOM de 25 neuronas unidimensional, ['" nombre ".csv']"]);
		print([directorio "/" nombre "_single.png"]);		
	end

endfunction
