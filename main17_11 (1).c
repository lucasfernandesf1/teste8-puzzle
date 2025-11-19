#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

static inline int rand_int(int a, int b)
{
 return a + rand() % (b - a + 1);
}

typedef struct lista
{
    int info[3][3];
    struct lista *prox;
}No;

typedef struct fila
{
    No *ini;
    No *fim;
} Fila;

void inicializa_fila(Fila *f)
{
    f->ini = NULL;
    f->fim = NULL;
}

void add_fila(Fila *f, int info[3][3])
{
    No *novo = malloc(sizeof(No));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            novo->info[i][j] = info[i][j];

    novo->prox = NULL;

    if (f->fim == NULL)
    {
        f->ini = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->prox = novo;           // liga no último
        f->fim = novo;                 // atualiza fim
    }
}
void remove_fila(Fila *f, int out[3][3])
{
    if (f->ini == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }

    No *tmp = f->ini;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {                                       // copia a matriz do nó
            out[i][j] = tmp->info[i][j];
        }
    }
    f->ini = f->ini->prox;

    if (f->ini == NULL)
    {
        f->fim = NULL;
    }

    free(tmp);
}

void cria_vetor_movimento (int m[3][3], int movitos[4], int *linha, int *col)
{
        if (*linha == 0 )
        {
            movitos[2] = 1;
        }
        else
        {
            movitos[0] = 1;
        }

        if (*linha == 1)
        {
            movitos[2] = 1;
        }
//---------------------------------------------------------------------
        if(*col == 0)
        {
            movitos[1] = 1;
        }
        else
        {
            movitos[3] = 1;
        }
        if(*col == 1)
        {
            movitos[1] = 1;
        }
        //falta chamar no main
}

void printEstado(int estado[3][3])
{
    printf("\t");
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if (estado[i][j] == 9)
            {
                printf("|   |");
            }
            else{
                printf("| %d |",estado[i][j]);
            }
        }
        printf("\n\t");
    }
    return;
}

void Ganhou ()
{
    printf("\n\t****************************************************");
    printf("\n\t**                                                **");
    printf("\n\t**                Você Ganhou!!                   **");
    printf("\n\t**                                                **");
    printf("\n\t****************************************************\n\n");
}

void deepcopy(int estado[3][3], int copiaEstado[3][3]){
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            copiaEstado[i][j] = estado[i][j];
        }
    }
    return;
}

void cria_random(int novaMatriz[3][3], int *linhaVazio, int *colVazio, int *guarda_rand)
{
    int z = 0;
    int aleatorio=0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int repetido;
            do {
                aleatorio = rand_int(1, 9);
                repetido = 0;

                for (int h = 0; h < z; h++)
                {
                    if (aleatorio == guarda_rand[h])
                    {
                        repetido = 1;
                        break;
                    }
                }guarda_rand[z] = aleatorio;
            } while (repetido);
            novaMatriz[i][j] = aleatorio;
            if (novaMatriz[i][j] == 9)
            {
                *linhaVazio = i;
                *colVazio = j;
            }
            z++;
        }
    }
}

int checa_matriz_possivel (int guarda_matriz[9])
{
    int cont_inversao = 0;
    for (int i=0; i<9; i++)
    {
        if (guarda_matriz[i] == 9)
        {continue;}

        for(int j=i; j<9; j++)
        {
            if (guarda_matriz[j] == 9)
            {continue;}
            if(guarda_matriz[i] > guarda_matriz[j])
            {
                cont_inversao++;
            }
        }
    }
    if(cont_inversao % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void jogador_mov (int *mover)
{
    char mov;
    printf("\n\tEscolha qual peça você quer mover: \n\tw - peça de cima\n\ts - peça de baixo\n\td - peça da direita\n\ta - peça da esquerda\n");
    scanf(" %c", &mov);
    printf("\n");
    switch (mov)
    {
    case 'w':
        // cima
        *mover = 1;
        break;
    case 'd':
        // direita
        *mover = 2;
        break;
    case 's':
        //baixo
        *mover = 3;
        break;
    case 'a':
        //esq
        *mover = 4;
        break;
    }
}

void movimentos (int m[3][3],  int mover, int *linha, int *col)
{
    int auxLinha, auxCol;
    auxLinha = *linha;
    auxCol = *col;

    switch (mover)
    {
    case 1:
        // printf("cima");
        if(*linha > 0)
        {
            *linha -= 1;
            m[auxLinha][*col] = m[*linha][*col];
            break;
        }
        break;

    case 2:
        //printf("direita");
        if(*col < 2)
        {
            *col += 1;
            m[*linha][auxCol] = m[*linha][*col];
            break;
        }
        break;

    case 3:
        //printf("baixo");
        if(*linha < 2)
        {
            *linha +=1;
            m[auxLinha][*col] = m[*linha][*col];
            break;
        }
        break;

    case 4:
        //printf("esq");
        if(*col > 0)
        {
            *col -= 1;
            m[*linha][auxCol] = m[*linha][*col];
            break;
        }
        break;
    }
     m[*linha][*col] = 9;
}

void interpreta_vetorMovimento (int V[4])
{
    int num = 1;
    for (int i=0; i<4; i++)
    {
        if(V[i]== 1)
        {
           V[i] = num;
        }
      num++;
    }
}
int verifica_matriz(int m[3][3])
{
    int verificacao=1;
    int true_false;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if(m[i][j] != verificacao)
            {
                return 0;
            }
            verificacao++;
        }
    }
    return 1;
}

int main()
{
    printf("\n\t****************************************************");
    printf("\n\t**                                                **");
    printf("\n\t**                 8-PUZZLE                       **");
    printf("\n\t**                                                **");
    printf("\n\t****************************************************\n\n\n");

    setlocale(LC_ALL, "");
    srand(time(NULL));
    int linhavazia, colvazia, movimento;
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int guarda_rand[9];
    int V_ou_F;
    int heuristica=0;
    int moriginal2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int V[4];

    printf("\n\tO tabuleiro gerado para você resolver é este:\n\n");
    do
    {
        cria_random(/*m,*/ m, &linhavazia, &colvazia, guarda_rand);
        V_ou_F = checa_matriz_possivel(guarda_rand);
    }while(V_ou_F == 0);
    printEstado(m);
    //escolher se quer jogar, BFS ou IDFS.
    int escolhe;
    printf("\n\tEscolha se você quer resolver ou usar uma solução automática:\n\n\t1 para JOGAR\n\t2 para SOLUÇÃO AUTOMÁTICA\n\n\tDigite: ");
    scanf("%d", &escolhe);

    if (escolhe == 1)//caso tenha escolhido jogar vai rodar essa parte:
    {
        printEstado(m);
        Sleep(1000);
        system("cls");

        while (verifica_matriz(m) != 1)
        {
            printEstado(m);
            jogador_mov(&movimento);
            movimentos(m, movimento, &linhavazia, &colvazia);
            system("cls");
        }
        Ganhou();
    }
    else if (escolhe == 2)
    {
        int escolheDnv;
        printf(" \n\tEscolha qual tipo de solução será usada:\n\n\t1 para BFS\n\t2 para IDDFS\n\n\tDigite: ");
        scanf("%d", &escolheDnv);

        if(escolheDnv == 1)
        {
            Fila *f;
            cria_vetor_movimento(m, V, &linhavazia, &colvazia);
            interpreta_vetorMovimento(V);
            add_fila(f, m);
        }
    }
    else
    {
        printf("\n\n\tvocê digitou uma opção inválida\n");
    }

    return 0;
}
