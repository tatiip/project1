
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;


//СОЗДАЕМ СТРУКТУРУ
struct Node                             
{
    /*Общие переменные для всех классов
    ==================================*/
    int height;     //Рост спортсмена
    string family;   //Фамилия спортсменов


    //Переменная для гонщиков
    string car;      //Модель машины, для гонщика
    

    //Переменная для пловцов
    double time;    //Время, за которое пловец проходит дистанцию в 100м.
    


    //Переменная для баскетболистов
    int points;     //Количество очков за профессиональную карьеру
    

    Node* Next, * Prev;     //Указатели на адреса следующего и предыдущего элементов списка
};


//НАЧАЛО КОНЦА

//Класс - родитель
class sportsman           
{
    public:
        
        Node* Head, * Tail;     //Указатели на адреса начала списка и его конца


        sportsman() : Head(NULL), Tail(NULL) {};    //Конструктор


        //Деструктор
        ~sportsman() {
            while (Head)                       //Пока по адресу на начало списка что-то есть
            {
                Tail = Head->Next;             //Резервная копия адреса следующего звена списка
                delete Head;                   //Очистка памяти от первого звена
                Head = Tail;                   //Смена адреса начала на адрес следующего элемента
            }
        };

        
        /*ФУНКЦИЯ УДАЛЕНИЯ КОНКРЕТНОГО ЭЛЕМЕНТА ДВУСВЯЗНОГО СПИСКА
        ЭТО ОБЩИЙ МЕТОД, КОТОРЫЙ МОГУТ ИСПОЛЬЗОВАТЬ ВСЕ КЛАССЫ-НАСЛЕДНИКИ*/
        void Del(int num, int &kol) { //Параметр - переменная num, которая указывает номер элемента для удаления
            
            //УДАЛЕНИЕ ПЕРВОГО ЭЛЕМЕНТА
            
            //В списке есть другие элементы
            if ((num == 1) and (Head->Next)) { 
                Node* temp = Head;	//Указываем на 1-ый элемент (начало)
                Head = Head->Next;	//Сдвигаем указатель на следующий элемент
                Head->Prev = NULL;	//Делаем предыдущий элемент пустым
                delete temp; //Удаляем начало
                kol--; //Уменьшаем счетчик
                return;	
            }

            else 
               //В списке 1 элемент
               if ((num == 1) and (Head == Tail)) {

                //обнуляем все, что необходимо
                Head->Next = NULL;	 
                Head = NULL;

                delete Head;     //Удаляем  указатель на 1 элемент (начало)
                kol = 0;		 //Обозначаем, что в списке ноль элементов
                return;	
            }
            

            //Удаляемый элемент является последним элементом списка
            if (num == kol) {
                Node* temp = Tail;  //Указываем, что нам нужен хвост
                Tail = Tail->Prev;	//Отодвигаем хвост назад
                Tail->Next = NULL;	//Обозначаем, что впереди за хвостом пусто
                delete temp;	    //Очищаем память от бывшего хвоста
                kol--;		    //Уменьшаем счетчик элементов
                return;		      
            }


            //Удаляемый элемент не первый и не последний
            Node* temp = Head, * temp2;  //temp-Удаляемый элемент, temp2 - переменная для временного запоминания адреса удаляемого элемента

            for (int i = 0; i < num - 1; i++) temp = temp->Next;  //Идем к адресу удаляемого элемента

            temp2 = temp;	//Временно запоминаем адрес удаляемого элемента
           
            //Записываем данные
            temp2->Prev->Next = temp->Next;	           
            temp2->Next->Prev = temp->Prev; 

            delete temp; //теперь освобождаем память, удалив адрес на начало удаляемого элемента
            kol--;    
        }

};





//Гонщик    
//Класс-наследник 
class racer : public sportsman {
    
public:

    racer() : sportsman() {};    //Конструктор

