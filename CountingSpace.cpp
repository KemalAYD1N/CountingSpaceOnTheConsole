
//Program Dev-C++ derleyicisi kullan�larak yaz�lm��t�r.

#include <iostream>

namespace KemalAydin{
	
	//Program Dev-C++ derleyicisi kullan�larak yaz�lm��t�r.
	
	#include <stdlib.h>
	#include <time.h>
	#include <math.h>
	
	using namespace std;	

	class MapInterface {
		
		public:
		
		virtual ~MapInterface() {}
		
		// Creates a map of given size.
		virtual void SetSize(const int width, const int height) = 0;
		
		// Returns size of map to solve.
		virtual void GetSize(int & width, int & height) = 0;
		
		// Sets border at given point.
		virtual void SetBorder(const int x, const int y) = 0;
		
		// Clears border at given point.
		virtual void ClearBorder(const int x, const int y) = 0;
		
		// Checks if there is a border at given point.
		virtual bool IsBorder(const int x, const int y) = 0;
		
		// Show map contents.
		 virtual void Show() = 0;
	};
	
	class MyMap : public MapInterface{
		
		private:
			
			int * emptyMap ;	//Harita nesnemizin adresini tutar	
			int height ;	//Harita y�ksekli�i
			int width ;	//Harita eni
		
		public:
			//constructor fonksiyonumuz ile s�n�f�m�z�n ba�lang�� durumunu belirlenir.
			MyMap(int height, int width){
				
				SetSize(height, width);	//nesne tan�mlamas� ile birlikte SetSize fonksiyonu �al���r ve harita olu�turulur.
				//Show();
			}
			
			void SetSize(const int height, const int width);
			
			void DrawLine(float x1, float y1, float x2, float y2);
			
			void GetSize(int & width, int & height);
			
			void SetBorder(const int x, const int y);
			
			void ClearBorder(const int x, const int y);
			
			bool IsBorder(const int x, const int y);
			
			void Show();
				
				
	};
	//harita �zerinde verilen 2 nokta aras�nda s�n�r �izer.
	void MyMap::DrawLine(float x1, float y1, float x2, float y2){
		
		float y;	//y = a * (x - x1) + y1;
		float a;	//e�im
		
		if( (x1 > 0 && x1 < width) && (y1 > 0 && y1 < height) ){
			
			if ( (x2 > 0 && x2 < width) && (y2 > 0 && y2 < height) ){
						
				if (x1 == x2){
					
					for (int i = y1 ; i < y2 ; i++){
						//emptyMap[int(i * width + x1)] = 1;
						//harita �zerinde verilen nokta s�n�r �izgisi yap�l�r.
						SetBorder(i, int(x1));			
					}			
				}
				else if(y1 == y2){
					
					for (int i = x1 ; i < x2 ; i++) {						
						//emptyMap[int(y1 * width + i)] = 1;
						//harita �zerinde verilen nokta s�n�r �izgisi yap�l�r.
						SetBorder(int(y1), i);
					}
				}					
				else{
					
					a = ((y2 - y1) / (x2 - x1));	//e�im hesaplan�r
					
					for (int i = x1 ; i <= x2 ; i++) {
						
						y = a * (i - x1) + y1;
						//emptyMap[ int(y)* width + i ] = 1;
						//harita �zerinde verilen nokta s�n�r �izgisi yap�l�r.
						SetBorder(int(y), i);
					}
				}
			}
			else {
				return ;
			}
		}
		else{
			return;
		}
	}
	// 1 de�erinin s�n�r, o de�erinin de alan� temsil etti�i varsay�msal bir harita olu�turulur. Random s�n�r �izgileri �izmek i�in lineNum de�i�keni �zerinde de�i�iklikler yap�n�z.
	void MyMap::SetSize(const int height, const int width) {
		
		this->height = height;
		this->width = width;
		
		this->emptyMap = new int[ width * height] ;
				
		for(int i = 0 ; i < height ; i++){
			
			for(int j = 0 ; j < width; j++){
				
				emptyMap[ i * width + j ] = 0;
			}				
		}
		
		int x1, x2, y1, y2 ;	//random �retilecek koordinat noktalar�n� tutarlar
		
		int lineNum = 20 ;	//�izilecek random s�n�r �izgi say�s�
		
		cout<< endl << "	Cizilecek random sinir cizgi sayisi ==> " << lineNum << endl;
		
		srand(time(0));
		
		
		for(int r =0 ; r < lineNum ; r++){
			
			x1 = rand() % (width) + 1;
			
			y1 = rand() % (height) + 1;
			
			x2 = rand() % (width) + 1;
			
			y2 = rand() % (height) + 1;
			
			DrawLine(x1, y1, x2, y2);	//random �retilen 2 nokta aras�nda s�n�r �izgisi �izilir.
		}
		
		DrawLine(10, 10, 40, 2);
		
		//harita �zerinde yatay s�n�r �izilir
		int j= width/2;
		for(int i = 0 ; i < height ; i++){
			
			SetBorder(i,j);
							
		}
		//dikey s�n�r �izgisi
		int i= height/2;
		for(int k = 0 ; k < width ; k++){
			
			SetBorder(i,k);
							
		}	
	}
	//harita y�kseklik ve en de�erlerini aktar�r.
	void MyMap::GetSize(int & width, int & height) {
		
		width = this->width;
		height = this->height;
	}
	//verilen adres s�n�r yap�l�r.
	void MyMap::SetBorder(const int x, const int y){
		
		this->emptyMap[ ( x * this->width ) + y] = 1;
	}
	//SetSize fonksiyonu ile �retilen haritay� konsol ekran�nda g�sterir. 
	void MyMap::Show(){
		
		for(int i = 0 ; i < this->height ; i++){
			
			for(int j = 0 ; j < this->width ; j++){
				
				cout<< "  " << this->emptyMap[ i * this->width + j ];
			}
			cout<< endl;	
		}		
	}
	
