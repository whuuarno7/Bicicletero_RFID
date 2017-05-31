

#include "soc-hw.h"




uint32_t read_uint32()
{
	uint32_t val = 0, i;

    for (i = 0; i < 4; i++) {
        val <<= 8;
        val += (uint8_t)uart_getchar();
    }

    return val;
}

void writeint(uint32_t entero) //Esta función permite escribir en la UART, de manera hexadecimal, un numero entero
{
	//entero = (entero & 0x0000000F);
	volatile uint8_t *p1 = (uint8_t *)entero;
	uint32_t i,j;
	
	volatile uint8_t val;
	
	for(i = 0; i<4 ; i++){
		val = *p1;
		for(j=0; j<4; j++)
		{
			val = val>>4;
		}
		if (val >= 0xA) 
			uart_putchar('A'+ (val) -10);
		else
			uart_putchar('0'+ (val));
	
		val = *p1;
		val = val & 0x0F;
		if (val >= 0xA)
				uart_putchar('A'+ (val) -10);
			else
				uart_putchar('0'+ (val));
		p1++;
	}
}

//Esta función permite escribir en la UART, de manera hexadecimal, los primeros 8 bits de un numero entero
void writeintXX(uint32_t entero)
{
	//entero = (entero & 0x0000000F);
	volatile uint8_t *p1 = (uint8_t *)entero; //antes &entero
	p1 = p1 + 3;
	uint32_t j;
	
	volatile uint8_t val;
	
	val = *p1;
	for(j=0; j<4; j++)
	{
		val = val>>4;
	}
	if (val >= 0xA) 
		uart_putchar('A'+ (val) -10);
	else
		uart_putchar('0'+ (val));

	val = *p1;
	val = val & 0x0F;
	if (val >= 0xA)
			uart_putchar('A'+ (val) -10);
		else
			uart_putchar('0'+ (val));
}

/*void funcion(uint32_t entero) //función que imprime de a 2
{
	//entero = (entero & 0x0000000F);
	volatile uint8_t *p1 = &entero;
	uint32_t i;
	
	
	for(i = 0; i<4 ; i++){
		if (*p1 >= 0xA) 
			uart_putchar('A'+ (*p1) -10);
		else
			uart_putchar('0'+ (*p1));
		p1++;
	}
}*/
void newLine() //Realiza un salto de línea y retorno de carro en el minicom
{
	uart_putchar(0xA); //salto
	uart_putchar(0xD); //retorno de carro
}

void Set_Bit(  int reg, ///< The register to update. One of the PCD_Register enums.
               int mask ///< The bits to set.
            ) { 
  int tmp;
  tmp = readReg(reg);
  //writeintXX(tmp);
  writeReg(reg, tmp | mask);     // set bit mask
} // End PCD_Set_BitMask()

void Clear_Bit( int reg, ///< The register to update. One of the PCD_Register enums.
                int mask ///< The bits to clear.
                    ) {
  int tmp;
  tmp = readReg(reg);
  //writeintXX(tmp);
  writeReg(reg, tmp & (~mask));    // clear bit mask
} // End PCD_Clear_BitMask()

void initRFID()
{
	//INIT

	//RESET
	uart_putstr("Toca hacer soft_reset");
	writeReg(CommandReg, PCD_RESETPHASE);
	//FIN_RESET

	writeReg( TModeReg, 0x8D );      //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	writeReg( TPrescalerReg, 0x3E ); //TModeReg[3..0] + TPrescalerReg
	writeReg( TReloadRegL, 0x30 );           
	writeReg( TReloadRegH, 0x0 );//WWWWWWWWWARNING: colocar ambo ceros o revisar que hace el registro
	writeReg( TxAutoReg, 0x40 );    //100%ASK
	writeReg( ModeReg, 0x3D );

	//AntennaON
	Set_Bit( TxControlReg, 0x03 );

	//FIN_INIT
}

