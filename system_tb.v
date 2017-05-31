//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 10;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

reg  MISO;
wire MOSI;
wire SCK;
wire[2:0] CS;

reg entrada1;
reg entrada2;
reg entrada3;
reg entrada4;
//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	//SPI
	.MISO(MISO),
	.MOSI(MOSI),
	.SCK(SCK),
	.CS(CS),
	
	.entrada1(entrada1),
	.entrada2(entrada2),
	.entrada3(entrada3),
	.entrada4(entrada4)
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */

	initial begin  // Initialize Inputs
      //clk = 0; reset = 0; start = 0;//start = 1;
      //SCK = 0;
      //byteWr =  8'b01011010;
      //address = 8'b01101001;
      entrada1 = 1;
      entrada2 = 0;
      entrada3 = 0;
      entrada4 = 0;
      #100;
      entrada1 = 0;
      entrada2 = 0;
      entrada3 = 1;
      entrada4 = 0;
   end
   
   initial begin // Reset the system, Start the image capture process
      forever begin 
        //@ (reset_trigger);
        
        //@(negedge clk);
        //MISO = 1;
        
        //start = 1;
        
        @(negedge clk);
        MISO = 1;
        #90;
        
        @(negedge clk);
        MISO = 1;
        #90;
        
        @(negedge clk);
        MISO = 0;
        #90;
        
        @(negedge clk);
        MISO = 0;
        #90;
        
        @(negedge clk);
        MISO = 1;
        #90;
        
        @(negedge clk);
        MISO = 0;
        #90;
        
        @(negedge clk);
        MISO = 0;
        #90;
        
        @(negedge clk);
        MISO = 1;
        #90;
        /*if(done == 1)
        begin
        	start = 0;
        	#80
        end*/
        //#50;
        //start = 0;
        end
   end


   
initial begin

	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
	#0  rst <= 0;
	#80 rst <= 1;
	//#10000 gpio_io[3:0] = 4'hF;
	#(tck*40000) $finish;
end



endmodule
