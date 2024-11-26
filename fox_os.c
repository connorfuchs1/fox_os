#include "fox_os.h"



//Opcode Entry Structure. Contains juicy info about our opcodes
typedef struct {
    void (*handler)(CPU_Registers *cpu, uint16_t operand, uint8_t *memory); // Function pointer
    uint8_t operand_size; // Number of bytes for operands
} OpcodeEntry;

// Dispatch table
OpcodeEntry opcode_table[256]; // Table of 256 opcode entries

void initialize_opcode_table() {
    opcode_table[OPCODE_LOAD]  = (OpcodeEntry){handle_load, 1};  // LOAD uses 1-byte operand
    opcode_table[OPCODE_ADD]   = (OpcodeEntry){handle_add, 1};   // ADD uses 1-byte operand
    opcode_table[OPCODE_STORE] = (OpcodeEntry){handle_store, 2}; // STORE uses 2-byte address
    opcode_table[OPCODE_HALT]  = (OpcodeEntry){handle_halt, 0};  // HALT uses no operand
}

void initialize_cpu(CPU_Registers *cpu) {
    for (int i = 0; i < NUM_GPRS; i++) {
        cpu->GPR[i] = 0;
    }
    cpu->ACCUMULATOR = 0;
    cpu->PROGRAMCOUNTER = 0;
    cpu->STACKPOINTER = 0xFFFF; // Stack grows downward!
    cpu->FLAGS.CARRY = 0;
    cpu->FLAGS.NEGATIVE = 0;
    cpu->FLAGS.OVERFLOW = 0;
    cpu->FLAGS.ZERO = 0;
}


// Handlers
void handle_load(CPU_Registers *cpu, uint16_t operand) {
    cpu->ACCUMULATOR = operand; // Load operand into the accumulator
    printf("LOAD: ACCUMULATOR = 0x%X\n", cpu->ACCUMULATOR);
}

void handle_add(CPU_Registers *cpu, uint16_t operand) {
    cpu->ACCUMULATOR += operand; // Add operand to the accumulator
    printf("ADD: ACCUMULATOR = 0x%X\n", cpu->ACCUMULATOR);
}

void handle_store(CPU_Registers *cpu, uint16_t address, uint8_t *memory) {
    memory[address] = (uint8_t)(cpu->ACCUMULATOR & 0xFF); // Store the lower byte of the accumulator
    printf("STORE: Memory[0x%X] = 0x%X\n", address, memory[address]);
}

void handle_halt(CPU_Registers *cpu) {
    printf("HALT: Execution stopped.\n");
    exit(0);
}

void load_program(uint8_t *memory) {
    memory[0x0000] = OPCODE_LOAD;  // LOAD
    memory[0x0001] = 0x42;         // Operand: 0x42
    memory[0x0002] = OPCODE_ADD;   // ADD
    memory[0x0003] = 0x10;         // Operand: 0x10
    memory[0x0004] = OPCODE_STORE; // STORE
    memory[0x0005] = 0x10;         // Address (low byte)
    memory[0x0006] = 0x00;         // Address (high byte)
    memory[0x0007] = OPCODE_HALT;  // HALT
}

void fetch_decode_execute(CPU_Registers *cpu, uint8_t *memory) {
    while (1) {
        // Fetch the opcode
        uint8_t opcode = memory[cpu->PROGRAMCOUNTER];
        cpu->PROGRAMCOUNTER += 1;

        // Decode and Execute
        OpcodeEntry entry = opcode_table[opcode];
        if (entry.handler == NULL) {
            printf("ERROR: Unknown opcode 0x%X\n", opcode);
            exit(1);
        }

        // Handle operands
        uint16_t operand = 0;

        //if the instruction is a store, we need get grab the next two bytes for the address.
        for (int i = 0; i < entry.operand_size; i++)
        {
            //combine the fetched and shifted byte via bitwise or
            operand |= memory[cpu->PROGRAMCOUNTER] << (i * 8);
            cpu->PROGRAMCOUNTER +=1;
        }

        // Execute the instruction
        entry.handler(cpu, operand, memory);
    }
}


int main(void) {
    // CPU and Memory Initialization
    CPU_Registers cpu;
    uint8_t memory[65536] = {0}; // 64KB memory

    // Initialize CPU and Opcodes
    initialize_cpu(&cpu);
    initialize_opcode_table();

    // Load Program into Memory
    load_program(memory);

    // Execute Program
    fetch_decode_execute(&cpu, memory);

    return 0;
}
