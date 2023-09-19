#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *(*Get)();
typedef void (*Set)(char *String);
typedef int (*Print)(const char *String, ...);
typedef Print (*PrintLn)(const char *String);
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
    PrintLn println;
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
Print println(const char *String)
{
    char variavel[strlen(String) + 2];
    strcpy(variavel,String);
    strcat(variavel,"\n");
    return printf(variavel);
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
    System.out.println = println;
    System.math.soma = soma;









    System.out.println("Ola Mundo!");
    System.out.print("%d\n",System.math.soma(5,10));
}