    void Add(string k, int x, string model, int &kol) {
        {
            Node* temp = new Node;         //Выделение памяти под новый элемент структуры
           
            temp->Next = NULL;   //Указываем, что изначально по следующему адресу пусто
            
            //Записываем значение в структуру
            temp->height = x;                         
            temp->family = k;
            temp->car = model;
            
            kol++;

            if (Head != NULL)                    //Если список не пуст
            {
                temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
                Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
                Tail = temp;                     //Меняем адрес хвоста
            }

            else //Если список пустой
            {
                temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
                Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
            }
        }
    };

    void Show() {
        Node* temp;

        //ВЫВОДИМ СПИСОК С НАЧАЛА
        temp = Head;                       //Временно указываем на адрес первого элемента
        int number = 1;

        cout << "СПИСОК ГОНЩИКОВ:" << endl << endl;

        while (temp != NULL)              //Пока не встретим пустое значение
        {
            cout << "Гонщик №" << number << endl;
            cout << "Фамилия: " << temp->family << endl; //Выводим каждое считанное значение на экран
            cout << "Рост: " << temp->height << endl;       
            cout << "Марка автомобиля: " << temp->car << endl;
            number++;
            cout << endl;
            temp = temp->Next;   //Смена адреса на адрес следующего элемента

        }
        cout << endl;
    };

    //сортировка по росту
    void sort_height() {
        Node* left = Head;                 //Первый элемент — голова
        Node* right = Head->Next;          //Второй элемент — следующий за головой элемент

        Node* temp = new Node;  //Временное звено для хранения всех значений переставляемого звена

        while (left->Next) {       //Обходим по всем звеньям, за исключением крайнего правого
            while (right) {        //Обходим по всем звеньям, включая крайний правый 
                              //(по всем относительно первого левого на текущий момент)
                if ((left->height) < (right->height)) {        //Проверяем необходимость перестановки
                    
                    //И переставляем все внутренние элементы, за исключением указателей связи, местами

                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;          
                    
                    temp->car = left->car;              
                    left->car = right->car;            
                    right->car = temp->car;

                    temp->family = left->family;    
                    left->family = right->family;          
                    right->family = temp->family;
                
                }
                right = right->Next;   //направляем указатель на следующий элемент 
            }
            left = left->Next;       //направляем указатель на следующий элемент 
            right = left->Next;    //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад
        }
    }

    //сортировка по фамилии
    void sort_family() {
        Node* left = Head;                 
        Node* right = Head->Next;          

        Node* temp = new Node;              

        while (left->Next) {                 
            while (right) {              
                if ((left->family) > (right->family)) {        
                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;             

                    temp->car = left->car;              
                    left->car = right->car;            
                    right->car = temp->car;

                    temp->family = left->family;              
                    left->family = right->family;         
                    right->family = temp->family;

                }
                right = right->Next;   
            }
            left = left->Next;          
            right = left->Next;        
        }
    }

    void write_f(ofstream& f) {
        Node* temp;

        temp = Head;                       //Временно указываем на адрес первого элемента
        int number = 1;

        f << "СПИСОК ГОНЩИКОВ:" << endl << endl;

        while (temp != NULL)              //Пока не встретим пустое значение
        {
            //Записываем каждое считанное значение в файл
            f << "Гонщик №" << number << endl;
            f << "Фамилия: " << temp->family << endl; 
            f << "Рост: " << temp->height << endl;        
            f << "Модель автомобиля: " << temp->car << endl;
            number++;
            f << endl;
            temp = temp->Next;             //Смена адреса на адрес следующего элемента

        }
        f << endl << endl;


    }

};



//Баскетболист
//Класс-наследник 
class basketball : public sportsman {

public:

    basketball() : sportsman() {};    //Конструктор

    void Add(string k, int x, int point, int &kol) {
        {
            Node* temp = new Node;               

            temp->Next = NULL;             

            //Записываем значение в структуру
            temp->height = x;
            temp->family = k;
            temp->points = point;

            kol++;

            if (Head != NULL)                    
            {
                temp->Prev = Tail;               
                Tail->Next = temp;               
                Tail = temp;                     
            }

            else 
            {
                temp->Prev = NULL;               
                Head = Tail = temp;              
            }
        }
    };

