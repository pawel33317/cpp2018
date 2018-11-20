#include <iostream>
using namespace std;

void functionTemplates();
void classTemplates();
void functionTemplateSpecialization();
void classTemplateSpecialization();

void t_chapter13run()
{
    printf("-----chapter 13 started-----\n");
    functionTemplates();
    classTemplates();
    functionTemplateSpecialization();
    classTemplateSpecialization();
}


template<typename T>//template declaration, aby stworzyć templateparametr używamy
                    //słowa typename lub class (nie ma między nimi różnicyw tym kontekście)
const T& myMax(const T& a, const T& b)
{
    return a > b ? a : b;
}
void functionTemplates()
{
    //templatku funkcji - wzorzec służący do robienia podobnych funkcji
    //placeholdery (template type parameters) zamiast typów
    cout << myMax(5, 66) << endl;
    cout << myMax(5.44, 66.19) << endl;//zostanie stworzona nowa funkcja
    cout << myMax<double>(5, 12) << endl;
    //w związku, że parametrami mogą być obiekty lepiej przekazać obiekty przez
    //referencje

    //dla więcej typów tamplate<typename T1, typenameT2>

    //templatki sa dobre bo nie trzeba powielać funkcji i przez to można uniknąć
    //błędów

    //stare kompilatory miały problemy z templatkami
    //kompilatory w przypadku błędów potrafią pokazywać szalone info dla templatek
    //mogą zwiększają czas kompilacji i rozmiar kodu jeżeli nie będzie więcej
    //niż jednego użycia (templatka będzie rekompilowana dla każdego pliku)

    //kompilator kompiluje templatki po napotkaniu na wszystkie wywołania
    //tak stworzona funkcja nazywa się function template instance

    //kiedy kompilator napotyka myMax(4,3); kompilator replikuje templatekę i tworzy
    //jej instancję: const int& myMax(const int& a, const int& b){...}

    //jeżeli nie wywołamy nigdy funkcji z templatki, żadna jej istancja nie będzie utworzona
    //oczywiście obiekt przekazany do templatki musi mieć operatory/metody
    //wykorzystywane w templatce
}

#include<assert.h>
template <class T>
class MyArray
{
    int mSize;
    T* mData;
public:
    MyArray(int size):mSize(size),mData(new T[size]){}
    ~MyArray(){delete[] mData;}
    T& operator[](int index)
    {
        assert(index >=0 && index < mSize); 
        return mData[index];
    }
    void erase(){ delete[] mData; mData = nullptr; mSize = 0; }
    //int getLength(){ return mSize; }
    int getLength();
};
template<class T>
int MyArray<T>::getLength(){ return mSize; }
//bez <T> error: ‘template<class T> class MyArray’ used without template parameters

template<class T, int size>
class StaticArray
{
    T mArr[size];
public:
    T* getArray();
    T& operator[](int index){return mArr[index];}
};

template<class T, int size>
T* StaticArray<T, size>::getArray() { return mArr; }

void classTemplates()
{
    MyArray<double> myArr(5);
    myArr[4] = 4;

    //każda meber funkcja template klasy deklarowana poza klasą musi mieć
    //własną template deklarację

    //template klasy są tworzone w ten sam sposób czyli na żądanie w miejscu
    //wywołania

    //np vector jest template klasą vector<int>

    //templatki są szablonami do tworzenia klas i funkcji

    //w przypadku normalnych klas i funkcji umieszcza się headery w plikach hpp
    //a definicje w plikach cpp o tej samej nazwie, więc źródło klasy jest
    //kompilowane jako osobny plik projektu
    //!!!w przypadku tamplatek to nie zadziała
    //jeżeli wywołamy funkcję z template klasy, która była zdefiniowana w pliku cpp
    //dostaniemy linker error:
    //unresolved external symbol "public: int __thiscall Array::getLength(void)" (?GetLength@?$Array@H@@QAEHXZ)

    //aby kompilator użył templatki musi widzieć definicje, deklarację
    //i typ templatki

    //C++ kompiluje pliki indywidualnie kiedy Array.h jest inkludowana przez main
    //zawartość templatki ląduje w pliku main.cpp kiedy kompilator widzi, że jest
    //potrzebna instancja MyArray<int> tworzy ich instancje i kompiluje jako
    //część main.cpp,   jednak gdy dojdzie do osobnego skompilowania pliku MyArray.cpp
    //zapomni on, że potrzebujemy tablicy dla <int> więc funkcja szablonu nigdy
    //nie zostanie stworzona i będzie błąd linkera bo nie będzie definicji dla
    //MyArray<int>

    //abo powyższy problem rozwiązać można np dać cały kod w pliku header
    //wada tego jest taka, że będzie wiele lokalnych kopii co prawdopodobnie
    //wydłuży czas kompilacji i linkowania (linker powinien usunąć duplikaty
    //więc sam plik .exe powinien być ok) - jest to preferowane rozwiązanie !!!!!

    //inne rozwiązanie to zmienić rozeszrzenie .cpp na inl (pd inline) i wpliku
    //.hpp robić include pliku .inl (zadziała tak samo jakby było w pliku .cpp)

    //inne podejscie: three-file approach, definicja klasy template w headerze
    //template class membery w .cpp i trzeci plik templates.cpp, który zweiera
    //wszystkie użycia templatki:
    //template class Array<int>; // Explicitly instantiate template Array<int>
    //template class Array<double>; // Explicitly instantiate template Array<double>
    //template class command wymusi na kompilatorze jawne zinstancjowanie klasy
    //template, ponieważ templates.cpp jest w naszym projekcje zpstanie
    //skompilowane i zlinkowane wszędzie -> bardziej wydajna metoda ale wymaga
    //utrzymywania pliku templates.cpp




    //!!!!!templatki mogą przyjąć też inny parametr zwany non-type parameter
    //jest on specjalnym typem parametru, który nie zastępuje typu ale WARTOŚĆ
    //np: wartość całkowita lub enumerator, pointer lub referencja do const obiektu
    //pointer lub referencja do funkcji lub metody, std::nullptr_t
    StaticArray<int, 10> sa;
    sa[4] = 4;
    cout << sa[4] << endl;
    //!!!nie musieliśmy dynamicznie alokować mArr, ponieważ dla każdej instancji
    //klasy StaticArray size jest constant
    //!!!!!!!!!teh ficzer jest używany w bibliotece standardowej w klasie array
    //std::array<int, 60> arr;
}