	void MyMap::ClearBorder(const int x, const int y){
		
		this->emptyMap[ ( x * this->width ) + y ] = 0;
	}
	//adresi verilen noktan�n de�eri 1 ise s�n�r(true), 0 ise alan(false) d�nderir.
	bool MyMap::IsBorder(const int x, const int y){
		 
		if(emptyMap[x * this->width + y] == 1)
			return true;
		else
			return false;
	}
	
	class ZoneCounterInterface {
		public:
			virtual ~ZoneCounterInterface() {}
			// Feeds map instance into solution class, and initialize.
			virtual void Init(MapInterface * map) = 0;
			// Counts zones in provided map, and return result.
			virtual int Solve() = 0;
	};
	
	class MyCounter : public ZoneCounterInterface{
		
		private:
			
			MapInterface *map;	//MapInterface turunde adres tutabilen de�i�ken tan�ml�yoruz.
			
		public:
			//constructor fonksiyonumuz ile s�n�f�m�z�n ba�lang�� durumunu belirlenir.
			MyCounter(MapInterface * map);
			// Feeds map instance into solution class, and initialize.
			void Init(MapInterface * map);
			// Counts zones in provided map, and return result.
			int Solve();
			//dizi i�erisndeki ayn� elemanlar� siler.
			int AyniElemanlariSil(int *dizi, int h, int w);
	};
	
	MyCounter::MyCounter(MapInterface * map){
		
		Init(map);
		
	}
	
	int MyCounter::AyniElemanlariSil(int *dizi, int h, int w){
		
		int size = w * h;	//dizi boyutu hesaplan�r
		
		//ayn� dizi elemanlar� denetlenir ve kald�r�l�r.
		for(int i = 0 ; i < size ; i++){
			
			for(int j = i + 1 ; j < size ;){
				
				if(dizi[j] == dizi[i]){	// ayn� eleman bulundu ise s�ras�yla kayma yap�l�r.
								
					for(int k = j ; k < size ; k++){
						
						dizi[k] = dizi[k + 1];
								}
						size--;	//t�m elemanlar bir sola kayd�r�ld�ktan sonra dizi boyutu 1 eksiltilir.
				}
				else{
					j++;
				}
			}
		}
		
		return size ;
	}
	
	void MyCounter::Init(MapInterface * map){
		
		this->map = map ;	//s�n�f i�erinde olu�turdu�umuz map pointer,art�k gelen map nesnesini g�sterir. 
		
		cout<< "\n	Asagida temsili olarak harita olusturulmustur.\n" << endl;
		cout<< "	1 ==> Sinir noktasini temsil eder"<< endl;
		cout<< "	0 ==> Alan noktasini temsil eder\n\n"<< endl;
		
		this->map->Show();	//harita g�sterilir.
		
		cout<< "\n\n	Toplam alan sayisi = " << Solve()<< endl;	//Solve fonksiyonu ile harita �zerindeki toplam alan ekrana bas�l�r.
	}
	
