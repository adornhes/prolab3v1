#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct komsular
{
    int plaka_kodu2;
    struct komsular *next_komsu;
     char ksehir_adi[20];

} ;
typedef struct komsular *knode;   //komsular structini isaret eden pointer veri tipimiz
struct sehirler
{
    int komsu_say;
    int plaka_kodu;
    char sehir_adi[20];
    char bolge[2];
    struct sehirler *next_sehir;
    knode ilk_komsu;
};
typedef struct sehirler *node;    // sehirler structini isaret eden pointer veri tipimiz

node ilk=NULL;
node son=NULL;
node iter=NULL;
node iter2=NULL;
knode kson=NULL;
node gecici=NULL;
knode kgecici=NULL;
knode kiter=NULL;


node createNode()       //sehirler structi icin bellekte yer tahsis eden kod parcasi...
{
    node temp;
    temp = (node)malloc(sizeof(struct sehirler));
    temp->next_sehir=NULL;
    return temp;
}
knode createKNode()       // komsu sehirler structi icin bellekte yer tahsis eden kod parcasi...
{
    knode temp;
    temp=(knode)malloc(sizeof(struct komsular));
    temp->next_komsu=NULL;
    return temp;
}
void fileread1(FILE *p)
{
    char trash[100];
    char buffer[150];
    p=fopen("sehirler.txt","r");
    char sub[20];
    char sub2[3];
    int sub3;
    while(feof(p)==0)
    {
        if(ilk!=NULL)
        {
            gecici=createNode();
            if(gecici==NULL)
            {
                printf("\nbellek tahsis edilemedi...");
                break;
            }
            fgets(buffer,sizeof(buffer),p);
            sscanf(buffer,"%d,%[^,],%[^,]",&sub3,&sub,&sub2);
            // printf("\nplaka:%d  ad:%s  bolge:%s\n",sub3,sub,sub2);
            strcpy(gecici->sehir_adi,sub);
            strcpy(gecici->bolge,sub2);
            gecici->plaka_kodu=sub3;
            sub[2]="";
            sub3=0;
            sub2[20]="";
            buffer[150]="";   //trashleri temizledik..
            son->next_sehir=gecici;
            son=gecici;
        }
        if(ilk==NULL)
        {
            ilk=createNode();
            fgets(buffer,sizeof(buffer),p);
            sscanf(buffer,"%d,%[^,],%[^,]",&sub3,&sub,&sub2);
            //  printf("plaka:%d  ad:%s  bolge:%s\n",sub3,sub,sub2);
            strcpy(ilk->sehir_adi,sub);
            strcpy(ilk->bolge,sub2);
            ilk->plaka_kodu=sub3;
            sub[2]="";
            sub2[20]="";
            sub3=0;
            buffer[150]="";
            ilk->next_sehir;
            son=ilk;
        }
    }
    fclose(p);
}
void fileread2(FILE *p)
{
    int trash,ksayac=0;
    char trash1[15],trash2[2],buffer[150],subbuffer[150];
    p=fopen("sehirler.txt","r");
    iter=ilk;
    char *delimiter;
    int temp; // sort icin gerekli degisken.Dongu icinde tekrar tanimlanmasina gerek yoktur..
    while(feof(p)==0)
    {
        fgets(buffer,150,p);      //dosyadan bir satir okuduk...
        sscanf(buffer,"%d,%[^,],%[^,],%[^\n]",&trash,&trash1,&trash2,&subbuffer);// satiri veri yapimiz icin uygun formata getirdik..
        trash2[2]="";                                                             //subbuffer bizim icin gerekli veriyi gecici olarak saklar...
        trash1[15]="";
        buffer[150]="";  //trashleri temizledik

        delimiter=strtok(subbuffer,",");
        while(delimiter!=NULL)
        {
            iter2=ilk;                     //komsu sehirlerin plakalarini bulmak icin her komsu sehir eklendiginde ana dugumun ilk sehrine donen pointer...
            if(iter->ilk_komsu==NULL)
            {
                iter->ilk_komsu=createKNode();
                if(iter->ilk_komsu==NULL)              //ilk_komsu icin node olusturduktan sonra ikinci NULL mu kontrolunu yaptik..
                {
                    printf("\n ilk kgecici icin bellek tahsis edilemedi...\n");
                    break;
                }
                 strcpy(iter->ilk_komsu->ksehir_adi,delimiter);
                kson=iter->ilk_komsu;
                kson->next_komsu=NULL;
                while(1)                                                 //komsu sehilerin plakalarini bulan dongu..
                {
                    if(strcmp(delimiter,iter2->sehir_adi)==0)    //komsu sehir dugumlerini ana dugumler ile karsilastiran if-else..
                    {
                        kson->plaka_kodu2=iter2->plaka_kodu;    //match yakalanirsa ana dugumde ki plaka kodu komsu ilgili komsu node a tasinir..
                        break;
                    }
                    else
                    {
                        iter2=iter2->next_sehir;                 //sehir isimleri math olmassa ana dugum ilerler..
                    }
                }
            }
            else
            {
                kgecici=createKNode();
                if(kgecici==NULL)
                {
                    printf("\nkgecici ye bellek tahsis edilemedi...\n");
                    break;
                }
                  strcpy(kgecici->ksehir_adi,delimiter);
                kson->next_komsu=kgecici;
                kson=kgecici;
                kgecici=NULL;
                while(1)
                {
                    if(strcmp(delimiter,iter2->sehir_adi)==0 )     //komsu sehir dugumlerini ana dugumler ile karsilastiran if-else..
                    {
                        kson->plaka_kodu2=iter2->plaka_kodu;    //match yakalanirsa ana dugumde ki plaka kodu komsu ilgili komsu node a tasinir..
                        break;
                    }
                    else
                    {
                        iter2=iter2->next_sehir;                 //sehir isimleri math olmassa ana dugum ilerler..
                    }
                }
            }
            delimiter=strtok(NULL,",");
            ksayac++;
        }
        iter->komsu_say=ksayac;
        ksayac=0;
        knode knode1= iter->ilk_komsu;     //sort icin gerekli yardimci degiskenler olusturuluyor...
        knode knode2=NULL;
        for(knode1; knode1!=NULL; knode1=knode1->next_komsu)         //bubble sort ile komsularin plaka kodlari siralandi...
        {
            for(knode2=knode1->next_komsu; knode2!=NULL; knode2=knode2->next_komsu)
            {
                if(knode1->plaka_kodu2>knode2->plaka_kodu2)
                {
                    temp=knode1->plaka_kodu2;
                    knode1->plaka_kodu2=knode2->plaka_kodu2;
                    knode2->plaka_kodu2=temp;
                }
            }
        }
        iter=iter->next_sehir;
    }
    fclose(p);
}


int main()
{
    FILE *p;
    fileread1(p);
    fileread2(p);


    iter=ilk;

    while(1)
    {
        kiter=iter->ilk_komsu;
        printf("\n%d %s %s komsu sayisi:%d      ",iter->plaka_kodu,iter->sehir_adi,iter->bolge,iter->komsu_say);
        while(kiter!=NULL)
        {
            printf(" %d ",kiter->plaka_kodu2);
            kiter=kiter->next_komsu;
        }
        iter=iter->next_sehir;
        if(iter==NULL)
            break;

    }
    return 0;
}









