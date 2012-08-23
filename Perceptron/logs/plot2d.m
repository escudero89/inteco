#! /usr/bin/octave -qf
1;

# DEFINO AQUI TODAS LAS VARIABLES #

# Nombre de archivos
filename_padrones = 'padrones.log';
filename_pesos = 'pesos.log';

# Carpeta donde guardo las figuras, la flag es para que guarde o no las figuras
prints = true;
filename_figs = "prints/";
filename_tag = "fig_";

# Maxima cantidad de veces que repito un peso para saltearlo
max_sequence = 100; 

# Rango de los ejes 
xrange = [-2, 2];
yrange = [-2, 2];

# para que imprima los titulos y comentarios en los ejes
labels = true; 

title_name = "Ajuste de la recta de clasificacion";
xlabel_name = "x1";
ylabel_name = "x2";

# INICIO EL SCRIPT #

padrones = dlmread(filename_padrones);
pesos = dlmread(filename_pesos);

# Revisa cuantas veces se repite los pesos, si son muchas veces, no lo agrega para plotear

max_iterations = 0;
sequences = runlength(pesos);

for i = 1 : length(sequences)
    if (sequences(i) > max_sequence)
        break;
    end
    max_iterations += sequences(i);
end
max_iterations += 1; # Agregamos uno mas para incluir el que excluimos en el bloque for


# Trazamos la linea que marca la clasificacion de patrones

for i = 1 : max_iterations # Cantidad de pesos
    
    clf;

    # Ploteo todos los padrones
    plot(padrones(:, 1), padrones(:, 2), 'rd');

    hold on;

    mu = pesos(i, 3); # umbral
    w1 = pesos(i, 1);
    w2 = pesos(i, 2);

    m = w1 / w2;    # pendiente
    b = mu / w2;    # ordenada al origen

    x = [-2 : 0.01 : 2];    # rango de x

    y = m * x - b;

    plot(x, y);
    
    # Extra decoracion
    
    xlim(xrange);
    ylim(yrange);
    
    if (labels)
        title(title_name);
        xlabel(xlabel_name);
        ylabel(ylabel_name);
    end
    
    grid;
    axis("square");
    
    if (prints)
        print([filename_figs filename_tag  num2str(i, "%03d") ".png"]);
    end
    
    hold off;
    
end

disp (["Las figuras han sido guardadas en: " filename_figs filename_tag "X.png"]);
close;

# Luego en la terminal hacemos
# convert -delay 20 -loop 200 -layers Optimize *.png animation.gif
# Y luego para pausar el ultimo frame
# convert animation.gif \( +clone -set delay 500 \) +swap +delete animation_with_pause.gif
# Y lo convertimos en gif
