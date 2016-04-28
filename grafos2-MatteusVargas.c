#include <stdio.h>
#include <math.h>
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
	for(i=1;i<=g->vertices;i++){
		for(j=1;j<=g->vertices;j++){
			g->m[i][j] = 0;
		}
	}
	printf("Insira os vertices\nEntre com (0,0) para finalizar a insercao\n");
	scanf("%hu%hu",&i,&j);
	while(i!=0){
		g->m[i][j] = 1;
		scanf("%hu%hu",&i,&j);
	}
	printf("\nA1\n");
	for(i=1;i<=g->vertices;i++){
		for(j=1;j<=g->vertices;j++){
			printf("%hu ",g->m[i][j]);
			if(j==g->vertices){
				printf("\n");
			}
		}
	}
}

void ImprimeN(grafo g){	
	short i,j;
	for(i=1;i<=g.vertices;i++){
		for(j=1;j<=g.vertices;j++){
			printf("%d ",g.m[i][j]);
			if(j==g.vertices){
				printf("\n");
			}
		}
	}
}	
void Alcabilidade(grafo *g){
	short m[g->vertices][g->vertices],a[g->vertices][g->vertices],f[g->vertices][g->vertices];
	short i,j,k;
	for(i=1;i<=g->vertices;i++){
		for(j=1;j<=g->vertices;j++){
			a[i][j] = g->m[i][j];
			m[i][j] = g->m[i][j];
			f[i][j]=0;
		}
	}
	short n = 2;
	do{
		for(i=1;i<=g->vertices;i++){
			for(j=1;j<=g->vertices;j++){
				for(k=1;k<=g->vertices;k++){
					if((f[i][j]+m[i][k]*a[k][j])==0){
						f[i][j]=0;
					}else{
						f[i][j]=1;
					}
				}
			}
		}
		printf("A%d\n",n);
		n++;
		for(i=1;i<=g->vertices;i++){
			for(j=1;j<=g->vertices;j++){
				printf("%hu ",f[i][j]);
				m[i][j]=f[i][j];
				if(j==g->vertices){
					printf("\n");
				}
			}
		}
		for(i=1;i<=g->vertices;i++){
			for(j=1;j<=g->vertices;j++){
				m[i][j]=f[i][j];
			}
		}
		for(i=1;i<=g->vertices;i++){
			for(j=1;j<=g->vertices;j++){
				f[i][j]=0;
			}
		}
		printf("\n");
	}while(n<=g->vertices);
}
void Resultante(grafo *g){
	short i,j,k;
	for(k=1; k<=g->vertices; k++){
		for(i=1; i<=g->vertices; i++){
			for(j=1; j<=g->vertices; j++){
				g->m[i][j]= g->m[i][j]||(g->m[i][k+1]&&g->m[k+1][j]);
			}
		}
	}
		printf("\nR\n");
		for(i=1;i<=g->vertices;i++){
			for(j=1;j<=g->vertices;j++){
				printf("%hu ",g->m[i][j]);
				if(j==g->vertices){
					printf("\n");
				}
			}
		}
}
void Conectividade(grafo *g){
	short forte=true,medio=true,fraco=true;
	short i,j,k;
	for(i=1;j<=g->vertices;j++){
		for(j=1;k<=g->vertices;k++){
			if(i!=j){
				if((g->m[i][j]==g->m[j][i])&&(g->m[i][j]==1)){
					forte = forte&&true;
					medio = medio&&false;
				}else{
					forte = forte&&false;
				}
				if(g->m[i][j]!=g->m[j][i]){
					medio=medio&&true;
				}
				if((g->m[i][j]==g->m[j][i])&&(g->m[i][j]==0)){
					fraco=fraco&&true;
				}
			}
		}
	}
	if(forte){
		printf("Fortemente conexo\n");
	}
	if(medio){
		printf("Unilateralmente conexo\n");
	}else{
		printf("Fracamente conexo\n");
	}
}
int main(){
	grafo g;
	inicializa(&g);
	printf("\n");
	Alcabilidade(&g);
	Resultante(&g);
	printf("\n");
	Conectividade(&g);
	return 0;
}
