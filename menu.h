#ifndef MENU_H
#define MENU_H
typedef enum {
    MENU_PLAY,
    MENU_RECORDS,
    MENU_EXIT
} MenuOption;
typedef enum {
    Easy,
    Normal,
    Hard
} DifficultyOption;
typedef struct {
    char name[50];
    int score;
    char date[50]; // اضافه کردن تاریخ به رکوردها
} Record;

// --- پروتوتایپ توابع ---
void SaveRecord(const char *filename, const Record *record);
int LoadRecords(const char *filename, Record records[], int maxRecords);
void DisplayRecords(const Record records[], int count, Font customFont);
int InputPlayerName(char *name, int maxLen, Font customFont, Texture2D background, Music menuMusic);
int ShowMenu(Texture2D background, Font customFont,Music menuMusic);
int ShowDifficulty(Texture2D background, Font customFont, Music menuMusic);
int Showmap(Texture2D background, Font customFont, Music menuMusic);
int CompareScores(const void *a, const void *b);
void SortRecords(const char *filePath);
#endif // MENU_H
