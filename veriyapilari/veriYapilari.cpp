/***********************************************************************************************************************/
#include<iostream>
#include<stack>
#include <queue> // Kuyruk (queue) kütüphanesi
/*kuyruk ve yıgın kutuphaneleri eklemememin sebebi main metodundaki nesne olusturdugumda onları
kullanamıyor ve anamenuye aktaramıyordum derleyicinin kutuphane eklememi istediği için ekledim.*/
//#include <Heap.h>
using namespace std;
/***********************************************************************************************************************/
class Dugum{
public:
	Dugum(int veri)
	{
        this->veri=veri;
		pSonraki = NULL;
	}
	int veri;
	Dugum* pSonraki;
} ;
/*********************************************************************************************************************/
                                    /*Liste yapısı için gerekli elemanlar*/
class BagliListe {
private:
    Dugum* pBas;
    int index;
public:
    BagliListe();
    void ArayaEkle(int);
    void SonaEkle(int );
    void AradanCikar();
    void SondanCikar();
    void Yazdir();
    int ElemanSayisi();
    void Temizle();
    void case1menu();
    void case2menu();
};
              //"Dugum*" yerine "void" de olabilir
BagliListe::BagliListe()
{
    index=-1;
    pBas=NULL;
}
void BagliListe::case1menu()
{
            cout<<"Ekleme turunu seciniz:"<<endl;
            cout<<"1- Araya eleman ekleme "<<endl;
            cout<<"2- Sona eleman ekleme"<<endl;
            cout<<"3- Liste islemlerine geri don"<<endl;
}
void BagliListe::case2menu()
{
            cout<<endl;
            cout<<"Cikarma turunu seciniz:"<<endl;
            cout<<"1- Aradan eleman cikar "<<endl;
            cout<<"2- Sondan eleman cikar"<<endl;
            cout<<"3- Liste islemlerine geri don"<<endl;

}
void BagliListe::ArayaEkle(int eleman)
{
    Dugum *yeniDugum=new Dugum(eleman);
    if (index == -1) {
        yeniDugum->pSonraki = pBas;
        pBas = yeniDugum;
        cout<<eleman<<" listenin basina eklendi"<<endl<<endl;
    } 
    else 
    {
    cout<<"Hangi indexe elemani eklemek istersiniz: ";
                cin>>index;
        Dugum* iter = pBas;
        for (int i = 0; i < index - 1; i++) {
            iter = iter->pSonraki;
        }
        yeniDugum->pSonraki = iter->pSonraki;
        iter->pSonraki = yeniDugum;
        cout<<eleman<<" "<< index<<"'e eklendi"<<endl<<endl;
    }
}
void BagliListe::SonaEkle(int eleman2)
{
    Dugum* yeniDugum = new Dugum(eleman2);
    if (pBas == NULL) {
        pBas = yeniDugum;
        cout<<eleman2<<" listenin basina eklendi"<<endl<<endl;
    } else {
        Dugum* p = pBas;         //Dugumu gezmek için kullandıgım işaretci
        while (p->pSonraki != NULL) {
            p = p->pSonraki;
        }
        p->pSonraki = yeniDugum;
        cout<<eleman2<<" Liste sonuna eklendi"<<endl<<endl;
    }
}   
void BagliListe::AradanCikar() 
{ //pBas silinir ise listeyi kaybederiz 
    if (pBas == NULL) {
        cout << "Liste bos, cikarilacak eleman yok" << endl<<endl;
    }
    int sileleman;
     cout<<"Silinecek elemani giriniz: ";
     cin>>sileleman;
    Dugum* pTemp = pBas;  //öncelikle ilk düğümün adresini alıyorum pTemp içerisine.
    while (pTemp->pSonraki != NULL)//son düğüme gidecek kadar bir döngü yapıyoruz
    {
        if (pTemp->pSonraki->veri == sileleman)
{//çıkaracağımız düğümden önceki düğümün adresini bilmemiz gerekecek
        Dugum* pDon = pTemp->pSonraki; //düğümün adresini yedekliyoruz
        pTemp->pSonraki = pDon->pSonraki;//sonraki düğüme bağlıyoruz
        delete pDon;
        cout<<sileleman<<" Listeden cikarildi"<<endl<<endl;//silmek istediğimiz düğümü siliyoruz
}//ilk düğüm değilse while ile sonraki düğüme geçeceğiz:
        pTemp = pTemp->pSonraki;
}
//buraya geldiysek silinecek düğüm yok demektir.
}
void BagliListe::SondanCikar() 
{
    if (pBas == NULL) {
        cout << "Liste bos, cikarilacak eleman yok" << endl<<endl;
    }
    while(pBas->pSonraki->pSonraki != NULL)
    pBas = pBas->pSonraki;
    Dugum* pTemp = pBas->pSonraki;
    pBas->pSonraki = NULL;
    cout<<pTemp->veri<< " Listeden cikarildi"<<endl<<endl;
}
void BagliListe::Temizle()
{
    pBas=NULL;
    index=-1;
    cout<<"Liste temizlendi"<<endl<<endl;
}
void BagliListe::Yazdir()
{
    if(pBas==NULL)
    {
        cout<<"Liste Bos!"<<endl<<endl;
    }
    else
   {
    Dugum *pTemp=pBas;
        cout<<"Listedeki Elemanlar: ";
        while(pTemp!=NULL){
            cout<<pTemp->veri<<" ";
            pTemp=pTemp->pSonraki;
        }
        cout<<endl<<endl;
    }
}
int BagliListe::ElemanSayisi()
{
    int sayac = 0;
    Dugum* pTemp = pBas;
    while (pTemp != NULL) {
        sayac++;
        pTemp = pTemp->pSonraki;
    }
    return sayac;
}
/*************************************************************************************************************************/
                                /*Yigin yapimiz için gerekli işlemler kümesi*/
