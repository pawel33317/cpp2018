#include <iostream>
#include "chapterS.hpp"

void pointersAndReferencesToBaseClass();
void funkcjeVirtualIPolimorfizm();
void overrideFinalAndCOVARIANT();
void wirtualneDestruktoryIVirtualizationOverloading();
void virtualAssigment();
void earlyAndLateBinding();
void virtualTable();
void pureVirtualFunctionsAbstractBaseClasesAndInterfaces();
void virtualBaskClass();
void objectSlicing();

void chapter12run()
{
    printf("\n\n-----chapter 12 started-----\n");
    pointersAndReferencesToBaseClass();
    funkcjeVirtualIPolimorfizm();
    overrideFinalAndCOVARIANT();
    wirtualneDestruktoryIVirtualizationOverloading();
    virtualAssigment();
    earlyAndLateBinding();
    virtualTable();
    pureVirtualFunctionsAbstractBaseClasesAndInterfaces();
    virtualBaskClass();
    objectSlicing();
}

class Base1
{
protected:
    int mValue;
public:
    Base1(int value) : mValue(value) {}
    void showName() {std::cout << "I am Base ";}
    int getValue(){return mValue;}
};
class Derived1 : public Base1
{
public:
    Derived1(int value) : Base1(value) {}
    void showName() {std::cout << "I am Derived ";}
    int getValue(){return mValue*2;}
};

void pointersAndReferencesToBaseClass()
{
    //Klasa dziedzicząca składa się z 2 lub więcej części -> bazowej i pochodnej
    //Dziedziczenie: is a -> klasa Derived jest również Base
    Derived1 d1(5);
    Derived1& d2 = d1;
    Derived1* d3 = &d2;

    Base1& b1 = d1;
    Base1* b2 = &d1;
    d1.showName();  std::cout << d1.getValue()  << std::endl;
    d2.showName();  std::cout << d2.getValue()  << std::endl;
    d3->showName(); std::cout << d3->getValue() << std::endl;
    b1.showName();  std::cout << b1.getValue()  << std::endl;
    b2->showName(); std::cout << b2->getValue() << std::endl;
    //Bez polimorfuzmu wywołują się metody klasy, którą jest zmienna a nie 
    //metody klasy na którą wskazuje zmienna
}



class Base2
{
public:
    int mValue;
    Base2(int value) : mValue(value) {}
    virtual void showName() {std::cout << "I am Base ";}
    virtual int getValue(){return mValue;}
};
class Derived2 : public Base2
{
public:
    int mValue=10;
    Derived2(int value) : Base2(value) {}
    void showName() {std::cout << "I am Derived ";}
    int getValue(){return mValue*2;}
    //int getValue(){return Base2::mValue*2;}
};
class A1          { public: virtual void show(){std::cout << "A1\n";}};
class B1:public A1{ public: void show(){std::cout << "B1\n";}};
class C1:public B1{ public: void show(){std::cout << "C1\n";}};

class A2{
public:
    A2(){show();}
    void pokaz() {show();}
    virtual void show(){std::cout << "A2\n";}
    ~A2(){show();}
};
class B2:public A2{
public:
    virtual void show(){std::cout << "B2\n";}
};
void funkcjeVirtualIPolimorfizm()
{
    std::cout << "===================================\n";
    //!!!Funkcja virtualna -> specjalny typ funkcji, który w momencie wywołania
    //rozwija się do najbardziej dziedziczonej wersji. 
    //!!!TAKA UMIEJĘTNOŚĆ JEST NAZYWANA: POLIMORFIZM
    //!!!Dziedziczona funkcja jest uznawana za zgodną jeżeli ma taką samą sygnaturę
    //!!!funkcja taka jest nazywana override
    Derived2 d2{1};
    d2.showName();  std::cout << d2.getValue()  << std::endl;
    Base2& b2 = d2;
    b2.showName();  std::cout << b2.getValue()  << std::endl;
    C1 c1;
    A1& a1 {c1};
    a1.show();//Wystarczy że A jest virtual, B i C nie musi

    //!!!jeżeli funkcja jest virtual to wszystkie jeej overridy są też uważane za
    //virtual mimo jeżeli nie mają słówk virtual
    //!!!jednak warto dopisywać virtual do metod przeciążających dla czytelności
    //!!!return type musi się zgadzać

    //!!!nie wykonywać wirtualnych funkcji z konstruktorów i destruktorów
    //!!!w konstruktorach bo base jest robione przed derived i zostanie
    //wywołana wersja Base
    //a w destruktorach bo część derived zostanie już skazowana więc kompilator
    //też wywoła funkcję Base

    {
        B2 b2;//w konstruktorze i destruktorze nie działa polimorfizm dla wywołań
        A2& a2 {b2};
        a2.pokaz();
    }

    //!!!Domyślnie funkcje nie są wirtualne z powodu optymalizacji
    //rozwinięcie funkcji virtualnej trwa dłużej niż funkcji niewirtualnej
    //!!!dodatkowo kompilator musi zaalokować dodatkowy pointer dla każdego obiektu
    //klasy dla funkcji wirtualnych
}



