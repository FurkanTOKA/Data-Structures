#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 
 */

struct dugum{
    int key;
    // istenilen diger bilgiler
};

struct heap{
    struct dugum *dizi;
    int kapasite;
    int eleman_sayisi;
};

struct heap *heap_olustur(int kapasite){
    struct heap *gecici;
    gecici=(struct heap*)malloc(sizeof(struct heap));
    if(!gecici){
        printf("Dinamik alan ayirma basarisiz... \n");
        exit(1);
    }
    gecici->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));
    if(!gecici->dizi){
       printf("Dinamik alan ayirma basarisiz... \n");
       exit(1); 
    }
    gecici->kapasite=kapasite;
    gecici->eleman_sayisi=0;
    return gecici;
}

void heap_olustur_yeni(struct heap **h,int kapasite){
   
    *h=(struct heap*)malloc(sizeof(struct heap));
    if(!*h){
        printf("Dinamik alan ayirma basarisiz... \n");
        exit(1);
    }
    (*h)->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));
    if(!(*h)->dizi){
       printf("Dinamik alan ayirma basarisiz... \n");
       exit(1); 
    }
    (*h)->kapasite=kapasite;
    (*h)->eleman_sayisi=0;
    
}

void print_heap(struct heap *heap){
    int i;
    for(i=0; i<heap->eleman_sayisi; i++) printf("%4d",heap->dizi[i].key);
    printf("\n");   
    
}

void initialize_heap(struct heap *heap,int eleman_sayisi, int aralik){
    int i,j;
    int yeni,cik;
    
    if(eleman_sayisi >heap->kapasite) {
        printf("Heap gerekli kapasiteye sahip degil... exit...\n");
        exit(1);
    }
    srand(time(NULL));
    
    heap->dizi[0].key=rand()%aralik;
    for(i=1; i<eleman_sayisi; i++){
        while(1){
            cik=1;
            yeni=rand()%aralik;
            for(j=0; j<i; j++){
                if(yeni==heap->dizi[j].key){
                    cik=0; break;
                }
            }
            if(cik==0) continue;
            heap->dizi[i].key=yeni;
            break;
        }
    }
    heap->eleman_sayisi=eleman_sayisi;
}

void buble_down(struct heap *heap, int index){
    int sol,sag;
    sol=2*index+1;
    sag=2*index+2;
    int temp_key;
    
    while((sol <heap->eleman_sayisi && heap->dizi[index].key < heap->dizi[sol].key) || (sag <heap->eleman_sayisi && heap->dizi[index].key < heap->dizi[sag].key)){
        if(sag>=heap->eleman_sayisi || heap->dizi[sol].key >heap->dizi[sag].key){
          temp_key = heap->dizi[sol].key;
          heap->dizi[sol].key=heap->dizi[index].key;
          heap->dizi[index].key=temp_key;
          index=2*index+1;
          
       }
        else{
          temp_key = heap->dizi[sag].key;
          heap->dizi[sag].key=heap->dizi[index].key;
          heap->dizi[index].key=temp_key;
          index=2*index+2;  
        } 
          sol=2*index+1;
          sag=2*index+2;
    }          
            
}

void heapify(struct heap *heap){
    int i;
    for(i=heap->eleman_sayisi/2-1; i>=0; i--) buble_down(heap,i);
}

void buble_up(struct heap *heap, int index){
    int parent, temp_key;
    parent=(index-1)/2;
    
    while(parent>=0 && heap->dizi[parent].key <heap->dizi[index].key){
        temp_key= heap->dizi[parent].key;
        heap->dizi[parent].key=heap->dizi[index].key;
        heap->dizi[index].key=temp_key;
        index=parent;
        parent=(index-1)/2;
        
    }
}


void heap_insert(struct heap *heap,int key){
    if(heap->eleman_sayisi <heap->kapasite){
        heap->eleman_sayisi++;
        heap->dizi[heap->eleman_sayisi-1].key=key;
        buble_up(heap,heap->eleman_sayisi-1);
    }
}

void delete_max(struct heap *heap){
    int temp_key;
    if(heap->eleman_sayisi>1){
        temp_key=heap->dizi[0].key;
        heap->dizi[0].key=heap->dizi[heap->eleman_sayisi-1].key;
        heap->dizi[heap->eleman_sayisi-1].key=temp_key;
        heap->eleman_sayisi--;
        buble_down(heap,0);
    }
}

void heap_sort(struct heap *heap){
    int i;
    int temp=heap->eleman_sayisi;
    for(i=1; i<temp; i++) delete_max(heap);
    heap->eleman_sayisi=temp;
}

int heap_mi(struct heap* h)
{
    int i;
    int sol = (2*i)+1;
    int sag = (2*i)+2;
    if(h == NULL) return 1;
    
    for(i=0; i<h->eleman_sayisi/2; i++)
    {
    	if(h->dizi[i].key > h->dizi[sol].key || (sag < h->eleman_sayisi && h->dizi[i].key > h->dizi[sag].key)) return 0;
	}
	return 1;
}

int heapi_bozan_eleman(struct heap *h) // 2017 Final
{
	int i;
    int sol = (2*i)+1;
    int sag = (2*i)+2;
    
    int kontrol = 1;
    int bozan;
    
    for(i=0; i<h->eleman_sayisi/2; i++)
    {
    	if(h->dizi[i].key < h->dizi[sol].key || (sag < h->eleman_sayisi && h->dizi[i].key < h->dizi[sag].key))
    	{
    		kontrol = 0;
    		bozan = h->dizi[i].key;
		}
		
		if(kontrol == 0)
		{
			break;
		}
	}
	
	if(kontrol == 0)
	{
		return bozan;
	}
	else
	{
		printf("HEAP YAPISI BOZUK DEGILDIR !");
		return 1;
	}
	
}

