#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

struct Node //Узел
{
    Node* pNext; //указатель на следующий элемент
    char data; //значение узла

    Node(char s, Node* ptr = nullptr) //конструктор узла
    {
        data = s;
        pNext = nullptr;
    }
};

struct List //Однонаправленный список
{
    Node* first; //указатель на первый элемент
    int size = 0; //размер списка
};

void add(List& list, char s) //Добавляет в список новый элемент
{
    Node* p = new Node(s);
    if (list.size == 0)
        list.first = p;
    else
    {
        Node* current = list.first;
        while (current->pNext != nullptr)
            current = current->pNext;
        current->pNext = p;
    }
    list.size++;
}

void print(List L) //Выводит список
{
    Node* current = L.first;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->pNext;
    }
}

List unique_L1(List L1) //Возвращает список, состоящий из уникальных элементов списка L1
{
    List L;
    vector <char> unique_sim;
    Node* current = L1.first;
    for (int i = 0; i < L1.size; i++)
    {
        bool flag = true;
        for (int j = 0; j < unique_sim.size(); j++)
            if (unique_sim[j] == current->data)
                flag = false;
        if (flag)
        {
            add(L, current->data);
            unique_sim.push_back(current->data);
        }
        current = current->pNext;
    }
    return L;
}

List unique_L(List L1, List L2) //Возвращает список L, состоящий из элементов списка L1, которых нет в списке L2
{
    List L = unique_L1(L1);
    Node* current_L = L.first;
    while (current_L != nullptr)
    {
        Node* current_L2 = L2.first;
        while (current_L2 != nullptr)
        {
            if (current_L == L.first && current_L->data == current_L2->data)
            {
                L.first = L.first->pNext;
                break;
            }
            else if (current_L->pNext != nullptr && current_L->pNext->data == current_L2->data)
            {
                current_L->pNext = current_L->pNext->pNext;
                break;
            }
            current_L2 = current_L2->pNext;
        }
        current_L = current_L->pNext;
    }
    return L;


}

List offset(List L1, int index, int count)
{
    int current_index = 0;
    Node* previous_begin = nullptr;
    Node* after_end = nullptr;
    Node* current = L1.first;
    while (true)
    {
        if (current_index + 1 == index)
            previous_begin = current;
        if (current_index == index + count - 1)
        {
            after_end = current;
            break;
        }
        current_index++;
        current = current->pNext;

    }
    if (index == 0)
        L1.first = after_end->pNext;
    else
        previous_begin->pNext = after_end->pNext;
    return L1;
}

List sort(List L2)
{
    bool flag = true;
    Node* current = L2.first;
    Node* previous = nullptr;
    while (flag)
    {
        flag = false;
        Node* current = L2.first;
        while (current->pNext != nullptr)
        {
            if (current->pNext != nullptr && current->data > current->pNext->data)
            {
                flag = true;
                if (current == L2.first)
                {
                    L2.first = current->pNext;
                    current->pNext = current->pNext->pNext;
                    L2.first->pNext = current;
                    previous = L2.first;
                }

                else
                {
                    previous->pNext = current->pNext;
                    current->pNext = current->pNext->pNext;
                    previous->pNext->pNext = current;
                    previous = previous->pNext;
                }

            }
            else
            {
                previous = current;
                current = current->pNext;
            }
        }
    }
    return L2;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Практическая работа №5 \"Однонаправленный динамический список.\". Тараканова Евгения." << endl << endl;
    //Описание программ
    int size, mode;
    List L1, L2;
    cout << "Введите размер однонаправленного списка L1: ";
    do
    {
        cin >> size;
        if (size < 1) cout << "Размер списка не может быть меньше 1. Введите корректный размер: ";
    } while (size < 1);
    cout << "Введите элементы списка L1: ";
    for (int i = 0; i < size; i++)
    {
        char s;
        cin >> s;
        add(L1, s);
    }

    cout << endl << "Введите размер однонаправленного списка L2: ";
    do
    {
        cin >> size;
        if (size < 1) cout << "Размер списка не может быть меньше 1. Введите корректный размер: ";

    } while (size < 1);
    cout << "Введите элементы списка L2: ";
    for (int i = 0; i < size; i++)
    {
        char s;
        cin >> s;
        add(L2, s);
    }

    cout << "\nВыберите функцию: \n1 - Создание списка L, в котором будут содержаться значения, входящие в список L1 и не входящие в список L2 \n2 - Удаление подсписка списка L1, заданного диапазоном позиций" <<
        "\n3 - Сортировка списка L2, располагая значения в порядке возрастания \n--->";

    do
    {
        cin >> mode;
        if (mode < 1 || mode > 3) cout << "Функции под таким номером нет. Введите корректный номер: ";
    } while (mode < 1 || mode > 3);

    switch (mode)
    {
    case 1:
    {
        List L = unique_L(L1, L2);
        if (L.first == nullptr)
            cout << "Все элементы списка L1 присутствуют в списке L2" << endl;
        else
        {
            cout << "Список L: ";
            print(L);
        }
        cout << endl;
        break;
    }
    case 2:
    {
        int index, size;
        cout << endl << "Введите позицию, с которой хотите начать удаление подсписка: ";
        cin >> index;
        cout << "Введите, сколько элементов нужно удалить: ";
        cin >> size;
        if ((index + size - 1) > L1.size)
            cout << endl << "Невозможно произвести удаление подсписка, поскольку минимальный размер списка L1 для этого должен быть = " << index + size << "\nРеальный же размер списка L1 - " << L1.size;
        else
        {
            List L = offset(L1, index - 1, size);
            if (L.first == nullptr)
                cout << endl << "Были удалены все элементы списка L1";
            else
            {
                cout << endl << "Новый список L1: ";
                print(L);
            }
        }
        cout << endl;
        break;
    }
    case 3:
    {
        List L = sort(L2);
        cout << "\nОтсортированный список L2: ";
        print(L);
        cout << endl;
        break;
    }
    }

}