using namespace std;
class A3
{
public:
    virtual void showName() const=0;
    virtual ~A3(){}
};
class B3 : public A3
{
public:
    virtual void showName() const override{}
    virtual ~B3(){}
    //virtual void showName() override {} !!!nie zadziala bo to inna funkcja
    //!!!override zapobiega problemom z overridowaniem finkcji 
    //np poprzez podanie złego typu czy też brak const
};

class A4
{
public:
    virtual void showName() {};
    virtual ~A4(){}
};
class B4 : public A4
{
public:
    virtual void showName() override final {} //!!!uniemożliwia overridowanie
    //void showName2() final {}; nie może być final a nie virtual
    virtual ~B4(){}
};
class C4 : public B4
{
public:
    //virtual void showName() override {}//ERROR
    virtual ~C4(){}
};

class A5 final
{
public:
    virtual void showName() {};
    virtual ~A5(){}
};
//class B5 : public A5 {}; //ERROR bo A5 jest finalna

class A6
{
public:
    void showNameNonVirtual() { std::cout << "A6\n";}
    virtual void showName() { std::cout << "A6\n";}
    virtual ~A6(){}
};
class B6 : public A6
{
public:
    virtual void showName() override { std::cout << "B6\n";};
    virtual ~B6(){}
};
class C6 : public B6
{
public:
    void showNameNonVirtual() { std::cout << "C6\n";};
    virtual void showName() override { std::cout << "C6" << "\n";};
    virtual ~C6(){}
};

//COVARIANT
class CoVariantBase
{
public:
    A6 a6;
    virtual A6  returnsA6(){ return a6;}
    virtual A6* returnsA6ptr(){ return &a6;}
    virtual A6& returnsA6ref(){ return a6;}
};
class CoVariantDerived : public CoVariantBase
{
public:
    C6 c6;

    //!!!covariant return type działaja tylko dla referencji i pointerów
    //!!!nie działa dla całych obiektów
    //virtual C6  returnsA6() override {return c6;}//ERROR

    virtual C6* returnsA6ptr() override {
        std::cout << "method from CoVariantDerived used\n";
        return &c6;
    }
    virtual C6& returnsA6ref() override {
        std::cout << "method from CoVariantDerived used\n";
        return c6;
    }
};
void overrideFinalAndCOVARIANT()
{
    //override i final nie są keyword a jedynie identyfikatorami o
    //specjalnym znaczeniu w zależności od kontekstu
    //!!!override nie powoduje spadku wydajności
    //!!!dodawać override specifier do każdej overridowanej funkcji
    C6* a6 = new C6;
    a6->showName();
    a6->C6::showName();
    a6->B6::showName();
    a6->A6::showName();

    //!!!covariant returns derived types
    //different than the base class
    CoVariantDerived cvd;
    cvd.returnsA6ptr()->showNameNonVirtual();//OK zwróci C6
                                             //(wykona C6::returnsA6ptr)
    cvd.returnsA6ref().showNameNonVirtual();//OK zwróci C6
    CoVariantBase& cvb = cvd;
    cvb.returnsA6ptr()->showNameNonVirtual();//!!! zwróci A6
                                             //(wykona C6::returnsA6ptr
                                             //(polimorficzną metodę zwracającą C6))
                                             //Ale ponieważ Base zwraca A6 obiekt
                                             //będzie downcasted to A6
    cvb.returnsA6ref().showNameNonVirtual();//!!! zwróci A6

    //!!!C++ nie umie dopasować typu więc zwracany typ dla metody returnsA6ptr/ref
    //będzie taki jaki jest w metodzie dla obiektu na którym wykonujemy tą metodę
    //mimo że zwróci go metoda polimorficznie overridowana
}


