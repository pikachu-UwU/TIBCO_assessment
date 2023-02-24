




#include "littleEndian.h"

unsigned short my_ntohs(unsigned short in) {
    // STEP1 - separate 1 and 2 byte from the number:
    unsigned short last_byte = in & 0x00FF;     // separates last byte in a farm of 0x00XX
    unsigned short first_byte = in & 0xFF00;    // separates first byte into 0xXX00

    // STEP2 - shift the bytes into correct positions:
    last_byte = (last_byte << 8) & 0xFF00;
    first_byte = (first_byte >> 8) & 0x00FF;
    
    // STEP3 - combine both bytes together into a single short:
    return first_byte | last_byte;
}


// NOTE: separation of bytes and shifts could technically be done
// in less steps, but considering the readability of code it would
// benefit to split the operations into different steps for easier
// understanding

unsigned int my_ntohl(unsigned int in) {
    // separate the bytes into correct order:
    // STEP1 - separate bytes from the number:
    unsigned int forth_byte = in & 0x000000FF;      // forth byte as 0x000000XX
    unsigned int third_byte = in & 0x0000FF00;      // third byte as 0x0000XX00
    unsigned int second_byte = in& 0x00FF0000;      // second byte as 0x00XX0000
    unsigned int first_byte = in & 0xFF000000;      // first byte as 0xXX000000

    // STEP2 - shift the bytes into correct positions:
    forth_byte = (forth_byte << 24) & 0xFF000000;
    third_byte = (third_byte << 8) & 0x00FF0000;
    second_byte = (second_byte >> 8) & 0x0000FF00;
    first_byte = (first_byte >> 24) & 0x000000FF;

    // STEP3 - connect all the bytes together:
    return first_byte | second_byte | third_byte | forth_byte;
}