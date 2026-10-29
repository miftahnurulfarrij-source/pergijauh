#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define JUMLAH 5
#define MAKS 10

char peralatan[JUMLAH][40] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int harga[JUMLAH] = {50000, 15000, 20000, 10000, 12000};

char nama[MAKS][100];
int pilihan[MAKS], unit[MAKS], hari[MAKS];
long long total[MAKS];
int jumlahTransaksi = 0;
int programBerjalan = 1;

void bersihkanInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inputAngka(char pesan[], int min, int max) {
    int angka;
    char sisa;

    while (1) {
        printf("%s", pesan);
        if (scanf("%d%c", &angka, &sisa) == 2 &&
            sisa == '\n' && angka >= min && angka <= max) {
            return angka;
        }

        printf("Input tidak valid!\n");
        bersihkanInput();
    }
}

void daftarPeralatan(void) {
    int i;

    printf("\n=== DAFTAR PERALATAN ===\n");
    for (i = 0; i < JUMLAH; i++) {
        printf("%d. %-30s Rp%d/hari\n",
               i + 1, peralatan[i], harga[i]);
    }
}

void riwayatTransaksi(void) {
    int i;
    long long pendapatan = 0;

    printf("\n=== RIWAYAT TRANSAKSI ===\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        return;
    }

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("%d. %s | %s | Rp%lld\n",
               i + 1, nama[i],
               peralatan[pilihan[i]],
               total[i]);

        pendapatan += total[i];
    }

    printf("Jumlah transaksi: %d\n", jumlahTransaksi);
    printf("Total pendapatan: Rp%lld\n", pendapatan);
}

void penyewaan(void) {
    int p, j, h, diskonPersen;
    long long subtotal, diskon;
    char lanjut;
    int i = jumlahTransaksi;

    if (jumlahTransaksi >= MAKS) {
        printf("Kapasitas transaksi sudah penuh!\n");
        return;
    }

    bersihkanInput();

    printf("Nama penyewa: ");
    fgets(nama[i], sizeof(nama[i]), stdin);
    nama[i][strcspn(nama[i], "\n")] = '\0';

    while (strlen(nama[i]) == 0) {
        printf("Nama tidak boleh kosong. Masukkan kembali: ");
        fgets(nama[i], sizeof(nama[i]), stdin);
        nama[i][strcspn(nama[i], "\n")] = '\0';
    }

    daftarPeralatan();

    p = inputAngka("Pilih peralatan [1-5]: ", 1, JUMLAH);
    j = inputAngka("Jumlah unit: ", 1, 1000000);
    h = inputAngka("Lama sewa (hari): ", 1, 1000000);

    pilihan[i] = p - 1;
    unit[i] = j;
    hari[i] = h;

    subtotal = (long long)harga[p - 1] * j * h;

    if (h >= 5)
        diskonPersen = 15;
    else if (h >= 3)
        diskonPersen = 10;
    else
        diskonPersen = 0;

    diskon = subtotal * diskonPersen / 100;
    total[i] = subtotal - diskon;

    printf("\n====== STRUK PENYEWAAN ======\n");
    printf("Nama penyewa : %s\n", nama[i]);
    printf("Peralatan    : %s\n", peralatan[p - 1]);
    printf("Harga per hari: Rp%d\n", harga[p - 1]);
    printf("Jumlah unit  : %d\n", j);
    printf("Lama sewa    : %d hari\n", h);
    printf("Subtotal     : Rp%lld\n", subtotal);
    printf("Diskon (%d%%) : Rp%lld\n", diskonPersen, diskon);
    printf("TOTAL BAYAR  : Rp%lld\n", total[i]);
    printf("=============================\n");

    jumlahTransaksi++;

    do {
        printf("Kembali ke menu utama? (Y/T): ");
        scanf(" %c", &lanjut);
        lanjut = (char)toupper((unsigned char)lanjut);

        if (lanjut != 'Y' && lanjut != 'T')
            printf("Masukkan Y atau T!\n");

    } while (lanjut != 'Y' && lanjut != 'T');

    if (lanjut == 'T') {
        printf("Terima kasih telah menggunakan Adventure Camp!\n");
        programBerjalan = 0;
    }
}

int main(void) {
    int menu;

    do {
        printf("\n====================================\n");
        printf("          ADVENTURE CAMP\n");
        printf("     SISTEM PENYEWAAN PERALATAN\n");
        printf("====================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("====================================\n");

        menu = inputAngka("Pilih menu [1-4]: ", 1, 4);

        switch (menu) {
            case 1:
                daftarPeralatan();
                break;
            case 2:
                penyewaan();
                break;
            case 3:
                riwayatTransaksi();
                break;
            case 4:
                printf("Terima kasih telah menggunakan Adventure Camp!\n");
                programBerjalan = 0;
                break;
        }

    } while (programBerjalan);

    return 0;
}5