int k_ninci_buyugu_getir(struct heap *h, int k) // Kitaptaki Soru
{
	struct heap *h2 = h;
	int buyuk = 0;
	int i =0;
	
	if(h->kapasite == 0) return -1;
	if(h->eleman_sayisi < k) return -1;
	
	
	for(i; i<k-1; i++)
	{
		delete_max(h2);
		
	}
	printf("%d . buyuk eleman -> %d \n",k,h2->dizi[0].key);
	
	return h2->dizi[0].key;
	
}

int k_ninci_elemanin_buyuk_cocugu(struct heap *h, int k) // Kitaptaki Soru
{
	int sol = (2*k+1);
	int sag = (2*k+2);
	
	if(h->kapasite == 0) return -1;
	
	if(sol <= h->kapasite && h->dizi[sol].key > h->dizi[sag].key) return h->dizi[sol].key;
	
	
	if(sag <= h->kapasite && h->dizi[sol].key < h->dizi[sag].key) return h->dizi[sag].key;
	
	else
	{
		return -1;
	}
	
	
}

void yer_degistir(struct heap *h, int k) // Kitaptaki Soru
{
	int temp;
	int sol = (2*k+1);
	int sag = (2*k+2);
	
	if(h == NULL) return;
	if(h->eleman_sayisi == 0) return;
	
	if(h->dizi[sol].key < h->dizi[sag].key)
	{
		temp = h->dizi[k].key;
		h->dizi[k].key = h->dizi[sol].key;
		h->dizi[sol].key = temp;
	}
	
	if(h->dizi[sag].key < h->dizi[sol].key)
	{
		temp = h->dizi[k].key;
		h->dizi[k].key = h->dizi[sag].key;
		h->dizi[sag].key = temp;
	}
	
	
	
}

int verilen_eleman_derinlik(struct heap *h, int k) // Kitaptaki Soru
{
	int sayac = 1;
	int sol;
	int sag;
	int i = 1;
	int kontrol;
	
	
	if(h->dizi[i].key == h->dizi[k].key) return sayac;
	
	else
	{
		while(h->dizi[i].key != h->dizi[k].key)
		{
			
			sol = i*2+1;
			sag = i*2+2;
		
			if(h->dizi[sol].key == h->dizi[k].key || h->dizi[sag].key == h->dizi[k].key)
			{
				
				sayac++;
				return sayac;
			}
			
			
			else
			{
				sayac++;
				i = i+1;
			}
			
		}
		
		
	}
	
}

int yukselik(struct heap *h, int k) // Kitaptaki Soru
{
	int sayacSol = 0;
	int sayacSag = 0;
	int sol = 2*k+1;
	int sag = 2*k+2;
	
	if(sol > h->eleman_sayisi || sag > h->eleman_sayisi) return 0;
	
	while(sol < h->eleman_sayisi )
	{
		
		sol = 2*(sol)+1;
		sayacSol++;
	}
	
	while(sag < h->eleman_sayisi)
	{
		sayacSag++;
		sag = 2*(sag)+2;
	}
	printf("SAG %d \n",sayacSag);
	printf("SOL %d \n",sayacSol);
	if(sayacSag > sayacSol) return sayacSag;
	
	else return sayacSol;
}

void kapasiteyi_arttir(struct heap *h) // 2018 Final
{
	struct heap *heap2;
	int i=0;
	
	int a = (h->kapasite)*2;
	
	
	heap2 =(struct heap*)malloc(sizeof(struct heap));
	
	if(heap2 == NULL)
	{
		printf("Yer ayrilamadi.");
		exit(1);
	}
	
	heap2->dizi = (struct dugum*)malloc((a*2)*sizeof(struct dugum));
	
	if(heap2->kapasite == NULL)
	{
		printf("Yer ayrilamadi");
		exit(1);
	}
	
	heap2->kapasite = a;
	heap2->eleman_sayisi = 0;
	
	
	printf("ESKI HEAP KAPASITE -> %d \n",h->kapasite);
	
	
	for(i; i<h->eleman_sayisi; i++)
	{
		heap2->dizi[i].key = h->dizi[i].key;
	}
	
	free(h);
	h = heap2;

	printf("YENI HEAP KAPASITE -> %d \n",h->kapasite);
	
}


int main(int argc, char** argv) {

    struct heap *heap=heap_olustur(10);
    initialize_heap(heap,10,10);
    print_heap(heap);
    //printf("heap mi -> : %d\n",heapi_bozan_eleman(heap));
    
    
    heapify(heap);
    
    //printf("heap mi ->: %d\n",heapi_bozan_eleman(heap));
    //printf("heap mi: %d\n",heap_mi(heap));
    
    //print_heap(heap);
    
    //printf("Verilen elemanin deringili %d \n", verilen_eleman_derinlik(heap,9));
    //printf("YUKSEKLIK -> %d \n",yukselik(heap,6));
    
    //k_ninci_buyugu_getir(heap,9);

    //printf("%d \n",k_ninci_elemanin_buyuk_cocugu(heap,3));
    kapasiteyi_arttir(heap);
    //print_heap(heap);
    //yer_degistir(heap,3);
    
    print_heap(heap);
   
    
    
    
    
    return (EXIT_SUCCESS);
}
