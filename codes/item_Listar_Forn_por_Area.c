#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"
#include "estruturas.h"

/**####################################################################################################################################################################################################

																				PRIMEIRO NIVEL

									Bloco correspondete ao item "3) Listar fornecedor por area", listado no menu principal

									Listar os forncedores no seguinte formato:

									COD_AREA1 | NOME_AREA1
								    ────────────────────────────────────────────────────────────────────
								  			cnpj_f1    nome_f1     anoCadatro_f1   situacao_f1
									  	   	...          ...	          ...         ...


####################################################################################################################################################################################################*/


typedef struct Fornecedor FORNECEDOR;
typedef struct Area AREA;

void cabecalho_item3_msg_erro(void);

void item_Listar_Forn_por_Area(void)
{

	FILE *Arqfornecedor, *arqArea;
	FORNECEDOR forn;
	AREA area;
	char resposta;
	int cod, verificador;
	int verificadorNull = 0; //evita que a mesmo msg seja emita duas vezes

	//abre arquivos
	if((Arqfornecedor = fopen("Fornecedores.dat", "rb")) == NULL) {
		verificadorNull = 1;
		cabecalho_item3_msg_erro();
		printf("\n\n\t\t\t\t█ Não exite um banco de dados!\n\t\t\t\t█ Inclua um fornecedor ou uma area e tente novamente.\n\n\n\n");
		exit(1);
	}


	if((arqArea = fopen("Areas.dat", "rb")) == NULL) {

		if(verificadorNull != 1) {
			cabecalho_item3_msg_erro();
			printf("\n\n\t\t\t\t█ Não exite um banco de dados!\n\t\t\t\t█ Inclua um fornecedor ou uma area e tente novamente.\n\n\n\n");
		}
		exit(1);
	}

	verificador = 0;

	system("clear");
	printf("\n\n\t█ LISTAGEM DE FORNECEDORES DE ACORDO COM A AREA\n\n\n");


	//primeiro while, resposavel por fixar o cod da area
	while(fread(&area, sizeof(AREA), 1, arqArea) == 1)
	{

		cod = area.codigo;

		printf("\n\n\t──────────────────────────────────────────────────────────────────────────────────────────\n");
		printf("\t%-6i -   %s\n", cod, area.nome);
		printf("\t──────────────────────────────────────────────────────────────────────────────────────────\n");

		fseek(Arqfornecedor, 0, 0);

		//para cada codigo, uma varredura no arquivo dos fornecedores
		while(fread(&forn, sizeof(FORNECEDOR), 1, Arqfornecedor) == 1)
		{
			if(forn.codArea == cod) {
				verificador = 1;
				printf("\t\t%-18s", forn.cnpj);
				imprime_nome_item3(forn.nome);
				printf("%-12d", forn.anoCadatro);
				printf("%-13c\n", forn.situacao);
			}


		}//while - leitura de fornecedores.dat


		if(verificador == 0) {
			printf("\t\tNão há fornecedor cadastrado nesta area!\n");
		}

		printf("\n\n");

		verificador = 0;

	}//while - leitura de area.dat

	fclose(Arqfornecedor);
	fclose(arqArea);

	//verificacao de continuidade
	printf("\n\n\t░ Deseja encerrar o programa: [s/ n]\n");
	printf("\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
	   exit(1);

}


///Imprime apenas parte do nome do Fornecedor / ex: distribuidora varegista cosme damiao paulista ltda ----resulta em---> distribuidora varegista cosme damiao
//permite uma exibicao adequada para o usuario
void imprime_nome_item3(char string[])
{
	int cont = 0, i;
	char nome[150];

	for(i = 0; string[i] != '\0'; i++) {

		if(string[i] != '\0')
			nome[i] = string[i];

		if(string[i] == ' ')
			cont++;

		if(cont == 4) //enquanto nao tiver passado por quatro palavras
			break;		//o for nao é finalizado
	}					//e enquanto nao houver um \0

	nome[i] = '\0';

	printf("%-45s", nome);

}


void cabecalho_item3_msg_erro(void) {
	system("clear");
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "COMPRAS");
    criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "MENU PRINCIPAL > LISTAR FORN/ AREA ");
    criaMenuLinhaRodape(STRTAM);
}
