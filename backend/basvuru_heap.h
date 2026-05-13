#ifndef BASVURU_HEAP_H
#define BASVURU_HEAP_H

#define HEAP_MAX_KAPASITE 500

typedef struct {
    char tc[12];
    char ad[50];
    char soyad[50];
    float puan;   /* puan = ortalama*20 + toplam_deneyim_yili*10 */
} BasvuruEleman;

typedef struct {
    BasvuruEleman elemanlar[HEAP_MAX_KAPASITE];
    int boyut;
} BasvuruMaxHeap;

BasvuruMaxHeap* heap_olustur();
int  heap_ekle(BasvuruMaxHeap* heap, const char* tc, const char* ad,
               const char* soyad, float puan);
BasvuruEleman heap_max_al(BasvuruMaxHeap* heap);   /* peek - silmez */
BasvuruEleman heap_max_cikar(BasvuruMaxHeap* heap); /* pop  - siler  */
int  heap_icinde_mi(BasvuruMaxHeap* heap, const char* tc);
void heap_listele(BasvuruMaxHeap* heap);
void heap_yok_et(BasvuruMaxHeap* heap);

#endif
