#include "bigint.h"



sn *criar(void)
{
	sn* resp = (sn*)malloc(sizeof(sn));
	resp->tam = 0;
	resp->prim = NULL;
	resp->ult = NULL;
	return resp;
}

void liberaNum(sn* num)
{
	dig *p = num->prim;
	while(p!=NULL)
	{
		dig* aux = p;
		p = p->prox;
		free(aux);
	}
	num->tam = 0;
	num->sinal = 0;
	free(p);
	free(num);
}

int comp(sn* num1, sn* num2)
{
	if (num1->tam > num2->tam)return 1;
	if (num1->tam < num2->tam)return -1;
	dig* p1 = num1->prim;
	dig* p2 = num2->prim;
	while(p1!=NULL)
	{
		if (p1->alg > p2->alg){
			return 1;
		}
		if (p1->alg < p2->alg){
			return -1;
		}
		p1 = p1->prox;
		p2 = p2->prox;
	}
	return 0;

}

sn* copiar(sn* num)
{
	sn*resp = criar();
	dig*p = num->prim;
	while (p!=NULL)
	{
		insertFinal(resp, p->alg);
		p = p->prox;
	}
	resp->sinal = num->sinal;
	resp->tam = num->tam;
	
	return resp;
}


void insertInit(sn* num, char d)
{
	dig* novo = (dig*)malloc(sizeof(dig));
	novo->alg = d;
	novo->prox = num->prim;
	novo->ant = NULL;
	if (num->prim != NULL)
		{
			num->prim->ant = novo;
		}
	else
	{
		num->ult = novo;
	}
	num->prim = novo;
	num->tam++;

}

void insertFinal(sn* num, char d)
{
	dig* novo = (dig*)malloc(sizeof(dig));
	novo->alg = d;
	novo->ant = num->ult;
	novo->prox = NULL;
	if (num->ult != NULL)
	{
		num->ult->prox = novo;
	}	
	else
	{
		num->prim = novo;
	}
	num->ult = novo;
	num->tam++;
}

sn* CriaZero(void)
{
	sn* Zero = criar();
	Zero->sinal = '+';
	char x = 0;
	insertInit(Zero, x);
	return Zero;
}

sn* novoNum(char* numero)
{
	sn* num = criar();
	int qntAlg = strlen(numero);
	if (numero[0] == '-') num->sinal = '-';
	else num->sinal = '+';
	if(isdigit(numero[0]))
	{
		for (int i =0; i < qntAlg; i++)
		{
			insertFinal(num, (numero[i] - 48));
		}
	}
	else
	{
		for (int i =1; i < qntAlg; i++)
		{
			insertFinal(num, (numero[i] - 48));
		}
	}
	return num;
}

void printNum(sn* num)
{
	printf("%c", num->sinal);
	dig* p = num->prim;
	while (p!=NULL)
	{
		printf("%d", p->alg);
		p = p->prox;
	}
	printf("\n");
}

sn* somar(sn* num1, sn* num2)
{
	sn* soma = criar();		
	char atual, vaiUm = 0;
	dig* pMaior;
	dig* pMenor;
	if (num1->tam > num2->tam)
	{
		pMaior = num1->ult;
		pMenor = num2->ult;
	}
	else
	{
		pMaior = num2->ult;
		pMenor = num1->ult;
	}
	while (pMenor != NULL)
	{
		atual = pMaior->alg + pMenor->alg + vaiUm;
		if (atual > 9)
		{
			vaiUm = 1;
			atual -= 10;
		}
		else vaiUm = 0;
		insertInit(soma, atual);
		pMaior = pMaior->ant;
		pMenor = pMenor->ant;
	}
	if (pMaior == NULL && vaiUm != 0)
		{
			insertInit(soma, vaiUm);
			vaiUm = 0;
		}
	while (pMaior!=NULL)
	{
		atual = pMaior->alg + vaiUm;
		if (atual > 9)
		{
			vaiUm = 1;
			atual -= 10;
		}
		else vaiUm = 0;
		insertInit(soma, atual);
		pMaior = pMaior->ant;
	}
	if (vaiUm != 0){
		insertInit(soma, vaiUm);
	}
	
	return soma;
}

sn* algMultBigint(sn* num, char alg)
{	
	sn* result = CriaZero();
	for (char i = 0; i < alg; i++)
	{
		result = somar(result, num);
	}
	return result;
}


