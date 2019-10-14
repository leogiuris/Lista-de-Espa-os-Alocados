#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LISTA.H"
#include"LEA.H"

LIS_tppLista lea;


typedef struct mem{
	void * address;
	char * nome;
	int size;
}Memory;


void CriarLEA();
void DestruirLEA();


void imprimeMem(Memory * f)
{
	
	if(f->nome != NULL)
		printf("%s  :  %d bytes\n", f->nome, f->size);
	else
		printf("%p  :  %d bytes\n", f->address, f->size);
	
}

void * LEA_malloc(int tamanho)
{
	Memory * f = (Memory*)malloc(sizeof(Memory));
	void * p;
	
	if(lea == NULL)
		CriarLEA();

	
	p = malloc(tamanho);

	
	f->address = p;
	f->size = tamanho;
	f->nome = NULL;
	IrFinalLista(lea);
	
	LIS_InserirElementoApos(lea, f);

	return p;
}

void * LEA_mallocTag(int tamanho, char * nome)
{
	
	Memory * f = (Memory*)malloc(sizeof(Memory));
	void * p;

	

	if(lea == NULL)
		CriarLEA();

	p = malloc(tamanho);

	f->address = p;
	f->size = tamanho;
	f->nome = nome;
	IrFinalLista(lea);
	
	LIS_InserirElementoApos(lea, f);

	return p;
}

void destroiMem(Memory * mem){
	free(mem->nome);
	free(mem);
	return;
}

void excluirNo(void * p){

	destroiMem((Memory*)p);
}

void LEA_free(void * p)
{
	Memory * fat;
	int res = 0;
	
	if(lea==NULL){
		printf("--------- LEA ----------\nlista vazia\n");
		return;
	}

	IrInicioLista(lea);
	do
	{
		fat = (Memory*) LIS_ObterValor(lea);
		if(fat->address == p){
			LIS_ExcluirElemento(lea);
			free(p);
			res = 1;
			break;
		}

	} while(LIS_AvancarElementoCorrente(lea,1) != LIS_CondRetFimLista);
	if(res==0)
		printf("Endereço nao existe ou ja foi liberado.\n");

	if(LIS_AvancarElementoCorrente(lea,1) == LIS_CondRetListaVazia)
	{
		printf("--------- LEA ----------\nMemoria esvaziada com sucesso\n\n");
		DestruirLEA();
	}
	return;
}

void LEA_Imprime()
{
	Memory * fat;

	if(lea == NULL){
		printf("--------- LEA ----------\nlista vazia\n");
		return;
	}

	printf("\n--------- LEA ---------\n");
	IrInicioLista(lea);
	do
	{
		fat = (Memory*) LIS_ObterValor(lea);
		imprimeMem(fat);
	} while(LIS_AvancarElementoCorrente(lea,1) != LIS_CondRetFimLista);

	printf("\n");
}

void CriarLEA()
{
	lea = LIS_CriarLista(excluirNo);
}

void DestruirLEA()
{
	LIS_DestruirLista(lea);
	lea = NULL;
}





//int main()
//{
//	int * i;
//	char * abc;
//	float * ff;
//	
//	CriarLEA();
//
//	i = (int*)LEA_mallocTag(2*sizeof(int),"cuu");
//	abc = (char*)LEA_mallocTag(sizeof(char),"marioooo");
//	ff = (float*)LEA_mallocTag(sizeof(float),"seu sirikejo");
//
//	LEA_free(i);
//	LEA_free(i);
//
//	LEA_Imprime();
//
//	return 0;
//}