    void Show() {
        Node* temp;

        //ВЫВОДИМ СПИСОК С НАЧАЛА
        temp = Head;                       
        int number = 1;

        cout << "СПИСОК БАСКЕТБОЛИСТОВ:" << endl << endl;

        while (temp != NULL)              
        {
            cout << "Баскетболист №" << number << endl;
            cout << "Фамилия: " << temp->family << endl;        
            cout << "Рост: " << temp->height << endl;        
            cout << "Очки за карьеру: " << temp->points << endl;
            number++;
            cout << endl;
            temp = temp->Next;             

        }
        cout << endl;
    };

    //сортировка по росту
    void sort_height() {
        Node* left = Head;                 
        Node* right = Head->Next;          

        Node* temp = new Node;              

        while (left->Next) {                 
            while (right) {              
                if ((left->height) < (right->height)) {        
                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;             

                    temp->points = left->points;              
                    left->points = right->points;             
                    right->points = temp->points;

                    temp->family = left->family;              
                    left->family = right->family;            
                    right->family = temp->family;

                }
                right = right->Next;                    
            }
            left = left->Next;                           
            right = left->Next;                            
        }
    }

    //сортировка по фамилии
    void sort_family() {
        Node* left = Head;                 
        Node* right = Head->Next;          

        Node* temp = new Node;              

        while (left->Next) {                 
            while (right) {             
                if ((left->family) > (right->family)) {        
                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;             

                    temp->points = left->points;             
                    left->points = right->points;            
                    right->points = temp->points;

                    temp->family = left->family;              
                    left->family = right->family;             
                    right->family = temp->family;

                }
                right = right->Next;                    
            }
            left = left->Next;                              
            right = left->Next;                            
        }
    }

    void write_f(ofstream &f) {
        Node* temp;
        


        temp = Head;                       
        int number = 1;

        f << "СПИСОК БАСКЕТБОЛИСТОВ:" << endl << endl;

        while (temp != NULL)              
        {
            f << "Баскетболист №" << number << endl;
            f << "Фамилия: " << temp->family << endl;     
            f << "Рост: " << temp->height << endl;        
            f << "Очки за карьеру: " << temp->points << endl;
            number++;
            f << endl;
            temp = temp->Next;             

        }
            f << endl << endl;
        
            
    }
};



//Пловец
//Класс-наследник 
class swimmer : public sportsman {

public:

    swimmer() : sportsman() {};    //Конструктор

    void Add(string k, int x, double time, int &kol) {
        {
            Node* temp = new Node;             



            temp->Next = NULL;                 


            //Записываем значение в структуру
            temp->height = x;
            temp->family = k;
            temp->time = time;

            kol++;

            if (Head != NULL)                   
            {
                temp->Prev = Tail;               
                Tail->Next = temp;               
                Tail = temp;                     
            }

            else 
            {
                temp->Prev = NULL;               
                Head = Tail = temp;              
            }
        }
    };

    void Show() {
        Node* temp;

        //ВЫВОДИМ СПИСОК С НАЧАЛА
        temp = Head;                      
        int number = 1;
        
        cout << "СПИСОК ПЛОВЦОВ:" << endl << endl;

        while (temp != NULL)          
        {   

            cout << "Пловец №" << number << endl;
            cout << "Фамилия: " << temp->family << endl;      
            cout << "Рост: " << temp->height << endl;       
            cout << "Время на 100м: " << temp->time << endl;
            number++;
            cout << endl;
            temp = temp->Next;             
        }
        cout << endl;
    };

    void sort_height() {
        Node* left = Head;                 
        Node* right = Head->Next;          

        Node* temp = new Node;             

        while (left->Next) {                 
            while (right) {             
                if ((left->height) < (right->height)) {       
                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;             

                    temp->time = left->time;              
                    left->time = right->time;             
                    right->time = temp->time;

                    temp->family = left->family;              
                    left->family = right->family;             
                    right->family = temp->family;

                }
                right = right->Next;                    
            }
            left = left->Next;                          
            right = left->Next;                       
        }
    }

