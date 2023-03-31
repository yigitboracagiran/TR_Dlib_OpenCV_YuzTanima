# 1- Program Hakkında 

a) Program 3 farklı koddan oluşmaktadır: Fotoğraf Çekme, Model Eğitme, Yüz Tanıma.

a-1) Model eğitimi için OpenCV'yi kullanarak bilgisayarın kamerası ile fotoğraf çeken bir C++17 kodu hazırladım.

a-2) C++17, OpenCV ve Dlib ile çekilen bu fotoğrafları kullanarak modeli eğiten bir algoritma hazırladım. Yüzlerin özelliklerini ve kişinin isimlerini iki .txt dosyasına kaydettim.

a-3) Yine C++17, OpenCV ve Dlib kullanarak, eğitilen model ile kameradan gelen canlı veriyi karşılaştıran ve kişiyi tahmin etmeye çalışan bir program hazırladım.

#  2- Dlib'i Bilgisayara Kurma

a) `git clone https://github.com/davisking/dlib.git` komutu ile source'undan indiriyoruz.

b) `cd dlib` ile indirilen dlib dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Dlib'i kuruyoruz.

# 1- OpenCV'yi Bilgisayara Kurma

a) `git clone https://github.com/opencv/opencv.git` komutu ile source'undan indiriyoruz.

b) `cd opencv` ile indirilen opencv dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Opencv'yi kuruyoruz.
