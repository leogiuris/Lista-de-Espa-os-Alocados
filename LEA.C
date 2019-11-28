

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


void CriaLea();



void imprimeMem(Memory * f)
{
	if(f->nome != NULL)
		printf("entrou %s :\t%d bytes\n", f->nome, f->size);
	else
		printf("entrou %p :\t%d bytes\n", f->address, f->size);
	
}

void * LEA_malloc(int tamanho)
{
	Memory * f = (Memory*)malloc(sizeof(Memory));
	void * p;
	
	if(lea == NULL)
		CriaLea();

	
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
		CriaLea();

	p = malloc(tamanho);

	f->address = p;
	f->size = tamanho;
	f->nome = nome;
	IrFinalLista(lea);
	
	LIS_InserirElementoApos(lea, f);

	return p;
}

void excluirNo(void * p){
	free(p);
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

void CriaLea()
{
	lea = LIS_CriarLista(excluirNo);
}

void DestruirLEA()
{
	LIS_DestruirLista(lea);
	lea = NULL;
}

void LEA_free(void * p)
{
	Memory * fat;
	int preenchida = 0;
	if(lea==NULL)
	{
		printf("--------- LEA ----------\n>lista vazia\n");
		return;
	}

	IrInicioLista(lea);
	do
	{
		fat = (Memory*) LIS_ObterValor(lea);
		if(fat->address == p)
		{
			LIS_ExcluirElemento(lea);
			free(p);
			preenchida = 1;
			break;
		}

	} while(LIS_AvancarElementoCorrente(lea,1) != LIS_CondRetFimLista);
	if(preenchida == 0)
		printf("Endereço nao existe ou ja foi liberado.\n");

	if(LIS_AvancarElementoCorrente(lea,1) == LIS_CondRetListaVazia)
	{
		printf("--------- LEA ----------\nMemoria esvaziada com sucesso\n\n");
		DestruirLEA();
	}

	return;
}
