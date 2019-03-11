#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 
 */

struct CELL {
    char *anahtar;
    struct CELL *next;
};
int lookup(char *anahtar, struct CELL *l){
    if(l==NULL) return 0;
    else if(!strcmp(anahtar,l->anahtar)) return 1;
    else return lookup(anahtar,l->next);
}

int insert(char *anahtar, struct CELL **l){
    if(*l==NULL){
        *l=(struct CELL*)malloc(sizeof(struct CELL));
        (*l)->anahtar=(char*)malloc((strlen(anahtar)+1)*sizeof(char));
        strcpy((*l)->anahtar,anahtar);
        (*l)->next=NULL;
        return 1;
    }
    else if(strcmp(anahtar,(*l)->anahtar)) 
        return insert(anahtar, &((*l)->next));
    else return 0;
}

void print_list(struct CELL *l){
    if(l!=NULL){
        printf("%s ", l->anahtar);
        print_list(l->next);
    }
    
}


struct table_node{
    int counter;
    struct CELL *header;
};

struct hash_tablosu{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

unsigned hash(char *anahtar, int multiplier, int table_size){
    int i=0;
    unsigned int value=0;
    while(anahtar[i]){
        value = (anahtar[i]+multiplier*value)% table_size;
        i++;
    }
    return value;
}

void initialize_hash_table(struct hash_tablosu **hash_table, 
        int multiplier, int table_size){
    int i;
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   if(*hash_table==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
   }    
    (*hash_table)->tablo_basi=
       (struct table_node *)malloc(table_size*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
    }
    (*hash_table)->tablo_uzunlugu= table_size;
    (*hash_table)->multiplier= multiplier;
    
    for(i=0; i<table_size; i++){
        ((*hash_table)->tablo_basi+i)->counter = 0;
        ((*hash_table)->tablo_basi+i)->header = NULL;
    }
}

void insert_hash_table(struct hash_tablosu *hash_table,
        char *anahtar){
    int hash_index = hash(anahtar, hash_table->multiplier,
            hash_table->tablo_uzunlugu);
    if(insert(anahtar,&((hash_table->tablo_basi +hash_index)->header)))
     (hash_table->tablo_basi +hash_index)->counter++;
}

void print_hash_table(struct hash_tablosu *hash_table){
    if(hash_table){
        int index;
        printf("----- HASH TABLOSU -----\n");
        for(index=0; index<hash_table->tablo_uzunlugu; index++){
            printf("%5d : (%2d) ",index,(hash_table->tablo_basi +index)->counter);
            print_list((hash_table->tablo_basi+index)->header);
            printf("\n");
        }
    }
    else printf("Hash Tablosu Bos ...\n"); 
    
}

int delete_dugum_liste(struct CELL **header,char *anahtar){
    struct CELL *simdiki,*onceki;
    simdiki=*header;
    while(simdiki && strcmp(simdiki->anahtar,anahtar)){
        onceki=simdiki;
        simdiki=simdiki->next;
    }
    if(!simdiki) return 0;
    if(simdiki==*header){
        *header=(*header)->next;
    }else {
        onceki->next=simdiki->next;
    }
    free(simdiki->anahtar);
    free(simdiki);
    return 1;
}

void delete_hash_table(struct hash_tablosu *table, char *anahtar){
    int hash_index= hash(anahtar,table->multiplier, table->tablo_uzunlugu);
    if(delete_dugum_liste(&((table->tablo_basi +hash_index)->header),anahtar))
    (table->tablo_basi+hash_index)->counter--; 
}

void liste_yok_et(struct CELL **liste_basi){
    struct CELL *onceki;
    while(*liste_basi){
        onceki=*liste_basi;
        *liste_basi=(*liste_basi)->next;
        free(onceki->anahtar);
        free(onceki);
    }
}

void hash_table_yok_et(struct hash_tablosu **hash_table){
    int index;
    if(*hash_table){
        for(index=0; index < (*hash_table)->tablo_uzunlugu; index++)
            liste_yok_et(&((*hash_table)->tablo_basi+index)->header);
        free((*hash_table)->tablo_basi);
        free(*hash_table);
    }
    *hash_table=NULL;
    
}

void hash_table_buyut(struct hash_tablosu **htable,
          int multiplier, int tablo_uzunlugu){
    int i;
    struct CELL *liste_basi;
    struct hash_tablosu *yeni_tablo;
    
    if(*htable){
    initialize_hash_table(&yeni_tablo, multiplier, tablo_uzunlugu);
    for(i=0; i<(*htable)->tablo_uzunlugu; i++){
        liste_basi=((*htable)->tablo_basi+i)->header;
        while(liste_basi!=NULL){
            insert_hash_table(yeni_tablo,liste_basi->anahtar);
            liste_basi=liste_basi->next;
        }
    }
    hash_table_yok_et(htable);
    *htable=yeni_tablo;
    }   
}

struct CELL *eleman_ara(struct hash_tablosu* h1, char *eleman) // Kitaptaki soru
{
	
