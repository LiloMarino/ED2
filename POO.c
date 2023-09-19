#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *(*Get)();
typedef void (*Set)(char *String);
typedef int (*Print)(const char *String, ...);
typedef int (*Soma)(int a, int b);

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
struct Stmath
{
    Soma soma;
};
struct StSystem
{
    struct Stout out;
    struct Stmath math;
};

typedef struct StCaneta Caneta;
typedef struct Stout out;
typedef struct Stmath math;
int soma(int a, int b)
{
    return a + b;
}
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
    System.math.soma = soma;









    System.out.print("Ola Mundo!\n");
    System.out.print("%d\n",System.math.soma(5,10));
}
