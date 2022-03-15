#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_DO_NOME 20

int menu(void);
void nomesListados(char *nomesDaLista);
char *listarNomes(char *nomesDaLista);
char *removerNomes(char *nomesDaLista);

int main() 
{

    int escolha;
    char *nomesDaLista = NULL;

    nomesDaLista = (char *)malloc(sizeof(char) + 1);
    nomesDaLista[0] = '\0';

    if (nomesDaLista == NULL) 
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    }

    while (1)
    {
        escolha = menu();
        switch (escolha)
        {
        case 1: 
            nomesDaLista = listarNomes(nomesDaLista);
            break;
        
        case 2: 
           nomesDaLista = removerNomes(nomesDaLista);
           break;
        case 3: 
            nomesListados(nomesDaLista);
            break;
        case 4: 
            free(nomesDaLista); //Libera a memória alocada.
            exit(0);
            break;
        }    
    }

    return 0;
}

int menu(void)
{
    int escolha = 0;
    
    do
    {
        printf("Menu:\n");
        printf("1) Adicionar nome.\n");
        printf("2) Remover nome.\n");
        printf("3) Listar.\n");
        printf("4) Sair.\n");
        printf("\nDigite a sua escolha:\n");
        scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 4);
    
    getchar(); //Só para limpar o buffer do teclado.
    return escolha;
}

void nomesListados(char *nomesDaLista)
{
    if (strlen(nomesDaLista) == 0)
    {
        printf("\nLista vazia.\n\n");
    }
    else
    {
        printf("\n\nNomes da lista: %s\n\n", nomesDaLista);
    }
}

char *listarNomes(char *nomesDaLista)
{
   char nomeNovo[TAMANHO_DO_NOME];

   printf("Digite o nome: ");
   scanf("%s", nomeNovo);

   printf("\n");
   
   if (strlen(nomesDaLista) == 0)
   {
       nomesDaLista = (char *)realloc(nomesDaLista, (strlen(nomeNovo) + 1) * sizeof(char));
       strcat(nomesDaLista, nomeNovo);
   }
   else
   {
       nomesDaLista = (char *)realloc(nomesDaLista, (strlen(nomesDaLista) + 2 + strlen(nomeNovo)) * sizeof(char));
       strcat(nomesDaLista, "-");
       strcat(nomesDaLista, nomeNovo);
   }
   
    strcat(nomesDaLista, "\0");

    return nomesDaLista;
}

char *removerNomes(char *nomesDaLista)
{
    char nomeRemove[TAMANHO_DO_NOME];
    int primeiraLetraRemove;

    printf("Digite o nome: ");
    scanf("%s", nomeRemove);

    char *verificaNome = strstr(nomesDaLista, nomeRemove);
    
    if (verificaNome == NULL)
    {
        printf("\nEste nome não está na lista.\n\n");
        return nomesDaLista;
    }

    primeiraLetraRemove = strlen(nomesDaLista) - strlen(verificaNome);

    if (primeiraLetraRemove != 0 &&  '-' == nomesDaLista[primeiraLetraRemove - 1])
    {
        primeiraLetraRemove--;
        verificaNome--;
    }

    for (int x = 0; x <= strlen(nomeRemove); x++)
    {
        for (int y = 0; y < strlen(verificaNome); y++)
        {
            nomesDaLista[primeiraLetraRemove + y] = nomesDaLista[primeiraLetraRemove + y + 1];
        }
    }

    nomesDaLista = (char *)realloc(nomesDaLista, (strlen(nomesDaLista) + 1) * sizeof(char));
    strcat(nomesDaLista, "\0");

    return nomesDaLista;
}