class A7 { public: ~A7(){cout<<"A7 Destructor\n";}};
class B7: public A7 { public: ~B7(){cout<<"B7 Destructor\n";}};
class A7V { public: virtual ~A7V(){cout<<"A7 Destructor\n";}};
class B7V: public A7V { public: virtual ~B7V(){cout<<"B7V Destructor\n";}};
class A8 { public: virtual void show(){cout<<"A8 method\n";}};
class B8: public A8 { public: virtual void show(){cout<<"B8 method\n";}};
void wirtualneDestruktoryIVirtualizationOverloading()
{
    cout << "\n-------------------------------\n";
    //Destruktor musi być publiczny
    {B7 b7;}//wykonają się oba mimo że nie są wirtualne
    B7* b72 = new B7{};
    delete b72;//Też wykonają się oba

    //!!!Bez wirtualnych destruktorów nie wykonają się oba przy kasowaniu
    //z użyciem pointera na base klasę
    A7* a7 = new B7{};
    delete a7;//!!!wykonał się tylko z klasy A7
    //!!!program zakłada, że jeżeli destruktor nie jest virtualny to musi wywołać
    //jedynie destruktor z klasy Base
    cout << "------------------\n";

    //!!!Zawsze tworzyć virtualny destruktor jeżeli używa się dziedziczenia
    A7V* a7v = new B7V{};
    delete a7v; //wykonają się oba

    //!!!aby wykonać funkcję, która zostałła overridowana należy użyć
    //SCOPE operatora
    B8 b8;
    A8& a8 = b8;
    b8.show();
    a8.show();
    b8.A8::show();//Wykona metody z klasy Base mimo virtuala
    a8.A8::show();
}


class B9;
class A9
{
public:
    int a9val;
    A9& operator=(const A9& other){
        cout << "A9::operatpr=A9\n";
        a9val = other.a9val;
        return *this;
    }
    A9& operator=(const B9& other){
        //a9val = other.a9val; //OK tylko nie ma forward deklaracji
        a9val = 666;
        //operator=(static_cast<const A9&>(other)); //jak wyżej

        //other.b9val zostaje pominięte
        cout << "A9::operatpr=B9\n";
        return *this;
    }
    virtual ~A9(){}
};
class B9: public A9
{
public:
    int b9val;
    B9& operator=(const B9& other){
        A9::operator=(other);//żeby skopiowało a9val
        b9val = other.b9val;
        cout << "B9::operatpr=B9\n";
        return *this;
    }
    /*
    B9& operator=(const A9& other){
        A9::operator=(other);
        b9val = 1111;//Brak wartości trzeba podać domyslną
        cout << "B9::operatpr=A9\n";
        return *this;
    }
    */
    B9& operator=(const A9& other){
        const B9* b9ptr = dynamic_cast<const B9*>(&other);
        if(b9ptr)
        {
            a9val = b9ptr->a9val;
            b9val = b9ptr->b9val;
        }
        else
        {
            //to można wywołać też operator= klasy Bazowej A9
            a9val = other.a9val;
            constexpr int defaultVal = 555;
            b9val = defaultVal;
        }
        cout << "B9::operatpr=A9\n";
        return *this;
    }
};
void virtualAssigment()
{
    cout << "------------------\n";
    A9 a91{};
    A9 a92{};
    B9 b91{};
    B9 b92{};
    a91 = a92;//A9::operatpr=A9
    cout << "------\n";
    b91 = b92;//B9::operatpr=B9
    cout << "------\n";
    a91 = b91;//A9::operatpr=B9
    cout << "------\n";
    b91 = a91;//B9::operatpr=A9
    //!!!możliwe jest zrobienie virtualnego operatora przypisania
    //!!!Lepiej nie używać virtualnego operator=

    //Operatory przypisania ciężko zrobić virtual bo typ w klasach 
    //pochodnych jest inny -> więc są to różne funkcje
    //B::operator=(const B& right) != D::operator=(const D& right)
    //!!!NIE UZYWAC VIRTUALNEGO ASSIGMENTU

    //Inną opcją jest użycie RTTI -> run time type information
    //czyli użyć dynamic_casta sprawdzić typ obiektu i przypisać dane
    /*
    B9& operator=(const A9& other){
        const B9* b9ptr = dynamic_cast<const B9*>(&other);
        if(b9ptr)
        {
            a9val = b9ptr->a9val;
            b9val = b9ptr->b9val;
        }
        else
        {
            //to można wywołać też operator= klasy Bazowej A9
            a9val = other.a9val;
            constexpr int defaultVal = 555;
            b9val = defaultVal;
        }
        cout << "B9::operatpr=A9\n";
        return *this;
    }
    */

   //!!!żeby zrobić dynamic Coś musi być virtualne
}


