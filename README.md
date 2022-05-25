# Tugas Besar EL2008 Pemecahan Masalah dengan C

## Membuat Program Minimisasi Fungsi Logika

```
Oleh Kelompok 6:
1. Farhan Hakim Iskandar    / 1322007
2. Fitra Nurindra           / 13220011
3. Muhammad Daffa Daniswara	/ 13220043
```

### Tugas

1. Eksplorasi algoritma minimisasi logic
2. Rancanglah sebuah simulator untuk menggambarkan kerja sistem tersebut
    - Buat deskripsi simulasi. Deskripsikan dengan jelas: input - proses – output 
    - Lengkapi deskripsi di atas dengan algoritma dalam bentuk flowchart untuk setiap fungsi-fungsi dalam sistem
    - Buat Data Flow Diagram (DFD)
3. Berdasarkan rancangan simulasi dan algoritma yang telah dibuat pada tugas sebelumnya, buatlah program dalam bahasa pemrograman C untuk menjalankan simulasi tersebut.

### Spesifikasi Rancangan Simulasi Program yang Telah Dibuat
1. Program akan meminta _user_ untuk memberikan _input_ berupa informasi mengenai ekspresi fungsi _boolean algebra_ yang meliputi:
   -	Banyaknya variabel dari fungsi _boolean algebra_.
   -	Banyaknya minterm secara keseluruhan (termasuk _don’t care_ minterm).
   -	Banyaknya _don’t care_ minterm.
   -	Indeks minterm secara keseluruhan (termasuk _don’t care_ minterm) dalam bentuk desimal.
   -	Indeks _don’t care_ minterm dalam bentuk desimal (jika terdapat _don't care_ minterm).
2. Dalam setiap pemberian _input_ program simulasi yang dibuat diharapkan dapat memvalidasi nilai _input_ yang diberikan oleh _user_ agar program simulasi dapat berjalan dengan baik. Validasi tersebut diantaranya:
   -  Banyaknya variabel maksimal dari fungsi _boolean algebra_ hanya sebanyak 10 variabel dan jumlah variabel minimalnya adalah sebanyak 1 variabel.
   -  Banyaknya minterm keseluruhan haruslah (0 < Total Minterm ≤ 2^nVariable).
   -  Banyakya _don’t care_ minterm haruslah (0 ≤ _Don't Care_ minterm < Total Minterm).
