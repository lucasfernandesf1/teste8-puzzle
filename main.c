#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

#define TAM 500000

typedef struct matriz
{
    int m[3][3];
}matrizEstado;

//==================================================
matrizEstado fila[TAM];
int ini = 0, fim = 0;

matrizEstado visitados[TAM];
int totalVisitados = 0;                 // globais

int movs[4][2] = {
    {-1, 0}, // cima
    { 0, 1},  // direita
    { 1, 0}, // baixo
    { 0,-1}, // esquerda
};
//==================================================
static inline int rand_int(int a, int b)
{
 return a + rand() % (b - a + 1);
}

void enfileira(matrizEstado matriz)
{
    fila[fim++] = matriz;
}

matrizEstado desenfileira()
{
    return fila[ini++];
}

int estadosIguais(matrizEstado matrizA, matrizEstado matrizB)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matrizA.m[i][j] != matrizB.m[i][j])
                return 0;
    return 1;
}

int jaVisitado(matrizEstado e)   //verifica se ja foi visitado ou nao
{
    for (int i = 0; i < totalVisitados; i++)
    {
        if (estadosIguais(e, visitados[i]))
        {
            return 1;
        }
    }
    return 0;
}

void marcaVisitado(matrizEstado e)// marca no vetor de struct mais um q foi visitado.
{
    visitados[totalVisitados++] = e;
}

int ehObjetivo(matrizEstado e) //checa se ganhou.
{
    int objetivo[3][3] = {   {1,2,3},{4,5,6},{7,8,9}   };

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (e.m[i][j] != objetivo[i][j])
                return 0;

    return 1;
}

void posVazio(matrizEstado e, int *l, int *c)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (e.m[i][j] == 9)
            {
                *l = i;
                *c = j;
                return;
            }
}

int posValida(int linha, int coluna)
{
    if (linha < 0 || linha >= 3)
    {
        return 0;
    }
    if (coluna < 0 || coluna >= 3)
    {
         return 0;
    }
    return 1;
}



int gerarVizinhos(matrizEstado atual, matrizEstado vizinho[])
{
    int qtd = 0;

    int linhaVazio=0, colunaVazio=0;
    posVazio(atual, &linhaVazio, &colunaVazio);

    for (int i = 0; i < 4; i++)
    {
        int novaLinha = linhaVazio + movs[i][0];
        int novaColuna = colunaVazio + movs[i][1];

        if (posValida(novaLinha, novaColuna))
        {
            matrizEstado novo = atual;
            int temp = novo.m[linhaVazio][colunaVazio];

            novo.m[linhaVazio][colunaVazio] = novo.m[novaLinha][novaColuna];
            novo.m[novaLinha][novaColuna] = temp;

            vizinho[qtd++] = novo;
        }
    }
    return qtd;
}

int filaVazia()
{
    return ini == fim;
}

void PrintEstado(matrizEstado e)
{
    printf("\n\t---------------------------\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\t");
        for (int j = 0; j < 3; j++)
        {
            if (e.m[i][j] == 9)
            {
                printf("|       |");
            }
            else{
                printf("|   %d   |", e.m[i][j]);
            }
        }
        printf("\n");
    }
    printf("\t---------------------------\n");
}

void printEstado(int estado[3][3])
{
    printf("\n\t---------------------------\n");
    for(int i=0; i<3; i++)
    {
        printf("\t");
        for(int j=0; j<3; j++)
        {
            if (estado[i][j] == 9)
            {
                printf("|       |");
            }
            else{
                printf("|   %d   |",estado[i][j]);
            }
        }
        printf("\n");
    }
    printf("\t---------------------------\n");
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

void ObjetivoEncontrado ()
{
    printf("\n\t****************************************************");
    printf("\n\t**                                                **");
    printf("\n\t**             Objetivo encontrado!               **");
    printf("\n\t**                                                **");
    printf("\n\t****************************************************\n\n");
}

void deepcopy(int estado[3][3], matrizEstado *e)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            (*e).m[i][j] = estado[i][j];
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

int verifica_matriz(int m[3][3])
{
    int verificacao=1;
    //int true_false;
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

int DFS_limitada(matrizEstado atual, int limite, int passopasso)
{
    if (ehObjetivo(atual))
    {
        if (passopasso == 1)
        {
            PrintEstado(atual);
        }
        return 1;
    }

    if (limite == 0)
    {return 0;}

    matrizEstado vizinhos[4];
    int qtd = gerarVizinhos(atual, vizinhos);

    for (int i = 0; i < qtd; i++)
    {
        if (passopasso == 1)
        {PrintEstado(vizinhos[i]);}

        if (DFS_limitada(vizinhos[i], limite - 1, passopasso))
            return 1;
    }

    return 0;
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
    int escolhe;

    while(1)
    {
    printf("\n\tDigite 0 para sair e qualquer coisa para continuar:\n\t");
    scanf("%d", &sair);

    if (sair==0){break;}

    printf("\n\tO tabuleiro gerado para você resolver é este:\n\n");

    do //loop pra criar matriz resolvivel
    {
        cria_random(m, &linhavazia, &colvazia, guarda_rand);
        V_ou_F = checa_matriz_possivel(guarda_rand);
    }while(V_ou_F == 0);
    printEstado(m);

    //escolher se quer jogar, BFS ou IDFS.
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
        int escolheDnv, passopasso;
        printf(" \n\tEscolha qual tipo de solução será usada:\n\n\t1 para BFS\n\t2 para IDDFS\n\t3 para DFS limitado\n\n\tDigite: ");
        scanf("%d", &escolheDnv);

        printf("\n\tDeseja ver o passo a passo da busca?\n\n\t1 para Sim\n\t2 para Não\n\n\tDigite: ");
        scanf("%d", &passopasso);

        int cont = 0;

        if(escolheDnv == 1)
        {
            printf("\n\tBUSCANDO...\n");
            matrizEstado inicial;
            deepcopy(m, &inicial);

            enfileira(inicial);
            marcaVisitado(inicial);
            while (!filaVazia())
            {
                matrizEstado atual = desenfileira();
                cont++;

                if(passopasso == 1)
                {
                    PrintEstado(atual);
                }
                if (ehObjetivo(atual))
                {
                    ObjetivoEncontrado();
                    PrintEstado(atual);
                    return;
                }
                matrizEstado vizinho[4];
                int qtd = gerarVizinhos(atual, vizinho);

                for (int i = 0; i < qtd; i++)
                {
                    if (!jaVisitado(vizinho[i]))
                    {
                        marcaVisitado(vizinho[i]);
                        enfileira(vizinho[i]);
                    }
                }
            }
            printf("Não existe solução\n");
        }
        else if(escolheDnv==2)//IDDFS
        {
            printf("\n\tBUSCANDO...\n");
            matrizEstado inicial;
            deepcopy(m, &inicial);
            {
                for (int limite = 0; limite <= 50; limite++)
                {
                    printf("\nTestando profundidade: %d\n", limite);

                    if (DFS_limitada(inicial, limite, passopasso))
                    {
                        ObjetivoEncontrado();
                        return;
                    }
                }

                printf("Não encontrado.\n");
            }
        }

        else if(escolheDnv==3)
        {
            matrizEstado inicial;
            deepcopy(m, &inicial);
            DFS_limitada(inicial, 30, passopasso);
        }
    }
        else
        {
            printf("\n\n\tvocê digitou uma opção inválida\n");
        }
    }
    return 0;
}
