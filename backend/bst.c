#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- Yardımcılar ---- */
static IsArayan* dugum_olustur(const char* tc, const char* ad, const char* soyad,
                                const char* adres, const char* telefon,
                                const char* eposta, const char* dogum_tarihi) {
    IsArayan* d = (IsArayan*)malloc(sizeof(IsArayan));
    if (!d) return NULL;

    strncpy(d->tc,           tc,           11);  d->tc[11]           = '\0';
    strncpy(d->ad,           ad,           49);  d->ad[49]           = '\0';
    strncpy(d->soyad,        soyad,        49);  d->soyad[49]        = '\0';
    strncpy(d->adres,        adres,        199); d->adres[199]       = '\0';
    strncpy(d->telefon,      telefon,      19);  d->telefon[19]      = '\0';
    strncpy(d->eposta,       eposta,       99);  d->eposta[99]       = '\0';
    strncpy(d->dogum_tarihi, dogum_tarihi, 19);  d->dogum_tarihi[19] = '\0';

    d->egitimler  = egitim_liste_olustur();
    d->deneyimler = deneyim_liste_olustur();
    d->sol = d->sag = NULL;
    return d;
}

static IsArayan* _ekle(IsArayan* kok, IsArayan* yeni, int* basari) {
    if (!kok) { *basari = 1; return yeni; }
    int cmp = strcmp(yeni->tc, kok->tc);
    if      (cmp < 0) kok->sol = _ekle(kok->sol, yeni, basari);
    else if (cmp > 0) kok->sag = _ekle(kok->sag, yeni, basari);
    else              *basari = -1; /* TC zaten var */
    return kok;
}

static IsArayan* _en_kucuk(IsArayan* kok) {
    while (kok->sol) kok = kok->sol;
    return kok;
}

static IsArayan* _sil(IsArayan* kok, const char* tc, int* basari) {
    if (!kok) return NULL;
    int cmp = strcmp(tc, kok->tc);
    if      (cmp < 0) kok->sol = _sil(kok->sol, tc, basari);
    else if (cmp > 0) kok->sag = _sil(kok->sag, tc, basari);
    else {
        *basari = 1;
        if (!kok->sol) {
            IsArayan* sag = kok->sag;
            egitim_liste_yok_et(kok->egitimler);
            deneyim_liste_yok_et(kok->deneyimler);
            free(kok);
            return sag;
        } else if (!kok->sag) {
            IsArayan* sol = kok->sol;
            egitim_liste_yok_et(kok->egitimler);
            deneyim_liste_yok_et(kok->deneyimler);
            free(kok);
            return sol;
        } else {
            /* İki çocuk: sağ alt ağacın en küçüğünü bul */
            IsArayan* halef = _en_kucuk(kok->sag);
            /* Halefin verisini kopyala */
            strncpy(kok->tc,           halef->tc,           11);
            strncpy(kok->ad,           halef->ad,           49);
            strncpy(kok->soyad,        halef->soyad,        49);
            strncpy(kok->adres,        halef->adres,        199);
            strncpy(kok->telefon,      halef->telefon,      19);
            strncpy(kok->eposta,       halef->eposta,       99);
            strncpy(kok->dogum_tarihi, halef->dogum_tarihi, 19);
            /* Listeleri de taşı */
            egitim_liste_yok_et(kok->egitimler);
            deneyim_liste_yok_et(kok->deneyimler);
            kok->egitimler  = halef->egitimler;
            kok->deneyimler = halef->deneyimler;
            halef->egitimler  = egitim_liste_olustur();
            halef->deneyimler = deneyim_liste_olustur();
            /* Halefi sil */
            kok->sag = _sil(kok->sag, halef->tc, basari);
        }
    }
    return kok;
}

static IsArayan* _ara(IsArayan* kok, const char* tc) {
    if (!kok) return NULL;
    int cmp = strcmp(tc, kok->tc);
    if      (cmp == 0) return kok;
    else if (cmp  < 0) return _ara(kok->sol, tc);
    else               return _ara(kok->sag, tc);
}

static void _yok_et(IsArayan* kok) {
    if (!kok) return;
    _yok_et(kok->sol);
    _yok_et(kok->sag);
    egitim_liste_yok_et(kok->egitimler);
    deneyim_liste_yok_et(kok->deneyimler);
    free(kok);
}

