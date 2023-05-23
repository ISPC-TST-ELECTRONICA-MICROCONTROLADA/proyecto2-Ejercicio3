/*
 * Archivo: main.c
 * Fecha de creación: 5/03/2023
 * Micro: PIC16F1938
 * @frec: 8MHZ
 * Autor: Cristian Gonzalo Vera
 * Descripción: Realizar un programa que controle un display LM044L a 4 hilos desde el puerto C. 
 * Fecha de Modificacion: 19/05/2023
 */

#include <xc.h>
#include <stdint.h>
#include <string.h>

#define _XTAL_FREQ 8000000

#define LCD_RS_PIN PORTCbits.RC0
#define LCD_EN_PIN PORTCbits.RC1
#define LCD_D4_PIN PORTCbits.RC2
#define LCD_D5_PIN PORTCbits.RC3
#define LCD_D6_PIN PORTCbits.RC4
#define LCD_D7_PIN PORTCbits.RC5

// Configuración de bits de configuración (Ejemplo PIC16F1938)
#pragma config FOSC = INTOSC  // Bits de Selección del oscilador (oscilador INTOSC: función CLKIN deshabilitada)
#pragma config WDTE = OFF     // Bit de habilitación del Watchdog Timer (WDT deshabilitado)
#pragma config PWRTE = OFF    // Bit de habilitación del temporizador de encendido (PWRT deshabilitado)
#pragma config MCLRE = ON     // Bit de selección de función del pin MCLR (la función del pin MCLR es MCLR)
#pragma config CP = OFF       // Bit de protección de código (la protección de código de la memoria del programa está deshabilitada)
#pragma config BOREN = ON     // Bits de selección de reinicio por bajo voltaje (BOR habilitado)
#pragma config CLKOUTEN = OFF // Bit de habilitación de la salida de reloj (la función CLKOUT está deshabilitada, I/O o función de oscilador en el pin CLKOUT)
#pragma config IESO = OFF     // Bit de conmutación interno/externo (modo de conmutación interno/externo deshabilitado)
#pragma config FCMEN = OFF    // Bit de habilitación del Monitor de reloj a prueba de fallos (el Monitor de reloj a prueba de fallos está deshabilitado)
#pragma config WRT = OFF      // Protección de escritura de la memoria flash (protección de escritura desactivada)
#pragma config PLLEN = OFF    // Bit de habilitación del PLL (PLL 4x deshabilitado)
#pragma config STVREN = ON    // Bit de habilitación del reinicio por desbordamiento/subdesbordamiento de la pila (Desbordamiento o subdesbordamiento de la pila 
                              // provocará un reinicio)
#pragma config LVP = OFF      // Bit de habilitación de programación de bajo voltaje (se debe utilizar voltaje alto en MCLR/VPP para la programación)
#pragma config BORV = LO      // Selección de Voltaje de Restablecimiento por Caída de Tensión (Vbor) (Se ha seleccionado el punto de activación bajo del voltaje 
                              // de restablecimiento por caída de tensión.)

// #pragma config FOSC = INTOSC, WDTE = OFF, PWRTE = OFF, MCLRE = ON, CP = OFF, BOREN = ON, CLKOUTEN = OFF, IESO = OFF, FCMEN = OFF
// #pragma config WRT = OFF, PLLEN = OFF, STVREN = ON, LVP = OFF, BORV = LO


// Prototipos de funciones 
void lcd_send_nibble(uint8_t data);
void lcd_send_byte(uint8_t data, uint8_t control);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_write_string(const char* str);


// Funcion principal
int main(void) {

    // Configuración de puertos y periféricos
    // Configuración de puertos
    TRISA = 0xFF;   // Puerto A como entrada
    ANSELA = 0x00;  // Deshabilitar entradas analógicas en Puerto A
    TRISB = 0xAA;   // Puerto B configurado como: RB1, RB3, RB5 y RB7 como entrada y RB0, RB2, RB4 y RB6 como salida
    ANSELB = 0x00;  // Deshabilitar entradas analógicas en Puerto B
    TRISC = 0x00;   // Puerto C configurado como salida
    // ANSELC = 0x00; // Deshabilitar entradas analógicas en Puerto C
    
    // Variables y/o constantes
    
    // SETUP de dispositivos
    // Inicialización del display
    lcd_init();
    
    // Escribir una cadena de caracteres en el display
    lcd_write_string("¡Hola, mundo!");
    
    // Mover el cursor a la segunda fila, primera columna
    lcd_set_cursor(1, 0);
    
    // Escribir otra cadena de caracteres en el display
    lcd_write_string("Este es un ejemplo.");
    
    
    // LOOP principal
    while(1) {
        // El programa se queda en un bucle infinito
    }
    
    return 0;
}

// Funciones auxiliares
/* 
* void lcd_send_nibble(uint8_t data);
* void lcd_send_byte(uint8_t data, uint8_t control);
* void lcd_send_cmd(uint8_t cmd);
* void lcd_send_data(uint8_t data);
* void lcd_init(void);
* void lcd_clear(void);
* void lcd_set_cursor(uint8_t row, uint8_t col);
* void lcd_write_string(char* str);
*/

void lcd_send_nibble(uint8_t data) {
    LCD_D4_PIN = (data >> 0) & 0x01;
    LCD_D5_PIN = (data >> 1) & 0x01;
    LCD_D6_PIN = (data >> 2) & 0x01;
    LCD_D7_PIN = (data >> 3) & 0x01;
    LCD_EN_PIN = 1;
    __delay_us(1);
    LCD_EN_PIN = 0;
    __delay_us(1);
}

void lcd_send_byte(uint8_t data, uint8_t control) {
    LCD_RS_PIN = control;
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    __delay_us(40);
}

void lcd_send_cmd(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
}

void lcd_send_data(uint8_t data) {
    lcd_send_byte(data, 1);
}

void lcd_init(void) {
    LCD_RS_PIN = 0;
    LCD_EN_PIN = 0;
    LCD_D4_PIN = 0;
    LCD_D5_PIN = 0;
    LCD_D6_PIN = 0;
    LCD_D7_PIN = 0;
    __delay_ms(40);
    lcd_send_nibble(0b0011);
    __delay_ms(5);
    lcd_send_nibble(0b0011);
    __delay_us(150);
    lcd_send_nibble(0b0011);
    __delay_us(40);
    lcd_send_nibble(0b0010);
    __delay_us(40);
    lcd_send_cmd(0b00101000);
    lcd_send_cmd(0b00001100);
    lcd_send_cmd(0b00000110);
    lcd_clear();
}

void lcd_clear(void) {
    lcd_send_cmd(0b00000001);
    __delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address = 0;
    if (row == 0) {
        address = col;
    } else if (row == 1) {
        address = 0x40 + col;
    } else if (row == 2) {
        address = 0x10 + col;
    } else if (row == 3) {
        address = 0x50 + col;
    }
    lcd_send_cmd(0b10000000 | address);
}

void lcd_write_string(const char* str) {
    for (uint8_t i = 0; i < strlen(str); i++) {
        lcd_send_data(str[i]);
    }
}