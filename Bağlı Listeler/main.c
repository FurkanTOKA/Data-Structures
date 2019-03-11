#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

struct hucre{
    int icerik;
    struct hucre *sonraki;
};

struct hucre* hucre_olustur(int icerik){
    struct hucre *a;
    a=(struct hucre*)malloc(sizeof(struct hucre));
    if(a==NULL){
        printf("Heap alaninda yer ayrilamadi ...\n");
        exit(1);
    }
    a->icerik=icerik;
    a->sonraki=NULL;
}

void liste_basina_ekle(int icerik,struct hucre **liste_basi){
    struct hucre* a=hucre_olustur(icerik);
    a->sonraki=*liste_basi;
    *liste_basi=a;
}

void liste_sonuna_ekle(int icerik,struct hucre **liste_basi)
{
	struct hucre *eklenen = hucre_olustur(icerik);
	struct hucre *kontrol;
	kontrol = *liste_basi;
	
	if(*liste_basi == NULL)
	{
		eklenen->sonraki = *liste_basi;
		*liste_basi = eklenen;
	}
	
	else
	{
		while(kontrol->sonraki != NULL)
		{
			kontrol = kontrol->sonraki;
		}
		
		kontrol->sonraki = eklenen;
	}
    
}

void liste_yaz(struct hucre *liste_basi)
{
    while(liste_basi != NULL)
    {
    	printf("%4d", liste_basi->icerik);
    	liste_basi = liste_basi->sonraki;
	}
    printf("\n");
}

void liste_yaz_recursive(struct hucre *liste_basi)
{
    
    if(liste_basi != NULL)
    {
    	printf("%4d", liste_basi->icerik);
    	liste_yaz_recursive(liste_basi->sonraki);
	}
    
    
    else{ 
        printf("\n");
    }
}
void tersten_liste_yaz_recursive(struct hucre *liste_basi)
{
    
    if(liste_basi != NULL)
    {
    	tersten_liste_yaz_recursive(liste_basi->sonraki);
    	printf("%4d ",liste_basi->icerik);
	}
   
}
void liste_yok_et(struct hucre **liste_basi)
{
    struct hucre *silici;
    
    if(*liste_basi == NULL)
    {
    	printf("Liste zaten bos !");
	}
    
    while(*liste_basi != NULL)
    {
    	silici = *liste_basi;
    	*liste_basi = (*liste_basi)->sonraki;
    	free(silici);
	}
	free(*liste_basi);
	
	printf("Liste silinmistir...");
}

void liste_sirali_ekle(int icerik, struct hucre **liste_basi) // 2017 Vize
{
	struct hucre *a;
	struct hucre *b;
	struct hucre *eklenen = hucre_olustur(icerik);
	
	a = *liste_basi;
	b = *liste_basi;
	
	
	if(*liste_basi == NULL)
	{
		eklenen->sonraki = *liste_basi;
		
		*liste_basi = eklenen;
	}
	
	while(b != NULL && b->icerik < eklenen->icerik)
	{
		if(eklenen->icerik == b->icerik) return;
		a=b;
		b = b->sonraki;
	}
	
	if(b == *liste_basi)
	{
		eklenen->sonraki = *liste_basi;
		*liste_basi=eklenen; 
		
	}
	else
	{
		a->sonraki = eklenen;
		eklenen->sonraki = b;
		
	}
	
	
	
	
   
}

void liste_eleman_sil(int silinen, struct hucre **liste_basi)
{
	
	struct hucre *a;
	struct hucre *b;
	
	b = *liste_basi;
	
	if(*liste_basi == NULL) return;
	
	while(b != NULL && b->icerik != silinen)
	{
		a = b;
		b = b->sonraki;
	}
	
	if(b == *liste_basi)
	{
		*liste_basi = (*liste_basi)->sonraki;
		free(b);
	}
	else
	{
		a->sonraki = b->sonraki;
		free(b);
	}

    
        
}


