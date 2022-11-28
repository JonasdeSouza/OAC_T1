#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

int32_t lw(uint32_t address, int32_t kte);
int32_t lb(uint32_t address, int32_t kte);
int32_t lbu(uint32_t address, int32_t kte);
void sw(uint32_t address, int32_t kte, int32_t dado);
void sb(uint32_t address, int32_t kte, int8_t dado);

void sb(uint32_t address, int32_t kte, int8_t dado){
    int32_t dadomem;
    uint32_t dadoextended, endereco;
    int8_t byte;
    uint32_t mask = 0xFFFFFF00;
    int shift;

    endereco = address + kte;
    dadomem = mem[(endereco)/4];

    shift = 8 * ((endereco)%4);
    mask = (mask << shift) | (mask >> (32 - shift)); 
    dadomem &= mask;

    dadoextended = (uint32_t)dado;
    dadoextended = dadoextended << shift;
    dadomem |= dadoextended;

    mem[address/4] = dadomem;
}

void sw(uint32_t address, int32_t kte, int32_t dado){
    int indice;

    if((address + kte)% 4 == 0){
        indice = (address + kte)/4;
        mem[indice] = dado;
    }
}

int32_t lw(uint32_t address, int32_t kte){
    int32_t dado;
    int indice;

    if((address + kte)% 4 == 0){
        indice = (address + kte)/4;
        dado = mem[indice];
    } else { return 0; }

    return dado;
}   

int32_t lb(uint32_t address, int32_t kte){
    int32_t dado;
    uint32_t endereco;
    int8_t byte;
    int indice;
    int shift;
    endereco = address + kte;
    dado = mem[endereco/4];

    
    shift = 8*(endereco%4);
    dado = dado >> shift;
    byte = (int8_t)dado;

    return byte;
}

int32_t lbu(uint32_t address, int32_t kte){
    int32_t dado;
    uint32_t byte, endereco;
    uint8_t teste;
    int shift;
    endereco = address + kte;
    dado = mem[endereco/4];

    shift = 8*(endereco%4);
    dado = dado >> shift;
    byte = (uint8_t)dado;

    //teste = (uint8_t)byte;

    return byte;
}


int main (int argc, const char * argv[]) {
    int8_t b0, b1, b2, b3;
    int32_t w;

    scanf("%hhx, %hhx, %hhx, %hhx", &b0, &b1, &b2, &b3);
    sb(0, 0, b0);
    sb(0, 1, b1);
    sb(0, 2, b2);
    sb(0, 3, b3);

    scanf("%hhx, %hhx, %hhx, %hhx", &b0, &b1, &b2, &b3);
    sb(4, 0, b0);
    sb(4, 1, b1);
    sb(4, 2, b2);
    sb(4, 3, b3);
    scanf("%x", &w);
    sw(8, 0, w);
    scanf("%x", &w);
    sw(12, 0, w);
    scanf("%x", &w);
    sw(16, 0, w);
    scanf("%x", &w);
    sw(20, 0, w);
    
    printf("%.08x\n", mem[0]);
    printf("%.08x\n", mem[1]);
    printf("%.08x\n", mem[2]);
    printf("%.08x\n", mem[3]);
    printf("%.08x\n", mem[4]);
    printf("%.08x\n", mem[5]);
    printf("%08x\n", lb(4,0));
    printf("%08x\n", lbu(4,0));
    printf("%08x\n", lw(12, 0));
    printf("%08x\n", lw(16, 0));
    printf("%08x\n", lw(20, 0));
    return 0;
}