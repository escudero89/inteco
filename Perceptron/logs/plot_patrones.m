#! /usr/bin/octave -qf

# Le paso un CSV, con una serie de patrones, y teniendo dos clases para separar
function plot_patrones(A, clases = [-1, 0, 1], imprimir = false)
    
    # Ordenamos la matriz en base a la columna de clases
    A = sortrows(A, 3);
    
    N = size(A)(1);
    
    cero = 0;
    uno = 0;
    
    colores = ['k', 'g', 'b', 'm'];
    
    clf;
    hold on;    

    # TEXTO IMPRESION #
    
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

    old_i = 1;
    
    for clase = clases

        for i = old_i : N
                
            if (A(i, 3) != clase | i == N)
                ['o' colores(clase + 2)]
                size(A(old_i : i-1, :))
                plot(A(old_i : i-1, 1), A(old_i : i-1, 2), ['o' colores(clase + 2)]);
                old_i = i;
                pause
                break;
            end
        end
    
    end

    hold off;   
    
    if (imprimir)
        print("prints/patrones.png");
    end
        
endfunction
