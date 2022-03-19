#include <iostream>
#include <cstdlib>  // for rand/srand
#include <ctime>
using namespace std;
#define MUSTERI_SAYISI 3

class Islem{
public:
     int islemNo;
     string islem;
     float ucret;
     char* dt;
     void islemOlustur();
};


void Islem::islemOlustur(){
     srand((unsigned)time(NULL));
     int rastgeleSayi=(rand()%10)+1;
     islemNo=rastgeleSayi;
}


class Hesap{
public:
     int hesapNo;
     float bakiye;
     Islem islemler[5];
     void hesapOlustur();
     void hesapYaz();
     bool HesapVarMi(int);
};

Hesap hesap;

void Hesap::hesapOlustur(){

     srand((unsigned)time(NULL));
     int rastgeleSayi=(rand()%1000)+1;
     hesapNo=rastgeleSayi;
}

void Hesap::hesapYaz(){
     cout<<"HesapNo:"<<hesapNo<<endl<<"Hesap Bakiyesi:"<<bakiye<<endl<<endl;
}



class Musteri {
 public:
     int musteriNo;
     string musteriAd;
     string musteriSoyad;
     int musteriTipi;//bireysel:0, kurumsal:1
     Hesap hesaplar[5];
     friend ostream &operator<< (ostream&, Musteri&);
     void musteriOlustur();
     void musteriYaz();
     bool musteriVarMi(int);
     int musteriTut(int);//musteri no parametre olarak gelecek ve musteriyi bulunca indeksini dondurcek.
     int musteriHesapTut(int);
     int hesapaAitMusteriTut(int);
     void hesapIslemYaz(int);
};

Musteri musteriler[MUSTERI_SAYISI];
Musteri musteri;

ostream& operator<<(ostream &os, Musteri &m)
{
     cout<<"MusteriNo:"<<m.musteriNo<<endl<<"MusteriAd_Soyad:"<<m.musteriAd<<" "<<m.musteriSoyad<<endl<<"MusteriTipi:"<<m.musteriTipi<<endl;
     return os;
}

bool Musteri::musteriVarMi(int mNo){
     int i=0;
     for(i=0;i<MUSTERI_SAYISI;i++){
          if(mNo==musteriler[i].musteriNo){
               return true;
          }
     }
     return false;
}

void Musteri::musteriOlustur(){

     srand((unsigned)time(NULL));
     int rastgeleSayi=(rand()%10)+1;
     musteriNo=rastgeleSayi;
}

void Musteri::musteriYaz()
{
     cout<<"MusteriNo:"<<musteriNo<<endl<<"MusteriAd_Soyad:"<<musteriAd<<" "<<musteriSoyad<<endl<<"MusteriTipi:"<<musteriTipi<<endl<<endl;
}

int Musteri::musteriTut(int mNo)
{
     int i=0;
     for(i=0;i<MUSTERI_SAYISI;i++){
          if(musteriler[i].musteriNo==mNo){
               return i;
          }
     }
}

int Musteri::musteriHesapTut(int hNo)
{
     int i=0;
     int j=0;
     for(i=0;i<MUSTERI_SAYISI;i++){
          for(j=0;j<5;j++){
               if(musteriler[i].hesaplar[j].hesapNo==hNo){
                    return j;
               }
          }
     }
}

int Musteri::hesapaAitMusteriTut(int hNo)
{
     int i=0;
     int j=0;
     for(i=0;i<MUSTERI_SAYISI;i++){
          for(j=0;j<5;j++){
               if(musteriler[i].hesaplar[j].hesapNo==hNo){
                    return i;
               }
          }
     }
}

void Musteri::hesapIslemYaz(int hNo){
     int i=0;
     int mus=musteri.hesapaAitMusteriTut(hNo);
     int hesap=musteri.musteriHesapTut(hNo);
     cout<<musteriler[mus].hesaplar[hesap].hesapNo<<"No'lu hesabiniza ait hesap ozeti:"<<endl;
     for(i=0;i<5;i++){
          if(musteriler[mus].hesaplar[hesap].islemler[i].islemNo==0){
               break;
          }
          cout<<musteriler[mus].hesaplar[hesap].islemler[i].ucret<<" TL "<<musteriler[mus].hesaplar[hesap].islemler[i].islem<<" "<<musteriler[mus].hesaplar[hesap].islemler[i].dt<<endl;
     }

}

bool Hesap::HesapVarMi(int hNo){
     int i=0,j=0;
     for(i=0;i<MUSTERI_SAYISI;i++){
        for(j=0;j<5;j++){
          if(hNo==musteriler[i].hesaplar[j].hesapNo){
              return true;
          }
        }
     }
     return false;
}


