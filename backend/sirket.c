#include "sirket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sirket_hash(int sirket_no) {
    return ((sirket_no % SIRKET_TABLO_BOYUT) + SIRKET_TABLO_BOYUT) % SIRKET_TABLO_BOYUT;
}

SirketHashTable* sirket_tablo_olustur() {
    SirketHashTable* ht = (SirketHashTable*)malloc(sizeof(SirketHashTable));
    if (!ht) return NULL;
    for (int i = 0; i < SIRKET_TABLO_BOYUT; i++) {
        ht->tablo[i].dolu      = 0;
        ht->tablo[i].sirket_no = 0;
        ht->tablo[i].ilanlar   = NULL;
    }
    ht->eleman_sayisi = 0;
    return ht;
}

int sirket_ekle(SirketHashTable* ht, int sirket_no, const char* ad,
                const char* adres, const char* telefon, const char* eposta) {
    if (!ht || ht->eleman_sayisi >= SIRKET_TABLO_BOYUT - 1) return 0;

    int indeks    = sirket_hash(sirket_no);
    int baslangic = indeks;

    while (ht->tablo[indeks].dolu == 1) {
        if (ht->tablo[indeks].sirket_no == sirket_no) return -1; /* zaten var */
        indeks = (indeks + 1) % SIRKET_TABLO_BOYUT;
        if (indeks == baslangic) return 0;
    }

    Sirket* s = &ht->tablo[indeks];
    s->sirket_no = sirket_no;
    strncpy(s->ad,      ad,      99);  s->ad[99]      = '\0';
    strncpy(s->adres,   adres,   199); s->adres[199]  = '\0';
    strncpy(s->telefon, telefon, 19);  s->telefon[19] = '\0';
    strncpy(s->eposta,  eposta,  99);  s->eposta[99]  = '\0';
    s->dolu    = 1;
    s->ilanlar = ilan_tablo_olustur();
    ht->eleman_sayisi++;
    return 1;
}

Sirket* sirket_ara(SirketHashTable* ht, int sirket_no) {
    if (!ht) return NULL;
    int indeks    = sirket_hash(sirket_no);
    int baslangic = indeks;

    while (ht->tablo[indeks].dolu != 0) {
        if (ht->tablo[indeks].dolu == 1 &&
            ht->tablo[indeks].sirket_no == sirket_no)
            return &ht->tablo[indeks];
        indeks = (indeks + 1) % SIRKET_TABLO_BOYUT;
        if (indeks == baslangic) break;
    }
    return NULL;
}

/* Cascade delete: şirket silinince tüm ilanlar ve heap'ler de silinir */
int sirket_sil(SirketHashTable* ht, int sirket_no) {
    if (!ht) return 0;
    int indeks    = sirket_hash(sirket_no);
    int baslangic = indeks;

    while (ht->tablo[indeks].dolu != 0) {
        if (ht->tablo[indeks].dolu == 1 &&
            ht->tablo[indeks].sirket_no == sirket_no) {
            /* Önce ilan tablosunu (ve içindeki heap'leri) yok et */
            ilan_tablo_yok_et(ht->tablo[indeks].ilanlar);
            ht->tablo[indeks].ilanlar = NULL;
            ht->tablo[indeks].dolu    = 2; /* tombstone */
            ht->eleman_sayisi--;
            return 1;
        }
        indeks = (indeks + 1) % SIRKET_TABLO_BOYUT;
        if (indeks == baslangic) break;
    }
    return 0;
}

int sirket_guncelle(SirketHashTable* ht, int sirket_no, const char* yeni_ad,
                    const char* yeni_adres, const char* yeni_telefon,
                    const char* yeni_eposta) {
    Sirket* s = sirket_ara(ht, sirket_no);
    if (!s) return 0;
    if (yeni_ad      && yeni_ad[0])      { strncpy(s->ad,      yeni_ad,      99);  s->ad[99]      = '\0'; }
    if (yeni_adres   && yeni_adres[0])   { strncpy(s->adres,   yeni_adres,   199); s->adres[199]  = '\0'; }
    if (yeni_telefon && yeni_telefon[0]) { strncpy(s->telefon, yeni_telefon, 19);  s->telefon[19] = '\0'; }
    if (yeni_eposta  && yeni_eposta[0])  { strncpy(s->eposta,  yeni_eposta,  99);  s->eposta[99]  = '\0'; }
    return 1;
}

void sirket_tablo_listele(SirketHashTable* ht) {
    if (!ht || ht->eleman_sayisi == 0) {
        printf("  (Sirket kaydi yok)\n");
        return;
    }
    for (int i = 0; i < SIRKET_TABLO_BOYUT; i++) {
        if (ht->tablo[i].dolu == 1) {
            printf("  [No:%d] %s | Tel: %s | E-posta: %s\n",
                   ht->tablo[i].sirket_no,
                   ht->tablo[i].ad,
                   ht->tablo[i].telefon,
                   ht->tablo[i].eposta);
        }
    }
}

void sirket_tablo_yok_et(SirketHashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < SIRKET_TABLO_BOYUT; i++) {
        if (ht->tablo[i].dolu == 1 && ht->tablo[i].ilanlar)
            ilan_tablo_yok_et(ht->tablo[i].ilanlar);
    }
    free(ht);
}