int notDirectFunction(double d)
{
    cout << "notDirectFunction(double)" << endl;
    return 0;
}
void directFunction()
{
    cout << "directFunction()" << endl;
}
void earlyAndLateBinding()
{
    //!!!Jak virtual funkcje są zaimplementowane

    //program jest wykonywany sekwencyjnie
    //program zaczyna wykonywać się od main(), gdy napotka wywołanie jakiejś
    //funkcji punkt wykonania skacze do jej początku -> skąd wie ???

    //podczas kompilacji kompilator konwertuje każdą linię kodu 
    //do jednej lub więcej linii kodu maszynowego
    //każda linia kodu maszynowego ma swój unikalny sekwencyjny adres
    //dak samo działa to dla funkcji -> kiedy kompilator napotyka funkcję
    //konwertuje ją do kodu maszynowego i nadaje kolejny wolny adres
    //każda funkcja kończy się więc unikalnym adresem

    //BINDING -> proces konwertowania identyfikatorów (np. zmienne, nazwy funkcji)
    //do adresów
    //tu będziemy tylko omawiać bindowanie funkcji

    //EARLY BINDING -> większość funkcji, które napotka kompilator będą
    //bezpośrednimi wywołaniami czyli instrukcjami, które bezpośrednio wywołują
    //funkcję np.
    directFunction();
    //takie proste wywołania mogą zostać rozwiązane przy pomocy early bindingu
    //EARLY BINDING nazywany też static binding -> oznacza że kompilator umie
    //powiązać bezpośrednio nazwę identyfikatora np. nazwę funkcji
    //z adresem maszynowym. Tak więc kiedy kompilator lub linker napotka wywołanie
    //funkcji zastąpi je instrukcją maszynową*(adresem), która mówi pod jaki adres
    //musi skoczyć CPU do funkcji

    //LATE BINDING (dynamic binding)
    //w niektórych programach nie jest możliwe określenie na etapie kompilacji jaka
    //funkcja będzie wywołana aż do runetime
    //Jednym ze sposobów żeby zrobić LATE BINDING są pointery do funkcji
    //Pointery do funkcji wskazują na funkcję a nie na zmienną można wywołać ()
    int (*funcPtr)(double) = notDirectFunction;
    funcPtr(5.5);
    //wywoływanie funkcji przez pointer znane jest jako niebezpośrednie wywołanie
    //funkcji
    //Kompilator nie jest w stanie użeć EARLU BINDING żeby rozwiązać wykonanie
    //funkcji będącej pod wskaźnikiem bo nie wie jaka funkcja zostanie przypisana
    //do pointera przed runetime (mogą być różne funkcje w zależności od ifów)

    //LATE BINDING jest troszeczkę mniej wydajne bo wymaga pośredniogo dodatkowego
    //poziomu. W early bindingu CPU mógł skoczyć bezpośrednio do wykonania funkcji.
    //Z Late bindingiem program musi odczytać adres funkcji trzymane we wskaźniku
    //i dopiero potem skoczyć do tego adresu czyli do funkcji

    //LATE BINDING -> mniej wydajny bo jest dodatkowy pozziom, w którym musi
    //CPU przeczytać adres funkcji z pointera ale bardziej elastyczny
    //bo umożliwia decydowanie w runtime jaka funkcja będzie wywołana

}

