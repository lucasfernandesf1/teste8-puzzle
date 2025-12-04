#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

#define TAM 500000

static inline int rand_int(int a, int b)
{
 return a + rand() % (b - a + 1);
}

typedef struct v
{
    int m[3][3];
} estado;

estado fila [TAM];
int inicio = 0;
int fim = 0;

void enfileira(estado e)
{
    fila[fim] = e;
    fim = (fim + 1) % TAM;
}

estado desenfileira()
{
    estado e = fila[inicio];
    inicio = (inicio + 1) % TAM;
    return e;
}

void geraVetorMov (int m[3][3], int movitos[4], int *linha, int *col)
{
    movitos[0] = movitos[1] = movitos [2] = movitos[3] = 0;

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
}

void printfila(estado e)
{
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) printf("%d ", e.m[i][j]);
        printf("\n");
    }
    printf("\n");
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
        case 'w': *mover = 1; break;
        case 'd': *mover = 2; break;
        case 's': *mover = 3; break;
        case 'a': *mover = 4; break;
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

estado criaFilho(int movimento, estado pai, int linha, int coluna)
{
    estado novo = pai;
    movimentos(novo.m, movimento, &linha, &coluna);
    return novo;
}

void MoveBFS (int V[4], estado atual, int linha, int col)
{
    for (int i = 0; i < 4; i++)
    {
        if (V[i] == 0) continue;
        estado novo = criaFilho(V[i], atual, linha, col);
        enfileira(novo);
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
    printf("\n\t**                   8-PUZZLE                     **");
    printf("\n\t**                                                **");
    printf("\n\t****************************************************\n\n\n");


    setlocale(LC_ALL, "");
    srand(time(NULL));
    int linhavazia, colvazia, movimento;
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int guarda_rand[9];
    int V_ou_F, sair;
    int heuristica=0;
    int moriginal2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int V[4];

    while(1)
    {
    printf("\n\tDigite 0 para sair e qualquer coisa para continuar:\n\t");
    scanf("%d", &sair);

    if (sair==0){break;}


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

    estado atual;
    deepcopy(m, atual.m);

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
            while(verifica_matriz(atual.m) != 1)
            {
                geraVetorMov(atual.m, V, &linhavazia, &colvazia);
                interpreta_vetorMovimento(V);                           //FALTA PRINTAR
                MoveBFS(V, atual, linhavazia, colvazia);
            }
        }
    }
    else
    {
        printf("\n\n\tvocê digitou uma opção inválida\n");
    }
    }
    return 0;
}
