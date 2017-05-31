/**
 * 
 */

#include "soc-hw.h"

inline void writeintB(volatile uint32_t val)
{
	uint32_t i, j;
	volatile uint32_t digit;

	for (i=0; i<8; i++) {
		digit = (val & 0xF0000000);
		for(j=0; j<28; j++){
			digit >>= 28;
		}
		if (digit >= 0xA) {
			uart_putchar('A'+digit-10);//uart_putchar('Y');
			}
		else{
			uart_putchar('0'+digit);//uart_putchar('N');
		for(j=0; j<4; j++){
			val <<= 4;
		}
		
		}
	}
}

inline void writeintC(uint32_t val)
{
	uint32_t i, digit;

	for (i=0; i<8; i++) {
		digit = (val & 0xF0000000) >> 28;
		if (digit >= 0xA) 
			uart_putchar('A'+digit-10);
		else
			uart_putchar('0'+digit);
		val <<= 4;
	}
}

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
	volatile uint8_t *p1 = &entero;
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
	volatile uint8_t *p1 = &entero;
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
void test2() {
    uart_putchar('b');   
}

void test() {
    uart_putchar('a');
    test2();
    uart_putchar('c');
} 

void Set_Bit(  int reg, ///< The register to update. One of the PCD_Register enums.
               int mask ///< The bits to set.
            ) { 
  int tmp;
  tmp = readReg(reg);
  writeintXX(tmp);
  writeReg(reg, tmp | mask);     // set bit mask
} // End PCD_Set_BitMask()

void Clear_Bit( int reg, ///< The register to update. One of the PCD_Register enums.
                int mask ///< The bits to clear.
                    ) {
  int tmp;
  tmp = readReg(reg);
  writeintXX(tmp);
  writeReg(reg, tmp & (~mask));    // clear bit mask
} // End PCD_Clear_BitMask()

void init()
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

void newLine() //Realiza un salto de línea y retorno de carro en el minicom
{
	uart_putchar(0xA); //salto
	uart_putchar(0xD); //retorno de carro
}
char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;

volatile uint32_t A = 0x0A;
volatile uint32_t B = 0x0B;
volatile uint32_t mask = 0xBEAFA209;//0xBEAFA209
volatile uint32_t resul = 0x00;
volatile uint32_t cont;
char Ac = 'A';
char Bc = 'B';

extern uint32_t tic_msec;

