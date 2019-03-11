#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


struct dugum {
    int eleman;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_agac{
    struct dugum *kok;
};

struct dugum* dugum_olustur(int eleman){
    struct dugum *d;
    d=(struct dugum*)malloc(sizeof(struct dugum));
    d->eleman=eleman;
    d->sol=d->sag=NULL;
    return d;
}

void ikili_agac_olustur(struct ikili_agac **agac){
    *agac=(struct ikili_agac*)malloc(sizeof(struct ikili_agac));
    (*agac)->kok=NULL;
}

void ikili_agac_eleman_ekle(struct ikili_agac *agac, int eleman){
    struct dugum *dugum;
    struct dugum *d;
    struct dugum *geri;
    
    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(eleman < d->eleman) d=d->sol;
        else if(eleman > d->eleman) d=d->sag;
        else return; // eleaman tekrari yok
    }
    
    dugum=dugum_olustur(eleman);
    if(agac->kok==NULL){
        agac->kok=dugum;
        return;
    }
    if(eleman<geri->eleman) geri->sol=dugum;
    else geri->sag=dugum;    
}

void ikili_agac_eleman_sil(struct ikili_agac *agac, int silinen){
    struct dugum *d=agac->kok;
    struct dugum *parent=NULL;
    struct dugum *d1,*d2;;
    int sol_sag;  // 0 sol, 1 sag
    while(d!=NULL){     
        if(silinen < d->eleman)   { parent=d; d=d->sol; sol_sag=0;}
        else if(silinen > d->eleman) { parent=d; d=d->sag; sol_sag=1;}
        else break;
    }
    if(d==NULL) return; //eleman agacta yok!
    
    if(d->sol==NULL){ // silinen dugumun solu bos
        if(d==agac->kok) agac->kok=d->sag;
        else {
            if(sol_sag==0) parent->sol=d->sag;
            else parent->sag =d->sag;
        }   
    }
    else if(d->sag==NULL){ // silinen dugumun sagi bos
        if(d==agac->kok)agac->kok=d->sol;
        else {
            if(sol_sag==0) parent->sol=d->sol;
            else parent->sag=d->sol;
        }       
    }
    else { // silinen dugumun hem sagi hem de solu dolu
        d1=d->sol;
        while(d1->sag!=NULL) d1=d1->sag;
        if(d1!=d->sol){
            d2=d->sol;
            while(d2->sag!=d1) d2=d2->sag;
            d2->sag=d1->sol;
            d1->sol=d->sol;
            
        }
        d1->sag=d->sag;
        if(parent!=NULL){
              if(sol_sag==0) parent->sol=d1;
              else parent->sag=d1; 
        } 
        else { // kok degisti
              if(d1==d->sol) agac->kok=d->sol;
              else agac->kok=d1; 
        }          
    } 
    free(d);
}


struct dugum* minValueNode(struct dugum *node){
    struct dugum *current = node;
    if(node==NULL) return node;
    while(current->sol!=NULL) current=current->sol;
    return current;
}

struct dugum *deleteDugum(struct dugum *root, int key){
    if(root==NULL) return root;
    if(key < root->eleman) root->sol=deleteDugum(root->sol,key);  
    else if(key > root->eleman) root->sag=deleteDugum(root->sag,key);
    else {
        // note with only one child or no child 
        if(root->sol == NULL || root->sag == NULL) {
            struct dugum *temp= root->sol ? root->sol : root->sag;
            
         //   if(root->sol!=NULL) temp=root->sol;
         //   else temp=root->sag;
            
            if(temp== NULL ){ // no child
                temp = root;
                root = NULL;
                
            }
            else { // single child
                root->eleman = temp->eleman;
                root->sol = temp->sol;
                root->sag = temp->sag;
            }
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct dugum *temp= minValueNode(root->sag);
            // copy the inorder succeror's data to this node
            
            
            root->eleman = temp->eleman;
            root->sag= deleteDugum(root->sag, temp->eleman);   
        }    
    }
    return root;
}




void inorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    inorder_yaz(kok->sol);
    printf("%3d ",kok->eleman);
    inorder_yaz(kok->sag);
    
}

void preorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    printf("%3d ",kok->eleman);
    preorder_yaz(kok->sol);
    preorder_yaz(kok->sag);
    
}

void postorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    
    postorder_yaz(kok->sol);
    postorder_yaz(kok->sag);
    printf("%3d ",kok->eleman);
    
}

int dolu_dugum_sayisi(struct dugum* kok) // Kitaptaki Soru, aðacýn hem sað cocugu hem de sol cocugu olacak.
{
	
	if(kok == NULL) return 0;
	
	
	else
	{
		if(kok->sol != NULL && kok->sag != NULL) return dolu_dugum_sayisi(kok->sol) + dolu_dugum_sayisi(kok->sag) + 1;
		
	}
	
	
}

