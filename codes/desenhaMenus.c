#include "prototipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

	AS SEGUINTES FUNCOES SAO RESPONSAVEL POR DESENHAR AS BORDAS DOS MENUS

*/




/*Desenha as bordas */
void criaMenuLinhaSuperior(void) {
	int i;

	printf("\t\t\t\t┌");

	for(i = 0; i < STRTAM; i++)
		printf("─");

	printf("┐\n");
}

void criaMenuLinhaRodape (int tamX) {
	int i;

	printf("\t\t\t\t└");

	for(i = 0; i < STRTAM; i++)
		printf("─");

	printf("┘\n");
}

void criaMenuLinhaHorizontal(int tamX) {
	int i;

	printf("\t\t\t\t├");
	for(i = 0; i < tamX; i++)
		printf("─");
	printf("┤\n");
}

void desenhaLinha(void) {
	int i;

	printf("\t\t\t\t");
	for(i = 0; i < STRTAM + 1; i++)
		printf("─");

	printf("\n");

}
//fim desenho de bordas



//permite que um item fique dentro das bordas
void criaMenuItem(int tamX, char str[]) {
	int i;
	int contaLetras = 0;

	for(i = 0; i < tamX; i++) {
		if(str[i] == '\0')
		break;

		else
		contaLetras++;
	}


	printf("\t\t\t\t│");

	//auxilia na centralizacao do cabecalho principal "compras"
	if(strcmp(str, "COMPRAS") == 0) {
		printf("\t\t");
		printf(" %11s", str);

		while(contaLetras < (tamX - 20)) {
			printf("%c", 32);
			contaLetras++;
		}
	}

	else {
		printf("  %s", str);

		while(contaLetras < tamX - 2) {
			printf("%c", 32);
			contaLetras++;
		}
	}

	printf("│\n");
}