int main()
{
	init();
	while(1){
		
		
		//IS_CARD
		
		//REQUEST
		
		writeReg( BitFramingReg, 0x07 );

		//TO_CARD

		char irqEn = 0x77;
		writeintXX(irqEn);//Serial.println(irqEn, HEX);
		writeReg( ComIEnReg, irqEn | 0x80 );
		newLine(); //SALTO
		Clear_Bit( ComIrqReg, 0x80 );
		Set_Bit( FIFOLevelReg, 0x80 );
		writeReg( CommandReg, PCD_IDLE );
		writeReg( FIFODataReg, 0x26 ); //EScribiendo
		writeReg( CommandReg, PCD_TRANSCEIVE );
		Set_Bit( BitFramingReg, 0x80 );
		newLine(); //SALTO
		//25ms revisando esto:
		char n;
		char waitIrq = 0x30;
		
		
		
		bool flag = true;
		while(flag){
			uart_putstr("entro a verificar");//Serial.println("Entro a verificar");
			n = readReg( ComIrqReg );
			if(n & waitIrq){
				uart_putstr("ha cambiado algo");//Serial.println("ha cambiado algo");
				flag = false;
				newLine(); //SALTO
			}
			if(n & 0x01){
				uart_putstr("TIMEOUT, nada en 25ms");//Serial.println("TIMEOUT, nada en 25ms");
				flag=false;
			}
			for(cont = 0; cont < 333334; cont++);
			//delay(1);
		}
		flag=true;

		Clear_Bit( BitFramingReg, 0x80 );
		char lec;
		lec = readReg( ErrorReg);
		newLine(); //SALTO
		if( !( lec & 0x1B) ){
			writeintXX(lec);//Serial.println(lec, HEX);
			uart_putstr("status=MI_OK, todo va bien");//Serial.println("status=MI_OK, todo va bien");
			newLine(); //SALTO
		if ( n & irqEn & 0x01 )// WWWWWWWWARNING: Parece ser otra lectura de un posible error, pero pues
			uart_putstr("status=NOTAGERR, NO todo va bien");//Serial.println("status=NOTAGERR, NO todo va bien");
			newLine(); //SALTO
		}
		n = readReg(FIFOLevelReg); //leer cantidad de datos
		uart_putstr("la cantidad de datos n a leer es: ");//Serial.print("la cantidad de datos n a leer es: ");
		uart_putstr("---------");//Serial.print(n, BIN); Serial.println("----");
		newLine(); //SALTO
		
		uint32_t i;
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
		//Serial.println();

		//FIN TO_CARD
		//FIN REQUEST
		//FIN IS_CARD

		//READ_CARD_SERIAL

		//ANTICOLL
		writeReg( BitFramingReg, 0x00 );
		Clear_Bit( Status2Reg, 0x08 );//WWWWWWWWARGNING: no presente en anterior ejemplo del cuaderno, tal vez puede ser omitido
		newLine(); //SALTO
		//TO_CARD

		//char irqEn = 0x77;
		//Serial.println(irqEn, HEX);
		writeReg( ComIEnReg, irqEn | 0x80 );
		Clear_Bit( ComIrqReg, 0x80 );
		Set_Bit( FIFOLevelReg, 0x80 );
		writeReg( CommandReg, PCD_IDLE );
		writeReg( FIFODataReg, 0x93 ); //EScribiendo PICC_ANTICOLL
		writeReg( FIFODataReg, 0x20 ); //EScribiendo NVB
		writeReg( CommandReg, PCD_TRANSCEIVE );
		Set_Bit( BitFramingReg, 0x80 );
		
		newLine(); //SALTO
		//25ms revisando esto:
		//char n;
		//char waitIrq = 0x30;


		//bool flag = false;
		while(flag){
			uart_putstr("entro a verificar");//Serial.println("Entro a verificar");
			n = readReg( ComIrqReg );
			if(n & waitIrq){
				uart_putstr("ha cambiado algo");//Serial.println("ha cambiado algo");
				flag = false;
				newLine(); //SALTO
			}
			if(n & 0x01){
				uart_putstr("TIMEOUT, nada en 25ms");//Serial.println("TIMEOUT, nada en 25ms");
				flag=false;
			}
			for(cont = 0; cont < 333334; cont++);
			//delay(1);
		}
		flag=true;
		newLine(); //SALTO

		Clear_Bit( BitFramingReg, 0x80 );
		//char lec;
		lec = readReg( ErrorReg);		
		if( !( lec & 0x1B) ){
			writeintXX(lec);//Serial.println(lec, HEX);
			uart_putstr("status=MI_OK, todo va bien");//Serial.println("status=MI_OK, todo va bien");
			newLine(); //SALTO
		if ( n & irqEn & 0x01 )// WWWWWWWWARNING: Parece ser otra lectura de un posible error, pero pues
			uart_putstr("status=NOTAGERR, NO todo va bien");//Serial.println("status=NOTAGERR, NO todo va bien");
			newLine(); //SALTO
		}
		n = readReg(FIFOLevelReg); //leer cantidad de datos
		uart_putstr("la cantidad de datos n a leer es: ");//Serial.print("la cantidad de datos n a leer es: ");
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
		validBits = readReg(ControlReg) & 0x07; //Ver nro de bits validos
		uart_putstr("Bits validos");//Serial.print("Bits validos");Serial.print(validBits, BIN);
		writeintXX(validBits);
		newLine();
		
		//FIN TO_CARD

		//FIN READ_CARD_SERIAL
	
		//writeint(resul);
		//writeint(mask);
		uart_putstr("hecho");
		newLine();
		//resul = readReg(FIFODataReg);
		//uart_putchar(0xA);
		//writeintXX(resul);
		//writeReg(TModeReg, 0x8B);
		char tecla = uart_getchar();
		uart_putchar(tecla);
	}

	/*while(1){
		uart_putstr("Comienza:");
		//resul = readReg(FIFODataReg);
		//writeint(resul);
		//writeintC(mask);
		/*volatile uint32_t i,j, digit; //Este For funciona(el de adentro tambien), y se ve correctamente los corrimientos
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


/*
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