	int MyCounter::Solve(){
		
		//MyMap *m = new MyMap(50, 50);
		MapInterface *m = this->map;
		
		int h, w ;
		m -> GetSize(w, h);	//haritan�n y�kseklik ve geni�lik de�erleri al�n�r.
		int *etNum = new int[ w * h ];	//her noktan�n etiket numaras�n�n tutulmas� i�in dizi olu�turulur.
		
		for(int i =0; i < w * h ; i++){
			etNum[i] = 0;	//ba�lang�� olarak t�m etiket de�erleri 0 olarak belirlendi.
		}
		
		int iD = 0, sD = 0 ;	//noktalar�n ilk ve i�lemden sonraki etiket de�erlerini tutar
		bool dVar = true;	//etiket de�i�imini ve dolayl� olarak while d�ng�s�n� kontrol eder
		int enKucEt = 0;	//noktan�n 4 kom�usunun en k���k etiket de�eri
		int etNo = 0;	//verilecek etiket numaras�
		
		//de�i�im oldu�u s�rece d�ng� devam eder
		while(dVar == true){		
			
			dVar = false;
			
			for(int y = 1 ; y < h-1 ; y++){
				for(int x = 1 ; x < w-1 ; x++){
					
					bool bol = m->IsBorder( y, x);
					//�zerinde bulundu�umuz nokta s�n�r de�ilse ko�ula girilir
					if ( bol == 0 ){
						iD = etNum[y * w + x]; //en ba�ta noktan�n etiket de�eri al�n�r
						
						enKucEt = 0;	//ilk ba�ta en k���k etiket de�erine 0 atan�r
						
						//kom�uluklar aras�ndaki en k���k etiket numaras� bulunur
						for(int i = -1 ; i <= 1 ; i++){
							for(int j = -1 ; j <= 1 ; j++){
								
								//dikey ve yatay y�ndeki 4 kom�usuna bakar
								if( (i == 0 && j == 1) || (i == 1 && j == 0) || (i == -1 && j == 0) || (i == 0 && j == -1) ){
									
									//bak�lan nokta alan� temsil ediyorsa, kom�ular aras�ndaki en k���k etiket de�eri halen 0 ise ve bu kom�u 0 dan b�y�k etiketli ise en k���k etiket yap�l�r.
									if( etNum[(y + i) * w + (x + j)] != 0 && enKucEt == 0 && m->IsBorder( y+i, x+j) == 0){
										
										enKucEt = etNum[(y + i) * w + (x + j)];
									}
									//bak�lan kom�unun etiket de�eri en k���k de�erden k���kse ve s�f�ra e�it de�ilse en k���k etiket de�eri bu etiketle de�i�tirilir.
									else if (etNum[(y + i) * w + (x + j)] < enKucEt && etNum[(y + i) * w + (x + j)] != 0 && enKucEt != 0 && m->IsBorder( y+i, x+j) != 1){
										
										enKucEt = etNum[(y + i) * w + (x + j)];
									}
								}
							}
						}
						//en k���k etiket de�eri bulunmu� ise bu de�er noktam�z�n yeni etiket de�eridir.
						if(enKucEt != 0){
							etNum[y * w + x] = enKucEt ;
						}
						//kom�ular� aras�nda 0 dan farkl� en k���k etiket de�eri yok ise noktaya yeni etiket de�eri verilir.
						else if(enKucEt == 0 && etNum[y * w + x] < w *h){
							//cout<< "h;";
							etNo = etNo + 1 ;
							etNum[y * w + x] = etNo ;
						}
						
						sD = etNum[y * w + x];
						//toplam alanda 1 etiket bile de�i�tirilmi� ise d�ng� devam eder
						if(iD != sD){
							dVar = true ;
						}
						
					}
				}
			}if(enKucEt == 0 /*|| etNo >= w*h*/)break;	//ilk turda en k���k etiket de�eri 0 da kalm��sa d�ng�n�n devam etmesine gerek yok
		}
		/*cout<<endl<<endl;
		for(int i = 0 ; i < h ; i++){
			for(int j = 0 ; j < w ; j++){
				cout<<" "<<etNum[i * w + j];
			}
			cout<<endl;
		}*/
		
		//son olarak ayn� etiket numaralar�n� ��kard���m�z zaman geriye kalan etNum dizi boyutu toplam b�lge say�s�n� verir.
		return AyniElemanlariSil(etNum, h, w) - 1;
	}
	
	ZoneCounterInterface * getZoneCounter() {
		
		MyMap *map = new MyMap(50, 50); //map nesnesi olu�turulur. Parametre olarak, olu�turulacak haritan�n boyutlar� girilir.
		 
		return new MyCounter( map );
	}

}

int main(){
	
	KemalAydin::getZoneCounter();
	
	return 0;
}