void addZeroEsq(sn* num, int qnt)
{
	char aux = 0;
	for (int i = 0; i < qnt; i++)
	{
		insertFinal(num, aux);
	}
}





sn* mult(sn* num1, sn* num2) //num1 - num2
{
	sn* result = CriaZero();
	int cont = 0;
	dig* pMaior;
	dig* pMenor;
	sn* maiorNum;
	sn* menorNum;
	int qntSomas;
	if (num1->tam > num2->tam)
	{
		maiorNum = num1;
		menorNum = num2;
	}
	else
	{
		maiorNum = num1;
		menorNum = num2;	
	}
	pMaior = maiorNum->ult;
	pMenor = menorNum->ult;
	qntSomas = menorNum->tam;
	int i = 0;
	while (pMenor != NULL)
	{
		sn* tempResult = algMultBigint(maiorNum, pMenor->alg);
		addZeroEsq(tempResult, cont);
		sn* tempResult2 = copiar(result);
		result = somar(tempResult2, tempResult);
		pMenor = pMenor->ant;
		cont++;
		liberaNum(tempResult2);
		liberaNum(tempResult);
	}
	if (num1->sinal == num2->sinal){
		result->sinal = '+';
	}
	else {
		result->sinal = '-';
	}
	
	
	return result;
	

}

sn* subtrair(sn* num1, sn*num2)
{
	char aux = 0;
	if (comp(num1, num2)==0)
	{
		sn* resp = CriaZero();
		return resp;
	}
	sn* resp = criar();
	sn* maiorNum;
	sn* menorNum;
	if (num1->tam != num2->tam)
	{
		if (num1->tam > num2->tam)
		{
			maiorNum = num1;
			menorNum = num2;
		}
		else
		{
			maiorNum = num1;
			menorNum = num2;	
		}
	}
	else
	{
		if (num1->prim->alg > num2->prim->alg)
		{
			maiorNum = num1;
			menorNum = num2;
		}
		else
		{
			maiorNum = num2;
			menorNum = num1;
		}
	}
	dig *pMaior = maiorNum->ult;
	dig *pMenor = menorNum->ult;
	while (pMenor != NULL)
	{
		char val = pMaior->alg - pMenor->alg - aux;
		if (val >= 0)aux = 0;
		else
		{
			val += 10;
			aux = 1;
		}
		insertInit(resp, val);
		pMaior = pMaior->ant;
		pMenor = pMenor->ant;			
	}									   
	while (pMaior != NULL)
	{
		char val = pMaior->alg - aux;
		if (val >= 0)aux = 0;
		if (val < 0)
		{
			val += 10;
			aux = 1;
		}
		insertInit(resp, val);
		
		pMaior = pMaior->ant;
	}
	dig* pFormat = resp->prim;
	while(pFormat->alg==0)
	{
		if (pFormat->prox == NULL)break;
		resp->prim = pFormat->prox;
		pFormat->prox->ant = NULL;
		resp->tam--;
		pFormat = pFormat->prox;
	}
	return resp;

}

sn* soma_com_sinal(sn* num1, sn*num2)
{
	sn*resp;
	
	if (num1->sinal == num2->sinal)
	{
		sn*resp = somar(num1, num2);
		resp->sinal=num1->sinal;
		return resp;
	}
	if (comp(num1, num2)==0)
	{
		resp = CriaZero();
		return resp;
	}
	if (comp(num1, num2)>0)
	{
		resp = subtrair(num1, num2);
		resp->sinal = num1->sinal;
		return resp;
	}
	if (comp(num1, num2)<0)
	{
		resp = subtrair(num2, num1);
		resp->sinal = num2->sinal;
		return resp;
	}
}

