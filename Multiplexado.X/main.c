

//Asunto: Curso PIC en C - Tarea clase 03
//Correo: ivan.vargas@smartelectronics.com.pe

/*
 1.- El pulsador RB2: 
 -El primer pulso seleccionar� contador manual con pulsadores:
 a) RB0 realizara incrementar� conteo.
 b) RB1realizara drecremento de conteo.
 -El segundo pulso seleccionara contador automatico de 0 a 9999.
 -En tercer pulso deja de operacion las dos primeras opciones, a la vez apagara todo display.
 -En cuarto pulso repite secuencia de operacion.

*/
#include "Librerias/config.h"


void init_osc(void);
void init_puertos(void);
void lcd_numero(uint16_t iterator);
void contador_up(uint16_t *numero);
void contador_down(uint16_t *numero);
uint8_t descomponiendo(char i, uint16_t numero);
void mostrarDISPLAY(uint16_t numero);
uint8_t  display[10]= {
    0b1000000,
    0b1111001,
    0b0100100,
    0b0110000,
    0b0011001,
    0b0010010,
    0b0000010,
    0b1111000,
    0b0000000,
    0b0010000
};


int main(void) {
    init_osc();
    init_puertos();
    uint16_t numero = 0;
    uint8_t selector = 0;
    uint16_t contador_auto= 0;
    while(1){
        
        if(PORTBbits.RB2==0){
           while(PORTBbits.RB2 == 0){
                numero = 0;
                mostrarDISPLAY(0);
           };
            selector = selector +1;
        }
        if(selector == 1){
                contador_up(&numero);
                contador_down(&numero);
                mostrarDISPLAY(numero);          
        }else if(selector == 2){
            
                contador_auto = contador_auto + 1;
                if(contador_auto > 10){
                    if(numero < 9999){
                        numero = numero +1;
                    }
                    contador_auto = 0;
                }
                mostrarDISPLAY(numero);
              
        }else{
            selector = 0;
        }
    }
    return 1;
}
void init_puertos(void){
    ANSELD = 0b00000000;
    TRISD     = 0b00000000;
    LATD = 0b11111111;
    
    ANSELBbits.ANSB0 = 0b0;
    TRISBbits.RB0 = 0b1;
    
    ANSELBbits.ANSB1 = 0b0;
    TRISBbits.RB1 = 0b1;
    

    TRISBbits.RB6 = 0b0;
    LATB6 = 0b0;
    
    ANSELBbits.ANSB3 = 0b0;
    TRISBbits.RB3 = 0b0;
     LATB3 = 0b0;
    
     ANSELBbits.ANSB4 = 0b0;
    TRISBbits.RB4 = 0b0;
    LATB4 = 0b0;
                
     ANSELBbits.ANSB5 = 0b0;
    TRISBbits.RB5 = 0b0;
    LATB5 = 0b0;
    
    
    ANSELBbits.ANSB2 = 0b0;
    TRISBbits.RB2 = 0b1;
    
}
void init_osc(void){
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 0b11;
}
void contador_up(uint16_t *numero){
    
    if(PORTBbits.RB0 == 0){
        if(*numero<9999){
            *numero = *numero + 1;
            while(PORTBbits.RB0 == 0){
                mostrarDISPLAY(*numero);
            }
        }
    }
}
void contador_down(uint16_t *numero){
    
    if(PORTBbits.RB1 == 0){
        if(*numero>=1){
            *numero = *numero - 1;
            while(PORTBbits.RB1 == 0){
                mostrarDISPLAY(*numero);
            }
        }
    }
}
uint8_t descomponiendo(char i, uint16_t numero){
    uint8_t resultado = 0;
    switch(i){
        case 'm':
            resultado = (uint8_t) (numero / 1000);
            break;
        case 'c': 
             resultado = (uint8_t) ((numero % 1000) / 100);
            break;
        case 'd': 
            resultado = (uint8_t) (((numero % 1000) % 100) / 10);
            break;
        case 'u': 
            resultado = (uint8_t) (((numero % 1000) % 100) % 10);
            break;
    }
    return resultado;
}
void mostrarDISPLAY(uint16_t numero){
        LATD = display[descomponiendo('m',numero)];
        LATB6 = 0b1;
        __delay_ms(2);
        LATB6 = 0b0;
        
        LATD = display[descomponiendo('c',numero)];
        LATB3 = 0b1;
        __delay_ms(2);
        LATB3 = 0b0;

        LATD = display[descomponiendo('d',numero)];
        LATB4 = 0b1;
        __delay_ms(2);
        LATB4 = 0b0;

        LATD = display[descomponiendo('u',numero)];
         LATB5 = 0b1;
        __delay_ms(2);
        LATB5= 0b0;
}


