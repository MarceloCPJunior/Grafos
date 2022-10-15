#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int lista_adj[1000];
    int tam_lista_adj;
    int in;
    int lower;
}vertice;


void mostrar_tudo (vertice * vertices, int qtd_vertices);
void dfs(vertice * vertices, int qtd_vertices, int raiz, int cont, int pai);

int pontes[1000];
int indice;

int main()
{
    int qtd_vertices, qtd_arestas;
    int i,a,b,cont=0;
    vertice * vertices;
    scanf("%d %d",&qtd_vertices, &qtd_arestas);
    
    indice = 0;

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(i=0;i<qtd_arestas;i++)
    {
        scanf("%d %d",&a,&b);
        vertices[a].lista_adj[vertices[a].tam_lista_adj] = b;
        vertices[a].tam_lista_adj++;
        vertices[b].lista_adj[vertices[b].tam_lista_adj] = a;
        vertices[b].tam_lista_adj++;
    }

    for(i=1;i<=qtd_vertices;i++)
    {
        if (vertices[i].visitado==0)
        {
            dfs(vertices,qtd_vertices,i,cont,i);
        }
    }
	
	printf("\nPontes:");
	for(i = 0; i < indice; i += 2){
		printf("\n%d ponte com %d", pontes[i], pontes[i+1]);
	}

    return 0;
}

void dfs(vertice * vertices, int qtd_vertices, int raiz, int cont, int pai)
{
    int i;
    if (vertices[raiz].visitado!=0)
    {
        return;
    }

    vertices[raiz].visitado=1;
    vertices[raiz].in=cont;
	vertices[raiz].lower=cont; 
	
    for(i=0;i<vertices[raiz].tam_lista_adj;i++)
    {
        if (vertices[vertices[raiz].lista_adj[i]].visitado==0)
        {
        	cont += 1;
            dfs(vertices,qtd_vertices,vertices[raiz].lista_adj[i],cont, raiz);
        }else{
        	if(vertices[raiz].lista_adj[i] != pai){
        		if(vertices[vertices[raiz].lista_adj[i]].in < vertices[raiz].lower){
        			vertices[raiz].lower = vertices[vertices[raiz].lista_adj[i]].in;
				}
			}
		}
    }
    
    if(vertices[raiz].lower > vertices[pai].in){
    	pontes[indice] = pai;
    	pontes[indice+1] = raiz;
    	indice += 2;
	}else{
		if(vertices[raiz].lower < vertices[pai].lower){
			vertices[pai].lower = vertices[raiz].lower;
		}
	}
}
