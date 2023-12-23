#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

void editString(string* str1);
void printReverse(string str);
void printInColumns(string str);
void mainMenu(string* str);

void printStringFromFile(string* str1)
{
    ifstream File("Laba_4_text.txt");

    if (!File.is_open()) {
        cout << "Не удалось открыть файл\n";
        exit(1);
    }
    while (!File.eof()) {
        getline(File, *str1);
    }
    cout << *str1;

    File.close();
    cout << "\n\n";
}

void getString(string* str1)
{
    int getStringMenu;
    cout << "Каким способом вы хотите получить строку?:\n"
        << "1 - Ввести строку вручную в консоль\n"
        << "2 - Вывести строку из файла\n";
    cin >> getStringMenu;
    switch (getStringMenu)
    {
    case 1:
        system("cls");
        cin.ignore();
        getline(cin, *str1);
        _getch();
        break;
    case 2:
        system("cls");
        printStringFromFile(str1);
        _getch();
        break;
    default:
        cout << "Ошибка! Попробуйте еще раз.\n\n";
        _getch();
        system("cls");
        getString(str1);
        break;
    }
}

void removeExtraSpaces(string* str1)
{
    int countSpace = 0;
    for (int i = 0; (*str1)[i] == ' '; i++)
        countSpace++;
    (*str1).erase(0, countSpace);
    int lenStr = (*str1).length();
    for (int j = 0; j < lenStr; j++)
    {
        if (((*str1)[j] == ' ') && ((*str1)[j + 1] == ' '))
        {
            countSpace = 0;
            while ((*str1)[j + countSpace + 1] == ' ')
                countSpace++;
            (*str1).erase(j + 1, countSpace);
            lenStr = (*str1).length();
        }
    }
}

void addSpaces(string* str1)
{
    int lenStr = (*str1).length();
    for (int j = 0; j < lenStr; j++) {
        if (((*str1)[j] == '!') || ((*str1)[j] == ',') || ((*str1)[j] == '-') ||
            ((*str1)[j] == ':') || ((*str1)[j] == ';') || ((*str1)[j] == '?'))
        {
            if ((*str1)[j + 1] != ' ') {
                (*str1).insert(j + 1, 1, ' ');
                lenStr = (*str1).length();
            }
        }
        if ((*str1)[j] == '.' && (*str1)[j + 1] == '.' && (*str1)[j + 2] == '.')
        {
            if ((*str1)[j + 3] != ' ')
            {
                (*str1).insert(j + 3, 1, ' ');
                lenStr = (*str1).length();
            }
        }
    }
}

void removeExtraPunctuation(string* str1)
{
    int countPuncts = 0, countPeriod = 0;
    for (int i = 0; ((*str1)[i] == '.') || ((*str1)[i] == '-') || ((*str1)[i] == ',') || ((*str1)[i] == ';') || ((*str1)[i] == ':') || ((*str1)[i] == '!') || ((*str1)[i] == '?'); i++)
        countPeriod++;
    (*str1).erase(0, countPeriod);
    int lenSpS1 = (*str1).length();
    for (int i = 0; i < lenSpS1; i++)
    {
        if (((*str1)[i] == '.') || ((*str1)[i] == '-') || ((*str1)[i] == ',') || ((*str1)[i] == ';') || ((*str1)[i] == ':') || ((*str1)[i] == '!') || ((*str1)[i] == '?'))
        {
            char mark = (*str1)[i];
            countPuncts = 0;
            while (((*str1)[i + countPuncts + 1] == '.') || ((*str1)[i + countPuncts + 1] == '-') || ((*str1)[i + countPuncts + 1] == ',') || ((*str1)[i + countPuncts + 1] == ':') || ((*str1)[i + countPuncts + 1] == '?') || ((*str1)[i + countPuncts + 1] == '!') || ((*str1)[i + countPuncts + 1] == ';'))
                countPuncts++;
            countPeriod = 0;
            while ((*str1)[i + countPeriod + 1] == mark)
                countPeriod++;
            if ((*str1)[i] == '.' && countPeriod + 1 >= 3)
            {
                (*str1).erase(i + 3, countPuncts - 2);
                lenSpS1 = (*str1).length();
                i += 2;
                continue;
            }
            (*str1).erase(i + 1, countPuncts);
            lenSpS1 = (*str1).length();
        }
    }
}