class A10              { public: virtual void show(){cout << "A10\n";}
                                 virtual void show2(){cout << "A10\n";};};
class B10 : public A10 { public: virtual void show(){cout << "B10\n";};};
class C10 : public A10 { public: virtual void show2(){cout << "C10\n";};};

class A11 { public: virtual void show(){cout << "A10\n";}};
class B11 { public: virtual void show2(){cout << "B10\n";};};
class C11 : public A11, public B11 {};
void virtualTable()
{
    //vTable tablica wirtualnych funkcji

    //!!!każda klasa, która używa funkcji wirtualnych ma własne vtable
    //jest to statyczna tablica, którą tworzy kompilator w czasie kompilacji
    //posiada jedną pozycję dla każdej funkcji wirtualnej
    //pozycją jest zwykłym wskaźnikiem, który wskazuje na najbardziej dziedziczącą
    //funkcję

    //!!!kompilator dodaje dodatkowo do obiektu klasy ukryty wskaźnik na 
    //klasę bazową *__vptr.
    //*__vptr jest ustawiany automatycznie podczas tworzenia instancji klasy
    //i *__vptr wskazuje na vtable dla danej klasy

    //w przeciwieństwie do *this pointer, który jest przekazywany jako parametr
    //funkcji aby rozwiązać self-references *__vptr jest prawdziwym pointerem
    //więc każda klasa posiadająca wirtualną metodę, będzie większa rozmiarem
    //o ten pointer *__vptr
    //!!!tak więc *__vptr jest dziedziczony!!!!


    //!!!dla klas A10, B10, C10 kompilator stworzy 3 wirtualne tablice
    //po jednej dla każdej klasy, i dodatkowo doda ukryty *__vptr wskaźnik tylko dla
    //klasy bazowej

    //Podczas tworzenia obiektu klasy *__vptr jest ustawiony aby wskazywać na
    //wirtualną tablicę tej klasy. Np jak tworzymy obiekt A10 vptr wskazuje na
    //vtable dla 10. Jak robimy obiekt C10 vptr wskazuje na vtable od C10

    //jak vtable są wypełnione
    //ponieważ są tylko 2 virtual funkcje, każda wirtualna tablica
    //będzie miała 2 entry - j dla funkcji show() a drugi dla funkcji show2()
    //!każde entry jest wypełniane najbardziej dziedziczącą funkcją danego typu klasy
    //Obiekt Base (A10) ma dostęp tylko do siebie więc vtable wskazuje na:
    //A10::show() i A10::show2();
    //Obiekt B10 ma dostęp do metod B10 i A10 ale B10 ma overridowaną funkcję
    //show() więc vTable dla B10 wskazuje na B10::show() i A10::show2()
    //C10 analogicznie do B10

    B10 b10; //vptr wskazuje na B10 vtable
    A10& a10 = b10; //a10 jest base klasą i wskazuje tylko na część A10 jednak
                    //*__vptr jest w części base więc obiekt a10 ma dostęp do niego
                    //więc a10.__vptr wskazuje na B10 vtable
    a10.show(); //program rozpoznaje że show() jest wirtialna i następnie używa
                //vptr do wywołania metody

    //!!!wywołanie wirtualnych funkcji jest wolniejsze ponieważ:
    //musimy użyć __vptr aby uzyskać właściwe vtable
    //musimy indeksować vtable aby znaleźć właściwą funkcję 
    //!!!więc musimy zrobić 3 operacje (w indirect function cal były 2 operacje
    //a w direct tylko jedna operacja)

    C11 c11;
    cout << sizeof(c11) << endl;
    //c11 zajmuje 16 16 bajtów bo ma w sobie 2 vtable jedno z A11 drugie z B11
}


class A12 {public: virtual void show()=0;};
class B12 : public A12 {public: void show() override {cout <<"I am B12\n";}};

class A13 {public: virtual void show()=0;};
void A13::show(){cout << "I am default\n"; }
class B13 : public A13 {public: void show() override {return A13::show();}};

