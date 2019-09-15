#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>


typedef struct digito dig;
typedef struct sinal sn;
typedef struct fatores fats;
struct digito
{
	dig* ant;
	dig* prox;
	char alg;
} ;
struct sinal
{
	char sinal;
	int tam;
	dig* prim;
	dig* ult;
};



sn *criar(void);
void liberaNum(sn* num);
void retira(sn* num, char alg);
void redefTam(sn* num);
int comp(sn* num1, sn* num2);
sn* copiar(sn* num);
void insertInit(sn *num, char d);
void insertFinal(sn *num, char d);
sn* CriaZero(void);
void addOne(sn* num);
sn* novoNum(char* numero);
void printNum(sn* num);
sn* somar(sn* num1, sn* num2);
sn* algMultBigint(sn* num, char alg);
void addZeroEsq(sn* num, int qnt);
sn* mult(sn* num1, sn* num2);
sn* subtrair(sn* num1, sn* num2);
sn* soma_com_sinal(sn* num1, sn*num2);
sn* subtrair_com_sinal(sn* num1, sn* num2);
int comp_com_sinal(sn*num1, sn*num2);
sn* BigintDivLong(sn* num1, unsigned long num2);
unsigned long resto(sn* num1, unsigned long num2);
fats * Fatora(sn* num);
sn *divide(unsigned long* num, sn* num2);
unsigned long* fatora(sn* num);