void fixLetterCase(string* str1)
{
    int lenStr = (*str1).length();
    if ((*str1)[0] >= 'a' && (*str1)[0] <= 'z')
        (*str1)[0] -= 32;
    for (int i = 1; i < lenStr; i++)
    {
        if (((*str1)[i] >= 'A' && (*str1)[i] <= 'Z') && ((*str1)[i - 1] != ' '))
            (*str1)[i] += 32;
        else if ((i >= 2) && ((*str1)[i] >= 'a' && (*str1)[i] <= 'z') && (((*str1)[i - 2] == '.') || ((*str1)[i - 2] == '!') || ((*str1)[i - 2] == '?')))
            (*str1)[i] -= 32;
    }
}

void printReverse(string* str)
{
    istringstream iss(*str);
    string word;
    vector<string> allWords;
    while (iss >> word) {
        if (!word.empty()) {
            allWords.push_back(word);
        }
    }
    for (int i = allWords.size() - 1; i >= 0; i--) {
        cout << allWords[i] << " ";
    }
    cout << "\n\n";
}

void printInColumns(string* str)
{
    istringstream iss(*str);
    string word;
    vector<string> allWords;
    while (iss >> word) {
        allWords.push_back(word);
    }
    int cols = (allWords.size() >= 6 ? 3 : 2);
    for (int i = 0; i < allWords.size(); i++) {
        cout << right << setw(10) << allWords[i];
        if ((i + 1) % cols == 0)
            cout << endl;
    }
}

void editString(string* str1)
{
    removeExtraSpaces(str1);
    removeExtraPunctuation(str1);
    addSpaces(str1);
    fixLetterCase(str1);
    cout << "Отредактированная строка:\n" << *str1 << "\n";
}

void lineSearch(string* str)
{
    string subStr;
    cout << *str << "\n\n";
    cout << "Введите строку\n";
    cin.ignore();
    getline(cin, subStr);
    int endString = subStr.length();
    int endLSS1 = (*str).length();
    if (endString == 0 || endLSS1 < endString)
    {
        cout << "Ошибка! Попробуйте снова.";
        system("Pause");
        subStr.erase(0, endString);
        lineSearch(str);
        return;
    }
    int j, flag = 0;
    for (int i = 0; i < endLSS1 - endString + 1; i++)
    {
        for (j = 0; j < endString; j++)
        {
            if ((*str)[i + j] != subStr[j])
                break;
            if (((*str)[i + j] == subStr[j]) && (j == endString - 1))
            {
                cout << "Строка найдена в позиции " << i + 1 << '\n';
                flag++;
                break;
            }
        }
    }
    if (!flag)
        cout << "Строка не найдена.\n";
}

void searchMenu(string* str)
{
    int menu;
    {
        cout << "\n1 - для запуска линейного поиска\n"
            << "0 - Выход из программы\n\n";
    }
    cin >> menu;
    switch (menu)
    {
    case 1:
        system("cls");
        lineSearch(str);
        _getch();
        searchMenu(str);
        break;
    case 0:
        system("cls");
        break;
    default:
        cout << "Ошибка! Попробуйте снова\n";
        _getch();
        system("cls");
        searchMenu(str);
        break;
    }
}

void main()
{
    string str;
    setlocale(LC_ALL, "RU");
    getString(&str);
    editString(&str);
    _getch();
    cout << "\nВывод последовательности слов в обратном порядке:\n";
    printReverse(&str);
    _getch();
    cout << "\nВывод последовательности слов в колонках:\n";
    printInColumns(&str);
    cout << "\n\nПоиск подстроки:\n\n";
    searchMenu(&str);
}