class IClass
{
public:
    virtual int func1(int)=0;
    virtual void func2()=0;
    virtual ~IClass();
};
void pureVirtualFunctionsAbstractBaseClasesAndInterfaces()
{
    //pure virtual funcitons -> abstract functions nie mają ciała
    //!!!są placeholderem, który ma być redefiniowany przez klasy dziedziczace
    //teraz zależy od klasy jak będzie zaimplementowana funkcja

    //klasa z funkcją wirtualną zerową jest klasą abstrakcyjną
    //czyli nie można utworzyć jej obiektu

    //żeby uniemożliwić utworzenia obiektu już nie trzeba robić
    //konstruktora protected
    B12 b12;
    b12.show();
    //funkcje czysto wirtualne są użyteczne kiedy chcemy mieć implementację funkcji
    //w klasie bazowej ale jedynie klasa dziedzicząca wie jak ją zaimplementować

    //!!!funkcje czystor wirtualne zerowe mogą mieć ciało
    //ciało musi zostać zdefiniowane oddzielnie nie inline
    //metoda jest wciąż roazwżana jako czysto wirtualna zerowa
    //a klasa jako abstrakcyjna i nie może być utworzony jej obiekt
    //A13 a13; ERROR wciąż abstrakcyjna
    //Klasa dziedzicząca wciąż musi overridować tą metodę aby umożliwić
    //utworzenie obiektu B13 b13 -> ERROR
    //Dobre kiedy chcemy dostarczyć domyślną implementację ale wciąż zmusić
    //klasę dziedziczącą do przeciążenia
    //lecz klasa dziedziczą może wywołać domyślną implementację
    B13 b13;
    b13.show();
    //nie jest to często stosowane

    //Interface classes
    //!!!nie ma member zmiennych a wszystkie funkcje są wirtualne czysto zerowe
    //nie ma więc żadnej implementacji
    //użyteczne kiedy chcemy zaimplementować całą funkcjonalność w klasach
    //dziedziczących
    //!!!często nazwy plików z interfejsami zaczynają się od I

    //!!!używając Interfejsy można zmieniać jedną implementację na inną
    //bez zmiany kldu, który jej używa
    //!!!Przekazywać do metod obiekty interfejsów a nie klas
    //dzięki temu można przekazać dowolną klasę implementującą interfejs
    //!!!nie zapominać o wirtualnych destruktorach
    //Interface classes są bardzo popularne łatwe w rozszerzaniu i proste w utrzymaniu
    //w Javie i C# doczekały się słówka Interface i chociaż w tych językach
    //nie ma wielodziedziczenia z klas jest z interfejsów
    //gdyż nie mają danych i ciałą funkcji unika się przez to wielu problemów

    //Klasy abstrakcyjne również mają vTable a te wskaźniki na nullptr lub
    //na generyczną funkcję, która wyświetla error __purecall()
}




class A14 {public: void show(){} A14(){cout<<"A14 constructor\n";}};
class B14 : public A14 {public: B14(){cout<<"B14 constructor\n";}};
class C14 : public A14 {public: C14(){cout<<"C14 constructor\n";}};
class D14 : public B14, public C14 {public: D14(){cout<<"D14 constructor\n";}};


class A15 {public: void show(){} A15(){cout<<"A15 constructor\n";}};
class B15 : virtual public A15 {public: B15(){cout<<"B15 constructor\n";}};
class C15 : virtual public A15 {public: C15(){cout<<"C15 constructor\n";}};
class D15 : public B15, public C15 {public: D15(){cout<<"D15 constructor\n";}};
//!!!klasa D wywołuje wszystkie konstruktory klas bazowych
//!!!najpierw A później B lub C zależy od kolejności
//!!!jawne i niejawne Wywołania konstruktora A w klasach B i C zostałyby pominięte !!!
//!!!takie wywołanie powinno być w klasie C !!!!!!!
//!!!!nawet jeżeli klasa D dziedziczyłaby tylko z B to i tak ona tworzy
//obiekt klasy bazowej A bo B dziedziczy wirtualnie

