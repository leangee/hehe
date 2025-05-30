#include "railway_system.h"
#include <iostream>
#include <clocale>
#include <limits>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef max
#undef max
#endif

void initLocalization() {
    setlocale(LC_ALL, "ru_RU.UTF-8");  // Для macOS/Linux
    std::locale::global(std::locale(""));  // Установка системной локали
}

void displayMenu() {
    std::cout << "\n=== Железнодорожная сортировочная система ===";
    std::cout << "\n1. Загрузить данные из файла";
    std::cout << "\n2. Ввести данные вручную";
    std::cout << "\n3. Показать результаты";
    std::cout << "\n4. Сохранить результаты в файл";
    std::cout << "\n5. Очистить систему";
    std::cout << "\n6. Выход";
    std::cout << "\nВыберите действие: ";
}

void manualInput(RailwaySystem& system) {
    int id, typeInput;
    float weight;
    char choice;

    do {
        std::cout << "\n=== Ввод данных ===";

        // Ввод ID
        std::cout << "\nВведите ID вагона: ";
        while (!(std::cin >> id) || id <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите положительное число для ID: ";
        }

        // Ввод типа
        std::cout << "Введите тип (0 - тип 1, 1 - тип 2): ";
        while (!(std::cin >> typeInput) || (typeInput != 0 && typeInput != 1)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите 0 или 1: ";
        }
        WagonType type = static_cast<WagonType>(typeInput);

        // Ввод веса
        std::cout << "Введите вес вагона (тонны): ";
        while (!(std::cin >> weight) || weight <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите положительное число для веса: ";
        }

        system.addWagon(Wagon(id, type, weight));

        std::cout << "\nДанные успешно добавлены!";
        std::cout << "\nХотите добавить ещё вагон? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');
}

int main() {
    initLocalization();

    RailwaySystem system;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();

        int maxChoice = 6;
        while (!(std::cin >> choice) || choice < 1 || choice > maxChoice) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Пожалуйста, введите число от 1 до "
                << maxChoice << ": ";
        }

        try {
            switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "\nВведите имя файла (например: data/input.txt): ";
                std::cin >> filename;
                system.loadFromFile(filename);
                system.processSorting();
                std::cout << "\nДанные успешно загружены и обработаны!";
                break;
            }
            case 2:
                manualInput(system);
                system.processSorting();
                break;
            case 3:
                system.displayResults();
                break;
            case 4: {
                std::string filename;
                std::cout << "\nВведите имя файла для сохранения: ";
                std::cin >> filename;
                system.saveToFile(filename);
                std::cout << "\nРезультаты успешно сохранены в файл!";
                break;
            }
            case 5:
                system.clearSystem();
                std::cout << "\nСистема очищена!";
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "\nНеизвестная команда! Пожалуйста, попробуйте снова.";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "\nОшибка: " << e.what() << std::endl;
        }
    }

    std::cout << "\nПрограмма завершена. Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}