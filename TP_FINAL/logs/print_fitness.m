function print_fitness(archivo = "fitness.dat")

   matriz_fitness = csvread(archivo);
   
   clf;
   hold on;
   
   % primera fila los min, medio max
   for k = 1 : size(matriz_fitness)(2)
      
     plot(matriz_fitness(:, 2), 'm');
     plot(matriz_fitness(:, 3), 'r');
     stem(matriz_fitness(:, 1), 'b');
   
   end
   hold off;
   
end
