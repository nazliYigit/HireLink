#ifndef DENEYIM_LISTE_H
#define DENEYIM_LISTE_H

typedef struct DeneyimDugum {
    char isyeri_adi[100];
    char pozisyon[100];
    int deneyim_yili;
    struct DeneyimDugum* sonraki;
} DeneyimDugum;

typedef struct {
    DeneyimDugum* bas;
    int adet;
} DeneyimLinkedList;

DeneyimLinkedList* deneyim_liste_olustur();
void deneyim_ekle(DeneyimLinkedList* liste, const char* isyeri,
                  const char* pozisyon, int yil);
int deneyim_sil(DeneyimLinkedList* liste, const char* isyeri, const char* pozisyon);
void deneyim_listele(DeneyimLinkedList* liste);
int deneyim_toplam_yil(DeneyimLinkedList* liste);
void deneyim_liste_temizle(DeneyimLinkedList* liste);
void deneyim_liste_yok_et(DeneyimLinkedList* liste);

#endif