bool toCard(int *info, int lengthData)
{
	uint32_t i;
	char irqEn = 0x77;
	writeintXX(irqEn);//Serial.println(irqEn, HEX);
	writeReg( ComIEnReg, irqEn | 0x80 );
	newLine(); //SALTO
	Clear_Bit( ComIrqReg, 0x80 );
	Set_Bit( FIFOLevelReg, 0x80 );
	uart_putstr("Escribe: ");
	writeReg( CommandReg, PCD_IDLE );
	for(i = 0; i < lengthData; i++){		//Escribe en el RFID FIFORreg los datos de info
		writeReg(FIFODataReg, *info);
		writeintXX(*info);
		info++;
	}
	//writeReg( FIFODataReg, 0x26 ); // Ya lo hace el for
	writeReg( CommandReg, PCD_TRANSCEIVE );
	Set_Bit( BitFramingReg, 0x80 );
	newLine(); //SALTO
	//25ms revisando esto:
	char n;
	char waitIrq = 0x30;
	
	volatile uint32_t cont;
	
	bool flag = true;
	bool status = false;
	while(flag){
				
		uart_putstr("entro a verificar");//Serial.println("Entro a verificar");
		newLine();
		n = readReg( ComIrqReg );
		if(n & waitIrq){
			uart_putstr("ha cambiado algo");//Serial.println("ha cambiado algo");
			flag = false;
			status = true;
			newLine(); //SALTO
		}
		if(n & 0x01){
			uart_putstr("TIMEOUT, nada en 25ms");//Serial.println("TIMEOUT, nada en 25ms");
			flag=false;
			status = false;//RETURN
		}
		
		for(cont = 0; cont < 50; cont++);//{ //cont < 333334
			//writeint(cont);
			//newLine();
		
		flag = false;
		//delay(1);
	}
	flag=true;
	//uart_putstr("salio del ciclo");
	newLine(); //SALTO

	Clear_Bit( BitFramingReg, 0x80 );
	char lec;
	lec = readReg( ErrorReg);
	newLine(); //SALTO
	if( !( lec & 0x1B) ){
		writeintXX(lec);//Serial.println(lec, HEX);
		uart_putstr("status=MI_OK, todo va bien");//Serial.println("status=MI_OK, todo va bien");
		status = true;
		newLine(); //SALTO
	}
	if ( n & irqEn & 0x01 ){// WWWWWWWWARNING: Parece ser otra lectura de un posible error, pero pues
		uart_putstr("status=NOTAGERR, NO todo va bien");//
		status = false;//RETURN
		newLine(); //SALTO
	}
	n = readReg(FIFOLevelReg); //leer cantidad de datos
	uart_putstr("la cantidad de datos n a leer es: ");//Serial.print("la cantidad de datos n a leer es: ");
	writeintXX(n);
	uart_putstr("---------");//Serial.print(n, BIN); Serial.println("----");
	newLine(); //SALTO
	
	
	for(i=0 ;i < n; i++){   //WWWWWWWWWARNING: Tener en cuenta para la FPGA, colocar un if(n == 0) o algo asi, para evitar que lea inecesariamente si no hay datos que leer
		lec = readReg(FIFODataReg);
		uart_putstr(" Dato leido de FIFO: ");//Serial.print(" Dato leido de FIFO: ");
		writeintXX(lec);//Serial.print(lec, HEX);
		newLine(); //SALTO
	}
	uart_putstr("---------");//Serial.println("----");
	newLine(); //SALTO
	int validBits;
	validBits = readReg(ControlReg) & 0x07; //Ver nro de bits validos
	uart_putstr("Bits validos");//Serial.print("Bits validos");Serial.print(validBits, BIN);
	writeintXX(validBits);
	newLine();
	return status;
	//Serial.println();

	//FIN TO_CARD
}

bool isCard()
{
	int request[] = {0x26};
	bool status;
	//IS_CARD

	//REQUEST

	writeReg( BitFramingReg, 0x07 );

	status = toCard(&request, 1);
	return status;
	//FIN REQUEST
	//FIN IS_CARD
}

void getUIDCard()
{
	int UIDRead[] = {0x93, 0x20};
	//READ_CARD_SERIAL

	//ANTICOLL
	writeReg( BitFramingReg, 0x00 );
	Clear_Bit( Status2Reg, 0x08 );//WWWWWWWWARGNING: no presente en anterior ejemplo del cuaderno, tal vez puede ser omitido
	newLine(); //SALTO
	toCard(&UIDRead, 2);
	//FIN READ_CARD_SERIAL
}

char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;

volatile uint32_t AA = 0x0A;
volatile uint32_t BB = 0x0B;
volatile uint32_t mask = 0xBEAFA209;//0xBEAFA209
volatile uint32_t resul = 0x00;

char Ac = 'A';
char Bc = 'B';

extern uint32_t tic_msec;