class Stack 
{
    int top;                          //en son eklenen pozisyon
    Dugum *pBas;
    public:
        Stack();
        bool Push(int pYeni);            //İşlemin gerçekleşip gerçekleşmediğinin anlaşılması için bool kullanıyoruz.
        int Pop();                  //silinen sayıyı göterecek parametreye gerek yok zaten en üst eleeman silinecek
        bool IsEmpty();             /*top elemanı -1 değerine sahipse yığın boş demek olacak.*/
        void WriteAll();
	    void Stacktop();
        void DeleteAll();
};
Stack::Stack()
{
    top=-1;
    pBas=NULL;
}
bool Stack::IsEmpty(){
    if(pBas == NULL)
    return true;
    return false;
}
bool Stack::Push(int pYeni)
{
    Dugum* yeniDugum = new Dugum(pYeni);
    yeniDugum->veri = pYeni;
    yeniDugum->pSonraki = pBas;
    pBas = yeniDugum;
    top++;
    cout<<pYeni<<" yigina eklendi"<<endl<<endl;
    return true;
}
int Stack::Pop() 
{
    if (IsEmpty()) {
        cout << "Yigin Bos!" << endl<<endl;
        return -1;
    }
    Dugum* temp= pBas;
    int x = temp->veri;
    pBas = pBas->pSonraki;
    temp->pSonraki=NULL;
    top--;
    cout << x << " yigindan cikarildi" << endl<<endl;
    return x;
}
void Stack::DeleteAll(){
    top=-1;
    cout<<"Yigin temizlendi!"<<endl<<endl;
}
void Stack::WriteAll(){
    if(top>=0)
    {
        Dugum *pTemp=pBas;
        cout<<"Yigindaki Elemanlar: ";
        while(pTemp!=NULL){
            cout<<pTemp->veri<<" ";
            pTemp=pTemp->pSonraki;
        }
        cout<<endl<<endl;
    }
    else
    cout<<"Yigin Bos!"<<endl<<endl;
}
void Stack::Stacktop()
{
    int x;
    if(top==-1)
    cout<<"Yigin Bos!!! "<<"Yigindaki elelman sayisi: 0"<<endl<<endl;
    else{
    x=top+1;
    cout<<"Yigindaki eleman sayisi: "<< x<<endl<<endl;}
}
/***********************************************************************************************************************/
                                    /*Kuyruk için gerekli fonksiyonlarım*/
