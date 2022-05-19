/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : main.c
 *  Deskripsi           : Program utama untuk meminimisasi logic dengan menggunakan algoritma 
 * Quine McCluskey (Metode Tabular) berdasarkan input yang diberikan oleh user dan menampilkan hasilnya pada layar.
 */

#include "minimisasi_lib.c"

int main(){
    int NumberOfVariable, NumberOfAllMinterm, NumberOfDontCare;
    int i, j, k;

    printf("Selamat Datang di Program Minimisasi Logic.\nSilakan Masukkan Informasi Mengenai Ekspresi Logic yang Ingin Diminimisasi\n\n");

    //--Algoritma Untuk Menyimpan Input Dari User Serta Memvalidasinya--//

    printf("Masukkan Banyak Variabel: ");
    scanf("%d",&NumberOfVariable);
    
    // Memvalidasi Input Jumlah Variabel
    while(NumberOfVariable<=0){
        printf("Jumlah Variabel Harus Lebih Dari 0!!\n\n");
        printf("Masukkan Banyak Variabel: ");
        scanf("%d",&NumberOfVariable);
    }

    printf("Masukkan Banyak Minterm Keseluruhan (Termasuk Don't Care Minterm): ");
    scanf("%d",&NumberOfAllMinterm);

    // Memvalidasi Input Banyak Minterm Keseluruhan
    while(NumberOfAllMinterm>pow(2,NumberOfVariable) || NumberOfAllMinterm<=0){
        printf("Banyak Minterm Tidak Dapat Lebih Besar Dari 2^%d atau Lebih Kecil Dari 1!\n\n",NumberOfVariable);
        printf("Masukkan Banyak Minterm Keseluruhan (Termasuk Don't Care Minterm): ");
        scanf("%d",&NumberOfAllMinterm);
    }

    printf("Masukkan Banyak Don't Care Minterm: ");
    scanf("%d",&NumberOfDontCare);

    // Memvalidasi Input Banyak Don't Care Minterm
    while(NumberOfDontCare>=NumberOfAllMinterm || NumberOfDontCare<0){
        printf("Banyak Don't Care Minterm Tidak Dapat Lebih Besar Dari Sama Dengan Banyak Minterm Keseluruhan atau Lebih Kecil Dari 0!\n\n");
        printf("Masukkan Banyak Don't Care Minterm: ");
        scanf("%d",&NumberOfDontCare);
    }

    printf("\n");

    // Array of Int Untuk Menyimpan Seluruh Indeks Minterm Dalam Desimal
    int *MintermIndicesDecimal;
    MintermIndicesDecimal=(int *)malloc(NumberOfAllMinterm*sizeof(int));

    // Array of Int Untuk Menyimpan Seluruh Indeks Don't Care Minterm Dalam Desimal
    int *MintermIndicesDecimal_DontCare;
    MintermIndicesDecimal_DontCare=(int *)malloc(NumberOfDontCare*sizeof(int));

    printf("Masukkan Minterm Keseluruhan (Termasuk Don't Care Minterm)! \n\n");
    // Mengisi Nilai Array IdxMinterm dan Memvalidasinya
    for(i=0;i<NumberOfAllMinterm;i++){
        printf("Masukkan Minterm ke-%d (Dalam Urutan Meningkat): ",i+1);
        scanf("%d",&MintermIndicesDecimal[i]);

        // Memvalidasi Input Indeks Minterm
        if(i!=0 && MintermIndicesDecimal[i]<=MintermIndicesDecimal[i-1]){
            printf("Input Minterm Tidak Dalam Urutan Meningkat\n");
            printf("Masukkan Kembali Seluruh Minterm Dari Awal\n\n");
            i=-1;
        }
        else if(MintermIndicesDecimal[i]>=pow(2,NumberOfVariable) || MintermIndicesDecimal[i] < 0){
            int a = pow(2,NumberOfVariable);
            printf("\nIndeks Minterm Harus Lebih Besar Dari Sama Dengan 0 dan Lebih Kecil Dari %d\n", a);
            printf("Masukkan Kembali Seluruh Minterm Dari Awal\n\n");
            i=-1;
        }

    }

    if(NumberOfDontCare!=0){
        printf("\n\nMasukkan Minterm yang Merupakan Don't Care Minterm! \n\n");

        // Mengisi Nilai Array IdxMintermD dan Memvalidasinya
        for(i=0;i<NumberOfDontCare;i++){
            printf("Masukkan Don't Care Minterm ke-%d (Dalam Urutan Meningkat): ",i+1);
            scanf("%d",&MintermIndicesDecimal_DontCare[i]);

            // Memvalidasi Input Indeks Don't Care Minterm
            if(i!=0 && MintermIndicesDecimal_DontCare[i]<=MintermIndicesDecimal_DontCare[i-1]){
                printf("Input Don't Care Minterm Tidak Dalam Urutan Meningkat\n");
                printf("Masukkan Kembali Seluruh Don't Care Minterm Dari Awal\n\n");
                i=-1;
            }
            else if(MintermIndicesDecimal_DontCare[i]>=pow(2,NumberOfVariable) || MintermIndicesDecimal_DontCare[i] < 0){
                int a = pow(2,NumberOfVariable);
                printf("\nIndeks Don't Care Minterm Harus Lebih Besar Dari Sama Dengan 0 dan Lebih Kecil Dari %d\n", a);
                printf("Masukkan Kembali Seluruh Minterm Dari Awal\n\n");
                i=-1;
            }
        }
    }


    //--Algoritma Untuk Mengubah Indeks Desimal Minterm Menjadi Binary--//
    int **Minterm_Binary;
    Minterm_Binary=(int **)malloc(NumberOfAllMinterm*sizeof(int*));
    for(i = 0; i <= NumberOfAllMinterm; i++){
        Minterm_Binary[i]=(int *)malloc((NumberOfVariable+4)*sizeof(int));
    }

    // Mengubah Desimal Menjadi Binary
    int dividend;
    for(i = 0; i < NumberOfAllMinterm; i++){
        dividend = MintermIndicesDecimal[i];

        for(j = NumberOfVariable-1; j >= 0; j--){
            Minterm_Binary[i][j] = dividend%2;
            dividend = dividend/2;
        }
    }

    for(i=0;i<NumberOfAllMinterm;i++){
        Minterm_Binary[i][NumberOfVariable] = OneCounter(Minterm_Binary[i], NumberOfVariable); // Menghitung Banyaknya Angka 1 Dari Seluruh Minterm

        Minterm_Binary[i][NumberOfVariable + 1] = 0; // Inisialisasi Kondisi Awal Sebelum Dibentuk Grup Dengan Minterm Lain (0 Belum Dibentuk Grup, 1 Sudah Dibentuk Grup Dengan Minterm Lain)
 
        Minterm_Binary[i][NumberOfVariable + 2] = MintermIndicesDecimal[i]; // Menyimpan Indeks Minterm Dalam Bentuk Desimal

        Minterm_Binary[i][NumberOfVariable + 3] = MintermIndicesDecimal[i]; // Menyimpan Indeks Minterm Keseluruhan Setelah Dibentuk Grup
    }

    //---Mempersiapkan Kolom Awal Untuk Grouping---//
    int ****Column;
    Column=(int ****)malloc((NumberOfVariable + 1) * sizeof(int***));

    for(i = 0; i < NumberOfVariable + 1; i++){
        Column[i]=(int ***)malloc((NumberOfVariable + 1 - i) * sizeof(int**)); // Column[i] Untuk Menyimpan Grup Minterm Pada Kolom Ke-(i+1)
    }

    for(i = 0; i < NumberOfVariable + 1; i++){
        for(j = 0; j < NumberOfVariable + 1 - i; j++){
            Column[i][j] = (int**)malloc(Combination(NumberOfVariable,i,j) * sizeof(int*)); // Column[i][j] Menyimpan Seluruh Minterm Dalam Bentuk Binary Pada Kolom Ke-(i+1)
            for(k=0;k<Combination(NumberOfVariable,i,j);k++){
                Column[i][j][k] = NULL; // Column[i][j][k] Representasi Minterm Dalam Bentuk Binary Pada Kolom Ke-(i+1)
            }
        }
    }

    for(i = 0; i < NumberOfVariable + 1; i++){                // i adalah banyaknya grup sesuai banyaknya angka 1 : grup 1 (0 buah angka 1), grup 2 (1 buah angka 1), dst
        for(j = 0, k = 0; j < NumberOfAllMinterm; j++){
            if(Minterm_Binary[j][NumberOfVariable] == i){     // Membagi Grup Sesuai Dengan Banyaknya Angka 1 

                Column[0][i][k++] = Minterm_Binary[j];        // Column 0 (Berisi Minterm yang Telah Digrup Berdasarkan Banyaknya Angka 1)
            }
        }
    }

    //---Algoritma Untuk Proses Grouping Pada Kolom Selanjutnya---//
    int p, position, m;
    int Groupable = 1;
    int LogicProbe;
    int l, n;

    for(i = 0; i < NumberOfVariable + 1; i++){
        if(Groupable != 0){
            Groupable = 0;

            for(j = 0; j < NumberOfVariable - i; j++){
                m = 0;

                for(k = 0; k < Combination(NumberOfVariable,i,j); k++){
                    if(Column[i][j][k] != NULL){
                        for(l = 0; l < Combination(NumberOfVariable,i,j+1); l++){
                            if(Column[i][j+1][l] != NULL && Column[i][j+1][l][NumberOfVariable+2+i] > Column[i][j][k][NumberOfVariable+2+i]){
                                if(IsPowerOfTwo(Column[i][j+1][l][NumberOfVariable+2+i]-Column[i][j][k][NumberOfVariable+2+i])){
                                    LogicProbe = 0 - i; // Digunakan untuk mengecek apakah 2 minterm terletak pada posisi yang sama (direpresentasikan dengan 2)

                                    for(n = 1; n <= i; n++){
                                        for(p = 1; p <= i; p++){
                                            if(Column[i][j+1][l][NumberOfVariable+1+n] == Column[i][j][k][NumberOfVariable+1+p]){
                                                LogicProbe++;
                                            }
                                        }
                                    }

                                    if(LogicProbe == 0){
                                        Groupable = 1;
                                        Column[i][j][k][NumberOfVariable+1] = 1;
                                        Column[i][j+1][l][NumberOfVariable+1] = 1;
                                        Column[i+1][j][m] = (int *)malloc((NumberOfVariable+4+i+pow(2,i+1)) * sizeof(int));

                                        for(n = 0; n <= NumberOfVariable+1+i; n++){
                                            Column[i+1][j][m][n] = Column[i][j][k][n];
                                        }

                                        Column[i+1][j][m][NumberOfVariable+3+i] = Column[i][j][k][NumberOfVariable+2+i];

                                        for(n = NumberOfVariable+4+i; n < NumberOfVariable+4+i+pow(2,i+1); n++){
                                            Column[i+1][j][m][n] = 0;
                                        }
                                        
                                        position = log((Column[i][j+1][l][NumberOfVariable+2+i]-Column[i][j][k][NumberOfVariable+2+i]))/log(2);

                                        Column[i+1][j][m][NumberOfVariable-1-position] = 2; // Terletak Pada Posisi yang Sama
                                        Column[i+1][j][m][NumberOfVariable+1] = 0;
                                        Column[i+1][j][m][NumberOfVariable+2+i] = position;

                                        for(p = 0; p < pow(2,i); p++){
                                            Column[i+1][j][m][NumberOfVariable+4+i+p] = Column[i][j][k][NumberOfVariable+3+i+p];
                                        }

                                        for(p = pow(2,i); p < pow(2,i+1); p++){
                                            Column[i+1][j][m][NumberOfVariable+4+i+p] = Column[i][j+1][l][NumberOfVariable+3+i+p-(int)pow(2,i)];
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

                                    
    //---Menghitung Seberapa Banyak Setiap Indeks Desimal Muncul---//
    int *NumberCounter;
    NumberCounter=(int *)malloc(pow(2,NumberOfVariable) * sizeof(int));
    for(i = 0; i < pow(2,NumberOfVariable); i++){
        NumberCounter[i] = 0; // Inisialisasi Nilai Awal
    }
    
    //---Menyimpan Indeks Prime Implicant (Jika Terdapat Duplikat Akan Dihapus)---//
    int **PI_Index;
    PI_Index = (int **)malloc(NumberOfAllMinterm * sizeof(int*));

    for(i = 0; i < NumberOfAllMinterm; i++){
        PI_Index[i] = (int*)malloc(3 * sizeof(int));
    }

    int NumberOfPI = 0;

    for(i = 0; i < NumberOfVariable+1; i++){
        for(j = 0; j < NumberOfVariable+1-i; j++){
            for(k = 0; k < Combination(NumberOfVariable,i,j); k++){
                if(Column[i][j][k] != NULL && Column[i][j][k][NumberOfVariable+1] == 0){
                    LogicProbe = 0 - pow(2,i); // Untuk Mengecek Apakah PI Duplikat Atau Tidak

                    for(l = k-1; l >= 0; l--){
                        if(LogicProbe){
                            LogicProbe = 0 - pow(2,i);

                            for(m = 0; m < pow(2,i); m++){
                                for(n = 0; n < pow(2,i); n++){
                                    if(Column[i][j][l][NumberOfVariable+3+i+m] == Column[i][j][k][NumberOfVariable+3+i+n]){
                                        LogicProbe++;
                                    }
                                }
                            }
                        }
                    }
                    

                    if(LogicProbe != 0){
                        PI_Index[NumberOfPI][0] = i;
                        PI_Index[NumberOfPI][1] = j;
                        PI_Index[NumberOfPI][2] = k;

                        NumberOfPI++;
                        
                        for(l = 0; l < pow(2,i); l++){
                            NumberCounter[Column[i][j][k][NumberOfVariable+3+i+l]]++;
                        }
                    }           
                }
            }
        }
    }
        
    
    //---Menghapus Don't Care Minterm yang Tidak Digunakan---//
    for(i = 0; i < NumberOfDontCare; i++){
        NumberCounter[MintermIndicesDecimal_DontCare[i]] = 0;
    }

    int **EPI_Index;
    EPI_Index=(int **)malloc(NumberOfAllMinterm * sizeof(int*));
    int NumberOfEPI = 0;
    
    //---Mengambil Minterm yang Hanya Muncul Satu Kali Pada Tabel PI dan Menyimpannya Pada EPI. Kemudian Mengeset Ulang NumberCounternya Menjadi 0---//
    for(i = 0; i < pow(2,NumberOfVariable); i++){
        if(NumberCounter[i] == 1){
            for(j = 0; j < NumberOfPI; j++){
                for(k = 0; k < pow(2,PI_Index[j][0]); k++){
                    if(Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable+3+PI_Index[j][0]+k] == i){
                        EPI_Index[NumberOfEPI] = PI_Index[j];

                        for(l = 0;l < pow(2,PI_Index[j][0]); l++){
                            NumberCounter[Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable+3+PI_Index[j][0]+l]] = 0;
                        }

                        NumberOfEPI++;

                        k = pow(2,PI_Index[j][0]);
                    }
                }
            }
        }
    }
            
    //--Membuat Tabel Prime Implicant yang Sudah Tereduksi--//
    int NumberOfRemainingMT = 0;

    for(i = 0; i < pow(2,NumberOfVariable); i++){
        if(NumberCounter[i] != 0){
            NumberOfRemainingMT++;
        }
    }

    int *ReducedPIChart_X;
    ReducedPIChart_X = (int *)malloc(NumberOfRemainingMT * sizeof(int));
    for(i = 0; i < NumberOfRemainingMT; i++){
        ReducedPIChart_X[i] = -1;
    }
    
    int **ReducedPIChart_Y;
    ReducedPIChart_Y = (int **)malloc(NumberOfPI * sizeof(int*));
    for(i = 0; i < NumberOfPI; i++){
        ReducedPIChart_Y[i] = NULL;
    }

    int **ReducedPIChart;
    ReducedPIChart = (int **)malloc(NumberOfRemainingMT * sizeof(int*));

    //---Baris Pertama yang Terdiri Atas Minterm yang Masih Tersisa---//
    i = 0;
    
    for(j = 0; j < pow(2,NumberOfVariable); j++){
        if(NumberCounter[j] != 0)
        {
            ReducedPIChart_X[i] = j;
            i++;
        }
    }

    //---Kolom Pertama yang Terdiri Atas PIs yang Masih Tersisa---//
    int NumberOfRemainingPI = 0;

    for(i = 0; i < NumberOfPI; i++){
        for(j = 0; j < pow(2,PI_Index[i][0]); j++)
        {
            if(NumberCounter[Column[PI_Index[i][0]][PI_Index[i][1]][PI_Index[i][2]][NumberOfVariable+3+PI_Index[i][0]+j]] != 0){
                j = pow(2,PI_Index[i][0]);
                ReducedPIChart_Y[NumberOfRemainingPI] = PI_Index[i];
                NumberOfRemainingPI++;
            }
        }
    }
    

    //---ReducedPIChart[i][j] Menyimpan Nilai Yang Menandakan Bahwa PI('1'berarti sudah diambil, '0' berarti belum diambil)---//
    if(NumberOfRemainingPI != 0){
        for(i = 0; i < NumberOfRemainingMT; i++){
            ReducedPIChart[i] = (int *)malloc(NumberOfRemainingPI * sizeof(int));
        }

        for(i = 0; i < NumberOfRemainingMT; i++){
            for(j = 0; j < NumberOfRemainingPI; j++){
                ReducedPIChart[i][j] = 0;
            }
        }

        for(i = 0; i < NumberOfRemainingPI; i++){
            for(j = 0; j < pow(2,ReducedPIChart_Y[i][0]); j++){
                for(k = 0;k < NumberOfRemainingMT; k++){
                    if(Column[ReducedPIChart_Y[i][0]][ReducedPIChart_Y[i][1]][ReducedPIChart_Y[i][2]][NumberOfVariable+3+ReducedPIChart_Y[i][0]+j] == ReducedPIChart_X[k]){
                        ReducedPIChart[k][i] = 1;
                    }
                }
            }
        }
                
            
        //---Memilih EPIs Dari PI Chart yang Sudah Tereduksi---//
        int *For;
        For = (int *)malloc(NumberOfRemainingMT*sizeof(int)); // For[i] digunakan sebagai input untuk fungsi Recursion_For_Loop(int m)

        for(i = 0; i < NumberOfRemainingMT; i++){
            For[i] = -1;
        }

        int NumberOfPossibleEPI = 1;

        for(i = 0; i < NumberOfRemainingMT; i++){
            NumberOfPossibleEPI = NumberOfPossibleEPI * NumberCounter[ReducedPIChart_X[i]];
        }

        int **Potential_EPI;
        Potential_EPI=(int **)malloc(NumberOfPossibleEPI * sizeof(int*));

        for(i = 0; i < NumberOfPossibleEPI; i++){
            Potential_EPI[i]=(int *)malloc(NumberOfRemainingMT*sizeof(int));
        }

        Recursion_For_Loop(NumberOfRemainingMT-1, NumberOfRemainingMT, NumberOfRemainingPI, ReducedPIChart, For, Potential_EPI);

        int *NoOfPIForEPI;
        NoOfPIForEPI = (int *)malloc(NumberOfPossibleEPI * sizeof(int)); // NoOfPIForEPI[i] digunakan untuk menghitung banyaknya PI yang terdapat pada setiap kombinasi yang mengcover seluruh minterm
        
        for(i = 0; i < NumberOfPossibleEPI; i++){
            NoOfPIForEPI[i] = 0;
        }
        

        for(i = 0; i < NumberOfPossibleEPI; i++){
            for(j = 0; j < NumberOfRemainingMT; j++){
                if(Potential_EPI[i][j] != -1){
                    NoOfPIForEPI[i]++;

                    for(k = j+1; k < NumberOfRemainingMT; k++){
                        if(Potential_EPI[i][k] == Potential_EPI[i][j]){
                            Potential_EPI[i][k] = -1;
                        }
                    }
                }
            }
        }

                
        //---Mencari Kombinasi yang Hanya Membutuhkan Minterm Paling Sedikit dari PI untuk Mengcover Seluruh Minterm---//
        int MinimumNo = 0;
        for(i = 1; i < NumberOfPossibleEPI; i++){
            if(NoOfPIForEPI[i] < NoOfPIForEPI[MinimumNo]){
                MinimumNo = i;
            }
        }


        for(i = 0; i < NumberOfRemainingMT; i++){
            if(Potential_EPI[MinimumNo][i] != -1){
                EPI_Index[NumberOfEPI++] = ReducedPIChart_Y[Potential_EPI[MinimumNo][i]];
            }
        }
    }

    //---Menampilkan Hasil Akhir Minimisasi Logic dalam Bentuk SOP---//
    printf("\nFungsi Logika Setelah Minimisasi Dalam Bentuk SOP:\n\n");
    printf("\n ");
    int x, y;
    for(x = 0; x < NumberOfEPI; x++){
        for(y = 0; y < NumberOfVariable; y++)
        {
            if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 1){
                printf("%c", 65 + y);
            }

            else if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 0){
                printf("%c'", 65 + y);
            }
            
        }

        if(x < NumberOfEPI-1){
            printf(" + ");
        }
        
    }

    printf("\n\nTekan Tombol Apapun Untuk Keluar!\n");
    getch();
    return 0;
}