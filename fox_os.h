
#include <stdint.h>


/*
    16 bit CPU
    8 general purpose registers


*/


/**
 * 
 *      ____STRUCTURES____
 * 
 */
#define NUM_GPRS 8

typedef struct {
    uint16_t GPR[NUM_GPRS];   //General Purpose Registers
    uint16_t PROGRAMCOUNTER;
    uint16_t STACKPOINTER;
    uint16_t ACCUMULATOR;

    struct {
        uint8_t ZERO     : 1;  //Zero Flag
        uint8_t NEGATIVE : 1;  //Negative Flag
        uint8_t CARRY    : 1;  //Carry Flag
        uint8_t OVERFLOW : 1;  //Overflow Flag
        uint8_t          : 4;  //Padding bits
    } FLAGS;
} CPU_Registers;

CPU_Registers cpu;







/*
*
*       ____FUNCTIONS____
*        
*/

void initialize_cpu(CPU_Registers *cpu);
int main(void);