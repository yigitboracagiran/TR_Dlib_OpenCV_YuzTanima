#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <filesystem>
#include <opencv2/opencv.hpp>

#define MAKSIMUM_DOSYA_SAYISI 50 //Klasorde bulunabilecek tahmini maksimum dosya sayisi...

using namespace std;
namespace fs = std::filesystem; //c++17'ye ozel...

int main(){
    char *yeniKlasorAdi = NULL; //Olusturulacak klasorun ismi aliniyor
    yeniKlasorAdi = new char[20];
    cout << "Kisinin Adini Giriniz: ";
    cin >> yeniKlasorAdi;

    const char *klasor = "/home/zeobora/Desktop/dataset/"; //Klasorun eklenecegi yer belirleniyor.

    size_t uzunluk1 = strlen(yeniKlasorAdi); //Olusturulacak klasorun adi olusturuluyor. Ornek: /home/zeobora/Desktop/dataset/yeniKlasor
    size_t uzunluk2 = strlen(klasor);
    char *kisininKlasoru = NULL;
    kisininKlasoru = new char[uzunluk1+uzunluk2+2];
    strncpy(kisininKlasoru, klasor, uzunluk2+1);
    strncat(kisininKlasoru, yeniKlasorAdi, uzunluk1+1);   

    struct stat sb; //Klasorun eklenecegi yerde, yeni olusturulacak klasorun isminde bir klasor bulunuyor mu kontrol ediliyor.
    if (stat (kisininKlasoru, &sb) == 0){
        cout << "Bu Isimde Klasor Daha Once Olusturulmus!" << endl;
    }
    else{
        cout << "Yeni Klasor Olusturuluyor!" << endl;
        cout << kisininKlasoru << endl;
        if (mkdir(kisininKlasoru, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0){ 
            cout << "Klasor Basariyla Olusturuldu!" << endl;
        }
        else{
            cout << "Klasor Olusturulamadi!" << endl;
        }
    }

    char *dosyalarinKonumlari[MAKSIMUM_DOSYA_SAYISI]; //Dosyalarin konumlarini tutacak...
    char *dosyaIsimleri[MAKSIMUM_DOSYA_SAYISI]; //Dosyalarin isimlerini tutacak...
    int dosyaSayisi=0; //Sayacimiz...

    //Burada klasorun icinde kac tane resim var o hesaplaniyor. Bu sayede dosyada 10 tane resim varsa, yeni cekilen resmin adi "yeniKlasor_11.jpg" olur.
    //Not: Eger resim disinda dosyalar da varsa, sayac onlari da sayar ve resim cekilirken ona gore sayi verir.

    for (const auto & yol : fs::directory_iterator(kisininKlasoru)){ 
        dosyaIsimleri[dosyaSayisi] = new char[strlen( yol.path().c_str() ) - strlen(kisininKlasoru) + 1];
        strncpy(dosyaIsimleri[dosyaSayisi], ( yol.path().c_str() + strlen(kisininKlasoru) + 1 ), ( strlen( yol.path().c_str()) - strlen(kisininKlasoru) + 1 ));

        dosyalarinKonumlari[dosyaSayisi]=new char[strlen( yol.path().c_str() ) + 1];
        strncpy(dosyalarinKonumlari[dosyaSayisi++], ( yol.path().c_str() ), ( strlen( yol.path().c_str()) + 1 )); 
    } 

    for (int i = 0; i < dosyaSayisi; i++) { //Bellekten siliyoruz.
        delete[] dosyaIsimleri[i]; 
        delete[] dosyalarinKonumlari[i]; 
    }

    cv::Mat resim;
    cv::VideoCapture kamera( 0 );
    while(1){
        kamera.read( resim );
        char key = ( cv::waitKey( 1 ) & ( 0xFF ) );
        if ( key == ' ' ){ //Bosluk tusuna basilirsa resmi cekip belirlenen klasore kaydediyor. 
            dosyaSayisi++;
            char *resimAdi=NULL;
            resimAdi = new char[uzunluk1+uzunluk2+2+uzunluk2+1+1+4+1]; // /home/zeobora/Desktop/dataset/yeniKlasor/yeniKlasor_1.jpg
            strncpy(resimAdi, kisininKlasoru, uzunluk1+uzunluk2+1);
            strncat(resimAdi, "/", 2); 
            strncat(resimAdi, yeniKlasorAdi, uzunluk2);  
            strncat(resimAdi, "_", 2);
            string dosyaSayisiStr = std::to_string(dosyaSayisi); //String'e cevirip, char pointer'a ceviriyoruz cunku strncat foksiyonu char pointer'i parametre aliyor.
            strncat(resimAdi, dosyaSayisiStr.c_str(), 2);  
            strncat(resimAdi, ".jpg", 5);  
            cv::imwrite(resimAdi, resim);
            cout << "Fotograf Basariyla Olusturuldu." << endl;

        }
        else if ( key == 'q' ){ //q'ya basilirsa kod sonlandiriliyor.
            break;
        }
        cv::imshow("Canli Yayin", resim); 
    }

    cv::destroyAllWindows();
    delete yeniKlasorAdi; //Bellekten siliyoruz.
    delete kisininKlasoru;
    return 0;
}