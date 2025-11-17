#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

static inline int rand_int(int a, int b)
{
 return a + rand() % (b - a + 1);
}

typedef struct lista
{
    int info;
    int prox;
}no;

void calcula_heuristica(int v[9])
{
    int cont=0;
    for (int i=0; i<9; i++)
    {
        if (v[i] == 9)
        {continue;}

        for(int j=i; j<9; j++)
        {
            if (v[j] == 9)
            {continue;}
            if(v[i] > v[j])
            {
                cont++;
            }
        }
    }
    printf("%d heuristica\n\n", cont);
}

void printEstado(int estado[3][3])
{
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
        printf("\n");
    }
    return;
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
    printf("escolha qual peça vc quer mover: \nw - peça de cima\ns - peça de baixo\nd - peça da direita\na - peça da esquerda\n");
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
void atualiza_vetor (int m[3][3], int v[9])
{
    int k=0;
     for (int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
         {
             v[k] = m[i][j];
             k++;
         }
     }
     for (int i=0; i<9; i++)
     {
         printf("%d\t", v[i]);
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
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int linhavazia, colvazia, movimento;
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int guarda_rand[9];
    int V_ou_F;
    int heuristica=0;
    int moriginal2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    printf("\nCriando uma matriz com posições aleatórias:\n");
    do
    {
        cria_random(/*m,*/ m, &linhavazia, &colvazia, &guarda_rand);
        V_ou_F = checa_matriz_possivel(guarda_rand);
    }while(V_ou_F == 0);
    //escolher se quer jogar, A* ou BFS.
    //selecionar qual ele quer para rodar com if e else
    //---------------------------------------------------------------------------------
    //caso tenha escolhido jogar vai rodar essa parte:

    //printEstado(m);
    //sleep(2);
    //system("cls");

    while (verifica_matriz(m) != 1)
    {
        printEstado(m);
        atualiza_vetor(m, &guarda_rand);
        calcula_heuristica(guarda_rand);  //atualizar guarda-rand;
        jogador_mov(&movimento);
        movimentos(m, movimento, &linhavazia, &colvazia);
        //deepcopy(moriginal2, m); verificação funcionando;
        //system("cls");
    }
    printf("Você ganhou!");
    //------------------------------------------------------------------------------------
                                                          //queria dar a opção de limpar a tela antiga ao jogador;
    return 0;
}
