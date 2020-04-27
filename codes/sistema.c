/**####################################################################################################################################################################################################
#Programa criado para fins da disciplina Introdução á Programação, da UFG, referente ao trabalho final.

#Autores: Daniel Machado/ Wendel Marques
#Última atualização: 11/12/2017


#Ele foi construido com base nas seguites informacoes

COMPRAS:
	Fornecedor: cnpj, nome, capitalSocial, nomeRepresentante, Telefone, anoCadastro, situacao, codArea; e,
	Area: codigo, nome.



ARQUIVOS MUNIPULADOS:
	fornecedores.dat
	areas.dat

/**####################################################################################################################################################################################################*/





/**####################################################################################################################################################################################################

																			MENU PRINCIPAL
												Blocos correspondentes ao menu principal,  o qual chama uma das funcoes abaixo
																	de acordo com a escolha do usuario

																		1 - itemFornecedor
																		2 - itemArea
																		3 - item_Listar_Forn_por_Area
																		--
																		4 - encerra o programa


####################################################################################################################################################################################################*/
#include <stdio.h>
#include <stdlib.h> //para system
#include "prototipos.h" //contem os prototipos das funcoes mais utilizadas



int main()
{
	montarMenu(); //funcao que monta o menu principal

	return 0;
}

void cabecalhoMenuPrincipal(void);

int montarMenu(void)
{

	int escolha; //escolha de uma das opcoes do menu

	do
    {
        cabecalhoMenuPrincipal(); //monta as bordas do menu principal, assim como
								  //exibe os itens do mesmo
		printf("\n\n\t\t\t\t░ Digite uma opcao:\n");
		printf("\t\t\t\t░ ");

		scanf("%d", &escolha);

		switch (escolha)
		{
			case 1:
				itemFornecedor();
				break;
			case 2:
				itemArea();
				break;

			case 3:
				item_Listar_Forn_por_Area();
				break;

			case 4:
				return 0;

		} //switch

	} while (escolha != 0);


	return 0;
} //fim monta menus

void cabecalhoMenuPrincipal(void)
{
		system("clear"); ///LIMPA A TELA NO LINUX
		criaMenuLinhaSuperior();
		criaMenuItem(STRTAM, "COMPRAS");
		criaMenuLinhaRodape(STRTAM);
		criaMenuLinhaSuperior();
		criaMenuItem(STRTAM, "MENU PRINCIPAL");
		criaMenuLinhaHorizontal(STRTAM);
		criaMenuItem(STRTAM, "1) Fornecedores");
		criaMenuItem(STRTAM, "2) Areas");
		criaMenuItem(STRTAM, "3) Listar fornecedores por area");
		criaMenuItem(STRTAM, "4) Encerrar");
		criaMenuLinhaRodape(STRTAM);
}
