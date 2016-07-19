#include <stdio.h>
#include <stdlib.h>

typedef struct aluno
{
	int mat;
	float cr;
	char nome[81], cor;
	struct aluno *pai,*esq,*dir;
}TAluno;

TAluno *busca(int ele, TAluno *a)
{
	if(!a)return NULL;
	if(ele == a->mat) return a;
	if(a->mat < ele) return busca(ele,a->esq);
	else return busca(ele,a->dir);
}
TAluno *obtemPai(TAluno *a)
{
	if(a)return a->pai;
}


TAluno *RSE(TAluno *a, TAluno *novoPai)
{
	TAluno *novo = a->dir;
	a->dir = novo->esq;
	novo->esq = a;
	novo->cor = a->cor;
	novo->pai = novoPai;
	a->cor = 'v';
	return novo;
}

TAluno *RSD(TAluno *a, TAluno *novoPai)
{
	TAluno *novo = a->esq;
	a->esq = novo->dir;
	novo->dir = a;
	novo->cor = a->cor;
	novo->pai = novoPai;
	a->cor = 'v';
	return novo;
}

TAluno *corr_ins(TAluno *a, TAluno *z)
{
	TAluno *aux = z, *pai = obtemPai(aux), *avo = obtemPai(pai),*tio;
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

TAluno* insere(TAluno *a, int elem)
{
	//caso haja o elemento na lista, retorne a propria arvore
	if(busca(elem,a))return a;
	TAluno *novo = (TAluno*)malloc(sizeof(TAluno));
	novo->mat = elem;
	novo->esq=novo->dir=NULL;
	if(!a)
	{
		novo->cor = 'p';
		novo->pai=NULL;
		return novo;
	}
	TAluno *x=a,*w;
	while(x)
	{
		w = x;
		if(x->mat<elem)x=x->dir;
		else x=x->esq;
	}
	if(elem < w->mat)
		w->esq = novo;
	else w->dir = novo;
	novo->pai = w;
	novo->cor='v';
	a=corr_ins(a,novo);
	return a;
}

TAluno *irmao(TAluno *a)
{
	if(a == a->pai->esq)
		return a->pai->dir;
	return a->pai->esq;
}

void imprime_aux(TAluno *a, int andar){
  if(a){
      int j;
      imprime_aux(a->esq,andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d %c\n", a->mat,a->cor);
      imprime_aux(a->dir,andar+1);
  }
}

void imprime(TAluno *a){
  imprime_aux(a, 0);
}

int main(void)
{
	int p = 0;
	TAluno *a = NULL;
	do
	{
		scanf("%d",&p);
		imprime(a);
		a = insere(a,p);
	}while(p != 0);
	imprime(a);
	return 0;
}
