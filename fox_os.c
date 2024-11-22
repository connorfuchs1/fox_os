#include <fox_os.h>
#include <stdio.h>

void initialize_cpu(CPU_Registers *cpu)
{
    for(int i =0; i < NUM_GPRS; i++)
    {
        cpu->GPR[i]     = 0;    
    }
    cpu->ACCUMULATOR    = 0;
    cpu->PROGRAMCOUNTER = 0;
    cpu->STACKPOINTER   = 0xFFFF;  //stack grows downward!
    cpu->FLAGS.CARRY    = 0;
    cpu->FLAGS.NEGATIVE = 0;
    cpu->FLAGS.OVERFLOW = 0;
    cpu->FLAGS.ZERO     = 0;
}


int main(void)
{
    //CPU_Registers *cpu;
    initialize_cpu(&cpu);
}