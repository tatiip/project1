
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;


//������� ���������
struct Node                             
{
    /*����� ���������� ��� ���� �������
    ==================================*/
    int height;     //���� ����������
    string family;   //������� �����������


    //���������� ��� ��������
    string car;      //������ ������, ��� �������
    

    //���������� ��� �������
    double time;    //�����, �� ������� ������ �������� ��������� � 100�.
    


    //���������� ��� ��������������
    int points;     //���������� ����� �� ���������������� �������
    

    Node* Next, * Prev;     //��������� �� ������ ���������� � ����������� ��������� ������
};


//������ �����

//����� - ��������
class sportsman           
{
    public:
        
        Node* Head, * Tail;     //��������� �� ������ ������ ������ � ��� �����


        sportsman() : Head(NULL), Tail(NULL) {};    //�����������


        //����������
        ~sportsman() {
            while (Head)                       //���� �� ������ �� ������ ������ ���-�� ����
            {
                Tail = Head->Next;             //��������� ����� ������ ���������� ����� ������
                delete Head;                   //������� ������ �� ������� �����
                Head = Tail;                   //����� ������ ������ �� ����� ���������� ��������
            }
        };

        
        /*������� �������� ����������� �������� ����������� ������
        ��� ����� �����, ������� ����� ������������ ��� ������-����������*/
        void Del(int num, int &kol) { //�������� - ���������� num, ������� ��������� ����� �������� ��� ��������
            
            //�������� ������� ��������
            
            //� ������ ���� ������ ��������
            if ((num == 1) and (Head->Next)) { 
                Node* temp = Head;	//��������� �� 1-�� ������� (������)
                Head = Head->Next;	//�������� ��������� �� ��������� �������
                Head->Prev = NULL;	//������ ���������� ������� ������
                delete temp; //������� ������
                kol--; //��������� �������
                return;	
            }

            else 
               //� ������ 1 �������
               if ((num == 1) and (Head == Tail)) {

                //�������� ���, ��� ����������
                Head->Next = NULL;	 
                Head = NULL;

                delete Head;     //�������  ��������� �� 1 ������� (������)
                kol = 0;		 //����������, ��� � ������ ���� ���������
                return;	
            }
            

            //��������� ������� �������� ��������� ��������� ������
            if (num == kol) {
                Node* temp = Tail;  //���������, ��� ��� ����� �����
                Tail = Tail->Prev;	//���������� ����� �����
                Tail->Next = NULL;	//����������, ��� ������� �� ������� �����
                delete temp;	    //������� ������ �� ������� ������
                kol--;		    //��������� ������� ���������
                return;		      
            }


            //��������� ������� �� ������ � �� ���������
            Node* temp = Head, * temp2;  //temp-��������� �������, temp2 - ���������� ��� ���������� ����������� ������ ���������� ��������

            for (int i = 0; i < num - 1; i++) temp = temp->Next;  //���� � ������ ���������� ��������

            temp2 = temp;	//�������� ���������� ����� ���������� ��������
           
            //���������� ������
            temp2->Prev->Next = temp->Next;	           
            temp2->Next->Prev = temp->Prev; 

            delete temp; //������ ����������� ������, ������ ����� �� ������ ���������� ��������
            kol--;    
        }

};





//������    
//�����-��������� 
class racer : public sportsman {
    
public:

    racer() : sportsman() {};    //�����������

    void Add(string k, int x, string model, int &kol) {
        {
            Node* temp = new Node;         //��������� ������ ��� ����� ������� ���������
           
            temp->Next = NULL;   //���������, ��� ���������� �� ���������� ������ �����
            
            //���������� �������� � ���������
            temp->height = x;                         
            temp->family = k;
            temp->car = model;
            
            kol++;

            if (Head != NULL)                    //���� ������ �� ����
            {
                temp->Prev = Tail;               //��������� ����� �� ���������� ������� � �����. ����
                Tail->Next = temp;               //��������� ����� ���������� �� ������� ��������
                Tail = temp;                     //������ ����� ������
            }

            else //���� ������ ������
            {
                temp->Prev = NULL;               //���������� ������� ��������� � �������
                Head = Tail = temp;              //������=�����=��� �������, ��� ������ ��������
            }
        }
    };

