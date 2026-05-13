#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- Global durum -------- */
static IsArayanBST*   g_bst    = NULL;
static SirketHashTable* g_sirket = NULL;

void sistem_baslat() {
    if (!g_bst)    g_bst    = bst_olustur();
    if (!g_sirket) g_sirket = sirket_tablo_olustur();
}

void sistem_kapat() {
    bst_yok_et(g_bst);          g_bst    = NULL;
    sirket_tablo_yok_et(g_sirket); g_sirket = NULL;
}

/* ============================== İŞ ARAYAN ============================== */

int ia_ekle(const char* tc, const char* ad, const char* soyad,
            const char* adres, const char* telefon,
            const char* eposta, const char* dogum_tarihi) {
    if (!g_bst) return 0;
    return bst_ekle(g_bst, tc, ad, soyad, adres, telefon, eposta, dogum_tarihi);
}

int ia_sil(const char* tc) {
    if (!g_bst) return 0;
    return bst_sil(g_bst, tc);
}

int ia_guncelle(const char* tc, const char* yeni_ad, const char* yeni_soyad,
                const char* yeni_adres, const char* yeni_telefon,
                const char* yeni_eposta, const char* yeni_dogum) {
    if (!g_bst) return 0;
    return bst_guncelle(g_bst, tc, yeni_ad, yeni_soyad,
                        yeni_adres, yeni_telefon, yeni_eposta, yeni_dogum);
}

int ia_varmi(const char* tc) {
    if (!g_bst) return 0;
    return bst_ara(g_bst, tc) != NULL ? 1 : 0;
}

void ia_bilgi_al(const char* tc,
                 char* ad_buf,    int ad_len,
                 char* soyad_buf, int soyad_len,
                 char* adres_buf, int adres_len,
                 char* tel_buf,   int tel_len,
                 char* email_buf, int email_len,
                 char* dogum_buf, int dogum_len) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return;
    if (ad_buf    && ad_len    > 0) strncpy(ad_buf,    k->ad,           ad_len    - 1);
    if (soyad_buf && soyad_len > 0) strncpy(soyad_buf, k->soyad,        soyad_len - 1);
    if (adres_buf && adres_len > 0) strncpy(adres_buf, k->adres,        adres_len - 1);
    if (tel_buf   && tel_len   > 0) strncpy(tel_buf,   k->telefon,      tel_len   - 1);
    if (email_buf && email_len > 0) strncpy(email_buf, k->eposta,       email_len - 1);
    if (dogum_buf && dogum_len > 0) strncpy(dogum_buf, k->dogum_tarihi, dogum_len - 1);
}

float ia_puan_al(const char* tc) {
    IsArayan* k = bst_ara(g_bst, tc);
    return k ? is_arayan_puan_hesapla(k) : 0.0f;
}

/* ---- Eğitim ---- */
int ia_egitim_ekle(const char* tc, const char* okul, const char* bolum,
                   const char* baslama, const char* bitis, float ort) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    egitim_ekle(k->egitimler, okul, bolum, baslama, bitis, ort);
    return 1;
}

int ia_egitim_sil(const char* tc, const char* okul, const char* bolum) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    return egitim_sil(k->egitimler, okul, bolum);
}

int ia_egitim_sayisi(const char* tc) {
    IsArayan* k = bst_ara(g_bst, tc);
    return k ? k->egitimler->adet : 0;
}

int ia_egitim_bilgi(const char* tc, int indeks,
                    char* okul_buf, int okul_len,
                    char* bolum_buf, int bolum_len,
                    char* bas_buf, int bas_len,
                    char* bit_buf, int bit_len,
                    float* ort_out) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    EgitimDugum* d = k->egitimler->bas;
    for (int i = 0; i < indeks && d; i++) d = d->sonraki;
    if (!d) return 0;
    if (okul_buf  && okul_len  > 0) strncpy(okul_buf,  d->okul_adi,       okul_len  - 1);
    if (bolum_buf && bolum_len > 0) strncpy(bolum_buf, d->bolum,           bolum_len - 1);
    if (bas_buf   && bas_len   > 0) strncpy(bas_buf,   d->baslama_tarihi, bas_len   - 1);
    if (bit_buf   && bit_len   > 0) strncpy(bit_buf,   d->bitis_tarihi,   bit_len   - 1);
    if (ort_out)                    *ort_out = d->ortalama;
    return 1;
}

/* ---- Deneyim ---- */
int ia_deneyim_ekle(const char* tc, const char* isyeri,
                    const char* pozisyon, int yil) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    deneyim_ekle(k->deneyimler, isyeri, pozisyon, yil);
    return 1;
}

int ia_deneyim_sil(const char* tc, const char* isyeri, const char* pozisyon) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    return deneyim_sil(k->deneyimler, isyeri, pozisyon);
}

int ia_deneyim_sayisi(const char* tc) {
    IsArayan* k = bst_ara(g_bst, tc);
    return k ? k->deneyimler->adet : 0;
}

