/** EL2008 Pemecahan Masalah dengan C 2020/2021
 *  Tugas Besar         : Minimisasi Logic
 *  Kelompok            : 6
 *  Nama File           : minimisasi_lib.h
 *  Deskripsi           : Header file untuk library minimisasi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** fillAllMT. Prosedur untuk mengisi nilai dari array IdxMinterm yang berisi seluruh indeks minterm yang ingin diminimisasi.
 * 
 * @param nAllMT merupakan banyaknya minterm secara keseluruhan (termasuk don't care minterm).
 * @param nVariable merupakan banyaknya variabel dalam fungsi logika yang ingin diminimisasi.
 * @param IdxMinterm merupakan array of integer yang berisi seluruh indeks minterm yang akan diminimisasi.
 * 
 */
void fillAllMT(int nAllMT, int nVariable, int *IdxMinterm);

/** fillDontCareMT. Prosedur untuk mengisi nilai dari array IdxMintermDC yang berisi seluruh indeks don't care minterm yang ingin diminimisasi.
 * 
 * @param nDontCareMT merupakan banyaknya don't care minterm.
 * @param nVariable merupakan banyaknya variabel dalam fungsi logika yang ingin diminimisasi.
 * @param IdxMintermDC merupakan array of integer yang berisi seluruh indeks don't care minterm yang akan diminimisasi.
 * 
 */
void fillDontCareMT(int nDontCareMT, int nVariable, int *IdxMintermDC);

/** DecToBin. Prosedur untuk mengubah indeks minterm yang berformat desimal menjadi indeks minterm dalam format binary.
 * 
 * @param nAllMT merupakan banyaknya minterm secara keseluruhan (termasuk don't care minterm).
 * @param nVariable merupakan banyaknya variabel dalam fungsi logika yang ingin diminimisasi.
 * @param IdxMinterm merupakan array of integer yang berisi seluruh indeks minterm yang akan diminimisasi.
 * @param MTinBinary merupakan array of array integer yang berisi seluruh indeks minterm yang akan diminimisasi dalam format binary.
 * 
 */
void DecToBin(int nAllMT, int nVariable, int *IdxMinterm, int **MTinBinary);

/** countOne. Fungsi untuk menghitung banyaknya angka 1 yang terdapat pada array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * 
 * @param binary merupakan array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * @param nDigit merupakan banyaknya digit pada bilangan biner (panjang array of integer).
 * @return count merupakan banyaknya angka 1 yang terdapat pada array of integer yang merepresentasikan bilangan dalam bentuk biner.
 * 
 */
int countOne (int *binary, int nDigit);

/** Combination. Fungsi untuk menghitung banyaknya kombinasi berdasarkan kolom yang diberikan.
 * 
 * @param n merupakan banyaknya bilangan secara keseluruhan yang akan dihitung kombinasinya (dalam kasus ini berupa banyaknya variabel yang diberikan).
 * @param ColumnNo merupakan nomor kolom yang akan menentukan banyaknya kombinasi.
 * @param k merupakan kondisi lain dalam setiap nomor kolom yang sama.
 * @return Comb merupakan banyaknya kombinasi yang dihasilkan berdasarkan input yang telah diberikan.
 * 
 */
int Combination(int n, int ColumnNo, int k);

/** IsPowerOfTwo. Fungsi untuk mengecek apakah suatu bilangan dapat direpresentasikan ke dalam bentuk 2^n.
 * 
 * @param n merupakan bilangan yang akan dicek. 
 * @return (floor(log(n)/log(2)) == (log(n)/log(2))) merupakan kondisi True/False, jika True akan memberikan hasil 1, sedangkan jika False akan memberikan hasil 0.
 * 
 */
int IsPowerOfTwo(int n);

/** Grouping. Prosedur untuk melakukan proses grouping.
 * 
 * @param nVariable merupakan banyaknya variabel dalam fungsi logika yang ingin diminimisasi.
 * @param Column merupakan column yang menyimpan hasil dari setiap proses grouping.
 * 
 */
void Grouping(int nVariable, int ****Column);

/** recursive. Prosedur untuk menyimpan seluruh nilai prime implicant yang memenuhi kriteria EPI dengan cara rekursif.
 * 
 * @param m merupakan
 * @param nSisaMT merupakan banyaknya minterm yang masih tersisa atau belum tercover dalam IdxEPI.
 * @param nSisaPI merupakan banyaknya prime implicant yang masih tersisa atau belum tercover dalam IdxEPI.
 * @param reduksiPIChart merupakan array of array integer yang berisi prime implicant hasil reduksi (yang masih tersisa).
 * @param chooseEPI merupakan array of integer untuk menyimpan nilai prime implicant yang memenuhi kriteria EPI.
 * @param potentialEPI merupakan array of array integer untuk menyimpan seluruh nilai prime implicant yang memenuhi kriteria EPI.
 * 
 */
void recursive(int m, int nSisaMT, int nSisaPI, int **reduksiPIChart, int *chooseEPI, int **potentialEPI);

/** minResult. Prosedur untuk menampilkan hasil akhir dari proses minimisasi fungsi logika.
 * 
 * @param nVariable merupakan banyaknya variabel dalam fungsi logika yang ingin diminimisasi.
 * @param nEPI merupakan jumlah minimum prime implicant yang sudah mengcover seluruh minterm.
 * @param IdxEPI merupakan array of array integer yang berisi prime implicant dalam jumlah minimum namun sudah mengcover seluruh minterm.
 * @param Column merupakan column yang menyimpan hasil dari setiap proses grouping
 * 
 */
void minResult(int nVariable, int nEPI, int **IdxEPI, int ****Column);