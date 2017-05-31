`timescale 1ns / 1ps

`define SIMULATION


module wb_SPI_TB;

   reg clk;
   reg reset;
   reg[31:0] wb_adr_i; //reg[7:0] address;
   reg[31:0] wb_dat_i;//reg[7:0] byteWr;
   wire[31:0]   wb_dat_o;
   reg[3:0]   wb_sel_i;
   reg 			wb_cyc_i;
   reg             wb_stb_i;
	wire              wb_ack_o;
	reg               wb_we_i;
	// SPI 
	wire              spi_sck;
	wire              spi_mosi;
	reg               spi_miso;
	wire				  spi_cs;

//input clk, input init, input reset, input[7:0] address, input[7:0] dataWr, input MISO, output SCKclock, output[7:0] dataRd, output MOSI, output NSS, output done);
   //mult_32 uut (.clk(clk) , .rst(rst) , .init(start) , .A(in_A) , .B(in_B) , .pp(pp) , .done(done));
   //topSPI uut (.clk(clk), .init(start), .reset(reset), .address(address), .dataWr(byteWr), .MISO(MISO), .SCKclock(SCKclock), .dataRd(byteRd), .MOSI(MOSI), .NSS(NSS), .done(done) );
   
   wb_SPI uut (
	.clk(clk),
	.reset(reset), //en los dema perifericos, aparece negado (?
	// Wishbone bus
	.wb_adr_i(wb_adr_i),
	.wb_dat_i(wb_dat_i),
	.wb_dat_o(wb_dat_o),
	.wb_sel_i(wb_sel_i), //desconectada en GPIO (?)
	.wb_cyc_i(wb_cyc_i),
	.wb_stb_i(wb_stb_i),
	.wb_ack_o(wb_ack_o),
	.wb_we_i(wb_we_i),
	// SPI 
	.spi_sck(spi_sck),
	.spi_mosi(spi_mosi),
	.spi_miso(spi_miso),
	.spi_cs(spi_cs)
);
	
   parameter PERIOD          = 10;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   //reg [21:0] i;
   event reset_trigger;
   


   initial begin  // Initialize Inputs
      clk = 0; reset = 0; //start = 0;//start = 1;
      //SCK = 0;
      //byteWr =  8'b01011010;
      //address = 8'b01101001;
      wb_adr_i = 32'b0100;
      wb_dat_i = 32'b01101001;
      wb_cyc_i = 1;
      wb_stb_i = 1;
      wb_we_i = 0; //0 leer, 1 escribir
      #20
      wb_adr_i = 32'b0000;
   end

   initial  begin  // Process for clk
     #OFFSET;
     forever
       begin
         clk = 1'b0;
         #(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
         #(PERIOD*DUTY_CYCLE);
       end
   end


   /*initial begin // Reset the system, Start the image capture process
      forever begin 
        @ (reset_trigger);
        @ (posedge clk);
        senal = 0;
        @ (posedge clk);
        senal = 1;

       for(i=0; i<2; i=i+1) begin
         @ (posedge clk);
       end
          senal = 0;
      end
   end*/


   initial begin // Reset the system, Start the image capture process
      forever begin 
        //@ (reset_trigger);
        
        //@(negedge clk);
        //MISO = 1;
        #90;
        //start = 1;
        
        @(negedge clk);
        spi_miso = 1;
        #90;
        
        @(negedge clk);
        spi_miso = 1;
        #90;
        
        @(negedge clk);
        spi_miso = 0;
        #90;
        
        @(negedge clk);
        spi_miso = 0;
        #90;
        
        @(negedge clk);
        spi_miso = 1;
        #90;
        
        @(negedge clk);
        spi_miso = 0;
        #90;
        
        @(negedge clk);
        spi_miso = 0;
        #90;
        
        @(negedge clk);
        spi_miso = 1;
        #90;
        
        /*if(done == 1)
        begin
        	start = 0;
        	#80
        end*/
        //#50;
        //start = 0;
        end
        /*
        for(i=0; i<600000; i=i+10) begin
			@(posedge clk);
		  end


      


        @ (posedge clk);
        senal=0;
        for(i=0; i<2400000; i=i+10) begin
         @ (posedge clk);
	
        end
        @ (posedge clk);
       
        senal = 1;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


        
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<1200000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;	

  
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;

	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<1200000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;


	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
       senal=0;
	for(i=0; i<600000; i=i+10) begin
	@(posedge clk);
	end
	senal=1;
      end
      */
   end
  

   initial begin: TEST_CASE
     $dumpfile("wb_SPI_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*5000000) $finish;
   end

endmodule

