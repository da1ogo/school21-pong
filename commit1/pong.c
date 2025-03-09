#include <stdio.h>

// Переменные для хранения счета игроков
int player_one_score = 0; // Счет первого игрока
int player_two_score = 0; // Счет второго игрока

// Объявление функций
void play_game(); // Функция для игры
int handle_player_one_input(char input, int paddle_one_top, int paddle_one_bottom,
                            int min_y, int max_y);
int handle_player_two_input(char input, int paddle_two_top, int paddle_two_bottom,
                            int min_y, int max_y);

int main(void) {
    // Основной игровой цикл
    while (player_one_score < 21 && player_two_score < 21) {
        play_game(); // Запускаем игру
    }

    // Поздравление победителя
    if (player_one_score == 21) {
        printf("Congratulations! Player One has won with a score of: %d - %d\n", 
               player_one_score, player_two_score);
    } else if (player_two_score == 21) {
        printf("Congratulations! Player Two has won with a score of: %d - %d\n", 
               player_two_score, player_one_score);
    }

    return 0; // Завершение программы
}

void play_game() {
    // Позиции ракеток
    int paddle_one_top = 5;    // Верхняя граница первой ракетки
    int paddle_one_bottom = 7; // Нижняя граница первой ракетки
    int paddle_one_x = 3;      // X-координата первой ракетки
    int paddle_two_top = 17;   // Верхняя граница второй ракетки
    int paddle_two_bottom = 19; // Нижняя граница второй ракетки
    int paddle_two_x = 76;     // X-координата второй ракетки

    // Символы для отображения
    char vertical_border = '|';   // Вертикальная граница
    char horizontal_border = '-'; // Горизонтальная граница
    char empty_space = ' ';       // Пустое пространство
    char ball_symbol = 'o';       // Символ мяча

    // Позиции мяча
    int ball_x = 39;       // X-координата мяча
    int ball_y = 12;       // Y-координата мяча
    int ball_speed_x = 1;  // Скорость мяча по X
    int ball_speed_y = 1;  // Скорость мяча по Y

    // Параметры игрового поля
    int max_y = 25; // Максимальная высота игрового поля
    int max_x = 80; // Максимальная ширина игрового поля
    int min_y = 1;  // Минимальная высота игрового поля

    printf("\033[0d\033[2J"); // Очистка экрана
    while (1) {               // Игровой цикл
        printf("\033[0d\033[2J"); // Очистка экрана

        // Отображение игрового поля
        for (int y = 0; y < max_y; y++) {   // Проход по высоте
            for (int x = 0; x < max_x; x++) { // Проход по ширине
                if (x == 0 || x == max_x - 1) {
                    printf("%c", vertical_border); // Отображение вертикальных границ
                } else if (y == 0 || y == max_y - 1) {
                    printf("%c", horizontal_border); // Отображение горизонтальных границ
                } else if (y == ball_y && x == ball_x) {
                    printf("%c", ball_symbol); // Отображение мяча
                } else if ((y >= paddle_one_top && y <= paddle_one_bottom &&
                            x == paddle_one_x) ||
                           (y >= paddle_two_top && y <= paddle_two_bottom &&
                            x == paddle_two_x)) {
                    printf("%c", vertical_border); // Отображение ракеток
                } else {
                    printf("%c", empty_space); // Отображение пустого пространства
                }
            }
            printf("\n"); // Переход на новую строку
        }

        // Изменение направления мяча при достижении границ
        if (ball_y == 23)
            ball_speed_y = -1; // Если мяч достиг нижней границы, меняем направление
        if (ball_y == 1)
            ball_speed_y = 1; // Если мяч достиг верхней границы, меняем направление

        // Проверка на победу первого игрока
        if (ball_x == 79) {
            player_one_score++; // Увеличиваем счет первого игрока
            printf("Point for Player One! Current score: %d - %d\n",
                   player_one_score, player_two_score);
            break; // Завершение раунда
        }
        // Проверка на победу второго игрока
        if (ball_x == 0) {
            player_two_score++; // Увеличиваем счет второго игрока
            printf("Point for Player Two! Current score: %d - %d\n",
                   player_one_score, player_two_score);
            break; // Завершение раунда
        }

        // Проверка столкновений мяча с ракетками
        if ((paddle_two_top <= ball_y && ball_y <= paddle_two_bottom &&
             ball_x == paddle_two_x - 1))
            ball_speed_x = -1; // Проверка для второй ракетки
        if (paddle_one_top <= ball_y && ball_y <= paddle_one_bottom &&
            ball_x == paddle_one_x + 1)
            ball_speed_x = 1; // Проверка для первой ракетки

        // Отображение текущего счета
        printf("Player One's score: %d\n", player_one_score);
        printf("Player Two's score: %d\n", player_two_score);

        char input = getchar(); // Получение ввода от пользователя
        // Обработка ввода для первой ракетки
        if (handle_player_one_input(input, paddle_one_top, paddle_one_bottom,
                                    min_y, max_y) == 1) {
            paddle_one_top++;    // Двигаем ракетку вверх
            paddle_one_bottom++; // Обновляем нижнюю границу ракетки
        } else if (handle_player_one_input(input, paddle_one_top, paddle_one_bottom,
                                           min_y, max_y) == -1) {
            paddle_one_top--;    // Двигаем ракетку вниз
            paddle_one_bottom--; // Обновляем нижнюю границу ракетки
        }
        // Обработка ввода для второй ракетки
        if (handle_player_two_input(input, paddle_two_top, paddle_two_bottom,
                                    min_y, max_y) == 1) {
            paddle_two_top++;    // Двигаем ракетку вверх
            paddle_two_bottom++; // Обновляем нижнюю границу ракетки
        } else if (handle_player_two_input(input, paddle_two_top, paddle_two_bottom,
                                           min_y, max_y) == -1) {
            paddle_two_top--;    // Двигаем ракетку вниз
            paddle_two_bottom--; // Обновляем нижнюю границу ракетки
        }

        // Движение мяча
        if (input == '\n') {        // Если нажата клавиша Enter
            ball_x += ball_speed_x; // Обновляем X-координату мяча
            ball_y += ball_speed_y; // Обновляем Y-координату мяча
        }
    }
}

// Функция обработки ввода для первой ракетки
int handle_player_one_input(char input, int paddle_one_top, int paddle_one_bottom,
                            int min_y, int max_y) {
    if ((input == 'a' || input == 'A') && paddle_one_top != min_y)
        return -1; // Движение вниз
    if ((input == 'z' || input == 'Z') && paddle_one_bottom != max_y - 2)
        return 1; // Движение вверх
    return 0;   // Нет движения
}

// Функция обработки ввода для второй ракетки
int handle_player_two_input(char input, int paddle_two_top, int paddle_two_bottom,
                            int min_y, int max_y) {
    if ((input == 'k' || input == 'K') && paddle_two_top != min_y)
        return -1; // Движение вниз
    if ((input == 'm' || input == 'M') && paddle_two_bottom != max_y - 2)
        return 1; // Движение вверх
    return 0;   // Нет движения
}
