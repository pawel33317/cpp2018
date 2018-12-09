#include <iostream>
using namespace std;

void potrzebaWyjatkowiPodstawy();

void t_14_exceptions()
{
    cout << "-----chapter 14 exceptions-----" << endl;
    potrzebaWyjatkowiPodstawy();
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