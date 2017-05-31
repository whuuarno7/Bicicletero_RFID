`timescale 1ns / 1ps

module fsm_Teclado(clk, reset, entrada1, entrada2, entrada3, entrada4, load1, load2, load3, load4, rtecla, done);

input clk;
input reset;
input entrada1;
input entrada2;
input entrada3;
input entrada4;
output reg load1;
output reg load2;
output reg load3;
output reg load4;
output reg rtecla;
output reg done;
reg [4:0] count=0;


parameter inicio =0;
parameter tecla1 =1;
parameter tecla2 =2;
parameter tecla3 =3;
parameter tecla4 =4;
parameter hecho =5;

reg[2:0] state;
initial begin

load1 =0;
load1 =0;
load1 =0;
load1 =0;
load1 =0;
rtecla=0;
done =0;
end

always @(posedge clk) begin
if(reset) 
 state= inicio;
 else begin
  case (state)
    inicio: begin
    if(~entrada1 && ~entrada2 && ~entrada3 && ~entrada4)
     state=inicio;
    else begin
    if(entrada1)
     state=tecla1;
    if(entrada2)
     state=tecla2;			
    if(entrada3)
     state=tecla3;
    if(entrada4)
     state=tecla4;
    end
   end


 	tecla1:begin
	state=hecho;
	end
	tecla2:begin
	state=hecho;
	end	
	tecla3:begin
	state=hecho;
	end
	tecla4:begin
	state=hecho;
	end	
	
	hecho:begin
	if(count<20)
	begin
	count=count+10;
	state=hecho;
	end
	else
	 begin
          count=0;
	  state=inicio;
	end
	end

default:state=inicio;


 endcase
end
end

always @(state) begin
case(state)
inicio:begin
load1=0;
load2=0;
load3=0;
load4=0;
rtecla=1;
done=0;
end

tecla1:begin
load1=1;
load2=0;
load3=0;
load4=0;
rtecla=0;
done=0;
end

tecla2:begin
load1=0;
load2=1;
load3=0;
load4=0;
rtecla=0;
done=0;
end

tecla3:begin
load1=0;
load2=0;
load3=1;
load4=0;
rtecla=0;
done=0;
end

tecla4:begin
load1=0;
load2=0;
load3=0;
load4=1;
rtecla=0;
done=0;
end

hecho:begin
load1=0;
load2=0;
load3=0;
load4=0;
rtecla=0;
done=1;
end

endcase
end


endmodule
