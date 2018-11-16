
#include <iostream>
#include <memory>
#include "chapterS.hpp"
using namespace std;

void w_prostaFabryka();
void w_statycznaFabryka();

void w_fabryka()
{
    printf("-----w_fabryka-----\n");

    //Uzywając New uzależniamy się od konkretnej implementacji a jedna reguła:
    //dependency inversion principle mówi:

    //!!!Uzależniaj kod od abstrakcji a nie rzeczywistych klas

    //kolejna zasada
    //!!!System powinien być otwarty na rozbudowę a zamknięty na modyfikację

            /*
                void doAction(String type) {
                Product product;
                if (type.equals("round")) {
                    product = new RoundProduct();
                } else if (type.equals("square")) {
                    product = new SquareProduct();
                }
                
                product.doSomething();
                product.doSomethingElse();
                //i mnóstwo innych operacji...
                }
            */

    //Powyższy kod jest słaby bo przy rozbudowie programu trzeba będzie zmienić
    //kod powyższego if'a, dodatkowo kod nie jest zamknięty na zmiany, jak
    //będziemy chcieli wywalić produkt lub dodać będziemy musieli zmieniać
    //powyższy kod

    //Rodzaje fabryk
    //Prosta - simple factory
    //Statyczna - static factory
    //Metofda fabrykująca - factory method
    //Fabryka abstrakcyjna - abstract factory

    w_prostaFabryka();
    w_statycznaFabryka();
}





class Figura
    { public: virtual void show() const { std::cout << "I am Figura\n"; } 
      virtual ~Figura(){}};
class Kolo : public Figura
    { public: virtual void show() const override { std::cout << "I am Kolo\n"; }
    virtual ~Kolo(){}};
class Kwadrat : public Figura
    { public: virtual void show() const override { std::cout << "I am Kwadrat\n"; }
    virtual ~Kwadrat(){}};
class SimpleFactory
{
public:
    std::unique_ptr<Figura> virtual getFigura(int type)
    {
        if (type == 1)
            return std::make_unique<Kolo>();
        else
            return std::make_unique<Kwadrat>();
    }
};
class FiguraHandler
{
public:
    std::unique_ptr<Figura> f;
    FiguraHandler() = delete;
    FiguraHandler(SimpleFactory&& sf)
    {
        f = sf.getFigura(1);
        f->show();
    }
};
void w_prostaFabryka()
{
    printf("-----w_prostaFabryka-----\n");
    //FiguraHandler fh(SimpleFactory()); //to traktuje jako deklarację czegoś oO

    FiguraHandler fh {SimpleFactory()};
    //Prosta fabryka jest wywoływana bezpośrednio przez klasę, która chce
    //utworzyć obiekt
}




class StaticFactory
{
public:
    std::unique_ptr<Figura> static getFigura(int type)
    {
        if (type == 1)
            return std::make_unique<Kolo>();
        else
            return std::make_unique<Kwadrat>();
    }
};
class FiguraStaticHandler
{
public:
    FiguraStaticHandler()
    {
        auto figura = StaticFactory::getFigura(1);
        figura->show();
    }
};
void w_statycznaFabryka()
{
    //prosta fabryka mająca metodę statyczną więc nie trzeba robić obiektu
    //fabryki, jednak nie można zastosować dziedziczenia, żeby przekazać
    //dodatkowe parametry w konstruktorze

    //!!!Czyli słabe rozwiązanie !!!

    //np chcielibyśmy dodać możlowośc utworzenia klasy Koło na podstawie kąta
    //np trójkąt, wykorzystując prosta fabrykę możnaby zrobić klasę:
    //TriangleSimpleFactory dziedziczacą po SimpleFactory i przekazać taki obiekt
    //do FiguraHandler

    //łamiemy w fabryce statycznej zasadę
    //!!!staraj się aby współpracujące obiekty były ze sobą luźno powiązane

    FiguraStaticHandler fh {};
}