class Kuyruk
{ 
    //kuyruk için oncelikle kuyruk bası ve kuruk sonu elemanlarını tutatk degikenlerimiz olmalı
    private:
        Dugum *pSon;
        int ES;
        Dugum *pBas;
    //private yazmasak da olurdu bir şey degişmezdi
    public:
        Kuyruk();
        bool ekle(int pNew);   //Enquene-push
        int cikar();          //Dequene-pop
        //FIFO: ilk giren ilk çikar
        void temizle();
        void yazdir();
        void sysGoster();
};
Kuyruk::Kuyruk()
{
    ES=0;
    pBas = NULL;
    pSon = NULL;
}
bool Kuyruk::ekle(int pNew)
{
    Dugum* yeniDugum = new Dugum(pNew);
    yeniDugum->veri = pNew;
    yeniDugum->pSonraki = NULL;
    if(ES==0)
        pBas=pSon=yeniDugum;
    //Kuyrugun son elemanını bul
    else
    {
        pSon->pSonraki = yeniDugum;
        pSon = yeniDugum;
    }
    
    ES++;
    return true;
}
int Kuyruk::cikar()
{
    //ilk eleman kuyruktan cıkmalı yani pBas ancak ilk bos mu diye kontrol etmeliyiz
    if(ES==0)
    {
        cout<<"Kuyruk bos!"<<endl<<endl;
        return -1;
    }
    Dugum* temp = pBas;
    int x = temp->veri;
    pBas = pBas->pSonraki;
    temp->pSonraki=NULL;
    ES--;
    cout << x << " kuyruktan cikarildi" << endl << endl;
    return x;
}
void Kuyruk::temizle()
{
    while(ES>0)
    cikar();
    cout<<"Kuyruk temizlendi!"<<endl<<endl;
}
void Kuyruk::yazdir()
{
    if(ES==0)
        cout<<"Kuyruk bos!"<<endl<<endl;
    else
    {
        Dugum* temp = pBas;
        cout << "Kuyruktaki Elemanlar: ";
        while (temp != NULL) {
            cout << temp->veri << " ";
            temp = temp->pSonraki;
        }
        cout << endl << endl;
    }
}
void Kuyruk::sysGoster() {
    cout << "Kuyruktaki eleman sayisi: " << ES << endl << endl;
}
/*********************************************************************************************************************/
                                /*Cirpilama Tablom için sinif ve fonksiyonlarim*/
