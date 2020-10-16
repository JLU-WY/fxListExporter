/*
fxFile.hpp

Functions about file operation.
*/


#ifndef _FXFILE_HPP_
#define _FXFILE_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// Storge: flash
#define FLASH 0

// Storge: sdcard
#define SDCARD 1


// Create file. If fail, return 0
int FileCreate(char* file_name, int storge, int file_size);

// Delete file. If fail, return 0
int FileDelete(char* file_name, int storge);

// Open file, return file handle. If fail, return 0
int FileOpen(char* file_name, int storge);

// Create and open and write CSV. If fail ,return 0
int FileGenerateCSV(char* file_name, int storge, int col_amount, int *col, int row_amount, int *row);




#ifdef __cplusplus
}
#endif

#endif