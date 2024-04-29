#include <stdint.h>
#define SIZE 100000

struct sensor {
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t min;
    int8_t t;
};
//Функия вывода статистики из файла, считываются все записи
void statistics_output(struct sensor* info, long string_counter);
//Функия вывода статистики из файла, считываются записи за указаный месяц
void statistics_output_month(struct sensor* info, long string_counter, int input_month);
//Функция проверки данных в строке. Если данные не соответствуют, то выводится сообщение с конкретной ошибкой и номером пропущеной строки
int checking_data(long string_counter, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, int8_t t);
//Функция переноса данных из строки в конкретную структуру
void add_record(struct sensor *info, long string_number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, int8_t t);
//Функция в которой происходит чтение из файла и запись в массив структурного типа при помощи вспомогательных фунций checking_data() и add_record()
long add_info(struct sensor *info, char * file_name);
//Функция вывода подсказки на экран
void help();