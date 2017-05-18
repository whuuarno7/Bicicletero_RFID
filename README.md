# Bicicletero_RFID




# INDICE:


1. Problema.
2. Requerimientos del proyecto.
3. Kit de llvero RFID.
4. Especifiaciones técnicas.
5. Características tarjeta.
6. Características llavero.
7. Diagrama de flujo general
8. Perifericos
9. SPI 




# SISTEMA DE ALARMA PARA BICICLETAS

PROBLEMA: El problema que se busca mitigar con el desarrollo de este proyecto, es el robo de bicicletas en un entorno como el de la Universidad Nacional sede Bogotá, la idea es brindar un sistema que permita dar una alarma rápida cuando se intente retirar del sitio de parqueo las bicicletas. Para ello se usará un tag RFID adherido a la bicicleta que será censado por un lector RFID ubicado en el sitio de parqueo de la bicicleta. Para retirar la bicicleta, será necesario que el usuario, pase por un panel (otro lector RFID) otro tag que estará vinvulado con el que está adherido a su bicicleta.

# Requerimientos del proyecto:

1- Censado de la bicicleta (Lector RFID)

2- Alarma sonora o visual.

3- Sistema de visualización parqueadero ocupado o no.

4- Teclado de para el ingreso de una TAG.

Propuestas de dispositivos iniciales:


# KIT DE LLAVERO RFID

Este kit incluye todo lo necesario para hacer uso de la tecnología RFID con la cual podrás controlar dispositivos usando tarjetas de proximidad usando la interfaz SPI a 3.3V.

# Especificaciones técnicas
Referencia chip: MFRC522
Soporta tarjetas tipo: mifare1 S50, mifare1 S70, Mifare UltraLight, Mifare Pro, Mifare DESFire
Corriente de operación 13-26mA / DC 3.3V
Corriente máxima: <30mA
Protocolo RF: ISO14443A
Dimensiones: 6 x 4 x 1 cm
Color: Azul
Peso: 350 g

# Características tarjeta
Frecuencia de operación: 13.56MHz
Velocidad de comunicación: 106KBPS
Temperatura de operación: -20 ~ 50 ¿
Distancia de lectura/escritura : ≤ 10 cm
Capacidad de sobreescritura: > 100.000 veces
Capacidad de lectura: ilimitada

# Características llavero
Frecuencia de operación: 13.56MHz
Velocidad de comunicación: 106KBPS
Capacidad: 8KB EEPROM
Chip: Philips Mifare 1 S50
Distancia de lectura/escritura : 2.5 ~ 10 cm
Tiempo de lectura/escritura : 1 ~ 2 ms
Temperatura de operación: -20 ~ 85 ¿
Capacidad de sobreescritura: > 100.000 veces








http://articulo.mercadolibre.com.co/MCO-434449516-kit-rfid-rc522-con-lector-llavero-y-tarjeta-para-arduino-_JM







# Diagrama de flujo general



Cuando la bicicleta sea estacionada en un lugar libre del bicicletero, se empieza el censado por parte del sensor RFID, además se enciende un led rojo. Si se deja de censar la bicicleta, se observa si se ha presentado la tarjeta de indentificación en el panel 
del bicicletero, si no se ha presentado se activa la alarma, si si se ha presentado se desactiva el censado y se activa un led verde, que indica que puede ser retirada la bicicleta. 

![diagrama de bloques general](https://cloud.githubusercontent.com/assets/25775237/26181044/8bcd164e-3b32-11e7-90b0-4669b16d351d.png)










# Perifericos

En el diagrama de bloques podemos observar los perifericos qa utilizar y los protocolos .A traves del protocolo spi se deben cumplir dos funciones ,lectura y autentificación .El protocolo Gpio activara un led rojo o verde dependiendo del sensado de la bicicleta y un buzzer.  


![lm32 y perifericos](https://cloud.githubusercontent.com/assets/25775237/26181045/8bdaa11a-3b32-11e7-9549-793cb6322d57.png)



# SPI 


Este periférico es utilizado para la comunicación con el sensor RFID para dos propósitos, ingresar a la base de datos un nuevo usuario (carnet o TAG cualquiera), o bien para retirar una bicicleta, lo cual se hace acaercando el carnet o TAG a el sensor que estará ubicado en el tablero del dispositivo.




### Diagrama de flujo spi.
![diagrama de flujo spi](https://cloud.githubusercontent.com/assets/25775237/26180686/64e92948-3b30-11e7-9e22-26bd38b93d83.png)

### Diagrama de máquina de estados spi.

![diagrama de maquina de estados spi](https://cloud.githubusercontent.com/assets/25775237/26180683/64dc28ce-3b30-11e7-8c59-8d0429968ab9.png)

### Diagrama de caja spi.
![diagrama de caja spi](https://cloud.githubusercontent.com/assets/25775237/26180685/64e5f2c8-3b30-11e7-86ea-7950d9c388c2.png)

### Datapath spi.
![datapath spi](https://cloud.githubusercontent.com/assets/25775237/26180684/64df23bc-3b30-11e7-9d09-196bd3b4e8e8.png)



# MISO
### Diagrama de flujo miso.

![diagrama de flujo miso](https://cloud.githubusercontent.com/assets/25775237/26180688/65768f9a-3b30-11e7-9c4e-6a88c4dcd18c.png)

### Diagrama de caja miso.

![diagrama de caja miso](https://cloud.githubusercontent.com/assets/25775237/26180681/64bded8c-3b30-11e7-8189-788a81ef2653.png)

### Datapah miso.

![datapath miso](https://cloud.githubusercontent.com/assets/25775237/26180679/64b3ebd4-3b30-11e7-8bd7-f88e74870154.png)



# MOSI


### Diagrama de flujo mosi.
![diagrama de flujo mosi](https://cloud.githubusercontent.com/assets/25775237/26180689/6594b0ba-3b30-11e7-8b29-2d8effe1d90c.png)

### Diagrama de caja mosi.
![diagrama de caja mosi](https://cloud.githubusercontent.com/assets/25775237/26180682/64c44164-3b30-11e7-9f29-58e12f8af5d7.png)

### Datapath mosi.
![datapath mosi](https://cloud.githubusercontent.com/assets/25775237/26180680/64b76638-3b30-11e7-907c-1a24579f5c93.png)





