static void _yazdir(IsArayan* d) {
    printf("  TC: %s | %s %s | Tel: %s | E-posta: %s\n",
           d->tc, d->ad, d->soyad, d->telefon, d->eposta);
}

/* ---- API ---- */
IsArayanBST* bst_olustur() {
    IsArayanBST* bst = (IsArayanBST*)malloc(sizeof(IsArayanBST));
    if (!bst) return NULL;
    bst->kok           = NULL;
    bst->eleman_sayisi = 0;
    return bst;
}

int bst_ekle(IsArayanBST* bst, const char* tc, const char* ad,
             const char* soyad, const char* adres, const char* telefon,
             const char* eposta, const char* dogum_tarihi) {
    if (!bst) return 0;
    IsArayan* yeni = dugum_olustur(tc, ad, soyad, adres, telefon, eposta, dogum_tarihi);
    if (!yeni) return 0;
    int basari = 0;
    bst->kok = _ekle(bst->kok, yeni, &basari);
    if (basari == 1) { bst->eleman_sayisi++; return 1; }
    if (basari == -1) { /* TC zaten var, temizle */
        egitim_liste_yok_et(yeni->egitimler);
        deneyim_liste_yok_et(yeni->deneyimler);
        free(yeni);
        return -1;
    }
    return 0;
}

IsArayan* bst_ara(IsArayanBST* bst, const char* tc) {
    if (!bst) return NULL;
    return _ara(bst->kok, tc);
}

int bst_sil(IsArayanBST* bst, const char* tc) {
    if (!bst) return 0;
    int basari = 0;
    bst->kok = _sil(bst->kok, tc, &basari);
    if (basari) bst->eleman_sayisi--;
    return basari;
}

int bst_guncelle(IsArayanBST* bst, const char* tc,
                 const char* yeni_ad, const char* yeni_soyad,
                 const char* yeni_adres, const char* yeni_telefon,
                 const char* yeni_eposta, const char* yeni_dogum) {
    IsArayan* k = bst_ara(bst, tc);
    if (!k) return 0;
    if (yeni_ad      && yeni_ad[0])      { strncpy(k->ad,           yeni_ad,      49);  k->ad[49]           = '\0'; }
    if (yeni_soyad   && yeni_soyad[0])   { strncpy(k->soyad,        yeni_soyad,   49);  k->soyad[49]        = '\0'; }
    if (yeni_adres   && yeni_adres[0])   { strncpy(k->adres,        yeni_adres,   199); k->adres[199]       = '\0'; }
    if (yeni_telefon && yeni_telefon[0]) { strncpy(k->telefon,      yeni_telefon, 19);  k->telefon[19]      = '\0'; }
    if (yeni_eposta  && yeni_eposta[0])  { strncpy(k->eposta,       yeni_eposta,  99);  k->eposta[99]       = '\0'; }
    if (yeni_dogum   && yeni_dogum[0])   { strncpy(k->dogum_tarihi, yeni_dogum,   19);  k->dogum_tarihi[19] = '\0'; }
    return 1;
}

/* ---- Dolaşma ---- */
void bst_inorder(IsArayan* kok) {
    if (!kok) return;
    bst_inorder(kok->sol);
    _yazdir(kok);
    bst_inorder(kok->sag);
}

void bst_preorder(IsArayan* kok) {
    if (!kok) return;
    _yazdir(kok);
    bst_preorder(kok->sol);
    bst_preorder(kok->sag);
}

void bst_postorder(IsArayan* kok) {
    if (!kok) return;
    bst_postorder(kok->sol);
    bst_postorder(kok->sag);
    _yazdir(kok);
}

float is_arayan_puan_hesapla(IsArayan* k) {
    if (!k) return 0.0f;
    float ort  = egitim_ortalama_hesapla(k->egitimler);
    int   yil  = deneyim_toplam_yil(k->deneyimler);
    return ort * 20.0f + yil * 10.0f;
}

void bst_yok_et(IsArayanBST* bst) {
    if (!bst) return;
    _yok_et(bst->kok);
    free(bst);
}