int inicializar1 = 0b00000001100;
int inicializar2 = 0b00000010100;
int inicializar3 = 0b00001111100;
int inicializar4 = 0b00111100100;
int ubicarlinea2= 0b11000000100;
int A = 0b01000001101;
int B = 0b01000010101;
int C = 0b01000011101;
int D = 0b01000100101;
int E = 0b01000101101;
int F = 0b01000110101;
int G = 0b01000111101;
int H = 0b01001000101;
int I = 0b01001001101;
int J = 0b01001010101;
int K = 0b01001011101;
int L = 0b01001100101;
int M = 0b01001101101;
int N = 0b01001110101;
int O = 0b01001111101;
int P = 0b01011111101;
int Q = 0b01010001101;
int R = 0b01010010101;
int S = 0b01010011101;
int T = 0b01010100101;
int U = 0b01010101101;
int V = 0b01010110101;
int W = 0b01010111101;
int X = 0b01011000101;
int Y = 0b01011001101;
int Z = 0b01011010101;
int ESPACIO = 0b00010000101;

int main()
{
	while(1){
		int teclaoprimida = Leerteclado();
		writeint(teclaoprimida);
		if(teclaoprimida == 3){
			chooseRFID(0x00);
			initRFID();
			bool status = isCard();
			if( status == true){
				getUIDCard();
			}else{
				newLine();
				uart_putstr("NO hay tarjeta");
				newLine();
			}
		}else{
			uart_putstr("No se ha pulsado nada");
			newLine();
		}
	}
	/*
	while(1){
		
		int teclaoprimida = Leerteclado();
		if(teclaoprimida == 3){
			chooseRFID(0x00);
			initRFID();
			bool status = isCard();
			if( status == true){
				getUIDCard();
				uart_putstr("ya consiguió el UID");
				newLine();
				writelcd(15,inicializar1,inicializar2,inicializar3,X,ESPACIO,ESPACIO,ESPACIO,U,N,I,V,E,R,S,I,D,A,D,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,N,A,C,I,O,N,A,L,X,X,X,X,X,X,X,X,X,X);	
			}else{
				newLine();
				uart_putstr("NO hay tarjeta");
				newLine();
				writelcd(15,inicializar1,inicializar2,inicializar3,X,ESPACIO,ESPACIO,ESPACIO,N,O,ESPACIO,H,A,Y,X,X,X,X,X,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,N,A,C,I,O,N,A,L,X,X,X,X,X,X,X,X,X,X);
			}
		}else{
			newLine();
			uart_putstr("tecla incorrecta");
			uart_getchar();
		}
	}*/
			
						
			
	
	/*while(1){
		chooseRFID(0x00);
		initRFID();
		bool status = isCard();
		
		if( status == true){
			getUIDCard();
		}else{
			newLine();
			uart_putstr("NO hay tarjeta");
			newLine();
		}
		uart_putstr("hecho");
		newLine();
		//resul = readReg(FIFODataReg);
		//uart_putchar(0xA);
		//writeintXX(resul);
		//writeReg(TModeReg, 0x8B);
		char tecla = uart_getchar();
		uart_putchar(tecla);		
	}*/
	/* //RUTINA Pabon
	writelcd(1,inicializar1,inicializar2,inicializar3,inicializar4,ESPACIO,ESPACIO,ESPACIO,U,N,I,V,E,R,S,I,D,A,D,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,N,A,C,I,O,N,A,L,1,2,3,4,5,6,7,8,9,10);	
	Leerteclado();
	Leerteclado();
	Leerteclado();
	Leerteclado();
	Leerteclado();
	Leerteclado();
	Leerteclado();

	writelcd(1,1,3,5,5,6,8,9,0,N,I,V,E,R,S,I,D,A,D,ubicarlinea2,
			ESPACIO,ESPACIO,ESPACIO,N,A,C,I,O,N,A,L,1,2,3,4,5,6,7,8,9,10);
			
	*/
	
	
	/*while(1){
		uart_putstr("Comienza:");
		//resul = readReg(FIFODataReg);
		//writeint(resul);
		//writeintC(mask);
		volatile uint32_t i,j, digit; //Este For funciona(el de adentro tambien), y se ve correctamente los corrimientos
		digit = 0xFA340CBA;
		for (i=0; i<8; i++) {
			uart_putchar(digit);
			for(j=0; j<4; j++){
				digit >>= 4; //solo está corriendo un bit a la vez, sea cual sea el número que se coloque ahí
			}
		}*/
		
		//PRUEBA de que solo hace 1 corrimiento (1 bit a la vez)
		/*uint32_t i, digit;
		digit = 0xF00000BA;
	for (i=0; i<9; i++) {
		uart_putchar(digit);
		digit >>= 8; //solo está corriendo un bit a la vez
	}*/
		//writeReg(TModeReg, 0x8B);
		//char tecla = uart_getchar();
		//uart_putchar(tecla);}
	
	/*
	while(1){
	 
	 if(A & mask){
	 	uart_putstr( "A y mask1 \n" );
	 }else{
	 	uart_putstr( "A y mask0 \n" );
	 }
	 
	 if(B & mask){
	 	uart_putstr( "B y mask1 \n" );
	 }else{
	 	uart_putstr( "B y mask0 \n" );
	 }
	 uart_putchar(A + 55); //muestra la A. En ASCII A es 10(decimal) y sumando 55, genera el character A
	 uart_putchar(Ac);
	 uart_putchar(Bc);
	 //if(A & mask)
	 	//uart_put
	 char tecla = uart_getchar();
	 uart_putchar(tecla);
	 
	 writeReg(0x14, 0xA1);
	 uart_putstr( "written. ");
	 resul = readReg(0x22);
	 uart_putstr( "read: ");
	 uart_putchar(resul + 0);
	 
	}
	*/
	
	/*
	while(1){
	 char tecla = uart_getchar();
	 uart_putchar(tecla);
	}*/
	
	/*
	while(1){
	 char tecla = uart_getchar();
	 if(tecla == 'a'){
	   uart_putstr( "PAbon"+ "\n" );
	 }
	 if(tecla == 'n'){
	   uart_putstr( "Juan" +"\n"  );
	 }
	}
	*/
	
	/*
	volatile uint8_t *p;
	
	p = (uint8_t *)0x2000;
	*p = 0xf0f0;
	p++;
	*p = 0xe0e0;
	*/

	// Funcion get_char
	

/*    char test2[] = "Lokalerstr";
    char *str = test2;
    uint32_t i;
    
//    for (i = 0; i < 4; i++)
 //       test2[i] = 'l';
  //  glob[0]  = 'g';
	
	
    	
 	// Initialize stuff
	uart_init();

	// Say Hello!
	uart_putstr( "** Spike Test Firmware **\n" );

	// Initialize TIC
	isr_init();
	tic_init();
	irq_set_mask( 0x00000002 );
	irq_enable();

	// Say Hello!
	uart_putstr( "Timer Interrupt instelled.\n" );

	// Do some trivial tests
	uart_putstr( "Subroutine-Return Test: " );
	test();
	uart_putchar('\n');    

	uart_putstr( "Local-Pointer Test:" );
	for (;*str; str++) {
	   uart_putchar(*str);
	}
	uart_putchar('\n');    
	
	uart_putstr( "Global-Pointer Test:" );
	str = glob;
	for (;*str; str++) {
	   uart_putchar(*str);
	}
	uart_putchar('\n');    

	uart_putstr( "Stack Pointer : " );
	writeint(get_sp());
	uart_putchar('\n');    

	uart_putstr( "Global Pointer: " );
	writeint(get_gp());
	uart_putchar('\n');    

	uart_putstr( "Timer Test (1s): " );
	for(i=0; i<4; i++) {
		uart_putstr("tic...");    
		msleep(1000);
	}
	uart_putchar('\n');    

	uart_putstr( "Timer Interrupt counter: " );
	writeint( tic_msec );
	uart_putchar('\n');    

	int val = tic_msec;
	uart_putstr( "Shift: " );
	writeint( val );
	uart_putstr(" <-> ");    
	for(i=0; i<32; i++) {
		if (val & 0x80000000)
			uart_putchar( '1' );
		else
			uart_putchar( '0' );
			
		val <<= 1;
	}
	uart_putstr("\r\n");
	
	uart_putstr( "GPIO Test..." );
	gpio0->oe = 0x000000ff;
	for(;;) {
		for(i=0; i<8; i++) {
			uint32_t out1, out2;

			out1 = 0x01 << i;
			out2 = 0x80 >> i;
			gpio0->out = out1 | out2;

			msleep(100);
		}
	}



	uart_putstr( "Memory Dump: " );
	uint32_t *start = (uint32_t *)0x40000000;
	uint32_t *end   = (uint32_t *)0x40000100;
	uint32_t *p;
	for (p=start; p<end; p++) {
		if (((uint32_t)p & 12) == 0) {
			uart_putstr("\r\n[");
			writeint((uint32_t) p);
			uart_putchar(']');    
		}

		uart_putchar(' ');    
		writeint(*p);
	}


	uart_putstr("Entering Echo Test...\n");
	while (1) {
	   uart_putchar(uart_getchar());
	}
*/
}

