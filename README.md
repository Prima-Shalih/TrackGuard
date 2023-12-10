# TRACKGUARD 
Solusi pemantauan lokasi inovatif yang memadukan GPS berbasis SIM card. Dengan kemampuan portabilitas, Anda dapat membawa TrackGuard ke mana saja, bahkan tanpa koneksi WiFi. Melalui integrasi dengan ThingsBoard, lokasi dapat dipantau secara langsung, memberikan keterbatasan dan kenyamanan dalam satu perangkat canggih.

# Problem Statement

Dalam era teknologi pemantauan lokasi yang semakin canggih, banyak perangkat pemantau hadapi kendala keamanan saat terputus dari internet. Misalnya, pencurian pada benda yang dipantau dapat menyulitkan penemuan lokasi secara real-time, karena ketergantungan pada koneksi internet seperti WiFi. Masalah tambahan muncul terkait kurangnya respons darurat, mengakibatkan ketidakresponsifan dalam keadaan darurat. Oleh karena itu, inovasi diperlukan untuk meningkatkan responsivitas sistem, tidak hanya dalam memberikan lokasi real-time, tetapi juga dalam menyediakan mekanisme respons darurat yang efektif.

# Proposed solution
Proyek "TrackGuard" merancang solusi terintegrasi untuk mengatasi tantangan dalam pemantauan lokasi. Inovasi ini melibatkan:

* Modul SIM800L untuk Konsektivitas Seluler: 

    Mengatasi keterbatasan akses WiFi, memastikan konektivitas di berbagai lokasi.
* Platform Utama ESP32: 
    
    Memastikan efisiensi daya dan portabilitas, dan memungkinkan operasi yang mudah dibawa ke berbagai lokasi.
* Integrasi Modul GPS NEO-6M:
    
    Menjamin akurasi lokasi dan pemantauan real-time melalui ThingsBoard, sehingga dapat memberikan visualisasi data yang mudah dimengerti untuk pengguna.

# Hardware Design and Implementation Details
* Skematik Design
![Skematik Design](https://i.ibb.co/hdh2kkr/Skematik-Hardware-Design.png)
* Hardware Design 
![Hardware](https://i.ibb.co/vxR2Dpd/Hardware-Design.png)
**Implementation Details** 
- ESP32, Sebagai otak utama sistem, ESP32 digunakan untuk mengontrol dan mengkoordinasikan fungsi-fungsi perangkat, dalam proyek ini ESP32 memiliki peran kunci dalam mengumpulkan data dari modul GPS dan mengirimkannya ke platform ThingsBoard untuk pemantauan lokasi
- LED, Memberikan sinyal visual bahwa ESP32 sudah terhubung ke internet
- Buzzer, Memberikan sinyal auditori untuk indikasi bahwa ESP32 sudah terhubung ke internet
- Resistor, Resistor dalam rangkaian proyek "TrackGuard" dihubungkan ke buzzer dan LED dengan tujuan untuk membatasi arus listrik dan mencegah kerusakan pada kedua komponen tersebut.
- SIM800L, modul SIM800L dihubungkan ke ESP32 untuk memungkinkan ESP32 terhubung dengan jaringan seluler melalui kartu SIM. Sehingga dapat menyediakan akses jaringan seluler bagi ESP32, memungkinkan perangkat untuk berkomunikasi di lokasi tanpa ketersediaan jaringan WiFi.
- GPS NEO 6-M, Modul GPS NEO-6M diintegrasikan dengan ESP32 melalui koneksi serial, memungkinkan ESP32 untuk terus memantau dan membaca data lokasi yang diterima dari GPS.
- Battery, Menyediakan daya untuk menjalankan seluruh sistem secara mobile.
- PCB, Membantu penyusunan komponen dan mengoptimalkan koneksi antara perangkat

# Software Implementation Details

Implementasi  software melibatkan pemrograman ESP32 untuk mengumpulkan dan mentransmisikan data lokasi. Integrasi dengan platform ThingsBoard dibangun untuk memvisualisasikan data lokasi. Selain itu, fungsi LED dan buzzer diprogram untuk memberikan indikator jelas status konektivitas internet.

**Flowchart**
![Flowchart](https://i.ibb.co/Nrhsf29/Flowchart.png)

# Test Results and Performance Evaluation

Selama langkah pengujian, kami menguji fungsionalitas perangkat dengan meletakkan rangkaian pada dua tempat yang berbeda, yaitu

- Lokasi DTE 
![DTE](https://i.ibb.co/tQ1T8Gg/Testing-DTE1.png)
![DTE ThingsBoard](https://i.ibb.co/Kmh6HV4/Testing-DTE.png)
- Lokasi Pusgiwa
![PUSGIWA](https://i.ibb.co/TRv5PvH/Testing-PUSGIWA1.png)
![PUSGIWA ThingsBoard](https://i.ibb.co/7QgN5g2/Testing-PUSGIWA.png)

**Evaluation Performance**

Meskipun berukuran besar untuk perangkat GPS, "TrackGuard" tetap memberikan pemantauan lokasi yang akurat dan responsif. Dengan mesin pemrosesan ESP32 dan modul GPS NEO-6M, perangkat ini menjamin kinerja optimal. Performa sangat baik terlihat dari hasil pengujian di Departemen Teknik Elektro dan Pusgiwa. Indikator LED dan Buzzer menyala saat terhubung ke internet, menandakan integrasi perangkat keras dan lunak sukses. Koneksi dengan ThingsBoard melalui MQTT client berjalan lancar.

# Conclusion and Future Work

Dalam proyek "TrackGuard," kami berhasil menghadirkan solusi inovatif untuk pemantauan lokasi. Menggunakan ESP32, SIM800L, dan GPS NEO-6M, proyek ini memberikan pemantauan lokasi yang akurat dan responsif. Uji coba di Departemen Teknik Elektro dan Pusgiwa menunjukkan performa yang sangat baik. Meskipun berukuran cukup besar, kehandalan TrackGuard dalam memberikan pemantauan lokasi menjadi nilai tambah. Mesin pemrosesan ESP32 dan modul GPS NEO-6M menjadikan proyek ini efisien dan handal dalam menghasilkan data koordinat yang akurat. TrackGuard memberikan solusi efektif dalam pemantauan dan pelacakan, terbukti melalui uji coba dan validasi di lapangan. Antarmuka ThingsBoard memberikan pemantauan lokasi real-time yang dapat diandalkan. Evaluasi menegaskan bahwa TrackGuard berhasil memenuhi tujuan utamanya secara efektif, menjadi solusi yang holistik dan adaptif untuk pemantauan dan pengamanan dalam sistem pemantauan lokasi.