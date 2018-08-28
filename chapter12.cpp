#include <iostream>
#include "chapterS.hpp"

void pointersAndReferencesToBaseClass();
void funkcjeVirtualIPolimorfizm();
void overrideFinalAndCOVARIANT();


void chapter12run()
{
    printf("\n\n-----chapter 12 started-----\n");
    pointersAndReferencesToBaseClass();
    funkcjeVirtualIPolimorfizm();
    overrideFinalAndCOVARIANT();
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