void liste_sirala(struct hucre **liste_basi){
    struct hucre *a,*b,*c,*d;
    
    if(*liste_basi == NULL || (*liste_basi)->sonraki==NULL) return;
    
    d=(*liste_basi)->sonraki;
    (*liste_basi)->sonraki=NULL;
    
    while(d!=NULL){
        c=d;
        d=d->sonraki;
        b=*liste_basi;
        while(b!=NULL && b->icerik < c->icerik){
            a=b;
            b=b->sonraki;
        }
        if(b==*liste_basi){
            c->sonraki=*liste_basi;
            *liste_basi=c;
        }
        else {
            a->sonraki = c;
            c->sonraki = b;
        }
        }
}


 
void liste_ters_cevir(struct hucre **liste_basi){
    
    struct hucre *a,*b,*c;
    
    c = *liste_basi;
    a = NULL;
    
    while(c != NULL)
    {
    	
    	b = c;
    	c = c->sonraki;
    	
    	b->sonraki = a;
    	
    	a = b;

	}
	
	*liste_basi = a;
    
}


    
void sonu_bas_yap(struct hucre **liste_basi)  // 2016 Büt Sorusu
{
	struct hucre *a,*b,*c,*d;
	

	
	a = *liste_basi;
	b = *liste_basi;
	d = *liste_basi;
	
	d = d->sonraki;
	
	
	
	if(*liste_basi == NULL) return;
	if((*liste_basi)->sonraki == NULL) return;
	
	while(b->sonraki != NULL)
	{
		c = b;
		b = b->sonraki;
	}
	
	
	b->sonraki = d;
	c->sonraki = NULL;
	c->sonraki = a;
	a->sonraki = NULL;
	
	*liste_basi = b;
	
	
}  

 
int sirali_mi(struct hucre *liste_basi)  // 2016 Final Sorusu
{
	
	struct hucre *a,*b;
	
	a = liste_basi;
	b = liste_basi;
	
	if(liste_basi == NULL) return;
	if(liste_basi->sonraki == NULL) return;
	
	while(a->sonraki != NULL)
	{
		while(b->sonraki != NULL)
		{
			b = b->sonraki;
			if(a->icerik < b->icerik) return 0;
		}
		a = a->sonraki;
		b = a->sonraki;
	}
	
	return 1;
	
}


void en_kucuk_sil(struct hucre **liste_basi) // 2015 Final Sorusu
{

	struct hucre *enkucuk;
	struct hucre *a;
	struct hucre *b;
	struct hucre *c;
	struct hucre *d;
	
	if(*liste_basi == NULL) return;
	if((*liste_basi)->sonraki == NULL)
	{
		//free((*liste_basi)->icerik);
	}
	
	enkucuk = *liste_basi;
	a = (*liste_basi)->sonraki;
	
	while(a != NULL)
	{
		if(enkucuk->icerik < a->icerik)
		{
			a = a->sonraki;
		}
		
		else
		{
			enkucuk = a;
			a = a->sonraki;
		}
		
	}
	
	c = *liste_basi;
	
	
	while(c->icerik != enkucuk->icerik)
	{
		d = c;
		c = c->sonraki;
	}
	if(enkucuk == *liste_basi)
	{
		(*liste_basi) =(*liste_basi)->sonraki;
		free(enkucuk);
	}
	else
	{
		d->sonraki = c->sonraki;
		free(enkucuk);
	}
	
}



void cift_tek_sayisi(struct hucre *liste_basi) // 2015 Vize Sorusu
{
	int tek = 0;
	int cift = 0;
	
	struct hucre *kontrol;
	
	kontrol = liste_basi;
	
	if(liste_basi == NULL) return;
	
	while(kontrol != NULL)
	{
		if((kontrol->icerik) % 2 == 0)
		{
			cift++;
		}
		else
		{
			tek++;
		}
		kontrol = kontrol->sonraki;
	}
	
	printf("Ciftlerin sayisi : %d \n",cift);
	printf("Teklerin sayisi : %d \n",tek);
}

void ikinci_sil(struct hucre **liste_basi) // Kitaptaki Soru
{

	struct hucre *a;
	struct hucre *b;
	
	a = *liste_basi;
	
	
	if(*liste_basi == NULL) return;
	if((*liste_basi)->sonraki == NULL) return;
	
	else
	{
		b = a->sonraki;	
	}
	
	a->sonraki = b->sonraki;
	
	free(b);	
}

