#include <iostream>
#include "chapterS.hpp"

void pointersAndReferencesToBaseClass();
void funkcjeVirtualIPolimorfizm();

void chapter12run()
{
    printf("\n\n-----chapter 12 started-----\n");
    pointersAndReferencesToBaseClass();
    funkcjeVirtualIPolimorfizm();
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

    //!!!Domyślnie funkcje nei są wirtualne z powodu optymalizacji
    //rozwinięcie funkcji virtualnej trwa dłużej niż funkcji niewirtualnej
    //!!!dodatkowo kompilator musi zaalokować dodatkowy pointer dla każdego obiektu
    //klasy dla funkcji wirtualnych
}