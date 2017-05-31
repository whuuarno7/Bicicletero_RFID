`timescale 1ns / 100ps

////aqui se definen las entradas y salidas que tendra la maquina de estados; siempre se tiene como entrada la señal de reloj clk/////////
module fsm_LCD(clk, init, reset, C1, C2, C3, C4, C5, ADD1, ADD2, LOAD1, LOAD2, LOAD3, LOAD4, RESET1, RESET2, DONE);


///////////entradas a la maquina de estaods (señales de control)////

input clk;
input init;
input reset;     //cambiado a =0;error:(   ESTO SEGURO ES DE FATHR.. PREGUNTARLE QUE ES
input C1;
input C2;
input C3;
input C4;
input C5;

reg [2:0] count = 0;


//salidas de la maquina de control; algunas de estas señales las recibe el datapath////

output reg ADD1; //estan dentro de un always, son reg (a la izqierda)
output reg ADD2;
output reg LOAD1;
output reg LOAD2;
output reg LOAD3;
output reg LOAD4;
output reg RESET1;
output reg RESET2;
output reg DONE;

////// AQUI SE DEFINEN LOS ESTADOS QUE SE TENDRAN


parameter INICIO = 4'b0000;
parameter ASIGNARINS = 4'b0001;
parameter ASIGNARDAT = 4'b0010;
parameter CONTADOR1 = 4'b0011;
parameter ACTIVARE = 4'b0100;
parameter CONTADOR2 = 4'b0101;
parameter DESACTIVARE = 4'b0110;
parameter CONTADOR3 = 4'b0111;
parameter CONTADORINS = 4'b1000;
parameter TERMINADO = 4'b1001;



reg[3:0] state;

initial begin

 ADD1=0; 
 ADD2=0;
 LOAD1=0;
 LOAD2=0;
 LOAD3=0;
 LOAD4=0;
 RESET1=1;
 RESET2=0;
 DONE=1;

end

always @(posedge clk) begin

   //este reset es UNA ENTRADA , es el reset general de todo  //( pues lleva al estado INCIO)
  if(reset) begin  
    state = INICIO;
  end 
  else begin
   case (state)
	
	 INICIO:begin
	  if(~init)
	    state = INICIO;
	  else
	    state = ASIGNARINS;
	 end
	 
	 ASIGNARINS:begin
           count=count+1;
	  if(count<3)        
	    state = ASIGNARINS;
	  else
            count=0;
	    state = ASIGNARDAT;
	 end
	 
	 ASIGNARDAT:begin
          count = count+1;
	  if(count<3)
	    state = ASIGNARDAT;
	  else
            count = 0;
	    state = CONTADOR1;
	 end
	 
	  CONTADOR1:begin
	  if(~C1)
	    state = CONTADOR1;
	  else
	    state = ACTIVARE;
	 end
	 
	  ACTIVARE:begin
	  count= count+1;	 
	  if(count<3)
	    state = ACTIVARE;
	  else
            count=0;
	    state = CONTADOR2;
	 end
	 
	 
	  CONTADOR2:begin
	  if(~C2)
	    state = CONTADOR2;
	  else
	    state = DESACTIVARE;
	 end
	 
	  DESACTIVARE:begin
          count=count+1;
	  if(count<3)
            state = DESACTIVARE;
          else
            count=0;
            state = CONTADOR3;
	 end
	 
	 CONTADOR3:begin
          if(~C3)
            state = CONTADOR3;
          else
            state = CONTADORINS;
	 end
	 
	 
	 CONTADORINS:begin       ///AQUI QUE SE HACE PRIMERO, LEER LA VARIABLE DE CONTROL O MODIFICAR LOS VALORES DE ADD1, ADD2, LOAD, ETC.
	  if(C4)
	    state = TERMINADO;
	  else
	    state = ASIGNARINS;
	 end
	 
	 TERMINADO:begin
	  if(~C5)
	    state = TERMINADO;
	  else
	    state = INICIO;
	 end
	 
	 default:state = INICIO;
	 
	endcase
  end
end



always @(state) begin

 case(state)
 
  INICIO:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=1;
	 RESET2=0;
	 DONE=1;

	
  end
  
  ASIGNARINS:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=1;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=0;
	 DONE=0;
	
end

  ASIGNARDAT:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=1;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=0;
	 DONE=0;

end

 CONTADOR1:begin
	 ADD1=1; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=0;
	 DONE=0;
	
end

 ACTIVARE:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=1;
	 LOAD4=0;
	 RESET1=1;
	 RESET2=0;
	 DONE=0;
	
end

 CONTADOR2:begin
	 ADD1=1; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=0;
	 DONE=0;
	
end

 DESACTIVARE:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=1;
	 RESET1=1;
	 RESET2=0;
	 DONE=0;
	
end

 CONTADOR3:begin
	 ADD1=1; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=0;
	 DONE=0;
	
end

 CONTADORINS:begin
	 ADD1=0; 
	 ADD2=1;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=1;
	 RESET2=0;
	 DONE=0;

end

 TERMINADO:begin
	 ADD1=1; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=0;
	 RESET2=1;
	 DONE=1;
end
    
  
  default:begin
	 ADD1=0; 
	 ADD2=0;
	 LOAD1=0;
	 LOAD2=0;
	 LOAD3=0;
	 LOAD4=0;
	 RESET1=1;
	 RESET2=1;
	 DONE=0;
	
  end
  
  
  
 endcase
end


endmodule
