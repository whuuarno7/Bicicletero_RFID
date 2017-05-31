#include "soc-hw.h"

uart_t   *uart0  = (uart_t *)   0x20000000;
timer_t  *timer0 = (timer_t *)  0x30000000;
gpio_t   *gpio0  = (gpio_t *)   0x40000000;
SPI_t		*SPI0	  = (SPI_t *)	  0x50000000;
LCD_t	 *LCD0	 = (LCD_t *)         0x60000000;
Teclado_t *Teclado0 = (Teclado_t *) 0x70000000;   

isr_ptr_t isr_table[32];


void tic_isr();
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}

/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	isr_register(1, &tic_isr);
}


/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ; //Se queda esperando a que haya un 1 en rx_avail.
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY); //si ucr muestra un 1 (ART_BUSY), entonces queda en el while siempre. Sale cuando no está ocupado
	uart0->rxtx = c; //COMO carajos envia c al wb_data_i. O mejor dicho, rxtx que es como tal.
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}
/********************************************************************
// SPI functions
Formato address: Bits: 
[7] = 1 para leer
	 =	0 para escribir
[6:1] = address del registro
[0] = siempre es cero

*/
void writeReg(int addressReg, int data_Wr)
{
	addressReg = addressReg & 0x7E;//0111 1110
	SPI0->address = addressReg;
	SPI0->dataWr = data_Wr;
	while(SPI0->status & 0x01);
}

int readReg(int addressReg)
{
	addressReg = (addressReg & 0x7E) | 0x80;//(0111 1110 & address) | 1000 0000
	SPI0->address = addressReg;
	while(SPI0->status & 0x01);
	return SPI0->dataRd;
}

void chooseRFID(int numberRFID)
{
	SPI0->chipSelect = numberRFID;
}

/**************************************************************************/

////FUNCIONES LCD

void writelcd(int numeroInstrucciones, int reg0, int reg1, int reg2, int reg3, int reg4, int reg5, int reg6, int reg7, int reg8, int reg9, int reg10, int reg11, int reg12, int reg13, int reg14, int reg15, int reg16, int reg17, int reg18, int reg19, int reg20, int reg21, int reg22, int reg23, int reg24, int reg25, int reg26, int reg27, int reg28, int reg29, int reg30, int reg31, int reg32, int reg33, int reg34, int reg35, int reg36, int reg37, int reg38, int reg39)
{     
      LCD0->numeroInstrucciones=numeroInstrucciones;
      LCD0->instruccion0=reg0;
      LCD0->instruccion1=reg1;
      LCD0->instruccion2=reg2;
      LCD0->instruccion3=reg3;
      LCD0->instruccion4=reg4;
      LCD0->instruccion5=reg5;
      LCD0->instruccion6=reg6;
      LCD0->instruccion7=reg7;
      LCD0->instruccion8=reg8;
      LCD0->instruccion9=reg9;
      LCD0->instruccion10=reg10;
      LCD0->instruccion11=reg11;
      LCD0->instruccion12=reg12;
      LCD0->instruccion13=reg13;
      LCD0->instruccion14=reg14;
      LCD0->instruccion15=reg15;
      LCD0->instruccion16=reg16;
      LCD0->instruccion17=reg17;
      LCD0->instruccion18=reg18;
      LCD0->instruccion19=reg19;
      LCD0->instruccion20=reg20;
      LCD0->instruccion21=reg21;
      LCD0->instruccion22=reg22;
      LCD0->instruccion23=reg23;
      LCD0->instruccion24=reg24;
      LCD0->instruccion25=reg25;
      LCD0->instruccion26=reg26;
      LCD0->instruccion27=reg27;
      LCD0->instruccion28=reg28;
      LCD0->instruccion29=reg29;
      LCD0->instruccion30=reg30;
      LCD0->instruccion31=reg31;
      LCD0->instruccion32=reg32;
      LCD0->instruccion33=reg33;
      LCD0->instruccion34=reg34;
      LCD0->instruccion35=reg35;
      LCD0->instruccion36=reg36;
      LCD0->instruccion37=reg37;
      LCD0->instruccion38=reg38;
      LCD0->instruccion39=reg39;
      LCD0->init=1;
      LCD0->init=0;
      
}
////////////////////////////////////////

//Teclado functions

int Leerteclado()
{
	return Teclado0->teclaoprimida;	
}
/////////////////////////////////////////


