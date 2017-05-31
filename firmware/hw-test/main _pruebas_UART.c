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
	uint32_t i,j;
	
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

char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;

volatile uint32_t A = 0x0A;
volatile uint32_t B = 0x0B;
volatile uint32_t mask = 0xBEAFA209;//0xBEAFA209
volatile uint32_t resul = 0x00;

char Ac = 'A';
char Bc = 'B';

extern uint32_t tic_msec;

int main()
{
	//INIT
	
	while(1){
		//writeint(resul);
		//writeint(mask);
		uart_putstr("comienza:");
		uart_putchar(0xA); //salto
		resul = readReg(FIFODataReg);
		uart_putchar(0xA);
		writeintXX(resul);
		writeReg(TModeReg, 0x8B);
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