	struct CELL *ara;
	
	int x = hash(eleman,3,5);
	int sayac = 1;
	
	if(h1->tablo_uzunlugu == 0) return 0;
	
	
	ara = (h1->tablo_basi+x)->header;
	
	if((h1->tablo_basi+x)->header == NULL) return 0;
	
	while(ara != NULL)
	{
		
		
		if(!strcmp(ara->anahtar,eleman))
		{
			
			printf("Aradiginiz eleman Hash Tablosunda mecvuttur. Hash tablosunda %d. sirasinin %d. elemanidir.",x,sayac);
			return ara;
			
		}
		
		else
		{
			ara = ara->next;
			sayac++;
		}
		
	}
	
	if(ara == NULL)
	{
		printf("Aradiginiz eleman Hash Tablosunda yoktur !");
		return NULL;
		
	}

}

void en_buyuk_elemani_bul(struct hash_tablosu* h1)  // Kitaptaki soru
{
	struct CELL *liste_basi;
	struct CELL *a;
	
	char buyuk[] = "0";
	int i =0;
	int j =0;
	
	
	
	for(i; i<h1->tablo_uzunlugu;i++)
	{
		
		liste_basi = (h1->tablo_basi+i)->header;
		if(liste_basi == NULL) continue;
		
		a = liste_basi;
		
		for(j=0; j<(h1->tablo_basi+i)->counter; j++)
		{
			if(strcmp(buyuk,a->anahtar)<0)
			{
				strcpy(buyuk,a->anahtar);
			}
			
			a=a->next;
			
		}
	}
	int k=0;
	
	printf("Tablodaki en buyuk eleman -> ");
	
	while(buyuk[k] != '\0')
	{
		printf("%c",buyuk[k]);
		k++;
		
	}
	printf("\n");
	
	
}

float yukleme_orani(struct hash_tablosu* h1) // Kitaptaki Soru
{
	int toplam_eleman = 0;
	
	int i=0;
	
	for(i; i<h1->tablo_uzunlugu; i++)
	{
		toplam_eleman = toplam_eleman + (h1->tablo_basi+i)->counter;
	}
	printf("Tabloda saklanan veri sayisi -> %d \n", toplam_eleman);
	
	float s_o = toplam_eleman/(h1->tablo_uzunlugu);
	return s_o;
}

int en_kucuk_hash_degeri(struct hash_tablosu* h1) // 2017 Final
{
	struct CELL *liste_basi;
	struct CELL *a;
	
	char en_kucuk[] = "~";
	
	int i = 0;
	int j = 0;
	
	
	for(i; i<h1->tablo_uzunlugu; i++)
	{
		liste_basi = (h1->tablo_basi+i)->header;
		a = liste_basi;
		
		for(j; j<(h1->tablo_basi+i)->counter; j++)
		{
			if(strcmp(en_kucuk,a->anahtar)>0)
			{
				strcpy(en_kucuk,a->anahtar);
			}
			a = a->next;
		}
	}
	int hashDegeri = hash(en_kucuk,h1->multiplier,h1->tablo_uzunlugu);
	
	int k =0;
	
	printf("Tablodaki en kucuk eleman -> ");
	
	
	while(en_kucuk[k] != '\0')
	{
		printf("%c",en_kucuk[k]);
		k++;
	}
	
	printf("\n");
	
	return hashDegeri;
	
}

int ayni_mi(struct hash_tablosu *h1, struct hash_tablosu *h2) // 2015 Final
{
	struct CELL *liste_basi;
	struct CELL *liste_basi2;
	int kontrol;
	int i;
	int j;
	//int i =0;
	
	if(h1->tablo_uzunlugu != h2->tablo_uzunlugu) return 0;
	
	
	for(i=0; i<h1->tablo_uzunlugu; i++)
	{
		if((h1->tablo_basi+i)->counter == (h2->tablo_basi+i)->counter) continue;
		
		else return 0;
	}
	
	for(i=0; i<h1->tablo_uzunlugu; i++)
	{
		
		liste_basi = (h1->tablo_basi+i)->header;
		liste_basi2 = (h2->tablo_basi+i)->header;
		
		if(liste_basi == NULL && liste_basi2 == NULL)
		{
			
			kontrol = 1;
			continue;
		}
		
		else
		{
			for(j=0; j<(h1->tablo_basi+i)->counter; j++)
			{
				
			
				if(!strcmp(liste_basi->anahtar,liste_basi2->anahtar))
				{
					
					kontrol = 1;
					liste_basi = liste_basi->next;
					liste_basi2 = liste_basi2->next;
					continue;
				}
				else
				{
					kontrol = 0;
					break;
				}
			}
			if(kontrol == 0) break;
		}
		
	}
	
	
	if(kontrol == 1)
	{
		
		return 1;
	}
	else
	{
		return 0;
		
	}
	
}

void verilen_elemani_sil(struct hash_tablosu* h1, char *eleman)  // 2016 Büt
{
	struct CELL *liste_basi;
	struct CELL *a;
	struct CELL *b;
	
	int kontrol;
	
	if(h1->tablo_uzunlugu == 0 )
	{
		printf("TABLO YOK !");
		return;
	}
		
	int t_yeri = hash(eleman, h1->multiplier,h1->tablo_uzunlugu);
		
	if((h1->tablo_basi+t_yeri)->counter == 0)
	{
			
		printf("Aradiginiz elemanin listesi bostur !");
		return;
	}
	
	liste_basi = (h1->tablo_basi+t_yeri)->header;
	a = liste_basi;
	while(a != NULL)
	{
		if(!strcmp(a->anahtar,eleman))
		{
			if(a == liste_basi)
			{
				kontrol = 1;
				(h1->tablo_basi+t_yeri)->header = ((h1->tablo_basi+t_yeri)->header)->next;
				free(a);
				break;
			}
			else
			{
				kontrol = 1;
				b->next = a->next;
				free(a);
				break;
			}
		}
		
		else
		{
			kontrol = 0;
			b = a;
			a = a->next;
		}
	}	
	
	if(kontrol == 1)
	{
		printf("Istediginiz eleman silinmistir !\n");
	}
	else
	{
		printf("Istediginiz eleman tabloda ve listede yoktur ! \n");
	}
		

}

int yeni_hash(char *tc, int onun_kuvveti) // 2016 Final
{
	if(tc[11] != '\0') return -1;
	
	int sonuc = 0;
	int i = 0;
	
	for(i; i<onun_kuvveti; i++)
	{
		char simdiki = tc[10-i];
		
		int simdiki_int = simdiki - '0';
		
		sonuc = (sonuc*10) + simdiki_int;
	}
	return sonuc;
}

int main(int argc, char** argv) {
    struct hash_tablosu *htable=NULL;
    
    
    
    initialize_hash_table(&htable,3,5);
    
    
    insert_hash_table(htable,"Trabzonspor");
    insert_hash_table(htable,"kadayif");
    insert_hash_table(htable,"gundogdu");
    insert_hash_table(htable,"besiktas");
    insert_hash_table(htable,"baklava");
    insert_hash_table(htable,"dembaba");
    insert_hash_table(htable,"cardoza");
    insert_hash_table(htable,"furkan");
    insert_hash_table(htable,"MARIO GOMEZ");


    
    
    print_hash_table(htable);
    
    printf("Tablonun saklama orani -> %f \n",yukleme_orani(htable));
    
    en_buyuk_elemani_bul(htable);
    

    printf("Tablonun en kucuk elemaninin HASH degeri -> %d \n",en_kucuk_hash_degeri(htable));
    
    verilen_elemani_sil(htable,"kadayif");
    print_hash_table(htable);
    
    struct hash_tablosu *htable2 = NULL;
    
    initialize_hash_table(&htable2,3,5);
    
    insert_hash_table(htable2,"Trabzonspor");
    insert_hash_table(htable2,"kadayif");
    insert_hash_table(htable2,"gundogdu");
    insert_hash_table(htable2,"besiktas");
    insert_hash_table(htable2,"baklava");
    insert_hash_table(htable2,"dembaba");
    insert_hash_table(htable2,"cardoza");
    insert_hash_table(htable2,"furkan");
    
    print_hash_table(htable2);
    
    
    
    printf("Karsilastirilan Hash Tablolalari ayni mi ? -> %d \n",ayni_mi(htable,htable2));
    
    
    
    //eleman_ara(htable,"gundogdu");
   
    
   
    
    
    
    
   
    
    
    return (EXIT_SUCCESS);
}
