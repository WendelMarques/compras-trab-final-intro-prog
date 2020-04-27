#include <stdio.h>
#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED
#define STRTAM 50 //auxilia no enquadramento dos menus


/*#######################################################################################################################################################################################*/

// -------------------------------------------------------------MONTA O MENU PRINCIPAL-----------------------------------------------------------

int montarMenu(void);
	//Funcoes chamadas pela funcao MONTARMENU
void itemFornecedor(void);
void itemArea(void);
void item_Listar_Forn_por_Area(void);






/*#######################################################################################################################################################################################*/


// ---------------------------------------------_---------------itemFornecedor (principais)--------------------------------------------------------------------------------

void menuPrincipalFornecedor(void);
void incluirF(void);
void consultarF(void);
void listarF(void);
void excluirF(void);
void alterarF(void);
void imprimirF(void);

// ------------------------------------------------------------itemFornecedor (secundarias) --------------------------------------------------------------------------------

void flush_in(void);
void lerInformacoes(void); //chamada em inclurirF
void ordena_por_cnpj(void);//chamada em listarF
void ordena_por_situacao(void); //chamada em listarF
void ordena_por_ano(void); //chamada em listarF
int compara_ano(const void *, const void *); //chamada por qsort em ordena_por_ano



// --------------------------------------------------------MONTAGEM DOS CABECALHOS DOS FORNECEDORES  --------------------------------------------------------------------------------

void cabecalhoMenuPrincipalF(void);
void cabecalhoIncluirF(void);
void cabecalhoConsultarF(void);
void cabecalhoListarF(void);
void cabecalhoExcluirF(void);
void cabecalhoAlterarF(void);



/*#######################################################################################################################################################################################*/


// --------------------------------------------FUNCOES CORRESPONDENTES AS AREAS - [itemArea]----------------------------------------------------------------------------
void menuPrincipalArea(void);
void incluirA(void);
void consultarA(void);
void listarA(void);
void excluirA(void);
void alterarA(void);

// ------------------------------------------------------------------itemArea (secundarias)-------------------------------------------------------------------------------
void ordena_crescente(void);
void ordena_decrescente(void);
void lerInformacoesArea(void);

// --------------------------------------------------------------MONTAGEM DAS CABECALHOS DAS AREAS-----------------------------------------------------------------------
void cabecalhoIncluirA(void);
void cabecalhoConsultarA(void);
void cabecalhoListarA(void);
void cabecalhoExcluirA(void);
void cabecalhoAlterarA(void);


/*#######################################################################################################################################################################################*/

// --------------------------------------------------------------item_Listar_Forn_por_Area - DELIMITA A IMPRESSAO DO NOME DO FORNECEDOR-----------------------------------------------------------------------
void imprime_nome_item3(char[]);

/*#######################################################################################################################################################################################*/

// ------------------------------------------------------------------CRIAM AS BORDAS DOS MENUS-----------------------------------------------------------------------

void criaMenuItem(int, char[]);
void criaMenuLinhaSuperior(void);
void criaMenuLinhaRodape (int);
void criaMenuLinhaHorizontal(int);
void desenhaLinha(void);
void imprimeLinhaExibicoes(void);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------


#endif // PROTOTIPOS_H_INCLUDED