//!!!!!!wirtualna klasa bazowa (A) jest uważana za BEZPOŚREDNIĄ podstawę dla
//najbardziej dziedziczącej klasy (D) dlatego też jest odpowiedzialna
//za jej tworzenie
//Jednak klasy dziedziczące z wirtualnej klasy bazowej wciąż jej potrzebują
//więc kompilator tworzy virtual table dla każdej klasy bezpośredni dziedziczącej
//z klasy wirtualnej czyli tworzy vtable dla (B i C)
//te vTable wskazują na funkcje z najbardziej dziedziczącej klasy
//są więc większe o te wirtualne pointery

class A17
{
    int mVal;
public:
    A17(int val) : mVal(val){}
    void showVal(){cout << "A17 val: " << mVal << endl;}
};
class B17 : virtual public A17
{
public:
    B17() : A17(4444) { std::cout << "Konstruktor klasy B17\n"; }
        //przy tworzeniu obiektu klasy C17 wywołanie konstruktora klasy A17 z tej
        //klasy zostanie pominięte bo A17 jest klasą wirtualną bazową
        //i za utworzenie obiektu klasy !7 odpowiada klasa C17
};
class C17 : public B17
{
public:
    //C17() : B17(){}//nie skompiluje się ponieważ nie ma wywołania konstruktora A17
                   //a wzwiązku z tym że A17 jest wirtualną klasą bazową
                   //najbardziej dziedzicząca klasa odpowiada za jej utworzenie
    //C17() : B17(), A17(3333){} //B17 byłoby zainicjalizowane i tak po A17
                    //zmieniam kolejność bo kompilator daje ostrzeżenia
    C17() : A17(3333), B17() {}
};

void virtualBaskClass()
{
    cout << "X1---------------------------\n";
    //Dla klas ABCD14 diagram dziedziczenia NIE wygląda tak
    /*
         A
       /   \
      B     C
       \   /
         D
    */
    //a tak jak poniżej
    /*
        A     A
        |     |
        B     C
         \   /
           D
    */
    //więc mamy 2 kopie klasy A14
    //nie można więc wykonać żadnej metody z klasy A i użyć zmiennej z klasy A bo
    //wywołanie będzie dwuznaczne
    //!!!!można wywołać jeżeli jedna z klas ją przeciąża ale tylko jedna
    D14 d14;
    cout << "Rozmiar klasy bez wirtualnego dziedziczenia: " << sizeof(D14) << endl;
    //2B czyli pusta
    //d14.show(); AMBIGOUS
    cout << "X2---------------------------\n";
    //Zwykle chcemy mieć jednak jedną kopię klasy bazowej współdzielonej przez B i C
    //używamy do tego słówka virtual na liście dziedziczenia
    //Tworzy to virtualną klasę bazową
    D15 d15;
    d15.show();
    cout << "Rozmiar klasy z wirtualnym dziedziczeniem: " << sizeof(D15) << endl;
    //16B -> 2 pointery na vtable

    //kolejne problemy
    //kto jest odpowiedzialny za stworzenie klasy bazowej ?
    //okazuje się, że klasa D (wow)
    //!!!jest to jedyny moment w którym klasa D może wywołać
    //konstruktor niebezpośredniego rodzica

    //wirtualne klasy bazowe są zawsze tworzone przed niewirtualnymi
    //klasami bazowymi co zapewnia że będą utworzone przed klasami derived

    //Jeżeli klasa dziedziczy z jednej lub więcej klas, które mają wirtualnych
    //rodziców, najbardziej dziedziczaca klasa jest odpowiedzialna za utworzenie
    //klasy bazowej

    //!!!pusta klasa ma rozmiar 1 bo standard C++ nie pozwala aby miała 0
    //umożliwiłoby to aby 2 różne obiekty miały ten sam adres
    //Empty a, b;
    //if(&a == &b) -> po stworzeniu obiektu a stos by się nie przesunął
    //i b mogłoby mieć ten sam adres podobnie z użyciem operatora new dla sterty

    //!!!!ciekawostka
    int& ir = *new int {5};
    cout << ir << endl;
    delete &ir;
    //dla zmiennych które są niszczone w swoim scope lepiej zrobić to na stosie
    //bnie można rzucać wyjątkami w destruktorze


    cout << "X3---------------------------\n";
    C17 c17;
    c17.showVal();
    //initjalizacja konstruktora klasy A17 została wykonana poprzez klasę C17
    //mimo że jest też na liście inicjalizacyjnej klasy B17
    cout << "X4---------------------------\n";
}

