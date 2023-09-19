#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *(*Get)();
typedef void (*Set)(char *String);
typedef int (*Print)(const char *String);
 

struct StCaneta
{
    char cor;
    Get getCor;
    Set setCor;
};

struct Stout
{
    Print print;
};
struct StSystem
{
    struct Stout out;
};

typedef struct StCaneta Caneta;
typedef struct Stout out;

// Caneta this;

// char getCor()
// {
//     return this.cor;
// }

// void setCor(char cor)
// {
//     this.cor = cor;
// }

// Caneta newCaneta(char cor)
// {
//     this.cor = cor;
//     this.getCor = getCor;
//     this.setCor = setCor;
//     return this;
// }
struct StSystem System;

int main()
{
    System.out.print = printf;
    System.out.print("Ola Mundo!\n");
}

