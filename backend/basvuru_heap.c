#include "basvuru_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- Yardımcı ---- */
static void swap(BasvuruEleman* a, BasvuruEleman* b) {
    BasvuruEleman tmp = *a; *a = *b; *b = tmp;
}

static void yukari_tas(BasvuruMaxHeap* h, int i) {
    while (i > 0) {
        int ebeveyn = (i - 1) / 2;
        if (h->elemanlar[ebeveyn].puan < h->elemanlar[i].puan) {
            swap(&h->elemanlar[ebeveyn], &h->elemanlar[i]);
            i = ebeveyn;
        } else break;
    }
}

static void asagi_tas(BasvuruMaxHeap* h, int i) {
    int boyut = h->boyut;
    while (1) {
        int sol = 2 * i + 1;
        int sag = 2 * i + 2;
        int en_buyuk = i;

        if (sol < boyut && h->elemanlar[sol].puan > h->elemanlar[en_buyuk].puan)
            en_buyuk = sol;
        if (sag < boyut && h->elemanlar[sag].puan > h->elemanlar[en_buyuk].puan)
            en_buyuk = sag;

        if (en_buyuk != i) {
            swap(&h->elemanlar[i], &h->elemanlar[en_buyuk]);
            i = en_buyuk;
        } else break;
    }
}

/* ---- API ---- */
BasvuruMaxHeap* heap_olustur() {
    BasvuruMaxHeap* h = (BasvuruMaxHeap*)malloc(sizeof(BasvuruMaxHeap));
    if (!h) return NULL;
    h->boyut = 0;
    return h;
}

int heap_ekle(BasvuruMaxHeap* h, const char* tc, const char* ad,
              const char* soyad, float puan) {
    if (!h || h->boyut >= HEAP_MAX_KAPASITE) return 0;

    /* Aynı TC zaten başvurmuş mu? */
    if (heap_icinde_mi(h, tc)) return -1;

    BasvuruEleman* e = &h->elemanlar[h->boyut];
    strncpy(e->tc, tc, 11);       e->tc[11]    = '\0';
    strncpy(e->ad, ad, 49);       e->ad[49]    = '\0';
    strncpy(e->soyad, soyad, 49); e->soyad[49] = '\0';
    e->puan = puan;

    yukari_tas(h, h->boyut);
    h->boyut++;
    return 1;
}

BasvuruEleman heap_max_al(BasvuruMaxHeap* h) {
    BasvuruEleman bos = {"", "", "", -1.0f};
    if (!h || h->boyut == 0) return bos;
    return h->elemanlar[0];
}

BasvuruEleman heap_max_cikar(BasvuruMaxHeap* h) {
    BasvuruEleman bos = {"", "", "", -1.0f};
    if (!h || h->boyut == 0) return bos;

    BasvuruEleman kok = h->elemanlar[0];
    h->boyut--;
    h->elemanlar[0] = h->elemanlar[h->boyut];
    asagi_tas(h, 0);
    return kok;
}

int heap_icinde_mi(BasvuruMaxHeap* h, const char* tc) {
    if (!h) return 0;
    for (int i = 0; i < h->boyut; i++)
        if (strcmp(h->elemanlar[i].tc, tc) == 0) return 1;
    return 0;
}

void heap_listele(BasvuruMaxHeap* h) {
    if (!h || h->boyut == 0) {
        printf("  (Basvuru yok)\n");
        return;
    }
    /* Sıralı göstermek için geçici kopya üzerinde sıralama */
    BasvuruMaxHeap kopya = *h;
    int sira = 1;
    while (kopya.boyut > 0) {
        BasvuruEleman e = heap_max_cikar(&kopya);
        printf("  [%d] %s %s (TC: %s) | Puan: %.2f\n",
               sira++, e.ad, e.soyad, e.tc, e.puan);
    }
}

void heap_yok_et(BasvuruMaxHeap* h) {
    free(h);
}
