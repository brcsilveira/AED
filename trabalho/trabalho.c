#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void menu(int *escolha);
void PUSH(int *pBuffer);
void SORT(void *pBuffer, void *pessoa);
void LIST(void *pBuffer);
void PRINT(void *pessoa);
void FIND(void *pBuffer);
void POP(void *pBuffer);
void CLEAR(void *pBuffer);
int EMPTY(void *pBuffer);

//Estrutura de pBuffer:
#define ESCOLHA 0 
#define pPrimeiro (sizeof(int))
#define pUltimo (sizeof(int) + sizeof(void *))
#define BUSCAR_PESSOA (sizeof(int) + sizeof(void *) * 2)

// Estrutura de pessoa:
#define ANTERIOR 0
#define NOME (sizeof(void *))
#define IDADE (sizeof(void *) + sizeof(char) * 10)
#define TELEFONE (sizeof(void *) + sizeof(char) * 10 + sizeof(int))
#define PROXIMO (sizeof(void *) + sizeof(char) * 10 + sizeof(int) * 2)

int main()
{
    void *pBuffer = NULL;

    pBuffer = (void *)malloc(sizeof(int) + sizeof(void *) * 2 + sizeof(char) * 10);

    if (pBuffer == NULL)
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    } 

    int *escolha = &*(int *)(pBuffer + ESCOLHA); 

    *(void **)(pBuffer + pPrimeiro) = NULL;
    *(void **)(pBuffer + pUltimo) = NULL;

    while (1)
    {
        menu(escolha);
        switch (*escolha)
        {
        case 1:
            PUSH(pBuffer);
            break;
        case 2:
            POP(pBuffer);
            break;
        case 3:
            FIND(pBuffer);
            break;
        case 4:
            LIST(pBuffer);
            break;
        case 5:
            CLEAR(pBuffer);
            exit(0);
            break;
        default:
        printf("Opção inválida. Digite uma opção válida(1 ao 5).");
        break;
        }
    }
    return 0;
}

void menu(int *escolha)
{
    printf("\nMenu:\n");
    printf("1) Adicionar Contato.\n");
    printf("2) Remover Contato.\n");
    printf("3) Buscar.\n");
    printf("4) Listar.\n");
    printf("5) Sair.\n");
    printf("\nDigite a sua escolha: ");
    scanf("%d", &*escolha);
}

void PUSH(int *pBuffer)
{
    void *pessoa = NULL;
    
    pessoa = (void *)malloc(sizeof(void *) * 2 + sizeof(char) * 10 + sizeof(int) * 2);

    if (pessoa == NULL)
    {
        printf("ERRO: Sem memória.\n");
        exit(1);
    }

    printf("Informe o nome que deseja inserir na agenda: ");
    scanf("%s", (char *)(pessoa + NOME));

    while (strlen((char *)(pessoa + NOME)) > 10)
    {
        printf("ESCOLHA INVÁLIDA!\n Digite um nome com no máximo 10 letras: ");
        scanf("%s", (char *)(pessoa + NOME));
    }
    
    printf("Informe a idade: ");
    scanf("%d", (int *)(pessoa + IDADE));

    printf("Informe o telefone: ");
    scanf("%d", (int *)(pessoa + TELEFONE));

    SORT(pBuffer, pessoa);
}

void SORT(void *pBuffer, void *pessoa)
{
    *(void **)(pessoa + ANTERIOR) = NULL; 
    *(void **)(pessoa + PROXIMO) = NULL;

    void *auxiliarParaPessoa = *(void **)(pBuffer + pUltimo);

    if (auxiliarParaPessoa == NULL)
    {
        *(void **)(pBuffer + pPrimeiro) = pessoa;
        *(void **)(pBuffer + pUltimo) = pessoa;
        printf("\nCadastro efetuado com sucesso.\n");
        return;
    }

    while (auxiliarParaPessoa != NULL)
    {
        if (strcmp((char *)(pessoa + NOME), (char *)(auxiliarParaPessoa + NOME)) >= 0)
        {
            if (*(void**)(auxiliarParaPessoa + PROXIMO) == NULL)
            {   
                // Inserção no fim
                *(void **)(pessoa + ANTERIOR) = auxiliarParaPessoa;
                
                void *pessoaTemporaria = *(void **)(pBuffer + pUltimo);

                *(void **)(pBuffer + pUltimo) = pessoa;
                *(void **)(pessoaTemporaria + PROXIMO) = pessoa;

                printf("\nCadastro efetuado com sucesso.\n");

                return;
            }
            else
            {   
                // Inserção no meio 
                *(void **)(pessoa + ANTERIOR) = auxiliarParaPessoa;
                *(void **)(pessoa + PROXIMO) = *(void **)(auxiliarParaPessoa + PROXIMO);
                
                void *pessoaTemporia = *(void **)(auxiliarParaPessoa + PROXIMO);
                
                *(void **)(pessoaTemporia + ANTERIOR) = pessoa;
                *(void **)(auxiliarParaPessoa + PROXIMO) = pessoa;

                printf("\nCadastro efetuado com sucesso.\n");

                return;
            }
            
        }

        auxiliarParaPessoa = *(void **)(auxiliarParaPessoa + ANTERIOR);
    }

    // Inserção no inicio
    *(void **)(pessoa + PROXIMO) = *(void **)(pBuffer + pPrimeiro);
    auxiliarParaPessoa = *(void **)(pBuffer + pPrimeiro);
    *(void **)(auxiliarParaPessoa + ANTERIOR) = pessoa;
    *(void **)(pBuffer + pPrimeiro) = pessoa;
    
    printf("\nCadastro efetuado com sucesso.\n");

    return;
}

