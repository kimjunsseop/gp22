/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int PC = 0;
unsigned int instruction_memory[1024];
unsigned int register_file[32] = { 0 };
unsigned int data_memory[1024] = { 0 };
int R_type_count = 0;
int I_type_count = 0;
int J_type_count = 0;
int cycle_count = 1;
unsigned int sign_extend(unsigned int imm) {

    if (imm & 0x8000) {
        imm |= 0xFFFF0000;
    }
    return imm;
}
unsigned int zero_extend(unsigned int imm) {

    return imm;
}



void execute(unsigned int opcode, unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt, unsigned int funct, unsigned int imm, unsigned int address) {
    unsigned int operand1 = register_file[rs];
    unsigned int operand2;
    unsigned int result = 0;
    unsigned int mem_address;

    // ALU 연산 수행
    switch (opcode)
    {
    case 0x00: // R-type
        switch (funct) {
        case 0x20: // Add
            operand2 = register_file[rt];
            result = operand1 + operand2;
            R_type_count += 1;
            cycle_count++;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            break;

        case 0x21: // Addu
            operand2 = register_file[rt];
            result = operand1 + operand2;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, funct : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x22:
            operand2 = register_file[rt];
            result = operand1 - operand2;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x24: //AND
            operand2 = register_file[rt];
            result = operand1 & operand2;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x25: //OR
            operand2 = register_file[rt];
            result = operand1 | operand2;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x08: // JR
            PC = operand1;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x27: // NOR
            operand2 = register_file[rt];
            result = ~(operand1 | operand2);
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x2A: // SLT
            operand2 = register_file[rt];
            result = (operand1 < operand2) ? 1 : 0;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x00: // SLL

            result = operand1 << shamt;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        case 0x02: // SRL
            result = operand1 >> shamt;
            printf("this instruction type : R\n");
            printf("op : 0x%x, rs : 0x%x, rt : 0x%x, rd : 0x%x, shamt : 0x%x, fucnt : 0x%x\n", opcode, rs, rt, rd, shamt, funct);
            R_type_count += 1;
            cycle_count++;
            break;

        default:
            printf("Invalid R-type instruction.\n");
            break;
        }
        break;

    case 0x08: // Addi
        result = operand1 + sign_extend(imm);
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x0C: // Andi
        result = operand1 & zero_extend(imm);
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x0D: // Ori
        result = operand1 | zero_extend(imm);
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x0F: // Lui
        result = imm << 16;
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x23: // LW
        operand2 = sign_extend(imm);
        mem_address = operand1 + operand2;
        result = data_memory[mem_address / 4];
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x2B: // SW
        operand2 = sign_extend(imm);
        mem_address = operand1 + operand2;
        data_memory[mem_address / 4] = register_file[rt];
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x04: // BEQ
        operand2 = sign_extend(imm);
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        if (operand1 == register_file[rt]) {
            PC += operand2 << 2;
        }
        break;

    case 0x09: // Addiu
        result = operand1 + sign_extend(imm);
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x0A: // Slti
        result = (int)operand1 < (int)sign_extend(imm) ? 1 : 0;
        printf("this instruction type : I\n");
        printf("op : 0x%x, rs : 0x%x, rt : 0x%x, imm : 0x%x\n", opcode, rs, rt, imm);
        I_type_count += 1;
        cycle_count++;
        break;

    case 0x03: // Jal
        register_file[31] = PC;
        PC = (PC & 0xF0000000) | (address << 2);
        printf("this instruction type : J\n");
        printf("op : 0x%x, address : 0x%x\n", opcode, address);
        J_type_count += 1;
        cycle_count++;
        break;

    case 0x02: // J
        PC = (PC & 0xF0000000) | (address << 2);
        printf("this instruction type : J\n");
        printf("op : 0x%x, address : 0x%x\n", opcode, address);
        J_type_count += 1;
        cycle_count++;
        break;



    default:
        printf("Invalid opcode.\n");
        break;
    }


    if (opcode == 0x00 && funct != 0x08) {
        register_file[rd] = result;
    }
}

void decode(unsigned int instruction) {
    unsigned int opcode = (instruction >> 26) & 0x3F;
    unsigned int rs = (instruction >> 21) & 0x1F;
    unsigned int rt = (instruction >> 16) & 0x1F;
    unsigned int rd = (instruction >> 11) & 0x1F;
    unsigned int shamt = (instruction >> 6) & 0x1F;
    unsigned int funct = instruction & 0x3F;
    unsigned int imm = instruction & 0xFFFF;
    unsigned int address = instruction & 0x3FFFFFF;

    execute(opcode, rs, rt, rd, shamt, funct, imm, address);
}
unsigned int Change_endian(unsigned int c) {

    return ((c << 24) & 0xff000000) | ((c << 8) & 0x00ff0000) |
        ((c >> 8) & 0x0000ff00) | ((c >> 24) & 0x000000ff);

}


void fetch() {
    unsigned int instruction = instruction_memory[PC / 4];
    // Instruction을 decode 함수로 전달
    unsigned int changed_instruction = Change_endian(instruction);
    printf("cycle : %d\n", cycle_count);
    decode(changed_instruction);
    printf("PC : 0x%x\n", PC);
    printf("fetched instruction : 0x%x\n", changed_instruction);
    printf("\n");
    if (PC == 0Xffffffff)
    {
        return;
    }
    PC += 4;
}



int main() {
    // Instruction memory 초기화
    for (int i = 0; i < 1024; i++) {
        instruction_memory[i] = 0xFFFFFFFF;
    }

    // Data memory 초기화
    for (int i = 0; i < 1024; i++) {
        data_memory[i] = i * 2;
    }
    register_file[31] = 0xffffffff;//$ra

    // Instruction memory에 바이너리 파일에서 읽어온 instruction 저장

    FILE* fp = fopen("input.bin", "rb");
    if (fp == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    fread(instruction_memory, sizeof(unsigned int), 1024, fp);
    fclose(fp);

    while (1) {
        fetch();

        if (PC >= 1024) {
            break;
        }
    }

    printf("===========================\n");
    printf("executed R-type intruction : %d\n", R_type_count);
    printf("executed I-type instruction : %d\n", I_type_count);
    printf("executed J-type instruction : %d\n", J_type_count);
    printf("total cycles : %d\n", cycle_count - 1);

    return 0;
}*/