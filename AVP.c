#include <stdio.h>
#include <stdlib.h>
TAVP *insere(TAVP *a, int elem)
{
	if(busca(a,elem))return a;
	TAVP *novo = (TAVP*)malloc(sizeof(TAVP));
	novo -> info = elem;
	novo->esq=novo->dir=NULL;
	if(!a)
	{
		novo->cor = 'p';
		novo->pai=NULL;
		return novo;
	}
	TAVP *x=a;*w;
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
	a=corr_ins(a,novo);p
	return novo;
}

TAVP *corr_ins(TAVP *a, TAVP *z)
{
	TAVP *aux = z; *pai = obtemPai(aux), *avo = obtemPai(pai),*tio;
	while(aux && aux != a && pai->cor=='v' && avo)
	{
		if(pai == avo->esq)
		{
			tio = avo->dir;
			if(tio && tio->cor = 'v')
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
int main(void)
{
	int p;
	scanf("%d",&p);
	printf("%d",p);
	return 0;
}
