#! /usr/bin/octave -qf

# Le paso un CSV, con una serie de patrones, y teniendo dos clases para separar
function plot_patrones(A, imprimir = false)
    
    # Ordenamos la matriz en base a la columna de clases
    A = sortrows(A, 3);
    
    N = size(A)(1);
    
    for i = 1 : N
        # Recorre hasta encontrar un uno
        if (A(i, 3) == 1)
            break;
        end
    end
    
    
    # IMPRESION #
    
    # Parte basica de impresion
    clf;
    hold on;
    
    plot(A(1 : i-1, 1), A(1 : i-1, 2), 'or');
    plot(A(i+1 : N, 1), A(i+1 : N, 2), 'xb');
    
    hold off;
    
    # para que imprima los titulos y comentarios en los ejes
    labels = true; 

    title_name = "Distribucion de clases dada por el Perceptron Multicapa (concent.csv)";
    xlabel_name = "x1";
    ylabel_name = "x2";

     # Extra decoracion
    
    title(title_name);
    xlabel(xlabel_name);
    ylabel(ylabel_name);
    
    grid;
    axis("square");
    
    if (imprimir)
        print("prints/patrones.png");
    end
        
endfunction
