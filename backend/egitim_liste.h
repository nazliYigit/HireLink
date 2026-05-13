#ifndef EGITIM_LISTE_H
#define EGITIM_LISTE_H

typedef struct EgitimDugum {
    char okul_adi[100];
    char bolum[100];
    char baslama_tarihi[20];
    char bitis_tarihi[20];
    float ortalama;
    struct EgitimDugum* sonraki;
} EgitimDugum;

typedef struct {
    EgitimDugum* bas;
    int adet;
} EgitimLinkedList;

EgitimLinkedList* egitim_liste_olustur();
void egitim_ekle(EgitimLinkedList* liste, const char* okul, const char* bolum,
                 const char* baslama, const char* bitis, float ort);
int egitim_sil(EgitimLinkedList* liste, const char* okul, const char* bolum);
void egitim_listele(EgitimLinkedList* liste);
float egitim_ortalama_hesapla(EgitimLinkedList* liste);
void egitim_liste_temizle(EgitimLinkedList* liste);
void egitim_liste_yok_et(EgitimLinkedList* liste);

#endif
