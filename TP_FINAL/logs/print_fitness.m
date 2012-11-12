function print_fitness(archivo = "fitness.dat")

   matriz_fitness = csvread(archivo);
   
   clf;
   hold on;

	matriz_fitness = 1000 ./ (1 + matriz_fitness);
   
   % primera fila los min, medio max
   for k = 1 : size(matriz_fitness)(2)
      
     plot(matriz_fitness(:, 3), 'xm');
     plot(matriz_fitness(:, 2), 'r');
     plot(matriz_fitness(:, 1), 'b');
     
     title("Funcion de fitness");
     
     ylabel("fitness");
     xlabel("generacion");
     
     grid;
     ylim([min(matriz_fitness(:, 3)) max(matriz_fitness(:, 1))*1.1]);
   
   end
   hold off;
   
end
