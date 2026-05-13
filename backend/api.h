#ifndef API_H
#define API_H

/*
 * Bu header, C# tarafının P/Invoke ile çağıracağı tüm
 * exported fonksiyonları tanımlar.
 * DLL derlenirken: gcc -shared -o backend.dll *.c
 */

#ifdef _WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

#include "bst.h"
#include "sirket.h"

/* -------- Global sistem durumu -------- */
EXPORT void sistem_baslat();
EXPORT void sistem_kapat();

/* -------- İş Arayan -------- */
EXPORT int  ia_ekle(const char* tc, const char* ad, const char* soyad,
                    const char* adres, const char* telefon,
                    const char* eposta, const char* dogum_tarihi);
EXPORT int  ia_sil(const char* tc);
EXPORT int  ia_guncelle(const char* tc, const char* yeni_ad, const char* yeni_soyad,
                        const char* yeni_adres, const char* yeni_telefon,
                        const char* yeni_eposta, const char* yeni_dogum);
EXPORT int  ia_varmi(const char* tc);

/* Bilgi alma - char* buffer doldurur, C# tarafı okur */
EXPORT void ia_bilgi_al(const char* tc,
                        char* ad_buf,    int ad_len,
                        char* soyad_buf, int soyad_len,
                        char* adres_buf, int adres_len,
                        char* tel_buf,   int tel_len,
                        char* email_buf, int email_len,
                        char* dogum_buf, int dogum_len);
EXPORT float ia_puan_al(const char* tc);

/* Eğitim */
EXPORT int  ia_egitim_ekle(const char* tc, const char* okul, const char* bolum,
                           const char* baslama, const char* bitis, float ort);
EXPORT int  ia_egitim_sil (const char* tc, const char* okul, const char* bolum);
EXPORT int  ia_egitim_sayisi(const char* tc);

/* egitim_listele: indeks'e göre bilgi döndürür (C# döngüsü için) */
EXPORT int  ia_egitim_bilgi(const char* tc, int indeks,
                            char* okul_buf, int okul_len,
                            char* bolum_buf, int bolum_len,
                            char* bas_buf, int bas_len,
                            char* bit_buf, int bit_len,
                            float* ort_out);

/* Deneyim */
EXPORT int  ia_deneyim_ekle(const char* tc, const char* isyeri,
                            const char* pozisyon, int yil);
EXPORT int  ia_deneyim_sil (const char* tc, const char* isyeri, const char* pozisyon);
EXPORT int  ia_deneyim_sayisi(const char* tc);
EXPORT int  ia_deneyim_bilgi(const char* tc, int indeks,
                             char* isyeri_buf, int isyeri_len,
                             char* poz_buf,    int poz_len,
                             int*  yil_out);

/* BST dolaşma - callback yerine sırayla okuma (C# uyumu için indeks tabanlı) */
EXPORT int  ia_toplam_sayisi();
/* inorder sırasında i. elemanın TC'sini yazar */
EXPORT int  ia_inorder_tc   (int indeks, char* tc_buf, int tc_len);
EXPORT int  ia_preorder_tc  (int indeks, char* tc_buf, int tc_len);
EXPORT int  ia_postorder_tc (int indeks, char* tc_buf, int tc_len);

/* -------- Şirket -------- */
EXPORT int  sirket_ekle_api(int sirket_no, const char* ad, const char* adres,
                            const char* telefon, const char* eposta);
EXPORT int  sirket_sil_api(int sirket_no);
EXPORT int  sirket_guncelle_api(int sirket_no, const char* yeni_ad,
                                const char* yeni_adres, const char* yeni_telefon,
                                const char* yeni_eposta);
EXPORT int  sirket_varmi(int sirket_no);
EXPORT void sirket_bilgi_al(int sirket_no,
                            char* ad_buf,  int ad_len,
                            char* adr_buf, int adr_len,
                            char* tel_buf, int tel_len,
                            char* email_buf, int email_len);
EXPORT int  sirket_toplam_sayisi();
EXPORT int  sirket_no_listele(int indeks); /* i. şirketin no'sunu döndürür */

/* -------- İlan -------- */
EXPORT int  ilan_ekle_api(int sirket_no, int ilan_no, const char* baslik,
                          const char* aciklama, const char* pozisyon);
EXPORT int  ilan_sil_api(int sirket_no, int ilan_no);
EXPORT int  ilan_guncelle_api(int sirket_no, int ilan_no, const char* yeni_baslik,
                              const char* yeni_aciklama, const char* yeni_poz);
EXPORT int  ilan_varmi(int sirket_no, int ilan_no);
EXPORT void ilan_bilgi_al(int sirket_no, int ilan_no,
                          char* baslik_buf, int baslik_len,
                          char* aciklama_buf, int aciklama_len,
                          char* poz_buf, int poz_len);
EXPORT int  ilan_toplam_sayisi(int sirket_no);
EXPORT int  ilan_no_listele(int sirket_no, int indeks);
EXPORT int  ilan_basvuru_sayisi(int sirket_no, int ilan_no);

/* -------- Başvuru -------- */
EXPORT int  basvuru_yap(const char* tc, int sirket_no, int ilan_no);
EXPORT int  basvuru_varmi(const char* tc, int sirket_no, int ilan_no);
/* i. başvuranın bilgisi (puan sırasına göre) */
EXPORT int  basvuru_bilgi(int sirket_no, int ilan_no, int indeks,
                          char* tc_buf,  int tc_len,
                          char* ad_buf,  int ad_len,
                          char* soy_buf, int soy_len,
                          float* puan_out);

#endif
