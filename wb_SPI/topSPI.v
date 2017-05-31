`timescale 1ns / 1ps


module topSPI(
input clk, input init, input reset, input[7:0] address, input[7:0] dataWr, input MISO, output SCKclock, output[7:0] dataRd, output MOSI, output NSS, output done);

wire doneWr;
wire doneRd;
wire Z3;
wire work;
wire[1:0] A;
wire initRd;
wire initWr;
wire activeNSS;
wire rstRd;
wire rstWr;
wire rstSCK;


control_SPI fsm(clk, init, reset, doneWr, doneRd, Z3, work, A, initRd, initWr, activeNSS, rstRd, rstWr, rstSCK, done);
datapath_SPI datapath(clk, work, rstSCK, initRd, initWr, rstRd, rstWr, address, dataWr, dataRd, doneRd, doneWr, SCKclock, MOSI, MISO, NSS, A, activeNSS, Z3);

endmodule
