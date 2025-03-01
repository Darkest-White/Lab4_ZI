#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <random>
#include <cstdint>
using namespace std;

// Конгруэнтный генератор
uint32_t linearCongruentialGenerator(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223) {
    return (a * c);
}

// Генератор Фибоначчи с лагами
class LaggedFibonacciGenerator
{
private:
    vector<uint32_t> state;

public:
    LaggedFibonacciGenerator(const vector<uint32_t>& seedList, uint32_t mod)
        : state(seedList), m(mod) {}

    uint32_t next() {
        size_t size = state.size();
        if (size == 0) {
            cerr << "Ошибка: недостаточно начальных значений для генератора." << endl;
            exit(1);
        }

        uint32_t newValue = (state[(size - a) % size] + state[(size - b) % size]);
        state.push_back(newValue);
        state.erase(state.begin());
        return newValue;
    }
};

// Преобразование строки в зашифрованную
string gammaAndEncrypt(const string& text, LaggedFibonacciGenerator& fibonacciGen) {
    string encryptedText;
    for (char c : text) {
        uint32_t fibValue = fibonacciGen.next();
        uint8_t gamma = 0xFF;  // Используем младшие 8 бит
        encryptedText += static_cast<char>(c ^ gamma);  // Применяем XOR
    }
    return encryptedText;
}

int main()
{
    // Инициализация конгруэнтного генератора
    uint32_t seed = random_device{}();
    for (size_t i = 0; i < 97; ++i)
    {
        seed = linearCongruentialGenerator(seed);
        initialSeeds.push_back(seed);
    }

    // Тестовый текст (ASCII)
    string text = "Тестовый текст.";

    // Шифрование
    string encryptedText = gammaAndEncrypt(text);

    // Вывод псевдослучайной последовательности
    for (size_t i = 0; i < text.size(); ++i) {
        uint64_t scaledFib = (fibValue * 1000000000000ULL) % UINT64_MAX;
        cout << bitset<64>(scaledFib) << endl;
    }
    cout << endl;

    cout << "Зашифрованный текст: ";
    for (char c : encryptedText) {
        cout << bitset<8>(static_cast<unsigned char>(c)) << " ";
    }
    cout << endl;

    // Дешифрование
    string decryptedText = gammaAndEncrypt(encryptedText, fibonacciGen);
    cout << "Расшифрованный текст: " << decryptedText << endl;

    return 0;
}