
//Program Dev-C++ derleyicisi kullanýlarak yazýlmýþtýr.

#include <iostream>

namespace KemalAydin{
	
	//Program Dev-C++ derleyicisi kullanýlarak yazýlmýþtýr.
	
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
			int height ;	//Harita yüksekliði
			int width ;	//Harita eni
		
		public:
			//constructor fonksiyonumuz ile sýnýfýmýzýn baþlangýç durumunu belirlenir.
			MyMap(int height, int width){
				
				SetSize(height, width);	//nesne tanýmlamasý ile birlikte SetSize fonksiyonu çalýþýr ve harita oluþturulur.
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
	//harita üzerinde verilen 2 nokta arasýnda sýnýr çizer.
	void MyMap::DrawLine(float x1, float y1, float x2, float y2){
		
		float y;	//y = a * (x - x1) + y1;
		float a;	//eðim
		
		if( (x1 > 0 && x1 < width) && (y1 > 0 && y1 < height) ){
			
			if ( (x2 > 0 && x2 < width) && (y2 > 0 && y2 < height) ){
						
				if (x1 == x2){
					
					for (int i = y1 ; i < y2 ; i++){
						//emptyMap[int(i * width + x1)] = 1;
						//harita üzerinde verilen nokta sýnýr çizgisi yapýlýr.
						SetBorder(i, int(x1));			
					}			
				}
				else if(y1 == y2){
					
					for (int i = x1 ; i < x2 ; i++) {						
						//emptyMap[int(y1 * width + i)] = 1;
						//harita üzerinde verilen nokta sýnýr çizgisi yapýlýr.
						SetBorder(int(y1), i);
					}
				}					
				else{
					
					a = ((y2 - y1) / (x2 - x1));	//eðim hesaplanýr
					
					for (int i = x1 ; i <= x2 ; i++) {
						
						y = a * (i - x1) + y1;
						//emptyMap[ int(y)* width + i ] = 1;
						//harita üzerinde verilen nokta sýnýr çizgisi yapýlýr.
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
	// 1 deðerinin sýnýr, o deðerinin de alaný temsil ettiði varsayýmsal bir harita oluþturulur. Random sýnýr çizgileri çizmek için lineNum deðiþkeni üzerinde deðiþiklikler yapýnýz.
	void MyMap::SetSize(const int height, const int width) {
		
		this->height = height;
		this->width = width;
		
		this->emptyMap = new int[ width * height] ;
				
		for(int i = 0 ; i < height ; i++){
			
			for(int j = 0 ; j < width; j++){
				
				emptyMap[ i * width + j ] = 0;
			}				
		}
		
		int x1, x2, y1, y2 ;	//random üretilecek koordinat noktalarýný tutarlar
		
		int lineNum = 20 ;	//çizilecek random sýnýr çizgi sayýsý
		
		cout<< endl << "	Cizilecek random sinir cizgi sayisi ==> " << lineNum << endl;
		
		srand(time(0));
		
		
		for(int r =0 ; r < lineNum ; r++){
			
			x1 = rand() % (width) + 1;
			
			y1 = rand() % (height) + 1;
			
			x2 = rand() % (width) + 1;
			
			y2 = rand() % (height) + 1;
			
			DrawLine(x1, y1, x2, y2);	//random üretilen 2 nokta arasýnda sýnýr çizgisi çizilir.
		}
		
		DrawLine(10, 10, 40, 2);
		
		//harita üzerinde yatay sýnýr çizilir
		int j= width/2;
		for(int i = 0 ; i < height ; i++){
			
			SetBorder(i,j);
							
		}
		//dikey sýnýr çizgisi
		int i= height/2;
		for(int k = 0 ; k < width ; k++){
			
			SetBorder(i,k);
							
		}	
	}
	//harita yükseklik ve en deðerlerini aktarýr.
	void MyMap::GetSize(int & width, int & height) {
		
		width = this->width;
		height = this->height;
	}
	//verilen adres sýnýr yapýlýr.
	void MyMap::SetBorder(const int x, const int y){
		
		this->emptyMap[ ( x * this->width ) + y] = 1;
	}
	//SetSize fonksiyonu ile üretilen haritayý konsol ekranýnda gösterir. 
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
	//adresi verilen noktanýn deðeri 1 ise sýnýr(true), 0 ise alan(false) dönderir.
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
			
			MapInterface *map;	//MapInterface turunde adres tutabilen deðiþken tanýmlýyoruz.
			
		public:
			//constructor fonksiyonumuz ile sýnýfýmýzýn baþlangýç durumunu belirlenir.
			MyCounter(MapInterface * map);
			// Feeds map instance into solution class, and initialize.
			void Init(MapInterface * map);
			// Counts zones in provided map, and return result.
			int Solve();
			//dizi içerisndeki ayný elemanlarý siler.
			int AyniElemanlariSil(int *dizi, int h, int w);
	};
	
	MyCounter::MyCounter(MapInterface * map){
		
		Init(map);
		
	}
	
	int MyCounter::AyniElemanlariSil(int *dizi, int h, int w){
		
		int size = w * h;	//dizi boyutu hesaplanýr
		
		//ayný dizi elemanlarý denetlenir ve kaldýrýlýr.
		for(int i = 0 ; i < size ; i++){
			
			for(int j = i + 1 ; j < size ;){
				
				if(dizi[j] == dizi[i]){	// ayný eleman bulundu ise sýrasýyla kayma yapýlýr.
								
					for(int k = j ; k < size ; k++){
						
						dizi[k] = dizi[k + 1];
								}
						size--;	//tüm elemanlar bir sola kaydýrýldýktan sonra dizi boyutu 1 eksiltilir.
				}
				else{
					j++;
				}
			}
		}
		
		return size ;
	}
	
	void MyCounter::Init(MapInterface * map){
		
		this->map = map ;	//sýnýf içerinde oluþturduðumuz map pointer,artýk gelen map nesnesini gösterir. 
		
		cout<< "\n	Asagida temsili olarak harita olusturulmustur.\n" << endl;
		cout<< "	1 ==> Sinir noktasini temsil eder"<< endl;
		cout<< "	0 ==> Alan noktasini temsil eder\n\n"<< endl;
		
		this->map->Show();	//harita gösterilir.
		
		cout<< "\n\n	Toplam alan sayisi = " << Solve()<< endl;	//Solve fonksiyonu ile harita üzerindeki toplam alan ekrana basýlýr.
	}
	
	int MyCounter::Solve(){
		
		//MyMap *m = new MyMap(50, 50);
		MapInterface *m = this->map;
		
		int h, w ;
		m -> GetSize(w, h);	//haritanýn yükseklik ve geniþlik deðerleri alýnýr.
		int *etNum = new int[ w * h ];	//her noktanýn etiket numarasýnýn tutulmasý için dizi oluþturulur.
		
		for(int i =0; i < w * h ; i++){
			etNum[i] = 0;	//baþlangýç olarak tüm etiket deðerleri 0 olarak belirlendi.
		}
		
		int iD = 0, sD = 0 ;	//noktalarýn ilk ve iþlemden sonraki etiket deðerlerini tutar
		bool dVar = true;	//etiket deðiþimini ve dolaylý olarak while döngüsünü kontrol eder
		int enKucEt = 0;	//noktanýn 4 komþusunun en küçük etiket deðeri
		int etNo = 0;	//verilecek etiket numarasý
		
		//deðiþim olduðu sürece döngü devam eder
		while(dVar == true){		
			
			dVar = false;
			
			for(int y = 1 ; y < h-1 ; y++){
				for(int x = 1 ; x < w-1 ; x++){
					
					bool bol = m->IsBorder( y, x);
					//üzerinde bulunduðumuz nokta sýnýr deðilse koþula girilir
					if ( bol == 0 ){
						iD = etNum[y * w + x]; //en baþta noktanýn etiket deðeri alýnýr
						
						enKucEt = 0;	//ilk baþta en küçük etiket deðerine 0 atanýr
						
						//komþuluklar arasýndaki en küçük etiket numarasý bulunur
						for(int i = -1 ; i <= 1 ; i++){
							for(int j = -1 ; j <= 1 ; j++){
								
								//dikey ve yatay yöndeki 4 komþusuna bakar
								if( (i == 0 && j == 1) || (i == 1 && j == 0) || (i == -1 && j == 0) || (i == 0 && j == -1) ){
									
									//bakýlan nokta alaný temsil ediyorsa, komþular arasýndaki en küçük etiket deðeri halen 0 ise ve bu komþu 0 dan büyük etiketli ise en küçük etiket yapýlýr.
									if( etNum[(y + i) * w + (x + j)] != 0 && enKucEt == 0 && m->IsBorder( y+i, x+j) == 0){
										
										enKucEt = etNum[(y + i) * w + (x + j)];
									}
									//bakýlan komþunun etiket deðeri en küçük deðerden küçükse ve sýfýra eþit deðilse en küçük etiket deðeri bu etiketle deðiþtirilir.
									else if (etNum[(y + i) * w + (x + j)] < enKucEt && etNum[(y + i) * w + (x + j)] != 0 && enKucEt != 0 && m->IsBorder( y+i, x+j) != 1){
										
										enKucEt = etNum[(y + i) * w + (x + j)];
									}
								}
							}
						}
						//en küçük etiket deðeri bulunmuþ ise bu deðer noktamýzýn yeni etiket deðeridir.
						if(enKucEt != 0){
							etNum[y * w + x] = enKucEt ;
						}
						//komþularý arasýnda 0 dan farklý en küçük etiket deðeri yok ise noktaya yeni etiket deðeri verilir.
						else if(enKucEt == 0 && etNum[y * w + x] < w *h){
							//cout<< "h;";
							etNo = etNo + 1 ;
							etNum[y * w + x] = etNo ;
						}
						
						sD = etNum[y * w + x];
						//toplam alanda 1 etiket bile deðiþtirilmiþ ise döngü devam eder
						if(iD != sD){
							dVar = true ;
						}
						
					}
				}
			}if(enKucEt == 0 /*|| etNo >= w*h*/)break;	//ilk turda en küçük etiket deðeri 0 da kalmýþsa döngünün devam etmesine gerek yok
		}
		/*cout<<endl<<endl;
		for(int i = 0 ; i < h ; i++){
			for(int j = 0 ; j < w ; j++){
				cout<<" "<<etNum[i * w + j];
			}
			cout<<endl;
		}*/
		
		//son olarak ayný etiket numaralarýný çýkardýðýmýz zaman geriye kalan etNum dizi boyutu toplam bölge sayýsýný verir.
		return AyniElemanlariSil(etNum, h, w) - 1;
	}
	
	ZoneCounterInterface * getZoneCounter() {
		
		MyMap *map = new MyMap(50, 50); //map nesnesi oluþturulur. Parametre olarak, oluþturulacak haritanýn boyutlarý girilir.
		 
		return new MyCounter( map );
	}

}

int main(){
	
	KemalAydin::getZoneCounter();
	
	return 0;
}
