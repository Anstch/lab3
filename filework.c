#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filework.h"

Video* pRoot = NULL;

const char* const VideoFile = "videos.txt";


void loadVideos() {
    FILE* file = fopen(VideoFile, "rb");
    if (!file) {
        printf("Файл не найден\n");
        return;
    }
    removeAll(); // Удаляем всё, что хранится в памяти в этот момент, чтобы записать по новой всё из файла

    Video* video = (Video*)malloc(sizeof(Video)); //выделяем память под запись, который будем читать
    if (video == NULL)
    {
        printf("Память не выделена\n");
        return;
    }

    fread(video, sizeof(Video), 1, file);    // Читаем из файла первую запись в выделеную память
    pRoot = video;                         // Записываем указатель на эту карточку в pRoot, так как это первая запись
   pRoot->pPrev = NULL;

    while (1) // Создаём бесконечный цикл, пока его не прервёт другой цикл, который находится в нём
    {
        video = (Video*)malloc(sizeof(Video)); // Выделяем память под новую запись
        if (video == NULL)                                         // Если память не выделена, то выходим
        {
            printf("Память не выделена\n");
            return;
        }
        fread(video, sizeof(Video), 1, file); // Считываем запись
        if (feof(file))                                   // Если достигли конца файла, то 
        {
            free(video);                                          // освобождаем память (она нам не понадобилась)
            break;                                                // и выходим из бесконечного цикла
        }
        video->pPrev = pRoot;  // Добавляем указатель на предыдущее видео
        pRoot = video;         // Запоминаем адрес нового элемента
    }
    fclose(file);
}

void removeAll()
{
    Video* pRem;

    while (pRoot != NULL)        // Пока есть записи
    {
        pRem = pRoot;         // Записываем в удаляемую переменную найденную запись
        pRoot = pRoot->pPrev; // Переходим к следующей
        free(pRem);           // Освобождаем память, удаляя карточку
    }
    pRoot = NULL;
}

void saveVideos() {
    FILE* file = fopen(VideoFile, "wb");
    if (!file) {
        printf("Файл не найден\n");
        return;
    }
    Video* video = pRoot;

    while (video)  // Пока не дойдем до конца списка
    {
        fwrite(video, sizeof(Video), 1, file); // Записываем элемент в файл
        video = video->pPrev;                              // Переходим к следующей записи
    }
    fclose(file);
}

void addVideo() {
    Video* pNew = (Video*)malloc(sizeof(Video));
    if (pNew == NULL) {    // проверим выделилась ли память
        printf("Ошибка!\n");
        return;
   }

    printf("Введите название видео:\n>");
    scanf(" %s", pNew->title);

    printf("Введите автора:\n>");
    scanf(" %s", pNew->author);

    printf("Укажите количество лайков:\n>");
    scanf("%d", &pNew->likes);

    pNew->pPrev = pRoot; // добавляем указатель на последнюю добавленную запись до этой (или =0, если это единственная >
    pRoot = pNew; // делаем pRoot последней добавленной записью (запоминаем, что база данных непуста)
}

void deleteVideo() {
    int index;
    printf("Введите номер элемента, который желаете удалить: \n");
    scanf("%d", &index);
    index--;
    
    if (pRoot == NULL) // Если книжка пуста, то выходим
    {
        return;
    }

    if (index < 0)
    {
       printf("Ошибка, введен некорректный номер\n");
        return;
    }

    Video* pRem = pRoot; // Создаём указатель на ту запись, которую хотим удалим

    if (index == 0) // Если первая запись, то удаляем начальный элемент
    {
        pRoot = pRoot->pPrev; // Переставляем pRoot на следующую запись
        free(pRem);           // Начальный элемент удаляем из памяти
    }
    else           // Любая другая
    {
        int num = 0; // Текущий номер видео
        Video* pCur = pRoot;
        while (num < index)
        {
            if (pRem->pPrev == NULL) { // Если предыдущей записи не существует
                printf("Номер слишком большой, такой записи нет\n");
            }
            pCur = pRem;
            pRem = pRem->pPrev; // Переходим к предыдущему видео
            num++;
        }

        if (pRem == NULL) // Проверяем существует ли найденное удаляемое видео
        {
            printf("Запись не найдена!\n");
            return;
        }
        pCur->pPrev = pRem->pPrev;  // Переставляем связи
        free(pRem);                          // Освобождаем память, удаляя запись
    }
}

void displayVideos() {
    Video* video = pRoot; // Указатель на отображаемую карточку видео
    int i = 1; // Номер карточки видео

    printf(" № | Название        | Автор       | Лайки         \n");

    while (video) // Пока есть видео, выводим их на экран
    {
        printf("---+-----------------+-------------+---------------\n");
        printf("%2d ", i);
        printf("| %-16.16s",video->title);
        printf("| %-12s", video->author);
        printf("| %-16d\n", video->likes);

        video = video->pPrev;
        i++;
    }
}