#include <vector>
#include <functional>
class A16
{
public:
    virtual void show() {cout << "I am a A16\n";}
    A16(){cout<<"A14 constructor\n";}
};
class B16 : public A16
{
public:
    B16(){cout<<"B14 constructor\n";}
    void show() {cout << "I am a B16\n";}
};
void objectSlicing()
{
    cout << "object slicing ==================\n";
    //wskaźnik klasy bazowej, który wskazuje na obiekt klasy dziedziczącej widzi
    //tylko część klasy bazowej, część klasy dziedziczącej ciągle istnieje
    //ale nie jest widziana przez obiekt klasy bazowej
    //jednak dzięki funkcją wirtualnym mamy dostęp do metod klasy dziedzuczącej

    //!!!inicjalizacja obiektu obiektem klasy pochodnej
    B16 b16;
    b16.show();
    A16 a16 = b16;//konstruktor kopiujący
    //Tylko część Base jest kopiowana !!!!!
    //!!!część klasy B została odcięta

    //!!!przypisanie do obiektu klasy bazowej obiektu klasy pochodnej jest
    //nazywane "object slicing"
    a16.show();//ponieważ A16 nie ma części derived show() wskazuje na
    //A16::show()

    //object slicing zgarza się sporadycznie głównie gdy przekazujemy do jakiejś
    //metody obiekt Deiedziczący a metoda odbiera go przez wartość jako obiekt
    //bazowy
    //i tu się można przejechać bo wykona się netoda z klasy bazowej
    //jak byłby pointer lub referencja wykonałaby się metoda z klasy dziedziczącej


    cout << "reference_wrapper ==================\n";
    //Często też występuje w wektorze jak dodajemy element a wektor trzyma
    //wartości a nie pointery, wtedy też wykona się metoda z base

    //w wektorze nie można trzymać referencji bo referencje nie są assignable
    //czyli są inicjalizowane i nie można zmienić tego na co wskazują
    //czyli nie da sie pobrać ich adresu jedynie adres tego na co wskazują
    //musi być możliwość jej przypisania przez funkcję (inicjalizacja nie wystarczy)
    vector<int> vi;
    //vector<const int> vic; ERROR
    //vector<int&> vir; ERROR
    //podsumowująć alementy wektora muszą mieć możliwość przypisania a
    //consty i referencje mogą być jedynie inicjalizowane


    //Trzymanie referencji w wektorze <functional> header
    //std::reference_wrapper - klasa ta działa jak referencja ale pozwala na
    //assigmenty i kopiowanie więc nadaje się dla wektora
    //nie może być obiektem anonimowym bo będzie reference dangling

    vector<reference_wrapper<A16>> vrwi;
    B16 b162;
    A16 a162;
    vrwi.push_back(b162);
    vrwi.push_back(a162);

    reference_wrapper<A16> rw {b162};
    vrwi.push_back(rw);
    rw.get().show();
    cout << "Sizeof reference_wraper object: " << sizeof(rw) << endl;


    //FrnkenObject XD
    B16 b163;
    B16 b164;
    A16& a163 = b163;
    a163 = b164;//wartość a nie adres referencji bo ten jest niezmienny

    //w ostatniej linii b164 nie zostanie skopiowane w miejsce b163 ponieważ
    //referencja a163 jest typu A16 a nie B16, jeżeli referencja bałaby typu B16
    //takby to zadziałało
    //ale a163 jest typu A16(czyli klasa bazowa) więc tylko część Base zostanie
    //skopiowana
    //operator= nie jest tomyślnie wirtualny więc tak to działa jak wyżej napisane

    //tak więc b163 ma teraz część A16 z obiektu b164 a część B16 z obiektu b163
    //jeżeli część B16 miałaby jekieś member zmienne

    //ogólnie obiekt jest teraz zepsuty składa się z dwóch i nie jest łatwo temu
    //zapobiec

    //C++ pozwala na przypisanie obiektu klasy pochodnej do obiektu klasy bazowej
    //poprzez object slicing -> i często powoduje to błędy
    //!!!!!!!unikać
    //!!!!unikać przekazywania przez wartość



}