/**
 * 
 */

#include "soc-hw.h"
///////// los siguientes métodos son los necesariós para escribir sobre la LCD haciendo el corrimiento para dar paso al siguiente carácter
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
			uart_putchar('A'+digit-10);  //uart_putchar('Y');
			}
		else{
			uart_putchar('0'+digit);  //uart_putchar('N');
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
//////////////////////////////////////////////////////////////
//Esta función permite escribir en la UART, de manera hexadecimal, un numero entero por lo que es la función que escribe sobre el display.
///////////////////////////////////////////////////////////////

void writeint(uint32_t entero) 
{
	//entero = (entero & 0x0000000F);
	volatile uint8_t *p1 = &entero;
	uint32_t i,j;
	
	volatile uint8_t val;
	
	for(i = 0; i<4 ; i++){ 
		val = *p1;
		for(j=0; j<4; j++)
		{
			val = val>>4; //corrimiento de 4 BITS para dar paso a la siguiente letra o número.
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

////////////////////////Esta función permite escribir en la UART, de manera hexadecimal, los primeros 8 bits de un número entero
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

/*void funcion(uint32_t entero)
 ////////////////función que imprime de a 2 no fue necesario implementarlo ////////////////////////////////////////////
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







//Libreria en el uso del teclado en donde se entrelazan la comunicación por hexádecimal y se tiene como respuesta el carriage return que corresponde a la tecla oprimida.
////////////////////// No se utilizó /////////////////////////////
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

void newLine() //Realiza un salto de línea y Carriage Return en el minicom (Minicom es método de escritura para plataformas UNIX)
{
	uart_putchar(0xA); //salto
	uart_putchar(0xD); // Carriage return (retorno de carro)
}

//Método para iniciar la comunicación por SPI configurando frecuencia de Reloj.
void initRFID(
{
	//INIT

	//RESET
	uart_putstr("Toca hacer soft_reset");
	writeReg(CommandReg, PCD_RESETPHASE);
	//FIN_RESET

	writeReg( TModeReg, 0x8D );      //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	writeReg( TPrescalerReg, 0x3E ); //TModeReg[3..0] + TPrescalerReg
	writeReg( TReloadRegL, 0x30 );           
	writeReg( TReloadRegH, 0x0 ); // Se corrobora que el registro se encuentre en $0 
	writeReg( TxAutoReg, 0x40 );    //100%ASK
	writeReg( ModeReg, 0x3D );

	//AntennaON
	Set_Bit( TxControlReg, 0x03 );

	//FIN de INITRFID
}

bool toCard(int *info, int lengthData, int ID0, int ID1, int ID2, int ID3)
{
	uint32_t i;
	char irqEn = 0x77;
	writeintXX(irqEn);
	//Serial.println(irqEn, HEX);
	writeReg( ComIEnReg, irqEn | 0x80 );
	newLine(); ///// SALTO
	Clear_Bit( ComIrqReg, 0x80 );
	Set_Bit( FIFOLevelReg, 0x80 );
	uart_putstr("Escribe: ");
	writeReg( CommandReg, PCD_IDLE );
	for(i = 0; i < lengthData; i++){		//Escribe en el RFID FIFORreg los datos de info
		writeReg(FIFODataReg, *info);
		writeintXX(*info);
		info++;
	}
	//writeReg( FIFODataReg, 0x26 ); //EScribiendo
	writeReg( CommandReg, PCD_TRANSCEIVE );
	Set_Bit( BitFramingReg, 0x80 );
	newLine(); ////////SALTO
	//25ms revisando esto:
	char n;
	char waitIrq = 0x30;
	
	volatile uint32_t cont;
	
	bool flag = true;
	bool status = false;
	while(flag){
				
		uart_putstr("entro a verificar");
		//Serial.println("Entro a verificar");
		newLine();
		n = readReg( ComIrqReg );
		if(n & waitIrq){
			uart_putstr("ha cambiado algo");
			//Serial.println("ha cambiado algo");
			flag = false;
			status = true;
			newLine(); //SALTO
		}
		if(n & 0x01){
			uart_putstr("TIMEOUT, nada en 25ms");
			//Serial.println("TIMEOUT, nada en 25ms");
			flag=false;
			status = false;//RETURN
		}
		if(cont == 1000){
			uart_putstr("terminó de contar");
			flag = false;
			status = false;
		}
		cont = cont + 1;

		newLine();
		
	}
	flag=true;
	newLine(); //// SALTO

	Clear_Bit( BitFramingReg, 0x80 );
	char lec;
	lec = readReg( ErrorReg);
	newLine(); //SALTO
	if( !( lec & 0x1B) ){
		writeintXX(lec);//Serial.println(lec, HEX);
		uart_putstr("status=MI_OK, todo va bien");//Serial.println("status=MI_OK, todo va bien");
		newLine(); //SALTO
	
		if ( n & irqEn & 0x01 ){
			uart_putstr("status=NOTAGERR, NO todo va bien");//
			status = false;//RETURN
			newLine(); //SALTO
			return status;
		}
	}
	n = readReg(FIFOLevelReg); 
	uart_putstr("la cantidad de datos n a leer es: ");
	writeintXX(n);
	uart_putstr("---------");
	newLine(); //SALTO
	
	
	for(i=0 ;i < n; i++){   //Cuidado: Tener en cuenta para la FPGA, colocar un if(n == 0) o algo parecido, es para evitar que lea inecesariamente si no hay datos que leer.
		lec = readReg(FIFODataReg);
		if(i==0){
		ID0=lec;
		}
		if(i==1){
		ID1=lec;
		}
		if(i==2){
		ID2=lec;
		}
		if(i==3){
		ID3=lec;
		}
		uart_putstr(" Dato leido de FIFO: ");
		writeintXX(lec);
		newLine(); //SALTO
	}
	uart_putstr("---------");
	newLine(); //SALTO
	int validBits;
	validBits = readReg(ControlReg) & 0x07; 
	uart_putstr("Bits validos");
	writeintXX(validBits);
	newLine();
	return status;

	//FIN TO_CARD
}

bool isCard()
{
int x;
	int request[] = {0x26};
	bool status;
	//Variable para mostrar el estado del lector IS_CARD 

	//Petición de lectura si se pone una tarjeta sobre el lector.

	writeReg( BitFramingReg, 0x07 );

	status = toCard(&request, 1,x,x,x,x);
	return status;
	//FIN REQUEST
	//FIN IS_CARD
}

int* getUIDCard()
{
int ID0;
int ID1;
int ID2;
int ID3;


	int UIDRead[] = {0x93, 0x20};
	//Dentro del array podemos almacenar el ID de la tarjeta READ_CARD_SERIAL

	writeReg( BitFramingReg, 0x00 );
	Clear_Bit( Status2Reg, 0x08 );
	newLine(); /////////SALTO
	toCard(&UIDRead, 2,ID0, ID1, ID2, ID3);
	
	int identificacion[4] = {ID0, ID1, ID2, ID3};
        int *p=identificacion;
	return p;
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
// Se dan los valores de carácteres según el código Binario para escribir sobre el diplay 
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
		if(teclaoprimida == 3){
			chooseRFID(0x00);
			initRFID();
			bool status = isCard();
			if( status == true){
				getUIDCard();
				writelcd(19,inicializar1,inicializar2,inicializar3,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,S,I,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,1,2,3,4,5,6,7,8,9,10);	// 19 es el número total de instrucciones a ejecutar y se dan los carácteres que se quieren mostrar en el Display.
			}else{
				writelcd(19,inicializar1,inicializar2,inicializar3,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,N,O, ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,1,2,3,4,5,6,7,8,9,10);	
			}
		}else{
			writelcd(19,inicializar1,inicializar2,inicializar3,ESPACIO,ESPACIO,ESPACIO,ESPACIO,N,O,ESPACIO,T,E,C,L,A,ESPACIO,ESPACIO,ESPACIO,ubicarlinea2, ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,1,2,3,4,5,6,7,8,9,10);	
		}
	}

}

