/*
fxFile.hpp

Functions about file operation.
*/


#ifndef _FXFILE_HPP_
#define _FXFILE_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// Storage: flash
#define FLASH 0

// Storage: sdcard
#define SDCARD 1


// Create file. If fail, return 0
int FileCreate(char* file_name, int storage, int file_size);

// Delete file. If fail, return 0
int FileDelete(char* file_name, int storage);

// Open file, return file handle. If fail, return 0
int FileOpen(char* file_name, int storage);

// Create and open and write CSV. If fail ,return 0
int FileGenerateCSV(char* file_name, int storage, int col_amount, int *col, int row_amount, int *row);




#ifdef __cplusplus
}
#endif

#endif