int ia_deneyim_bilgi(const char* tc, int indeks,
                     char* isyeri_buf, int isyeri_len,
                     char* poz_buf,    int poz_len,
                     int*  yil_out) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    DeneyimDugum* d = k->deneyimler->bas;
    for (int i = 0; i < indeks && d; i++) d = d->sonraki;
    if (!d) return 0;
    if (isyeri_buf && isyeri_len > 0) strncpy(isyeri_buf, d->isyeri_adi, isyeri_len - 1);
    if (poz_buf    && poz_len    > 0) strncpy(poz_buf,    d->pozisyon,   poz_len    - 1);
    if (yil_out)                       *yil_out = d->deneyim_yili;
    return 1;
}

/* ---- BST Dolaşma (indeks tabanlı, C# uyumlu) ---- */
/* Dolaşma sonuçlarını geçici diziye yazar */
static IsArayan* g_gezi_dizi[5000];
static int       g_gezi_boyut = 0;

static void _inorder_doldur(IsArayan* kok) {
    if (!kok) return;
    _inorder_doldur(kok->sol);
    if (g_gezi_boyut < 5000) g_gezi_dizi[g_gezi_boyut++] = kok;
    _inorder_doldur(kok->sag);
}
static void _preorder_doldur(IsArayan* kok) {
    if (!kok) return;
    if (g_gezi_boyut < 5000) g_gezi_dizi[g_gezi_boyut++] = kok;
    _preorder_doldur(kok->sol);
    _preorder_doldur(kok->sag);
}
static void _postorder_doldur(IsArayan* kok) {
    if (!kok) return;
    _postorder_doldur(kok->sol);
    _postorder_doldur(kok->sag);
    if (g_gezi_boyut < 5000) g_gezi_dizi[g_gezi_boyut++] = kok;
}

int ia_toplam_sayisi() {
    return g_bst ? g_bst->eleman_sayisi : 0;
}

int ia_inorder_tc(int indeks, char* tc_buf, int tc_len) {
    g_gezi_boyut = 0;
    _inorder_doldur(g_bst->kok);
    if (indeks < 0 || indeks >= g_gezi_boyut) return 0;
    strncpy(tc_buf, g_gezi_dizi[indeks]->tc, tc_len - 1);
    return 1;
}

int ia_preorder_tc(int indeks, char* tc_buf, int tc_len) {
    g_gezi_boyut = 0;
    _preorder_doldur(g_bst->kok);
    if (indeks < 0 || indeks >= g_gezi_boyut) return 0;
    strncpy(tc_buf, g_gezi_dizi[indeks]->tc, tc_len - 1);
    return 1;
}

int ia_postorder_tc(int indeks, char* tc_buf, int tc_len) {
    g_gezi_boyut = 0;
    _postorder_doldur(g_bst->kok);
    if (indeks < 0 || indeks >= g_gezi_boyut) return 0;
    strncpy(tc_buf, g_gezi_dizi[indeks]->tc, tc_len - 1);
    return 1;
}

/* ============================== ŞİRKET ============================== */

int sirket_ekle_api(int sirket_no, const char* ad, const char* adres,
                    const char* telefon, const char* eposta) {
    if (!g_sirket) return 0;
    return sirket_ekle(g_sirket, sirket_no, ad, adres, telefon, eposta);
}

int sirket_sil_api(int sirket_no) {
    if (!g_sirket) return 0;
    return sirket_sil(g_sirket, sirket_no);
}

int sirket_guncelle_api(int sirket_no, const char* yeni_ad,
                        const char* yeni_adres, const char* yeni_telefon,
                        const char* yeni_eposta) {
    if (!g_sirket) return 0;
    return sirket_guncelle(g_sirket, sirket_no, yeni_ad, yeni_adres,
                           yeni_telefon, yeni_eposta);
}

int sirket_varmi(int sirket_no) {
    if (!g_sirket) return 0;
    return sirket_ara(g_sirket, sirket_no) != NULL ? 1 : 0;
}

void sirket_bilgi_al(int sirket_no,
                     char* ad_buf,  int ad_len,
                     char* adr_buf, int adr_len,
                     char* tel_buf, int tel_len,
                     char* email_buf, int email_len) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return;
    if (ad_buf    && ad_len    > 0) strncpy(ad_buf,    s->ad,      ad_len    - 1);
    if (adr_buf   && adr_len   > 0) strncpy(adr_buf,   s->adres,   adr_len   - 1);
    if (tel_buf   && tel_len   > 0) strncpy(tel_buf,   s->telefon, tel_len   - 1);
    if (email_buf && email_len > 0) strncpy(email_buf, s->eposta,  email_len - 1);
}

int sirket_toplam_sayisi() {
    return g_sirket ? g_sirket->eleman_sayisi : 0;
}

