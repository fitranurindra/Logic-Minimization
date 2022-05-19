/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : minimisasi_lib.c
 *  Deskripsi           : Implementation file untuk library minimisasi.
 */

#include "minimisasi_lib.h"

int OneCounter (int *binary, int NumberOfDigit){
    int i, count = 0;

    for(i = 0; i <= NumberOfDigit-1; i++){
        if(binary[i] == 1){
            count++;
        }
    }

    return count;
}

int Combination (int n, int ColumnNo, int k){
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


void Recursion_For_Loop(int m, int NumberOfRemainingMT, int NumberOfRemainingPI, int **ReducedPIChart, int *For, int **Potential_EPI){
    int i;
    int n = m;
    int PotEPINo = 0;

    for(For[n] = 0;For[n] < NumberOfRemainingPI; For[n]++){
        if(ReducedPIChart[NumberOfRemainingMT-1-n][For[n]]){
            if(n > 0){
                m = n;
                m--;
                Recursion_For_Loop(m, NumberOfRemainingMT, NumberOfRemainingPI, ReducedPIChart, For, Potential_EPI);
            }

            else if(n == 0){
                for(i = 0; i < NumberOfRemainingMT;i++){
                    Potential_EPI[PotEPINo][i] = For[NumberOfRemainingMT-1-i];
                }
                
                PotEPINo++;
            }
        }
    }
}