#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
RV32I Simulator

To use on a linux machine, run:

./main tests/task1/<test_file>.bin


To compile:

gcc simsource/main.c -o main




*/

uint32_t x[32]; // Registers
uint32_t PC; // TODO: Implementing PC

void dump_registers(){
    for (short i = 0; i < 32; i++){
        printf("x%d = 0x%08x\n", i, x[i]);
    }
}

/* -------------------- Instruction formats -------------------- */
void r_type_executioner(uint32_t instr){
    uint8_t func3, func7;
    uint8_t rd, rs1, rs2;
    uint8_t opcode;
    uint8_t shamt;

    opcode  = instr & 0x0000007F;
    rd      = (instr >> 7) & 0x0000001F;
    func3   = (instr >> 12) & 0x00000007;
    rs1     = (instr >> 15) & 0x0000001F;
    rs2     = (instr >> 20) & 0x0000001F;
    func7   = (instr >> 25) & 0x0000007F;

    printf("Instr: %08x, Opcode: %x, rd: %d, func3: 0x%x, rs1: %d, rs2: %d, func7: 0x%x", 
        instr, opcode, rd, func3, rs1, rs2, func7);
    
    switch (opcode)
    {
    case 0x33: // Bitwise functions
        switch (func3)
        {
        case 0x0:
            if (func7 == 0x00) {x[rd] = x[rs1] + x[rs2];} //add
            else if (func7 == 0x20) {x[rd] = x[rs1] - x[rs2];} //sub
            else {
                printf("\nError in R-type. Exiting... \n\n");
                dump_registers();
                exit(EXIT_FAILURE);
            }
            break;    
        case 0x4:
            x[rd] = x[rs1] ^ x[rs2]; //xor
            break;
        case 0x6:
            x[rd] = x[rs1] | x[rs2]; //or
            break;
        case 0x7:
            x[rd] = x[rs1] & x[rs2]; //and
            break;
        case 0x1:
            shamt = x[rs2] & 0x1F;
            x[rd] = x[rs1] << shamt; //sll
            break;
        case 0x5:
            shamt = x[rs2] & 0x1F; //make sure that max shift is 31
            if(func7 == 0x00) {
                x[rd] = x[rs1] >> shamt; //srl
            } else if (func7 == 0x20) {
                x[rd] = (int32_t)x[rs1] >> shamt; //sra
            } else {
                printf("\nError in R-type. Exiting... \n\n");
                dump_registers();
                exit(EXIT_FAILURE);
            }
            break;
        case 0x2: 
            x[rd] = ((int32_t)x[rs1] < (int32_t)x[rs2]) ? 1 : 0; //slt
            break;
        case 0x3:
            x[rd] = (x[rs1] < x[rs2]) ? 1 : 0; //sltu
            break;
        default:
            break;
        }
        break;
    case 0x2F:

        break;

    default:
        printf("\nError in R-type. Exiting... \n\n");
        dump_registers();
        exit(EXIT_FAILURE);
        break;
    }
}

void i_type_executioner(uint32_t instr){
    uint8_t func3;
    int32_t imm;
    uint8_t rd, rs1;
    uint8_t opcode;
    uint8_t shamt;

    /* Disassembly */
    opcode  = instr & 0x0000007F;
    rd      = (instr >> 7) & 0x0000001F;
    func3   = (instr >> 12) & 0x00000007;
    rs1     = (instr >> 15) & 0x0000001F;
    imm     = (instr >> 20) & 0x00000FFF;

    /* imm conversion from 12 bit to 32 bit */
    if (imm & 0x800) {imm = 0xFFFFF000 | imm;}

    printf("Instr: %08x, Opcode: %x, rd: %d, func3: 0x%x, rs1: %d, imm: %x", 
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
        case 0x4: //xori
            x[rd] = x[rs1] ^ imm;
            break;
        case 0x6: //ori
            x[rd] = x[rs1] | imm;
            break;
        case 0x7: //andi
            x[rd] = x[rs1] & imm;
            break;
        case 0x1: //slli
            shamt = imm & 0x1F;
            x[rd] = x[rs1] << shamt;
            break;
        case 0x5: 
            shamt = imm & 0x1F;
            if(imm & 0x400) {  //1 << 10 (binary 0100 0000 0000)
                x[rd] = (int32_t)x[rs1] >> shamt; //srai
            } else {
                x[rd] = x[rs1] >> shamt; //srli
            }
            break;
        case 0x2: //slti
            x[rd] = ((int32_t)x[rs1] < imm) ? 1 : 0;
            break;
        case 0x3: //sltiu
            x[rd] = (x[rs1] < (uint32_t)imm) ? 1 : 0;
            break;
        default:
            printf("\nError in I-type func3. Exiting... \n\n");
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
        printf("\nError in I-type. Exiting... \n\n");
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
    uint8_t imm11, imm4_1, imm10_5, imm12, imm;
    uint8_t rs1, rs2;
    uint8_t opcode;

    opcode      = instr & 0x0000007F;
    imm11       = (instr >> 7) & 0x00000001;
    imm4_1      = (instr >> 8) & 0x0000000F;
    func3       = (instr >> 12) & 0x00000007;
    rs1         = (instr >> 15) & 0x0000001F;
    rs2         = (instr >> 20) & 0x0000001F;
    imm10_5     = (instr >> 25) & 0x0000003F;
    imm12       = (instr >> 31) & 0x00000001;

    switch (func3) {
        case 0x0:
            if(rs1 == rs2) {
                PC += imm;
            }
            break;
        case 0x1:
            if(rs1 != rs2) {
                PC += imm;
            }
            break;
        case 0x4:
            if(rs1 < rs2) {
                PC += imm;
            }
            break;
        case 0x5:
            if(rs1 >= rs2) {
                PC += imm;
            }
            break;
        case 0x6:
            if(rs1 < rs2) {
                PC += (uint32_t)imm;
            }
            break;
        case 0x7:
            if(rs1 >= rs2) {
                PC += (uint32_t)imm;
            }
            break;
        default: 
            printf("\nError in I-type func3. Exiting... \n\n");
            dump_registers();
            exit(EXIT_FAILURE);
            break;
    }
}

void u_type_executioner(uint32_t instr){
    uint32_t imm;
    uint8_t rd;
    uint8_t opcode;

    /* Disassembly */
    opcode = instr & 0x0000007F;
    rd = (instr >> 7) & 0x0000001F;
    imm = (instr >> 12) & 0x000FFFFF;

    printf("Instr: %08x, Opcode: %x, rd: %d, imm: %x", instr, opcode, rd, imm);

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

/* -------------------- Disassembler -------------------- */
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

int main(int argc, char* argv[]){

    /* Parse the command line arguments. */
    if (argc != 2) {
        printf("Usage:   %s <path to binary>\n", argv[0]);
        printf("Example: %s tests/task1/bool.bin\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Importing the binary */
    FILE *bin_file;
    bin_file = fopen(argv[1], "rb");
    if (bin_file == NULL) {
            printf("Error opening file\n");
            exit(EXIT_FAILURE);
        }
    uint8_t bin[65536];
    size_t bytes_read = fread(bin, 1, 65536, bin_file);

    /* Reading the binary */
    uint32_t instr = 0;
    for (PC = 0; PC < bytes_read; PC++) {
        instr = (instr >> 8) + (bin[PC] << 24);  // Rearranging the bytes from LSB to MSB
        if ((PC + 1) % 4 == 0) {
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