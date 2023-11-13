#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include"AdditionalFunctions.h"

#define size_eng_alphabet 26
#define size_ukr_alphabet 33
using namespace std;


//декодування зашифрованого тексту на українській мові
void ukr_decrypted() {
    // вектор с теоретичою частоою літер укр алфавіта
    vector<pair<char, double>> theoretical_freq;
    theoretical_freq.push_back(make_pair('а', 9.1));
    theoretical_freq.push_back(make_pair('б', 1.9));
    theoretical_freq.push_back(make_pair('в', 6.6));
    theoretical_freq.push_back(make_pair('г', 2.3));
    theoretical_freq.push_back(make_pair('ґ', 0.0));
    theoretical_freq.push_back(make_pair('д', 3.6));
    theoretical_freq.push_back(make_pair('е', 5.3));
    theoretical_freq.push_back(make_pair('є', 0.7));
    theoretical_freq.push_back(make_pair('ж', 1.0));
    theoretical_freq.push_back(make_pair('з', 2.7));
    theoretical_freq.push_back(make_pair('и', 6.7));
    theoretical_freq.push_back(make_pair('і', 5.0));
    theoretical_freq.push_back(make_pair('ї', 1.1));
    theoretical_freq.push_back(make_pair('й', 1.4));
    theoretical_freq.push_back(make_pair('к', 3.5));
    theoretical_freq.push_back(make_pair('л', 4.3));
    theoretical_freq.push_back(make_pair('м', 3.6));
    theoretical_freq.push_back(make_pair('н', 6.6));
    theoretical_freq.push_back(make_pair('о', 10.2));
    theoretical_freq.push_back(make_pair('п', 3.1));
    theoretical_freq.push_back(make_pair('р', 5.7));
    theoretical_freq.push_back(make_pair('с', 4.7));
    theoretical_freq.push_back(make_pair('т', 4.8));
    theoretical_freq.push_back(make_pair('у', 3.8));
    theoretical_freq.push_back(make_pair('ф', 0.3));
    theoretical_freq.push_back(make_pair('х', 1.0));
    theoretical_freq.push_back(make_pair('ц', 0.6));
    theoretical_freq.push_back(make_pair('ч', 1.7));
    theoretical_freq.push_back(make_pair('ш', 0.9));
    theoretical_freq.push_back(make_pair('щ', 0.8));
    theoretical_freq.push_back(make_pair('ь', 1.3));
    theoretical_freq.push_back(make_pair('ю', 0.8));
    theoretical_freq.push_back(make_pair('я', 2.5));


    //текущяя частота, инициализация вектора и дальнейшее заполнение
    vector<pair<char, double>> current_freq(size_ukr_alphabet);

    const char* ukr_alphabet_lower = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";   // українский алфавіт з діакритикою в кодуванні 
    const char* ukr_alphabet_upper = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";

    for (size_t i = 0; i < current_freq.size(); i++)
    {
        current_freq[i].first = ukr_alphabet_lower[i];
        current_freq[i].second = 0.0;
    }

    //Перенесення даних з файлу до вектору
    vector<string> encoded_text;
    ifstream original_texts;
    original_texts.open("Original_text_ukr.txt");
    while (!original_texts.eof())
    {
        string str;
        getline(original_texts, str);
        encoded_text.push_back(str);

    }
    original_texts.close();

    //Підрахунок загальної кількості літер у тексті + підрахунок кількості кожної літери окремо у тексті
    int character_counter = 0;
    for (size_t i = 0; i < encoded_text.size(); i++)    //количество строк
    {
        for (size_t j = 0; j < encoded_text[i].length(); j++)   //длина і-той строки
        {
            //cout << encoded_text[i][j];
            if (!chek_ukr_super(encoded_text[i][j]) && !chek_ukr_litle(encoded_text[i][j]) || encoded_text[i][j] == ' ')
            {
                continue;
            }
            else
            {
                character_counter++;
                for (size_t k = 0; k < size_ukr_alphabet; k++)
                {
                    if (tolower(encoded_text[i][j]) == current_freq[k].first)
                    {
                        current_freq[k].second += 1.0;
                        break;
                    }
                }
            }
        }
    }

    //Підрахунок фактичної частоти кожної букви
    for (size_t i = 0; i < size_ukr_alphabet; i++)
    {
        current_freq[i].second = (current_freq[i].second / character_counter) * 100;
    }

    // Пошук можливих ключів та їх запис у вектор з повторами
    vector<int> possible_keys;
    for (size_t i = 0; i < size_ukr_alphabet; i++)
    {
        for (size_t j = 0; j < size_ukr_alphabet; j++)
        {
            if (current_freq[i].second >= (theoretical_freq[j].second - 0.3) && current_freq[i].second <= (theoretical_freq[j].second + 0.3))
            {
                possible_keys.push_back(((current_freq[i].first - theoretical_freq[j].first) + size_ukr_alphabet) % size_ukr_alphabet);

            }
        }
    }
    //Сортування вектора ключів та знаходження самого ключа
    vector<int> keys = sort(possible_keys);


    int minys = 0, error = 0;
    while (true)
    {
        int key = keys[0 + minys];

        //Дешифровка тексту та його вивід на єкран
        vector<string> decoded_text;
        char litter;
        for (size_t i = 0; i < encoded_text.size(); i++)
        {
            string text;
            for (size_t j = 0; j < encoded_text[i].length(); j++)
            {
                int index = -1;
                bool is_upper = false;
                for (int k = 0; k < size_ukr_alphabet; k++)
                {
                    if (encoded_text[i][j] == ukr_alphabet_lower[k])
                    {
                        index = k;
                        break;
                    }
                    else if (encoded_text[i][j] == ukr_alphabet_upper[k])
                    {
                        index = k;
                        is_upper = true;
                        break;
                    }
                }
                if (index == -1)
                {
                    text.push_back(encoded_text[i][j]);
                }
                else
                {
                    index = (index - key + size_ukr_alphabet) % size_ukr_alphabet;
                    if (is_upper)
                    {
                        text.push_back(ukr_alphabet_upper[index]);
                    }
                    else
                    {
                        text.push_back(ukr_alphabet_lower[index]);
                    }
                }
            }
            decoded_text.push_back(text);
        }
        //Перевірка на те, що дешифрований текст розшифрован правильно
        vector<string> ukr_words = { "там", "про", "вона", "за", "та", "його", "він", "бути", "по",
            "ти", "але", "вже", "або", "також", "під", "він", "вона", "вони", "як", "над",
            "коли", "чому", "але", "так", "зараз","тут", "там", "хто", "щоб", "все"
        };

        if (!checkWords(decoded_text, ukr_words))
        {
            //cout << "\n\t МИНУС КЛЮЧ" << endl;
            minys++;
            error++;
        }

        if (checkWords(decoded_text, ukr_words))
        {
            cout << "\nДешифрований текст має вигляд:" << endl;
            for (size_t i = 0; i < decoded_text.size(); i++)
            {
                cout << decoded_text[i];
            }
            break;
        }

        if (error >= keys.size())
        {
            cout << "\n!----------------------------------------------!"
                "\n!            | !Виникла помилка! |             !"
                "\n! Можливі причини винекнення помилки:          !"
                "\n! *Недостатній розмір зашифрованого тексту     !"
                "\n! *Текст зашифрован за допомогою іншого шифру  !"
                "\n! *Інша невідома нам причина                   !"
                "\n!----------------------------------------------!";
            break;
        }
        //36 //43 //46
    }
}


