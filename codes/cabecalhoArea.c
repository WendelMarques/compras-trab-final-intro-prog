#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

/*############################################# MONTAM OS CABECALHOS DAS FUNCOES DO ARQUIVO itemFornecedor#############################################*/

/*EXEMPLO
┌──────────────────────────────────────────────────┐
│		    		 COMPRAS                       │
└──────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────┐
│  MENU PRINCIPAL > AREA  > LISTAR          │
├──────────────────────────────────────────────────┤
│  1) Ordenar lista por Situacao                   │
│  2) Ordenar lista por ano de cadastro            │
│  3) Voltar para o menu anterior                  │
└──────────────────────────────────────────────────┘
 */


void cabecalhoIncluirA(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > INCLUIR ");
	criaMenuLinhaRodape(STRTAM);

}

void cabecalhoConsultarA(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > CONSULTAR ");
	criaMenuLinhaRodape(STRTAM);
}

void cabecalhoListarA(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > LISTAR");
	criaMenuLinhaHorizontal(STRTAM);
	criaMenuItem(STRTAM, "1) Ordenar lista por Codigo Crescente");
	criaMenuItem(STRTAM, "2) Ordenar lista por Codigo Decrescente");
	criaMenuItem(STRTAM, "3) Voltar para o menu anterior");
	criaMenuLinhaRodape(STRTAM);
}

void cabecalhoExcluirA(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > EXCLUIR ");
	criaMenuLinhaRodape(STRTAM);
}

void cabecalhoAlterarA(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > ALTERAR ");
	criaMenuLinhaRodape(STRTAM);

}
