#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <random>
#include <cstdint>
using namespace std;

// ������������ ���������
uint32_t linearCongruentialGenerator(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223) {
    return (a * seed + c) % 4294967296;
}

// ��������� ��������� � ������
class LaggedFibonacciGenerator
{
private:
    vector<uint32_t> state;
    size_t a, b;
    long int m;

public:
    LaggedFibonacciGenerator(const vector<uint32_t>& seedList, size_t lagA, size_t lagB, uint32_t mod)
        : state(seedList), a(lagA), b(lagB), m(mod) {}

    uint32_t next() {
        size_t size = state.size();
        if (size == 0 || size < a || size < b) {
            cerr << "������: ������������ ��������� �������� ��� ����������." << endl;
            exit(1);
        }

        uint32_t newValue = (state[(size - a) % size] + state[(size - b) % size]);
        state.push_back(newValue);
        state.erase(state.begin());
        return newValue;
    }
};

// �������������� ������ � �������������
string gammaAndEncrypt(const string& text, LaggedFibonacciGenerator& fibonacciGen) {
    string encryptedText;
    for (char c : text) {
        uint32_t fibValue = fibonacciGen.next();
        uint64_t scaledFib = (fibValue * 1000000000000ULL) % UINT64_MAX;
        uint8_t gamma = scaledFib & 0xFF;  // ���������� ������� 8 ���
        encryptedText += static_cast<char>(c ^ gamma);  // ��������� XOR
    }
    return encryptedText;
}

int main()
{
    system("chcp 1251");
    system("cls");

    // ������������� ������������� ����������
    uint32_t seed = random_device{}();
    vector<uint32_t> initialSeeds;
    for (size_t i = 0; i < 97; ++i)
    {
        seed = linearCongruentialGenerator(seed);
        initialSeeds.push_back(seed);
    }
    // ������������� ���������� ���������
    LaggedFibonacciGenerator fibonacciGen(initialSeeds, 97, 33, 4294967296);

    // �������� ����� (ASCII)
    string text = "�������� �����.";

    // ����������
    string encryptedText = gammaAndEncrypt(text, fibonacciGen);

    // ����� ��������������� ������������������
    cout << "��������������� ������������������ (� �������� ����):" << endl;
    for (size_t i = 0; i < text.size(); ++i) {
        uint32_t fibValue = fibonacciGen.next();
        uint64_t scaledFib = (fibValue * 1000000000000ULL) % UINT64_MAX;
        cout << bitset<64>(scaledFib) << endl;
    }
    cout << endl;

    // ����� �����������
    cout << "������������ �����: " << text << endl;
    cout << endl;

    cout << "������������� �����: ";
    for (char c : encryptedText) {
        cout << bitset<8>(static_cast<unsigned char>(c)) << " ";
    }
    cout << endl;

    // ������������
    string decryptedText = gammaAndEncrypt(encryptedText, fibonacciGen);
    cout << "�������������� �����: " << decryptedText << endl;

    return 0;
}