int tek_dugum(struct dugum* kok) // Kitaptaki Soru, aðacýn düðümlerinde tek eleman barýndýran düðüm sayýsý
{
	if(kok == NULL) return 0;
	
	if(kok->eleman%2 == 0) return tek_dugum(kok->sol) + tek_dugum(kok->sag);
	
	else
	{
		if(kok->eleman%2 != 0 ) return tek_dugum(kok->sol) + tek_dugum(kok->sag) + 1;
	}
}

int kucuk_X(struct dugum* kok, int x)  // Kitaptaki Soru, verilen bir X deðerinden aðaçtaki küçük olan düðümlerin sayýsý
{
	
	
	if(kok == NULL) return 0;
	
	if(kok->eleman > x) return kucuk_X(kok->sol,x) + kucuk_X(kok->sag,x);
	
	else
	{
		return kucuk_X(kok->sol,x) + kucuk_X(kok->sag,x) + 1 ; 
	}
	
	
}

int agac_Topla(struct dugum* kok)  // Kitaptaki Soru, aðacýn tüm düðümlerinin toplamý
{
	int toplam = 0;
	
	if(kok == NULL) return 0;
	
	if(kok->sol != NULL || kok->sag != NULL) return agac_Topla(kok->sol) + agac_Topla(kok->sag) + kok->eleman + toplam;
	
	if(kok->sol == NULL && kok->sag  == NULL) return agac_Topla(kok->sol) + agac_Topla(kok->sag) + kok->eleman + toplam;
	
}



int derinlik(struct dugum* kok) // Kitaptaki Soru, aðacýn derinliðini bulur
{
	if(kok == NULL)
	{
		return -1;
	}
	
	else
	{
		int solDerinlik = derinlik(kok->sol);
		int sagDerinlik = derinlik(kok->sag);
		
		if(solDerinlik >sagDerinlik)
		{
			return (solDerinlik+1);
			
		}
		else
		{
			return (sagDerinlik+1);
		}
	}	
}

void aralik_yaz(struct dugum* kok, int a1, int a2)
{
	

}

int toplam_derinlik(struct dugum* kok) // Kitaptaki Soru, aðactaki tüm düðümlerin derinliklerinin toplamýný bulur.
{
	if(kok == NULL) return 1;
	
	else
	{
		int solDerinlik = derinlik(kok->sol);
		int sagDerinlik = derinlik(kok->sag);
		
		if(solDerinlik > sagDerinlik)
		{
			solDerinlik = solDerinlik + 1;
			return toplam_derinlik(kok->sol) + solDerinlik;
		}
		
	
		else
		{
			sagDerinlik = sagDerinlik + 1;
			return toplam_derinlik(kok->sag) + sagDerinlik;
		}
		
		
	}
			
}

int kardes_mi(struct dugum *kok, struct dugum *dugum1, struct dugum *dugum2) // 2017 Vize, 2016 Büt
{
	if(kok->sol == NULL || kok->sag == NULL) return 0;
	
	if ((kok->sag == dugum1 && kok->sol == dugum2) || (kok->sol==dugum1 && kok->sag == dugum2)) return 1;
	
	
	if(dugum1->eleman > kok->eleman) kardes_mi(kok->sag,dugum1,dugum2);
	
	else
	{
		kardes_mi(kok->sol,dugum1,dugum2);
	}

}

int ic_dugum_sayisi(struct dugum *kok) // 2015 Final
{
	if(kok == NULL) return 0;
	
	if(kok->sol == NULL && kok->sag == NULL) return 0;
	
	if(kok->sol != NULL || kok->sag != NULL)
	{
		return ic_dugum_sayisi(kok->sol) +  ic_dugum_sayisi(kok->sag) +1;
	}
	
	
}

int koke_uzaklik(struct dugum *kok, struct dugum *a) // 2015 Vize
{
	
	if(kok == a) return 0;
	
	
	
	if(kok->eleman > a->eleman)
	{
		
		return koke_uzaklik(kok->sol,a) + 1;
		
	}
	
	else
	{

		return koke_uzaklik(kok->sag,a) + 1;
		
	}
	
	
}


int ikili_mi(struct dugum *kok) // 2016 But
{
	if(kok == NULL) return 1;
	
	if(kok->sol != NULL && kok->eleman < (kok->sol)->eleman || kok->sag != NULL && kok->eleman > (kok->sag)->eleman) return 0;

	else
	{
		ikili_mi(kok->sol);
		ikili_mi(kok->sag);
	}
}

struct dugum* kardes_bul(struct dugum *kok, struct dugum* a) // 2016 Final
{
	if(kok == NULL) return NULL;
	
	if(kok->eleman == a->eleman) return NULL;
	
