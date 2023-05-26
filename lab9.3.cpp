#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

struct Product {
    string name;
    string store;
    float price;
    string quantity;
};

void Print(Product* products, const int N)
{
    cout << "====================================================================="
        << endl;
    cout << "|  №  |  Назва товару  |     Магазин     |  Ціна  | Од. вимірювання |"
        << endl;
    cout << "---------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";

        cout << "| " << setw(15) << left << products[i].name
            << "| " << setw(16) << left << products[i].store
            << "| " << setw(7) << left << products[i].price
            << "| " << setw(15) << left << products[i].quantity
            << " |" << endl;

    }
    cout << "====================================================================="
        << endl;
    cout << endl;
};

int FindFreeIndex(Product products[], const int maxNumber) {
    for (int i = 0; i < maxNumber; i++) {
        if (products[i].name == "") {
            return i;
        }
    }
    return -1;
}

int FindProductIndex(Product* products, int N, const string& name)
{
    for (size_t i = 0; i < N; i++) {
        if (products[i].name == name) {
            return i;
        }
    }
    return -1;
}

void AddProduct(Product products[], const int maxNumber) {
    int index = FindFreeIndex(products, maxNumber);

    if (index == -1) {
        cout << "Список товарів заповнений!" << endl;
        return;
    }

    Product newProduct;

    cout << "Введіть назву товару: ";
    cin >> newProduct.name;
    cout << "Введіть назву магазину: ";
    cin >> newProduct.store;
    cout << "Введіть вартість одиниці товару в гривнях: ";
    cin >> newProduct.price;
    cin.ignore();
    cout << "Введіть кількість та одиницю вимірювання (наприклад, 100 шт.): ";
    getline(cin, newProduct.quantity);

    products[index] = newProduct;

    cout << endl << "Товар додано до списку!" << endl;
}

void DeleteProduct(Product products[], int size)
{
    int productNumber;
    cout << "Введіть номер продукту, який потрібно видалити: ";
    cin >> productNumber;
    if (productNumber <= 0 || productNumber > size) {
        cout << "Невірний номер продукту. Введіть число від 1 до " << size << endl;
        return;
    }
    for (int i = productNumber - 1; i < size - 1; i++) {
        products[i] = products[i + 1];
    }
    cout << "Продукт успішно видалено!" << endl;
}

void EditProduct(Product* products, int maxNumber)
{
    int productIndex;
    cout << "Введіть номер продукту, який ви хочете редагувати: ";
    cin >> productIndex;

    if (productIndex >= 0 && productIndex < maxNumber)
    {
        Product& productToEdit = products[productIndex];
        cout << "Поточна інформація про продукт: " << endl;
        cout << "Назва: " << productToEdit.name << endl;
        cout << "Магазин: " << productToEdit.store << endl;
        cout << "Ціна: " << productToEdit.price << endl;
        cout << "Кількість: " << productToEdit.quantity << endl;

        cout << endl << "Введіть нові дані:" << endl;
        cout << "Назва: ";
        getline(cin >> ws, productToEdit.name);
        cout << "Магазин: ";
        getline(cin >> ws, productToEdit.store);
        cout << "Ціна: ";
        cin >> productToEdit.price;
        cout << "Кількість: ";
        getline(cin >> ws, productToEdit.quantity);
    }
    else
    {
        cout << "Продукт з номером " << productIndex << " не знайдено" << endl;
    }
}

void SortByStore(Product* products, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (products[i].name != "") {
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (products[i].store > products[j].store) {
                swap(products[i], products[j]);
            }
        }
    }
    cout << "Масив впорядковано!" << endl;
}

void SortByTotalPrice(Product* products, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (products[i].name != "") {
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (products[i].price > products[j].price) {
                swap(products[i], products[j]);
            }
        }
    }
    cout << "Масив впорядковано!" << endl;
}

void PrintByStore(Product* products, int maxNumber)
{
    string storeName;
    cout << "Введіть назву магазину: ";
    cin >> storeName;
    cout << endl;

    cout << "Товари в магазині \"" << storeName << "\":" << endl << endl;

    bool found = false;
    for (int i = 0; i < maxNumber; i++) {
        if (products[i].store == storeName) {
            cout << "Назва товару: " << products[i].name << endl;
            cout << "Магазин: " << products[i].store << endl;
            cout << "Ціна: " << products[i].price << endl;
            cout << "Кількість: " << products[i].quantity << endl;
            cout << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Товарів в магазині \"" << storeName << "\" не знайдено." << endl;
    }
}

void PrintByPriceRange(Product* products, int size, double minPrice, double maxPrice)
{
    cout << "Продукти в діапазоні вартості від " << minPrice << " до " << maxPrice << ":" << endl << endl;
    cout << setw(15) << left << "Назва"
        << setw(20) << left << "Магазин"
        << setw(10) << left << "Ціна"
        << setw(15) << left << "Кількість" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < size; i++)
    {
        if (products[i].price >= minPrice && products[i].price <= maxPrice)
        {
            cout << setw(15) << left << products[i].name
                << setw(20) << left << products[i].store
                << setw(10) << left << products[i].price
                << setw(15) << left << products[i].quantity << endl;
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int maxNumber = 50;

    Product products[maxNumber] = {
            {"Банан", "АТБ", 2.50, "1 штука"},
        {"Молоко", "Сільпо", 1.99, "1 літр"},
        {"Хліб", "АТБ", 2.50, "1 буханка"},
        {"Яйця", "Рукавичка", 3.99, "1 дюжина"}
    };

    int menuItem;

    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - вивід даних на екран" << endl;
        cout << " [2] - + додати продукт" << endl;
        cout << " [3] - - прибрати продукт" << endl;
        cout << " [4] - * змінити продукт" << endl;
        cout << " [5] - сортування" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            int printMenuItem;
            cout << "Виберіть дію:" << endl << endl;
            cout << " [1] - вивести список всіх товарів" << endl;
            cout << " [2] - вивести список товарів в конкретному магазині" << endl;
            cout << " [3] - вивести список в діапазоні цін" << endl << endl;
            cout << endl << "Введіть значення: "; cin >> printMenuItem;
            cout << endl << endl;

            switch (printMenuItem)
            {
            case 1:
                Print(products, maxNumber);
                break;
            case 2:
                PrintByStore(products, maxNumber);
                break;
            case 3:
                double minPrice;
                double maxPrice;

                cout << "Мінімальна ціна: " << endl;
                cin >> minPrice;
                cout << "Максимальна ціна: " << endl;
                cin >> maxPrice;

                PrintByPriceRange(products, maxNumber, minPrice, maxPrice);
                break;
            default:
                cout << "Ви ввели помилкове значення! "
                    "Слід ввести число - номер вибраного пункту меню" << endl;
            }
            break;
        case 2:
            AddProduct(products, maxNumber);
            break;
        case 3:
            DeleteProduct(products, maxNumber);
            break;
        case 4:
            EditProduct(products, maxNumber);
            break;
        case 5:
            int sortMenuItem;
            cout << "Сортувати за:" << endl;
            cout << " [1] - назвою магазину" << endl;
            cout << " [2] - загальною вартістю" << endl;
            cout << "Введіть значення: "; cin >> sortMenuItem;
            cout << endl << endl << endl;
            switch (sortMenuItem)
            {
            case 1:
                SortByStore(products, maxNumber);
                break;
            case 2:
                SortByTotalPrice(products, maxNumber);
                break;
            default:
                cout << "Ви ввели помилкове значення! "
                    "Слід ввести число - номер вибраного пункту меню" << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

}