#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "prototipos.h"
#include <string.h>


/**####################################################################################################################################################################################################
																SEGUNDO NIVEL - chamando por itemFornecedor

Este arquivo contem:
 	> A struct referente aos dados dos fornecedor;
	> Funcoes principais: incluirF, consultarF, listarF, excluirF, alterarF; e,
	> Funcoes secundarias, que auxiliam no bom funcionamento das anteriores: imprimeDadosAlterar, lerInformacoes, imprime_nome_fornecedor, ordena_por_ano,
																			 ordena_por_situacao e compara_ano.

/**####################################################################################################################################################################################################*/




/*########################################################## ESTRUTURA UTILIZADA PARA O itemFornecedor #######################################################*/



typedef struct Fornecedor FORNECEDOR;

//chamada por alterarA
void imprimeDadosAlterar(struct Fornecedor); //prototipo


/*################################################################### FUNCOES PRINCIPAIS #####################################################################*/

//inclui um fornecedor
void incluirF(void)
{
	char resposta; //pergunta se o usuario deseja inserir outro fornecedor


	//enqunto o usuario digitar 's' ou 'S', o while roda
	do
	{

		lerInformacoes();  //ler as informcacoes que serao incluidas no arquivo

		printf("\n\n\t\t\t\t░ Precisa incluir mais um fornecedor? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);

	} while(resposta != 'n' && resposta != 'N');


} //INCLUIR_F

//consulta informacoes de um fornecedor
void consultarF(void)
{

	FORNECEDOR forn;
	FILE *arqConsultar;
	char cnpjProcurado[15];
	char resposta;
	int verificador = 1; //Se for alterado para 0, entao o cnpjProcurado foi encontrado no arquivo
							//caso contrario, continua com 1, entao emite um aviso sobre a inexitencia do fornecedor

	do
	{

		if((arqConsultar = fopen("Fornecedores.dat", "rb")) == NULL)
			exit(1);

		verificador = 1;
		cabecalhoConsultarF(); //chama a funcao que monta o cabecalho p/ consultarF

		printf("\n\n\t\t\t\t░ Digite o CNPJ do fornecedor: ");
		scanf(" %[^\n]", cnpjProcurado); //cnpj que o usuario deseja consultar

		//varredura no arquivo em busca do cnpjInformado
		while(fread(&forn, sizeof(FORNECEDOR), 1, arqConsultar) == 1) {

			//se encontrado, entrará no if
			if(strcmp(cnpjProcurado, forn.cnpj) == 0) {

				cabecalhoConsultarF();
				//em seguida imprime as informacoes da empresa
				printf("\n\n\t\t\t\t▓ Sua busca resultou no seguinte fornecedor:\n");

				printf("\n\n");
				desenhaLinha();
				printf("\t\t\t\tCNPJ: ");
				printf("%s\n", forn.cnpj);
				printf("\t\t\t\tNome da empresa: ");
				printf("%s\n", forn.nome);
				printf("\t\t\t\tCapital social: ");
				printf("%s\n", forn.capitalSocial);
				printf("\t\t\t\tNome do representante: ");
				printf("%s\n", forn.nomeRepresentante);
				printf("\t\t\t\tTelefone: ");
				printf("%s\n", forn.telefone);
				printf("\t\t\t\tSituacao:"); ///Imprime INATIVO para I ou ATIVO para A

				if(forn.situacao == 'A' || forn.situacao == 'a')
					printf(" %s", "Ativo\n");

				else if(forn.situacao == 'I' || forn.situacao == 'i')
					printf(" %s", "Inativo\n");

				printf("\t\t\t\tAno de Cadastro: ");
				printf("%d\n", forn.anoCadatro);
				printf("\t\t\t\tCodigo da area: ");
				printf("%d\n", forn.codArea);

				desenhaLinha();

				verificador = 0;
				break;
			}//if

		}//while interno

		fclose(arqConsultar);

		//se cnpjProcurado nao for encontrado, entra nesse if
		if(verificador == 1) {
			cabecalhoConsultarF();
			printf("\n\n\t\t\t\t█ Fornecedor nao encontrado. \n\t\t\t\t█ Tente novamente!\n");
		}

		//verificacao de continuidade
		printf("\n\n\t\t\t\t░ Precisa consultar outro fornecedor? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);

	} while(resposta != 'n' && resposta != 'N');
} ///consultarF

//lista os fornecedores de acordo com a ordenacao escolhida
void listarF()
{
	int resposta;

	//O usuario deve escolher uma das opcoes de ordenacao
	do {

		cabecalhoListarF();
		criaMenuItem(STRTAM, "1) Ordenar lista por Situacao");
		criaMenuItem(STRTAM, "2) Ordenar lista por ano de cadastro");
		criaMenuItem(STRTAM, "3) Voltar para o menu anterior");
		criaMenuLinhaRodape(STRTAM);

		printf("\n\n");
		printf("\t\t\t\t░ Opcao: ");
		scanf(" %d", &resposta);

		switch (resposta) {
			case 1:
				ordena_por_situacao(); //ordena agrupada a lista dos fornecedores em dois bloco (Ativos e Inativos)
				break;

			case 2:
				ordena_por_ano(); //ordena a lista por ano
				break;

			case 3:
				break;

		 } //switch

	} while(resposta != 3);


} ///listarF

//exclui um fornecedor
void excluirF()
{

	FORNECEDOR forn; //estrutura principal, utilizada para varrer o arquivo
	FORNECEDOR estruturaNula = {"", "", "", "", "", 0, ' ', 0}; //estrutura que subistituirá a linha q o usuario deseja excluir
	char fornProcurado[15];
	FILE *arqExcluir;
	int verificador = 0, posicao = 0;
	char respostasExclusao, resposta, situacao;

	do
	{
		posicao = 0;
		verificador = 0;
		// flush_in(); //esvazia o buffer, tipo fflush
		cabecalhoExcluirF();

		printf("\n\n\t\t\t\t░ Digite o CNPJ do fornecedor que deseja excluir \n");
		printf("\t\t\t\t░ (somento numeros): ");
		scanf(" %[^\n]", fornProcurado);

		if((arqExcluir = fopen("Fornecedores.dat", "rb+")) == NULL)
		{
			printf("\n\n\t\tNão existe um banco de dados ou nao foi possivel abri-lo!\n");
			exit(1);
		}

		//respontavel por procurar o fornecedor
		while (fread(&forn, sizeof(FORNECEDOR), 1, arqExcluir) == 1)
		{
			if(strcmp(fornProcurado, forn.cnpj) == 0)
			{
				verificador = 1;
				situacao = forn.situacao;
				cabecalhoExcluirF();

				//imprime as informcacoes do forn quando for encontrado
				printf("\n\n\t\t\t\t▓ A sua busca resultou no seguinte fornecedor:\n");
				printf("\n\n");
				desenhaLinha();
				printf("\t\t\t\tCNPJ: ");
				printf("%s\n", forn.cnpj);
				printf("\t\t\t\tNome da empresa: ");
				printf("%s\n", forn.nome);
				printf("\t\t\t\tSituacao: ");

						if(situacao == 'A' || situacao == 'a') ///Imprime INATIVO para I ou ATIVO para A
						printf("%s", "Ativo\n");

						else if(situacao == 'I' || situacao == 'i')
						printf("%s", "Inativo\n");

				printf("\t\t\t\tCodigo da area: ");
				printf("%d\n", forn.codArea);
				desenhaLinha();


				//verifica se o usuario realmente quer excluir
				printf("\n\n\t\t\t\t░ Realmente deseja excluir? [s/ n]\n");
				printf("\t\t\t\t░ ");
				scanf(" %c", &respostasExclusao);

				//se SIM, entrará neste if
				if(respostasExclusao == 's' || respostasExclusao == 'S')
				{
					fseek(arqExcluir, posicao, SEEK_SET);
					fwrite(&estruturaNula, sizeof(FORNECEDOR), 1, arqExcluir);
					cabecalhoExcluirF();

					printf("\n\n\t\t\t\t█ Fornecedor excluido com sucesso!\n\n");
				}

				break;
			} //if


			/*É aqui que a posição é atualizada, no final do ciclo WHILE,
			sendo descolocado de + sizeof(FORNECEDOR) a cada iteração do ciclo*/
			posicao = posicao + sizeof(FORNECEDOR);

			/*Move posição de leitura/escrita de volta para a posição original*/
			fseek(arqExcluir, posicao, SEEK_SET);

		}//while

		fclose(arqExcluir);

		///Entrará neste if se o fornecedor nao for encontrado no arquivo
		if(verificador == 0)
		{

			cabecalhoExcluirF();

			printf("\n\n\t\t\t\t█ Fornecedor %s nao encontrado.\n\t\t\t\t█ Tente novamente!\n\n", fornProcurado);

		}

		//verifica se o usuario quer continuar ou voltar para o menu anterior
		printf("\n\n\t\t\t\t░ Deseja excluir outro fornecedor? [s/ n]\n");
		printf("\t\t\t\t░ ");
		scanf(" %c", &resposta);

	} while(resposta == 's' || resposta == 'S');

} ///excluirF

//altera um fornecedor
void alterarF()
{

	FORNECEDOR forn;
	FILE *arqAlterar;
	char cnpjProcurado[15], novo_cnpj[15];
	int posicao = 0;
	int verificador;
	char resposta;
	int opcao;


	cabecalhoAlterarF();

	// flush_in(); // limpa os caracteres que ainda estiverem na entrada padrão stdin
	printf("\n\n\t\t\t\t░ Digite o CNPJ do fornecedor:\n");
	printf("\t\t\t\t░ ");
	scanf(" %[^\n]", cnpjProcurado);

	if((arqAlterar = fopen("Fornecedores.dat", "rb+")) == NULL)
	{
		printf("\n\n\t\tNão existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

	verificador = 1;

	//Etapa responsavel por procurar o arquivo
	while(fread(&forn, sizeof(FORNECEDOR), 1, arqAlterar)==1)
    {
		if(strcmp(cnpjProcurado, forn.cnpj) == 0)
        {

			imprimeDadosAlterar(forn); //quando encontrado, imprime suas informacoes p/ o usuario conferir

			printf("\n\n\t\t\t\t░ Escolha uma das opções:\n");
			printf("\t\t\t\t░ ");
			scanf(" %d", &opcao);
			// flush_in();



			//pergunta qual das informacoes ele deseja alterar
			switch (opcao) {
				//altera cnpj
				case 1:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o novo CNPJ(somente numeros):");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]", novo_cnpj);

					while(strlen(novo_cnpj) < 14 || strlen(novo_cnpj) > 14) {
						system("clear");
						cabecalhoAlterarF();
						printf("\n\n\t\t\t\t█ O CNPJ informado é invalido! \n\n");


						printf("\n\t\t\t\t▓ Digite o novo CNPJ (com 14 caracteres)\n");
						printf("\t\t\t\t░ CNPJ (somente numeros): ");
						scanf(" %[^\n]", novo_cnpj);

					}

					if(strlen(novo_cnpj) == 14)
						strcpy(forn.cnpj, novo_cnpj);

					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera nome
				case 2:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o novo nome da empresa:\n");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]", forn.nome);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;


				//altera capital social
				case 3:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o novo capital social (formato R$ XX.XXX,XX): ");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]", forn.capitalSocial);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera nome do representante
				case 4:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o nome do novo representante: ");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]", forn.nomeRepresentante);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera fone
				case 5:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o novo telefone:");
					printf("\n\t\t\t\t░ ");
					scanf(" %[^\n]", forn.telefone);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera ano de cadastro
				case 6:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o ano de cadastro:");
					printf("\n\t\t\t\t░ ");
					scanf(" %d", &forn.anoCadatro);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera situacao
				case 7:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite a nova situacao: [A/ I]");
					printf("\n\t\t\t\t░ ");
					scanf(" %c", &forn.situacao);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//altera cod area
				case 8:
					cabecalhoAlterarF();
					verificador = 0;

					printf("\n\n\t\t\t\t░ Digite o novo codigo da area:");
					printf("\n\t\t\t\t░ ");
					scanf(" %d", &forn.codArea);


					fseek(arqAlterar, posicao, SEEK_SET);
					fwrite(&forn,sizeof(FORNECEDOR),1,arqAlterar) == sizeof(FORNECEDOR);
					break;

				//auxilia nos casos de teste a execucao deste switch case
				case 0:
					verificador = 3;
					break;

				//auxilia nos casos de teste a execucao deste switch case
				default:
					verificador = 2;
					break;

			} //switch

		}//if

		/*É aqui que a posição deve ser atualizada, no final do ciclo WHILE,
		sendo descolocado de +sizeof(CONTATO) a cada iteração do ciclo*/
		posicao = posicao + sizeof(FORNECEDOR);

		/*Move posição de leitura/escrita de volta para a posição original*/
		fseek(arqAlterar, posicao, SEEK_SET);

	} //while

	fclose(arqAlterar);

	//Se o Fornecedor nao for encontrado, emite o aviso
	if (verificador == 0)
	{
		cabecalhoAlterarF();

		printf("\n\n\t\t\t\t█ %s alterado com sucesso!\n\n", cnpjProcurado);
	}


	//SE for encontrado e alterado, entao informa isso ao usuario
	else
		if (verificador == 1)
		{
		cabecalhoAlterarF();

		printf("\n\n\t\t\t\t█ Fornecedor %s nao foi encontrado!\n\n", cnpjProcurado);

		}

	//caso ele digite um opcao invalida
	else
		if (verificador == 2)
		{
		cabecalhoAlterarF();

		printf("\n\n\t\t\t\t█ Opcao invalida! Tente novamente.\n\n");
		}


	printf("\n\n\t\t\t\t░ Deseja encerrar o programa? [s/ n] ");
	printf("\n\t\t\t\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
		exit(1);

} //alterarF

/*################################################################### FUNCOES SECUNDARIAS #####################################################################*/
	//isto é, chamadas pelas principais


//Chamada por incluirF - ler as informacoes dos fornecedores e armazena no arquivo
void lerInformacoes(void)
{
	FORNECEDOR forn;
	FILE *arqIncluir, *arq;
	char cnpjInformado[15], cnpjAdd[15];
	int verDupli = 1; //auxilia na verificacao de duplicadade

	system("clear"); //limpa a tela no linux
	cabecalhoIncluirF(); //chama a funcao que monta o cabecalho p/ incluirF

	printf("\n\n\t\t\t\t▓ Digite as informacoes solicitadas abaixo:\n");
	printf("\t\t\t\t░ CNPJ (somente numeros): ");
	scanf(" %[^\n]", cnpjAdd);

	//valida a entrada do cnpj, ou seja, so para de pedir o cnpj quando o mesmo tiver 14 caracteres validos
	while(strlen(cnpjAdd) < 14 || strlen(cnpjAdd) > 14)
	{
		system("clear");
		cabecalhoIncluirF(); //monta o cabecalho
		printf("\n\n\t\t\t\t█ O CNPJ informado é invalido! \n\n");


		printf("\n\t\t\t\t▓ Digite um CNPJ que contenha exatos 14 caracteres.\n");
		printf("\t\t\t\t░ CNPJ (somente numeros): ");
		scanf(" %[^\n]", cnpjAdd);
		verDupli = 1;

	}

	strcpy(cnpjInformado, cnpjAdd);
	//abre o arquivo
	if((arq = fopen("Fornecedores.dat", "rb")) == NULL)
	{
		printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
		exit(1);
	}

	//Verifica se cnpjInformado já esta no arquvio, se estiver, verDupli recebe 0
	while(fread(&forn, sizeof(FORNECEDOR), 1, arq) == 1)
	{

		//se entrar no if, quer dizer que o forn informado ja existe no banco de dados
			//um mensagem é emitada
		if(strcmp(cnpjInformado, forn.cnpj) == 0)
		{
			system("clear"); //limpa a tela no linux
			cabecalhoIncluirF();

			printf("\n\n\t\t\t\t█ %s já foi incluido anteriormente!\n\n", cnpjInformado);
			verDupli = 0;

			break;
		}
	}

	fclose(arq); //fecha o arquivo

	//Se o cnpjInformado não estiver no arquivo, verDupli é igual a 1, como foi declarado, entao
		//entra neste if, no qual as informacoes q devem se armazenadas sao lidas
	if(verDupli == 1)
	{

		//abre o arquivo novamente de outro modo
		if((arqIncluir = fopen("Fornecedores.dat", "ab")) == NULL)
		{
			printf("O arquvivo nao pode ser aberto ou criado. Tente novamente!");
			exit(1);
		}

		cabecalhoIncluirF();

		printf("\n\n\t\t\t\t▓ Digite as informacoes solicitadas:\n\n");
		strcpy(forn.cnpj, cnpjInformado);

		printf("\t\t\t\t░ Nome da empresa: ");
		scanf(" %[^\n]", forn.nome);

		printf("\t\t\t\t░ Capital social (c/ cifrão): ");
		scanf(" %[^\n]", forn.capitalSocial);

		printf("\t\t\t\t░ Nome e ultimo sobrenome do representante: ");
		scanf(" %[^\n]", forn.nomeRepresentante);

		printf("\t\t\t\t░ Telefone: ");
		scanf(" %[^\n]", forn.telefone);

		printf("\t\t\t\t░ Ano de cadastro: ");
		scanf(" %d", &forn.anoCadatro);

		printf("\t\t\t\t░ Situacao [A ou I]: ");
		scanf(" %c", &forn.situacao);

		printf("\t\t\t\t░ Codigo da area: ");
		scanf(" %d", &forn.codArea);

		rewind(stdin); //limpa sobra de bytes

		//grava no arquivo as informacoes lidas
		fwrite(&forn, sizeof(FORNECEDOR), 1, arqIncluir);

		fclose(arqIncluir);

		system("clear"); //limpa a tela no linux
		cabecalhoIncluirF();

		printf("\n\n\t\t\t\t█ Fornecedor incluido com sucesso!\n\n");

	}//if
}

///Imprime apenas parte do nome do Fornecedor / ex: distribuidora cosme damiao paulista ltda ----resulta em---> distribuidora cosme damiao
//chamada por: ordena_por_situacao e ordena_por_ano - as quais sao chamadas por listarF
//permite uma exibicao adequada para o usuario
void imprime_nome_fornecedor (char string[])
{
	int cont = 0, i;
	char nome[150];

	for(i = 0; string[i] != '\0'; i++) {

		if(string[i] != '\0')
			nome[i] = string[i];

		if(string[i] == ' ')
			cont++;

		if(cont == 4) //enquanto nao tiver passado por 4 palavras
			break;		//o for nao é finalizado
	}					//e enquanto nao houver um \0

	nome[i] = '\0';

	printf("%-45s", nome);

}

//Ordena os fornecedores por situacao| chamadas por listarF
void ordena_por_situacao(void)
{
	FILE *arqSituacao;
	FORNECEDOR forn;
	int verificador = 1; //verifica se ha itens em cada classificacao(I e A)
	int qtdFornecedores = 0; //calcula a qtd de fornecedores armazenados
	char resposta;

	// flush_in();
	system("clear");
	printf("\n\n\t█ FORNECEDORES AGRUPADOS POR SITUAÇÃO\n\n\n");

	printf("\n\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");
	printf("\t%-18s%-46s%-12s%-17s%-4s\n",
											"CNPJ",
											"NOME",
											"ANO",
											"SITUACAO",
											"COD. AREA");
   printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");

   arqSituacao = fopen("Fornecedores.dat", "rb");

	//IMPRIME PRIMEIRAMENTE OS ATIVOS
	//varre o arquivo
	while(fread(&forn, sizeof(FORNECEDOR), 1, arqSituacao) == 1)
	{

		if(forn.situacao == 'A' || forn.situacao == 'a')
		{
			verificador = 0;
			printf("\t%-18s", forn.cnpj);
			imprime_nome_fornecedor(forn.nome);
			printf("\t%-12d", forn.anoCadatro);
			printf("\t%-13c", forn.situacao);
			printf("\t%-4d\n", forn.codArea);

			qtdFornecedores++;
		}

	}

	fclose(arqSituacao);

	arqSituacao = fopen("Fornecedores.dat", "rb");

	//IMPRIME EM SEGUIDA OS INATIVOS
	while(fread(&forn, sizeof(FORNECEDOR), 1, arqSituacao) == 1)
	{

		if(forn.situacao == 'I' || forn.situacao == 'i')
		{
			verificador = 0;
			printf("\t%-18s", forn.cnpj);
			imprime_nome_fornecedor(forn.nome);
			printf("\t%-12d", forn.anoCadatro);
			printf("\t%-13c", forn.situacao);
			printf("\t%-4d\n", forn.codArea);

			qtdFornecedores++;
		}

	}

	fclose(arqSituacao);
	////FIM - INATIVOS////

	if(verificador == 1)
		printf("\n\n\t█ Nao ha fornecedores cadastrados no momento!\n\n");


	printf("\n\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");

	//imprime q qtd de fornecedores armazenados
	printf("\n\n\n\tQUANTIDADE DE FORNCEDORES: %d\n", qtdFornecedores);

	//verificacao de continuidade
	printf("\n\n\n\t░ Deseja encerrar o programa: [s/ n]\n");
	printf("\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
	   exit(1);

}

//Ordena os fornecedores por ano em ordem crescente| chamadas por listarF
void ordena_por_ano(void)
{

	/*
		Esta funcao ordena os fornecedores por ano. Ela calcula a quantidade de itens no arquivo, armazena os anos
		em um vetor, em seguida o ordena. Por fim, varre o arquivo ao mesmo tempo que imprime na tela do usuario
		informacoes dos forn, entretanto, a saida é de acordo com a ordem do vetor.
	*/

	FORNECEDOR forn;
	int i = 0, j = 0, verificadorAno = 1;
	char c;
	FILE *arqAno;
	char resposta;
	int tamanho_vetor = 0;
	int qtdFornecedores = 0; //calcula a qtd de forn armazenados

	system("clear");
	printf("\n\n\t█ FORNECEDORES ORDENADOS POR ANO – ↓\n\n\n");


	//##### CALCULA QUANTIDADE DE ITENS NO ARQUIVO  #####
	if((arqAno = fopen("Fornecedores.dat", "rb")) == NULL)
	{
		system("clear");
		printf("\n\n\t\t\t\t\tNão existe um banco de dados ou nao foi possivel abri-lo!\n");
		exit(1);
	}

	while(fread(&forn, sizeof(FORNECEDOR), 1, arqAno) == 1) {

		//diferente de 0 por causa da estrutura nula usada na funcao excluirF
		if(forn.anoCadatro != 0 && (strlen(forn.cnpj) == 14))
			qtdFornecedores = qtdFornecedores + sizeof(FORNECEDOR); //calcula a qtd de forn armazenados

	} //while

	qtdFornecedores = qtdFornecedores / (sizeof(FORNECEDOR));

	fclose(arqAno);
	//##### FIM  - CALCULO DE ITENS #####


 	/*##### INICIO PREENCHE O VETOR ordena_ano COM OS ANOS ##### */

	int ordena_ano[qtdFornecedores];

	arqAno = fopen("Fornecedores.dat", "rb");

	while(fread(&forn, sizeof(FORNECEDOR), 1, arqAno) == 1)
	{
		verificadorAno = 1;
		if(forn.anoCadatro != 0 && (strlen(forn.cnpj) == 14))
		{

			//evita que um determinado ano seja incluida mais de uma vezes no array
			for(j = 0; j < tamanho_vetor; j++)
			{
				if(forn.anoCadatro == ordena_ano[j])
				{
					verificadorAno = 0;
					break;
				}
			} //for

			if(verificadorAno == 1)
			{
				ordena_ano[tamanho_vetor] = forn.anoCadatro;
				tamanho_vetor++;
			} //if interno

		} //ifexterno
	} //while

	fclose(arqAno);
	//##### FIM PREENCHIMENTO DO VETOR Q SERA ORDENADO #####



	//ORDENACAO POR ANO - qsort no auxilio da ordenacao
	qsort(ordena_ano, tamanho_vetor, sizeof(int), compara_ano);


	 //INICIO IMPRIME RESULTADO

	//cabecalho
	printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");
	printf("\t%-18s%-46s%-12s%-17s%-4s\n",
											"CNPJ",
											"NOME",
											"ANO",
											"SITUACAO",
											"COD. AREA");
   printf("\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");

   arqAno = fopen("Fornecedores.dat", "rb");

   for(i = 0; i < tamanho_vetor; i++)
   {
		fseek(arqAno, 0, 0); //posiciona no inicio do arquivo
		while(fread(&forn, sizeof(FORNECEDOR), 1, arqAno) == 1)
		{
			//imprime os fornecedores de acordo com a ordem do vetor ordena_ano
			if(forn.anoCadatro == ordena_ano[i] && (strlen(forn.cnpj) == 14))
			{
				printf("\t%-18s", forn.cnpj);
				imprime_nome_fornecedor(forn.nome);
				printf("\t%-12d", ordena_ano[i]);
				printf("\t%-13c", forn.situacao);
				printf("\t%-4d\n", forn.codArea);
			} //if
		}//while
	}//for


	fclose(arqAno);
	/////FIM IMPRIME /////

	//se nao houver fornecedores cadastrados, entrara no seguinte if
	if(qtdFornecedores == 0)
		printf("\n\t█ Nao ha fornecedores cadastrados!\n\n");

	printf("\n\t──────────────────────────────────────────────────────────────────────────────────────────────────────\n");

	printf("\n\n\n\tQUANTIDADE DE FORNCEDORES: %d\n", qtdFornecedores);

	//verificacao de continuidade
	printf("\n\n\n\t░ Deseja encerrar o programa: [s/ n]\n");
	printf("\t░ ");
	scanf(" %c", &resposta);

	if(resposta == 's' || resposta == 'S')
	   exit(1);
}

//chamada por qsort - funcao para comparar inteiros (utilizada em ordena_por_ano)
int compara_ano(const void *a, const void *b)
{
	const int *pa = (const int *)a; //modifica o tipo do ponteiro
	const int *pb = (const int *)b;

	//retorna negativo se a < b e positivo se a > b
	return *pa - *pb;
}

//Imprime dados do forn procurado pelo usuario // chamada por alterarF
void imprimeDadosAlterar(FORNECEDOR forn)
{

	cabecalhoConsultarF();

	printf("\n\n\t\t\t\t█ Escolha uma da opções abaixo para alterar:\n\n\n");

	desenhaLinha();

	printf("\t\t\t\t1 - CNPJ: ");
	printf(" %s\n", forn.cnpj);
	printf("\t\t\t\t2 - Nome da empresa: ");
	printf(" %s\n", forn.nome);
	printf("\t\t\t\t3 - Capital social: ");
	printf(" %s\n", forn.capitalSocial);
	printf("\t\t\t\t4 - Nome e ultimo sobrenome do representante: ");
	printf(" %s\n", forn.nomeRepresentante);
	printf("\t\t\t\t5 - Telefone: ");
	printf(" %s\n", forn.telefone);
	printf("\t\t\t\t6 - Ano de cadastro: ");
	printf(" %d\n", forn.anoCadatro);
	printf("\t\t\t\t7 - Situacao: ");
	printf(" %c\n", forn.situacao);
	printf("\t\t\t\t8 - Codigo da area: ");
	printf(" %d\n", forn.codArea);
	// printf("\t\t\t\t\n");
	printf("\n\t\t\t\tDigite 0 para cancelar\n");
	desenhaLinha();

}


//Funcionamento semelhante a funcao fflush  // esvazia o buffer
// limpa os caracteres que ainda estiverem na entrada padrão stdin
// void flush_in()
// {
// 	int ch;
//
// 	while ((ch = fgetc (stdin)) != '\n' && ch != EOF)
// 	{
//
// 	}
// }
