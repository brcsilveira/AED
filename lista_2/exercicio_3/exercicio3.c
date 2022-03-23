#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
    char nome[10];
    int idade; 
    int telefone;
} Pessoa; 

int menu(void);
void nomesListados(void *pBuffer);
void *listarNomes(void *pBuffer);
void *removerNomes(void *pBuffer);
int buscarNomes(void *pBuffer);

int main()
{
    int escolha, procura;
    void *pBuffer;

    pBuffer = malloc(sizeof(int));

    if(pBuffer == NULL)
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    }

    *(int *)pBuffer = 0;

    while (1)
    {
        escolha = menu();
        switch (escolha)
        {
        case 1:
            pBuffer = listarNomes(pBuffer);
            break;
        case 2:
            pBuffer = removerNomes(pBuffer);
            break;
        case 3:
            nomesListados(pBuffer);
            break;
        case 4:
            procura = buscarNomes(pBuffer);
            break;
        case 5:
            free(pBuffer);
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
        printf("1) Adicionar Contato.\n");
        printf("2) Remover Contato.\n");
        printf("3) Listar.\n");
        printf("4) Buscar.\n");
        printf("5) Sair.\n");
        printf("\nDigite a sua escolha: ");
        scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 5);
    
    getchar(); //Só para limpar o buffer do teclado.
    return escolha;
}

void nomesListados(void *pBuffer)
{
    int pessoasTotal;
    pessoasTotal = *(int *)pBuffer;

    if (pessoasTotal == 0)
    {
        printf("\nAgenda vazia.\n\n");
    }
    else
    {
        Pessoa person;
        
        for (int i = 0; i < pessoasTotal; i++)
        {
            person = *(Pessoa *)(pBuffer + sizeof(int) + (sizeof(Pessoa) * i));
            printf("\n%dº USUÁRIO:\n", i + 1);
            printf("Nome: %s\n", person.nome);
            printf("Idade: %d\n", person.idade);
            printf("Telefone/Celular: %d\n\n", person.telefone);
        }
    }    
}

void *listarNomes(void *pBuffer)
{
    Pessoa novaPessoa;
    int tamanho;

    printf("\nDigite o nome: ");
    scanf("%s", novaPessoa.nome);
    printf("Informe a idade: ");
    scanf("%d", &novaPessoa.idade);
    printf("Informe o telefone/celular: ");
    scanf("%d", &novaPessoa.telefone);

    tamanho = *(int *)pBuffer;
    tamanho++;
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Pessoa) * tamanho));

    if (pBuffer == NULL)
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    }

    if (tamanho == 1)
    {
        *(Pessoa *)(pBuffer + sizeof(int)) = novaPessoa;
    }
    else
    {
        *(Pessoa *)(pBuffer + sizeof(int) + (tamanho - 1) * sizeof(Pessoa)) = novaPessoa;
    }

    *(int *)pBuffer = tamanho;

    printf("\nPessoa cadastrada na agenda.\n\n");  
    return pBuffer;  
}

void *removerNomes(void *pBuffer)
{
    int tamanho = *(int *)pBuffer;
    int removePessoa = buscarNomes(pBuffer);

    if (removePessoa == -1)
    {
        return pBuffer;
    }
    else
    {
        Pessoa person = *(Pessoa *)(pBuffer + sizeof(int) + sizeof(Pessoa) * removePessoa);

        if ((removePessoa + 1) < tamanho)
        {
            Pessoa proximaPessoa;
            for (int i = removePessoa; i < (tamanho - 1); i++)
            {
                proximaPessoa = *(Pessoa *)(pBuffer + sizeof(int) + sizeof(Pessoa) * (i + 1));
                *(Pessoa *)(pBuffer + sizeof(int) + sizeof(Pessoa) * i) = proximaPessoa;
            }
        }

        tamanho--;
        *(int *)pBuffer = tamanho;

        pBuffer = realloc(pBuffer, sizeof(int) + sizeof(Pessoa) * tamanho);

        if (pBuffer == NULL)
        {
            printf("ERRO: Sem memória.\n");
            exit(1);
        }
        
        printf("Pessoa removida da agenda.\n\n");
        return pBuffer;    
    }
}

int buscarNomes(void *pBuffer)
{
    int pessoasTotal = *(int *)pBuffer;
    char nome[10];

    if (pessoasTotal == 0)
    {
        printf("Não existem pessoas cadastradas na agenda.\n");
        return -1;
    }

    printf("Informe o nome que você está procurando: ");
    scanf("%s", nome);

    Pessoa person;

    for (int i = 0; i < pessoasTotal; i++)
    {
        person = *(Pessoa *)(pBuffer + sizeof(int) + i * sizeof(Pessoa));
        if (strcmp(person.nome, nome) == 0)
        {
            Pessoa person = *(Pessoa *)(pBuffer + sizeof(int) + sizeof(Pessoa) * i);
            printf("\n%dº USUÁRIO:\n", i + 1);
            printf("Nome: %s\n", person.nome);
            printf("Idade: %d\n", person.idade);
            printf("Telefone/Celular: %d\n\n", person.telefone);
            
            return i;
        }
        
    }    
    printf("Pessoa não encontrada.\n");
    return -1;     
}