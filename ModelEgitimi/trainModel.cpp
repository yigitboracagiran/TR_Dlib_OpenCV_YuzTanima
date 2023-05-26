#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <filesystem>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

#define MAX_KISI_SAYISI 50
using namespace dlib;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET> 
using block  = BN<con<N, 3, 3, 1, 1,relu<BN<con<N, 3, 3, stride,stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<alevel0<alevel1<alevel2<alevel3<alevel4<max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input_rgb_image_sized<150>>>>>>>>>>>>>;

char *names[MAX_KISI_SAYISI];
char *resimYollari[MAX_KISI_SAYISI];

int main(void){
    //Resimleri ve Kisi Isimlerini Okuma
    int kisiSayisi = 0;
    int resimSayisi = 0;
    const char *dosyaYolu = "/home/zeobora/Desktop/ModelEgitimi/dataset/";

    for (const auto &entry : std::filesystem::directory_iterator(dosyaYolu)){
        for ( const auto &entry1 : std::filesystem::directory_iterator( entry.path() ) ){  
            resimYollari[resimSayisi] = new char[ strlen( entry1.path().c_str() ) + 1 ];
            strncpy( resimYollari[resimSayisi++], ( entry1.path().c_str() ), ( strlen( entry1.path().c_str() ) + 1 ) );
            names[kisiSayisi] = new char[ strlen( entry.path().c_str() ) - strlen( dosyaYolu ) + 1 ];
            strncpy( names[kisiSayisi++], ( entry.path().c_str() + strlen(dosyaYolu) ), ( strlen( entry.path().c_str() ) - strlen( dosyaYolu ) + 1 ) );
        }
    }
    
    std::cout << "Dosyalarin Konumlari: " << std::endl; //Dosyalarin konumlarini ekrana yazdiriyoruz.
    for( int i = 0 ; i < resimSayisi ; i++ ){
        std::cout << resimYollari[i] << std::endl;
    }

    std::cout << "Dosya Isimleri: "; //Dosyalarin isimlerini ekrana yazdiriyoruz.
    for ( int i = 0 ; i < kisiSayisi ; i++ ){
        std::cout << names[i] << " " << std::endl;
    }
    
    //Model Egitiminde Kullanilacaklar
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor pose_model;
    deserialize("/home/zeobora/Desktop/ModelEgitimi/models/shape_predictor_68_face_landmarks.dat") >> pose_model;
    anet_type net;
    deserialize("/home/zeobora/Desktop/ModelEgitimi/models/dlib_face_recognition_resnet_model_v1.dat") >> net;
    cv::Mat image, imageResize, rgb;
    std::cout << "Model Egitimi Basliyor..." << std::endl;
    std::vector<matrix<rgb_pixel>> faces;

    //Bir Resmin Suresi Icin
    std::clock_t start;
    double duration;

    //Model Egitimi
    for (int i = 0 ; i < resimSayisi ; i++){
        start = std::clock(); 
        image = cv::imread( resimYollari[i], cv::IMREAD_GRAYSCALE );
        resize(image, image, cv::Size(image.cols/2, image.rows/2));
        cv_image<unsigned char> img(image);
        std::vector<rectangle> faceRects = detector(img);
        std::vector<full_object_detection> shapes;
        matrix<rgb_pixel> face_chip;
        full_object_detection shape = pose_model(img, faceRects[0]);
        shapes.push_back(shape); 
        extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
        faces.push_back(std::move(face_chip));
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout << duration << " saniye surdu." << std::endl;
        std::cout << i+1 << "/" << resimSayisi << std::endl;
    }
    std::vector<matrix<float, 0, 1>> face_descriptors = net(faces);
    std::cout << "Model Egitimi Sonlandi!" << std::endl;

    //Dosyaya Yazma
    std::ofstream file1("kisininOzellikleri.txt");
    if (file1.is_open()){
        for (int i = 0 ; i < face_descriptors.size() ; i++) {
            for (int j = 0 ; j < face_descriptors[i].size() ; j++) {
                if( j == ( face_descriptors[i].size() - 1 ) ){
                    file1 << face_descriptors[i](j);
                    break;
                }
                file1 << face_descriptors[i](j) << ",";
            }
            file1 << std::endl;
        }
        
        file1.close();
        std::cout << "Dosyaya Basariyla Yazildi!" << std::endl;
    }
    else{
        std::cout << "Dosyaya Yazma Basarisiz!" << std::endl;
    }
    file1.close();
    
    std::ofstream file2("kisilerinIsimleri.txt");
    if (file2.is_open()){
        for (int i = 0 ; i < kisiSayisi ; i++) {
            if( i == ( kisiSayisi - 1 ) ){
                file2 << names[i];
                break;
            }
            file2 << names[i] << ",";
        }
        file2.close();
        std::cout << "Dosyaya Basariyla Yazildi!" << std::endl;
    }
    else{
        std::cout << "Dosyaya Yazma Basarisiz!" << std::endl;
    }
    file2.close();

    //Bellegi Temizleme
    for (int i = 0; i < kisiSayisi; i++) {
        delete[] names[i]; 
        delete[] resimYollari[i]; 
    }

    cv::destroyAllWindows();
    return 0;

}