void LIST(void *pBuffer)
{
    void *pessoa = *(void **)(pBuffer + pPrimeiro);

    if (EMPTY(pBuffer))
    {
        printf("\nLista vazia.\n");
        return;
    }
    
    printf("\n\nLISTA:\n\n");
    do
    {
        PRINT(pessoa);
        pessoa = *(void **)(pessoa + PROXIMO);
        printf("\n");
    } while (pessoa != NULL);
}

void PRINT(void *pessoa)
{
    printf("NOME: %s\n", (char *)(pessoa + NOME));
    printf("IDADE:  %d\n", *(int *)(pessoa + IDADE));
    printf("TELEFONE: %d\n", *(int *)(pessoa + TELEFONE));
}

void FIND(void *pBuffer)
{
    char *pessoaBuscar = &*(char *)(pBuffer + BUSCAR_PESSOA);
    void *pessoa = *(void **)(pBuffer + pPrimeiro);

    if (EMPTY(pBuffer))
    {
        printf("\nLista vazia.\n");
        return;
    }

    printf("Informe o nome que voce deseja buscar na agenda: ");
    scanf("%s", pessoaBuscar);

    do
    {
        if (strcmp(pessoaBuscar, (char *)(pessoa + NOME)) == 0)
        {
            printf("\n");
            PRINT(pessoa);
            return;
        } 

        pessoa = *(void **)(pessoa + PROXIMO);

    } while (pessoa != NULL);
    
    printf("\nCadastro não encontrado.\n");
    return;
}

void POP(void *pBuffer)
{
    char *pessoaRemover = &*(char *)(pBuffer + BUSCAR_PESSOA);
    void *pessoa = *(void **)(pBuffer + pPrimeiro);
    void *pessoaTemporaria;
 
    if (EMPTY(pBuffer))
    {
        printf("\nLista vazia.\n");
        return;
    }

    printf("Informe a pessoa que você deseja remover da agenda: ");
    scanf("%s", pessoaRemover);

    do
     {
        if (strcmp(pessoaRemover, (char *)(pessoa + NOME)) == 0)
        {
            break;
        } 

        pessoa = *(void **)(pessoa + PROXIMO);

     } while (pessoa != NULL);

    if (!pessoa)
    {
        printf("\nCadastro não encontrado.\n");
        return;
    }        
   if(pessoa == *(void **)(pBuffer + pPrimeiro))
   {    
       // Remoção no inicio
       *(void **)(pBuffer + pPrimeiro) = *(void **)(pessoa + PROXIMO);
       if (pessoa == *(void **)(pBuffer + pUltimo))
       {
           *(void **)(pBuffer + pUltimo) = NULL;
       }
       free(pessoa);
   } 
    else if(pessoa == *(void **)(pBuffer + pUltimo))
    {   
        // Remoção no fim
        pessoaTemporaria = *(void **)(pessoa + ANTERIOR);
        *(void **)(pBuffer + pUltimo) = *(void **)(pessoa + ANTERIOR);
       *(void **)(pessoaTemporaria + PROXIMO) = NULL;
        free(pessoa);
    }
    else
    {   
        // Remoção no meio
        pessoaTemporaria = *(void **)(pessoa + ANTERIOR);
        *(void **)(pessoaTemporaria + PROXIMO) = *(void **)(pessoa + PROXIMO);
        pessoaTemporaria = *(void **)(pessoa + PROXIMO);
        *(void **)(pessoaTemporaria + ANTERIOR) = *(void **)(pessoa + ANTERIOR);
        free(pessoa);
    }

 printf("\nCadastro removido com sucesso.\n");

}

void CLEAR(void *pBuffer)
{
    void *pessoa = *(void **)(pBuffer + pPrimeiro);
    void *auxiliarParaPessoa;

    while (pessoa != NULL)
    {
        auxiliarParaPessoa = *(void **)(pessoa + PROXIMO);
        free(pessoa);
        pessoa = auxiliarParaPessoa;
    }

    free(pBuffer);
}

int EMPTY(void *pBuffer)
{
    if (*(void **)(pBuffer + pPrimeiro) == NULL && *(void **)(pBuffer + pUltimo) == NULL)
        return 1;
    return 0;
}