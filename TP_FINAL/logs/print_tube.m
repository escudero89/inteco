#! /usr/bin/octave -qf

% Le voy a pasar dos archivos csv para que lea, uno vector<punto> y otro matriz
function print_tube(directorio, archivo_vector_puntos = 'puntos.dat', archivo_Field = 'field.dat', surfacing = false)

	vector_puntos = csvread([directorio "/" archivo_vector_puntos]);
	Field = csvread([directorio "/" archivo_Field]);
	
	% En la primera fila agregamos tomas y origen
	punto_origen = vector_puntos(1, :);
	tomas = [];
	for k = 2 : size(vector_puntos)(1)
		if vector_puntos(k, 2) == -9999
			break;
		end
		tomas = [tomas ; vector_puntos(k, :) ];
	end

	cant_rows = size(Field)(1);
	cant_cols = size(Field)(2);
	
	Field_nuevo = [];
	% Bloques
	for j = 1 : cant_cols
		for i = 1 : cant_rows
			if (Field(i, j) != 0)
				Field_nuevo = [Field_nuevo; (j - 1) (cant_rows - i) ];
			end
		end
	end
	

	iteracion = 0;
	h = k;
	% Ahora estoy parado en algo -9999
	while (h < size(vector_puntos)(1))
		
		cant_tubos = vector_puntos(h, 1);
		recorrer = vector_puntos((h + 1) : (h + cant_tubos), :);
		
		if (surfacing)
			print_tube_surface(recorrer, Field_nuevo, punto_origen, tomas, iteracion);
		else
			print_tube_plot(recorrer, Field_nuevo, punto_origen, tomas, iteracion);
		end
		
		h += cant_tubos + 1;
		iteracion++;

	end

end

function print_tube_plot(vector_puntos, Field, punto_origen, tomas, iteracion)
	
	clf;
	% Ploteo comun
	hold on;

	if (size(Field)(1) > 0)
		plot(Field(:, 1), Field(:, 2), 'xk');
	end

	plot(vector_puntos(:,1), vector_puntos(:,2), 'ob');

	% Origen
	plot(punto_origen(1), punto_origen(2), 'or');

	% Tomas
	plot(tomas(:,1), tomas(:,2), 'om');

	% Ajustamos limites
%	xlim([min(vector_puntos(:,1) - 1) , max(vector_puntos(:,1)) + 1]);
%	ylim([min(vector_puntos(:,2) - 1) , max(vector_puntos(:,2)) + 1]);

	grid;
	axis("equal");
	title(["Generacion [" num2str(round(50 * iteracion)) "]" ]);
    
     ylabel("y");
     xlabel("x");

	%		pause(0.01);
	print(["draws/dibujo_" padding_zeros(iteracion) ".png"]);

	hold off;

endfunction

function print_tube_surface(vector_puntos, Field, punto_origen, tomas, iteracion)

% Primera columna filas, segunda columnas
	cant_y = size(Field)(1);
	cant_x = size(Field)(2);

	x = 1 : cant_x;
	y = 1 : cant_y;

	% Damos peso positivo a los ocupados
	Field = Field * 1000;

	for k = 1 : size(vector_puntos)(1)
		% Obtenemos puntos siempre positivos
		x_pto = round(vector_puntos(k, 1));
		y_pto = round(vector_puntos(k, 2));

		% Damos un valor negativo muy alto a las tuberias
		% Pero solo una vez
		if x_pto > 0 & y_pto > 0 
			if Field(abs(x_pto), abs(y_pto)) != 1000
			   Field(abs(x_pto), abs(y_pto)) = -1000;
			else
			   Field(abs(x_pto), abs(y_pto)) = -2000;
			end
		end
	end

	clf;
	surface(y, x, Field);
	title(["Generacion [" num2str(iteracion) "]" ]);
	print(["draws/surface_" padding_zeros(iteracion) ".png"]);

endfunction

function [ret] = padding_zeros(num)
	
	ceros = "0000";

	for it = 1 : 4
	
		if (num / 10^it < 1)
			if (it > 0)
				ceros = ceros(it:4);
			end
			ret = [ ceros num2str(num) ];
			break;
		end
	end
end
