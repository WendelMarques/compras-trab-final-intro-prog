#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "prototipos.h"


/**####################################################################################################################################################################################################
																SEGUNDO NIVEL - chamando por itemArea

Este arquivo contem:
 	> A struct referente aos dados dos fornecedor;
	> Funcoes principais: incluirA, consultarA, listarA, excluirA, alterarA; e,
	> Funcoes secundarias, que auxiliam no bom funcionamento das anteriores: imprimeDados, lerInformacoes, imprime_nome_area, ordena_crescente e ordena_decrescente

/**####################################################################################################################################################################################################*/


/*########################################################## ESTRUTURA UTILIZADA PARA O itemFornecedor #######################################################*/

typedef struct Area AREA;

//funcao secundaria, chamada por alterarA
void imprimeDados(AREA area)
{

	system("clear");
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "COMPRAS");
	criaMenuLinhaRodape(STRTAM);
	criaMenuLinhaSuperior();
	criaMenuItem(STRTAM, "MENU PRINCIPAL > AREAS > CONSULTAR ");
	criaMenuLinhaRodape(STRTAM);

	printf("\n\n\t\t\t\t█ Escolha uma da opções abaixo para alterar:\n\n\n");

	desenhaLinha();

	printf("\t\t\t\t1 - Codigo: ");
	printf("%d\n", area.codigo);
	printf("\t\t\t\t2 - Nome da Area: ");
	printf(" %s\n", area.nome);
	// printf("\t\t\t\t\n");
	printf("\n\t\t\t\tDigite 0 para cancelar\n");
	desenhaLinha();

}

/*################################################################### FUNCOES PRINCIPAIS #####################################################################*/

