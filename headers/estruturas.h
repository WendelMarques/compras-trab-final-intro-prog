#include <stdio.h>
#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED



/*############################################# AREA #############################################*/


struct Area
{
	int codigo;
	char nome[100];
};



/*############################################# FORN #############################################*/

struct Fornecedor
{
	char cnpj[15]; //somente numeros
	char nome[150];
	char capitalSocial[100]; //permite cifrao
	char nomeRepresentante[150];
	char telefone[20]; //permite o formato +xx (xx) xxxx-xxxx
	int anoCadatro;
	char situacao; // A OU I
	int codArea;
};


#endif // ESTRUTURAS_H_INCLUDED