int main()
{
    int mNo, mTip, hNo, hBakiye, mSayac=0, hSayac=0, aktarilacakHNo, tutar;
    string mAd, mSoyad;
    int i=0, j=0;
    int islem=0;

    while(true){
          cout<<"\t\tLUTFEN YAPMAK ISTEDIGINIZ ISLEMI TUSLAYINIZ:"<<endl<<"\t\t1-MUSTERI EKLEME"<<endl<<"\t\t2-HESAP ACTIRMA"<<endl<<"\t\t3-HESAP ISLEMLERI"<<endl<<"\t\t4-HESAP OZETI"<<endl<<"\t\t";
          cout<<"CIKMAK ICIN (0) TUSLAYINIZ."<<endl;
          cin>>islem;
          if(islem==0){
             break;
          }

          switch(islem)
          {
               case 1:
               {
                    if(mSayac>=MUSTERI_SAYISI){
                         cout<<"Yeni kayit alinmamaktadir."<<endl<<endl;
                         break;
                    }
                    else{
                    cout<<"MUSTERI EKLEME"<<endl;
                    musteriler[mSayac].musteriOlustur();
                    cout<<"Isim ve Soyad Bilgisini Giriniz:";
                    cin>>musteriler[mSayac].musteriAd>>musteriler[mSayac].musteriSoyad;
                    cout<<"Musteri Tipini Giriniz:(Bireysel:0, Kurumsal:1)";
                    cin>>musteriler[mSayac].musteriTipi;
                    while(1){
                    if(musteriler[mSayac].musteriTipi==0 || musteriler[mSayac].musteriTipi==1){
                    cout<<endl<<"Basariyla eklendi. Bilgiler;"<<endl;
                    musteriler[mSayac].musteriYaz();
                    mSayac++;
                    break;
                    }
                    else{
                        cout<<"Gecersiz Musteri Tipi!!\n";
                        cout<<"Musteri Tipini Giriniz:(bireysel:0, kurumsal:1)";
                        cin>>musteriler[mSayac].musteriTipi;

                    }
                    }
                    break;
                    }
               }

               case 2:
               {
                    cout<<"HESAP ACTIRMA"<<endl;
                    cout<<"Musteri Numaranizi Giriniz:";
                    cin>>mNo;
                    int cikis=0;
                    int hesapSayac=0;


                    if(musteri.musteriVarMi(mNo)){
                         int i=musteri.musteriTut(mNo);
                         cout<<"Hosgeldiniz "<<musteriler[i].musteriAd<<" "<<musteriler[i].musteriSoyad<<endl;
                         while(true){
                              if(hesapSayac>=5){
                                   cout<<"Daha fazla hesap acamazsiniz."<<endl<<endl;
                                   break;
                              }
                              else{
                                   musteriler[i].hesaplar[hesapSayac].hesapOlustur();
                                   cout<<endl<<"Yuklemek istediginiz bakiyeyi giriniz:";
                                   cin>>hBakiye;
                                   musteriler[i].hesaplar[hesapSayac].bakiye=hBakiye;
                                   cout<<"Hesap basari ile olusturuldu. Hesap Bilgileri;"<<endl;
                                   musteriler[i].hesaplar[hesapSayac].hesapYaz();
                                   hesapSayac++;
                              }
                              cout<<"Cikis yapmak icin (1) tuslayiniz. Isleme devam etmek icin herhangi bir rakam tuslayiniz:";
                              cin>>cikis;
                              if(cikis==1){
                                   break;
                              }
                         }
                    }
                    else{
                         cout<<"Bankamiza kayitli bir musteri degilsiniz. Lutfen oncelikle kayit olunuz."<<endl<<endl;

                    }

                    break;
               }

               case 3:
               {
                    cout<<"HESAP ISLEMLERI"<<endl;
                    int islemSayac=0;
                    cout<<"Musteri Numaranizi Giriniz:";
                    cin>>mNo;
                    if(musteri.musteriVarMi(mNo)){
                         int i=musteri.musteriTut(mNo);
                         cout<<"Hosgeldiniz "<<musteriler[i].musteriAd<<" "<<musteriler[i].musteriSoyad<<endl;
                         cout<<"Hesaplariniz:"<<endl;
                         for(j=0;j<5;j++){
                              if(musteriler[i].hesaplar[j].hesapNo==0){
                                   break;
                              }
                              cout<<musteriler[i].hesaplar[j].hesapNo<<" No'lu hesapta "<<musteriler[i].hesaplar[j].bakiye<<"TL bulunmaktadir."<<endl;
                         }
                         while(true){
                                   cout<<"Havale yapmak icin (1) Fatura Odemek icin (2) Cikis yapmak icin (0) tuslayiniz:";
                                   cin>>islem;
                                   if(islem==0){
                                        break;
                                   }
                                   if(islemSayac>5){
                                        cout<<"Daha fazla islem gerceklestiremezsiniz."<<endl;
                                        break;
                                   }
                                   switch(islem){
                                        case 1:
                                        {
                                             cout<<"PARA AKTARMA(HAVALE)"<<endl;
                                             cout<<endl<<"Para aktarmak istediginiz hesapNo'nuzu giriniz:";
                                             cin>>hNo;
                                             hesap.HesapVarMi(hNo);
                                             cout<<"Para aktarilacak olan hesapNo giriniz:";
                                             cin>>aktarilacakHNo;
                                             hesap.HesapVarMi(aktarilacakHNo);
                                             if((hesap.HesapVarMi(aktarilacakHNo)) && (hesap.HesapVarMi(hNo))){
                                             cout<<"Aktarilacak tutari giriniz:";
                                             cin>>tutar;
                                             int hesabin=musteri.musteriHesapTut(hNo);
                                             int aktarilacakHesap=musteri.musteriHesapTut(aktarilacakHNo);
                                             int aktarilacakMusteri=musteri.hesapaAitMusteriTut(aktarilacakHNo);
                                             if(tutar<=musteriler[i].hesaplar[hesabin].bakiye){
                                             musteriler[i].hesaplar[hesabin].bakiye-=tutar;
                                             musteriler[aktarilacakMusteri].hesaplar[aktarilacakHesap].bakiye+=tutar;
                                             cout<<"Hesabinizin yeni bakiyesi:"<<musteriler[i].hesaplar[hesabin].bakiye<<endl<<endl;
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].islemOlustur();
                                             time_t now = time(0);
                                             char* dataTime = ctime(&now);
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].dt=dataTime;
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].islem="Havale";
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].ucret=tutar;
                                             islemSayac++;
                                             }

                                             else{
                                                cout<<"Yetersiz Bakiye!!\n";
                                                cout<<"Hesabinizin bakiyesi:"<<musteriler[i].hesaplar[hesabin].bakiye<<endl<<endl;
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].islemOlustur();
                                                time_t now = time(0);
                                                char* dataTime = ctime(&now);
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].dt=dataTime;
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].islem="Havale(Basarisiz)";
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].ucret=tutar;
                                                islemSayac++;


                                             }
                                             }
                                             else
                                                cout<<"Hesap Bulunamadi!!\n";
                                             break;
                                        }

                                        case 2:
                                        {
                                             cout<<"ODEME YAPMA(FATURA ODEME)"<<endl;
                                             cout<<"Odeme yapmak istediginiz hesapNo giriniz:";
                                             cin>>hNo;
                                             hesap.HesapVarMi(hNo);
                                             if(hesap.HesapVarMi(hNo)){
                                             cout<<"Odeme yapilacak tutari giriniz:";
                                             cin>>tutar;
                                             int hesabin=musteri.musteriHesapTut(hNo);
                                             if(tutar<=musteriler[i].hesaplar[hesabin].bakiye){
                                             musteriler[i].hesaplar[hesabin].bakiye-=tutar;
                                             cout<<"Hesabinizin yeni bakiyesi:"<<musteriler[i].hesaplar[hesabin].bakiye<<endl<<endl;
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].islemOlustur();
                                             time_t now = time(0);
                                             char* dataTime = ctime(&now);
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].dt=dataTime;
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].islem="FaturaOdeme";
                                             musteriler[i].hesaplar[hesabin].islemler[islemSayac].ucret=tutar;
                                             islemSayac++;
                                             }
                                             else{
                                                cout<<"Yetersiz Bakiye!!\n";
                                                cout<<"Hesabinizin bakiyesi:"<<musteriler[i].hesaplar[hesabin].bakiye<<endl<<endl;
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].islemOlustur();
                                                time_t now = time(0);
                                                char* dataTime = ctime(&now);
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].dt=dataTime;
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].islem="FaturaOdeme(Basarisiz)";
                                                musteriler[i].hesaplar[hesabin].islemler[islemSayac].ucret=tutar;
                                                islemSayac++;

                                             }
                                             }
                                             else
                                                cout<<"Hesap Bulunamadi!!\n";
                                             break;
                                        }
                                   }
                         }
                    }
                    else
                    {
                         cout<<"Lutfen oncelikle bankamiza kayit olunuz."<<endl<<endl;
                    }
                    break;
               }

               case 4:
               {
                    cout<<"HESAP OZETI"<<endl;
                    cout<<"Musteri Numaranizi Giriniz:";
                    cin>>mNo;
                    if(musteri.musteriVarMi(mNo)){
                         int i=musteri.musteriTut(mNo);
                         cout<<"Hosgeldiniz"<<endl;
                         cout<<"Bilgileriniz:"<<endl<<musteriler[i]<<endl;
                         cout<<"Hesaplariniz:"<<endl;
                         for(j=0;j<5;j++){
                              if(musteriler[i].hesaplar[j].hesapNo==0){
                                   break;
                              }
                              cout<<musteriler[i].hesaplar[j].hesapNo<<" No'lu hesapta "<<musteriler[i].hesaplar[j].bakiye<<"TL bulunmaktadir."<<endl;
                         }
                         cout<<"Hesap ozeti goruntulemek istediginiz hesapNo giriniz:";
                         cin>>hNo;
                         if(hesap.HesapVarMi(hNo)){
                         musteri.hesapIslemYaz(hNo);
                         }
                         else{
                            cout<<"Hesap Bulunamadi!!\n";
                         }
                    }
                    else{
                         cout<<"Lutfen oncelikle bankamiza kayit olunuz."<<endl;
                    }
                    break;
               }
          }
    }

    cout<<"Iyi Gunler Dileriz :)"<<endl;


    return 0;
}
