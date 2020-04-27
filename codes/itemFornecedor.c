#include "prototipos.h"
#include <stdio.h>
#include <stdlib.h>


/**####################################################################################################################################################################################################

																				PRIMEIRO NIVEL

									Bloco correspondete ao item "1) Fornecedor", listado no menu principal, o qual chama uma das funcoes abaixo
																	de acordo com a escolha do usuario

																				1 - incluirF
																				2 - consultarF
																				3 - listarF
																				4 - exluirF
																				5 - alterarF
																				--
																				6 - Volta para o menu principal


									O arquivo itemFornecedorFuncoes.c contem as funcoes e alguns prototipos correspondentes as funcoes anteriores

####################################################################################################################################################################################################*/

void itemFornecedor(void)
{
	int escolhaForn;
	FILE *criacaoArquivosDadosF;

	//cria o arquivo para "evitar o NULL" nas demais funcoes (avisos serão emitidos no decorrer da execucao quando o arquivo estiver vazio)
	if((criacaoArquivosDadosF = fopen("Fornecedores.dat", "ab")) == NULL)
	{
		printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
		exit(1);
	}

	fclose(criacaoArquivosDadosF);

	//inicia a exibicao do menu
	do
    {
        system("clear"); //limpa a tela
		//monta o topo do menu, a parte central do cabecalho e desenha bordas
		menuPrincipalFornecedor();

		printf("\n\n\t\t\t\t░ Digite uma opcao:\n");
		printf("\t\t\t\t░ ");
		scanf("%d", &escolhaForn);

		switch (escolhaForn)
		{
			case 1:
				incluirF();
				break;
			case 2:
				consultarF();
				break;

			case 3:
				listarF();
				break;

			case 4:
				excluirF();
				break;

			case 5:
				alterarF();
				break;

			case 6:
				escolhaForn = 0;
				break;
		}//s-case

	} while (escolhaForn != 0);
} //itemFornecedor


void menuPrincipalFornecedor(void) {
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES ");
	criaMenuLinhaHorizontal(STRTAM);
	criaMenuItem(STRTAM, "1) Incluir");
	criaMenuItem(STRTAM, "2) Consultar");
	criaMenuItem(STRTAM, "3) Listar");
	criaMenuItem(STRTAM, "4) Excluir");
	criaMenuItem(STRTAM, "5) Alterar");
	criaMenuItem(STRTAM, "6) Menu principal");
	criaMenuLinhaRodape(STRTAM);
}
