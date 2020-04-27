#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"


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
