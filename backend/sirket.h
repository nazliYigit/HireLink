#ifndef SIRKET_H
#define SIRKET_H

#include "ilan.h"

#define SIRKET_TABLO_BOYUT 97

typedef struct {
    int    sirket_no;
    char   ad[100];
    char   adres[200];
    char   telefon[20];
    char   eposta[100];
    int    dolu;   /* 0=bos, 1=dolu, 2=tombstone */
    IlanHashTable* ilanlar;
} Sirket;

typedef struct {
    Sirket tablo[SIRKET_TABLO_BOYUT];
    int    eleman_sayisi;
} SirketHashTable;

SirketHashTable* sirket_tablo_olustur();
int     sirket_ekle(SirketHashTable* ht, int sirket_no, const char* ad,
                    const char* adres, const char* telefon, const char* eposta);
Sirket* sirket_ara(SirketHashTable* ht, int sirket_no);
int     sirket_sil(SirketHashTable* ht, int sirket_no);
int     sirket_guncelle(SirketHashTable* ht, int sirket_no, const char* yeni_ad,
                        const char* yeni_adres, const char* yeni_telefon,
                        const char* yeni_eposta);
void    sirket_tablo_listele(SirketHashTable* ht);
void    sirket_tablo_yok_et(SirketHashTable* ht);

#endif
