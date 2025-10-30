#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t x[32]; // Registers
uint32_t PC; // TODO: Implementing PC

void dump_registers(){
    for (short i = 0; i < 32; i++){
        printf("x%d = 0x%08x\n", i, x[i]);
    }
}


/* Instruction formats */
void r_type_executioner(uint32_t instr){
    uint8_t func3, func7;
    uint8_t rd, rs1, rs2;
    uint8_t opcode;

    opcode = instr & 0x0000007F;
}
void i_type_executioner(uint32_t instr){
    uint8_t func3;
    int32_t imm;
    uint8_t rd, rs1;
    uint8_t opcode;

    /* Disassembly */
    opcode  = instr & 0x0000007F;
    rd      = (instr >> 7) & 0x0000001F;
    func3   = (instr >> 12) & 0x00000007;
    rs1     = (instr >> 15) & 0x0000001F;
    imm     = (instr >> 20) & 0x00000FFF;

    /* imm conversion from 12 bit to 32 bit */
    if (imm & 0x800) {imm = 0xFFFFF000 | imm;}

    printf("Instr: %x, Opcode: %x, rd: %d, func3: 0x%x, rs1: %d, imm: %x", 
        instr, opcode, rd, func3, rs1, imm);

    /* Execution */
    switch (opcode)
    {
    case 0x13: // Immediate operations
        switch (func3)
        {
        case 0x0: // ADD Immediate
            x[rd] = x[rs1] + imm;
            break;
        
        default:
            printf("\nError in i-type. Exiting... \n\n");
            dump_registers();
            exit(EXIT_FAILURE);
            break;
        }
        break;
    case 0x03:

        break;

    case 0x73: // Enviroment operations
        if (!imm) { // ecall
            printf("\nEnvironment call registered.\nDumping registers and exiting... \n\n");
            dump_registers();
            exit(EXIT_SUCCESS);
        } else {
            // TODO: ebreak
        }
        
        break;

    default:
        printf("\nError in i-type. Exiting... \n\n");
        dump_registers();
        exit(EXIT_FAILURE);
        break;
    }
}
void s_type_executioner(uint32_t instr){
    uint8_t func3;
    uint8_t imm_upper, imm_lower;
    uint8_t rs1, rs2;
    uint8_t opcode;

    opcode = instr & 0x0000007F;
}
void b_type_executioner(uint32_t instr){
    uint8_t func3;
    uint8_t imm_upper, imm_lower;
    uint8_t rs1, rs2;
    uint8_t opcode;

    opcode = instr & 0x0000007F;
}

void u_type_executioner(uint32_t instr){
    uint32_t imm;
    uint8_t rd;
    uint8_t opcode;

    /* Disassembly */
    opcode = instr & 0x0000007F;
    rd = (instr >> 7) & 0x0000001F;
    imm = (instr >> 12) & 0x000FFFFF;

    printf("Instr: %x, Opcode: %x, rd: %d, imm: %x", instr, opcode, rd, imm);

    /* Execution */
    switch (opcode)
    {
    case 0x37: // Load upper Imm
        x[rd] = (imm << 12);
        break;

    case 0x17: // Add Upper Imm to PC
        x[rd] = PC + (imm << 12);
        break;

    default:
        printf("\nError in U-type. Exiting... \n\n");
        dump_registers();
        exit(EXIT_FAILURE);
        break;
    }
}
void j_type_executioner(uint32_t instr){
    uint32_t imm;
    uint8_t rd;
    uint8_t opcode;
}

/* Disassembler */
void instruction_disassembler(uint32_t instr){
    uint8_t opcode = instr & 0x0000007F;
    printf("%x | ", opcode);

    /* Deciding which instruction format to use for disassembly */
    switch (instr & 0x0000007F)
    {
    /* R-types */
    case 0x33:
    case 0x2F:
        r_type_executioner(instr);
        break;
    
    /* I-types */
    case 0x13:
    case 0x03:
    case 0x73:
        i_type_executioner(instr);
        break;

    /* S-types */
    case 0x23:
        s_type_executioner(instr);
        break;
    
    /* B-types */
    case 0x63:
        b_type_executioner(instr);
        break;
    
    /* U-types */
    case 0x37:
        u_type_executioner(instr);
        break;
    
    /* J-types */
    case 0x6F:
        j_type_executioner(instr);
        break;
    
    default:
        printf("\nUnknown opcode: 0x%x\nExiting...\n\n", opcode);
        dump_registers();
        exit(EXIT_FAILURE);
        break;
    }
}

int main(){
    /* Importing the binary */
    FILE *bin_file;
    bin_file = fopen("./tests/task1/addlarge.bin", "rb");
    if (bin_file == NULL) {
            printf("Error opening file\n");
            exit(EXIT_FAILURE);
        }
    uint8_t bin[65536];
    size_t bytes_read = fread(bin, 1, 65536, bin_file);

    /* Reading the binary */
    uint32_t instr = 0;
    for (size_t i = 0; i < bytes_read; i++) {
        instr = (instr >> 8) + (bin[i] << 24);  // Rearranging the bytes from LSB to MSB
        if ((i + 1) % 4 == 0) {
            printf("\n%08x ", instr); 
            // Execute instruction
            instruction_disassembler(instr);
        }

    }
    printf("\n");
    dump_registers();

    fclose(bin_file);
    return 0;
}