static const int MAX = 10;
class HashTable
{
    public:
    Dugum *veri[MAX];     //Dizi adres tutacak
    HashTable();
    void ekle(int);
    void sil(int);
    void temizle();
    void tablegoster();
    void tableyazdir();
};
HashTable::HashTable()
{
    for(int i=0;i<MAX;i++)
    veri[i]=NULL;
}
void HashTable::ekle(int eleman)
{
    Dugum* pYeni = new Dugum(eleman);
    int mod = eleman % MAX;
    if (!veri[mod]) //ilgili hücrede bir adres var mı
    {//eğer varsa oaryaa bağlı bir bağlı liste var demektir
    veri[mod] = pYeni;
    cout<<eleman <<" tabloya eklendi"<<endl<<endl;
    return;
    }
//buraya geldiysek bağlı liste var:
    Dugum* pTemp = veri[mod];//ilgili indisteki adres bilgisini pTemp'e atacağız.
    while (pTemp->pSonraki != NULL)
    {//son elemana kadar gideceğiz. Liste konusunda görmüştük
    pTemp = pTemp->pSonraki;
    }
    pTemp->pSonraki = pYeni;//son düğüme yeni düğümü ekleyebiliriz.
    cout<<eleman <<" tabloya eklendi"<<endl<<endl;
}
void HashTable::sil(int eleman)
{
    int mod = eleman % MAX;
//ilk durum hiç elemanın(düğümün) olmadığı durum
        if (!veri[mod]) //Hiç bir elemanın olmadığı durum
        {
            cout<<"Tablo bos!!"<<endl<<endl;
            return;
        }
//buraya geldiysek en az 1 düğüm var
//ilk düğümü çıkarmaya çalışacağız:
    if (!veri[mod]->pSonraki) //tek düğüm olma durumudur
    {
        if (veri[mod]->veri == eleman)
        {//tamam 1 düğüm var ama bu benim aradığım düğüm mü.
        //Eğer öyle ise bu tek düğümü silelim
        delete veri[mod]; //silicem ama yeterli değil, çünkü adresini silmedik
        veri[mod] = NULL; //NULL yapmazsam hafıza hatasıyla karşılaşırım,
 //çünkü orada düğüm var zannedecek
        cout<<"Tablodaki tek dugum silindi"<<endl<<endl;
}
return; //aradığımız düğümse veya değilse her iki durumda da işlemi bitiriyoruz
}
//buraya geldiysek birden fazla düğüm var demektir.
//Birden fazla elemanın(düğümün) olması durumu:
if (veri[mod]->veri == eleman)
{//birden fazla düğüm var ama ilk düğüm aradığımız düğüm ve sileceğiz
//ilk düğüm sileceğiz, dolayısıyla bağlı olan sonraki düğüme bağlanmalıyı
Dugum* pDon = veri[mod]->pSonraki;//silinen düğüme bağlı olan düğüme ulaşamazdık
delete veri[mod]; //silinen düğüm, şimdi ona bağlı olan düğüme bağlanalım:
veri[mod] = pDon;
cout<<eleman<<" tablodan silindi"<<endl<<endl;
return;
}
//tek bir durum kaldı: aradığımız düğüm arada bir yerde
//Listelerdeki aradan çıkarmaya benziyor.
Dugum* pTemp = veri[mod];//öncelikle ilk düğümün adresini alıyorum pTemp içerisine.
while (pTemp->pSonraki != NULL)//son düğüme gidecek kadar bir döngü yapıyoruz
{
if (pTemp->pSonraki->veri == eleman)
{//çıkaracağımız düğümden önceki düğümün adresini bilmemiz gerekecek
Dugum* pDon = pTemp->pSonraki; //düğümün adresini yedekliyoruz
pTemp->pSonraki = pDon->pSonraki;//sonraki düğüme bağlıyoruz
delete pDon;//silmek istediğimiz düğümü siliyoruz
cout<<eleman<<" tablodan silindi"<<endl<<endl;
return;//silme işlemi gerçeklendiğine göre return
}//ilk düğüm değilse while ile sonraki düğüme geçeceğiz:
pTemp = pTemp->pSonraki;
}
//buraya geldiysek silinecek düğüm yok demektir.
}
void HashTable:: temizle()
{
    for(int i=0;i<MAX;i++)
    veri[i]=NULL;
    cout<<"Tablo Temizlendi!!!"<<endl<<endl;
}
void HashTable::tablegoster()
{
    int sayac1 = 0;
    for (int i = 0; i < MAX; i++) {
        Dugum* pTemp = veri[i];
        while (pTemp != NULL) {
            sayac1++;
            pTemp = pTemp->pSonraki;
        }
    }
    cout<<"Tablodaki toplam eleman sayisi: "<<sayac1<<endl<<endl;
}
void HashTable::tableyazdir()
{
    for (int i = 0; i < MAX; i++) {
        Dugum* pTemp = veri[i];
        while (pTemp != NULL) {
            cout << pTemp->veri << " ";
            pTemp = pTemp->pSonraki;
        }
    }
    cout << endl<<endl;
}
/*********************************************************************************************************************/
                                        /*Ikili agaac icin class tanımı*/
class IkiliAgac
{
    public:
	struct Agacdugum //düğüm oluşturalım
	{	int deger;
		Agacdugum *sol;
		Agacdugum *sag;
	};
	
	Agacdugum *kok;
	
	IkiliAgac()	// Kurucu
	{ 
		kok = NULL; 
	}
	
