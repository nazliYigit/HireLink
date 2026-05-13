#include "api.h"
#include <stdio.h>

int main() {
    printf("=== Sistem Baslatiliyor ===\n");
    sistem_baslat();

    /* ---- Şirket ekle ---- */
    printf("\n--- Sirket Ekle ---\n");
    int r = sirket_ekle_api(1001, "TechCorp A.S.", "Ankara", "0312-000-0001", "info@techcorp.com");
    printf("Sirket 1001 ekle: %s\n", r == 1 ? "OK" : "HATA");
    r = sirket_ekle_api(1002, "DataSoft Ltd.", "Istanbul", "0212-000-0002", "hr@datasoft.com");
    printf("Sirket 1002 ekle: %s\n", r == 1 ? "OK" : "HATA");

    /* ---- İlan ekle ---- */
    printf("\n--- Ilan Ekle ---\n");
    r = ilan_ekle_api(1001, 501, "Backend Developer", "C/C++ deneyimli", "Yazilim Muhendisi");
    printf("Ilan 501 ekle: %s\n", r == 1 ? "OK" : "HATA");
    r = ilan_ekle_api(1001, 502, "Frontend Developer", "React bilgisi", "UI Gelistirici");
    printf("Ilan 502 ekle: %s\n", r == 1 ? "OK" : "HATA");

    /* ---- İş arayan ekle ---- */
    printf("\n--- Is Arayan Ekle ---\n");
    r = ia_ekle("12345678901", "Ahmet", "Yilmaz", "Ankara Cad. No:1",
                "0555-111-2233", "ahmet@mail.com", "1995-03-15");
    printf("Ahmet ekle: %s\n", r == 1 ? "OK" : "HATA");

    r = ia_ekle("98765432100", "Zeynep", "Kaya", "Izmir Cad. No:5",
                "0544-999-8877", "zeynep@mail.com", "1998-07-20");
    printf("Zeynep ekle: %s\n", r == 1 ? "OK" : "HATA");

    r = ia_ekle("55544433322", "Mehmet", "Demir", "Istanbul Cad. No:3",
                "0533-222-4455", "mehmet@mail.com", "1992-11-01");
    printf("Mehmet ekle: %s\n", r == 1 ? "OK" : "HATA");

    /* ---- Eğitim ve deneyim ekle ---- */
    printf("\n--- Egitim / Deneyim Ekle ---\n");
    ia_egitim_ekle("12345678901", "ODTU", "Bilgisayar Muhendisligi", "2013", "2017", 3.20f);
    ia_egitim_ekle("12345678901", "Hacettepe", "Yuksek Lisans", "2017", "2019", 3.50f);
    ia_deneyim_ekle("12345678901", "TechCorp", "Junior Developer", 2);
    ia_deneyim_ekle("12345678901", "StartupX", "Senior Developer", 3);
    printf("Ahmet egitim ort: %.2f\n", ia_puan_al("12345678901"));

    ia_egitim_ekle("98765432100", "Bilkent", "Matematik", "2016", "2020", 3.80f);
    ia_deneyim_ekle("98765432100", "DataSoft", "Analist", 1);

    /* ---- Başvuru yap ---- */
    printf("\n--- Basvuru Yap ---\n");
    r = basvuru_yap("12345678901", 1001, 501);
    printf("Ahmet -> Ilan 501: %s\n", r == 1 ? "OK" : (r == -1 ? "Zaten basvurmus" : "HATA"));
    r = basvuru_yap("98765432100", 1001, 501);
    printf("Zeynep -> Ilan 501: %s\n", r == 1 ? "OK" : "HATA");
    r = basvuru_yap("55544433322", 1001, 501);
    printf("Mehmet -> Ilan 501: %s\n", r == 1 ? "OK" : "HATA");

    /* ---- Başvuru listesi ---- */
    printf("\n--- Ilan 501 Basvuranlar (puan sirasi) ---\n");
    int bs = ilan_basvuru_sayisi(1001, 501);
    printf("Toplam basvuru: %d\n", bs);
    char tc_b[12], ad_b[50], soy_b[50];
    float puan_b;
    for (int i = 0; i < bs; i++) {
        basvuru_bilgi(1001, 501, i, tc_b, 12, ad_b, 50, soy_b, 50, &puan_b);
        printf("  %d. %s %s (TC:%s) Puan:%.2f\n", i+1, ad_b, soy_b, tc_b, puan_b);
    }

    /* ---- BST Dolaşma ---- */
    printf("\n--- BST Inorder (TC sirali) ---\n");
    int toplam = ia_toplam_sayisi();
    char tc_buf[12];
    char ad_buf[50], soy_buf[50];
    for (int i = 0; i < toplam; i++) {
        ia_inorder_tc(i, tc_buf, 12);
        ia_bilgi_al(tc_buf,
                    ad_buf, 50, soy_buf, 50,
                    NULL, 0, NULL, 0, NULL, 0, NULL, 0);
        printf("  %d. %s %s (TC:%s)\n", i+1, ad_buf, soy_buf, tc_buf);
    }

    printf("\n--- BST Preorder ---\n");
    for (int i = 0; i < toplam; i++) {
        ia_preorder_tc(i, tc_buf, 12);
        ia_bilgi_al(tc_buf,
                    ad_buf, 50, soy_buf, 50,
                    NULL, 0, NULL, 0, NULL, 0, NULL, 0);
        printf("  %d. %s %s\n", i+1, ad_buf, soy_buf);
    }

    /* ---- Şirket silme (cascade) ---- */
    printf("\n--- Sirket 1001 Sil (cascade) ---\n");
    r = sirket_sil_api(1001);
    printf("Sirket 1001 sil: %s\n", r == 1 ? "OK" : "HATA");
    printf("Ilan 501 hala var mi: %s\n", ilan_varmi(1001, 501) ? "EVET (HATA!)" : "HAYIR (OK)");

    printf("\n=== Sistem Kapatiliyor ===\n");
    sistem_kapat();
    return 0;
}
