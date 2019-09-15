#include "bigint.h"

int main(void)
{
	
	char *teste = (char*)malloc(sizeof(char)*300);
	char *teste2 = (char*)malloc(sizeof(char)*300);
	char *operador = (char*)malloc(sizeof(char)*20);
	printf("\n\nCALCULADORA DE NÚMEROS INTEIROS GIGANTES:\nDigite dois números inteiros para serem calculados, o programa PARA se um dos números é igual a 0:\n");
	while(1){
		operador[0]=0;
		printf("\n\tDigite o primeiro número:\n>>>");
		scanf("%s", teste);
		if(!teste || (teste[0] <= 90 && teste[0] >= 65) || (teste[0]<=122 && teste[0]>=97)){
			printf("\tFIM DO PROGRAMA\n\n");
			
			free(teste);
			free(teste2);
			return 0;
		}

		while (operador[0]!= '+' && operador[0]!='-' && operador[0]!='*' && operador[0]!='/')
		{
			printf("\n\tDigite um dos operadores: (+, *, -, /)\n>>>");	
			scanf(" %s", operador);		
			if (operador[0]!= '+' && operador[0]!='-' && operador[0]!='*' && operador[0]!='/')
			{
				printf("\nOperador invalido!\n");
			}
		}
		printf("\n\tDigite o segundo número:\n>>>");
		scanf("%s", teste2);

		if(!teste || (teste[0] <= 90 && teste[0] >= 65) || (teste[0]<=122 && teste[0]>=97)){
			printf("\tFIM DO PROGRAMA\n\n");
			
			free(teste);
			free(teste2);
			return 0;
		}

		sn* numero = novoNum(teste);
		sn* numero2 = novoNum(teste2);
		sn* result;
		unsigned long *fatores;
		char checkNum = 1;
		switch(operador[0])
		{
			case '+':
				result = soma_com_sinal(numero, numero2);
				printf("\nSoma: ");
				break;
			
			case '-':
				result = subtrair_com_sinal(numero, numero2);
				printf("\nSubtração: ");
				break;
			case '*':
				result = mult(numero, numero2);
				printf("\nMultiplicação: ");
				break;
			case '/':
				fatores = fatora(numero2);
				if (fatores[0]==0){
					printf("\nDivisão: ERRO! O dividendo possui fatores primos de valor muito alto.\n");
					checkNum = 0;
				}
				else
				{
					int numCompara = comp(numero, numero2);
					if (numCompara == 1){	
						printf("\nDivisão: ");
						result = divide(fatores, numero);
					}else{ 
						printf("\nDivisão: ERRO! A divisão dará um número contido entre -1 e 1.\n");
						checkNum = 0;
					}
				}
				break;
		}
		if (checkNum)
		{
			printNum(result);
			liberaNum(result);
		}
		printf("\n--------------------------------------------------------------------------\n");
		liberaNum(numero);
		liberaNum(numero2);
	}
	return 0;
}