sn* subtrair_com_sinal(sn* num1, sn* num2)
{
	sn* resp;
	if (num1->sinal == '-' && num2->sinal == '-')
	{
		if (comp(num1, num2)==0)
		{
			resp = CriaZero();
			return resp;
		}
		if (comp(num1, num2)>0)
		{
			resp = subtrair(num1, num2);
			resp->sinal = '-';
			return resp;
		}
		if (comp(num1, num2)<0)
		{
			resp = subtrair(num2, num1);
			resp->sinal = '+';
			return resp;
		}
	}
	if (num1->sinal == '+' && num2->sinal == '-')
	{
		resp = somar(num1, num2);
		resp->sinal = '+';
		return resp;
	}
	if (num1->sinal == '-' && num2->sinal == '+')
	{
		resp = somar(num1, num2);
		resp->sinal = '-';
		return resp;
	}
	if (num1->sinal == '+' && num2->sinal == '+')
	{
		if (comp(num1, num2)==0)
		{
			resp = CriaZero();
			return resp;
		}
		if (comp(num1, num2)>0)
		{
			resp = subtrair(num1, num2);
			resp->sinal = '+';
			return resp;
		}
		if (comp(num1, num2)<0)
		{
			resp = subtrair(num2, num1);
			resp->sinal = '-';
			return resp;
		}
	}
}
int comp_com_sinal(sn*num1, sn*num2)
{
	if (num1->sinal == '+' && num2->sinal == '-')return 1;
	if (num1->sinal == '-' && num2->sinal == '+')return -1;
	if(num1->sinal==num2->sinal && num1->sinal=='+')return comp(num1, num2);
	if(num1->sinal==num2->sinal && num1->sinal=='-')return comp(num2, num1);
}

sn* BigintDivLong(sn* num1, unsigned long num2)
{
	sn* resp = criar();
	resp->sinal = num1->sinal;
	unsigned long numerador = 0;
	dig* p = num1->prim;
	if (num2<1) exit(1);
	while (p!=NULL)
	{
		numerador += p->alg;
		insertFinal(resp, (numerador/num2));
		numerador = (numerador - (resp->ult->alg*num2)) * 10;
		p = p->prox;
		
	}
	p = resp->prim;
	while (p->alg==0)
	{
		dig* aux = p;
		p = p->prox;
		resp->prim = p;
		free(aux);
		resp->tam--;
	}
	return resp;
}

unsigned long resto(sn* num1, unsigned long num2)
{
	dig* p = num1->prim;
	long numerador = 0;
	while(p!=NULL)
	{
		numerador *=10;
		numerador += p->alg;
		numerador = (numerador - ((numerador/num2)) * num2);
		p = p->prox;
	}
	return numerador;	
}

unsigned long* fatora(sn* num){
	sn* bint = num;	
	unsigned long *resp = malloc(sizeof(unsigned long)*100);
	
	for (int i = 0; i < 100; i++)  //Só pra me livrar do lixo.
	{
		resp[i] = 1; 
	}

	int l = 1, indice = 0;

	while(bint->tam > 17)
	{		
		indice = 0;
		unsigned long fator = primos[indice];

		while(resto(bint, fator) != 0) //Acha os números divisiveis
		{	
			fator = primos[++indice];
			
			if(indice>210107){
				resp[0]=0;
				break;
			}
		}
		if(indice>210107)break;
		sn* aux = copiar(bint);
		bint = BigintDivLong(aux, fator); //Divide e guarda eles.
		liberaNum(aux);
		
		resp[l++] = fator;
	}
	
	for (int i = 0; i < 100; i++)
	{
		if (resp[i]>1 && resp[i]<999999999 && resp[i+1]>1 && resp[i]<999999999) //Se dois números são muito pequenos...
		{
			resp[i] *= resp[i+1];	//Multiplicam-se entre eles para diminuir o número de operações.
			resp[i+1] = 1;
		}
	}
	
	dig* p2 = bint->ult;
	unsigned long termo = 1, soma = 0;
	bint->prim->ant = NULL;
	while (p2 !=NULL)  //Depois de diminuido, o BigInt é transformado em long e adicionado a lista.
	{
		soma += p2->alg * termo;
		termo *= 10;
		p2= p2->ant;
	}
	termo = 0;
	while(resp[termo]!=1){
		termo++;
	}
	
	resp[termo] = soma;
	return resp;  //A lista é retornada contendo ĺongs que multiplicados dão como resultado o BingInt original.
}


sn* divide(unsigned long* num, sn* num2){
	
	sn* bint = num2;
	sn* somaResp = CriaZero();
	unsigned long*  lista = num;
	
	sn *buff;
	
	for (int i = 0; i < 100; i++)
		if(lista[i]>1){
		
		if(somaResp && somaResp->prim->alg != 0){
			buff = BigintDivLong(somaResp, lista[i]);
				
		}else{
			buff = BigintDivLong(bint, lista[i]);
		}
		somaResp = copiar(buff);
	}
	liberaNum(buff);
	
	return somaResp;
}