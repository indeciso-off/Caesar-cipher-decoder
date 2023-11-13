#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

using namespace std;

//Перевірка символа, що він є литерою українського алфавіта (у нижньому та у верхньому регістрі)
bool chek_ukr_litle(char c) {
    if (c == 'а' || c == 'б' || c == 'в' || c == 'г' || c == 'ґ' || c == 'д'
        || c == 'е' || c == 'є' || c == 'ж' || c == 'з' || c == 'и' || c == 'і'
        || c == 'ї' || c == 'й' || c == 'к' || c == 'л' || c == 'м' || c == 'н'
        || c == 'о' || c == 'п' || c == 'р' || c == 'с' || c == 'т' || c == 'у'
        || c == 'ф' || c == 'х' || c == 'ц' || c == 'ч' || c == 'ш' || c == 'щ'
        || c == 'ь' || c == 'ю' || c == 'я')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool chek_ukr_super(char c) {
    if (c == 'А' || c == 'Б' || c == 'В' || c == 'Г' || c == 'Ґ' || c == 'Д'
        || c == 'Е' || c == 'Є' || c == 'Ж' || c == 'З' || c == 'И' || c == 'І'
        || c == 'Ї' || c == 'Й' || c == 'К' || c == 'Л' || c == 'М' || c == 'Н'
        || c == 'О' || c == 'П' || c == 'Р' || c == 'С' || c == 'Т' || c == 'У'
        || c == 'Ф' || c == 'Х' || c == 'Ц' || c == 'Ч' || c == 'Ш' || c == 'Щ'
        || c == 'Ь' || c == 'Ю' || c == 'Я')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Функція для сортуавання вектора по частоті можливих ключів без повторів //////////
vector<int> sort(vector<int>& vec)
{
    map<int, int> m;
    for (int i = 0; i < vec.size(); i++)
        m[vec[i]]++;
    vector<pair<int, int>> v(m.begin(), m.end());
    for (int i = 0; i < v.size() - 1; i++)
        for (int j = i + 1; j < v.size(); j++)
            if (v[i].second < v[j].second)
                swap(v[i], v[j]);
    vector<int> res;
    for (int i = 0; i < v.size(); i++)
        if (find(res.begin(), res.end(), v[i].first) == res.end())
            res.push_back(v[i].first);
    return res;
}

//Ввод зашифрованого тексту до файлу
void input_to_file(string FileName) {           //Функция ввода данных в файл, который требуеться расшифровать
    ofstream original_text;

    original_text.open(FileName);

    string text;
    cout << " Введіть зашифрований текст. Для завершення введіть спеціальний символ '/' та натисніть Enter\n >> ";
    getline(cin, text, '/');
    original_text << text;

    original_text.close();
}

void app_to_file(string FileName) {           //Функция ввода данных в файл, который требуеться расшифровать
    ofstream original_text;

    original_text.open(FileName, ios::app);

    string text;
    cout << "Доповніть зашифрований текст. Для завершення введіть спеціальний символ '/' та натисніть Enter\n >> ";
    getline(cin, text, '/');
    original_text << text;

    original_text.close();
}

//Перетворення строк в окремі слова для перевірки
vector<string> splitString(string str) {
    vector<string> words;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

//Перевірка тексту на наявність укрїнських слів
bool checkWords(vector<string> text, vector<string> words) {
    int count = 0;
    for (int i = 0; i < text.size(); i++) {
        vector<string> temp = splitString(text[i]);
        for (int j = 0; j < temp.size(); j++) {

            for (int k = 0; k < words.size(); k++) {
                if (temp[j] == words[k]) {
                    //cout << words[k] << endl;
                    count++;
                    if (count == 5) {
                        return true;
                    }

                }
            }
        }
    }
    return false;
}
