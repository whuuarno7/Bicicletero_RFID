`timescale 1ns / 1ps


module byteMOSI(
input clk, input init, input rst, input[7:0] byteWr, output MOSI, output reg done = 0);

reg load = 1;
//reg flag = 0;
reg[3:0] contadorWr = 0;
reg[7:0] reg_temp;
assign MOSI = ~load ? reg_temp[7] : byteWr[7];



always @(negedge clk)  // Siempre que haya flanco de bajada
begin

	if(rst)
	begin
		contadorWr = 0;
		done = 0;
		load = 1;
	end
	if(init == 1)
	begin
		done = 0;
		if(load == 1)
		begin
			reg_temp = byteWr;  // Se le asigna a un regidtro temporal lo que haya en byteWr
			load = 0;
		end

		reg_temp = reg_temp << 1;     // Se desplaza el registro temporal a la izquierda
		contadorWr = contadorWr + 1;  // A contador de escritura se le suma 1

		if(contadorWr == 8)      // ¿Ya se  llegó a un byte? 
		begin
			contadorWr = 0;
			load = 1;
			done = 1;
		end
	end

end

endmodule
