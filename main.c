#include < stdio.h > 
#include < stdlib.h > 
#include < time.h >

struct min_deger tablo_deger(int, int, int[]); 
void yazdir(int[][7], int, int); 

struct min_deger 
{
    int deger;
    int index;
};

int main() {
    int sayi, f;
    int i, n, m;
    int rastgele;
    int a, b;
    int min;

    printf("\n ****** Matris sayisini giriniz ******\n");
    scanf("%d", & sayi); /

    int dizi_boyut[2 * sayi]; // her matrisin boyutu dizi_boyut adli dizisinde tutuluyor
    long int matris[50][50][50]; 
    long int matris_ek[50][50];
    printf("Her matris icin n x m boyutu girilmelidir.\n\n");

    printf("\n A1 in matrisi icin n(satiri) giriniz:");
    scanf("%d", & n);
    dizi_boyut[0] = n;

    FILE * Dosya;
    Dosya = fopen("Matrisler.txt", "w");
    if (Dosya == NULL)
        printf("dosya acilmadi");
    else {

        for (i = 0; i < sayi; i++) {
            printf("A%d in matrisi icin m(sutunu) giriniz:", i + 1);
            scanf("%d", & m);
            dizi_boyut[2 * (i + 1) - 1] = m;
       
            fprintf(Dosya, "\n A %d matrisi (%d x %d):\n", i + 1, n, m);
            for (a = 0; a < n; a++) {
                for (b = 0; b < m; b++) {
                    rastgele = rand() % 10;
                    matris[a][b][i] = rastgele;
                    fprintf(Dosya, "[%d] ", rastgele);

                }
                fprintf(Dosya, " \n");
            }
         
            if (i + 2 <= sayi) {
                printf("A%d in matrisin n(satiri) de %d olur\n", i + 2, m);
                dizi_boyut[2 * (i + 1)] = m;
                n = m;
            }
        }
        fclose(Dosya);
    }

    long int sum, c;
    FILE * dosya2;
    dosya2 = fopen("Matrisler Carpimi.txt", "w");
    if (dosya2 == NULL)
        printf("dosya acilmadi");
    else {
        for (a = 0; a < dizi_boyut[0]; a++)
        {
            for (b = 0; b < dizi_boyut[3]; b++) {
                sum = 0;
                for (c = 0; c < dizi_boyut[1]; c++)
                    sum = sum + matris[a][c][0] * matris[c][b][1];

                matris_ek[a][b] = sum; 
                fprintf(dosya2, "[%ld] ", sum);
            }
            fprintf(dosya2, "\n");
        }

        int t, j, s;
        long int matris_ek_1[50][50] = {
            0
        };
        // tum matrislerin ardisik bir sekilde carpimi
        for (t = 2; t < sayi; t++) {
            fprintf(dosya2, " \n matris %d ile carpimi:\n", t + 1);

            for (i = 0; i < a; i++) {
                for (j = 0; j < dizi_boyut[2 * t + 1]; j++) {
                    sum = 0;
                    for (s = 0; s < b; s++) {
                        sum = sum + matris_ek[i][s] * matris[s][j][t];
                    }

                    matris_ek_1[i][j] = sum;
                    fprintf(dosya2, "[%ld] ", sum);
                }
                fprintf(dosya2, "\n");
            }
            fprintf(dosya2, "\n");
            for (a = 0; a < i; a++)
                for (b = 0; b < j; b++)
                    matris_ek[a][b] = matris_ek_1[a][b];
            a = i;
            b = j;
        }

        int toplam = 0;
    
        for (i = 2; i < 2 * sayi - 1; i++) {
            toplam = toplam + dizi_boyut[0] * dizi_boyut[i] * dizi_boyut[i + 1];
            i++;
        }
        fprintf(dosya2, " \n Brute Force ile matrislerin carpim sayisi :%d \n", toplam);
        printf(" \n Brute Force ile matrislerin carpim sayisi :%d \n", toplam);
        fclose(dosya2);
    }

    int j, k, g;
    int tablo[sayi + 1][sayi + 1]; // m matrisi tutan tablo
    int s_matris[sayi + 1][sayi + 1]; // s matrisi

    struct min_deger en_kucuk;
    for (i = 0; i < sayi; i++)
        tablo[i][i] = 0;

    for (g = 0; g < sayi; g++) {
        s_matris[0][g] = 0;
        s_matris[g][sayi] = 0;
    }

    int p[sayi + 1];
    p[0] = dizi_boyut[0];
    for (i = 0; i < sayi; i++) {
        p[i + 1] = dizi_boyut[2 * i + 1];

    }
    FILE * dosya3;
    dosya3 = fopen("Dynamic Programming.txt", "w");
    if (dosya3 == NULL)
        printf("dosya acilmadi");
    else { 
        fprintf(dosya3, "\n\n m matrisi:\n");
        printf("\n\n m matrisi:\n");
        int u;
        fprintf(dosya3, "\n");
        printf("\n");
        for (i = 1; i <= sayi; i++) {
            fprintf(dosya3, "\n");
            printf("\n");
            for (u = 0; u < i; u++) {
                fprintf(dosya3, " ---- ");
                printf(" ---- ");
            }
            for (j = i; j <= sayi; j++) {
                en_kucuk = tablo_deger(i, j, p);
                tablo[i][j] = en_kucuk.deger;
                fprintf(dosya3, " [%d]", tablo[i][j]);
                printf(" [%d]", tablo[i][j]);
                s_matris[i][j] = en_kucuk.index;
            }
            fprintf(dosya3, "\n");
            printf("\n");
        }
        // s matrisi yazdirilir
        fprintf(dosya3, "\n\n S matrisi:\n");
        printf("\n\n S matrisi:\n");

        for (i = 1; i <= sayi; i++) {
            fprintf(dosya3, "\n");
            printf("\n");
            for (u = 0; u < i; u++) {
                fprintf(dosya3, " --- ");
                printf(" ---");
            }
            for (j = i; j <= sayi; j++) {
                fprintf(dosya3, " [%d]", s_matris[i][j]);
                printf(" [%d]", s_matris[i][j]);
            }
            printf("\n");
        }
        fprintf(dosya3, "\n Dinamik programlama ile carpim sayisi: %d\n", tablo[1][sayi]);
        printf("\n Dinamik programlama ile carpim sayisi: %d\n\n", tablo[1][sayi]);

        yazdir(s_matris, 1, sayi);
        fclose(dosya3);
    }

    return 0;
}

struct min_deger tablo_deger(int i, int j, int p[]) {

    struct min_deger min;
    struct min_deger z;
    struct min_deger x;
    if (i == j) {
        min.deger = 0;
        min.index = 0;

        return min;
    } else if (j - i == 1) {
        min.deger = p[i - 1] * p[j - 1] * p[j];
        min.index = i;
        return min;
    } else {

        int k;
        struct min_deger vektor[j - i];
        for (k = i; k < j; k++) {
            z = tablo_deger(i, k, p);
            x = tablo_deger(k + 1, j, p);
            vektor[k - i].deger = z.deger + x.deger + p[i - 1] * p[k] * p[j];
        }

        int f;
        // s matrisi icin degerler hesaplanir
        min.deger = vektor[0].deger;
        for (f = 1; f < j - i; f++)
            if (min.deger > vektor[f].deger) {
                min.deger = vektor[f].deger;
                min.index = f;
            }
        min.index = min.index + i;
        return min;

    }

}

void yazdir(int matris[][7], int i, int j) 
{

    if (i == j)
        printf("A%d ", i);

    else {
        printf(" (");
        yazdir(matris, i, matris[i][j]);
        yazdir(matris, matris[i][j] + 1, j);
        printf(" )");
    }

}