    void Show() {
        Node* temp;

        //������� ������ � ������
        temp = Head;                       //�������� ��������� �� ����� ������� ��������
        int number = 1;

        cout << "������ ��������:" << endl << endl;

        while (temp != NULL)              //���� �� �������� ������ ��������
        {
            cout << "������ �" << number << endl;
            cout << "�������: " << temp->family << endl; //������� ������ ��������� �������� �� �����
            cout << "����: " << temp->height << endl;       
            cout << "����� ����������: " << temp->car << endl;
            number++;
            cout << endl;
            temp = temp->Next;   //����� ������ �� ����� ���������� ��������

        }
        cout << endl;
    };

    //���������� �� �����
    void sort_height() {
        Node* left = Head;                 //������ ������� � ������
        Node* right = Head->Next;          //������ ������� � ��������� �� ������� �������

        Node* temp = new Node;  //��������� ����� ��� �������� ���� �������� ��������������� �����

        while (left->Next) {       //������� �� ���� �������, �� ����������� �������� �������
            while (right) {        //������� �� ���� �������, ������� ������� ������ 
                              //(�� ���� ������������ ������� ������ �� ������� ������)
                if ((left->height) < (right->height)) {        //��������� ������������� ������������
                    
                    //� ������������ ��� ���������� ��������, �� ����������� ���������� �����, �������

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
                right = right->Next;   //���������� ��������� �� ��������� ������� 
            }
            left = left->Next;       //���������� ��������� �� ��������� ������� 
            right = left->Next;    //��������� ������ ��������� ������ ������� �����, ����������� ���������� ��� �����
        }
    }

    //���������� �� �������
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

        temp = Head;                       //�������� ��������� �� ����� ������� ��������
        int number = 1;

        f << "������ ��������:" << endl << endl;

        while (temp != NULL)              //���� �� �������� ������ ��������
        {
            //���������� ������ ��������� �������� � ����
            f << "������ �" << number << endl;
            f << "�������: " << temp->family << endl; 
            f << "����: " << temp->height << endl;        
            f << "������ ����������: " << temp->car << endl;
            number++;
            f << endl;
            temp = temp->Next;             //����� ������ �� ����� ���������� ��������

        }
        f << endl << endl;


    }

};



//������������
//�����-��������� 
class basketball : public sportsman {

public:

    basketball() : sportsman() {};    //�����������

    void Add(string k, int x, int point, int &kol) {
        {
            Node* temp = new Node;               

            temp->Next = NULL;             

            //���������� �������� � ���������
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

        //������� ������ � ������
        temp = Head;                       
        int number = 1;

        cout << "������ ��������������:" << endl << endl;

        while (temp != NULL)              
        {
            cout << "������������ �" << number << endl;
            cout << "�������: " << temp->family << endl;        
            cout << "����: " << temp->height << endl;        
            cout << "���� �� �������: " << temp->points << endl;
            number++;
            cout << endl;
            temp = temp->Next;             

        }
        cout << endl;
    };

    //���������� �� �����
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

    //���������� �� �������
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

        f << "������ ��������������:" << endl << endl;

        while (temp != NULL)              
        {
            f << "������������ �" << number << endl;
            f << "�������: " << temp->family << endl;     
            f << "����: " << temp->height << endl;        
            f << "���� �� �������: " << temp->points << endl;
            number++;
            f << endl;
            temp = temp->Next;             

        }
            f << endl << endl;
        
            
    }
};



//������
//�����-��������� 
class swimmer : public sportsman {

public:

    swimmer() : sportsman() {};    //�����������

