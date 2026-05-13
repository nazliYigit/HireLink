# Makefile - Windows (MinGW) için
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
SRCS    = egitim_liste.c deneyim_liste.c basvuru_heap.c \
          ilan.c sirket.c bst.c api.c

# Paylaşımlı kütüphane (C# P/Invoke için)
dll: $(SRCS)
	$(CC) $(CFLAGS) -shared -o backend.dll $(SRCS) -Wl,--out-implib,libbackend.a

# Konsol test uygulaması
test: $(SRCS) main_test.c
	$(CC) $(CFLAGS) -o test_app $(SRCS) main_test.c

clean:
	del /Q *.dll *.a *.exe *.o 2>nul || true
