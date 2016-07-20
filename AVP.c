#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if(a->mat > ele) return busca(ele,a->esq);
	else return busca(ele,a->dir);
}
TAluno *obtemPai(TAluno *a)
{
	if(a)return a->pai;
}

void mudaCR(TAluno *a,int mat, float novoCR)
{
    TAluno *x = busca(mat,a);
    if(x)x->cr = novoCR;
    else{printf("Aluno não encontrado");}
}

void mudaNome(TAluno *a, int mat, char novoNome[80])
{
    TAluno *x = busca(mat,a);
    if(x)strcpy(x->nome,novoNome);
    else{printf("Aluno não encontrado");}
}

void RSE(TAluno *a, TAluno **arvore)
{
    TAluno *y = a->dir;
    a->dir = y->esq;
    if(y->esq)
    {
        y->esq->pai = a;
    }
    y->pai = a->pai;
    if(!a->pai)
        *arvore = y;
    else
    {
        if(a == a->pai->esq)
            a->pai->esq = y;
        else a->pai->dir = y;
    }
    y->esq = a;
    a->pai = y;
}
void RSD(TAluno *a, TAluno **arvore)
{
    TAluno *y = a->esq;
    a->esq = y->dir;
    if(y->dir)
        y->dir->pai = a;
    y->pai = a->pai;
    if(!a->pai)
        *arvore = y;
    else
    {
        if(a == a->pai->dir)
            a->pai->dir = y;
        else a->pai->esq = y;
    }
    y->dir = a;
    a->esq = y;
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
					RSE(aux,&a);
					pai = obtemPai(aux);
					avo = obtemPai(pai);
				}
				pai->cor='p';
				avo->cor='v';
				RSD(avo,&a);
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
					a = RSD(aux,&a);
					pai = obtemPai(aux);
					avo = obtemPai(pai);
				}
				pai->cor = 'p';
				avo->cor = 'v';
				RSE(avo,&a);
			}
		}
	}
	a->cor = 'p';
	return a;
}

TAluno* insere(TAluno *a, int mat,float cr, char nome[81])
{
	//caso haja o matento na lista, retorne a propria arvore
	if(busca(mat,a))return a;
	TAluno *novo = (TAluno*)malloc(sizeof(TAluno));
	novo->mat = mat;
	novo->esq=novo->dir=NULL;
	novo->cr= cr;
	strcpy(novo->nome,nome);
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
		if(x->mat<mat)x=x->dir;
		else x=x->esq;
	}
	if(mat < w->mat)
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
      for(j=0; j<=andar; j++) printf("            ");
      printf("MAT:%d Nome:%s,C:%c\n", a->mat,a->nome,a->cor);
      imprime_aux(a->dir,andar+1);
  }
}

void imprime(TAluno *a){
  imprime_aux(a, 0);
}

int main(void)
{
	FILE *fp = fopen("teste.txt","r");
	char buff[30];
    int mat;
    float cr;
    char nome[30];
    TAluno *a = NULL;
    int c = 0;
    while(c < 3){
        //pega matrícula
        fscanf(fp, "%s", buff);
        mat = atoi(buff);
        //pega cr
        fscanf(fp, "%s", buff);
        cr = strtof(buff,NULL);
        //pega nome
        fgets(buff, 30, (FILE*)fp);
        strcpy(nome,buff);
        //insere na árvore
        a = insere(a,mat,cr,nome);
        c++;
    }
    fclose(fp);
    imprime(a);
	return 0;
}

