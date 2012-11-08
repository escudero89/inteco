#! /usr/bin/octave -qf

% Le voy a pasar dos archivos csv para que lea, uno vector<punto> y otro matriz
function print_tube(surfacing = false, archivo_vector_puntos = 'puntos.dat', archivo_Field = 'field.dat')

	vector_puntos = csvread(archivo_vector_puntos);
	Field = csvread(archivo_Field);
	
	% En la primera fila
	punto_origen = vector_puntos(1, :);
	for k = 1 : size(vector_puntos)(1)
		
	end

	% Primera columna filas, segunda columnas
	cant_y = size(Field)(1);
	cant_x = size(Field)(2);

	x = 1 : cant_x;
	y = 1 : cant_y;

	% Damos peso positivo a los ocupados
	Field = Field * 1000;

	for k = 1 : size(vector_puntos)(1)
		% Obtenemos puntos siempre positivos
		x_pto = round(vector_puntos(k, 1) + cant_x/2);
		y_pto = round(vector_puntos(k, 2) + cant_y/2);

		% Damos un valor negativo muy alto a las tuberias
		% Pero solo una vez
		Field(x_pto, y_pto) = -1000;
		
	end
x
y
Field

	clf;
	if (surfacing) 
		surface(x, y, Field);
	else
		% Ploteo comun
		hold on;
		plot(vector_puntos(:,1), vector_puntos(:,2), 'ob');

		% Origen
		plot(vector_puntos(1,1), vector_puntos(1,2), 'or');

		% Ajustamos limites
		xlim([min(vector_puntos(:,1) - 1) , max(vector_puntos(:,1) + 1)]);
		ylim([min(vector_puntos(:,2) - 1) , max(vector_puntos(:,2) + 1)]);
		
		grid;
		hold off;
	end

end
