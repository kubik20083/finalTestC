#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "temp_functions.h"
#include <bits/getopt_core.h>

int main(int argc, char *argv[])
{
    char * file_name;       
    int input_month = 0;    
    int res_arg = 0;        
    opterr=0;
    while ((res_arg = getopt(argc, argv, "hf:m::")) != -1)
    {
        switch (res_arg)
        {
        case 'h':
            help();
            break;
        case 'f':
            file_name = optarg;
            break;
        case 'm':
            input_month = atoi(optarg);
            break;
        case '?':
            printf("Ошибка: неверный параметр!\n");
            break;
        };
    };

    if (argc < 2){
        printf("\nПрограмма считывает данные датчика температуры из файла и печатает статистику за год или месяц\n");
        
        printf("Для вывода инструкций введите параметр \"-h\" \n");
    }

    if(file_name && ((input_month >= 0) && (input_month < 13)))
    {
        printf("%s\n", file_name);
        struct sensor * info;                                               
        info = (struct sensor *)malloc(SIZE * sizeof(struct sensor));       
        long number_of_lines = add_info(info, file_name);                   
        if(input_month == 0)
        {
            statistics_output(info, number_of_lines);
        }
        else 
        {
            statistics_output_month(info, number_of_lines, input_month);
        }
        free(info);
    }
    else
    {
        printf("\nНеверный параметр\n");
        help();
    }
    return 0;
}