template<class T>
class Storage1
{
private:
    T m_value;
public:
    Storage1(T value){m_value = value;}
    ~Storage1(){}
    void print(){std::cout << m_value << '\n';}
};
#include <cstring>
template<>
void Storage1<double>::print()
{
    std::cout << std::scientific << m_value << endl;
}
#include <cstring>
template<>
Storage1<char*>::Storage1(char* value)
{
    m_value = new char[std::strlen(value) + 1];
    std::strcpy(m_value, value);
}
template<>
Storage1<char*>::~Storage1()
{
    delete[] m_value;
}
void functionTemplateSpecialization()
{
    cout << "-----------------function specialization-------\n";
    //function templates służą do wygenerowania wielu funkcji o takiej
    //samej implementacji ale różnych typach

    //czasami jednak chcemy zrobić inną implementację dl jakiegoś typu
    Storage1<int> iVal{5};
    Storage1<double> dVal{5.23};
    iVal.print();
    dVal.print();//wykona się specjalizowana

    //aby zrobić specjalizację: zdefinuiwać spacjalizowaną funkcję (jeżeli jest to
    //metoda to zrobić to poza klasą), zmieniając typ templatki na nasz

    //gdy kompilator zacznie tworzyć Storage1<double>::print zauważy, że istnieje
    //jawnie zdefiniowana funkcja i uzyje naszej jawnej zamiast generować z
    //templatki

    //template,. mówi kompilatorowi że chodzi o function template ale nie przyjmuje
    //template parametrów (bo w tym przypadku wszystkie parametry określiliśmy
    //jawnie)

    char* stringg = new char[40];
    std::strcpy(stringg, "ala ma kota");
    cout << stringg << endl;
    Storage1<char*> cVal {stringg};
    delete[] stringg;
    //cVal.print();//śmieci bo jest po delete trzeba spacjalizację

    cVal.print();//po dodaniu specjalizacji
}

template <class T>
class Storage8
{
private:
    T m_array[8];
public:
    void set(int index, const T &value){m_array[index] = value;}
    const T& get(int index){return m_array[index];}
};
template <>
class Storage8<bool>
{
private:
    unsigned char m_data = 0;
public:
    void set(int index, bool value)
    {
        if(value)
            m_data |= 1 << index;
        else
            m_data &= ~(1 << index);
    }
    const bool get(int index)
    {
        return m_data & (1 << index);
    }
};
void classTemplateSpecialization()
{
    Storage8<int> si;
    for(int i = 0; i < 8; ++i)
        si.set(i, i);

    //dla bool'a jest małowydajne, można zrobić nową klasę ale będzie lipa
    //bo ta będzie służyła dla wszystkich poza boolami a dla booli będzie inna
    //klasa z inną nazwą

    //class template specializationa pozwala na specjalizacje template class
    //dla szczególnego typu
    //specialized functions/classes mają pierwszeństwo nad ogólnym template
    //!!!class template specializations są traktowane nak całkowicie niezalezne klasy
    //wiec możemy zmienić wszystko

    Storage8<bool> sb;
    for(int i = 0; i < 8; ++i)
        sb.set(i, true);

    for(int i = 0; i < 8; ++i)
        cout << sb.get(i) << ",";
    cout << endl;

    //template<> mówi kompilatorowi, że poniższe dotyczy szablonu
    //dodaliśmy <bool> do klasy aby pokazać, że dotyczy to tylko boola
    //warto utrzymywać wspólny interfejs między templatkami a ich specjalizacjami

    //PARTIAL TEMPLATE SPECIALIZATION NOT DONE
}