    //сортировка по фамилии
    void sort_family() {
        Node* left = Head;                 
        Node* right = Head->Next;          

        Node* temp = new Node;              

        while (left->Next) {                 
            while (right) {              
                if ((left->family) > (right->family)) {        
                    temp->height = left->height;              
                    left->height = right->height;             
                    right->height = temp->height;    

                    temp->time = left->time;              
                    left->time = right->time;             
                    right->time = temp->time;

                    temp->family = left->family;              
                    left->family = right->family;             
                    right->family = temp->family;

                }
                right = right->Next;       
            }
            left = left->Next;                        
            right = left->Next;                             
        }
    }

    void write_f(ofstream& f) {
        Node* temp;

        temp = Head;                   
        int number = 1;

        f << "СПИСОК ПЛОВЦОВ:" << endl << endl;

        while (temp != NULL)            
        {
            f << "Пловец №" << number << endl;
            f << "Фамилия: " << temp->family << endl;       
            f << "Рост: " << temp->height << endl;        
            f << "Время на 100М: " << temp->time << endl;
            number++;
            f << endl;
            temp = temp->Next;            

        }
        f << endl << endl;


    }
};





/*==========================================================================
                        ОСНОВНАЯ ЧАСТЬ ПРОГРАММЫ
==========================================================================*/

