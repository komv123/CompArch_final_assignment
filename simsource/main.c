#include <stdio.h>
#include <stdint.h>

int main(){
    FILE *bin_file;

    bin_file = fopen("./tests/task1/addlarge.bin", "rb");
    if (bin_file == NULL) {
            printf("Error opening file\n");
            return 1;
        }
    uint8_t bin[100];
    size_t bytes_read = fread(bin, 1, 4294967296, bin_file);

    uint32_t instr = 0;
    for (size_t i = 0; i < bytes_read; i++) {
        
        printf("%02x ", bin[i]);
        instr = (instr >> 8) + (bin[i] << 24);
        if ((i + 1) % 4 == 0) printf("%08x\n", instr);

    }
    printf("\n");

    fclose(bin_file);
    return 0;
}