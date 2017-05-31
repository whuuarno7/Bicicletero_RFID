`timescale 1ns / 1ps


module SCK(
input clk, input work, input rst, output reg SCK = 0);

reg[2:0] contadorSCK = 0;



always @(negedge clk)

begin
	if(rst == 1)
	begin
		contadorSCK = 0;
		//load = 0;
	end
	if(work == 1)
	begin
		if(contadorSCK == 6)
		begin
			SCK = ~SCK;
			contadorSCK = 0;
		end
		else
		begin
			SCK = SCK;
			contadorSCK = contadorSCK + 1;
		end
	end
	else
	begin
		SCK = 0;
		contadorSCK = 0;
	end
end

endmodule