int sirket_no_listele(int indeks) {
    if (!g_sirket || indeks < 0) return -1;
    int sayac = 0;
    for (int i = 0; i < SIRKET_TABLO_BOYUT; i++) {
        if (g_sirket->tablo[i].dolu == 1) {
            if (sayac == indeks) return g_sirket->tablo[i].sirket_no;
            sayac++;
        }
    }
    return -1;
}

/* ============================== İLAN ============================== */

int ilan_ekle_api(int sirket_no, int ilan_no, const char* baslik,
                  const char* aciklama, const char* pozisyon) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    return ilan_ekle(s->ilanlar, ilan_no, baslik, aciklama, pozisyon);
}

int ilan_sil_api(int sirket_no, int ilan_no) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    return ilan_sil(s->ilanlar, ilan_no);
}

int ilan_guncelle_api(int sirket_no, int ilan_no, const char* yeni_baslik,
                      const char* yeni_aciklama, const char* yeni_poz) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    return ilan_guncelle(s->ilanlar, ilan_no, yeni_baslik, yeni_aciklama, yeni_poz);
}

int ilan_varmi(int sirket_no, int ilan_no) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    return ilan_ara(s->ilanlar, ilan_no) != NULL ? 1 : 0;
}

void ilan_bilgi_al(int sirket_no, int ilan_no,
                   char* baslik_buf, int baslik_len,
                   char* aciklama_buf, int aciklama_len,
                   char* poz_buf, int poz_len) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return;
    Ilan* ilan = ilan_ara(s->ilanlar, ilan_no);
    if (!ilan) return;
    if (baslik_buf   && baslik_len   > 0) strncpy(baslik_buf,   ilan->baslik,   baslik_len   - 1);
    if (aciklama_buf && aciklama_len > 0) strncpy(aciklama_buf, ilan->aciklama, aciklama_len - 1);
    if (poz_buf      && poz_len      > 0) strncpy(poz_buf,      ilan->pozisyon, poz_len      - 1);
}

int ilan_toplam_sayisi(int sirket_no) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    return s->ilanlar->eleman_sayisi;
}

int ilan_no_listele(int sirket_no, int indeks) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s || indeks < 0) return -1;
    int sayac = 0;
    for (int i = 0; i < ILAN_TABLO_BOYUT; i++) {
        if (s->ilanlar->tablo[i].dolu == 1) {
            if (sayac == indeks) return s->ilanlar->tablo[i].ilan_no;
            sayac++;
        }
    }
    return -1;
}

int ilan_basvuru_sayisi(int sirket_no, int ilan_no) {
    Sirket* s = sirket_ara(g_sirket, sirket_no);
    if (!s) return 0;
    Ilan* ilan = ilan_ara(s->ilanlar, ilan_no);
    return (ilan && ilan->basvurular) ? ilan->basvurular->boyut : 0;
}

/* ============================== BAŞVURU ============================== */

int basvuru_yap(const char* tc, int sirket_no, int ilan_no) {
    IsArayan* k = bst_ara(g_bst, tc);
    if (!k) return 0;
    Sirket*  s  = sirket_ara(g_sirket, sirket_no);
    if (!s)  return 0;
    Ilan*    il = ilan_ara(s->ilanlar, ilan_no);
    if (!il) return 0;
    float puan = is_arayan_puan_hesapla(k);
    return heap_ekle(il->basvurular, tc, k->ad, k->soyad, puan);
}

int basvuru_varmi(const char* tc, int sirket_no, int ilan_no) {
    Sirket* s  = sirket_ara(g_sirket, sirket_no);
    if (!s)    return 0;
    Ilan*   il = ilan_ara(s->ilanlar, ilan_no);
    if (!il)   return 0;
    return heap_icinde_mi(il->basvurular, tc);
}

int basvuru_bilgi(int sirket_no, int ilan_no, int indeks,
                  char* tc_buf,  int tc_len,
                  char* ad_buf,  int ad_len,
                  char* soy_buf, int soy_len,
                  float* puan_out) {
    Sirket* s  = sirket_ara(g_sirket, sirket_no);
    if (!s)    return 0;
    Ilan*   il = ilan_ara(s->ilanlar, ilan_no);
    if (!il || !il->basvurular) return 0;

    /* Heap'i geçici kopyayla sıralı gez */
    BasvuruMaxHeap kopya = *il->basvurular;
    for (int i = 0; i <= indeks; i++) {
        if (kopya.boyut == 0) return 0;
        BasvuruEleman e = heap_max_cikar(&kopya);
        if (i == indeks) {
            if (tc_buf  && tc_len  > 0) strncpy(tc_buf,  e.tc,    tc_len  - 1);
            if (ad_buf  && ad_len  > 0) strncpy(ad_buf,  e.ad,    ad_len  - 1);
            if (soy_buf && soy_len > 0) strncpy(soy_buf, e.soyad, soy_len - 1);
            if (puan_out) *puan_out = e.puan;
            return 1;
        }
    }
    return 0;
}
