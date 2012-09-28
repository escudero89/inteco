function print_buffer(cant_x, cant_y, title_label = "")

	A = csvread("buffer.csv");

	cant = cant_x * cant_y;
	maxit = length(A) / cant
	
	for it = 1 : maxit
		
		A_sub = A(1 + cant * (it - 1) : cant * it, :);

		plot_pattern(A_sub, cant_x, cant_y, title_label);
		
		xlim([-1 1]);
		ylim([-1 1]);
		
		print(["buffer/" title_label "_it_" padding_zeros(it) ".png"]);

	end

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
