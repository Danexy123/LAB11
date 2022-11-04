#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//инициализируем узел и всё, что в нем хранится
struct Node
{
    int data;
    Node* pointer_to_next_node;

    Node(int _data)
    {
        data = _data;
        pointer_to_next_node = nullptr;
    }
};

//создаем список и его функции
struct list 
{
    Node* head_node;
    Node* tail_node;

    //инициализируем список
    list() : head_node(nullptr), tail_node(nullptr) {}

    //проверка на пустоту списка
    bool is_empty()
    {
        return head_node == nullptr;
    }

    //функция добавления элемента
    void push_back(int _data)
    {
        Node* new_node = new Node(_data);

        if (is_empty())
        {
            head_node = new_node;
            tail_node = new_node;

            return;
        }

        tail_node->pointer_to_next_node = new_node;
        tail_node = new_node;

    }

    //функция вывода всего списка на экран
    void print() 
    {
        if (is_empty()) return;

        Node* current_node = head_node;

        while (current_node) 
        {
            cout << current_node->data << " ";
            current_node = current_node->pointer_to_next_node;
        }

        cout << endl;
    }

    //функция удаления элемента по индексу
    Node* operator[] (const int index)
    {
        if (is_empty()) return nullptr;
        Node* p = head_node;
        Node* x = head_node;

        for (int i = 0; i < index; i++)
        {
            p = p->pointer_to_next_node;
            if (!p) return nullptr;
        }
        for (int i = 0; i < (index - 1); i++) 
        {
            x = x->pointer_to_next_node;
            if (!x) return nullptr;
        }
        x->pointer_to_next_node = p->pointer_to_next_node;
        delete p;

        return 0;
    }

    //удаление одного узла списка
    void one_del()
    {
        int num_del;

        cout << "Какой элемент удалить?\n";
        cin >> num_del;
        num_del--;

        if (num_del == 0)
        {
            if (is_empty()) return;
            Node* current_node = head_node;
            head_node = current_node->pointer_to_next_node;
            delete current_node;
        }
        else
        {
            operator[](num_del);
        }
    }

    //удаление всего списка
    void full_del()
    {
        Node* current;
        current = head_node;

        for (int i = 1; head_node->pointer_to_next_node = nullptr; i++) { }
        
        if (is_empty()) return;
        Node* current_node = head_node;
        head_node = current_node->pointer_to_next_node;
        delete current_node;
    }

    //запись списка в файл
    void file_copy(int kolichestvo_el)
    {
        Node* current_node;
        current_node = head_node;
        ofstream file;
        file.open("F1.bin",  ofstream::app);
        if (!file.is_open())
        {
            cout << "Ошибка открытия файла!\n";
        }
        else
        {
            int x;
            for (int i = 1; i < kolichestvo_el; i++)
            {
                x = current_node->data;
                if (current_node->pointer_to_next_node == NULL)
                {
                    file.close();
                }
                else
                { 
                    file.write((char*)&x, sizeof(int));
                    current_node = current_node->pointer_to_next_node;
                }
            }
        }
        file.close();
    }

    //восстановление списка из файла
    void file_pastate(int kolichestvo_el, struct list s)
    {
        Node* current_node = head_node;
        ifstream file;
        file.open("F1.bin");
        if (!file.is_open())
        {
            cout << "Ошибка открытия файла!\n";
        }
        else
        {   
             int x;
                for (int i = 1; i < kolichestvo_el-1; i++)
                {
                    file.read((char*)&x, sizeof(int));
                    s.push_back(x);
                }
        }
            file.close();
        cout << "Востановленный список: \n\n";
        s.print();

    }

    //заполнение списка
    void zapolnenie(int kolichestvo_el,struct list s)
    {
        cout << "Выберте метод заполнения списка:\n" << "1) Автоматически    2) Вручную\n";
        int metod_vvoda, data_uzla;
        bool var = false;

        while (!var)
        {
            cin >> metod_vvoda;
            if (metod_vvoda == 1)
            {
                for (int i = 1; i <= kolichestvo_el; i++)
                    push_back(rand() % 100);
                var = true;
            }
            if (metod_vvoda == 2)
            {
                for (int i = 1; i <= kolichestvo_el; i++)
                {
                    cout << "\nВведите " << i << " элемент списка\n";
                    cin >> data_uzla;

                    push_back(data_uzla);
                    var = true;
                }
            }
            if (metod_vvoda !=1 && metod_vvoda != 2)
            {
                cout << "Такого варианта нет, выберете снова\n";
            }
        }
    }
};



int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    cout << "Сколько узлов в списке?\n";

    list s;
    int kolichestvo_el;
    cin >> kolichestvo_el;

    while (kolichestvo_el < 0)
    {
        cout << "Введите количество узлов >= 0\n";
        cin >> kolichestvo_el;
    }

    if (kolichestvo_el == 0)
    {
        cout << "Список пуст\n";
    }
    else
    {
        s.zapolnenie(kolichestvo_el, s);
        s.print();
        s.one_del();

        cout << "Список после внесенных изменний: \n";
        s.print();

        s.file_copy(kolichestvo_el);

        s.full_del();

        if (s.is_empty())
            cout << "\nСписок удалён\n\n";

        s.file_pastate(kolichestvo_el, s);
    }
    return 0;
}