/*----------------------------------------------------------
        Universidade Federal de São João del-Rei
		Gabriel Spada Ramos
     	       Isabella Vieira Ferreira
       	        Mônica Neli de Resende  
    	  Ciência da Computação - 2º período
	  	    16/11/2011                                     
-------------------------------------------------------------*/
			             	             
/*---------------------------------------------------------------
Algoritmo de ordenação: Quicksort.
Modificação: Pivô aleatório

A idéia deste algoritmo é dividir o problema de ordenar 
um conjunto com n itens em dois problemas menores. Os problemas 
menores são ordenados independentemente.Os resultados são 
combinados para produzir a solução final. O pivô é escolhido 
aleatoriamente entre os elementos da partição.
----------------------------------------------------------------*/			           

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct item{
	int chave;
	// Outros componentes.
} Item;

int max;


/* Função que particiona o vetor,escolhendo aleatoriamente o pivô.*/

void particionar(int esq, int dir,int *i, int *j, Item a[max+1]) {
	Item x, w;
	int h;

	*i = esq; 
	
	*j = dir;
	
	//Escolhendo aleatoriamente o pivô
	srand(time(NULL));
	h = rand() % (*j-*i) + *i; 
	x = a[h];

	do {
		// Enquanto a chave for menor que o pivô, "i anda para a direita".
		while (x.chave > a[*i].chave) {
			(*i)++;
		}
		//Enquanto a chave for maior que o pivô, "j anda para a esquerda".
		while (x.chave < a[*j].chave) {
			(*j)--;
		}
		//Se os ponteiros "i" e "j" se cruzarem,ou "i" for menor que "j", troca os elementos de lugar.
		if (*i <= *j) {
			w = a[*i]; 
			a[*i] = a[*j]; 
			a[*j] = w;
			(*i)++; 
			(*j)--;
		}
	} while (*i <= *j);
} // particionar



// Funcao que ordena os elementos no vetor.
void ordenar(int esq, int dir, Item a[max+1]) {
	int i, j;
	
	// Chamada da função particionar.
	particionar(esq, dir, &i, &j, a);
	
	//Ordena as partições. Chamada recursiva da função ordenar.
	if (esq < j) {
		ordenar(esq, j, a);
	}
	if (i < dir) {
		ordenar(i, dir, a);
	}
}


// A função Quicksort chama a função ordenar.
void quicksort(Item a[max+1], int *n) {
	ordenar(1, *n, a);
}


// Função principal.
int main ( ){
	
	int i, opcao;
	char opt;
	printf ("\n\n");
	
	// Usuário informa quantos elementos terá no vetor.
	printf("Informe quantos valores terá no vetor: ");
	scanf("%d",&max);
	
	Item vetor[max+1]; //Declarando o vetor de registros que serão ordenados

	FILE *f1,*f2;	//Declarando os arquivos a serem utilizados.

	
	//Menu de opções.
	do {
	
	printf ("\n\n");
	printf ("          :: Menu :: \n");
	printf ("\n");
	printf ("[1] - Gerar sequencia crescente \n");
	printf ("[2] - Gerar sequencia decrescente \n");
	printf ("[3] - Gerar sequencia pseudo-aleatoria \n");
	printf ("[4] - Ordenar a sequencia gerada \n");	
	printf ("[5] - Sair \n");		
	
	printf("\n Digite a sua opcao: ");
	scanf("%d", &opcao);
	
	switch (opcao) {
	
	case 1: 	        
		// Assinalando o nome externo do arquivo, e abrindo-o.
		// "w" - escrita em arquivo
		f1 = fopen("Entrada.txt","w");		

		// Vetor em ordem crescente
		for(i = 1; i <= max; i++){
			vetor[i].chave = i;
			//Imprime os valores gerados no arquivo de entrada.
			fprintf(f1,"%d\t",vetor[i].chave);
		}
		

		printf("\nSequencia gerada com sucesso!\n");

		fclose(f1);			
		break;
	case 2: 
		// Assinalando o nome externo do arquivo, e abrindo-o.
		// "w" - escrita em arquivo
		f1 = fopen("Entrada.txt","w");
	
		// Vetor em ordem decrescente
		for(i = 1; i <= max; i++){
			vetor[i].chave = max - i;
			//Imprime os valores gerados no arquivo de entrada.
			fprintf(f1,"%d\t",vetor[i].chave);
		}
		
		printf("\nSequencia gerada com sucesso!\n");
	
		fclose(f1);	
		break;
	case 3:
		// Assinalando o nome externo do arquivo, e abrindo-o.
		// "w" - escrita em arquivo
		f1 = fopen("Entrada.txt","w");		
		
		//Para não gerar os mesmos números pseudo-aleatórios,semente definida como 12.
		srand(12);
		for(i = 1; i <= max; i++){
			//Gerando numeros pseudo-aleatorios e guardando no vetor.
	        	vetor[i].chave = rand() % max;
			//Imprime os valores gerados no arquivo de entrada.
			fprintf(f1,"%d\t",vetor[i].chave);
	        }
	        
	        printf("\nSequencia gerada com sucesso!\n");
	
		fclose(f1);        
	        break;
	
	case 4: 

		f2 = fopen("Saida.txt","w");

		// Chamada da funcao Quicksort para ordenar a sequência
		quicksort(vetor,&max);
		
		//Imprime no arquivo de saída os valores ja ordenados.
		for(i=1;i<=max;i++){
			fprintf(f2,"%d\t",vetor[i].chave);
		}
		

		printf("\nSequencia ordenada com sucesso!\n");
		
		fclose(f2);
		break;

	
	case 5: 
		printf ("\nPressione qualquer tecla para sair...\n\n");
		
		break;
		
	default:
		printf("\nOpcao invalida!\n\n");
		
		break;
		
	} //switch
	
	scanf("%c",&opt);
	scanf("%c",&opt);
	printf("\033[2J");
	printf("\033[0;0f"); //Limpa a tela

	} while (opcao != 5);
	
		
	return 0;
}
