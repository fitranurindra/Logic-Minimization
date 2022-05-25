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
   -  Banyakya _don’t care_ minterm haruslah (0 ≤ _Don't Care_ Minterm < Total Minterm).
   -  Indeks minterm yang diberikan harus dimulai dari indeks terkecil hingga indeks terbesar (terurut membesar dan indeks minterm haruslah (0 ≤ Indeks Minterm < 2^nVariable).
   -  	Indeks _don’t care_ minterm yang diberikan harus dimulai dari indeks terkecil hingga indeks terbesar (terurut membesar) dan indeks _don’t care_ minterm haruslah (0 ≤ Indeks _Don't Care_ Minterm <2^nVariable).
  
3. Kemudian setelah input yang diberikan sudah valid, maka program simulasi akan memulai proses minimisasi fungsi logika. Proses awal yang akan dilakukan yaitu mengubah indeks minterm yang telah diberikan dalam bentuk desimal menjadi ke dalam bentuk binary. Kemudian algoritma Quine-McCluskey pun akan mulai dilakukan. Mula-mula program akan membuat sebuah tabel awal atau tabel inisialisasi yang berisi minterm yang telah dikelompokkan berdasarkan banyaknya angka 1 dalam representasi binernya. Kemudian program akan mencari setiap pasangan minterm dengan kriteria hanya memiliki 1 buah perbedaan dalam setiap pasangan tersebut. Proses reduksi tersebut akan terus dilakukan hingga diperoleh tabel _prime implicant_ yaitu tabel yang berisi pasangan minterm yang sudah tidak dapat direduksi lagi. Proses selanjutnya adalah mencari set yang terdapat di dalam _prime implicant_ yang mengandung paling sedikit kemungkinan jumlah PI namun mencakup seluruh minterm yang terdapat dalam ekspresi fungsi _boolean algebra_ (proses mencari _minimum cover_) sehingga diperoleh tabel _essential prime implicant_ yang berisi fungsi logika yang telah disederhanakan.

5. Hasil akhir atau _output_ dari simulasi program yang telah dibuat ini adalah berupa fungsi logika yang telah disederhanakan.

### Contoh Simulasi Program yang Telah Dibuat
* Case 1 <br>
Selamat Datang di Program Minimisasi Logic. <br>
Silakan Masukkan Informasi Mengenai Ekspresi Logic yang Ingin Diminimisasi <br>
**input:**<br>
Masukkan Banyak Variabel: 4 <br>
Masukkan Banyak Minterm Keseluruhan (Termasuk Don't Care Minterm): 7 <br>

