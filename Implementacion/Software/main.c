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

// Definiciones de literales

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



// Funcion principal
int main(void) {

    return 0;
}

// Funciones auxiliares
/* 

*/
