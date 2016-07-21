
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
					RSD(aux,&a);
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

void troca(TAluno*a,TAluno*b){
	int temp = a->mat;
	a->mat = b->mat;
	b->mat = temp;
	
	a->cr = b->cr;
	strcpy(a->nome,b->nome);
	
}

void retira(TAluno* a,int ele){
	if(!a) return;
	
	TAluno *p = busca(ele,a);
	if(!p) return;
	
	if((p->esq)&&(p->dir)){
		TAluno* f = p->esq;
		while(f->dir) f=f->dir;
		
		troca(p,f);
		
		retira(a,ele);
	}
	else{
		if(p->cor='v'){
			TAluno* temp = p;
			if(p->esq){
				p = p->esq;	
			} 
			else{
				p=p->dir;	
			} 
			//corrigindo o campo pai dos nos envolvidos na troca
			if(temp->pai){
				if(temp->pai->esq == temp) temp->pai->esq = p;
				else temp->pai->dir = p;
			}
			if(!p) p->pai=temp->pai;
			free(temp);
		}
		else{
			if(p->cor='p'){
				
				if((p->esq)&&(p->esq->cor=='v')){
					p->esq->cor='p'; //pinta filho
					
					TAluno* temp = p;
					p = p->esq;
					if(temp->pai){
						if(temp->pai->esq == temp) temp->pai->esq = p;
						else temp->pai->dir = p;
					}
					if(!p) p->pai=temp->pai;					
					free(temp);
				}
				else if((p->dir)&&(p->dir->cor=='v')){
						p->dir->cor='p'; //pinta filho
					
						TAluno* temp = p;
						p = p->dir;
						if(temp->pai){
							if(temp->pai->esq == temp) temp->pai->esq = p;
							else temp->pai->dir = p;
						}
						if(!p) p->pai=temp->pai;					
						free(temp);
				}	
				else{
					TAluno* temp = p;
					if(p->esq){
						p = p->esq;	
					}	 
					else{
						p=p->dir;	
					} 
					//corrigindo o campo pai dos nos envolvidos na troca
					if(temp->pai){
						if(temp->pai->esq == temp) temp->pai->esq = p;
						else temp->pai->dir = p;
					}
					if(!p) p->pai=temp->pai;
					free(temp);
					
					//continuar com os outros casos
					//delete_one_child(a);
				}
			}
		}
	}
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
      printf("MAT:%d C:%c\n", a->mat,a->cor);
      imprime_aux(a->dir,andar+1);
  }
}

void imprime(TAluno *a){
  imprime_aux(a, 0);
}
void imprime_no(TAluno *a)
{
    if(!a) return;
    printf("Matricula:%d / Nome:%s / CR:%f\n",a->mat,a->nome,a->cr);
}
int mudaMatricula(TAluno *a, int mat, int novoMat)
{
    TAluno *aux = busca(mat,a);
    if(busca(novoMat,a))
    {
        printf("Matricula invalida\n");
        return 0;
    }
    if(aux)
    {
        float cr = aux->cr;
        char nome[80];
        strcpy(nome,aux->nome);
        //remove(a,mat);
        //insere(a,novoMat,cr,nome);
        return 1;
    }else
    {
        printf("Aluno nao encontrado");
        return 0;
    }
}
void interface(int maiorMat,TAluno *a)
{
    int op;
    int mat = maiorMat,matAux,novaMat;
    float cr;
    char nome[80];
    printf("Insira uma das opções para seguir:\n");
    printf("1-> Inserir aluno\n");
    printf("2-> Remover aluno\n");
    printf("3-> Modificar CR\n");
    printf("4-> Modificar nome\n");
    printf("5-> Modificar matricula\n");
    printf("6-> Para imprimir um aluno\n");
    printf("7-> Para imprimir a estrutura\n");
    scanf("%d",&op);
    while(op > 0)
    {
        switch(op)
        {
            case 1:
                printf("Insira o nome: ");
                fgets (nome, 80, stdin);
                scanf ("%[^\n]%*c", nome);
                printf("Insira o CR: ");
                scanf("%f",&cr);
                insere(a,++mat,cr,nome);
                break;
            case 2:
                printf("Insira a matricula: ");
                scanf("%d",&matAux);
				//retira(a,matAux);
                break;
            case 3:
                printf("Insira a matricula: ");
                scanf("%d",&matAux);
                printf("Insira o novo cr: ");
                scanf("%f",&cr);
                mudaCR(a,matAux,cr);
                break;
            case 4:
                printf("Insira a matricula: ");
                scanf("%d",&matAux);
                printf("Insira o novo nome: ");
                scanf("%s",nome);
                mudaNome(a,matAux,nome);
                break;
            case 5:
                printf("Insira a matricula: ");
                scanf("%d",&matAux);
                printf("Insira a nova matricula: ");
                scanf("%d",&novaMat);
                mat += mudaMatricula(a,mat,novaMat);
                break;

            case 6:
                printf("Insira a matricula: ");
                scanf("%d",&matAux);
                TAluno *aux = busca(matAux,a);
                imprime_no(aux);
                break;
            case 7:
                imprime(a);
                break;
            default:
                break;
        }
        printf("Insira uma das opções para seguir:\n");
        printf("1-> Inserir aluno\n");
        printf("2-> Remover aluno\n");
        printf("3-> Modificar CR\n");
        printf("4-> Modificar nome\n");
        printf("5-> Modificar matricula\n");
        printf("6-> Para imprimir um aluno\n");
        printf("7-> Para imprimir a estrutura\n");
        printf("0-> Para fechar\n");
        scanf("%d",&op);
    }
}
int main(void)
{
	FILE *fp = fopen("teste.txt","r");
	char buff[30];
    int mat;
    float cr;
    char nome[30];
    TAluno *a = NULL;
    int c = 0,maiorMat = 0;
    while(c < 100){
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
        maiorMat++;
    }
    fclose(fp);
    //imprime(a);
    interface(maiorMat,a);
	return 0;
}

