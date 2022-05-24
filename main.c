/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : main.c
 *  Deskripsi           : Program utama untuk meminimisasi logic dengan menggunakan algoritma 
 * Quine McCluskey (Metode Tabular) berdasarkan input yang diberikan oleh user dan menampilkan hasilnya pada layar.
 */

#include "minimisasi_lib.c"

int main(){
    int nVariable, nAllMT, nDontCareMT;
    int i, j, k;

    printf("Selamat Datang di Program Minimisasi Logic.\nSilakan Masukkan Informasi Mengenai Ekspresi Logic yang Ingin Diminimisasi\n\n");

    //--Algoritma Untuk Menyimpan Input Dari User Serta Memvalidasinya--//
    printf("Masukkan Banyak Variabel: ");
    scanf("%d",&nVariable);
    
    // Memvalidasi Input Jumlah Variabel
    while(nVariable<=0){
        printf("Jumlah Variabel Harus Lebih Dari 0!!\n\n");
        printf("Masukkan Banyak Variabel: ");
        scanf("%d",&nVariable);
    }

    printf("Masukkan Banyak Minterm Keseluruhan (Termasuk Don't Care Minterm): ");
    scanf("%d",&nAllMT);

    // Memvalidasi Input Banyak Minterm Keseluruhan
    while(nAllMT>pow(2,nVariable) || nAllMT<=0){
        printf("Banyak Minterm Tidak Dapat Lebih Besar Dari 2^%d atau Lebih Kecil Dari 1!\n\n",nVariable);
        printf("Masukkan Banyak Minterm Keseluruhan (Termasuk Don't Care Minterm): ");
        scanf("%d",&nAllMT);
    }

    printf("Masukkan Banyak Don't Care Minterm: ");
    scanf("%d",&nDontCareMT);

    // Memvalidasi Input Banyak Don't Care Minterm
    while(nDontCareMT >= nAllMT || nDontCareMT<0){
        printf("Banyak Don't Care Minterm Tidak Dapat Lebih Besar Dari Sama Dengan Banyak Minterm Keseluruhan atau Lebih Kecil Dari 0!\n\n");
        printf("Masukkan Banyak Don't Care Minterm: ");
        scanf("%d",&nDontCareMT);
    }

    printf("\n");

    // Array of Int Untuk Menyimpan Seluruh Indeks Minterm Dalam Desimal
    int *IdxMinterm;
    IdxMinterm=(int *)malloc(nAllMT*sizeof(int));

    printf("Masukkan Minterm Keseluruhan (Termasuk Don't Care Minterm)! \n\n");

    // Mengisi Nilai Array IdxMinterm dan Memvalidasinya
    fillAllMT(nAllMT, nVariable, IdxMinterm);

    // Array of Int Untuk Menyimpan Seluruh Indeks Don't Care Minterm Dalam Desimal
    int *IdxMintermDC;
    IdxMintermDC=(int *)malloc(nDontCareMT*sizeof(int));

    // Mengisi Nilai Array IdxMintermDC dan Memvalidasinya Jika Terdapat Don't Care Minterm
    fillDontCareMT(nDontCareMT, nVariable, IdxMintermDC);

    //--Algoritma Untuk Mengubah Indeks Desimal Minterm Menjadi Binary--//
    int **MTinBinary;

    // Alokasi Memori Untuk Variabel MTinBinary
    MTinBinary=(int **)malloc(nAllMT*sizeof(int*));

    for(i = 0; i <= nAllMT; i++){
        MTinBinary[i]=(int *)malloc((nVariable+4)*sizeof(int));
    }

    // Mengubah Desimal Menjadi Binary
    DecToBin(nAllMT, nVariable, IdxMinterm, MTinBinary);

    // Inisialisasi Nilai Dari Matriks MTinBinary
    for(i = 0; i < nAllMT; i++){
        MTinBinary[i][nVariable] = countOne(MTinBinary[i], nVariable); // Menghitung Banyaknya Angka 1 Dari Seluruh Minterm

        MTinBinary[i][nVariable + 1] = 0; // Inisialisasi Kondisi Awal Sebelum Dibentuk Grup Dengan Minterm Lain (0 Belum Dibentuk Grup, 1 Sudah Dibentuk Grup Dengan Minterm Lain)
 
        MTinBinary[i][nVariable + 2] = IdxMinterm[i]; // Menyimpan Indeks Minterm Dalam Bentuk Desimal

        MTinBinary[i][nVariable + 3] = IdxMinterm[i]; // Menyimpan Indeks Minterm Keseluruhan Setelah Dibentuk Grup
    }

    //---Mempersiapkan Kolom Awal Untuk Grouping---//
    int ****Column;

    // Alokasi Memory Serta Inisialisasi Nilai Variabel Column
    Column = (int ****)malloc((nVariable + 1) * sizeof(int***));

    for(i = 0; i < nVariable + 1; i++){
        Column[i] = (int ***)malloc((nVariable + 1 - i) * sizeof(int**)); // Column[i] Untuk Menyimpan Grup Minterm Pada Kolom Ke-(i+1)
    }

    for(i = 0; i < nVariable + 1; i++){
        for(j = 0; j < nVariable + 1 - i; j++){
            Column[i][j] = (int**)malloc(Combination(nVariable,i,j) * sizeof(int*)); // Column[i][j] Menyimpan Seluruh Minterm Dalam Bentuk Binary Pada Kolom Ke-(i+1)
            for(k = 0; k < Combination(nVariable,i,j); k++){
                Column[i][j][k] = NULL; // Column[i][j][k] Representasi Minterm Dalam Bentuk Binary Pada Kolom Ke-(i+1)
            }
        }
    }

    for(i = 0; i < nVariable + 1; i++){                // i adalah banyaknya grup sesuai banyaknya angka 1 : grup 1 (0 buah angka 1), grup 2 (1 buah angka 1), dst
        for(j = 0, k = 0; j < nAllMT; j++){
            if(MTinBinary[j][nVariable] == i){         // Membagi Grup Sesuai Dengan Banyaknya Angka 1 
                Column[0][i][k++] = MTinBinary[j];     // Column 0 (Berisi Minterm yang Telah Digrup Berdasarkan Banyaknya Angka 1)
            }
        }
    }

    //---Algoritma Untuk Proses Grouping Pada Kolom Selanjutnya---//

    // Proses Membuat Group Dengan Metode Tabular (Quine-McCluskey)
    Grouping(nVariable, Column);

    //---Menghitung Seberapa Banyak Setiap Indeks Desimal Muncul---//
    int *DecIdxCount;
    
    // Alokasi Memory Serta Inisialisasi Nilai Variabel DecIdxCount
    DecIdxCount=(int *)malloc(pow(2,nVariable) * sizeof(int));
    for(i = 0; i < pow(2,nVariable); i++){
        DecIdxCount[i] = 0; // Inisialisasi Nilai Awal
    }
    
    //---Menyimpan Indeks Prime Implicant (Jika Terdapat Duplikat Akan Dihapus)---//
    int **IdxPI;

    // Alokasi Memory  Variabel IdxPI
    IdxPI = (int **)malloc(nAllMT * sizeof(int*));
    for(i = 0; i < nAllMT; i++){
        IdxPI[i] = (int*)malloc(3 * sizeof(int));
    }

    int nPI = 0; // Inisialisasi Kondisi Awal
    int logicCheck;
    int l, m, n;

    // Mengisi Nilai Matriks/Tabel IdxPI
    for(i = 0; i < nVariable+1; i++){
        for(j = 0; j < nVariable+1-i; j++){
            for(k = 0; k < Combination(nVariable,i,j); k++){
                if(Column[i][j][k] != NULL && Column[i][j][k][nVariable+1] == 0){
                    logicCheck = 0 - pow(2,i); // Untuk Mengecek Apakah PI Duplikat Atau Tidak

                    for(l = k-1; l >= 0; l--){
                        if(logicCheck){
                            logicCheck = 0 - pow(2,i);

                            for(m = 0; m < pow(2,i); m++){
                                for(n = 0; n < pow(2,i); n++){
                                    if(Column[i][j][l][nVariable+3+i+m] == Column[i][j][k][nVariable+3+i+n]){
                                        logicCheck++;
                                    }
                                }
                            }
                        }
                    }
                    
                    if(logicCheck != 0){
                        IdxPI[nPI][0] = i;
                        IdxPI[nPI][1] = j;
                        IdxPI[nPI][2] = k;

                        nPI++;
                        
                        for(l = 0; l < pow(2,i); l++){
                            DecIdxCount[Column[i][j][k][nVariable+3+i+l]]++;
                        }
                    }           
                }
            }
        }
    }
     
    
    //---Menghapus Don't Care Minterm yang Tidak Digunakan---//
    for(i = 0; i < nDontCareMT; i++){
        DecIdxCount[IdxMintermDC[i]] = 0;
    }

    int **IdxEPI;

    // Alokasi Memory  Variabel IdxEPI
    IdxEPI=(int **)malloc(nAllMT * sizeof(int*));

    int nEPI = 0; // Inisialisasi Nilai Awal
    
    //---Mengambil Minterm yang Hanya Muncul Satu Kali Pada Tabel PI dan Menyimpannya Pada EPI. Kemudian Mengeset Ulang DecIdxCountnya Menjadi 0---//
    for(i = 0; i < pow(2,nVariable); i++){
        if(DecIdxCount[i] == 1){
            for(j = 0; j < nPI; j++){
                for(k = 0; k < pow(2,IdxPI[j][0]); k++){
                    if(Column[IdxPI[j][0]][IdxPI[j][1]][IdxPI[j][2]][nVariable+3+IdxPI[j][0]+k] == i){
                        IdxEPI[nEPI] = IdxPI[j];

                        for(l = 0; l < pow(2,IdxPI[j][0]); l++){
                            DecIdxCount[Column[IdxPI[j][0]][IdxPI[j][1]][IdxPI[j][2]][nVariable+3+IdxPI[j][0]+l]] = 0;
                        }

                        nEPI++;

                        k = pow(2,IdxPI[j][0]);
                    }
                }
            }
        }
    }

    //--Membuat Tabel Prime Implicant yang Sudah Tereduksi--//
    int nSisaMT = 0;

    for(i = 0; i < pow(2,nVariable); i++){
        if(DecIdxCount[i] != 0){
            nSisaMT++;
        }
    }

    int *reduksiPIChartX;

    // Alokasi Memory Serta Inisialisasi Nilai Variabel reduksiPIChartX
    reduksiPIChartX = (int *)malloc(nSisaMT * sizeof(int));
    for(i = 0; i < nSisaMT; i++){
        reduksiPIChartX[i] = -1;
    }
    
    int **reduksiPIChartY;

    // Alokasi Memory Serta Inisialisasi Nilai Variabel reduksiPIChartY
    reduksiPIChartY = (int **)malloc(nPI * sizeof(int*));
    for(i = 0; i < nPI; i++){
        reduksiPIChartY[i] = NULL;
    }

    int **reduksiPIChart;

    // Alokasi Memory Variabel reduksiPIChart
    reduksiPIChart = (int **)malloc(nSisaMT * sizeof(int*));

    //---Baris Pertama yang Terdiri Atas Minterm yang Masih Tersisa---//
    for(i = 0, j = 0; j < pow(2,nVariable); j++){
        if(DecIdxCount[j] != 0)
        {
            reduksiPIChartX[i] = j;
            i++;
        }
    }

    //---Kolom Pertama yang Terdiri Atas Prime Implicant yang Masih Tersisa---//
    int nSisaPI = 0;

    for(i = 0; i < nPI; i++){
        for(j = 0; j < pow(2,IdxPI[i][0]); j++){
            if(DecIdxCount[Column[IdxPI[i][0]][IdxPI[i][1]][IdxPI[i][2]][nVariable+3+IdxPI[i][0]+j]] != 0){
                j = pow(2,IdxPI[i][0]);
                reduksiPIChartY[nSisaPI] = IdxPI[i];
                nSisaPI++;
            }
        }
    }
    
    //---reduksiPIChart[i][j] Menyimpan Nilai Yang Menandakan Bahwa PI ('1'berarti sudah diambil, '0' berarti belum diambil)---//
    if(nSisaPI != 0){
        for(i = 0; i < nSisaMT; i++){
            reduksiPIChart[i] = (int *)malloc(nSisaPI * sizeof(int));
        }

        for(i = 0; i < nSisaMT; i++){
            for(j = 0; j < nSisaPI; j++){
                reduksiPIChart[i][j] = 0;
            }
        }

        for(i = 0; i < nSisaPI; i++){
            for(j = 0; j < pow(2, reduksiPIChartY[i][0]); j++){
                for(k = 0;k < nSisaMT; k++){
                    if(Column[reduksiPIChartY[i][0]][reduksiPIChartY[i][1]][reduksiPIChartY[i][2]][nVariable+3+reduksiPIChartY[i][0]+j] == reduksiPIChartX[k]){
                        reduksiPIChart[k][i] = 1;
                    }
                }
            }
        }
                
            
        //---Memilih EPI Dari PI Chart yang Sudah Tereduksi---//
        int *chooseEPI;
        
        // Alokasi Memory Serta Inisialisasi Nilai Variabel chooseEPI
        chooseEPI = (int *)malloc(nSisaMT*sizeof(int)); // chooseEPI[i] digunakan sebagai input untuk fungsi Recursion_For_Loop
        for(i = 0; i < nSisaMT; i++){
            chooseEPI[i] = -1;
        }

        int nPossibleEPI = 1;

        for(i = 0; i < nSisaMT; i++){
            nPossibleEPI = nPossibleEPI * DecIdxCount[reduksiPIChartX[i]];
        }

        int **potentialEPI;

        // Alokasi Memory Serta Inisialisasi Nilai Variabel potentialEPI
        potentialEPI=(int **)malloc(nPossibleEPI * sizeof(int*));
        for(i = 0; i < nPossibleEPI; i++){
            potentialEPI[i] = (int *)malloc(nSisaMT*sizeof(int));
        }

        recursive(nSisaMT-1, nSisaMT, nSisaPI, reduksiPIChart, chooseEPI, potentialEPI);

        int *NoOfPIForEPI;

        // Alokasi Memory Serta Inisialisasi Nilai Variabel NoOfPIForEPI
        NoOfPIForEPI = (int *)malloc(nPossibleEPI * sizeof(int)); // NoOfPIForEPI[i] digunakan untuk menghitung banyaknya PI yang terdapat pada setiap kombinasi yang mengcover seluruh minterm
        for(i = 0; i < nPossibleEPI; i++){
            NoOfPIForEPI[i] = 0;
        }
        
        for(i = 0; i < nPossibleEPI; i++){
            for(j = 0; j < nSisaMT; j++){
                if(potentialEPI[i][j] != -1){
                    NoOfPIForEPI[i]++;

                    for(k = j+1; k < nSisaMT; k++){
                        if(potentialEPI[i][k] == potentialEPI[i][j]){
                            potentialEPI[i][k] = -1;
                        }
                    }
                }
            }
        }

        //---Mencari Kombinasi yang Hanya Membutuhkan Minterm Paling Sedikit dari PI untuk Mengcover Seluruh Minterm---//
        int minComb = 0;
        for(i = 1; i < nPossibleEPI; i++){
            if(NoOfPIForEPI[i] < NoOfPIForEPI[minComb]){
                minComb = i;
            }
        }

        for(i = 0; i < nSisaMT; i++){
            if(potentialEPI[minComb][i] != -1){
                IdxEPI[nEPI++] = reduksiPIChartY[potentialEPI[minComb][i]];
            }
        }
    }

    //---Menampilkan Hasil Akhir Minimisasi Logic dalam Bentuk SOP---//
    minResult(nVariable, nEPI, IdxEPI, Column);

    return 0;
}