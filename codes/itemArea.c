#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"


/**####################################################################################################################################################################################################

																				PRIMEIRO NIVEL

									Bloco correspondete ao item "2) Area", listado no menu principal, o qual chama uma das funcoes abaixo
																	de acordo com a escolha do usuario

																				1 - incluirA
																				2 - consultarA
																				3 - listarA
																				4 - exluirA
																				5 - alterarA
																				--
																				6 - Volta para o menu principal


									O arquivo itemAreaFuncoes.c contem as funcoes e alguns prototipos correspondentes as funcoes anteriores

####################################################################################################################################################################################################*/

void itemArea(void)
{

	int escolhaArea;
	FILE *criacaoArquivosDadosA;

	//cria o arquivo para "evitar o NULL" nas demais funcoes (avisos serão emitidos no decorrer da execucao quando o arquivo estiver vazio)
	if((criacaoArquivosDadosA = fopen("Areas.dat", "ab")) == NULL)
	{
		printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
		exit(1);
	}

	fclose(criacaoArquivosDadosA);

	//inicia a exibicao do menu
	do {
		system("clear");
		//monta o topo do menu, a parte central do cabecalho e desenha bordas
		menuPrincipalArea();

		printf("\n\n\t\t\t\t░ Digite uma opcao:\n");
		printf("\t\t\t\t░ ");
		scanf("%d", &escolhaArea);

		switch (escolhaArea) {
			case 1:
				incluirA();
				break;
			case 2:
				consultarA();
				break;

			case 3:
				listarA();
				break;

			case 4:
				excluirA();
				break;

			case 5:
				alterarA();
				break;

			case 6:
				escolhaArea = 0;
				break;
		}//s-case

	} while (escolhaArea != 0);

} //itemArea


void menuPrincipalArea(void) {
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS ");
	criaMenuLinhaHorizontal(STRTAM);
	criaMenuItem(STRTAM, "1) Incluir");
	criaMenuItem(STRTAM, "2) Consultar");
	criaMenuItem(STRTAM, "3) Listar");
	criaMenuItem(STRTAM, "4) Excluir");
	criaMenuItem(STRTAM, "5) Alterar");
	criaMenuItem(STRTAM, "6) Menu principal");
	criaMenuLinhaRodape(STRTAM);
}
