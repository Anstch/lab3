#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "filework.h"

static void help() {
    printf(
        "Меню:\n"
        "  1   добавить видео\n"
        "  2   удалить видео\n"
        "  3   показать все видео\n"
        "  4   загрузить видео из файла\n"
        "  5   закончить работу\n\n"
    );
    printf("Введите команду:\n");
}

int main() {
    help(); // Выводим меню
    bool exit = false; // Для выхода из цикла, когда пользователь закончит работу
    int command;
    printf("\n>");

    while (!exit) {
        printf("Введите команду:\n");
        scanf("%d", &command);
        switch (command) {
        case 1:
            addVideo();
            saveVideos();
            break;
        case 2:
            deleteVideo();
            saveVideos();
            break;
        case 3:
            displayVideos();
            break;
        case 4:
            loadVideos();
            displayVideos();
            break;
        case 5:
            exit = true;
            return 0;
            break;
        default:
            printf("Ошибка\n\n");
            help();
            break;
        }

    }
    removeAll(); // Чистим память
    return 0;
}
