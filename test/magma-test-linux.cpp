#include <iostream>
#include <fstream>
#include <chrono> // Для замера времени
#include <iomanip> // Для форматирования вывода
#include "magma.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cerr << "Использование: " << argv[0] << " input.txt encrypted.txt" << endl;
        return 1;
    }

    // Открываем входной файл
    ifstream inputFile(argv[1], ios::binary);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть входной файл " << argv[1] << endl;
        return 1;
    }

    // Определяем размер файла
    inputFile.seekg(0, ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    // Читаем данные в буфер
    uint8_t* inputData = new uint8_t[fileSize];
    inputFile.read((char*)inputData, fileSize);
    inputFile.close();

    // Инициализируем шифр с фиксированным ключом (256 бит)
    Magma cipher;
    cipher.setKey({0xffeeddcc, 0xbbaa9988, 0x77665544, 0x33221100,
                   0xf0f1f2f3, 0xf4f5f6f7, 0xf8f9fafb, 0xfcfdfeff});

    // Замеряем время шифрования
    size_t paddedSize = (fileSize + 7) / 8 * 8; // Длина с учетом дополнения
    uint8_t* outputData = new uint8_t[paddedSize];
    
    auto start = chrono::high_resolution_clock::now();
    size_t encryptedSize = cipher.encryptECB(inputData, outputData, fileSize);
    auto end = chrono::high_resolution_clock::now();

    // Рассчитываем время в секундах
    double duration = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
    double fileSizeMB = fileSize / (1024.0 * 1024.0); // Размер файла в МБ
    double speedMBps = fileSizeMB / duration; // Скорость в МБ/с
    size_t numBlocks = encryptedSize / 8; // Количество 64-битных блоков
    double timePerBlock = duration / numBlocks; // Время на один блок в секундах

    // Открываем выходной файл
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Ошибка: не удалось открыть выходной файл " << argv[2] << endl;
        delete[] inputData;
        delete[] outputData;
        return 1;
    }

    // Записываем зашифрованные данные в шестнадцатеричном формате
    outputFile << hex;
    for (size_t i = 0; i < encryptedSize; i++) {
        outputFile << setw(2) << setfill('0') << (int)outputData[i];
        if (i % 16 == 15) outputFile << endl; // Разделяем на строки по 16 байт
    }
    outputFile.close();

    // Выводим результаты производительности
    cout << fixed << setprecision(2);
    cout << "Файл: " << argv[1] << endl;
    cout << "Размер файла: " << fileSizeMB << " МБ" << endl;
    cout << "Время шифрования: " << duration << " сек" << endl;
    cout << "Скорость шифрования: " << speedMBps << " МБ/с" << endl;
    cout << "Количество блоков: " << numBlocks << endl;
    cout << scientific << setprecision(2);
    cout << "Среднее время на блок: " << timePerBlock << " сек" << endl;
    cout << "Файл успешно зашифрован: " << argv[2] << endl;

    // Очищаем память
    delete[] inputData;
    delete[] outputData;

    return 0;
}