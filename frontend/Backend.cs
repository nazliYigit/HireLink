using System;
using System.Runtime.InteropServices;
using System.Text;

namespace IsIlani
{
    /// <summary>
    /// C backend DLL'ine P/Invoke köprüsü.
    /// backend.dll, uygulamanın yanında bulunmalıdır.
    /// </summary>
    internal static class Backend
    {
        private const string DLL = "backend.dll";

        // ── Sistem ──────────────────────────────────────────────────────────
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void sistem_baslat();

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void sistem_kapat();

        // ── İş Arayan ───────────────────────────────────────────────────────
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_ekle(string tc, string ad, string soyad,
            string adres, string telefon, string eposta, string dogum_tarihi);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_sil(string tc);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_guncelle(string tc,
            string yeni_ad, string yeni_soyad, string yeni_adres,
            string yeni_telefon, string yeni_eposta, string yeni_dogum);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_varmi(string tc);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ia_bilgi_al(string tc,
            StringBuilder ad_buf,    int ad_len,
            StringBuilder soyad_buf, int soyad_len,
            StringBuilder adres_buf, int adres_len,
            StringBuilder tel_buf,   int tel_len,
            StringBuilder email_buf, int email_len,
            StringBuilder dogum_buf, int dogum_len);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern float ia_puan_al(string tc);

        // Eğitim
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_egitim_ekle(string tc, string okul, string bolum,
            string baslama, string bitis, float ort);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_egitim_sil(string tc, string okul, string bolum);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_egitim_sayisi(string tc);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_egitim_bilgi(string tc, int indeks,
            StringBuilder okul_buf, int okul_len,
            StringBuilder bolum_buf, int bolum_len,
            StringBuilder bas_buf, int bas_len,
            StringBuilder bit_buf, int bit_len,
            out float ort_out);

        // Deneyim
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_deneyim_ekle(string tc, string isyeri,
            string pozisyon, int yil);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_deneyim_sil(string tc, string isyeri, string pozisyon);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_deneyim_sayisi(string tc);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_deneyim_bilgi(string tc, int indeks,
            StringBuilder isyeri_buf, int isyeri_len,
            StringBuilder poz_buf,    int poz_len,
            out int yil_out);

        // BST dolaşma
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_toplam_sayisi();

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_inorder_tc(int indeks, StringBuilder tc_buf, int tc_len);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_preorder_tc(int indeks, StringBuilder tc_buf, int tc_len);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ia_postorder_tc(int indeks, StringBuilder tc_buf, int tc_len);

        // ── Şirket ──────────────────────────────────────────────────────────
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_ekle_api(int sirket_no, string ad,
            string adres, string telefon, string eposta);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_sil_api(int sirket_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_guncelle_api(int sirket_no, string yeni_ad,
            string yeni_adres, string yeni_telefon, string yeni_eposta);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_varmi(int sirket_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void sirket_bilgi_al(int sirket_no,
            StringBuilder ad_buf,  int ad_len,
            StringBuilder adr_buf, int adr_len,
            StringBuilder tel_buf, int tel_len,
            StringBuilder email_buf, int email_len);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_toplam_sayisi();

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int sirket_no_listele(int indeks);

        // ── İlan ────────────────────────────────────────────────────────────
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_ekle_api(int sirket_no, int ilan_no,
            string baslik, string aciklama, string pozisyon);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_sil_api(int sirket_no, int ilan_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_guncelle_api(int sirket_no, int ilan_no,
            string yeni_baslik, string yeni_aciklama, string yeni_poz);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_varmi(int sirket_no, int ilan_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ilan_bilgi_al(int sirket_no, int ilan_no,
            StringBuilder baslik_buf,   int baslik_len,
            StringBuilder aciklama_buf, int aciklama_len,
            StringBuilder poz_buf,      int poz_len);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_toplam_sayisi(int sirket_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_no_listele(int sirket_no, int indeks);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ilan_basvuru_sayisi(int sirket_no, int ilan_no);

        // ── Başvuru ─────────────────────────────────────────────────────────
        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int basvuru_yap(string tc, int sirket_no, int ilan_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int basvuru_varmi(string tc, int sirket_no, int ilan_no);

        [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int basvuru_bilgi(int sirket_no, int ilan_no, int indeks,
            StringBuilder tc_buf,  int tc_len,
            StringBuilder ad_buf,  int ad_len,
            StringBuilder soy_buf, int soy_len,
            out float puan_out);

        // ── Yardımcı C# sarmalayıcılar ──────────────────────────────────────
        public static (string ad, string soyad, string adres,
                        string telefon, string eposta, string dogum) IaBilgiAl(string tc)
        {
            var ad    = new StringBuilder(50);
            var soyad = new StringBuilder(50);
            var adres = new StringBuilder(200);
            var tel   = new StringBuilder(20);
            var email = new StringBuilder(100);
            var dogum = new StringBuilder(20);
            ia_bilgi_al(tc, ad, 50, soyad, 50, adres, 200, tel, 20, email, 100, dogum, 20);
            return (ad.ToString(), soyad.ToString(), adres.ToString(),
                    tel.ToString(), email.ToString(), dogum.ToString());
        }

        public static (string ad, string adres, string telefon, string eposta) SirketBilgiAl(int no)
        {
            var ad    = new StringBuilder(100);
            var adres = new StringBuilder(200);
            var tel   = new StringBuilder(20);
            var email = new StringBuilder(100);
            sirket_bilgi_al(no, ad, 100, adres, 200, tel, 20, email, 100);
            return (ad.ToString(), adres.ToString(), tel.ToString(), email.ToString());
        }

        public static (string baslik, string aciklama, string pozisyon) IlanBilgiAl(int sirketNo, int ilanNo)
        {
            var baslik   = new StringBuilder(150);
            var aciklama = new StringBuilder(500);
            var poz      = new StringBuilder(100);
            ilan_bilgi_al(sirketNo, ilanNo, baslik, 150, aciklama, 500, poz, 100);
            return (baslik.ToString(), aciklama.ToString(), poz.ToString());
        }
    }
}
