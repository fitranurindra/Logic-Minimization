/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : minimisasi_lib.c
 *  Deskripsi           : Implementation file untuk library minimisasi.
 */

#include "minimisasi_lib.h"


void fillAllMT(int nAllMT, int nVariable, int *IdxMinterm){
    int i;

    for(i = 0;i<nAllMT;i++){
        printf("Masukkan Indeks Minterm ke-%d (Dalam Urutan Meningkat): ",i+1);
        scanf("%d",&IdxMinterm[i]);

        // Memvalidasi Input Indeks Minterm
        if(i != 0 && IdxMinterm[i] <= IdxMinterm[i-1]){
            printf("Input Indeks Minterm Tidak Dalam Urutan Meningkat\n");
            printf("Masukkan Kembali Seluruh Indeks Minterm Dari Awal\n\n");
            i=-1;
        }
        else if(IdxMinterm[i]>=pow(2,nVariable) || IdxMinterm[i] < 0){
            int a = pow(2,nVariable);
            printf("\nIndeks Minterm Harus Lebih Besar Dari Sama Dengan 0 dan Lebih Kecil Dari %d\n", a);
            printf("Masukkan Kembali Seluruh Indeks Minterm Dari Awal\n\n");
            i=-1;
        }

    }


}

void fillDontCareMT(int nDontCareMT, int nVariable, int *IdxMintermDC){
    int i;

    if(nDontCareMT != 0){
        printf("\nMasukkan Indeks Minterm yang Merupakan Don't Care Minterm! \n\n");

        // Mengisi Nilai Array IdxMintermD dan Memvalidasinya
        for(i=0;i<nDontCareMT;i++){
            printf("Masukkan Indeks Don't Care Minterm ke-%d (Dalam Urutan Meningkat): ",i+1);
            scanf("%d",&IdxMintermDC[i]);

            // Memvalidasi Input Indeks Don't Care Minterm
            if(i!=0 && IdxMintermDC[i]<=IdxMintermDC[i-1]){
                printf("Input Indeks Don't Care Minterm Tidak Dalam Urutan Meningkat\n");
                printf("Masukkan Kembali Seluruh Indeks Don't Care Minterm Dari Awal\n\n");
                i=-1;
            }
            else if(IdxMintermDC[i]>=pow(2,nVariable) || IdxMintermDC[i] < 0){
                int a = pow(2,nVariable);
                printf("\nIndeks Don't Care Minterm Harus Lebih Besar Dari Sama Dengan 0 dan Lebih Kecil Dari %d\n", a);
                printf("Masukkan Kembali Seluruh Indeks Don't Care Minterm Dari Awal\n\n");
                i=-1;
            }
        }
    }
}

void DecToBin(int nAllMT, int nVariable, int *IdxMinterm, int **MTinBinary){
    int i, j, temp;

    for(i = 0; i < nAllMT; i++){
        temp = IdxMinterm[i];

        for(j = nVariable-1; j >= 0; j--){
            MTinBinary[i][j] = temp%2;
            temp = temp/2;
        }
    }
}

int countOne (int *binary, int nDigit){
    int i, count = 0;

    for(i = 0; i <= nDigit-1; i++){
        if(binary[i] == 1){
            count++;
        }
    }

    return count;
}

int Combination(int n, int ColumnNo, int k){
    int Comb, i, NtoK = 1, Kto1 = 1;

    for(i = n; i >= n-k+1-ColumnNo; i--){
        NtoK = i*NtoK;
    }

    for(i = k; i >= 1; i--){
        Kto1 = i * Kto1;
    }

    Comb = NtoK/Kto1;

    return Comb;
}

int IsPowerOfTwo(int n){
    return(floor(log(n)/log(2)) == (log(n)/log(2)));
}

