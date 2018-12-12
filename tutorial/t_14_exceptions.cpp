#include <iostream>
using namespace std;

void potrzebaWyjatkowiPodstawy();
void wyjatkiiStos();
void catchAllAndSpecifiers();

void t_14_exceptions()
{
    cout << "-----chapter 14 exceptions-----" << endl;
    potrzebaWyjatkowiPodstawy();
    wyjatkiiStos();
    catchAllAndSpecifiers();
}

void potrzebaWyjatkowiPodstawy()
{
    //wcześniej assert(), cerr(), and exit() do obsługi wyjątków

    //funkcja może zwracać np -1 jak będzie źle zamiast wyjątku
    //ale jest to mylące bo niewiadomo np czy jak jest -1 wartość jest prawidłowa
    //trzeba grzebać w kodzie
        //dodatkowo funkcja może zwracać 1 wartość więc tracumy na kod błądu
    //można też dodać parametr przez referencję, ale to brzydki kod
    //kolejny sposób to sprawdzanie każdego wywołania funkcji np podczas operacji
        //na pliku np open readDouble readInt...

    //problem jest też z konstruktorami bo nei zwracają wartości a jak coś
        //się posypie nie ma jak poinformować

    //wyjątki pozwalają na oddzielenie normalnego flow od error flow

    //throw statement używany jest do sygnalizacji exception
        //zwany jest powszechnie jako raising an exception
        //zawiera zwykle error code i opis problemu

        //throw -1, throw ERROR_READ, throw MyException("blabla");

    //try blok nie mówi jak obsłużyć wyjątek a jedynie, że przechwyć wyjątek
        //który wystąpi w try bloku

    //catch obsługuje wyjątek dla ppojedynczego typu danych

    //try i catch współpracują
        //try wychwyca raised exception i routuje go do odpowiedniego catch'a
        //try musi mieć przynajmniej 1 catch
    //exception złapane przez try i zroutowane do catch nazywane jest handled
        //exception a flow programu wznowi się normalnie po catch

    //parametry catcha działają tak jak funkcji
        //proste odbierać przez value, a inne przez const referencje
        //można ominąć nazwę wyjątku w catch jak nie chcemy jej uzywać

    try
    {
        throw -11;
    }
    catch(double)
    {
        cerr << "Zlapalem doubla" << endl;
    }
    catch(int)
    {
        cerr << "Zlapalem inta" << endl;
    }
    catch(...)
    {
        cerr << "Zlapalem cos innego" << endl;
    }

    //po zgłoszeniu wyjątku wykonanie programu skacze natychmiast do najbliższego
    //try (propagując stos jeśli konieczne aby znaleźć otaczający blok try)
    //jeżeli jakiś catch obsługuje exception dany blok jest wywoływany i exception
    //rozważane jako obsłużone
        //jeżeli żaden z catchy nie obsługuje wyjątku wykonaniue programu
    //szuka kolejnego otaczającego bloku try, jeżeli nie znajdzie program failuje
    //z błędem wyjątku

    //!!!kompilator nie wykona niejawnej konwersji lub promocji w przypadku
    //dopasowywania wyjątków np char nie będzie rozpatrywane jako int

    //catch'e zwykle robią:
        //prontuja error
        //zwracają wartość lub error code do wywołujacego
        //zgłaszają inne exception do wyższego bloku try (nie będzie obsłużone
            //przez aktualny try)
}

static int count()
{
    throw "exception :)"s;
}
void wyjatkiiStos()
{
    //throw nie musi być bezpośrednio w bloku try
    //wyjątki więc propagują w górę stosu podczas rzucenia

    try
    {
        int i = count();
        cout << i;
    }
    catch(const std::string& s)
    {
        cout << "Zlapalem wyjatek: " << s << endl;
    }
    //najpierw program sprawdza czy wyjątek może być obsłużony natychmiast
        //czyli czy throw było bezpośrednio w try
    //jeżeli nie aktualna funkcja jest kończona i program sprawdza
    //czy caller funkcji może obsłużyć wyjątek
        //funkcje sa dalej kończone aż zostanie napotkana funkcja obsługująca
        //lub aż main zostanie zakończony bez obsługi wyjątku
    //taki proces nazywa się unwinding the stack

    //w skrócie funkcja count mówi: mamy problem i że nie umie go rozwiązać

    //wyjątek nie jest od razu obsługiwany w count, bo count nie wie jak go
        //rozwiązać, dla jednego callera funkcji count może to być
        //fatal error a dla innego nie
}




static void func1() throw() {  } //nie rzuca wyjątków
                                 //jeżeli rzuci program zostanie zakończony

//static void func2() throw(int) {} //nie rzuca wyjątków
    //C++17 zakazuje dynamicznych specyfikatorów wyjątków

//static void func3() throw(...) {} //nie rzuca wyjątków
    //C++17 zakazuje dynamicznych specyfikatorów wyjątków
void catchAllAndSpecifiers()
{
    //jeżeli main się zwinie ze stosu (nikt nie obsłuży wyjątku), system
    //operacyjny poinformuje o wystąpieniu wyjątku
        //to jak poinformuje zależy od systemu zwykle error info

    //catch-all handler
        //powinien być umieszczony na końcu listy catch'u
    try
    {
        throw -1;
    }
    catch(...)
    {
        cout << "Zlapalem wyjatek przez ..." << endl;
    }

    //można użyć w mainie do większości kodu a po catchu zrobić jakąś akcję awaryjną
    //np w try runGame() a w catch ... lub po saveGameData()
    //zapobiegnie to crashowi apki i umożliwi jakieś akcje dodatkowe

    //specyfikatory
        //rzadko używane .., czasami nawet źle wspierane przez kompilatory
    //moechanizm pozwalający na
    func1();
    //func2();
    //func3();
}