//inclui uma area
void incluirA(void)
{
	AREA area;
	char resposta;

	do {

		lerInformacoesArea();  //ler as informcacoes que serao incluidas no arquivo

		printf("\n\n\t\t\t\t░ Precisa incluir mais uma Area? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);
	} while(resposta != 'n' && resposta != 'N');
} //incluirA

//consulta uma area
void consultarA()
{

	AREA area;
	FILE *arqConsultar;
	int codigoProcurado;
	char resposta;
	int verificador = 1;

	do {

		if((arqConsultar = fopen("Areas.dat", "rb")) == NULL)
			exit(1);

		verificador = 1;
		cabecalhoConsultarA();

		printf("\n\n\t\t\t\t░ Digite o Codigo da area:\n");
		printf("\t\t\t\t░ ");
		scanf(" %d", &codigoProcurado);

		//varredura no arquivo em busca do codigoProcurado
		while(fread(&area, sizeof(AREA), 1, arqConsultar) == 1) {

			//se encontrado, entrara no if
			if(codigoProcurado == area.codigo) {

				cabecalhoConsultarA();

				printf("\n\n\t\t\t\t▓ Sua busca resultou na seguinte area:\n\n\n");

				desenhaLinha();

				printf("\t\t\t\tCodigo: ");
				printf("%d\n", area.codigo);
				printf("\t\t\t\tNome da area: ");
				printf("%s\n", area.nome);

				desenhaLinha();

				verificador = 0;
				break;
			}//if

		}//while interno

		fclose(arqConsultar);

		//se codigoProcurado nao for encontrado, entra nesse if
		if(verificador == 1) {
			cabecalhoConsultarA();
			printf("\n\n\t\t\t\t█ Area nao encontrada. \n\t\t\t\t█ Tente novamente!\n");
		}

		//verificacao de continuidade
		printf("\n\n\t\t\t\t░ Precisa consultar outra area? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);

	} while(resposta != 'n' && resposta != 'N');

}

//lista as areas em ordem crescente ou Decrescente
void listarA()
{

    int resposta;

	do {

		cabecalhoListarA();

        printf("\n\n");
		printf("\t\t\t\t░ Opcao: ");
		scanf(" %d", &resposta);


		switch (resposta) {
			case 1:
				ordena_crescente();
				break;

			case 2:
				ordena_decrescente();
				break;

			case 3:

				break;
		 }

	} while(resposta != 3);

}

//exclui uma area
void excluirA()
{

    AREA area;
    AREA estruturaNula = {0, ""}; //substituira a linha que o usuario quer excluir
    int areaProcurada;
    FILE *arqExcluir;
	int verificador = 0, posicao = 0;
	char respostasExclusao, resposta;

	do{

        posicao = 0;
		verificador = 0;
		cabecalhoExcluirA();

        printf("\n\n\t\t\t\t░ Digite o Codigo da area que deseja excluir \n");
		printf("\t\t\t\t░ (somente numeros): ");
		scanf(" %d", &areaProcurada);

		if((arqExcluir = fopen("Areas.dat", "rb+")) == NULL) {
			printf("\n\n\t\tNão existe um banco de dados ou nao foi possivel abri-lo!\n");
			exit(1);
		}

        //respontavel por procurar a area
		while (fread(&area, sizeof(AREA), 1, arqExcluir) == 1)
		{
			if(areaProcurada == area.codigo)
			{
				verificador = 1;

				cabecalhoExcluirA();

				//imprime as informcacoes da area quando for encontrado
				printf("\n\n\t\t\t\t▓ A sua busca resultou a seguinte area:\n");
				printf("\n\n");
				desenhaLinha();
				printf("\t\t\t\tCodigo: ");
				printf("%d\n", area.codigo);
				printf("\t\t\t\tNome da Area: ");
				printf("%s\n", area.nome);
				desenhaLinha();

                //verifica de o usuario realmente quer excluir
				printf("\n\n\t\t\t\t░ Realmente deseja excluir? [s/ n]\n");
				printf("\t\t\t\t░ ");
				scanf(" %c", &respostasExclusao);

				//se SIM:
				if(respostasExclusao == 's' || 'S') {
					//[pedir para alocar em outra area?]

					fseek(arqExcluir, posicao, SEEK_SET);
					fwrite(&estruturaNula, sizeof(AREA), 1, arqExcluir);

					cabecalhoExcluirA();

					printf("\n\n\t\t\t\t█ Area excluido com sucesso!\n\n");
				}
				break;
			}

			/*É aqui que a posição deve ser atualizada, no final do ciclo WHILE,
			sendo descolocado de + sizeof(AREA) a cada iteração do ciclo*/
			posicao = posicao + sizeof(AREA);

			/*Move posição de leitura/escrita de volta para a posição original*/
			fseek(arqExcluir, posicao, SEEK_SET);

		}

		//Entrará neste if se a area nao for encontrada no arquivo
		if(verificador == 0) {
			cabecalhoExcluirA();

			printf("\n\n\t\t\t\t█ Area %d nao encontrada.\n\t\t\t\t█ Tente novamente!\n\n", areaProcurada);

		}

		fclose(arqExcluir);

		//verifica se o usuario quer continuar ou voltar para o menu anterior
		printf("\n\n\t\t\t\t░ Deseja excluir outra Area? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);

	} while(resposta == 's' || resposta == 'S');

}

//altera uma area
void alterarA()
{
	AREA area;
	FILE *arqAlterar;
	int codigoProcurado;
	int posicao = 0;
	int achou, verificadorExistencia;
	char resposta;
	int opcao;

	cabecalhoAlterarA();

	printf("\n\n\t\t\t\t░ Digite o Codigo da area:\n");
	printf("\t\t\t\t░ ");
	scanf(" %d", &codigoProcurado);

	if((arqAlterar = fopen("Areas.dat", "rb+")) == NULL) {
		printf("\n\n\t\tNão existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

	verificadorExistencia = 1;

	//Etapa responsavel por procurar o arquivo
	while(fread(&area, sizeof(AREA), 1, arqAlterar)==1)
    {
		if(codigoProcurado == area.codigo)
        {

			imprimeDados(area); //quando encontrado, imprime suas informacoes p/ o usuario conferir

			printf("\n\n\t\t\t\t░ Escolha uma das opções:\n");
			printf("\t\t\t\t░ ");
			scanf(" %d", &opcao);

			//pergunta qual das informacoes ele deseja alterar
			switch (opcao) {
				case 1:
					cabecalhoAlterarA();
					verificadorExistencia = 0;
					printf("\n\n\t\t\t\t░ Digite o novo Codigo:");
					printf("\n\t\t\t\t░ ");
					scanf(" %d", &area.codigo);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&area,sizeof(AREA),1,arqAlterar) == sizeof(AREA);
					break;

				case 2:
					cabecalhoAlterarA();
					verificadorExistencia = 0;
					printf("\n\n\t\t\t\t░ Digite o novo nome da area:\n");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]s", area.nome);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&area,sizeof(AREA),1,arqAlterar) == sizeof(AREA);
					break;

				case 0:
					verificadorExistencia = 3;
					break;

				default:
					verificadorExistencia = 2;
					break;

			}

		}

		/*É aqui que a posição deve ser atualizada, no final do ciclo WHILE,
		sendo descolocado de +sizeof(CONTATO) a cada iteração do ciclo*/
		posicao = posicao + sizeof(AREA);

		/*Move posição de leitura/escrita de volta para a posição original*/
		fseek(arqAlterar, posicao, SEEK_SET);

	}

	fclose(arqAlterar);

	 //Se a Area for encontrado e alterado, entao informa isso ao usuario
	if (verificadorExistencia == 0) {
		cabecalhoAlterarA();

		printf("\n\n\t\t\t\t█ %d alterado com sucesso!\n\n", codigoProcurado);
	}


	//SE nao for encontrado, emite o aviso
	else
		if (verificadorExistencia == 1)
		{
		cabecalhoAlterarA();

		printf("\n\n\t\t\t\t█ Area %d nao foi encontrada!\n\n", codigoProcurado);

	}

	//caso ele digite um opcao invalida
	else
		if (verificadorExistencia == 2){
		cabecalhoAlterarA();

		printf("\n\n\t\t\t\t█ Opcao invalida! Tente novamente.\n\n");
	}



	printf("\n\n\t\t\t\t░ Deseja encerrar o programa? [s/ n] ");
	printf("\t\t\t\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
		exit(1);


}

/*################################################################### FUNCOES SECUNDARIAS #####################################################################*/

//Chamada por incluirA - ler as informacoes das areas
//e amarzena no arquivo
void lerInformacoesArea(void) {
	AREA area;
	FILE *arqIncluir, *arq;
	int codigoInformado;
	int verDupli = 1;

	cabecalhoIncluirA();


	printf("\n\n");
	printf("\t\t\t\t▓ Digite as informacoes solicitadas abaixo:\n");
	printf("\t\t\t\t░ Codigo: ");
	scanf(" %d", &codigoInformado);

	if((arq = fopen("Areas.dat", "rb")) == NULL) {
		printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
		exit(1);
	}

    //Verifica se codigojInformado já esta no arquvio, se estiver, verDupli recebe 0
	while(fread(&area, sizeof(AREA), 1, arq) == 1) {
		if(codigoInformado == area.codigo) {
			cabecalhoIncluirA();

			printf("\n\n\t\t\t\t█ %d já foi incluida anteriormente!\n\n", codigoInformado);
			verDupli = 0;
			break;
		}
	}

	fclose(arq);

    //Se o codigoInformado não estiver no arquivo, verDupli é igual a 1, entao
		//entra neste if, no qual as informacoes q devem se armazenadas sao lidas
	if(verDupli == 1) {

		if((arqIncluir = fopen("Areas.dat", "ab")) == NULL) {
			printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
			exit(1);
		}

		area.codigo = codigoInformado;

		printf("\t\t\t\t░ Nome da area: ");
		scanf(" %[^\n]s", area.nome);

		rewind(stdin); //limpa sobra de bytes

		//grava no arquivo as informacoes lidas
		fwrite(&area, sizeof(AREA), 1, arqIncluir);

		fclose(arqIncluir);

		cabecalhoIncluirA();

		printf("\n\n\t\t\t\t█ Area incluida com sucesso!\n\n");

	}//if
}

///INICIO - ORDENACOES - Chamadas por
void ordena_crescente(void) {
	AREA area;//estrutura
	int qtdAreas = 0; //armazena a quantidade de areas presentes no arquivo;
	FILE *arqListar;
	int i;
	int menor;
	int n, j;
	char resposta;
	long int aux;

	// flush_in();

	system("clear");
	printf("\n\n\t█ AREAS - ORDENACAO POR CODIGO | CRESCENTE  – ↓\n");

	printf("\n\n");
	if((arqListar = fopen("Areas.dat", "rb")) == NULL) {
		printf("\n\n\t\t\t\t█ Não existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

    //CALCULAR QUANTIDADE DE LINHAS  NO ARQUIVO//
	while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {

		if(area.codigo != 0)
			qtdAreas = qtdAreas + sizeof(AREA);
	}
	//armazena a quantidade de fornecedores presentes no arquivo;
	qtdAreas = qtdAreas / (sizeof(AREA));

	fclose(arqListar);

 	//FIM CALCULO DE LINHAS//

 	////PREENCHE O VETOR ordena_codigo COM TODOS OS CODIGOS//////
	int ordena_codigo[qtdAreas], codigo;

	i = 0;

	if((arqListar = fopen("Areas.dat", "rb")) == NULL) {
		printf("\n\n\t\t\t\t█ Não existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

	while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {

		codigo = area.codigo;
		if(codigo != 0) {
			ordena_codigo[i] = codigo;
			i++;
		}
	}

	fclose(arqListar);
	//////FIM BLOCO PREENCHIMENTO/////

 ///INICIO ORDENACAO DO VETOR ordena_codigo///
	for (i = 0; i < qtdAreas - 1; i++) {
		menor = i;
		for (j = i + 1; j < qtdAreas; j++) {
			if (ordena_codigo[j] < ordena_codigo[menor])
				menor = j;
		}

		if (i != menor) {
			aux = ordena_codigo[i];
			ordena_codigo[i] = ordena_codigo[menor];
			ordena_codigo[menor] = aux;
		}
	}
	///FIM ORDENACAO DO VETOR ///

    //////IMPRIME RESULTADO/////
	arqListar = fopen("Areas.dat", "rb");


	///imprime cabecalho
	printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");
	printf("\t%-18s%-25s\n", "CODIGO",
							"NOME");
	printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");

	///imprime areas
	for(i = 0; i < qtdAreas; i++) {

		fseek(arqListar, 0, 0); //garante que a leitura comece no inicio do arquivo
		while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {
			if(area.codigo == ordena_codigo[i]) {
				printf("\t%-18d", area.codigo);
				printf("%-25s\n", area.nome);
			}
		}
	}
	fclose(arqListar);
	///FIM IMPRESSAO DO RESULTADO//

    //Se nao conter dados, entra neste bif
	if(qtdAreas == 0)
		printf("\n\t█ Nao há areas cadastradas!\n\n");

	printf("\n\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");

	//verificacao de continuidade
	printf("\n\n\n\t░ Deseja encerrar o programa: [s/ n]\n");
	printf("\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
	   exit(1);
}

void ordena_decrescente(void) {
	AREA area;
	int qtdAreas = 0;
	FILE *arqListar;
	int i;
	int maior;
	int n, j;
	char resposta;
	long int aux;

	system("clear");
	printf("\n\n\t█ AREAS - ORDENACAO POR CODIGO | DESCRESCENTE – ↑\n");

	printf("\n\n");
	if((arqListar = fopen("Areas.dat", "rb")) == NULL) {
		printf("\n\n\t\t\t\t█ Não existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

    //CALCULAR QUANTIDADE DE LINHAS  NO ARQUIVO//
	while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {

		if(area.codigo != 0)
			qtdAreas = qtdAreas + sizeof(AREA);
	}
	//armazena a quantidade de fornecedores presentes no arquivo;
	qtdAreas = qtdAreas / (sizeof(AREA));

	fclose(arqListar);

 	//FIM CALCULO DE LINHAS//

 	////PREENCHE O VETOR ordena_codigo COM TODOS OS CODIGOS//////
	int ordena_codigo[qtdAreas], codigo;

	i = 0;

	if((arqListar = fopen("Areas.dat", "rb")) == NULL) {
		printf("\n\n\t\t\t\t█ Não existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

	while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {

		codigo = area.codigo;
		if(codigo != 0) {
			ordena_codigo[i] = codigo;
			i++;
		}
	}

	fclose(arqListar);
	//////FIM BLOCO PREENCHIMENTO/////

	///INICIO ORDENACAO DO VETOR ordena_codigo///
	for (i = 0; i < qtdAreas - 1; i++) {
		maior = i;
		for (j = i + 1; j < qtdAreas; j++) {
			if (ordena_codigo[j] > ordena_codigo[maior])
				maior = j;
		}

		if (i != maior) {
			aux = ordena_codigo[i];
			ordena_codigo[i] = ordena_codigo[maior];
			ordena_codigo[maior] = aux;
		}
	}
	///FIM ORDENACAO DO VETOR ///

    //////IMPRIME RESULTADO/////
	arqListar = fopen("Areas.dat", "rb");


	printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");
	printf("\t%-18s%-25s\n", "CODIGO",
							"NOME");
	printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");

	///imprime areas
	for(i = 0; i < qtdAreas; i++) {

		fseek(arqListar, 0, 0); //garante que a leitura comece no inicio do arquivo
		while(fread(&area, sizeof(AREA), 1, arqListar) == 1) {
			if(area.codigo == ordena_codigo[i]) {
				printf("\t%-18d", area.codigo);
				printf("%-25s\n", area.nome);
			}
		}
	}
	fclose(arqListar);
	///FIM IMPRESSAO DO RESULTADO//

    //Se nao conter dados, entra neste bif
	if(qtdAreas == 0)
		printf("\n\t\t\t\t█ Nao há areas cadastradas!\n\n");

	printf("\n\t───────────────────────────────────────────────────────────────────────────────────────────────────────────\n");

	//verificacao de continuidade
	printf("\n\n\n\t░ Deseja encerrar o programa: [s/ n]\n");
	printf("\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
	   exit(1);
}
