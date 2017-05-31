#ifndef SPIKEHW_H

#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x800
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x40000000

#define FCPU      50000000

#define UART_RXBUFSIZE 32

/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit
typedef unsigned   short   uint16_t;    // 16 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit
typedef enum {false, true} bool;   //definir bool

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_t;

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t ctrl;
	volatile uint32_t dummy1;
	volatile uint32_t dummy2;
	volatile uint32_t dummy3;
	volatile uint32_t in;
	volatile uint32_t out;
	volatile uint32_t oe;
} gpio_t;

/***************************************************************************
 * LCD0
 */
typedef struct {
        volatile uint16_t init;
        volatile uint16_t numeroInstrucciones;
	volatile uint16_t instruccion0;
	volatile uint16_t instruccion1;
	volatile uint16_t instruccion2;
	volatile uint16_t instruccion3;
	volatile uint16_t instruccion4;
	volatile uint16_t instruccion5;
	volatile uint16_t instruccion6;
	volatile uint16_t instruccion7;
	volatile uint16_t instruccion8;
	volatile uint16_t instruccion9;
	volatile uint16_t instruccion10;
	volatile uint16_t instruccion11;
	volatile uint16_t instruccion12;
	volatile uint16_t instruccion13;
	volatile uint16_t instruccion14;
	volatile uint16_t instruccion15;
	volatile uint16_t instruccion16;
	volatile uint16_t instruccion17;
	volatile uint16_t instruccion18;
	volatile uint16_t instruccion19;
	volatile uint16_t instruccion20;
	volatile uint16_t instruccion21;
	volatile uint16_t instruccion22;
	volatile uint16_t instruccion23;
	volatile uint16_t instruccion24;
	volatile uint16_t instruccion25;
	volatile uint16_t instruccion26;
	volatile uint16_t instruccion27;
	volatile uint16_t instruccion28;
	volatile uint16_t instruccion29;
   volatile uint16_t instruccion30;
	volatile uint16_t instruccion31;
	volatile uint16_t instruccion32;
	volatile uint16_t instruccion33;
	volatile uint16_t instruccion34;
	volatile uint16_t instruccion35;
	volatile uint16_t instruccion36;
	volatile uint16_t instruccion37;
	volatile uint16_t instruccion38;
	volatile uint16_t instruccion39;			
} LCD_t;

void writelcd(int numeroInstrucciones, int reg0, int reg1, int reg2, int reg3, int reg4, int reg5, int reg6, int reg7, int reg8, int reg9, int reg10, int reg11, int reg12, int reg13, int reg14, int reg15, int reg16, int reg17, int reg18, int reg19, int reg20, int reg21, int reg22, int reg23, int reg24, int reg25, int reg26, int reg27, int reg28, int reg29, int reg30, int reg31, int reg32, int reg33, int reg34, int reg35, int reg36, int reg37, int reg38, int reg39);




/***************************************************************************
*TECLADO
 */
typedef struct {
   volatile uint32_t teclaoprimida;
} Teclado_t;   	

int Leerteclado();

/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();

/***************************************************************************
 * SPI
 */
 
//MF522 Command word
#define PCD_IDLE              0x00               //NO action; Cancel the current command
#define PCD_AUTHENT           0x0E               //Authentication Key
#define PCD_RECEIVE           0x08               //Receive Data
#define PCD_TRANSMIT          0x04               //Transmit data
#define PCD_TRANSCEIVE        0x0C               //Transmit and receive data,
#define PCD_RESETPHASE        0x0F               //Reset
#define PCD_CALCCRC           0x03               //CRC Calculate

  // Page 0: Command and status
#define    CommandReg       0x01 << 1  // starts and stops command execution
#define    ComIEnReg        0x02 << 1  // enable and disable interrupt request control bits
#define    DivIEnReg        0x03 << 1  // enable and disable interrupt request control bits
#define    ComIrqReg        0x04 << 1  // interrupt request bits
#define    DivIrqReg        0x05 << 1  // interrupt request bits
#define    ErrorReg         0x06 << 1  // error bits showing the error status of the last command executed 
#define    Status1Reg         0x07 << 1  // communication status bits
#define    Status2Reg         0x08 << 1  // receiver and transmitter status bits
#define    FIFODataReg        0x09 << 1  // input and output of 64 byte FIFO buffer
#define    FIFOLevelReg       0x0A << 1  // number of bytes stored in the FIFO buffer
#define    WaterLevelReg      0x0B << 1  // level for FIFO underflow and overflow warning
#define    ControlReg         0x0C << 1  // miscellaneous control registers
#define    BitFramingReg      0x0D << 1  // adjustments for bit-oriented frames
#define    CollReg          0x0E << 1  // bit position of the first bit-collision detected on the RF interface
    //              0x0F      // reserved for future use
    
    // Page 1: Command
    //              0x10      // reserved for future use
