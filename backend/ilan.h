#ifndef ILAN_H
#define ILAN_H

#include "basvuru_heap.h"

#define ILAN_TABLO_BOYUT 101

typedef struct {
    int      ilan_no;
    char     baslik[150];
    char     aciklama[500];
    char     pozisyon[100];
    int      dolu;           /* 0=bos, 1=dolu, 2=silinmis (open addressing tombstone) */
    BasvuruMaxHeap* basvurular;
} Ilan;

typedef struct {
    Ilan     tablo[ILAN_TABLO_BOYUT];
    int      eleman_sayisi;
} IlanHashTable;

IlanHashTable* ilan_tablo_olustur();
int  ilan_ekle(IlanHashTable* ht, int ilan_no, const char* baslik,
               const char* aciklama, const char* pozisyon);
Ilan* ilan_ara(IlanHashTable* ht, int ilan_no);
int  ilan_sil(IlanHashTable* ht, int ilan_no);
int  ilan_guncelle(IlanHashTable* ht, int ilan_no, const char* yeni_baslik,
                   const char* yeni_aciklama, const char* yeni_pozisyon);
void ilan_tablo_listele(IlanHashTable* ht);
void ilan_tablo_yok_et(IlanHashTable* ht);

#endif