struct hucre * tek_numarali_ayir(struct hucre *liste_basi) // Kitaptaki Soru
{
	struct hucre *liste_basi2 = NULL;
	struct hucre *a;
	struct hucre *b;
	struct hucre *c;
	c = liste_basi2;
	
	a = liste_basi;
	int e_Sayisi = 0;
	
	int i = 1;
	
	while(a != NULL)
	{
		e_Sayisi++;
		a = a->sonraki;
	}
	a = liste_basi;
	
	while(i<e_Sayisi)
	{
		
		liste_sonuna_ekle(a->icerik, &liste_basi2);
		
		a = a->sonraki->sonraki;
		i = i+2;
		
	}
	if(i%2 != 0)
	{
		liste_sonuna_ekle(a->icerik, &liste_basi2);
	}
	
	return liste_basi2;
	
}

void sil_i(int i, struct hucre **liste_basi)  // Kitaptaki Soru
{
	struct hucre *a;
	struct hucre *b;
	
	int sayac;
	sayac = 1;
	
	a = *liste_basi;
	b = *liste_basi;
	
	
	while(sayac != i)
	{
		b = a;
		a = a->sonraki;
		
		sayac++;
	}
	if(sayac == 0) return;
	
	if(sayac == 1)
	{
		a = a->sonraki;
		*liste_basi = a;
		free(b);
	}
	else
	{
		b->sonraki = a->sonraki;
		free(a);
	}
	
	
	
	
}

void onundekini_sil(struct hucre **liste_basi, int x ) // Kitaptaki Soru
{
	struct hucre *a;
	struct hucre *b;
	
	a = *liste_basi;
	b = (*liste_basi)->sonraki;
	
	
	if(*liste_basi == NULL) return;
	
	if((*liste_basi)->sonraki == NULL) return;
	
	if(a->icerik == x)
	{
		a->sonraki = b->sonraki;
		free(b);
	}
	
	else
	{
		
		while(a->icerik != x)
		{
			a = b;
			b = b->sonraki;
		
			if(a->sonraki == NULL)
			{
				printf("Liste sonuna geldik, bu elemanin onunde eleman yoktur !");
			}
		}
		a->sonraki = b->sonraki;
		free(b);	
	}
	
	
	
	
	
}

void tasi(struct hucre **liste_basi, int eleman, int x) // Kitaptaki Soru
{
	struct hucre *a,*b,*c,*d,*e;
	int i;
	i = 1;
	int sayac;
	sayac = 1;
	int liste_uzunluk =1;
	
	a = *liste_basi;
	e = *liste_basi;
	
	
	if(*liste_basi == NULL) return;
	if((*liste_basi)->sonraki == NULL) return;
	
	// Listenin uzunluğunu buluyoruz.
	while(e->sonraki != NULL)
	{
		e = e->sonraki;            
		liste_uzunluk++;
	}
	
	// Taşınacak elemanın listenin kaçıncı elemanı olduğunu buluyoruz.
	while(a->icerik != eleman)
	{
		d = a;
		a = a->sonraki;
		sayac++;
	}
	
	// Taşınacak birim miktarı ve listenin kaçıncı elemanı olduğunu topluyoruz.
	int toplam = sayac + x;
	
	printf("TOPLAM -> %d \n",toplam);
	
	// Burada yapılan kontrol eğer bizden istenen elemanın taşınma miktarı listeden uzunsa hiç bir işlem yapmaması lazım.
	
	if(toplam > liste_uzunluk)
	{
		printf("Bu tasima islemi listeyi tasirmaktadir !! \n");
		
	}
	
	// Burada artık elemanı taşıma işlemi yapıyoruz.
	else
	{
		// Taşınacak eleman liste başındaki elemansa yapılacak taşıma işlemi
		if(a == *liste_basi)
		{
			b = a->sonraki;
			c = a;
			while(i <= x)
			{
				d = c;
				c = c->sonraki;
				i++;
			}
			d->sonraki = a;
			a->sonraki = c;
			
			*liste_basi = b;
			
		}
		
		// Taşınacak eleman listenin herhangi bir yerindeyse yapılacak taşıma işlemi
		else
		{
			
			b = a;
			c = a->sonraki;
	
			while(i <= x)
			{
				b = c;
				c = c->sonraki;
				i++;
			}
			d->sonraki = a->sonraki;
			b->sonraki = a;
			a->sonraki = c;
			
		}
		
		
		
	}
		
}

