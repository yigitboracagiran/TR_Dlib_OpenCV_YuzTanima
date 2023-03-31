#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <filesystem>
#include <cmath>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <unistd.h> 

using namespace dlib;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;
template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;
template <int N, template <typename> class BN, int stride, typename SUBNET> 
using block  = BN<con<N, 3, 3, 1, 1,relu<BN<con<N, 3, 3, stride,stride, SUBNET>>>>>;
template <int N, typename SUBNET> using ares      = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;
template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;
using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<alevel0<alevel1<alevel2<alevel3<alevel4<max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input_rgb_image_sized<150>>>>>>>>>>>>>;

int main(void){

    // Yuz ozelliklerinin oldugu dosyayi aciyoruz...
    const char *dosya1Yolu = "/home/zeobora/kodlar/ModelEgitimi/build/kisininOzellikleri.txt";
    std::vector<std::vector<double>> matrix1;
    std::ifstream dosya1( dosya1Yolu );
    if( dosya1.is_open() ) {
        std::string dosyaninSatiri;
        while( std::getline( dosya1, dosyaninSatiri ) ) {
            std::vector<double> matrixinSatiri;
            std::stringstream ss( dosyaninSatiri );
            std::string stringSayi;
            while (std::getline( ss, stringSayi, ',' )) {
                double sayi = std::stod( stringSayi );
                matrixinSatiri.push_back( sayi );
            }
            matrix1.push_back( matrixinSatiri );
        }
        dosya1.close();
    } 
    else {
        std::cout << "Yuzlerin ozelliklerine sahip dosya acilamadi!" << std::endl;
        return 0;
    }

    //Kisi isimlerinin oldugu dosyayi aciyoruz...
    const char *dosya2Yolu = "/home/zeobora/kodlar/ModelEgitimi/build/kisilerinIsimleri.txt";
    std::ifstream dosya2( dosya2Yolu );
    std::vector<std::vector<std::string>> matrix2;
    if ( dosya2.is_open() ) {
        std::string dosyaninSatiri;
        while( std::getline( dosya2, dosyaninSatiri ) ) {
            std::vector<std::string> matrixinSatiri;
            std::stringstream ss( dosyaninSatiri );
            std::string isim;
            while (std::getline( ss, isim, ',' )) {
                matrixinSatiri.push_back( isim );
            }
            matrix2.push_back( matrixinSatiri );
        }
        dosya2.close();
    } 
    else {
        std::cout << "Egitilmis kisilerinin isimlerine sahip dosya acilamadi!" << std::endl;
        return 0;
    }

    //Model egitiminde kullanilacaklar...
    frontal_face_detector yuzTespitEdici = get_frontal_face_detector();
    shape_predictor pose_model;
    deserialize("/home/zeobora/kodlar/ModelEgitimi/models/shape_predictor_68_face_landmarks.dat") >> pose_model;
    anet_type net;
    deserialize("/home/zeobora/kodlar/ModelEgitimi/models/dlib_face_recognition_resnet_model_v1.dat") >> net;

    // Kamera acma
    cv::VideoCapture kamera( 0 );
    cv::Mat resim;
    std::cout << "Yuz Tanima Basliyor..." << std::endl;  

    int sayi=0;
    while(1){
        // std::clock_t start=clock();
        sayi++;

        //Resmi okuma ve kucultme
        kamera.read( resim );
        resize( resim, resim, cv::Size( resim.cols/2, resim.rows/2 ) );
        if(sayi%30==0){            

            //Yuzlerin konumunu belirleme
            cv_image<rgb_pixel> img( resim );
            std::vector<rectangle> yuzlerinNoktalari = yuzTespitEdici( img );
            int kisiSayisi = yuzlerinNoktalari.size();

            //Yuz tespit edildiyse, yuzu resimden kesip aliyoruz.
            if( kisiSayisi != 0 ){
                matrix<rgb_pixel> kesilmisYuz;
                std::vector<matrix<rgb_pixel>> tespitEdilenYuzler;
                for ( int j = 0 ; j < kisiSayisi ; j++ ){
                    full_object_detection sekil = pose_model( img, yuzlerinNoktalari[j] );
                    extract_image_chip( img, get_face_chip_details( sekil, 150, 0.25 ), kesilmisYuz );
                    tespitEdilenYuzler.push_back( std::move( kesilmisYuz ) );
                }

                //Kesilen yuzun ozellikleri elde ediliyor.
                std::vector<matrix<float, 0, 1>> yuzlerinOzellikleri = net( tespitEdilenYuzler );

                //Resimde tespit edilen yuzleri, elimizde olan yuzlerle karsilasitiriyoruz.
                int egitilmisKisiSayisi=matrix1.size();
                for( int i = 0 ; i < kisiSayisi ; i++ ){
                    for( int k = 0 ; k < egitilmisKisiSayisi ; k++ ){
                        
                        //Oklid Uzakligi...
                        long double uzaklik = 0;
                        for( int j = 0 ; j < yuzlerinOzellikleri[i].size() ; j++ ){
                            uzaklik += ( ( yuzlerinOzellikleri[i](j) - matrix1[k][j] ) * ( yuzlerinOzellikleri[i](j) - matrix1[k][j] ) ); 
                        }
                        uzaklik = sqrt( uzaklik );

                        if( uzaklik < 0.48 ){ //Kisi Tahmin Edildi!
                            std::cout << "Tespit Edilen Yuz: " << matrix2[0][k] << std::endl;   
                            break;
                        }
                        if( ( k+1 ) == egitilmisKisiSayisi ){
                            std::cout << "Bilinmeyen Yuz!" << std::endl;
                            break;
                        }

                    }   
                }

            }

            else{
                std::cout << "Yuz Tespit Edilemedi!" << std::endl;
            }
            std::cout << std::endl << ".................." << std::endl << std::endl;
            sayi=0;
        }

        // std::cout << ( std::clock() - start ) / (double) CLOCKS_PER_SEC << " sn." << std::endl;

        cv::imshow("Kamera", resim); 
        char key = ( cv::waitKey( 1 ) & ( 0xFF ) );
        if ( key == 'q' ){ 
            break;
        }
        

    }
        
    return 0;
}