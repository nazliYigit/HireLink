#ifndef BST_H
#define BST_H

#include "egitim_liste.h"
#include "deneyim_liste.h"

typedef struct IsArayan {
    char tc[12];
    char ad[50];
    char soyad[50];
    char adres[200];
    char telefon[20];
    char eposta[100];
    char dogum_tarihi[20];
    EgitimLinkedList*  egitimler;
    DeneyimLinkedList* deneyimler;
    struct IsArayan* sol;
    struct IsArayan* sag;
} IsArayan;

typedef struct {
    IsArayan* kok;
    int       eleman_sayisi;
} IsArayanBST;

/* BST işlemleri */
IsArayanBST* bst_olustur();
int      bst_ekle(IsArayanBST* bst, const char* tc, const char* ad,
                  const char* soyad, const char* adres, const char* telefon,
                  const char* eposta, const char* dogum_tarihi);
IsArayan* bst_ara(IsArayanBST* bst, const char* tc);
int      bst_sil(IsArayanBST* bst, const char* tc);
int      bst_guncelle(IsArayanBST* bst, const char* tc,
                      const char* yeni_ad, const char* yeni_soyad,
                      const char* yeni_adres, const char* yeni_telefon,
                      const char* yeni_eposta, const char* yeni_dogum);

/* Dolaşma */
void bst_inorder   (IsArayan* kok);
void bst_preorder  (IsArayan* kok);
void bst_postorder (IsArayan* kok);

void bst_yok_et(IsArayanBST* bst);

/* Puan hesaplama yardımcısı */
float is_arayan_puan_hesapla(IsArayan* kisi);

#endif
