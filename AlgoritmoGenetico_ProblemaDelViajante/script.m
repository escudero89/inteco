1;

A = csvread("puntos2.dat");
B = csvread("logs2.dat");

for b = 1 : size(B)(1)
   clf;
   hold on;
   title(["Generacion [" num2str(b) "]"])
   plot(A(1,1),A(1,2),'ok');
   for a = 2 : size(A)(1)
      plot(A(a,1),A(a,2),'or');
   end

   x = [];
  y = [];
  
      for k = 1 : size(B)(2)
         x = [ x  A(B(b, k) + 1, 1) ];
         y = [ y  A(B(b, k) + 1, 2) ];
      end
      plot(x,y,'b');
      xlim([-.1 6.1]);
      ylim([-.1 6.1]);
   
hold off;
pause(0.1);
end
