#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void menu(int *pBuffer);
void nomesListados(void *pBuffer);
void listarNomes(void *pBuffer);
void removerNomes(void *pBuffer);
void buscarNomes(void *pBuffer);

typedef struct 
{
    char nome[10];
    int idade; 
    int telefone;
} Pessoa; 

Pessoa pessoas[10];

int main()
{
    void *pBuffer = NULL;
    
    pBuffer = malloc(sizeof(int) * 3 + sizeof(char) * 11); 
    if (pBuffer == NULL)
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    }
    
    int *escolha = &*(int *)(pBuffer); 
    *(int *)(pBuffer + sizeof(int)) = 0; 
    while (1)
    {
        menu(escolha);
        switch (*escolha)
        {
        case 1:
            listarNomes(pBuffer);
            break;
        case 2:
            removerNomes(pBuffer);
            break;
        case 3:
            nomesListados(pBuffer);
            break;
        case 4:
            buscarNomes(pBuffer);
            break;
        case 5:
            free(pBuffer);
            exit(0);
            break;
        default:
        printf("Opção inválida. Digite uma opção válida(1 ao 5).");
        }
    }
    return 0;
}

void menu(int *escolha)
{
    printf("\nMenu:\n");
    printf("1) Adicionar Contato.\n");
    printf("2) Remover Contato.\n");
    printf("3) Listar.\n");
    printf("4) Buscar.\n");
    printf("5) Sair.\n");
    printf("\nDigite a sua escolha: ");
    scanf("%d", &*escolha);
}

void nomesListados(void *pBuffer)
{
    int *contadorDePessoas = &*(int *)(pBuffer + sizeof(int));
    int *contador = &*(int *)(pBuffer + (sizeof(int) * 2));

    if (*contadorDePessoas == 0)
    {
        printf("\nAgenda vazia.\n\n");
    }
    else
    {
        for (*contador = 0; *contador < *contadorDePessoas; *contador += 1)
        {
            printf("\n%dº USUÁRIO:\n", *contador + 1);
            printf("Nome: %s\n", pessoas[*contador].nome);
            printf("Idade: %d\n", pessoas[*contador].idade);
            printf("Telefone/Celular: %d\n\n", pessoas[*contador].telefone);
        }
    }
}

void listarNomes(void *pBuffer)
{
    int *contadorDePessoas = &*(int *)(pBuffer + sizeof(int));

    if (*contadorDePessoas >= 10)
    {
        printf("\nAGENDA LOTADA: Não é possível inserir outra pessoa.\n");
    }
    else
    {
        printf("\nDigite o nome: ");
        scanf("%s", pessoas[*contadorDePessoas].nome);
        printf("Informe a idade: ");
        scanf("%d", &pessoas[*contadorDePessoas].idade);
        printf("Informe o telefone/celular: ");
        scanf("%d", &pessoas[*contadorDePessoas].telefone);

        *contadorDePessoas += 1;
        printf("\nPessoa cadastrada na agenda com sucesso.\n");
    }
}

void removerNomes(void *pBuffer)
{
    int *contadorDePessoas = &*(int *)(pBuffer + sizeof(int));
    int *contador = &*(int *)(pBuffer + (sizeof(int) * 2));
    char *nome = &*(char *)(pBuffer + (sizeof(int) * 3));
    
    if (*contadorDePessoas == 0)
    {
        printf("Não existem pessoas cadastradas na agenda.\n");
        return;
    }

    printf("Informe o nome que você quer remover: ");
    scanf("%s", nome);

    for (*contador = 0; *contador < *contadorDePessoas; *contador += 1)
    {
        if (strcmp(nome, pessoas[*contador].nome) == 0)
        {
            break;
        }
    }

    if (*contador == *contadorDePessoas)
    {
        printf("Pessoa não encontrada.\n");
        return;
    }

    for (*contador; *contador < *contadorDePessoas; *contador += 1)
    {
        strcpy(pessoas[*contador].nome, pessoas[*contador + 1].nome);
        pessoas[*contador].idade = pessoas[*contador + 1].idade;
        pessoas[*contador].telefone = pessoas[*contador + 1].telefone;
    }

    *contadorDePessoas -= 1;
    printf("\nPessoa removida da agenda com sucesso.\n");

    return;
}

void buscarNomes(void *pBuffer)
{
    int *contadorDePessoas = &*(int *)(pBuffer + sizeof(int));
    int *contador = &*(int *)(pBuffer + (sizeof(int) * 2));
    char *nome = &*(char *)(pBuffer + (sizeof(int) * 3));
    
    if (*contadorDePessoas == 0)
    {
        printf("Não existem pessoas cadastradas na agenda.\n");
        return;
    }

    printf("Informe o nome que você está procurando: ");
    scanf("%s", nome);

    for (*contador = 0; *contador < *contadorDePessoas; *contador += 1)
    {
        
        if (strcmp(nome, pessoas[*contador].nome) == 0)
        {
            printf("\n%dº USUÁRIO:\n", *contador + 1);
            printf("Nome: %s\n", pessoas[*contador].nome);
            printf("Idade: %d\n", pessoas[*contador].idade);
            printf("Telefone/Celular: %d\n\n", pessoas[*contador].telefone);
            
            return;
        }
    }
    printf("\nPessoa não encontrada.\n");
    return;
}