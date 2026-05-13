#include "deneyim_liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DeneyimLinkedList* deneyim_liste_olustur() {
    DeneyimLinkedList* liste = (DeneyimLinkedList*)malloc(sizeof(DeneyimLinkedList));
    if (!liste) return NULL;
    liste->bas = NULL;
    liste->adet = 0;
    return liste;
}

void deneyim_ekle(DeneyimLinkedList* liste, const char* isyeri,
                  const char* pozisyon, int yil) {
    if (!liste) return;
    DeneyimDugum* yeni = (DeneyimDugum*)malloc(sizeof(DeneyimDugum));
    if (!yeni) return;

    strncpy(yeni->isyeri_adi, isyeri, 99);   yeni->isyeri_adi[99] = '\0';
    strncpy(yeni->pozisyon, pozisyon, 99);    yeni->pozisyon[99] = '\0';
    yeni->deneyim_yili = yil;
    yeni->sonraki = liste->bas;
    liste->bas = yeni;
    liste->adet++;
}

int deneyim_sil(DeneyimLinkedList* liste, const char* isyeri, const char* pozisyon) {
    if (!liste || !liste->bas) return 0;
    DeneyimDugum* onceki = NULL;
    DeneyimDugum* mevcut = liste->bas;

    while (mevcut) {
        if (strcmp(mevcut->isyeri_adi, isyeri) == 0 &&
            strcmp(mevcut->pozisyon, pozisyon) == 0) {
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

void deneyim_listele(DeneyimLinkedList* liste) {
    if (!liste || !liste->bas) {
        printf("  (Deneyim bilgisi yok)\n");
        return;
    }
    DeneyimDugum* d = liste->bas;
    int i = 1;
    while (d) {
        printf("  [%d] %s | %s | %d yil\n",
               i++, d->isyeri_adi, d->pozisyon, d->deneyim_yili);
        d = d->sonraki;
    }
}

/* Tüm deneyim yıllarını topla */
int deneyim_toplam_yil(DeneyimLinkedList* liste) {
    if (!liste) return 0;
    int toplam = 0;
    DeneyimDugum* d = liste->bas;
    while (d) {
        toplam += d->deneyim_yili;
        d = d->sonraki;
    }
    return toplam;
}

void deneyim_liste_temizle(DeneyimLinkedList* liste) {
    if (!liste) return;
    DeneyimDugum* d = liste->bas;
    while (d) {
        DeneyimDugum* sonraki = d->sonraki;
        free(d);
        d = sonraki;
    }
    liste->bas = NULL;
    liste->adet = 0;
}

void deneyim_liste_yok_et(DeneyimLinkedList* liste) {
    if (!liste) return;
    deneyim_liste_temizle(liste);
    free(liste);
}
