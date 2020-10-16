/*
fxFile.cpp

Functions about file operation.
*/


#ifdef __cplusplus
extern "C"
{
#endif




#include <fxlib.h>
#include <stdlib.h>
#include <string.h>

#include "fxFile.hpp"
#include "fxCSV.hpp"


// Thanks diameter for this part
// Change string to FONTCHARACTER format
FONTCHARACTER *CharToFont(char *str)
{
    int len = strlen(str);

    FONTCHARACTER * font_str = (FONTCHARACTER *)calloc(len + 1, sizeof(FONTCHARACTER));

    int i;
    for (i = 0; i < len; ++i)
        font_str[i] = str[i];
    font_str[i] = '\0';

    return font_str;
}


// Change file name to file path, and change string to FONTCHARACTER format
FONTCHARACTER *CharFileNameToFontFilePath(char *file_name, int storage)
{
    char *file_path = (char *)malloc(sizeof(char) * (strlen(file_name) + 8));
    file_path[0] = '\0';

    // path
    if (storage == FLASH)
        strcat(file_path, "\\\\fls0\\");
    else strcat(file_path, "\\\\crd0\\");
    
    // name
    strcat(file_path, file_name);

    // convert char * to FONTCHARACTER *
    FONTCHARACTER *font_file_path = CharToFont(file_path);

    return font_file_path;
}


// Create file. If fail, return 0
int FileCreate(char *file_name, int storage, int file_size)
{
    FONTCHARACTER *font_file_path = CharFileNameToFontFilePath(file_name, storage);

    if (Bfile_CreateFile(font_file_path, file_size) == 0) // Success
    {
        free(font_file_path);
        
        return 1;
    }
    else // Fail
    {
        free(font_file_path);

        return 0; 
    }
}


// Delete file. If fail, return 0
int FileDelete(char *file_name, int storage)
{
    FONTCHARACTER *font_file_path = CharFileNameToFontFilePath(file_name, storage);

    if (Bfile_DeleteFile(font_file_path) == 0) // Success
    {
        free(font_file_path);
        
        return 1;
    }
    else // Fail
    {
        free(font_file_path);

        return 0; 
    }
}


// Open file, return file handle. If fail, return 0
int FileOpen(char *file_name, int storage)
{
    FONTCHARACTER *font_file_path = CharFileNameToFontFilePath(file_name, storage);

    int return_val = Bfile_OpenFile(font_file_path, _OPENMODE_READWRITE);

    free(font_file_path);

    if (return_val < 0) // Fail        
        return 0;
    else return return_val; // Success
}


// Calculate the size of the CSV file
int FileCalcCSVSize(int col_amount, int *col, int row_amount, int *row)
{
    int size = 0;
    
    int i;
    for (i = 0; i < row_amount; i++)
    {
        char *line = GenerateCSVLine(col_amount, col, row[i], LINE_END_TYPE_1);

        size += strlen(line);

        free(line);
    }

    return size;
}


// Create and open file and write CSV. If fail, return 0
int FileGenerateCSV(char *file_name, int storage, int col_amount, int *col, int row_amount, int *row)
{
    // create
    if (!FileCreate(file_name, storage, FileCalcCSVSize(col_amount, col, row_amount, row)))
        return 0;
    
    // open
    int file_handle = FileOpen(file_name, storage);

    if (!file_handle) // fail to open file
        return 0;

    // move file_handle to beginning
    Bfile_SeekFile(file_handle, 0);

    int i;
    for (i = 0; i < row_amount; i++)
    {
        // use \n to end a CSV line
        char *line = GenerateCSVLine(col_amount, col, row[i], LINE_END_TYPE_1);

        // write a CSV line into file
        Bfile_WriteFile(file_handle, line, strlen(line));

        free(line);
    }

    return 1;
}




#ifdef __cplusplus
}
#endif