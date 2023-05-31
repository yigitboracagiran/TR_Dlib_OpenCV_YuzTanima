# 1- Program Hakkında 

a) Program Ubuntu 20.04'te hazırlanmıştır.

b) Program 3 farklı koddan oluşmaktadır: Fotoğraf Çekme, Model Eğitme, Yüz Tanıma.

b-1) Model eğitimi için OpenCV'yi kullanarak bilgisayarın kamerası ile fotoğraf çeken bir C++17 kodu hazırlandı.

b-2) C++17, OpenCV ve Dlib ile çekilen bu fotoğrafları kullanarak modeli eğiten bir algoritma hazırlandı. Yüzlerin özelliklerini ve kişinin isimlerini iki .txt dosyasına kayededildi.

b-3) Yine C++17, OpenCV ve Dlib kullanarak, eğitilen model ile kameradan gelen canlı veriyi karşılaştıran ve kişiyi tahmin etmeye çalışan bir kod hazırlandı.

# 2- CMake'i Bilgisayara Kurma

Not: Eğer bilgisayarınızda kuruluysa, 5, 6 ve 7. adımlardaki CMakeLists.txt dosyalarındaki 1. satırlarında bulunan "cmake_minimum_required(VERSION 3.26)" versiyonu bilgisayarınızdaki versiyona göre uyarlayınız ve BU ADIMI ATLAYINIZ!

Not: Versiyonu öğrenmek için `cmake --version` komutunu çalıştırınız.

1- `git clone https://github.com/Kitware/CMake.git`

2- `cd CMake/`

3- `mkdir build`

4- `cd build/`

5- `../bootstrap`

6- `make`

7- `sudo make insall`

# 3- Dlib'i Bilgisayara Kurma

a) `git clone https://github.com/davisking/dlib.git` komutu ile source'undan indiriyoruz.

b) `cd dlib` ile indirilen dlib dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Dlib'i kuruyoruz.

# 4- OpenCV'yi Bilgisayara Kurma

a) `git clone https://github.com/opencv/opencv.git` komutu ile source'undan indiriyoruz.

b) `cd opencv` ile indirilen opencv dizininine giriyoruz.

c) `mkdir build` ile build klasörü oluşturuyoruz.

d) `cd build` ile oluşturduğumuz dizinine gidiyoruz.

e) `cmake ..` ile build klasörünün konfigürasyonu yapılıyor.

f) `sudo make install` ile de Opencv'yi kuruyoruz.

# 5- Kişilerin Fotoğraf Çekimi

a) `git clone https://github.com/yigitboracagiran/TR_Dlib_OpenCV_YuzTanima.git` komutu ile bu repo'yu indiriyoruz.

Not: Fotoğraf çekiminin yapılabilmesi için "ModelEgitimi" isimli klasörde "Dataset" isimli bir klasör bulunmalıdır. 

b) `cd ModelEgitimi` komutu ile Dataset'in olması gerektiği dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

c) `ls` komutu ile "Dataset" isimli bir klasör bulunuyor mu kontrol ediyoruz.

Not: Bu repo'yu ilk indirdiğinizde bulunmuyor, oluşturmanız gerekli.

d) `mkdir Dataset` komutu ile "Dataset" klasörü oluşturuluyor.

e) `cd ../FotografCekimi/` komutu ile fotoğraf çekimi kodunun bulunduğu dizinine gidiyoruz.

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

f) `mkdir build` ile build klasörü oluşturuyoruz.

Not: CMakeLists.txt dosyalarındaki 1. satırlarında bulunan "cmake_minimum_required(VERSION 3.26)" versiyonu bilgisayarınızdaki versiyona göre uyarlayınız. Versiyonu öğrenmek için `cmake --version` komutunu çalıştırınız.

g) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

h) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

i) `sudo make` komutu ile kodu derliyoruz.

j) `./fotografCekimi` komutu ile kodu çalıştırıyoruz.

k) Program Opencv kullanarak bilgisayarımız kamerasını açar ve ekranda gösterir. Ardından da "Kişinin Adını Giriniz: " diye bizden input alır.

Not: Kişinin klasörü daha önceden bulunuyorsa "Bu Isimde Klasor Daha Once Olusturulmus!", bulunmuyorsa "Yeni Klasor Olusturuluyor!" geri dönüşü yapılır.

l) Kişinin adının girilmesinin ardından; kamera ekranı diğer sekmelerin üstündeyken "boşluk" tuşuna basıldığında fotoğraf çeker, "q" tuşuna basılırsa kodu sonlandırır.

Not: Fotoğraf çekimi başarılı olursa "Fotograf Basariyla Olusturuldu." geri dönüşü yapılır.

Not: İstenilen sayıda fotoğraf çekilebilir ancak 1 fotoğrafla da olsa kişi tahmini başarıyla yapılmaktadır.

# 6- Model Eğitimi

a) "http://dlib.net/files/" sitesinden kodlarda "shape_predictor_68_face_landmarks.dat.bz2" dosyasını indiriyoruz.

Not: Bu repo'ya konmamasının nedeni boyutunun 25 MB'den büyük olmasıdır.

b) Dosyanın indirildiği dizine `cd Downloads/` komutu ile gidiyoruz.

c) `bunzip2 shape_predictor_68_face_landmarks.dat.bz2` komutu ile dosyadan .bz2 uzantısını kaldırıyoruz.

d) "shape_predictor_68_face_landmarks.dat" dosyasını "ModelEgitimi" klasörünün içindeki "models" klasörüne taşıyoruz.

e) `cd ModelEgitimi` komutu ile kodun bulunduğu dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

f) `mkdir build` ile build klasörü oluşturuyoruz.

Not: CMakeLists.txt dosyalarındaki 1. satırlarında bulunan "cmake_minimum_required(VERSION 3.26)" versiyonu bilgisayarınızdaki versiyona göre uyarlayınız. Versiyonu öğrenmek için `cmake --version` komutunu çalıştırınız.

g) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

h) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

i) `sudo make` komutu ile kodu derliyoruz.

j) `./modelEgitimi` komutu ile kodu çalıştırıyoruz.

Not: Aşağıdaki çıktı elde edilirse kod başarıyla çalışmıştır:

Model Egitimi Sonlandi!

Dosyaya Basariyla Yazildi!

Dosyaya Basariyla Yazildi!

# 7- Yüz Tanıma

a) `cd YuzTanima` komutu ile kodun bulunduğu dizine gidiyoruz. ( Dosya neredeyse o dizine gidiniz. )

Not: Kodu derlemeden önce koddaki dosya konumlarını kendinize göre ayarlayınız!!!

b) `mkdir build` ile build klasörü oluşturuyoruz.

Not: CMakeLists.txt dosyalarındaki 1. satırlarında bulunan "cmake_minimum_required(VERSION 3.26)" versiyonu bilgisayarınızdaki versiyona göre uyarlayınız. Versiyonu öğrenmek için `cmake --version` komutunu çalıştırınız.

c) `cmake -S . -B build/` komutu ile "CMakeLists.txt" dosyasını konfigüre ediyoruz.

d) `cd build/` komutu ile konfigüre edilen dizine gidiyoruz.

e) `sudo make` komutu ile kodu derliyoruz.

f) `./yuzTanima` komutu ile kodu çalıştırıyoruz.

g) Kamera ekranı diğer sekmelerin üstündeyken "q" tuşuna basılırsa kodu sonlandırır. 

Not: "Tespit Edilen Yüz: Kişi İsmi" veya "Yuz Tespit Edilemedi!" çıktıları elde edilmelidir.
