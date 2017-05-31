`timescale 1ns / 1ps


module control_SPI(clk, init, reset, doneWr, doneRd, Z3, work, A, initRd, initWr, activeNSS, rstRd, rstWr, rstSCK, done);




input clk;
input init;
input reset;//cambiado a =0;error:(
input doneWr;
input doneRd;
input Z3;

output reg work; //estan dentro de un always, son reg (a la izqierda)
output reg[1:0] A;
output reg initRd;
output reg initWr;
output reg activeNSS;
output reg rstRd;
output reg rstWr;
output reg rstSCK;
output reg done;



reg [4:0] count = 0;

parameter START = 3'b000;
parameter SEND_ADDR = 3'b001;
parameter WRITE = 3'b010;
parameter READ = 3'b011;
parameter SCK_OFF = 3'b100;
parameter NSS_ON = 3'b101;
parameter END = 3'b110;

reg[2:0] state;

initial begin
work=0; 
A=2'b00;
initRd=0;
initWr=0;
activeNSS=1;
rstRd=1;
rstWr=1;
rstSCK=1;
done=0;

end

always @(posedge clk) begin
  if(reset) begin  //este reset es entrada, es el reset general de todo 
						//( pues lleva al estado START)
    state = START;
  end 
  else begin
   case (state)
		
	 START:begin
	  count = 0;
	  if(init)
	    state = SEND_ADDR;
	  else
	    state = START;
	 end
	 
	 SEND_ADDR:begin
	  
	  if(count < 15)
	  	count = count + 1;
	  else
	  begin
	  	if(doneWr)
	  	begin
	  		if(Z3)
		  	begin
		  	 count = 0;
			 state = READ;
			end 
			else
			begin
			 count = 0;
			 state = WRITE;
			end
	  	end
	  	else
	  		state = SEND_ADDR;
	  	end
	 end
	 
	  WRITE:begin	    
	  	if(count < 15)
	    count = count + 1;
	   else
	   begin
	   	if(doneWr)
	   	begin
	   		count = 0;
	   		state = SCK_OFF;
	   	end
	   	else
	   		state = WRITE;
	   end
	 	 //state = (count == 6 && doneWr) ? SCK_OFF:WRITE ;
	 end
	 
	  READ:begin
	  	if(count < 15)
	    count = count + 1;
	   else
	   begin
	   	if(doneWr && doneRd)
	   	begin
	   		count = 0;
	   		state = SCK_OFF;
	   	end
	   	else
	   		state = READ;
	   end
	 	 //state = (count == 6 && doneWr) ? SCK_OFF:READ;
	 end
	 
	  SCK_OFF:begin
	  	count = count + 1;
	 	 //state = (count == 6 && doneWr) ? SCK_OFF:READ ;
	 	 if(count == 1)
	 	 begin
	 	 	count = 0;
	 	 	state = NSS_ON;
	 	 end
	 	 else
	 	 	state = SCK_OFF;

	 end
	 
	 
	  NSS_ON:begin
	  	count = count + 1;
	 	 if(count == 6)
	 	 begin
	 	 	count = 0;
	 	 	state = END;
	 	 end
	 	 else
	 	 	state = NSS_ON;
	 end
	 
	 END:begin
	  	count = count + 1;
	 	 if(count == 30) //Se puede ajustar para que <done> dure hasta 5 ciclos de reloj más. (antes era 15)
	 	 begin
	 	 	count = 0;
	 	 	state = START;
	 	 end
	 	 else
	 	 	state = END;
	 end
	 
	 default:state = START;
	 
	endcase
  end
end



always @(state) begin

 case(state)
 
  START:begin
	work=0; 
	A=2'b00;
	initRd=0;
	initWr=0;
	activeNSS=1;
	rstRd=1;
	rstWr=1;
	rstSCK=1;
	done=0;
	
  end
  
  SEND_ADDR:begin
	work=1; 
	A=2'b00;
	initRd=0;
	initWr=1;
	activeNSS=0;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=0;
	
end

  WRITE:begin
	work=1; 
	A=2'b10;
	initRd=0;
	initWr=1;
	activeNSS=0;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=0;

end

 READ:begin
	work=1; 
	A=2'b01;
	initRd=1;
	initWr=1;
	activeNSS=0;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=0;
	
end

 SCK_OFF:begin
	work=0; 
	A=2'b00;
	initRd=0;
	initWr=0;
	activeNSS=0;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=0;
	
end

 NSS_ON:begin
	work=0; 
	A=2'b00;
	initRd=0;
	initWr=0;
	activeNSS=1;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=0;
	
end

 END:begin
	work=0; 
	A=2'b00;
	initRd=0;
	initWr=0;
	activeNSS=1;
	rstRd=0;
	rstWr=0;
	rstSCK=0;
	done=1;
	
end
  
  default:begin
   work=0; 
	A=2'b00;
	initRd=0;
	initWr=0;
	activeNSS=1;
	rstRd=1;
	rstWr=1;
	rstSCK=1;
	done=0;
	
  end
    
 endcase
end


endmodule