	void dugumEkle(int);
    void cikar(int );
    Agacdugum* cikarDugum(Agacdugum*, int);  
    Agacdugum* enKucukDegerDugumu(Agacdugum*); 
    void agaciTemizle();
    int elemanSys(Agacdugum* dugum);
    //Ağaçta dolaşmak için gerekli fonksiyonlar
     void InOrderDolasim(Agacdugum *dugumPtr);
     void PreOrderDolasim(Agacdugum *dugumPtr);
	 void PostOrderDolasim(Agacdugum *dugumPtr);
  //Düğümleri göstermek için gerekli fonksiyonlar
    void InOrderDugumGoster(void)
    { InOrderDolasim(kok); }
    
    void PreOrderDugumGoster()
    { PreOrderDolasim(kok); }
    
    void PostOrderDugumGoster()
    { PostOrderDolasim(kok); }

};
void IkiliAgac::dugumEkle(int eleman)
{	Agacdugum *yenidugum,	// yeni  düğümü işaret edecek
	         *dugumPtr;	// ağacı dolaşacak işaretçi, pBas ile dolaşıyorduk ya.	
			 // Yeni düğüm oluştur	
			yenidugum = new Agacdugum;	
			yenidugum->deger = eleman;
			yenidugum->sol = yenidugum->sag = NULL;
			 if (!kok){ // Ağaç boş mu?
				kok = yenidugum;	
                cout<<eleman<<" Kok degerine eklendi"<<endl<<endl;}
			else	
			{		
				dugumPtr = kok; 
				while (dugumPtr != NULL)
					{
						if (eleman < dugumPtr->deger)
						{
							if (dugumPtr->sol){
								dugumPtr = dugumPtr->sol;
                                }
							else
							{
								dugumPtr->sol = yenidugum;
                                break;
							}
                        cout<<eleman<<" sol dugume eklendi"<<endl<<endl;			
						}//if kapat
						else if (eleman > dugumPtr->deger)
						{				
							if (dugumPtr->sag){
								dugumPtr = dugumPtr->sag;
                            }
							else
								{				
									dugumPtr->sag = yenidugum;
                                    break;
								}
                        cout<<eleman<<" sag dugume eklendi"<<endl<<endl;
						}//else if kapat
						else
						{
							cout << "Agacta ayni deger iki defa bulundu.\n";
							break;
						}	
					}//while kapat			
					
			}//else kapat	
}//fonksiyon sonu
void IkiliAgac::cikar(int eleman) {
    kok = cikarDugum(kok, eleman);
    cout<<kok->deger<< " agactan cikarildi"<<endl<<endl;
}
IkiliAgac::Agacdugum* IkiliAgac::cikarDugum(Agacdugum* kok, int eleman) {
    if (kok == NULL) 
        return kok;
    if (eleman < kok->deger) {
        kok->sol = cikarDugum(kok->sol, eleman);
    } else if (eleman > kok->deger) {
        kok->sag = cikarDugum(kok->sag, eleman);
    } else {
        if (kok->sol == NULL) {
            Agacdugum* temp = kok->sag;
            delete kok;
            return temp;
        } else if (kok->sag == NULL) {
            Agacdugum* temp = kok->sol;
            delete kok;
            return temp;
        }
        
        Agacdugum* temp = enKucukDegerDugumu(kok->sag);
        kok->deger = temp->deger;
        kok->sag = cikarDugum(kok->sag, temp->deger);
    }
    return kok;
}
IkiliAgac::Agacdugum* IkiliAgac::enKucukDegerDugumu(Agacdugum* dugum) {
    Agacdugum* current = dugum; // current başlangıçta verilen düğümü işaret eder
    while (current && current->sol != NULL) { // current NULL olmadığı ve current->sol NULL olmadığı sürece döngü devam eder
        current = current->sol; // current işaretçisini current->sol'a kaydır
    }
    return current; // en sol düğüm bulunduğunda current işaretçisi bu düğümü işaret eder
}
void IkiliAgac::agaciTemizle()
{
    kok=NULL;
    cout<<"Agac temizlendi!!!"<<endl<<endl;
}
int IkiliAgac::elemanSys(Agacdugum* dugum)
{
    if (dugum == NULL) {
        return 0;
    }
     return 1 + elemanSys(dugum->sol) + elemanSys(dugum->sag); //1 eklememizin sebebi indis 0'dan Basliyor.
}
void IkiliAgac::InOrderDolasim(Agacdugum *dugumPtr)
{
    if (dugumPtr)
    {
    InOrderDolasim(dugumPtr->sol);
    cout << dugumPtr->deger<<"  " ;
    InOrderDolasim(dugumPtr->sag);
    }
}
void IkiliAgac::PreOrderDolasim(Agacdugum *dugumPtr)
{
    if (dugumPtr)
    {
    cout << dugumPtr->deger <<" ";
    PreOrderDolasim(dugumPtr->sol);
    PreOrderDolasim(dugumPtr->sag);
    }
}
//Ağaçta PostOrder dolaşalım
void IkiliAgac::PostOrderDolasim(Agacdugum *dugumPtr)
{
    if (dugumPtr)
    {
    PostOrderDolasim(dugumPtr->sol);
    PostOrderDolasim(dugumPtr->sag);
    cout << dugumPtr->deger <<" ";
    }
}
/***********************************************************************************************************************/
void anamenu(Stack& stack, Kuyruk& kuyruk,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable);
void ygnmenu(Stack& stack, Kuyruk& kuyruk,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable);
void kyrkmenu(Kuyruk& kuyruk,Stack& stack,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable);
void baglimenu(BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack,IkiliAgac &agac,HashTable &hashTable);
void IkiliAgacMenu(IkiliAgac &agac,BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack,HashTable &hashTable);
void cirpilamamenu(HashTable &hashTable,IkiliAgac &agac,BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack);
/**********************************************************************************************************************/
int main()
{
    // main fonksiyonu içinde olusturdugumuz nesnelerimizi sırası ile anamenu fonsiyonuna geçiriyoruz
    Stack stack;
    Kuyruk kuyruk;
    BagliListe bagliListe;
    IkiliAgac agac;
    HashTable hashTable;
        anamenu(stack,kuyruk,bagliListe,agac,hashTable);
    return 0;
}
/*********************************************************************************************************************/
void anamenu(Stack& stack, Kuyruk& kuyruk,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable)
{
    int sayi; 
    cout<<"Yapmak istediginiz uygulamayi seciniz:"<<endl;
    cout<<"1- Yigin Uygulamasi"<<endl;
    cout<<"2- Kuyruk Uygulamasi"<<endl;
    cout<<"3- Tek Yonlu Bagli Liste Uygulamasi"<<endl;
    cout<<"4- Ikili Agac Uygulamasi"<<endl;
    cout<<"5- Cirpilama Uygulamasi"<<endl;
    cout<<"6- Programdan cikis"<<endl;
    cin>>sayi;
    switch(sayi) 
    {
        case 1:
            cout<<endl;
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable);
            break;
        case 2:
            cout<<endl;
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 3:
            cout<<endl;
            baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            break;
        case 4:
            cout<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 5:
            cout<<endl;
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 6:
            exit(0);
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable);// Ana menüye geri dön
            break;
    }
}
/*******************************************************************************************************************************/
void ygnmenu(Stack& stack,  Kuyruk& kuyruk,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable)
{
    int sayi2;
    cout<<"Yigin icin islem seciniz:"<<endl;
    cout<<"1- Yigina eleman ekle"<<endl;
    cout<<"2- Yigindan eleman cikar"<<endl;
    cout<<"3- Yigini temizle"<<endl;
    cout<<"4- Yigindaki elemanlari goster"<<endl;
    cout<<"5- Yigindaki eleman sayisini goster"<<endl;
    cout<<"6- Ana menuye geri don"<<endl;
    cin>>sayi2;
    switch(sayi2)
    {
        case 1:
            cout<<endl;
            int eleman;
            cout << "Eklenecek elemani giriniz: ";
            cin >> eleman;
            stack.Push(eleman);
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable); // Eleman eklendikten sonra yığın menüsünü tekrar çağır
            break;
        case 2:
            cout<<endl;
            stack.Pop();
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable); // Eleman eklendikten sonra yığın menüsünü tekrar çağır
            break;
        case 3:
            cout<<endl;
            stack.DeleteAll();
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable); // Eleman eklendikten sonra yığın menüsünü tekrar çağır
            break;
        case 4:
            cout<<endl;
            stack.WriteAll();
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable);
            break;
        case 5:
            cout<<endl;
            stack.Stacktop();
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable);
            break;
        case 6:
            cout<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable); // Ana menüye geri dön
            break;
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            ygnmenu(stack,kuyruk,bagliListe,agac,hashTable);
            break;
    }
}
/***************************************************************************************************************************/
void kyrkmenu(Kuyruk& kuyruk, Stack& stack,BagliListe &bagliListe,IkiliAgac &agac,HashTable &hashTable)
{
    int sayi3;
    cout<<"Kuyruk icin islem seciniz:"<<endl;
    cout<<"1- Kuyruga eleman ekle"<<endl;
    cout<<"2- Kuyruktan eleman cikar"<<endl;
    cout<<"3- Kuyrugu temizle"<<endl;
    cout<<"4- Kuyruktaki elemanlari goster"<<endl;
    cout<<"5- Kuyruktaki eleman sayisini goster"<<endl;
    cout<<"6- Ana menuye geri don"<<endl;
    cin>>sayi3;
    switch(sayi3)
    {
        case 1:
            cout<<endl;
            int eleman;
            cout << "Eklenecek elemani giriniz: ";
            cin >> eleman;
            kuyruk.ekle(eleman);
            cout<<endl;
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 2:
            cout<<endl;
            kuyruk.cikar();
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 3:
            cout<<endl;
            kuyruk.temizle();
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 4:
            cout<<endl;
            kuyruk.yazdir();
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 5:
            cout<<endl;
            kuyruk.sysGoster();
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
        case 6:
            cout<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable);// Ana menüye geri dön
            break;
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            kyrkmenu(kuyruk,stack,bagliListe,agac,hashTable);
            break;
    }
}
/***************************************************************************************************************************/
void baglimenu(BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack,IkiliAgac &agac,HashTable &hashTable)
{
    int sayi4;
    cout<<"Bagli liste icin islem seciniz:"<<endl;
    cout<<"1- Listeye eleman ekleme"<<endl;
    cout<<"2- Listeden eleman cikar"<<endl;
    cout<<"3- Listeyi temizle"<<endl;
    cout<<"4- Listedeki elemanlari goster"<<endl;
    cout<<"5- Listedeki eleman sayisini goster"<<endl;
    cout<<"6- Ana menuye geri don"<<endl;
    cin>>sayi4;
    switch (sayi4)
    {
        case 1:
            int altsecim;
            cout<<endl;
            while (true) { 
                // Döngüyü sonsuz yaparak tekrar tekrar case1menu'yu göster
            bagliListe.case1menu();
            cin>>altsecim;
            if(altsecim==1)
            {   cout<<endl;
                int eleman;
                cout<<"Eklenecek elemani giriniz: ";
                cin>>eleman;
                bagliListe.ArayaEkle(eleman);
            }
            else if(altsecim==2)
            {   cout<<endl;
                int eleman2;
                cout<<"Sona eklenecek elemani giriniz: ";
                cin>>eleman2;
                bagliListe.SonaEkle(eleman2);
            }
            else
            {
                cout<<endl;
                baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            }
            }
            break;
        case 2:
            int altsecim1;
            cout<<endl;
            while (true) { 
                // Döngüyü sonsuz yaparak tekrar tekrar case2menu'yu göster
                bagliListe.case2menu();
                cin>>altsecim1;
            if(altsecim1==1)
            {   
                cout<<endl;
                bagliListe.AradanCikar();
            }
            else if(altsecim1==2)
            {
                cout<<endl;
                bagliListe.SondanCikar();
            }
            else
            {
                cout<<endl;
                baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            }
            }
                break;
        case 3:
                cout<<endl;
                bagliListe.Temizle();
                baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
                break;
        case 4:
            cout<<endl;
            bagliListe.Yazdir();
            baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            break;
        case 5:
            cout<<endl;
            cout<<"Eleleman sayisi: "<<bagliListe.ElemanSayisi()<<endl<<endl;
            baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            break;
        case 6:
            cout<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable); // Ana menüye geri dön
            break;
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            baglimenu(bagliListe,kuyruk,stack,agac,hashTable);
            break;
    }
}
/*****************************************************************************************************************************/
void IkiliAgacMenu(IkiliAgac &agac,BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack,HashTable &hashTable)
{   
    int sayi5;
    cout<<endl;
    cout<<"Ikili agac icin islem seciniz: "<<endl;
    cout<<"1- Agaca eleman ekle"<<endl;
    cout<<"2- Agactan eleman sil"<<endl;
    cout<<"3- Agaci temizle"<<endl;
    cout<<"4- Agactaki eleman sayisini goster"<<endl;
    cout<<"5- Agaci InOrder dolasarak elemanlari goster"<<endl;
    cout<<"6- Agaci PreOrder dolasarak elemanlari goster"<<endl;
    cout<<"7- Agaci PostOrder dolasarak elemanlari goster"<<endl;
    cout<<"8- Ana menuye geri don"<<endl;
    cin>>sayi5;
    switch(sayi5)
    {
        case 1:
            cout<<endl;
                int eleman;
                cout<<"Eklenecek elemani giriniz: ";
                cin>>eleman;
                agac.dugumEkle(eleman);
                IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 2:
            cout<<endl;
                int eleman2;
                cout<<"Cikarilacak elemani giriniz: ";
                cin>>eleman;
                agac.cikar(eleman2);
                IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
                break;
        case 3:
            cout<<endl;
            agac.agaciTemizle();
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 4:
            cout<<endl;
            cout<<"Agactaki toplam eleman sayisi: "<<agac.elemanSys(agac.kok)<<endl<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 5:
            cout<<endl;
            cout<<"InOrder Dolasim: ";
            agac.InOrderDugumGoster();
            cout<<endl<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 6:
            cout<<endl;
            cout<<"PreOrder Dolasim: ";
            agac.PreOrderDugumGoster();
            cout<<endl<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 7:
            cout<<endl;
            cout<<"PostOrder Dolasim: ";
            agac.PostOrderDugumGoster();
            cout<<endl<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        case 8:
            cout<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable); // Ana menüye geri dön
            break;
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            IkiliAgacMenu(agac,bagliListe,kuyruk,stack,hashTable);
            break;
        }
}
/****************************************************************************************************************************/
void cirpilamamenu(HashTable &hashTable,IkiliAgac &agac,BagliListe &bagliListe,Kuyruk& kuyruk,Stack& stack)
{
    int sayi6;
    cout<<endl;
    cout<<"Cirpilama (Hash Tablosu) icin islem seciniz:"<<endl;
    cout<<"1- Tabloya eleman ekleme"<<endl;
    cout<<"2- Tablodan eleman sil"<<endl;
    cout<<"3- Tabloyu temizle"<<endl;
    cout<<"4- Tablodaki eleman sayisini goster"<<endl;
    cout<<"5- Tablodaki elemanlari goster"<<endl;
    cout<<"6- Ana menuye geri don"<<endl;
    cin>>sayi6;
    switch(sayi6)
    {
        case 1:
            cout<<endl;
            int eleman;
            cout<<"Eklenecek elemani giriniz: ";
                cin>>eleman;
            hashTable.ekle(eleman);
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 2:
            cout<<endl;
            int eleman1;
            cout<<"Silinecek elemani giriniz: ";
                cin>>eleman1;
            hashTable.sil(eleman1);
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 3:
            cout<<endl;
            hashTable.temizle();
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 4:
            cout<<endl;
            hashTable.tablegoster();
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 5:
            cout<<endl;
            hashTable.tableyazdir();
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
        case 6:
            cout<<endl;
            anamenu(stack,kuyruk,bagliListe,agac,hashTable); // Ana menüye geri dön
            break;
        default:
            cout<<endl;
            cout<<"HATALI TUSLAMA YAPTINIZ!"<<endl<<"TEKRAR TUSLAMA YAPINIZ!"<<endl<<endl;
            cirpilamamenu(hashTable,agac,bagliListe,kuyruk,stack);
            break;
    }
}