void Grouping(int nVariable, int ****Column){
    int i, j, k, l, m, n, p;
    int logicCheck, position;
    int groupAble = 1; // Inisialisasi Kondisi Awal

    for(i = 0; i < nVariable + 1; i++){
        if(groupAble != 0){
            groupAble = 0;

            for(j = 0; j < nVariable - i; j++){
                m = 0;

                for(k = 0; k < Combination(nVariable,i,j); k++){
                    if(Column[i][j][k] != NULL){
                        for(l = 0; l < Combination(nVariable,i,j+1); l++){
                            if(Column[i][j+1][l] != NULL && Column[i][j+1][l][nVariable+2+i] > Column[i][j][k][nVariable+2+i]){
                                if(IsPowerOfTwo(Column[i][j+1][l][nVariable+2+i]-Column[i][j][k][nVariable+2+i])){
                                    logicCheck = 0 - i; // Digunakan untuk mengecek apakah 2 minterm terletak pada posisi yang sama (direpresentasikan dengan 2)

                                    for(n = 1; n <= i; n++){
                                        for(p = 1; p <= i; p++){
                                            if(Column[i][j+1][l][nVariable+1+n] == Column[i][j][k][nVariable+1+p]){
                                                logicCheck++;
                                            }
                                        }
                                    }

                                    if(logicCheck == 0){
                                        groupAble = 1;
                                        Column[i][j][k][nVariable+1] = 1;
                                        Column[i][j+1][l][nVariable+1] = 1;
                                        Column[i+1][j][m] = (int *)malloc((nVariable+4+i+pow(2,i+1)) * sizeof(int));

                                        for(n = 0; n <= nVariable+1+i; n++){
                                            Column[i+1][j][m][n] = Column[i][j][k][n];
                                        }

                                        Column[i+1][j][m][nVariable+3+i] = Column[i][j][k][nVariable+2+i];

                                        for(n = nVariable+4+i; n < nVariable+4+i+pow(2,i+1); n++){
                                            Column[i+1][j][m][n] = 0;
                                        }
                                        
                                        position = log((Column[i][j+1][l][nVariable+2+i]-Column[i][j][k][nVariable+2+i]))/log(2);

                                        Column[i+1][j][m][nVariable-1-position] = 2; // Terletak Pada Posisi yang Sama
                                        Column[i+1][j][m][nVariable+1] = 0;
                                        Column[i+1][j][m][nVariable+2+i] = position;

                                        for(p = 0; p < pow(2,i); p++){
                                            Column[i+1][j][m][nVariable+4+i+p] = Column[i][j][k][nVariable+3+i+p];
                                        }

                                        for(p = pow(2,i); p < pow(2,i+1); p++){
                                            Column[i+1][j][m][nVariable+4+i+p] = Column[i][j+1][l][nVariable+3+i+p-(int)pow(2,i)];
                                        }

                                        m++;
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void recursive(int m, int nSisaMT, int nSisaPI, int **reduksiPIChart, int *chooseEPI, int **potentialEPI){
    int i;
    int n = m;
    int PotEPINo = 0;

    for(chooseEPI[n] = 0; chooseEPI[n] < nSisaPI; chooseEPI[n]++){
        if(reduksiPIChart[nSisaMT-1-n][chooseEPI[n]]){
            if(n > 0){
                m = n;
                m--;
                recursive(m, nSisaMT, nSisaPI, reduksiPIChart, chooseEPI, potentialEPI);
            }

            else if(n == 0){
                for(i = 0; i < nSisaMT;i++){
                    potentialEPI[PotEPINo][i] = chooseEPI[nSisaMT-1-i];
                }
                
                PotEPINo++;
            }
        }
    }
}

void minResult(int nVariable, int nEPI, int **IdxEPI, int ****Column){
    printf("\nFungsi Logika Setelah Minimisasi Dalam Bentuk SOP:\n\n");
    printf("\n ");

    int x, y;
    for(x = 0; x < nEPI; x++){
        for(y = 0; y < nVariable; y++){
            if(Column[IdxEPI[x][0]][IdxEPI[x][1]][IdxEPI[x][2]][y] == 1){
                printf("%c", 65 + y);
            }

            else if(Column[IdxEPI[x][0]][IdxEPI[x][1]][IdxEPI[x][2]][y] == 0){
                printf("%c'", 65 + y);
            }
            
        }

        if(x < nEPI-1){
            printf(" + ");
        }
        
    }

    printf("\n\nTekan Tombol Apapun Untuk Keluar!\n\n");

    getch();
}