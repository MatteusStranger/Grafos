#include <stdio.h>
#include <stdlib.h>
#define maxvertices 100
#define maxarestas 4500
#define true 1
#define false 0

typedef struct grafo{
    int m[maxvertices+1][maxvertices+1];
    int vertices;
    int arestas;
}grafo;
void inicializa(grafo *g){
    short i,j;
    printf("Entre com a quantidade de vertices:\n");
    scanf("%d",&g->vertices);
    g->arestas=0;
    for(i=0;i<g->vertices;i++){
        for(i=0;i<g->vertices;i++){
            g->m[i][j]=0;
        }
    }
    printf("\nInicializado\n\n");
}
void conecta(grafo *g){
    short x,y,i,j;
    printf("Entre com os vertices que se conectam\n");
    scanf("%hd%hd",&x,&y);
    while(x!=0||y!=0){
            g->m[x][y]=1;
            g->m[y][x]=1;
            g->arestas++;
            scanf("%hd%hd",&x,&y);
        }
    }
void itens(grafo *g){
    short i,j;
    int grau;
    short completo = true;
    short conexo = true;
    for(i=1;i<=g->vertices;i++){
        grau=0;
        for(j=1;j<=g->vertices;j++){
            if(g->m[i][j]==1){
                grau++;
            }
        }
        printf("O vertice %hd tem grau %d\n",i,grau);
        completo = completo&&(grau == g->vertices-1);
        conexo = conexo && (grau>0);
    }
    if(completo){
            printf("\nGrafo Completo\n");
        }else{
            printf("Grafo Nao Completo\n");
        }
    if(conexo){
        printf("\nGrafo Conexo\n");
    }else{
        printf("\nGrafo Desconexo\n");
    }
}
void CaminhoEuleriano(grafo *g){
    int total=0,grau,i=0,j;
    while(total<=2&&i<=g->vertices){
        grau=0;
        for(j=0;j<=g->vertices;j++){
            grau=grau+g->m[i][j];
            if(grau%2!=0){
                total++;
                i++;
            }
        }
    }
    if(total>2){
        printf("\nNao existe caminho Euleriano\n");
    }else{
        printf("\nExiste caminho Euleriano\n");
    }
}
int main(){
    grafo g;
    inicializa(&g);
    conecta(&g);
    itens(&g);
    CaminhoEuleriano(&g);

    return 0;
}