void eng_decrypted() {
    // вектор с теоретическими частотами букв англ алфавіта
    vector<pair<char, double>> theoretical_freq;
    theoretical_freq.push_back(make_pair('a', 8.2));
    theoretical_freq.push_back(make_pair('b', 1.5));
    theoretical_freq.push_back(make_pair('c', 2.8));
    theoretical_freq.push_back(make_pair('d', 4.3));
    theoretical_freq.push_back(make_pair('e', 12.7));
    theoretical_freq.push_back(make_pair('f', 2.2));
    theoretical_freq.push_back(make_pair('g', 2.0));
    theoretical_freq.push_back(make_pair('h', 6.1));;
    theoretical_freq.push_back(make_pair('i', 7.0));
    theoretical_freq.push_back(make_pair('j', 0.2));
    theoretical_freq.push_back(make_pair('k', 0.8));
    theoretical_freq.push_back(make_pair('l', 4.0));
    theoretical_freq.push_back(make_pair('m', 2.4));
    theoretical_freq.push_back(make_pair('n', 6.7));
    theoretical_freq.push_back(make_pair('o', 7.5));
    theoretical_freq.push_back(make_pair('p', 1.9));
    theoretical_freq.push_back(make_pair('q', 0.1));
    theoretical_freq.push_back(make_pair('r', 0.6));
    theoretical_freq.push_back(make_pair('s', 6.3));
    theoretical_freq.push_back(make_pair('t', 9.1));
    theoretical_freq.push_back(make_pair('u', 2.8));
    theoretical_freq.push_back(make_pair('v', 1.0));
    theoretical_freq.push_back(make_pair('w', 2.3));
    theoretical_freq.push_back(make_pair('x', 0.1));
    theoretical_freq.push_back(make_pair('y', 2.0));
    theoretical_freq.push_back(make_pair('z', 0.1));

    //текущяя частота, инициализация вектора и дальнейшее заполнение
    vector<pair<char, double>> current_freq(size_eng_alphabet);

    const char* eng_alphabet_lower = "abcdefghijklmnopqrstuvwxyz";
    const char* eng_alphabet_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (size_t i = 0; i < current_freq.size(); i++)
    {
        current_freq[i].first = eng_alphabet_lower[i];
        current_freq[i].second = 0.0;
    }
    vector<string> encoded_text;
    //Перенесення даних з файлу до вектору
    ifstream original_texts;
    original_texts.open("Original_text_eng.txt");
    while (!original_texts.eof())
    {
        string str;
        getline(original_texts, str);
        encoded_text.push_back(str);

    }
    original_texts.close();

    //Підрахунок загальної кількості символів та одночасний підрахунок кількості кожної літери окремо
    int character_counter = 0;
    for (size_t i = 0; i < encoded_text.size(); i++)
    {
        for (size_t j = 0; j < encoded_text[i].length(); j++)
        {
            if (!isupper(encoded_text[i][j]) && !islower(encoded_text[i][j]))
            {
                continue;
            }
            else
            {
                character_counter++;
                for (size_t k = 0; k < size_eng_alphabet; k++)
                {
                    if (tolower(encoded_text[i][j]) == current_freq[k].first)
                    {
                        current_freq[k].second += 1.0;
                        break;
                    }
                }
            }
        }
    }
    
    //Підрахунок фактичної частоті шифрованого тексту
    for (size_t i = 0; i < size_eng_alphabet; i++)
    {
        current_freq[i].second = (current_freq[i].second / character_counter) * 100;
    }

    // Пошук усіх можливих ключів
    vector<int> possible_keys;
    for (size_t i = 0; i < size_eng_alphabet; i++)
    {
        for (size_t j = 0; j < size_eng_alphabet; j++)
        {
            if (current_freq[i].second >= (theoretical_freq[j].second - 0.4) && current_freq[i].second <= (theoretical_freq[j].second + 0.4))
            {
                possible_keys.push_back(current_freq[i].first - theoretical_freq[j].first);

            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    //Сортування вектору з можливими ключами та знаходження самого ключа
    vector<int> keys = sort(possible_keys);


    int minys = 0, error = 0;
    while (true)
    {
        int key = keys[0 + minys];
        vector<string> decoded_text;
        char litter;

        for (size_t i = 0; i < encoded_text.size(); i++)
        {
            string text;
            for (size_t j = 0; j < encoded_text[i].length(); j++)
            {
                int index = -1;
                bool is_upper = false;
                for (int k = 0; k < size_eng_alphabet; k++)
                {
                    if (encoded_text[i][j] == eng_alphabet_lower[k])
                    {
                        index = k;
                        break;
                    }
                    else if (encoded_text[i][j] == eng_alphabet_upper[k])
                    {
                        index = k;
                        is_upper = true;
                        break;
                    }
                }
                if (index == -1)
                {
                    text.push_back(encoded_text[i][j]);
                }
                else
                {
                    index = (index - key + size_eng_alphabet) % size_eng_alphabet;
                    if (is_upper)
                    {
                        text.push_back(eng_alphabet_upper[index]);
                    }
                    else
                    {
                        text.push_back(eng_alphabet_lower[index]);
                    }
                }
            }
            decoded_text.push_back(text);
        }
        //Перевірка на те, що дешифрований текст розшифрован правильно
        vector<string> eng_words = { "the", "and", "in", "that", "have", 
            "for", "not", "with", "you", "this", "but", "his",  
            "from", "they", "say", "her", "she", "will", "one", "all", 
            "would", "what", "about", "who", "get", "which" 
        };

        if (!checkWords(decoded_text, eng_words))
        {
            minys++;
            error++;
        }

        if (checkWords(decoded_text, eng_words))
        {
            cout << "\nДешифрований текст має вигляд:" << endl;
            for (size_t i = 0; i < decoded_text.size(); i++)
            {
                cout << decoded_text[i];
            }
            break;
        }

        if (error >= keys.size())
        {
            cout << "\n!----------------------------------------------!"
                "\n!            | !Виникла помилка! |             !"
                "\n! Можливі причини винекнення помилки:          !"
                "\n! *Недостатній розмір зашифрованого тексту     !"
                "\n! *Текст зашифрован за допомогою іншого шифру  !"
                "\n! *Інша невідома нам причина                   !"
                "\n!----------------------------------------------!"; 
            break;
        }

    }

}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    cout<< "\n |---------------------------------|\n | \tЗЛОМ ШИФРУ ЦЕЗАРЯ\t   |\n |---------------------------------|"
        "\n  1. Дешифрувати англійський текст\n  2. Дешифрувати український текст\n  3. Вийти з програми"
        "\n -----------------------------------" << "\n | Оберіть один з варіантів(1/2/3) |" << "\n -----------------------------------\n >> ";

    while (true)
    {
        
        string command;
        cin >> command;

        if (command == "1")
        {
            cout << "\n -----------------------------------" << "\n |\tАнглійський дешифратор\t   |" << "\n -----------------------------------" << endl;
            input_to_file("Original_text_eng.txt");                             //Ввод данных в файл Оriginal_text_eng.txt
            while (true)
            {
                cout << "\n Ви завершили запис зашифрованого тексту?\n  1. Так\n  2. Ні\n >> ";  cin >> command;
                if (command == "1") { break; }
                if (command == "2") { app_to_file("Original_text_eng.txt"); }
                
            }
            eng_decrypted();
        }

        if (command == "2")
        {
            cout << "\n -----------------------------------" << "\n |\tУкраїнський дешифратор\t   |" << "\n -----------------------------------" << endl;
            input_to_file("Original_text_ukr.txt");                             //Ввод данных в файл Оriginal_text_ukr.txt
            while (true)
            {
                cout << "\n Ви завершили запис зашифрованого тексту?\n  1. Так\n  2. Ні\n >> ";  cin >> command;
                if (command == "1") { break; }
                if (command == "2") { app_to_file("Original_text_ukr.txt"); }

            }
            ukr_decrypted();
        }

        if (command == "3")
        {
            cout << "\nЗавершення програми";
            break;
        }

        else
        {
            cout << "\n\n ---------------------------------------" << "\n | Оберіть один з варіантів(1 / 2 / 3) | " << "\n ---------------------------------------";
            cout << "\n  1. Дешифрувати англійський текст\n  2. Дешифрувати український текст\n  3. Вийти з програми\n >> ";
        }
    }

    return 0;
}
