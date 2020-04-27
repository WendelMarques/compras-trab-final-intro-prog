#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"



/*############################################# MONTAM OS CABECALHOS DAS FUNCOES DO ARQUIVO itemFornecedor#############################################*/

/*EXEMPLO
┌──────────────────────────────────────────────────┐
│		    		 COMPRAS                       │
└──────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────┐
│  MENU PRINCIPAL > FORNECEDORES > LISTAR          │
├──────────────────────────────────────────────────┤
│  1) Ordenar lista por Situacao                   │
│  2) Ordenar lista por ano de cadastro            │
│  3) Voltar para o menu anterior                  │
└──────────────────────────────────────────────────┘
 */


void cabecalhoIncluirF(void)
{
	system("clear");
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "COMPRAS");
    criaMenuLinhaRodape(STRTAM);
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES > INCLUIR ");
    criaMenuLinhaRodape(STRTAM);
} //fim incluir

void cabecalhoConsultarF(void)
{
    system("clear");
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "COMPRAS");
    criaMenuLinhaRodape(STRTAM);
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES > CONSULTAR ");
    criaMenuLinhaRodape(STRTAM);
} //fim consultar

void cabecalhoListarF(void)
{
    system("clear");
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "COMPRAS");
    criaMenuLinhaRodape(STRTAM);
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES > LISTAR");
    criaMenuLinhaHorizontal(STRTAM);
} //fim listar

void cabecalhoExcluirF(void)
{
    system("clear");
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "COMPRAS");
    criaMenuLinhaRodape(STRTAM);
    criaMenuLinhaSuperior();
    criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES > EXCLUIR ");
    criaMenuLinhaRodape(STRTAM);
} //fim excluir

void cabecalhoAlterarF(void)
{
	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > FORNECEDORES > ALTERAR ");
	criaMenuLinhaRodape(STRTAM);
} //fim alterar
