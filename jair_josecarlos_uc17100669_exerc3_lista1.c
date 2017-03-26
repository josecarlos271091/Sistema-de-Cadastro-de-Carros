// Aluno: Jose Carlos
//Matricula: UC17100669

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //usar para funcoes String. 
#define QTD_MAX_CARROS 4
#define TAM_PLACA 8
/* 
Sintese:
Objetivo: Controle de Cadastro de Veiculos Antigos.
Entrada: Quantidade de carros, placa do carro (unica), valor de adquisicao.
Saida: Carros listados filtrados pelas tres primeiras letras da placa.
*/

//Prototipos das funções
int leInt(char msg[]);
int leValidaInt(char msg[], int min, int max);
float leFloat(char msg[]);
void leString(char str[],int tamMax);
void strlower(char str[]);
void strupper(char str[]);
int verificaPlacaRepetida(char placas[][TAM_PLACA], int posicao);
void cadastrarCarro(char placas[][TAM_PLACA],float valores[], int qtdCarros);
void apresentaCarros(char placas[][TAM_PLACA],float valores[],char palavraChave[], int qtdCarros);

int main() {  
//Declarações
    char placas[QTD_MAX_CARROS][TAM_PLACA],palavraChave[4],opcao;
    float valores[QTD_MAX_CARROS];
    int contCarros = 0;
//Instruções
    do{
        printf("\n\n------------------------- SISTEMA DE CADASTRO DE CARROS ANTIGOS -------------------------\n\n\n");
        printf("MENU:\n\nC - Cadastrar\nL - Listar\nE - Encerrar\n\nOpcao: ");
        fflush(stdin);
	    scanf("%c",&opcao);
        opcao = toupper(opcao);
        system("cls");

        switch(opcao) {
        case 'C': { // CADASTRAR
        if(contCarros >= QTD_MAX_CARROS){
        	printf("Sistema de cadastrado cheio!.");
        	break;
		}
        cadastrarCarro(placas,valores,contCarros);
        contCarros++;
        break;
        }
        case 'L': { // LISTAR
        leString(palavraChave,4);
        strupper(palavraChave);
        apresentaCarros(placas,valores,palavraChave,contCarros);
        break;
        }
        case 'E': {
        system("exit");
        break;
        }
        default :
        printf("Opcao Invalida!!");
        break;
        }
   }while(opcao!='E');

	return 0;
}

//Objetivo: Ler um número do tipo int
//Parâmetros: referência ao vetor msg.
//Retorno: número tipo int lido.
int leInt(char msg[]){
	int ret;
	int num;
	do{
		printf("%s", msg);
		fflush(stdin);
		ret = scanf("%d",&num);
		if (ret == 0)
			printf("Favor digitar numeros.\n");
	}while (ret == 0 );

	return num;
}

//Objetivo: Validar um número do tipo int com Valor minimo e valor maximo.
//Parâmetros: referência ao vetor mensagem, número minímo, número máximo.
//Retorno: número tipo int validado.
int leValidaInt(char msg[], int min, int max){
	int num;

	do{
		num = leInt(msg);
		if (num < min || num > max)
			printf("Favor digitar um valor entre %d e %d.\n", min, max);
	}while(num < min || num > max);

	return num;
}

//Objetivo: Ler um número do tipo float
//Parâmetros: referência ao vetor mensagem.
//Retorno: número tipo float lido.
float leFloat(char msg[]){
	float num;
	int ret;

	do{
		printf("%s", msg);
		fflush(stdin);
		ret = scanf("%f",&num);
		if (ret == 0 || num < 0)
			printf("Favor digitar valores maiores que zero!.\n");
	}while (ret == 0 || num < 0);

	return num;
}

//Objetivo: Ler e Validar String.
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void leString(char str[],int tamMax)
{
	printf("Informe Placa do Carro: ");
	fflush(stdin);
	fgets(str,tamMax,stdin);
	fflush(stdin);
	if(str[strlen(str)-1] == '\n')
	  str[strlen(str)-1] = '\0';
}

//Objetivo: Transforma String em minuscula..
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strlower(char str[])
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = tolower(str[cont]);
}

//Objetivo: Transforma String em Maiuscula.
//Parâmetros: Referencia ao Vetor String.
//Retorno: Void
void strupper(char str[])
{
	int cont;
	for(cont=0;cont<strlen(str);cont++)
	str[cont] = toupper(str[cont]);
}

//Objetivo: Verificar se existe uma placa repetida no vetor.
//Parametro: Referencia a matriz e a posicao que deve ser verificado 
//Retorno: 0 para se nao existe e 1 para se existe placa repetido
int verificaPlacaRepetida(char placas[][TAM_PLACA], int posicao)
{
	int cont,flag=0;
	for(cont=0;cont<posicao;cont++)
	{
		if(strcmp(placas[posicao],placas[cont]) == 0)
		{
			printf("Valor Inserido ja existe no sistema ...\n");
			flag=1;
			break;
		}
	}
	return flag;
}

//Objetivo: Cadastrar Carro.
//Entrada: Referencia ao Vetor placas, referencia ao vetor valores, quantidade de carros.
//Saida: nada
void cadastrarCarro(char placas[][TAM_PLACA],float valores[], int contCarros)
{
		do{
			leString(placas[contCarros],TAM_PLACA);
			verificaPlacaRepetida(placas,contCarros);
			if(strlen(placas[contCarros]) == 0)
			printf("Placa nao pode ser vazia!.\n"); 
		}while(verificaPlacaRepetida(placas,contCarros) == 1 || strlen(placas[contCarros]) == 0);
		strupper(placas[contCarros]); //Transformo as placas em maiusculo para futuras comparacoes.
		valores[contCarros] = leFloat("Informe o valor do carro: ");
}

//Objetivo: Listar os carros filtardos pelas placas
//Parametros: referencia ao vetor placas, referencia ao vetor valores, palavra chave
//Retorno: nada
void apresentaCarros(char placas[][TAM_PLACA],float valores[],char palavraChave[], int qtdCarros)
{
	int cont;
	printf("CARROS CADASTRADOS:\n");
	for(cont=0;cont<qtdCarros;cont++)
	{
		if(strncmp(placas[cont],palavraChave,3) == 0)
		printf("PLACA: %s , VALOR = %.2f\n",placas[cont],valores[cont]);
	}
}
