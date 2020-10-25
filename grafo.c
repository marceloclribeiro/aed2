#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INFINITO 999

int **criaGrafo(int n);
void leArestas(int **grafo, int n);
void imprimeGrafo(int **grafo, int n);
void liberaGrafo(int **grafo, int n);
void djikstra(int **grafo, int n, int ini, int desti);

int main (){

    int n,x,y,loop;
    int **grafo=NULL;
    printf("Insira o numero de vertices:");
    scanf("%d",&n);
    
    grafo = criaGrafo(n);

    imprimeGrafo(grafo,n);

    leArestas(grafo, n);

    imprimeGrafo(grafo,n);

    int va,vb;

    do{

    printf("\nSelecione que caminho encontrar:");
    scanf("%d %d", &va,&vb);
    dijkstra(grafo,n,va,vb);

    printf("Testar outro caminho?(1=Sim,0=Nao):");
    scanf("%d",&loop);

    }
    while(loop!=0);

    return 0;
}

int **criaGrafo(int n) {
    int x,y, **grafo;
    
    grafo = (int**)malloc(n * sizeof(int*));

    if (!grafo) {
        printf("Erro ao alocar memoria\n");
        exit(0);
    }

    for(x = 0; x < n; x++) {
        grafo[x] = (int*)malloc(n * sizeof(int));

        if (!grafo[x]) {
            printf("Erro ao alocar memoria\n");
            exit(0); 
        }
    }

     for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++) {
            grafo[x][y] = INFINITO;
        }
    }

    return grafo;
}

void imprimeGrafo(int **grafo, int n) {
    int x, y;

    for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++) {
            printf("%d ", grafo[x][y]);
        }
        printf("\n");
    }
}

void leArestas(int **grafo, int n) {
    int x, y, valor, teste;
    do{
        printf("Insira a aresta(v,v,d):");
        scanf("%d",&x);
        scanf("%d",&y);
        scanf("%d",&grafo[x][y]);
        printf("Ler outra aresta?:(0=F,1=V)");
        scanf("%d",&teste);
    }
    while(teste!=0);
}


void dijkstra(int **grafo,int n,int inicial,int final)
    {

        int distancia[n],pred[n],visitado[n];
        int cont,min,prox,x,y;  
        prox=final;

        for(y=0;y<n;y++)
        {
            distancia[y]=grafo[inicial][y];
            pred[y]=inicial;
            visitado[y]=0;
        }

        distancia[inicial]=0;
        visitado[inicial]=1;
        cont=1;

        while(cont<n-1)
        {
            min=INFINITO;

            for(x=0;x<n;x++)
                if(distancia[x]<min&&!visitado[x]) //tenho conexão com o outro vertice && não foi visitado
                {
                    min=distancia[x];
                    prox=x;
                }

            //verifica se existe melhor caminho
            visitado[prox]=1;  //marco que o nó ta sendo visitado
            for(x=0;x<n;x++){
                if(!visitado[x])
                    if(min+grafo[prox][x]<distancia[x]) // testo se a conexão é menor que a que eu ja tenho
                    {
                        distancia[x]=min+grafo[prox][x]; // se sim,atualizar a menor distancia
                        pred[x]=prox;                    // e salvar na posição do vertice o vertice anterior
                    }
            }
            cont++;
        }
        printf("\nDistancia=%d",distancia[final]);
        printf("\nCaminho=%d",final);
        do
        {
            final=pred[final];
            printf("<-%d",final);
        }while(final!=inicial);
    }