#define    ModeReg          0x11 << 1  // defines general modes for transmitting and receiving 
#define    TxModeReg        0x12 << 1  // defines transmission data rate and framing
#define    RxModeReg        0x13 << 1  // defines reception data rate and framing
#define    TxControlReg     0x14 << 1  // controls the logical behavior of the antenna driver pins TX1 and TX2
#define    TxAutoReg         0x15 << 1  // controls the setting of the transmission modulation
#define    TxSelReg         0x16 << 1  // selects the internal sources for the antenna driver
#define    RxSelReg         0x17 << 1  // selects internal receiver settings
#define    RxThresholdReg   0x18 << 1  // selects thresholds for the bit decoder
#define    DemodReg         0x19 << 1  // defines demodulator settings
    //              0x1A      // reserved for future use
    //              0x1B      // reserved for future use
#define    MfTxReg          0x1C << 1  // controls some MIFARE communication transmit parameters
#define    MfRxReg          0x1D << 1  // controls some MIFARE communication receive parameters
    //              0x1E      // reserved for future use
#define    SerialSpeedReg   0x1F << 1  // selects the speed of the serial UART interface
    
    // Page 2: Configuration
    //              0x20      // reserved for future use
#define    CRCResultRegH    0x21 << 1  // shows the MSB and LSB values of the CRC calculation
#define    CRCResultRegL    0x22 << 1
    //              0x23      // reserved for future use
#define    ModWidthReg      0x24 << 1  // controls the ModWidth setting?
    //              0x25      // reserved for future use
#define    RFCfgReg         0x26 << 1  // configures the receiver gain
#define    GsNReg           0x27 << 1  // selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
#define    CWGsPReg         0x28 << 1  // defines the conductance of the p-driver output during periods of no modulation
#define    ModGsPReg        0x29 << 1  // defines the conductance of the p-driver output during periods of modulation
#define    TModeReg         0x2A << 1  // defines settings for the internal timer
#define    TPrescalerReg    0x2B << 1  // the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define    TReloadRegH      0x2C << 1  // defines the 16-bit timer reload value
#define    TReloadRegL      0x2D << 1
#define    TCounterValueRegH    0x2E << 1  // shows the 16-bit timer value
#define    TCounterValueRegL    0x2F << 1
    
    // Page 3: Test Registers
    //              0x30      // reserved for future use
#define    TestSel1Reg        0x31 << 1  // general test signal configuration
#define    TestSel2Reg        0x32 << 1  // general test signal configuration
#define    TestPinEnReg       0x33 << 1  // enables pin output driver on pins D1 to D7
#define    TestPinValueReg    0x34 << 1  // defines the values for D1 to D7 when it is used as an I/O bus
#define    TestBusReg         0x35 << 1  // shows the status of the internal test bus
#define    AutoTestReg        0x36 << 1  // controls the digital self test
#define    VersionReg         0x37 << 1  // shows the software version
#define    AnalogTestReg      0x38 << 1  // controls the pins AUX1 and AUX2
#define    TestDAC1Reg        0x39 << 1  // defines the test value for TestDAC1
#define    TestDAC2Reg        0x3A << 1  // defines the test value for TestDAC2
#define    TestADCReg         0x3B << 1   // shows the value of ADC I and Q channels

typedef struct {
	volatile uint32_t dataRd;
	volatile uint32_t address;
	volatile uint32_t dataWr;
	volatile uint32_t status;
	volatile uint32_t chipSelect;
} SPI_t;

void writeReg(int addressReg, int data_Wr);
int readReg(int addressReg);
void chooseRFID(int numberRFID);

/***************************************************************************
 * Pointer to actual components
 */
extern timer_t  *timer0;
extern uart_t   *uart0; 
extern gpio_t   *gpio0; 
extern SPI_t	 *SPI0;
extern LCD_t	 *LCD0;
extern Teclado_t *Teclado0;
extern uint32_t *sram0;  

#endif // SPIKEHW_H