int main()
{

    //Смена кодировки для использования кириллицы
    SetConsoleCP(1251); //Для использования при вводе
    SetConsoleOutputCP(1251); //Для использования при выводе

    



    int menu_number = 0; //выбор пунтка меню

    string family, model, style, position;


    int speed , height, points;
    double time;

   

    racer race_lst; //Список гонщиков


    swimmer swim_lst; //Список пловцов


    basketball basket_lst; //Список баскетболистов


    //МЕНЮ ПРОГРАММЫ
    while (menu_number != 2) {


        cout << "Меню программы:" << endl;
        cout << "1. Загрузить базу данных." << endl;
        cout << "2. Завершить работу программы." << endl;
        cout << endl;


        cout << "Введите нужный пункт: ";
        cin >> menu_number;
        cout << endl;


        /*ЕСЛИ ВЫБРАН НЕВЕРНЫЙ ПУНКТ
        ========================================================*/
        if (menu_number < 1 || menu_number > 2) {
            cout << "Вы ввели неверный пункт меню." << endl;
            cout << endl;
        }

        else
            
        /*РАБОТА С БАЗОЙ ДАННЫХ
        ========================================================*/
        if (menu_number == 1) {


            char* name_bd = new char[30];   //Имя базы данных


            cout << "Введите имя базы данных: ";
            cin >> name_bd;


            //*Открытие входного файла txt
            ifstream file(name_bd);
            cout << endl;


            if (!file)
            {
                cout << "Не удалось загрузить базу данных." << endl;
                cout << "Провертье введенные данные и повторите попытку" << endl;
                cout << endl;
                menu_number = 6;
            }


            else
            {   

                //Считывание данных

                int kol;

                int kol1 = 0; //кол-во гонщиков

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    
                    file >> family;
                    file >> height;
                    file >> model;

                    race_lst.Add(family, height, model, kol1);

                }

                int kol2 = 0; //Количество баскетболистов

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    file >> family;
                    file >> height;
                    file >> points;

                    basket_lst.Add(family, height, points, kol2);
                }


                int kol3 = 0; //Количество пловцов

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    file >> family;
                    file >> height;
                    file >> time;

                    swim_lst.Add(family, height, points, kol3);
                }

                file.close();

                cout << "База данных успешно загружена." << endl;
                cout << endl;
                menu_number = 0;

                while (menu_number != 6) {

                    menu_number = 0;

                    cout << "1. Просмотреть базу данных." << endl;
                    cout << "2. Добавить элемент в базу данных." << endl;
                    cout << "3. Удалить элемент из базы данных." << endl;
                    cout << "4. Сортировка элементов." << endl;
                    cout << "5. Сохранить текущую базу данных." << endl;
                    cout << "6. Выход" << endl;


                    cout << endl;


                    cout << "Введите нужный пункт: ";
                    cin >> menu_number;
                    cout << endl;


                    if (menu_number < 1 || menu_number > 6) {
                        cout << "Вы ввели неверный пункт меню." << endl;
                        cout << endl;
                    }

                    else

                        /*===========================================
                                      ПРОСМОТР БАЗЫ ДАННЫХ
                        ===========================================*/
                        if (menu_number == 1) {
                            menu_number = 0;

                            while (menu_number != 5) {
                                cout << "1. Просмотреть всех спортсменов." << endl;
                                cout << "2. Просмотреть гонщиков." << endl;
                                cout << "3. Просмотреть баскетболистов." << endl;
                                cout << "4. Просмотреть пловцов." << endl;
                                cout << "5. Вернуться назад." << endl;
                                cout << endl;

                                cout << "Введите нужный пункт: ";
                                cin >> menu_number;
                                cout << endl;

                                if (menu_number < 1 || menu_number > 5) {
                                    cout << "Вы ввели неверный пункт меню." << endl;
                                    cout << endl;
                                }


                                if (menu_number == 1) {

                                    menu_number = 0;

                                    race_lst.Show();

                                    basket_lst.Show();

                                    swim_lst.Show();

                                }

                                if (menu_number == 2) {
                                    menu_number = 0;
                                    race_lst.Show();

                                }

                                if (menu_number == 3) {
                                    menu_number = 0;
                                    basket_lst.Show();

                                }

                                if (menu_number == 4) {
                                    menu_number = 0;
                                    swim_lst.Show();

                                }

                                if (menu_number == 5) {

                                    //ВЫХОД
                                }
                            }


                        }
                    //===========================================

                        else

                            //===========================================
                            //Добавить элемент в базу данных
                            if (menu_number == 2) {

                                cout << "1. Добавить гонщика." << endl;
                                cout << "2. Добавить баскетболиста." << endl;
                                cout << "3. Добавить пловца." << endl;
                                cout << "4. Вернуться назад." << endl;
                                cout << endl;


                                cout << "Введите нужный пункт: ";
                                cin >> menu_number;
                                cout << endl;

                                if (menu_number == 1) {

                                    menu_number = 0;

                                    cout << "Фамилия спортсмена: ";

                                    cin >> family;
                                    cout << "Рост спортсмена: ";
                                    cin >> height;

                                    cout << "Модель автомобиля: ";

                                    cin >> model;


                                    race_lst.Add(family, height, model, kol1);
                                    cout << "Спортсмен добавлен в базу данных." << endl;
                                    cout << endl;
                                    cout << "Текущая база данных гонщиков: " << endl;
                                    race_lst.Show();
                                    cout << endl;
                                }

                                if (menu_number == 2) {

                                    menu_number = 0;

                                    cout << "Фамилия спортсмена: ";

                                    cin >> family;
                                    cout << "Рост спортсмена: ";
                                    cin >> height;


                                    cout << "Очков за карьеру: ";
                                    cin >> points;
                                    cout << endl;

                                    basket_lst.Add(family, height, points, kol2);
                                    cout << "Спортсмен добавлен в базу данных." << endl;
                                    cout << endl;
                                    cout << "Текущая база данных баскетболистов: " << endl;
                                    basket_lst.Show();
                                    cout << endl;

                                }

                                if (menu_number == 3) {

                                    menu_number = 0;

                                    cout << "Фамилия спортсмена: ";

                                    cin >> family;
                                    cout << "Рост спортсмена: ";
                                    cin >> height;

                                    cout << "Время преодоления 100 м.: ";
                                    cin >> time;
                                    cout << endl;

                                    swim_lst.Add(family, height, time, kol3);
                                    cout << "Спортсмен добавлен в базу данных." << endl;
                                    cout << endl;
                                    cout << "Текущая база данных гонщиков: " << endl;
                                    swim_lst.Show();
                                    cout << endl;

                                }

                                if (menu_number == 4) {
                                    menu_number = 0;
                                }

                            }
                    //===========================================

                            else

                                //УДАЛИТЬ ЭЛЕМЕНТ ИЗ БАЗЫ ДАННЫХ
                                if (menu_number == 3) {
                                    int num;

                                    cout << "1. Удалить гонщика." << endl;
                                    cout << "2. Удалить баскетболиста." << endl;
                                    cout << "3. Удалить пловца." << endl;
                                    cout << "4. Вернуться назад." << endl;
                                    cout << endl;


                                    cout << "Введите нужный пункт: ";
                                    cin >> menu_number;
                                    cout << endl;


                                    /*===========================================
                                            УДАЛИТЬ ГОНЩИКА ИЗ БАЗЫ ДАННЫХ
                                    ============================================*/
                                    if (menu_number == 1) {

                                        race_lst.Show();

                                       

                                        if (kol1 == 0) {
                                            cout << "Нет элементов для удаления" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "Введите номер гонщика, которого нужно удалить: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol1) {
                                                cout << "Неверный номер удаляемого элемента." << endl << endl;
                                            }

                                            else {
                                                race_lst.Del(num, kol1);
                                                cout << "Удаление завершено." << endl;
                                                cout << endl;
                                                cout << "Текущая база данных гонщиков: " << endl;
                                                race_lst.Show();
                                                cout << endl;
                                            }
                                        }

                               

                                    }
                                    //===========================================




                                    /*===========================================
                                          УДАЛИТЬ БАСКЕТБОЛИСТА ИЗ БАЗЫ ДАННЫХ
                                    ===========================================*/
                                    if (menu_number == 2) {

                                        basket_lst.Show();

                                        

                                        if (kol2 == 0) {
                                            cout << "Нет элементов для удаления" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "Введите номер баскетболиста, которого нужно удалить: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol2) {
                                                cout << "Неверный номер удаляемого элемента." << endl << endl;
                                            }

                                            else {
                                                basket_lst.Del(num, kol2);
                                                cout << "Удаление завершено." << endl;
                                                cout << endl;
                                                cout << "Текущая база данных баскетболиста: " << endl;
                                                basket_lst.Show();
                                                cout << endl;
                                            }
                                        }

                                       
                                    }
                                    //===========================================




                                    /*===========================================
                                            УДАЛИТЬ ПЛОВЦА ИЗ БАЗЫ ДАННЫХ
                                    ============================================*/
                                    if (menu_number == 3) {
                                        swim_lst.Show();


                                        if (kol3 == 0) {
                                            cout << "Нет элементов для удаления" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "Введите номер пловца, которого нужно удалить: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol3) {
                                                cout << "Неверный номер удаляемого элемента." << endl << endl;
                                            }

                                            else {
                                                swim_lst.Del(num, kol3);
                                                cout << "Удаление завершено." << endl;
                                                cout << endl;
                                                cout << "Текущая база данных пловцов: " << endl;
                                                swim_lst.Show();
                                                cout << endl;
                                            }
                                        }

                                    }
                                    //===========================================


                                    //===========================================
                                    //      ВЕРНУТЬСЯ НАЗАД
                                    if (menu_number == 4) {

                                    }
                                    //===========================================


                                }
                    //===========================================

                                else

                                    /*==========================================
                                            СОРТИРОВКА БАЗЫ ДАННЫХ
                                    ==========================================*/
                                    if (menu_number == 4) {
                                        cout << "1. Сортировка гонщиков." << endl;
                                        cout << "2. Сортировка баскетболистов." << endl;
                                        cout << "3. Сортировка пловцов." << endl;
                                        cout << "4. Вернуться назад." << endl;
                                        cout << endl;


                                        cout << "Введите нужный пункт: ";
                                        cin >> menu_number;
                                        cout << endl;

                                        if (menu_number < 1 || menu_number > 4) {
                                            cout << "Вы ввели неверный пункт меню." << endl;
                                            cout << endl;
                                        }

                                        //===========================================
                                        //      СОРТИРОВКА ГОНЩИКОВ
                                        if (menu_number == 1) {
                                            menu_number = 0;

                                            while (menu_number != 3) {
                                                cout << "1. Сортировка по росту." << endl;
                                                cout << "2. Сортировка по фамилиям." << endl;
                                                cout << "3. Вернуться назад." << endl;
                                                cout << endl;

                                                cout << "Введите нужный пункт: ";
                                                cin >> menu_number;
                                                cout << endl;

                                                if (menu_number < 1 || menu_number > 3) {
                                                    cout << "Вы ввели неверный пункт меню." << endl;
                                                    cout << endl;
                                                }

                                                else

                                                    if (menu_number == 1) {
                                                        race_lst.sort_height();
                                                    }

                                                    else

                                                        if (menu_number == 2) {
                                                            race_lst.sort_family();
                                                        }

                                                        else

                                                            if (menu_number == 3) {

                                                            }

                                            }

                                        }
                                        //===========================================

                                        else

                                            //===========================================
                                            //      СОРТИРОВКА БАСКЕТБОЛИСТОВ
                                            if (menu_number == 2) {
                                                menu_number = 0;

                                                while (menu_number != 3) {
                                                    cout << "1. Сортировка по росту." << endl;
                                                    cout << "2. Сортировка по фамилиям." << endl;
                                                    cout << "3. Вернуться назад." << endl;
                                                    cout << endl;

                                                    cout << "Введите нужный пункт: ";
                                                    cin >> menu_number;
                                                    cout << endl;

                                                    if (menu_number < 1 || menu_number > 3) {
                                                        cout << "Вы ввели неверный пункт меню." << endl;
                                                        cout << endl;
                                                    }

                                                    else

                                                        if (menu_number == 1) {
                                                            basket_lst.sort_height();
                                                        }

                                                        else

                                                            if (menu_number == 2) {
                                                                basket_lst.sort_family();
                                                            }

                                                            else

                                                                if (menu_number == 3) {

                                                                }

                                                }
                                            }
                                        //===========================================

                                            else

                                                //===========================================
                                                //      СОРТИРОВКА ПЛОВЦОВ
                                                if (menu_number == 3) {
                                                    menu_number = 0;

                                                    while (menu_number != 3) {


                                                        cout << "1. Сортировка по росту." << endl;
                                                        cout << "2. Сортировка по фамилиям." << endl;
                                                        cout << "3. Вернуться назад." << endl;
                                                        cout << endl;

                                                        cout << "Введите нужный пункт: ";
                                                        cin >> menu_number;
                                                        cout << endl;

                                                        if (menu_number < 1 || menu_number > 3) {
                                                            cout << "Вы ввели неверный пункт меню." << endl;
                                                            cout << endl;
                                                        }

                                                        else

                                                            if (menu_number == 1) {
                                                                swim_lst.sort_height();
                                                            }

                                                            else

                                                                if (menu_number == 2) {
                                                                    swim_lst.sort_family();
                                                                }

                                                                else

                                                                    if (menu_number == 3) {

                                                                    }

                                                    }
                                                }
                                        //===========================================


                                        //===========================================
                                        //      ВЫХОД
                                        if (menu_number == 4) {

                                        }
                                        //===========================================
                                    }

                                    else

                                        //СОХРАНЕНИЕ БАЗЫ ДАННЫХ 
                                        if (menu_number == 5) {

                                            string name_save;
                                            cout << "Введите назване базы данных для сохранения: ";
                                            cin >> name_save;

                                            ofstream file;
                                            file.open(name_save);

                                            race_lst.write_f(file);
                                            basket_lst.write_f(file);
                                            swim_lst.write_f(file);

                                            file.close();

                                            cout << "База данных сохранена." << endl << endl;
                                        }

                                        else

                                            //Выход из базы данных 
                                            if (menu_number == 6) {

                                            }
                }

            }

            int n = 0;
            int height;
          
        }
        /*======================================================*/

        else

        /*ВЫХОД ИЗ ПРОГРАММЫ
        ========================================================*/
        if (menu_number == 2) {
            cout << "Завершение работы программы." << endl;
        }
        /*======================================================*/

    }

    system("PAUSE");
    return 0;
}