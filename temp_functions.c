#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"


int checking_data(long string_counter, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, int8_t t)
{
    if(year != 2021)
    {
        printf("\nОшибка формата даты\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - %d | t - %d\n", year, month, day, hour, min, t);
        return 0;
    }
    else if ((month < 1) || (month > 12))
    {
        printf("\nОшибка формата даты\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - %d | t - %d\n", year, month, day, hour, min, t);
        return 0;
    }
    else if ((day < 1) || (day > 31))
    {
        printf("\nОшибка формата даты\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - %d | t - %d\n", year, month, day, hour, min, t);
        return 0;
    }
    else if ((hour < 0) || (hour > 23))
    {
        printf("\nОшибка формата даты\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - %d | t - %d\n", year, month, day, hour, min, t);
        return 0;
    }
    else if ((min < 0) || (min > 59))
    {
        printf("\nОшибка формата даты\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - >%d< | t - %d\n", year, month, day, hour, min, t);
        return 0;
    }
    else if ((t < -99) || (t > 99))
    {
        printf("\nОшибка формата темпиратуры\n");
        printf("Год - %d | Месяц - %d | День - %d | Час - %d | Мин - %d | t - >%d<\n", year, month, day, hour, min, t);
        return 0;
    }
    else
    {
       return 1;
    }
}


void statistics_output(struct sensor* info, long string_counter)
{
    int minT = info[0].t;
    int maxT = info[0].t;
    long sum = 0;
    float average = 0;
    for (long i = 0; i < string_counter; i++)
    {
        if (minT > info[i].t)
        {
            minT = info[i].t;
        }
        if (maxT < info[i].t)
        {
            maxT = info[i].t;
        }
        sum += info[i].t;
    }
    average = (float)sum / string_counter;
    printf("\nПолная статистика\n");
    printf("Показания датчика : %ld\n", string_counter);
    printf("Минимальная температура = %d\n", minT);
    printf("Максимальная температура = %d\n", maxT);
    printf("Средняя температура = %.1f\n", average);
}

//Функия вывода статистики из файла, считываются записи за указаный месяц
void statistics_output_month(struct sensor* info, long string_counter, int input_month)
{
    int minT = 90;
    int maxT = -90;
    long sum = 0;
    float average = 0;
    long line_count_month = 0;                  
    for (long i = 0; i < string_counter; i++)
    {
        if((info[i].month == input_month))
        {
            if (minT > info[i].t)
            {
                minT = info[i].t;
            }
            if (maxT < info[i].t)
            {
                maxT = info[i].t;
            }
            line_count_month++;
            sum += info[i].t;
        }
    }
    average = (float)sum / line_count_month;
    printf("\nСтатистика за %d месяц\n", input_month);
    printf("Показания датчика : %ld\n", line_count_month);
    printf("Минимальная температура = %d\n", minT);
    printf("Максимальная температура = %d\n", maxT);
    printf("Средняя температура = %.1f\n", average);
}

//Функция переноса данных из строки в структуру
void add_record(struct sensor *info, long string_number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, int8_t t)
{
    info[string_number].year = year;
    info[string_number].month = month;
    info[string_number].day = day;
    info[string_number].hour = hour;
    info[string_number].min = min;
    info[string_number].t = t;
}


long add_info(struct sensor *info, char * file_name)
{
    FILE *fp;
    fp = fopen(file_name, "r");
    long counter = 0;                           
    long err_string_counter = 0;                
    if (fp == NULL)
    {
        printf("ОШИБКА: файл не может быть открыт.\n");
        exit(-1);
    }
        
    int Y, M, D, H, Min, T, r;                     
    long errors = 0;                            
    while ((r = fscanf(fp, "%d;%d;%d;%d;%d;%d", &Y, &M, &D, &H, &Min, &T)) > 0)
    {
        err_string_counter++;
        if (r < 6)
        {
            char s[20];
            r = fscanf(fp, "%[^\n]", s);
            printf("\nОШИБКА: Данные потеряны\n Строка %ld пропущена.\n", err_string_counter);
            errors++;
        }
        else
        {
            if(checking_data(err_string_counter, Y, M, D, H, Min, T))
            {
                add_record(info, counter++, Y, M, D, H, Min, T);
            }
            else
            {
                errors++;
            }
        }
    }
    printf("\nКоличество правильных записей в файле : %ld\n",counter);
    printf("Количество пропущенных строк : %ld\n",errors);
    
    fclose(fp);
    return counter;  
}

//Функция вывода подсказки на экран
void help()
{
    printf("-h                 Помощь\n");
    printf("-f <filename.csv>  Обязательный параметр\n");
    printf("                   Этот параметр необходим для запуска программы\n");
    printf("                   Необходимо указать имя файла, содержащего данные\n");
    printf("-m [1...12]        Необязательный параметр\n");
    printf("                   При использовании данного параметра отображается статистика за указанный месяц.\n");
    printf("                   Если этот параметр не используется, отображается полная статистика.\n");
}