struct hucre *asal_carpanlar(int sayi) // Kitaptaki Soru
{
	struct hucre *asal = NULL;
	struct hucre *a;
	struct hucre *b;
	struct hucre *c;
	struct hucre *d;
	int i;
	
	for(i=2;sayi!=1;i++)
	{
		
		if(sayi%i==0){
			
			
			
			sayi/=i;
			
			liste_sonuna_ekle(i,&asal);
			
			i--;
		
		}
	}
	a = asal;
	b = a->sonraki;
	c = asal;
	d = b;
	

	
	while(a != NULL)
	{
		
		
		while(b->sonraki != NULL)
		{
			
			if(a->icerik == b->icerik)
			{
				printf("bura");
				c->sonraki = d->sonraki;
				free(d);
				b = b->sonraki;
				
			}
			else
			{
				
				
				printf("bura2");
				c = b;
				b = b->sonraki;
			}
		}
		b = a->sonraki;
		c = asal;
	}
	
	return asal;
	
	
}

struct hucre katlari_sil(struct hucre **liste_basi, int N) // Kitaptaki Soru
{
	
}

void kesisim(struct hucre *liste_basi, struct hucre *liste_basi2) // Kitaptaki Soru
{
	struct hucre *l1;
	struct hucre *l2;
	
	l1 = liste_basi;
	
	
	if(liste_basi == NULL || liste_basi2 == NULL) return;
	
	while(l1 != NULL)
	{
		l2 = liste_basi2;
		
		while(l2 != NULL)
		{
			if(l1->icerik == l2->icerik)
			{
				printf("%d \n",l2->icerik);
				break;
			}
			
				l2 = l2->sonraki;
			
		}
		l1 = l1->sonraki;
	}
		
}


int main(int argc, char** argv) {
   
    struct hucre *liste1=NULL;
    
    struct hucre *liste2=NULL;
    
    
     liste_sonuna_ekle(6,&liste1);
     liste_sonuna_ekle(7,&liste1);
     liste_sonuna_ekle(11,&liste1);
     liste_sonuna_ekle(12,&liste1);
     liste_sonuna_ekle(13,&liste1);
     liste_sonuna_ekle(14,&liste1);
     liste_sonuna_ekle(15,&liste1);
     liste_sonuna_ekle(1,&liste1);
     
     liste_sonuna_ekle(6,&liste2);
     liste_sonuna_ekle(7,&liste2);
     liste_sonuna_ekle(11,&liste2);
     liste_sonuna_ekle(12,&liste2);
     liste_sonuna_ekle(13,&liste2);
     liste_sonuna_ekle(14,&liste2);
     liste_sonuna_ekle(15,&liste2);
     liste_sonuna_ekle(1,&liste2);
     
     
     
     
     liste_yaz(liste1);
     liste_yaz(liste2);
     
     kesisim(liste1,liste2);
     
     //cift_tek_sayisi(liste1);
     
     //ikinci_sil(&liste1);
     
     
     //sil_i(6,&liste1);
     
     //onundekini_sil(&liste1,15);
     
     //tasi(&liste1,6,7);
     
     //liste_yaz(asal_carpanlar(42));
     
     //liste_yaz(liste1);
     
     //liste_yaz(tek_numarali_ayir(liste1));
     
     //liste_eleman_sil(12,&liste1);
     
     //liste_ters_cevir(&liste1);
     //liste_yaz(liste1);
     
     
     //sonu_bas_yap(&liste1);  
	 //en_kucuk_sil(&liste1);   
     //liste_yaz(liste1);
     
     //printf("%d ", sirali_mi(liste1));
     
     
     //liste_yaz_recursive(liste1);
     
     //tersten_liste_yaz_recursive(liste1);
     
     //liste_yok_et(&liste1);
     
     
     
     
     
     
     
    system("PAUSE");
    return (EXIT_SUCCESS);
}