	struct dugum* kontrol;
	struct dugum* c;
	kontrol = kok;
	
	
	while(kontrol->eleman != a->eleman)
	{
		if(kontrol->eleman > a->eleman)
		{
			c = kontrol;
			kontrol = kontrol->sol;
			if(kontrol->eleman == a->eleman)
			{
				if(c->sag != NULL)
				{
					return (c->sag)->eleman;	
				}
				else return NULL;
				
			}
		}
		else
		{
			c = kontrol;
			kontrol = kontrol->sag;
			if(kontrol->eleman == a->eleman)
			{
				if(c->sol != NULL)
				{
					return (c->sol)->eleman;
				}
				else return NULL;
				
			}
		}
	}
	
}


struct dugum* dede_bul(struct dugum* kok, struct dugum *a) // 2018 Final
{
	if(kok == NULL) return NULL;
	
	if(kok->sol == NULL || kok->sag == NULL) return NULL;
	
	if((kok->sol->sol == NULL && kok->sol->sag == NULL) && (kok->sag->sag == NULL && kok->sag->sol == NULL)) return NULL;
	
	struct dugum *kontrol = kok;
	struct dugum *dede = kok;
	struct dugum *baba;
	int sayac = 0;
	
	kontrol = kok;
	
	while(kontrol->eleman != a->eleman)
	{
		if(kontrol->eleman > a->eleman)
		{
			baba = kontrol;
			kontrol = kontrol->sol;
			sayac++;
			if(sayac > 2)
			{
				dede = dede->sol;
			}
			
		}
		else
		{
			baba = kontrol;
			kontrol = kontrol->sag;
			sayac++;
			if(sayac > 2)
			{
				dede = dede->sag;
			}
		}
		
	}
	
	if(sayac == 1) return NULL;
	else
	{
		return dede->eleman;
	}
	
}

int yaprak_sayisi(struct dugum *kok)
{
	
	if(kok == NULL) return 0;
	
	if(kok->sol != NULL || kok->sag != NULL) return yaprak_sayisi(kok->sol) + yaprak_sayisi(kok->sag);
	
	else return 1;
	
	
	

	
}

int main(int argc, char** argv) {
    struct ikili_agac *agac;
    
    struct dugum *deneme = dugum_olustur(50);
    
    //struct ikili_agac *agac1=ikili_agac_olustur1();
    ikili_agac_olustur(&agac);   
    ikili_agac_eleman_ekle(agac, 80);  
    ikili_agac_eleman_ekle(agac, 70);
    ikili_agac_eleman_ekle(agac, 110);
    ikili_agac_eleman_ekle(agac, 60);
    ikili_agac_eleman_ekle(agac, 75);
    ikili_agac_eleman_ekle(agac, 50);
    ikili_agac_eleman_ekle(agac, 100);
    ikili_agac_eleman_ekle(agac, 240);
    ikili_agac_eleman_ekle(agac, 30);
    ikili_agac_eleman_ekle(agac, 105);
    ikili_agac_eleman_ekle(agac,65);
    ikili_agac_eleman_ekle(agac,90);
    
   
    
    inorder_yaz(agac->kok);
    printf("\n");
    
    
    
    
    printf("Agactaki dolu dugum sayisi          -> %d \n", dolu_dugum_sayisi(agac->kok));
    printf("Agactaki tek elemanli dugum sayisi  -> %d \n", tek_dugum(agac->kok));
    printf("Agactaki 200'den kucuk dugum sayisi -> %d \n", kucuk_X(agac->kok,200));
    printf("Agactaki tum dugumlerin toplami     -> %d \n", agac_Topla(agac->kok));
    printf("Agacin derinligi                    -> %d \n", derinlik(agac->kok));
    printf("Agacin toplam derinligi             -> %d \n", toplam_derinlik(agac->kok));
    printf("Verilen dugumler kardes mi          -> %d \n", kardes_mi(agac->kok, (agac->kok)->sol,((agac->kok)->sag)->sol));
    printf("Agacin toplam ic dugum sayisi       -> %d \n", ic_dugum_sayisi(agac->kok));
    printf("Verilen dugumun koke olan uzakligi  -> %d \n", koke_uzaklik(agac->kok,agac->kok->sol->sol->sol));
    printf("Verilen dugumun kardesi             -> %d \n", kardes_bul(agac->kok,agac->kok->sol->sol));
    printf("Verilen dugumun dedesi              -> %d \n", dede_bul(agac->kok,agac->kok->sol->sol->sol->sol));
    printf("Verilen agacin yaprak sayisi        -> %d \n", yaprak_sayisi(agac->kok));
    
    
    

    //printf("Agac, ikili arama agaci mi          -> %d \n", ikili_mi(agac->kok));
    
   // aralik_yaz(agac,30,100);
    
    
    
    
   
    
    printf("\n");
    
    
   
    
    //  ikili_agac_eleman_sil(agac, 100);
  //    inorder_yaz(agac->kok);
  //    printf("\n");
    
    //printf("Dugum Sayisi: %d\n",dugum_sayisi(agac->kok));
    
    
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}
