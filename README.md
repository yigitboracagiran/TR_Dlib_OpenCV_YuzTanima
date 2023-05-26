# 1- Program Hakkında 

a) Program Ubuntu 20.04'te hazırlanmıştır.

b) Program 3 farklı koddan oluşmaktadır: Fotoğraf Çekme, Model Eğitme, Yüz Tanıma.

b-1) Model eğitimi için OpenCV'yi kullanarak bilgisayarın kamerası ile fotoğraf çeken bir C++17 kodu hazırladım.

b-2) C++17, OpenCV ve Dlib ile çekilen bu fotoğrafları kullanarak modeli eğiten bir algoritma hazırladım. Yüzlerin özelliklerini ve kişinin isimlerini iki .txt dosyasına kaydettim.

b-3) Yine C++17, OpenCV ve Dlib kullanarak, eğitilen model ile kameradan gelen canlı veriyi karşılaştıran ve kişiyi tahmin etmeye çalışan bir program hazırladım.

#  2- Dlib'i Bilgisayara Kurma

a) `git clone https://github.com/davisking/dlib.git` komutu ile source'undan indiriyoruz.

b) `cd dlib` ile indirilen dlib dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Dlib'i kuruyoruz.

# 3- OpenCV'yi Bilgisayara Kurma

a) `git clone https://github.com/opencv/opencv.git` komutu ile source'undan indiriyoruz.

b) `cd opencv` ile indirilen opencv dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Opencv'yi kuruyoruz.

# 4- Kişilerin Fotoğraf Çekimi

a) `git clone https://github.com/yigitboracagiran/TR_Dlib_OpenCV_YuzTanima.git` komutu ile bu repo'yu indiriyoruz.

Not: Fotoğraf çekiminin yapılabilmesi için "ModelEgitimi" isimli klasörde "Dataset" isimli bir klasör bulunmalıdır. 

b) `cd ModelEgitimi` komutu ile Dataset'in olması gerektiği dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

c) `ls` komutu ile "Dataset" isimli bir klasör bulunuyor mu kontrol ediyoruz.

Not: Bu repo'yu ilk indirdiğinizde bulunmuyor, oluşturmanız gerekli.

d) `mkdir Dataset` komutu ile "Dataset" klasörü oluşturuluyor.

e) `cd ../FotografCekimi/` komutu ile fotoğraf çekimi kodunun bulunduğu dizinine gidiyoruz.

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

f) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

g) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

h) `make` komutu ile kodu derliyoruz.

i) `./fotografCekimi` komutu ile kodu çalıştırıyoruz.

j) Program Opencv kullanarak bilgisayarımız kamerasını açar ve ekranda gösterir. Ardından da "Kişinin Adını Giriniz: " diye bizden input alır.

Not: Kişinin klasörü daha önceden bulunuyorsa "Bu Isimde Klasor Daha Once Olusturulmus!", bulunmuyorsa "Yeni Klasor Olusturuluyor!" geri dönüşü yapılır.

k) Kişinin adının girilmesinin ardından "boşluk" tuşuna basıldığında fotoğraf çeker, "q" tuşuna basılırsa kodu sonlandırır.

Not: Fotoğraf çekimi başarılı olursa "Fotograf Basariyla Olusturuldu." geri dönüşü yapılır.

# 5- Model Eğitimi

a) `cd ModelEgitimi` komutu ile kodun bulunduğu dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

b) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

c) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

d) `sudo make` komutu ile kodu derliyoruz.

e) `./modelEgitimi` komutu ile kodu çalıştırıyoruz.

Not: Aşağıdaki çıktı elde edilirse kod başarıyla çalışmıştır:

Model Egitimi Sonlandi!

Dosyaya Basariyla Yazildi!

Dosyaya Basariyla Yazildi!

# 6- Yüz Tanıma

a) `cd YuzTanima` komutu ile kodun bulunduğu dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

b) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

c) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

d) `sudo make` komutu ile kodu derliyoruz.

e) `./yuzTanima` komutu ile kodu çalıştırıyoruz.

Not: "Tespit Edilen Yüz: Kişi İsmi" veya "Yuz Tespit Edilemedi!" çıktıları elde edilmelidir.
