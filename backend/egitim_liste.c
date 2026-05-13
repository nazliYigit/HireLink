#include "egitim_liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EgitimLinkedList* egitim_liste_olustur() {
    EgitimLinkedList* liste = (EgitimLinkedList*)malloc(sizeof(EgitimLinkedList));
    if (!liste) return NULL;
    liste->bas = NULL;
    liste->adet = 0;
    return liste;
}

void egitim_ekle(EgitimLinkedList* liste, const char* okul, const char* bolum,
                 const char* baslama, const char* bitis, float ort) {
    if (!liste) return;
    EgitimDugum* yeni = (EgitimDugum*)malloc(sizeof(EgitimDugum));
    if (!yeni) return;

    strncpy(yeni->okul_adi, okul, 99);   yeni->okul_adi[99] = '\0';
    strncpy(yeni->bolum, bolum, 99);      yeni->bolum[99] = '\0';
    strncpy(yeni->baslama_tarihi, baslama, 19); yeni->baslama_tarihi[19] = '\0';
    strncpy(yeni->bitis_tarihi, bitis, 19);     yeni->bitis_tarihi[19] = '\0';
    yeni->ortalama = ort;
    yeni->sonraki = liste->bas;
    liste->bas = yeni;
    liste->adet++;
}

int egitim_sil(EgitimLinkedList* liste, const char* okul, const char* bolum) {
    if (!liste || !liste->bas) return 0;
    EgitimDugum* onceki = NULL;
    EgitimDugum* mevcut = liste->bas;

    while (mevcut) {
        if (strcmp(mevcut->okul_adi, okul) == 0 && strcmp(mevcut->bolum, bolum) == 0) {
            if (onceki) onceki->sonraki = mevcut->sonraki;
            else        liste->bas = mevcut->sonraki;
            free(mevcut);
            liste->adet--;
            return 1;
        }
        onceki = mevcut;
        mevcut = mevcut->sonraki;
    }
    return 0;
}

void egitim_listele(EgitimLinkedList* liste) {
    if (!liste || !liste->bas) {
        printf("  (Egitim bilgisi yok)\n");
        return;
    }
    EgitimDugum* d = liste->bas;
    int i = 1;
    while (d) {
        printf("  [%d] %s - %s | %s ~ %s | Ort: %.2f\n",
               i++, d->okul_adi, d->bolum,
               d->baslama_tarihi, d->bitis_tarihi, d->ortalama);
        d = d->sonraki;
    }
}

/* Tüm eğitimlerin ortalamasının ortalaması */
float egitim_ortalama_hesapla(EgitimLinkedList* liste) {
    if (!liste || !liste->bas) return 0.0f;
    float toplam = 0.0f;
    int adet = 0;
    EgitimDugum* d = liste->bas;
    while (d) {
        toplam += d->ortalama;
        adet++;
        d = d->sonraki;
    }
    return (adet > 0) ? (toplam / adet) : 0.0f;
}

void egitim_liste_temizle(EgitimLinkedList* liste) {
    if (!liste) return;
    EgitimDugum* d = liste->bas;
    while (d) {
        EgitimDugum* sonraki = d->sonraki;
        free(d);
        d = sonraki;
    }
    liste->bas = NULL;
    liste->adet = 0;
}

void egitim_liste_yok_et(EgitimLinkedList* liste) {
    if (!liste) return;
    egitim_liste_temizle(liste);
    free(liste);
}
