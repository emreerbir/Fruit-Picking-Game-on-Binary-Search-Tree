#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Meyve{
	int firstValue;
	int currentValue;
	struct Meyve * sol;
	struct Meyve * sag;
}meyve;

meyve* Ekle(meyve* node, int deger);

meyve* sil(meyve* node, int deger);

meyve* atisYap(int deger, int atisGucu, meyve* node, int* kova);

meyve* olustur(int n, int m);

void bilgiAl(int *n, int *m);

void yazdir(meyve *node);

meyve* kontrol(meyve *node, int* kova);

int agacKontrol(meyve *node);

int maxf(meyve* node);

int maxc(meyve* node);

int minf(meyve* node);

int minc(meyve* node);

int randomKontrol(meyve* nodetmp, int randomSayi);

void push(int* kova, meyve* tmp);

int main(){
	srand(time(NULL));
	int n, m, deger, atisGucu, flag=1;
	meyve* node;
	bilgiAl(&n, &m);
	node = olustur(n, m);
	printf("Olusturulan agac: \n");
	yazdir(node);
	printf("\n");
	int *kova;
	kova = (int*)malloc(m*sizeof(int));
	int i;
	for(i=0;i<m;i++){
		kova[i] = 0;
	}
	
	do{
		printf("Atis gucunu giriniz: ");
		scanf("%d", &atisGucu);
		printf("Atis yapacaginiz meyvenin ilk degerini giriniz: ");
		scanf("%d", &deger);
		node = atisYap(deger, atisGucu, node, kova);
		printf("Agacin son hali: \n");
		yazdir(node);
		flag = agacKontrol(node);
	}while(flag);
	
	printf("Kovaya sirayla dusen meyveler su sekildedir: \n");
	
	for(i=0;i<m;i++){
		printf("%d ", kova[i]);
	}
	
	return 0;
}


void bilgiAl(int *n, int *m){
	printf("Maksimum meyve agirligini giriniz: ");
	scanf("%d", n);
	printf("Meyve adedini giriniz: ");
	scanf("%d", m);
}

meyve* Ekle(meyve* node, int deger){
	if(node==NULL){
		meyve* root = (meyve*)malloc(sizeof(meyve));
		root->firstValue=deger;
		root->currentValue=deger;
		root->sag=NULL;
		root->sol=NULL;
		return root;
	}
	
	if(node->firstValue < deger){
		node->sag = Ekle(node->sag, deger);
		return node;
	}
	node->sol = Ekle(node->sol, deger);
	return node;
}

meyve* atisYap(int deger, int atisGucu, meyve* node, int* kova){
	
	if(node==NULL){
		return NULL;
	}
	
	if(node->firstValue == deger){
		node->currentValue -= atisGucu;
		node = kontrol(node, kova);
		return node;
	}
	
	if(node->firstValue < deger){
		node->sag = atisYap(deger, atisGucu, node->sag, kova);
		return node;
	}
	
	node->sol = atisYap(deger, atisGucu, node->sol, kova);
	return node;
}

meyve* sil(meyve* node, int deger){
	if(node==NULL){
		return NULL;
	}
	
	if(node->firstValue == deger){
		if(node->sag==NULL && node->sol==NULL){
			return NULL;
		}
		
		if(node->sag!=NULL){
			node->firstValue = minf(node->sag);
			node->currentValue = minc(node->sag);
			node->sag=sil(node->sag, minf(node->sag));
			return node;
		}
		
		node->firstValue = maxf(node->sol);
		node->currentValue = maxc(node->sol);
		node->sol=sil(node->sol, maxf(node->sol));
		return node;
		
	}
	
	if(node->firstValue < deger){
		node->sag = sil(node->sag, deger);
		return node;
	}
	
	node->sol = sil(node->sol, deger);
	return node;
}

void yazdir(meyve *node){
	if(node == NULL){
		return;
	}
	yazdir(node->sol);
	printf(" %d (%d) ", node->firstValue, node->currentValue);
	yazdir(node->sag);
}

meyve* kontrol(meyve *node, int* kova){
	meyve* tmp = node;
	if(tmp == NULL){
		return;
	}
	kontrol(tmp->sol, kova);
	if(tmp->currentValue <= 0){
		push(kova, tmp);
		node = sil(node, tmp->firstValue);
	}
	kontrol(tmp->sag, kova);
	return node;
}

void push(int* kova, meyve* tmp){
	int i=-1;
	do{
		i++;
		if(kova[i]==0){
			kova[i]=tmp->firstValue;
		}
	}while(kova[i]!=tmp->firstValue);
}

int maxf(meyve* node){
	while(node->sag != NULL){
		node = node->sag;
	}
	return node->firstValue;
}

int maxc(meyve* node){
	while(node->sag != NULL){
		node = node->sag;
	}
	return node->currentValue;
}

int minf(meyve* node){
	while(node->sol != NULL){
		node = node->sol;
	}
	return node->firstValue;
}

int minc(meyve* node){
	while(node->sol != NULL){
		node = node->sol;
	}
	return node->currentValue;
}

meyve* olustur(int n, int m){
	meyve* nodetmp = NULL;
	int i, randomSayi;
	for(i=0;i<m;i++){
		do{
			randomSayi = rand() % n + 1;
		}while(randomKontrol(nodetmp, randomSayi));
		printf("Uretilen sayi: %d\n", randomSayi);
		nodetmp = Ekle(nodetmp, randomSayi);
	}
	return nodetmp;
}

int randomKontrol(meyve* nodetmp, int randomSayi){
	int flag = 0;
	if(nodetmp == NULL){
		return 0;
	}
	flag += randomKontrol(nodetmp->sol, randomSayi);
	if(nodetmp->firstValue==randomSayi){
		flag = 1;
	}
	flag += randomKontrol(nodetmp->sag, randomSayi);
	
	return flag;
}

int agacKontrol(meyve *node){
	if(node==NULL){
		return 0;
	}
	return 1;
}


