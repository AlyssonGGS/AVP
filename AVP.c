#include <stdio.h>
#include <stdlib.h>

typedef struct avp
{
	int info;
	char cor;
	struct avp *pai,*esq,*dir;
}TAVP;

TAVP *busca(int ele, TAVP *a)
{
	if(!a)return NULL;
	if(ele == a->info) return a;
	if(a->info < ele) return busca(ele,a->esq);
	else return busca(ele,a->dir);
}
TAVP *obtemPai(TAVP *a)
{
	if(a)return a->pai;
}


TAVP *RSE(TAVP *a, TAVP *novoPai)
{
	TAVP *novo = a->dir;
	a->dir = novo->esq;
	novo->esq = a;
	novo->cor = a->cor;
	novo->pai = novoPai;
	a->cor = 'v';
	return novo;
}

TAVP *RSD(TAVP *a, TAVP *novoPai)
{
	TAVP *novo = a->esq;
	a->esq = novo->dir;
	novo->dir = a;
	novo->cor = a->cor;
	novo->pai = novoPai;
	a->cor = 'v';
	return novo;
}

TAVP *corr_ins(TAVP *a, TAVP *z)
{
	TAVP *aux = z, *pai = obtemPai(aux), *avo = obtemPai(pai),*tio;
	while(aux && aux != a && pai->cor=='v' && avo)
	{
		if(pai == avo->esq)
		{
			tio = avo->dir;
			if(tio && tio->cor == 'v')
			{
				tio->cor = pai->cor='p';
				avo->cor = 'v';
				aux=avo;
				pai = obtemPai(aux);
				avo = obtemPai(pai);
			}
			else
			{
				if(aux==pai->dir)
				{
					aux = pai;
					a = RSE(a,aux);
					pai = obtemPai(aux);
					avo = obtemPai(pai);
				}
				pai->cor='p';
				avo->cor='v';
				a = RSD(a,avo);
			}
		}
		else
		{
			tio = avo->esq;
			if(tio && tio->cor == 'v')
			{
				tio->cor = pai->cor = 'p';
				avo->cor = 'v';
				aux = avo;
				pai = obtemPai(aux);
				avo = obtemPai(pai);
			}
			else
			{
				if(aux==pai->esq)
				{
					aux = pai;
					a = RSD(a,aux);
					pai = obtemPai(aux);
					avo = obtemPai(avo);
				}
				pai->cor = 'p';
				avo->cor = 'v';
				a = RSE(a,avo);
			}
		}
	}
	a->cor = 'p';
	return a;
}

TAVP* insere(TAVP *a, int elem)
{
	//caso haja o elemento na lista, retorne a propria arvore
	if(busca(elem,a))return a;
	TAVP *novo = (TAVP*)malloc(sizeof(TAVP));
	novo->info = elem;
	novo->esq=novo->dir=NULL;
	if(!a)
	{
		novo->cor = 'p';
		novo->pai=NULL;
		return novo;
	}
	TAVP *x=a,*w;
	while(x)
	{
		w = x;
		if(x->info<elem)x=x->dir;
		else x=x->esq;
	}
	if(elem < w->info)
		w->esq = novo;
	else w->dir = novo;
	novo->pai = w;
	novo->cor='v';
	a=corr_ins(a,novo);
	return a;
}



void imprime_aux(TAVP *a, int andar){
  if(a){
      int j;
      imprime_aux(a->esq,andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->info);
      imprime_aux(a->dir,andar+1);
  }
}

void imprime(TAVP *a){
  imprime_aux(a, 0);
}

int main(void)
{
	int p = 0;
	TAVP *a = NULL;
	do
	{
		scanf("%d",&p);
		a = insere(a,p);
	}while(p != 0);
	imprime(a);
	return 0;
}
