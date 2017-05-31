`timescale 1ns / 100ps

module datapath_LCD(clk, ADD1, ADD2, LOAD1, LOAD2, LOAD3, LOAD4, RESET1, RESET2, DONE, numeroInstrucciones, instruccion0, instruccion1, instruccion2, instruccion3, instruccion4, instruccion5, instruccion6, instruccion7, instruccion8, instruccion9,
instruccion10, instruccion11, instruccion12, instruccion13, instruccion14, instruccion15, instruccion16, instruccion17, instruccion18,instruccion19, instruccion20, instruccion21, instruccion22, instruccion23, instruccion24, instruccion25, instruccion26, instruccion27,instruccion28, instruccion29,instruccion30, instruccion31, instruccion32, instruccion33, instruccion34, instruccion35, instruccion36, instruccion37,instruccion38, instruccion39,  salida, C1, C2, C3, C4, C5);
	 
//////// el orden de los pines es el sigueinte instruccion[DB7, DB6, DB5, DB4, DB3, DB2, DB1, DB0, E, R/W, RS]//////7
/////¡¡¡¡¡¡¡¡¡IMPORTANTE R/w SIMPRE DEBERA ESTAR EN 0, YA QUE SOLO SE QUIERE ESCRIBIR EN EL LCD!!!!!!!//////


reg [10:0]  instruccionAEjecutar=11'b00000000000;


reg [31:0] contadorNano=0;
reg [5:0] contadorInstrucciones=0;  // este es i en el diagrama de flujo



input  clk;

///ESTAS ENTRADAS VIENEN DE LAS SEÑALES DE SALIDA DE LA MAQUINA DE ESTADOS
input ADD1; 
input ADD2;
input LOAD1;
input LOAD2;
input LOAD3;
input LOAD4;
input RESET1;
input RESET2;
input DONE;
input [6:0]   numeroInstrucciones;
input [10:0]  instruccion0;
input [10:0]  instruccion1;
input [10:0]  instruccion2;
input [10:0]  instruccion3;
input [10:0]  instruccion4;
input [10:0]  instruccion5;
input [10:0]  instruccion6;
input [10:0]  instruccion7;
input [10:0]  instruccion8;
input [10:0]  instruccion9;
input [10:0]  instruccion10;
input [10:0]  instruccion11;
input [10:0]  instruccion12;
input [10:0]  instruccion13;
input [10:0]  instruccion14;
input [10:0]  instruccion15;
input [10:0]  instruccion16;
input [10:0]  instruccion17;
input [10:0]  instruccion18;
input [10:0]  instruccion19;
input [10:0]  instruccion20;
input [10:0]  instruccion21;
input [10:0]  instruccion22;
input [10:0]  instruccion23;
input [10:0]  instruccion24;
input [10:0]  instruccion25;
input [10:0]  instruccion26;
input [10:0]  instruccion27;
input [10:0]  instruccion28;
input [10:0]  instruccion29;
input [10:0]  instruccion30;
input [10:0]  instruccion31;
input [10:0]  instruccion32;
input [10:0]  instruccion33;
input [10:0]  instruccion34;
input [10:0]  instruccion35;
input [10:0]  instruccion36;
input [10:0]  instruccion37;
input [10:0]  instruccion38;
input [10:0]  instruccion39;

/////ESTAS SERAN LAS SALIDA FISICAS/// EN EL DIAGRAMA DE FLUJO ESTO ES EL REGISTRO SALIDA////////
output reg [10:0]  salida=11'b00000000000;

//// ESTAS SON LAS SALIDAS DEL CAMINO DE DATOS, ESTAS SERAN ENTRADAS DE LA FSM 
output reg  C1=0;
output reg  C2=0;
output reg  C3=0;
output reg  C4=0;
output reg  C5=0;





always @(negedge clk)
 begin
////////CONTADORNANO////
   if(ADD1)
    contadorNano = contadorNano+10;
   else
    contadorNano = contadorNano;

   if(RESET1)
    contadorNano = 0;
   else
    contadorNano = contadorNano;

///////CONTADORINSTRUCCIONES////////

  if(ADD2)
   contadorInstrucciones= contadorInstrucciones+1;
  else
   contadorInstrucciones=contadorInstrucciones;

  if(RESET2)
   begin
    contadorInstrucciones=0;
    salida=11'b00000000000;
    end
  else
  contadorInstrucciones=contadorInstrucciones;






////////ASIGNACIONINSTRUCCION/////////

 if(LOAD1)
  begin
   if(contadorInstrucciones==0)
     instruccionAEjecutar=instruccion0;
   
   if(contadorInstrucciones==1)
     instruccionAEjecutar=instruccion1;
   
   if(contadorInstrucciones==2)
     instruccionAEjecutar=instruccion2;
   
   if(contadorInstrucciones==3)
     instruccionAEjecutar=instruccion3;
   
   if(contadorInstrucciones==4)
     instruccionAEjecutar=instruccion4;
   
   if(contadorInstrucciones==5)
     instruccionAEjecutar=instruccion5;
   
   if(contadorInstrucciones==6)
     instruccionAEjecutar=instruccion6;
   
   if(contadorInstrucciones==7)
     instruccionAEjecutar=instruccion7;
   
   if(contadorInstrucciones==8)
     instruccionAEjecutar=instruccion8;
   
   if(contadorInstrucciones==9)
     instruccionAEjecutar=instruccion9;

   if(contadorInstrucciones==10)
     instruccionAEjecutar=instruccion10;

   if(contadorInstrucciones==11)
     instruccionAEjecutar=instruccion11;

   if(contadorInstrucciones==12)
     instruccionAEjecutar=instruccion12;

   if(contadorInstrucciones==13)
     instruccionAEjecutar=instruccion13;

   if(contadorInstrucciones==14)
     instruccionAEjecutar=instruccion14;

   if(contadorInstrucciones==15)
     instruccionAEjecutar=instruccion15;

   if(contadorInstrucciones==16)
     instruccionAEjecutar=instruccion16;

   if(contadorInstrucciones==17)
     instruccionAEjecutar=instruccion17;

   if(contadorInstrucciones==18)
     instruccionAEjecutar=instruccion18;

   if(contadorInstrucciones==19)
     instruccionAEjecutar=instruccion19;

   if(contadorInstrucciones==20)
     instruccionAEjecutar=instruccion20;
     
   if(contadorInstrucciones==21)
     instruccionAEjecutar=instruccion21;
   
   if(contadorInstrucciones==22)
     instruccionAEjecutar=instruccion22;
   
   if(contadorInstrucciones==23)
     instruccionAEjecutar=instruccion23;
   
   if(contadorInstrucciones==24)
     instruccionAEjecutar=instruccion24;
   
   if(contadorInstrucciones==25)
     instruccionAEjecutar=instruccion25;
   
   if(contadorInstrucciones==26)
     instruccionAEjecutar=instruccion26;
   
   if(contadorInstrucciones==27)
     instruccionAEjecutar=instruccion27;
   
   if(contadorInstrucciones==28)
     instruccionAEjecutar=instruccion28;
   
   if(contadorInstrucciones==29)
     instruccionAEjecutar=instruccion29;
     
   if(contadorInstrucciones==30)
     instruccionAEjecutar=instruccion30;
     
   if(contadorInstrucciones==31)
     instruccionAEjecutar=instruccion31;
   
   if(contadorInstrucciones==32)
     instruccionAEjecutar=instruccion32;
   
   if(contadorInstrucciones==33)
     instruccionAEjecutar=instruccion33;
   
   if(contadorInstrucciones==34)
     instruccionAEjecutar=instruccion34;
   
   if(contadorInstrucciones==35)
     instruccionAEjecutar=instruccion35;
   
   if(contadorInstrucciones==36)
     instruccionAEjecutar=instruccion36;
   
   if(contadorInstrucciones==37)
     instruccionAEjecutar=instruccion37;
   
   if(contadorInstrucciones==38)
     instruccionAEjecutar=instruccion38;
   
   if(contadorInstrucciones==39)
     instruccionAEjecutar=instruccion39;
 end

///////////////////////////////AIGANACION DE LA SALIDA FISICA////////////////

 if(LOAD2)   ////ASIGA CUANDO LOAD2 ESTA EN ALTO
  begin
  salida[0]=instruccionAEjecutar[0];
  salida[1]=instruccionAEjecutar[1];
  salida[10:3]=instruccionAEjecutar[10:3];
  end
 else
  begin
  salida[0]=salida[0];
  salida[1]=salida[1];
  salida[10:3]=salida[10:3];
  end

 if(LOAD3)         ////////ASIGA CUANDO LOAD3 ESTA EN ALTO
  salida[2]=instruccionAEjecutar[2];
 else
 salida[2]=salida[2];

 if(LOAD4)         ////////ASIGA CUANDO LOAD3 ESTA EN ALTO
  salida[2]=0;
 else
 salida[2]=salida[2];


//////////COMPNANO1///////////////////

 if(contadorNano==200)
  C1=1;
 else
  C1=0;


//////////COMPNANO2///////////////////

 if(contadorNano==1000)
  C2=1;
 else
  C2=0;



//////////COMPNANO3///////////////////

 if(contadorNano==2000000)
  C3=1;
 else
  C3=0;

//////////COMPNANO5///////////////////este es de color vinotinto en el datapath

 if(contadorNano==30)
  C5=1;
 else
  C5=0;

//////////COMPINSTRUCCIONES///////////////////

 if(contadorInstrucciones==numeroInstrucciones)
  C4=1;
 else
  C4=0;


 


end



endmodule
