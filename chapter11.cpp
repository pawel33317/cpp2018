#include <iostream>
#include "chapterS.hpp"

void dziedziczenie();

void chapter11run()
{
    printf("\n\n-----chapter 11 started-----\n");
    dziedziczenie();
}



class Base
{
public:
    Base() { std::cout << "Base constructor\n"; }
    ~Base() { std::cout << "Base destructor\n"; }
    void printName() { std::cout << "Base class printName method\n";}
};
class Derived : public Base
{
public:
    Derived() { std::cout << "Derived constructor\n"; }
    ~Derived() { std::cout << "Derived destructor\n"; }
    void printName() { std::cout << "Derived class printName method\n";}
};
void dziedziczenie()
{
    //inny sposób obok kompozycji do tworzenia złożonych klas
    //is a
    //uzyskanie metod i pól z innych klas i ich rozszerzenie

    //hierarchia pokazuje połączenia obiektów
    //można dziedziczyć z klas które już dziedziczą z klas
    {Base b; b.printName();}
    std::cout << "1========================================\n";
    {Derived d; d.printName();}
    std::cout << "2========================================\n";
    Derived* d2 = new Derived();
    d2->printName();
    delete d2;
    std::cout << "3========================================\n";
    Base* b2 = new Derived();//Wywola sie z base bez polimorfizmu
    b2->printName();
    delete b2;//BRAK WYWOLANIA DESTRUKTORA KLASY POCHODNEJ
    std::cout << "4========================================\n";
    Derived d4;
    Base* b3 = &d4;
    d4.printName(); //z derived
    b3->printName();//z base
    nicNieRob(b3);
    //delete b3; -> niewolno bo jest na stosie
    //Derived* d5 = new Base(); Derived to nie base => czlowiek to nie sportowiec

    //!!!klasa derived w rzeczywistości nie jest klasą base a składa się z dwóch
    //części Base part oraz Derived part
    //C++ tworzy obiekty które dziedziczą po innej klasie w fazach
    //1: most-base class jest konstruowana jako pierwsza
    //2: tworzona jest każda kolejna dziedzicząca klasa w kolejności

    //1:alokacja miejsca na Base
    //2:konstruktor Base 
    //3:konstruktory pól które są częścią base
    //4:alokacja miejsca na Derived
    //5:konstruktor Derived
    //6:konstruktory pól któe są częścią base
}
