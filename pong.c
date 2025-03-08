#include <stdio.h>

// Переменные для хранения счета игроков
int perviyIgrokSchet = 0; // Счет первого игрока
int vtoroyIgrokSchet = 0; // Счет второго игрока

// Объявление функций
void igrovat(); // Функция для игры
int obrabotatVvodPervogoIgroka(char vvod, int pervayaRaketkaVerh,
                               int pervayaRaketkaNiz, int minY, int maxY);
int obrabotatVvodVtorogoIgroka(char vvod, int vtorayaRaketkaVerh,
                               int vtorayaRaketkaNiz, int minY, int maxY);

int main(void) {
    // Основной игровой цикл
    while (perviyIgrokSchet < 21 && vtoroyIgrokSchet < 21) {
        igrovat(); // Запускаем игру
    }

    // Поздравление победителя
    if (perviyIgrokSchet == 21) {
        printf("Поздравляем! Первый игрок победил со счетом : %d \n",
               perviyIgrokSchet);
    } else if (vtoroyIgrokSchet == 21) {
        printf("Поздравляем! Второй игрок победил со счетом : %d \n",
               vtoroyIgrokSchet);
    }

    return 0; // Завершение программы
}

void igrovat() {
    // Позиции ракеток
    int pervayaRaketkaVerh = 5; // верхняя граница первой ракетки
    int pervayaRaketkaNiz = 7; // нижняя граница первой ракетки
    int pervayaRaketkaX = 3; // x-координата первой ракетки
    int vtorayaRaketkaVerh = 17; // верхняя граница второй ракетки
    int vtorayaRaketkaNiz = 19; // нижняя граница второй ракетки
    int vtorayaRaketkaX = 76; // x-координата второй ракетки

    // Символы для отображения
    char vertikalnayaGranica = '|';   // Вертикальная граница
    char gorizontalnayaGranica = '-'; // Горизонтальная граница
    char pustoeProstranstvo = ' ';    // Пустое пространство
    char myachSimvol = 'o';           // Символ мяча

    // Позиции мяча
    int myachX = 39;       // x-координата мяча
    int myachY = 12;       // y-координата мяча
    int myachSkorostX = 1; // скорость мяча по x
    int myachSkorostY = 1; // скорость мяча по y

    // Параметры игрового поля
    int maxY = 25; // максимальная высота игрового поля
    int maxX = 80; // максимальная ширина игрового поля
    int minY = 1; // минимальная высота игрового поля

    printf("\033[0d\033[2J");   // Очистка экрана
    while (1) {                 // Игровой цикл
        printf("\033[0d\033[2J"); // Очистка экрана

        // Отображение игрового поля
        for (int y = 0; y < maxY; y++) {   // Проход по высоте
            for (int x = 0; x < maxX; x++) { // Проход по ширине
                if (x == 0 || x == maxX - 1) {
                    printf("%c", vertikalnayaGranica); // Отображение вертикальных границ
                } else if (y == 0 || y == maxY - 1) {
                    printf("%c",
                           gorizontalnayaGranica); // Отображение горизонтальных границ
                } else if (y == myachY && x == myachX) {
                    printf("%c", myachSimvol); // Отображение мяча
                } else if ((y >= pervayaRaketkaVerh && y <= pervayaRaketkaNiz &&
                            x == pervayaRaketkaX) ||
                           (y >= vtorayaRaketkaVerh && y <= vtorayaRaketkaNiz &&
                            x == vtorayaRaketkaX)) {
                    printf("%c", vertikalnayaGranica); // Отображение ракеток
                } else {
                    printf("%c", pustoeProstranstvo); // Отображение пустого пространства
                }
            }
            printf("\n"); // Переход на новую строку
        }

        // Изменение направления мяча при достижении границ
        if (myachY == 23)
            myachSkorostY = -1; // Если мяч достиг нижней границы, меняем направление
        if (myachY == 1)
            myachSkorostY = 1; // Если мяч достиг верхней границы, меняем направление

        // Проверка на победу первого игрока
        if (myachX == 79) {
            perviyIgrokSchet++; // Увеличиваем счет первого игрока
            printf("Очко для Первого игрока! Текущий счет: %d - %d\n",
                   perviyIgrokSchet, vtoroyIgrokSchet);
            break; // Завершение раунда
        }
        // Проверка на победу второго игрока
        if (myachX == 0) {
            vtoroyIgrokSchet++; // Увеличиваем счет второго игрока
            printf("Очко для Второго игрока! Текущий счет: %d - %d\n",
                   perviyIgrokSchet, vtoroyIgrokSchet);
            break; // Завершение раунда
        }

        // Проверка столкновений мяча с ракетками
        if ((vtorayaRaketkaVerh <= myachY && myachY <= vtorayaRaketkaNiz &&
             myachX == vtorayaRaketkaX - 1))
            myachSkorostX = -1; // Проверка для второй ракетки
        if (pervayaRaketkaVerh <= myachY && myachY <= pervayaRaketkaNiz &&
            myachX == pervayaRaketkaX + 1)
            myachSkorostX = 1; // Проверка для первой ракетки

        // Отображение текущего счета
        printf("Очки Первого игрока: %d\n", perviyIgrokSchet);
        printf("Очки Второго игрока: %d\n", vtoroyIgrokSchet);

        char vvod = getchar(); // Получение ввода от пользователя
        // Обработка ввода для первой ракетки
        if (obrabotatVvodPervogoIgroka(vvod, pervayaRaketkaVerh, pervayaRaketkaNiz,
                                       minY, maxY) == 1) {
            pervayaRaketkaVerh++; // Двигаем ракетку вверх
            pervayaRaketkaNiz++; // Обновляем нижнюю границу ракетки
        } else if (obrabotatVvodPervogoIgroka(vvod, pervayaRaketkaVerh,
                                              pervayaRaketkaNiz, minY,
                                              maxY) == -1) {
            pervayaRaketkaVerh--; // Двигаем ракетку вниз
            pervayaRaketkaNiz--; // Обновляем нижнюю границу ракетки
        }
        // Обработка ввода для второй ракетки
        if (obrabotatVvodVtorogoIgroka(vvod, vtorayaRaketkaVerh, vtorayaRaketkaNiz,
                                       minY, maxY) == 1) {
            vtorayaRaketkaVerh++; // Двигаем ракетку вверх
            vtorayaRaketkaNiz++; // Обновляем нижнюю границу ракетки
        } else if (obrabotatVvodVtorogoIgroka(vvod, vtorayaRaketkaVerh,
                                              vtorayaRaketkaNiz, minY,
                                              maxY) == -1) {
            vtorayaRaketkaVerh--; // Двигаем ракетку вниз
            vtorayaRaketkaNiz--; // Обновляем нижнюю границу ракетки
        }

        // Движение мяча
        if (vvod == '\n') {        // Если нажата клавиша Enter
            myachX += myachSkorostX; // Обновляем x-координату мяча
            myachY += myachSkorostY; // Обновляем y-координату мяча
        }
    }
}

// Функция обработки ввода для первой ракетки
int obrabotatVvodPervogoIgroka(char vvod, int pervayaRaketkaVerh,
                               int pervayaRaketkaNiz, int minY, int maxY) {
    if ((vvod == 'a' || vvod == 'A') && pervayaRaketkaVerh != minY)
        return -1; // Движение вниз
    if ((vvod == 'z' || vvod == 'Z') && pervayaRaketkaNiz != maxY - 2)
        return 1; // Движение вверх
    return 0;   // Нет движения
}

// Функция обработки ввода для второй ракетки
int obrabotatVvodVtorogoIgroka(char vvod, int vtorayaRaketkaVerh,
                               int vtorayaRaketkaNiz, int minY, int maxY) {
    if ((vvod == 'k' || vvod == 'K') && vtorayaRaketkaVerh != minY)
        return -1; // Движение вниз
    if ((vvod == 'm' || vvod == 'M') && vtorayaRaketkaNiz != maxY - 2)
        return 1; // Движение вверх
    return 0;   // Нет движения
}
