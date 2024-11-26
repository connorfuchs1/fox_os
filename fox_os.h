#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_GPRS 8

typedef struct {
    uint16_t GPR[NUM_GPRS]; // General Purpose Registers
    uint16_t ACCUMULATOR;
    uint16_t PROGRAMCOUNTER;
    uint16_t STACKPOINTER;

    struct {
        uint8_t ZERO     : 1;
        uint8_t NEGATIVE : 1;
        uint8_t CARRY    : 1;
        uint8_t OVERFLOW : 1;
        uint8_t          : 4; // Padding
    } FLAGS;
} CPU_Registers;

// Opcodes
#define OPCODE_LOAD  0x01
#define OPCODE_ADD   0x02
#define OPCODE_STORE 0x03
#define OPCODE_HALT  0xFF

// Function Prototypes
void initialize_cpu(CPU_Registers *cpu);
void initialize_opcode_table();
void load_program(uint8_t *memory);
void fetch_decode_execute(CPU_Registers *cpu, uint8_t *memory);

// Opcode Handlers
void handle_load(CPU_Registers *cpu, uint16_t operand);
void handle_add(CPU_Registers *cpu, uint16_t operand);
void handle_store(CPU_Registers *cpu, uint16_t address, uint8_t *memory);
void handle_halt(CPU_Registers *cpu);
