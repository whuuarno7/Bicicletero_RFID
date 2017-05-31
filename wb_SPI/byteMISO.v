`timescale 1ns / 1ps


module byteMISO(
input clk, input init, input rst, input MISO, output reg[7:0] byteRd, output reg done = 0);


reg[3:0] contadorRd = 0;



always @(posedge clk) // siempre que haya flanco de subida

begin
	if(rst)
	begin
		contadorRd = 0;
		done = 0;
		//load = 0;
	end
	if(init == 1)
	begin
		byteRd[0] = MISO; //  Se mira el bit menos significativo del registro byteRd
		contadorRd = contadorRd + 1; //se aumenta en 1 el registro que cuenta el número de bits
		if(contadorRd == 8) // ¿Ya se llegó a 1 byte?
		begin
			contadorRd = 0; //Si se llegó a un byte se reinicia el contador
			done = 1;
		end
		else
		begin
			byteRd = byteRd << 1; // Si no se llegó a un byte, se corre a la izquierda 
			contadorRd = contadorRd;
			done = 0;
		end
	end
end

endmodule
