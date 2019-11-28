
//	Modulo: Lista de Espaços Alocados  
//	Autor: Leonardo Santiago		11/10/2019 - Rio de Janeiro
//	
//	Ultima atualizaçao: 14/10/2019


/////////////////////////////////////////////////
void * LEA_malloc(int tamanho);

void * LEA_mallocTag(int tamanho, char * nome);

void LEA_free(void * p);

void LEA_Imprime();
/////////////////////////////////////////////////

void * AlocaLea(int tamanho);

void * AlocaLeaTag(int tamanho, char * nome);

void ImprimeLea();

void FreeLea(void * p);