    void Add(string k, int x, double time, int &kol) {
        {
            Node* temp = new Node;             



            temp->Next = NULL;                 


            //���������� �������� � ���������
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

        //������� ������ � ������
        temp = Head;                      
        int number = 1;
        
        cout << "������ �������:" << endl << endl;

        while (temp != NULL)          
        {   

            cout << "������ �" << number << endl;
            cout << "�������: " << temp->family << endl;      
            cout << "����: " << temp->height << endl;       
            cout << "����� �� 100�: " << temp->time << endl;
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

    //���������� �� �������
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

        f << "������ �������:" << endl << endl;

        while (temp != NULL)            
        {
            f << "������ �" << number << endl;
            f << "�������: " << temp->family << endl;       
            f << "����: " << temp->height << endl;        
            f << "����� �� 100�: " << temp->time << endl;
            number++;
            f << endl;
            temp = temp->Next;            

        }
        f << endl << endl;


    }
};





/*==========================================================================
                        �������� ����� ���������
==========================================================================*/

int main()
{

    //����� ��������� ��� ������������� ���������
    SetConsoleCP(1251); //��� ������������� ��� �����
    SetConsoleOutputCP(1251); //��� ������������� ��� ������

    



    int menu_number = 0; //����� ������ ����

    string family, model, style, position;


    int speed , height, points;
    double time;

   

    racer race_lst; //������ ��������


    swimmer swim_lst; //������ �������


    basketball basket_lst; //������ ��������������


    //���� ���������
    while (menu_number != 2) {


        cout << "���� ���������:" << endl;
        cout << "1. ��������� ���� ������." << endl;
        cout << "2. ��������� ������ ���������." << endl;
        cout << endl;


        cout << "������� ������ �����: ";
        cin >> menu_number;
        cout << endl;


        /*���� ������ �������� �����
        ========================================================*/
        if (menu_number < 1 || menu_number > 2) {
            cout << "�� ����� �������� ����� ����." << endl;
            cout << endl;
        }

        else
            
        /*������ � ����� ������
        ========================================================*/
        if (menu_number == 1) {


            char* name_bd = new char[30];   //��� ���� ������


            cout << "������� ��� ���� ������: ";
            cin >> name_bd;


            //*�������� �������� ����� txt
            ifstream file(name_bd);
            cout << endl;


            if (!file)
            {
                cout << "�� ������� ��������� ���� ������." << endl;
                cout << "��������� ��������� ������ � ��������� �������" << endl;
                cout << endl;
                menu_number = 6;
            }


            else
            {   

                //���������� ������

                int kol;

                int kol1 = 0; //���-�� ��������

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    
                    file >> family;
                    file >> height;
                    file >> model;

                    race_lst.Add(family, height, model, kol1);

                }

                int kol2 = 0; //���������� ��������������

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    file >> family;
                    file >> height;
                    file >> points;

                    basket_lst.Add(family, height, points, kol2);
                }


                int kol3 = 0; //���������� �������

                file >> kol;

                for (int i = 0; i < kol; i++) {
                    file >> family;
                    file >> height;
                    file >> time;

                    swim_lst.Add(family, height, points, kol3);
                }

                file.close();

                cout << "���� ������ ������� ���������." << endl;
                cout << endl;
                menu_number = 0;

                while (menu_number != 6) {

                    menu_number = 0;

                    cout << "1. ����������� ���� ������." << endl;
                    cout << "2. �������� ������� � ���� ������." << endl;
                    cout << "3. ������� ������� �� ���� ������." << endl;
                    cout << "4. ���������� ���������." << endl;
                    cout << "5. ��������� ������� ���� ������." << endl;
                    cout << "6. �����" << endl;


                    cout << endl;


                    cout << "������� ������ �����: ";
                    cin >> menu_number;
                    cout << endl;


                    if (menu_number < 1 || menu_number > 6) {
                        cout << "�� ����� �������� ����� ����." << endl;
                        cout << endl;
                    }

                    else

                        /*===========================================
                                      �������� ���� ������
                        ===========================================*/
                        if (menu_number == 1) {
                            menu_number = 0;

                            while (menu_number != 5) {
                                cout << "1. ����������� ���� �����������." << endl;
                                cout << "2. ����������� ��������." << endl;
                                cout << "3. ����������� ��������������." << endl;
                                cout << "4. ����������� �������." << endl;
                                cout << "5. ��������� �����." << endl;
                                cout << endl;

                                cout << "������� ������ �����: ";
                                cin >> menu_number;
                                cout << endl;

                                if (menu_number < 1 || menu_number > 5) {
                                    cout << "�� ����� �������� ����� ����." << endl;
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

                                    //�����
                                }
                            }


                        }
                    //===========================================

                        else

                            //===========================================
                            //�������� ������� � ���� ������
                            if (menu_number == 2) {

                                cout << "1. �������� �������." << endl;
                                cout << "2. �������� �������������." << endl;
                                cout << "3. �������� ������." << endl;
                                cout << "4. ��������� �����." << endl;
                                cout << endl;


                                cout << "������� ������ �����: ";
                                cin >> menu_number;
                                cout << endl;

                                if (menu_number == 1) {

                                    menu_number = 0;

                                    cout << "������� ����������: ";

                                    cin >> family;
                                    cout << "���� ����������: ";
                                    cin >> height;

                                    cout << "������ ����������: ";

                                    cin >> model;


                                    race_lst.Add(family, height, model, kol1);
                                    cout << "��������� �������� � ���� ������." << endl;
                                    cout << endl;
                                    cout << "������� ���� ������ ��������: " << endl;
                                    race_lst.Show();
                                    cout << endl;
                                }

                                if (menu_number == 2) {

                                    menu_number = 0;

                                    cout << "������� ����������: ";

                                    cin >> family;
                                    cout << "���� ����������: ";
                                    cin >> height;


                                    cout << "����� �� �������: ";
                                    cin >> points;
                                    cout << endl;

                                    basket_lst.Add(family, height, points, kol2);
                                    cout << "��������� �������� � ���� ������." << endl;
                                    cout << endl;
                                    cout << "������� ���� ������ ��������������: " << endl;
                                    basket_lst.Show();
                                    cout << endl;

                                }

                                if (menu_number == 3) {

                                    menu_number = 0;

                                    cout << "������� ����������: ";

                                    cin >> family;
                                    cout << "���� ����������: ";
                                    cin >> height;

                                    cout << "����� ����������� 100 �.: ";
                                    cin >> time;
                                    cout << endl;

                                    swim_lst.Add(family, height, time, kol3);
                                    cout << "��������� �������� � ���� ������." << endl;
                                    cout << endl;
                                    cout << "������� ���� ������ ��������: " << endl;
                                    swim_lst.Show();
                                    cout << endl;

                                }

                                if (menu_number == 4) {
                                    menu_number = 0;
                                }

                            }
                    //===========================================

                            else

                                //������� ������� �� ���� ������
                                if (menu_number == 3) {
                                    int num;

                                    cout << "1. ������� �������." << endl;
                                    cout << "2. ������� �������������." << endl;
                                    cout << "3. ������� ������." << endl;
                                    cout << "4. ��������� �����." << endl;
                                    cout << endl;


                                    cout << "������� ������ �����: ";
                                    cin >> menu_number;
                                    cout << endl;


                                    /*===========================================
                                            ������� ������� �� ���� ������
                                    ============================================*/
                                    if (menu_number == 1) {

                                        race_lst.Show();

                                       

                                        if (kol1 == 0) {
                                            cout << "��� ��������� ��� ��������" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "������� ����� �������, �������� ����� �������: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol1) {
                                                cout << "�������� ����� ���������� ��������." << endl << endl;
                                            }

                                            else {
                                                race_lst.Del(num, kol1);
                                                cout << "�������� ���������." << endl;
                                                cout << endl;
                                                cout << "������� ���� ������ ��������: " << endl;
                                                race_lst.Show();
                                                cout << endl;
                                            }
                                        }

                               

                                    }
                                    //===========================================




                                    /*===========================================
                                          ������� ������������� �� ���� ������
                                    ===========================================*/
                                    if (menu_number == 2) {

                                        basket_lst.Show();

                                        

                                        if (kol2 == 0) {
                                            cout << "��� ��������� ��� ��������" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "������� ����� �������������, �������� ����� �������: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol2) {
                                                cout << "�������� ����� ���������� ��������." << endl << endl;
                                            }

                                            else {
                                                basket_lst.Del(num, kol2);
                                                cout << "�������� ���������." << endl;
                                                cout << endl;
                                                cout << "������� ���� ������ �������������: " << endl;
                                                basket_lst.Show();
                                                cout << endl;
                                            }
                                        }

                                       
                                    }
                                    //===========================================




                                    /*===========================================
                                            ������� ������ �� ���� ������
                                    ============================================*/
                                    if (menu_number == 3) {
                                        swim_lst.Show();


                                        if (kol3 == 0) {
                                            cout << "��� ��������� ��� ��������" << endl << endl;
                                        }

                                        else
                                        {
                                            cout << "������� ����� ������, �������� ����� �������: ";
                                            cin >> num;
                                            cout << endl;

                                            if (num < 1 || num > kol3) {
                                                cout << "�������� ����� ���������� ��������." << endl << endl;
                                            }

                                            else {
                                                swim_lst.Del(num, kol3);
                                                cout << "�������� ���������." << endl;
                                                cout << endl;
                                                cout << "������� ���� ������ �������: " << endl;
                                                swim_lst.Show();
                                                cout << endl;
                                            }
                                        }

                                    }
                                    //===========================================


                                    //===========================================
                                    //      ��������� �����
                                    if (menu_number == 4) {

                                    }
                                    //===========================================


                                }
                    //===========================================

                                else

                                    /*==========================================
                                            ���������� ���� ������
                                    ==========================================*/
                                    if (menu_number == 4) {
                                        cout << "1. ���������� ��������." << endl;
                                        cout << "2. ���������� ��������������." << endl;
                                        cout << "3. ���������� �������." << endl;
                                        cout << "4. ��������� �����." << endl;
                                        cout << endl;


                                        cout << "������� ������ �����: ";
                                        cin >> menu_number;
                                        cout << endl;

                                        if (menu_number < 1 || menu_number > 4) {
                                            cout << "�� ����� �������� ����� ����." << endl;
                                            cout << endl;
                                        }

                                        //===========================================
                                        //      ���������� ��������
                                        if (menu_number == 1) {
                                            menu_number = 0;

                                            while (menu_number != 3) {
                                                cout << "1. ���������� �� �����." << endl;
                                                cout << "2. ���������� �� ��������." << endl;
                                                cout << "3. ��������� �����." << endl;
                                                cout << endl;

                                                cout << "������� ������ �����: ";
                                                cin >> menu_number;
                                                cout << endl;

                                                if (menu_number < 1 || menu_number > 3) {
                                                    cout << "�� ����� �������� ����� ����." << endl;
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
                                            //      ���������� ��������������
                                            if (menu_number == 2) {
                                                menu_number = 0;

                                                while (menu_number != 3) {
                                                    cout << "1. ���������� �� �����." << endl;
                                                    cout << "2. ���������� �� ��������." << endl;
                                                    cout << "3. ��������� �����." << endl;
                                                    cout << endl;

                                                    cout << "������� ������ �����: ";
                                                    cin >> menu_number;
                                                    cout << endl;

                                                    if (menu_number < 1 || menu_number > 3) {
                                                        cout << "�� ����� �������� ����� ����." << endl;
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
                                                //      ���������� �������
                                                if (menu_number == 3) {
                                                    menu_number = 0;

                                                    while (menu_number != 3) {


                                                        cout << "1. ���������� �� �����." << endl;
                                                        cout << "2. ���������� �� ��������." << endl;
                                                        cout << "3. ��������� �����." << endl;
                                                        cout << endl;

                                                        cout << "������� ������ �����: ";
                                                        cin >> menu_number;
                                                        cout << endl;

                                                        if (menu_number < 1 || menu_number > 3) {
                                                            cout << "�� ����� �������� ����� ����." << endl;
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
                                        //      �����
                                        if (menu_number == 4) {

                                        }
                                        //===========================================
                                    }

                                    else

                                        //���������� ���� ������ 
                                        if (menu_number == 5) {

                                            string name_save;
                                            cout << "������� ������� ���� ������ ��� ����������: ";
                                            cin >> name_save;

                                            ofstream file;
                                            file.open(name_save);

                                            race_lst.write_f(file);
                                            basket_lst.write_f(file);
                                            swim_lst.write_f(file);

                                            file.close();

                                            cout << "���� ������ ���������." << endl << endl;
                                        }

                                        else

                                            //����� �� ���� ������ 
                                            if (menu_number == 6) {

                                            }
                }

            }

            int n = 0;
            int height;
          
        }
        /*======================================================*/

        else

        /*����� �� ���������
        ========================================================*/
        if (menu_number == 2) {
            cout << "���������� ������ ���������." << endl;
        }
        /*======================================================*/

    }

    system("PAUSE");
    return 0;
}