#include "ilan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- Hash fonksiyonu ---- */
static int hash_hesapla(int ilan_no) {
    return ((ilan_no % ILAN_TABLO_BOYUT) + ILAN_TABLO_BOYUT) % ILAN_TABLO_BOYUT;
}

IlanHashTable* ilan_tablo_olustur() {
    IlanHashTable* ht = (IlanHashTable*)malloc(sizeof(IlanHashTable));
    if (!ht) return NULL;
    for (int i = 0; i < ILAN_TABLO_BOYUT; i++) {
        ht->tablo[i].dolu       = 0;
        ht->tablo[i].ilan_no    = 0;
        ht->tablo[i].basvurular = NULL;
    }
    ht->eleman_sayisi = 0;
    return ht;
}

int ilan_ekle(IlanHashTable* ht, int ilan_no, const char* baslik,
              const char* aciklama, const char* pozisyon) {
    if (!ht || ht->eleman_sayisi >= ILAN_TABLO_BOYUT - 1) return 0;

    int indeks = hash_hesapla(ilan_no);
    int baslangic = indeks;

    /* Linear probing */
    while (ht->tablo[indeks].dolu == 1) {
        if (ht->tablo[indeks].ilan_no == ilan_no) return -1; /* zaten var */
        indeks = (indeks + 1) % ILAN_TABLO_BOYUT;
        if (indeks == baslangic) return 0; /* tablo dolu */
    }

    Ilan* slot = &ht->tablo[indeks];
    slot->ilan_no = ilan_no;
    strncpy(slot->baslik,    baslik,    149); slot->baslik[149]    = '\0';
    strncpy(slot->aciklama,  aciklama,  499); slot->aciklama[499]  = '\0';
    strncpy(slot->pozisyon,  pozisyon,  99);  slot->pozisyon[99]   = '\0';
    slot->dolu       = 1;
    slot->basvurular = heap_olustur();
    ht->eleman_sayisi++;
    return 1;
}

Ilan* ilan_ara(IlanHashTable* ht, int ilan_no) {
    if (!ht) return NULL;
    int indeks   = hash_hesapla(ilan_no);
    int baslangic = indeks;

    while (ht->tablo[indeks].dolu != 0) {
        if (ht->tablo[indeks].dolu == 1 && ht->tablo[indeks].ilan_no == ilan_no)
            return &ht->tablo[indeks];
        indeks = (indeks + 1) % ILAN_TABLO_BOYUT;
        if (indeks == baslangic) break;
    }
    return NULL;
}

int ilan_sil(IlanHashTable* ht, int ilan_no) {
    if (!ht) return 0;
    int indeks    = hash_hesapla(ilan_no);
    int baslangic = indeks;

    while (ht->tablo[indeks].dolu != 0) {
        if (ht->tablo[indeks].dolu == 1 && ht->tablo[indeks].ilan_no == ilan_no) {
            heap_yok_et(ht->tablo[indeks].basvurular);
            ht->tablo[indeks].basvurular = NULL;
            ht->tablo[indeks].dolu       = 2; /* tombstone */
            ht->eleman_sayisi--;
            return 1;
        }
        indeks = (indeks + 1) % ILAN_TABLO_BOYUT;
        if (indeks == baslangic) break;
    }
    return 0;
}

int ilan_guncelle(IlanHashTable* ht, int ilan_no, const char* yeni_baslik,
                  const char* yeni_aciklama, const char* yeni_pozisyon) {
    Ilan* ilan = ilan_ara(ht, ilan_no);
    if (!ilan) return 0;
    if (yeni_baslik   && yeni_baslik[0])   { strncpy(ilan->baslik,   yeni_baslik,   149); ilan->baslik[149]   = '\0'; }
    if (yeni_aciklama && yeni_aciklama[0]) { strncpy(ilan->aciklama, yeni_aciklama, 499); ilan->aciklama[499] = '\0'; }
    if (yeni_pozisyon && yeni_pozisyon[0]) { strncpy(ilan->pozisyon, yeni_pozisyon, 99);  ilan->pozisyon[99]  = '\0'; }
    return 1;
}

void ilan_tablo_listele(IlanHashTable* ht) {
    if (!ht || ht->eleman_sayisi == 0) {
        printf("  (Ilan yok)\n");
        return;
    }
    for (int i = 0; i < ILAN_TABLO_BOYUT; i++) {
        if (ht->tablo[i].dolu == 1) {
            printf("  [No:%d] %s | Pozisyon: %s | Basvuru: %d\n",
                   ht->tablo[i].ilan_no,
                   ht->tablo[i].baslik,
                   ht->tablo[i].pozisyon,
                   ht->tablo[i].basvurular ? ht->tablo[i].basvurular->boyut : 0);
        }
    }
}

void ilan_tablo_yok_et(IlanHashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < ILAN_TABLO_BOYUT; i++) {
        if (ht->tablo[i].dolu == 1 && ht->tablo[i].basvurular)
            heap_yok_et(ht->tablo[i].basvurular);
    }
    free(ht);
}
