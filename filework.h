#ifndef FILEWORK_H
#define FILEWORK_H

extern const char* const VideoFile;

typedef struct tagVideo Video;
// Структура для видео
struct tagVideo {
    char title[100];    // Название видео
    char author[100];   // Автор
    int likes;          // Количество лайков
    Video* pPrev;       // Указатель на предыдущее видео
};
extern Video* pRoot;    // Последнее добавленное видео

void loadVideos();          // Загрузка видео
void saveVideos();          // Сохранение видео
void addVideo();            // Добавление видео
void deleteVideo();         // Удаление видео
void displayVideos();       // Вывести список видео на экране
void removeAll();           // Удалить всё из памяти

#endif // FILEWORK_H

