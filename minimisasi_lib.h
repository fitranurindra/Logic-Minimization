/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : minimisasi_lib.h
 *  Deskripsi           : Header file untuk library minimisasi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** OneCounter. Menghitung banyaknya angka 1 yang terdapat pada array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * 
 * @param binary array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * @param NumberOfDigit Banyaknya digit pada bilangan biner (panjang array of integer).
 * @return count banyaknya angka 1 yang terdapat pada array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * 
 */
int OneCounter(int *binary, int NumberOfDigit);

/** Combination. 
 * 
 * @param n 
 * @param ColumnNo 
 * @param k 
 * @return Comb
 * 
 */
int Combination(int n, int ColumnNo, int k);

/** IsPowerOfTwo 
 * 
 * @param n 
 * @return value
 * 
 */
int IsPowerOfTwo(int n);

/** Recursion_For_Loop 
 * 
 * @param m
 * @param NumberOfRemainingMT
 * @param NumberOfRemainingPI
 * @param ReducedPIChart
 * @param For
 * @param Potential_EPI
 * 
 */
void Recursion_For_Loop(int m, int NumberOfRemainingMT, int NumberOfRemainingPI, int **ReducedPIChart, int *For, int **Potential_EPI);