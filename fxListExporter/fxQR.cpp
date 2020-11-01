// QR.cpp by flaribbit
// See https://github.com/flaribbit/FxQr

/*
MIT License

Copyright (c) 2017 flaribbit

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifdef __cplusplus
  extern "C" {
#endif


#include <fxlib.h>
#include <string.h>
#include <stdlib.h>
#include "fxCSV.hpp"
#include "fxQR.hpp"

unsigned char a[] = { // 256 bytes
	1, 2, 4, 8, 16, 32, 64, 128,
	29, 58, 116, 232, 205, 135, 19, 38,
	76, 152, 45, 90, 180, 117, 234, 201,
	143, 3, 6, 12, 24, 48, 96, 192,
	157, 39, 78, 156, 37, 74, 148, 53,
	106, 212, 181, 119, 238, 193, 159, 35,
	70, 140, 5, 10, 20, 40, 80, 160,
	93, 186, 105, 210, 185, 111, 222, 161,
	95, 190, 97, 194, 153, 47, 94, 188,
	101, 202, 137, 15, 30, 60, 120, 240,
	253, 231, 211, 187, 107, 214, 177, 127,
	254, 225, 223, 163, 91, 182, 113, 226,
	217, 175, 67, 134, 17, 34, 68, 136,
	13, 26, 52, 104, 208, 189, 103, 206,
	129, 31, 62, 124, 248, 237, 199, 147,
	59, 118, 236, 197, 151, 51, 102, 204,
	133, 23, 46, 92, 184, 109, 218, 169,
	79, 158, 33, 66, 132, 21, 42, 84,
	168, 77, 154, 41, 82, 164, 85, 170,
	73, 146, 57, 114, 228, 213, 183, 115,
	230, 209, 191, 99, 198, 145, 63, 126,
	252, 229, 215, 179, 123, 246, 241, 255,
	227, 219, 171, 75, 150, 49, 98, 196,
	149, 55, 110, 220, 165, 87, 174, 65,
	130, 25, 50, 100, 200, 141, 7, 14,
	28, 56, 112, 224, 221, 167, 83, 166,
	81, 162, 89, 178, 121, 242, 249, 239,
	195, 155, 43, 86, 172, 69, 138, 9,
	18, 36, 72, 144, 61, 122, 244, 245,
	247, 243, 251, 235, 203, 139, 11, 22,
	44, 88, 176, 125, 250, 233, 207, 131,
	27, 54, 108, 216, 173, 71, 142, 1};

unsigned char a_inv[] = { // 256 bytes
	0, 0, 1, 25, 2, 50, 26, 198,
	3, 223, 51, 238, 27, 104, 199, 75,
	4, 100, 224, 14, 52, 141, 239, 129,
	28, 193, 105, 248, 200, 8, 76, 113,
	5, 138, 101, 47, 225, 36, 15, 33,
	53, 147, 142, 218, 240, 18, 130, 69,
	29, 181, 194, 125, 106, 39, 249, 185,
	201, 154, 9, 120, 77, 228, 114, 166,
	6, 191, 139, 98, 102, 221, 48, 253,
	226, 152, 37, 179, 16, 145, 34, 136,
	54, 208, 148, 206, 143, 150, 219, 189,
	241, 210, 19, 92, 131, 56, 70, 64,
	30, 66, 182, 163, 195, 72, 126, 110,
	107, 58, 40, 84, 250, 133, 186, 61,
	202, 94, 155, 159, 10, 21, 121, 43,
	78, 212, 229, 172, 115, 243, 167, 87,
	7, 112, 192, 247, 140, 128, 99, 13,
	103, 74, 222, 237, 49, 197, 254, 24,
	227, 165, 153, 119, 38, 184, 180, 124,
	17, 68, 146, 217, 35, 32, 137, 46,
	55, 63, 209, 91, 149, 188, 207, 205,
	144, 135, 151, 178, 220, 252, 190, 97,
	242, 86, 211, 171, 20, 42, 93, 158,
	132, 60, 57, 83, 71, 109, 65, 162,
	31, 45, 67, 216, 183, 123, 164, 118,
	196, 23, 73, 236, 127, 12, 111, 246,
	108, 161, 59, 82, 41, 157, 85, 170,
	251, 96, 134, 177, 187, 204, 62, 90,
	203, 89, 95, 176, 156, 169, 160, 81,
	11, 245, 22, 235, 122, 117, 44, 215,
	79, 174, 213, 233, 230, 231, 173, 232,
	116, 214, 244, 234, 168, 80, 88, 175};

unsigned char gen_poly[] = {																													  // 181 bytes
	74, 152, 176, 100, 86, 100, 106, 104, 130, 218, 206, 140, 78,																				  // 13th Polynomial (offset=0)
	215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153,															  // 18th Polynomial (offset=13)
	17, 60, 79, 50, 61, 163, 26, 187, 202, 180, 221, 225, 83, 239, 156, 164, 212, 212, 188, 190,												  // 20th Poly (offset=31)
	210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231,										  // 22nd Poly (offset=51)
	229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0, 117, 232, 87, 96, 227, 21,							  // 24th Poly (offset=73)
	173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13, 102, 48, 227, 153, 145, 218, 70,					  // 26th Poly (offset=97)
	168, 223, 200, 104, 224, 234, 108, 180, 110, 190, 195, 147, 205, 27, 232, 201, 21, 43, 245, 87, 42, 195, 212, 119, 242, 37, 9, 123,			  // 28th Poly  (offset=123)
	41, 173, 145, 152, 216, 31, 179, 182, 50, 48, 110, 86, 239, 96, 222, 125, 42, 173, 226, 193, 224, 130, 156, 37, 251, 216, 238, 40, 192, 180}; //30th Poly (offset=151)

unsigned char gen_offset[] = {0, 0, 0, 0, 0, 13, 0, 31, 0, 51, 0, 73, 0, 97, 0, 123, 0, 151}; //index 0 is for the 13th polynominal (18 bytes)

int16_t mask_info[] = {
	// 14 bytes
	13663, // Mask Q-0 (011010101011111)
	12392, // Mask Q-1 (011000001101000)
	16177, // Mask Q-2 (011111100110001)
	14854, // Mask Q-3 (011101000000110)
	9396,  // Mask Q-4 (010010010110100)
	8579,  // Mask Q-5 (010000110000011)
	11994, // Mask Q-6 (010111011011010)
	11245  // Mask Q-7 (010101111101101)
};

unsigned char version_info[] = {
	// 34 * 3 = 102 bytes; for simplicity, storing as three 6-bit numbers
	// TODO: CAN GET RID OF BYTE #3 -- IT'S PREDICTABLE!!!! REDUCES STORAGE TO 68 BYTES
	20, 50, 7,	// Version  7 (000111110010010100)
	60, 22, 8,	// Version  8 (001000010110111100)
	25, 42, 9,	// Version  9 (001001101010011001)
	19, 19, 10, // Version 10 (001010010011010011)
	54, 47, 11, // Version 11 (001011101111110110)
	34, 29, 12, // Version 12 (001100011101100010)
	7, 33, 13,	// Version 13 (001101100001000111)
	13, 24, 14, // Version 14 (001110011000001101)
	40, 36, 15, // Version 15 (001111100100101000)
	56, 45, 16, // Version 16 (010000101101111000)
	29, 17, 17, // Version 17 (010001010001011101)
	23, 40, 18, // Version 18 (010010101000010111)
	50, 20, 19, // Version 19 (010011010100110010)
	38, 38, 20, // Version 20 (010100100110100110)
	3, 26, 21,	// Version 21 (010101011010000011)
	9, 35, 22,	// Version 22 (010110100011001001)
	44, 31, 23, // Version 23 (010111011111101100)
	4, 59, 24,	// Version 24 (011000111011000100)
	33, 7, 25,	// Version 25 (011001000111100001)
	43, 62, 26, // Version 26 (011010111110101011)
	14, 2, 27,	// Version 27 (011011000010001110)
	26, 48, 28, // Version 28 (011100110000011010)
	63, 12, 29, // Version 29 (011101001100111111)
	53, 53, 30, // Version 30 (011110110101110101)
	16, 9, 31,	// Version 31 (011111001001010000)
	21, 39, 32, // Version 32 (100000100111010101)
	48, 27, 33, // Version 33 (100001011011110000)
	58, 34, 34, // Version 34 (100010100010111010)
	31, 30, 35, // Version 35 (100011011110011111)
	11, 44, 36, // Version 36 (100100101100001011)
	46, 16, 37, // Version 37 (100101010000101110)
	36, 41, 38, // Version 38 (100110101001100100)
	1, 21, 39,	// Version 39 (100111010101000001)
	41, 49, 40	// Version 40 (101000110001101001)
};

// Maximum unencoded original message length (character capacity) for Byte encoding, quality Q:
// V1=11, V2=20, V3=32, V4=46, V5=60, V6=74, V7=86, V8=108, V9=130, V10=151, V11=177, V12=203, V13=241, V14=258, V15=292,
// V16=322, V17=364, V18=394, V19=442, V20=482, V21=509
// V40 = 34*24 + 34*25 = 816+850=1666-3=1663 max len
unsigned char codeword_parameters[40][12] = {
	// 480 bytes
	// 1st column: error correction codewords per block
	// 2nd column: number of blocks in group 1
	// 3rd column: number of data codewords in each of group 1's blocks
	// 4th column: number of blocks in group 2
	// 5th column: number of data codewords in each of group 2's blocks
	// 6th column: number of remainder bits
	// 7th-13th column: alignment pattern locations center module (skipping location 6)
	//   note: (2nd * 3rd) + (4th * 5th) = number of maximum data codewords permitted in message
	//   note: pixel size is (4*VERSION+17) where VERSION starts at 1 through 40 (only 21 supported below)
	{13, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0},				// 1-Q
	{22, 1, 22, 0, 0, 7, 18, 0, 0, 0, 0, 0},			// 2-Q
	{18, 2, 17, 0, 0, 7, 22, 0, 0, 0, 0, 0},			// 3-Q
	{26, 2, 24, 0, 0, 7, 26, 0, 0, 0, 0, 0},			// 4-Q
	{18, 2, 15, 2, 16, 7, 30, 0, 0, 0, 0, 0},			// 5-Q
	{24, 4, 19, 0, 0, 7, 34, 0, 0, 0, 0, 0},			// 6-Q
	{18, 2, 14, 4, 15, 0, 22, 38, 0, 0, 0, 0},			// 7-Q
	{22, 4, 18, 2, 19, 0, 24, 42, 0, 0, 0, 0},			// 8-Q
	{20, 4, 16, 4, 17, 0, 26, 46, 0, 0, 0, 0},			// 9-Q
	{24, 6, 19, 2, 20, 0, 28, 50, 0, 0, 0, 0},			//10-Q
	{28, 4, 22, 4, 23, 0, 30, 54, 0, 0, 0, 0},			//11-Q
	{26, 4, 20, 6, 21, 0, 32, 58, 0, 0, 0, 0},			//12-Q
	{24, 8, 20, 4, 21, 0, 34, 62, 0, 0, 0, 0},			//13-Q
	{20, 11, 16, 5, 17, 3, 26, 46, 66, 0, 0, 0},		//14-Q
	{30, 5, 24, 7, 25, 3, 26, 48, 70, 0, 0, 0},			//15-Q
	{24, 15, 19, 2, 20, 3, 26, 50, 74, 0, 0, 0},		//16-Q
	{28, 1, 22, 15, 23, 3, 30, 54, 78, 0, 0, 0},		//17-Q
	{28, 17, 22, 1, 23, 3, 30, 56, 82, 0, 0, 0},		//18-Q
	{26, 17, 21, 4, 22, 3, 30, 58, 86, 0, 0, 0},		//19-Q
	{30, 15, 24, 5, 25, 3, 34, 62, 90, 0, 0, 0},		//20-Q
	{28, 17, 22, 6, 23, 4, 28, 50, 72, 94, 0, 0},		//21-Q
	{30, 7, 24, 16, 25, 4, 26, 50, 74, 98, 0, 0},		//22-Q
	{30, 11, 24, 14, 25, 4, 30, 54, 78, 102, 0, 0},		//23-Q
	{30, 11, 24, 16, 25, 4, 28, 54, 80, 106, 0, 0},		//24-Q
	{30, 7, 24, 22, 25, 4, 32, 58, 84, 110, 0, 0},		//25-Q
	{28, 28, 22, 6, 23, 4, 30, 58, 86, 114, 0, 0},		//26-Q
	{30, 8, 23, 26, 24, 4, 34, 62, 90, 118, 0, 0},		//27-Q
	{30, 4, 24, 31, 25, 3, 26, 50, 74, 98, 122, 0},		//28-Q
	{30, 1, 23, 37, 24, 3, 30, 54, 78, 102, 126, 0},	//29-Q
	{30, 15, 24, 25, 25, 3, 26, 52, 78, 104, 130, 0},	//30-Q
	{30, 42, 24, 1, 25, 3, 30, 56, 82, 108, 134, 0},	//31-Q
	{30, 10, 24, 35, 25, 3, 34, 60, 86, 112, 138, 0},	//32-Q
	{30, 29, 24, 19, 25, 3, 30, 58, 86, 114, 142, 0},	//33-Q
	{30, 44, 24, 7, 25, 3, 34, 62, 90, 118, 146, 0},	//34-Q
	{30, 39, 24, 14, 25, 0, 30, 54, 78, 102, 126, 150}, //35-Q
	{30, 46, 24, 10, 25, 0, 24, 50, 76, 102, 128, 154}, //36-Q
	{30, 49, 24, 10, 25, 0, 28, 54, 80, 106, 132, 158}, //37-Q
	{30, 48, 24, 14, 25, 0, 32, 58, 84, 110, 136, 162}, //38-Q
	{30, 43, 24, 22, 25, 0, 26, 54, 82, 110, 138, 166}, //39-Q
	{30, 34, 24, 34, 25, 0, 30, 58, 86, 114, 142, 170}	//40-Q
};

int is_mask_applicable(int16_t row, int16_t column, unsigned char mask_number)
{
	switch (mask_number)
	{
	case 0:
		return ((row + column) % 2 == 0);
	case 1:
		return ((row % 2) == 0);
	case 2:
		return ((column % 3) == 0);
	case 3:
		return ((row + column) % 3 == 0);
	case 4:
		return ((((row / 2) + (column / 3)) % 2) == 0); //double check floor
	case 5:
		return ((((row * column) % 2) + ((row * column) % 3)) == 0);
	case 6:
		return ((((row * column) % 2) + ((row * column) % 3)) % 2 == 0);
	case 7:
		return ((((row + column) % 2) + ((row * column) % 3)) % 2 == 0);
	}
	return 0;
}

void reedSolomon(int16_t data_codewords, int16_t data_offset, unsigned char message[], int16_t error_codewords, unsigned char errorcode[], unsigned char generator[])
{
	uint16_t i, j;
	for (i = 0; i < data_codewords; i++)
		errorcode[i] = message[i + data_offset];
	for (i = data_codewords; i < error_codewords; i++) // if error codewords > data codewords, need to initialize enough zeros for the math
		errorcode[i] = 0;
	//printArrayBYTE("init: ", error_codewords, errorcode);
	for (j = 1; j <= data_codewords; j++)
	{
		int16_t lead_term = a_inv[errorcode[0]];
		if (errorcode[0] != 0)
		{
			for (i = 1; i <= error_codewords; i++)
			{
				unsigned char temp_value = 0;
				if (i < error_codewords)
					temp_value = errorcode[i];
				errorcode[i - 1] = temp_value ^ a[(generator[i - 1] + lead_term) % 255];
			}
		}
		else
		{ // polynomial division step is greatly simiplified (just a shift of all terms left) if leading coeff. is zero
			for (i = 1; i <= error_codewords; i++)
				errorcode[i - 1] = errorcode[i];
		}
		for (i = error_codewords + 1; i <= data_codewords; i++)
		{
			errorcode[i - 1] = errorcode[i];
		}
		//printArrayBYTE("iter: ", error_codewords, errorcode);
	}
}

void parseMessage(const char *freetext, unsigned char test_vector[])
{
	unsigned char message[244] = {0};
	int16_t message_length = strlen(freetext);
	int16_t qr_version = -1;
	unsigned char *message_parameters;
	int message_index;

	int16_t error_codewords;
	unsigned char errorcode[30] = {0}; // 30 is highest EC count for Q-quality; 25 is highest dataword count for Q-quality
	int16_t total_blocks;
	unsigned char interleaved_output[532] = {0}; // 532 valid up to VERSION 13-Q; 3706 valid up to VERSION 40-Q
	int16_t message_offset;
	int16_t block_number;
	int16_t groups;

	int16_t output_size;
	int16_t max_pixels;
	unsigned char *image[64];
	int16_t finder_pattern;

	int16_t y;
	int16_t x;
	int16_t dir;
	int16_t primary_bits;
	int16_t remainder_bits;
	unsigned char working_byte;
	int16_t interleaved_index;
	unsigned char mask_number;

	uint16_t i, j;
	uint16_t x0, y0;

	for (i = 0; i < 40; i++)
	{
		int16_t capacity = codeword_parameters[i][1] * codeword_parameters[i][2] + codeword_parameters[i][3] * codeword_parameters[i][4] - 2;
		if (i > 8)
			capacity--; //subtract one extra byte because of switch to 16-bit length byte in QR Version 10+
		//printf("qr ver=%d  capacity=%d\n", i+1, capacity);
		if (message_length <= capacity)
		{
			qr_version = i;
			//printf("INFO: selected QR Version %d\n", qr_version+1);
			break;
		}
	}
	if (qr_version < 0 || qr_version > 10)
	{
		//printf("ERROR: Unable to find QR version capable of encoding input message.  Sorry, try again.\n");
		return;
	}

	message_parameters = codeword_parameters[qr_version];
	message_index = 0;
	message[message_index] = 64; // "0100" Byte Encoding
	if (qr_version > 8)
	{ // QR Verisons 10+ for Byte data encoding represent length as 16-bits
		message_index++;
		message[message_index++] = ((message_length & 5888) >> 4) | ((message_length & 240) >> 4);
	}
	else
	{ // QR Verisons 1 through 9 for Byte data encoding represent length as 8-bits
		message[message_index++] |= ((message_length & 240) >> 4);
	}
	message[message_index++] = ((message_length & 15) << 4) | ((freetext[0] & 240) >> 4);
	for (i = 0; i < message_length; i++)
		message[message_index++] = ((freetext[i] & 15) << 4) | ((freetext[i + 1] & 240) >> 4);

	{
		unsigned char pad[] = {236, 17};
		uint16_t pad_index = 0;
		uint16_t needed_pad_bytes =
			(message_parameters[1] * message_parameters[2]) + (message_parameters[3] * message_parameters[4]) - message_index;
		//printf("INFO: needed pad bytes: %d\n", needed_pad_bytes);
		for (i = 0; i < needed_pad_bytes; i++)
		{
			message[message_index++] = pad[pad_index];
			pad_index ^= 1;
		}
	}
	//printArrayBYTE("encoded input (with padding)", message_index, message);

	////
	error_codewords = message_parameters[0];
	total_blocks = message_parameters[1] + message_parameters[3];
	message_offset = 0;
	block_number = 0;
	for (groups = 0; groups < 2; groups++)
	{
		int16_t num_blocks = message_parameters[groups * 2 + 1];
		int16_t data_codewords = message_parameters[groups * 2 + 2];
		int16_t blocks;

		for (blocks = 0; blocks < num_blocks; blocks++)
		{
			int16_t interleaved_output_offset = block_number;
			reedSolomon(data_codewords, message_offset, message, error_codewords, errorcode, &gen_poly[gen_offset[message_parameters[0] - 13]]);
			//printf("REED OUTPUT: data_codewords=%d,  message_offset=%d,  error_codewords=%d,  gen_offset=%d\n", data_codewords, message_offset, error_codewords, gen_offset[message_parameters[0]-13]);
			//printArrayBYTEwithOffset("Data Codewords: ", data_codewords, message, message_offset);
			//printArrayBYTE("Error Codewords: ", error_codewords, errorcode);
			for (i = 0; i < data_codewords; i++)
			{
				interleaved_output[interleaved_output_offset] = message[i + message_offset];
				if (i + 1 < message_parameters[2]) // { 18, 2, 15, 2, 16}
					interleaved_output_offset += message_parameters[1];
				if (i + 1 < message_parameters[4])
					interleaved_output_offset += message_parameters[3];
			}
			interleaved_output_offset = message_parameters[1] * message_parameters[2] + message_parameters[3] * message_parameters[4] + block_number;
			for (i = 0; i < error_codewords; i++)
			{
				interleaved_output[interleaved_output_offset] = errorcode[i];
				interleaved_output_offset += total_blocks;
			}
			message_offset += data_codewords;
			block_number++;
		}
		//printArrayBYTE("output: ", 346, interleaved_output);
	}

	output_size =
		(message_parameters[1] * message_parameters[2]) + (message_parameters[3] * message_parameters[4]) // total data codewords
		+ ((message_parameters[1] + message_parameters[3])) * message_parameters[0];					  // total error codewords
	/*if (test_vector != 0) {
		for (i=0; i < output_size; i++) {
			if (interleaved_output[i] != test_vector[i]) {
				printf("\aERROR: TEST FAILED!  Index=%d\n", i);
				printArrayBYTE("output: ", output_size, interleaved_output);
				return;
			}
		}
		printf("INFO: TEST PASSED!\n");
	}
	//printArrayBYTE("output: ", output_size, interleaved_output);*/

	max_pixels = (qr_version * 4) + 21;
	for (i = 0; i < 64; i++)
	{
		image[i] = (unsigned char *)malloc(max_pixels);
		if (image[i] == 0)
		{
			return;
		}
	}
	for (i = 0; i < max_pixels; i++)
	{
		int j;
		for (j = 0; j < max_pixels; j++)
		{
			image[i][j] = 255; // set all pixels to white
		}
	}
	// add the three finder pattern modules to the qr code
	finder_pattern = (qr_version * 4) + 14;
	for (i = 0; i < 7; i++)
	{
		image[0][i] = 0; //top left module
		image[6][i] = 0;
		image[0][finder_pattern + i] = 0; //top right module
		image[6][finder_pattern + i] = 0;
		image[finder_pattern][i] = 0; //bottom left module
		image[max_pixels - 1][i] = 0;
	}
	for (i = 1; i < 6; i++)
	{
		image[i][0] = 0; //top left module
		image[i][6] = 0;
		image[i][finder_pattern] = 0; //top right module
		image[i][max_pixels - 1] = 0;
		image[finder_pattern + i][0] = 0; //bottom left module
		image[finder_pattern + i][6] = 0;
	}
	for (i = 2; i < 5; i++)
	{
		int j;
		for (j = 0; j < 3; j++)
		{
			image[2 + j][i] = 0;
			image[2 + j][i + finder_pattern] = 0;
			image[finder_pattern + 2 + j][i] = 0;
		}
	}
	//insert alignment patterns
	if (qr_version > 0)
	{ // no pattern for QR Version 1 (our qr_verison == 0)
		unsigned char center[7] = {0};
		center[0] = 6;
		for (i = 1; i < 7; i++)
			center[i] = message_parameters[5 + i];
		for (i = 0; i < 7; i++)
		{
			int j;
			for (j = 0; j < 7; j++)
			{
				if ((center[i] != 0) && (center[j] != 0))
				{
					//printf("coord=(%d,%d)\n", center[i], center[j]);
					if (image[center[i]][center[j]] == 255)
					{ //only add if bit is currently white
						int16_t k;
						image[center[i]][center[j]] = 0;
						for (k = 0; k < 5; k++)
						{
							image[center[i] - 2][center[j] - 2 + k] = 0;
							image[center[i] + 2][center[j] - 2 + k] = 0;
						}
						for (k = 0; k < 3; k++)
						{
							image[center[i] - 1 + k][center[j] - 2] = 0;
							image[center[i] - 1 + k][center[j] + 2] = 0;
						}
					}
				}
			}
		}
	}
	//adding timing patterns
	for (i = 8; i < max_pixels - 8; i += 2)
	{
		image[6][i] = 0;
		image[i][6] = 0;
	}
	//add the "dark module"
	image[(qr_version * 4) + 13][8] = 0;
	mask_number = 1; //printf("INFO: using mask %d\n", mask_number);
	//apply mask format info
	{
		int16_t mask = mask_info[mask_number];
		int16_t skip = 0;
		for (i = 0; i < 8; i++)
		{
			if (i == 6)
				skip = 1;
			if ((mask & 1) > 0)
			{
				image[8][max_pixels - i - 1] = 0;
				image[i + skip][8] = 0;
			}
			mask = mask >> 1;
		}
		skip = 0;
		for (i = 0; i < 7; i++)
		{
			if (i == 1)
				skip = -1;
			if ((mask & 1) > 0)
			{
				image[max_pixels - 7 + i][8] = 0;
				image[8][7 - i + skip] = 0;
			}
			mask = mask >> 1;
		}
	}
	//apply version info (for QR Versions 7+)
	if (qr_version > 5)
	{ //remember qr_version==6 is really V7
		int16_t offset = (qr_version - 6) * 3;
		for (i = 0; i < 3; i++)
		{
			unsigned char ver = version_info[offset + i];
			for (j = 0; j < 2; j++)
			{
				int k;
				for (k = 0; k < 3; k++)
				{
					if ((ver & 1) > 0)
					{
						image[0 + j + (i * 2)][max_pixels - 11 + k] = 0;
						image[max_pixels - 11 + k][0 + j + (i * 2)] = 0;
					}
					ver = ver >> 1;
				}
			}
		}
	}

	y = max_pixels - 1;
	x = max_pixels - 1;
	dir = -1;
	primary_bits = output_size * 8;
	remainder_bits = message_parameters[5];
	working_byte = 0;
	interleaved_index = -1;
	for (i = 0; i < primary_bits + remainder_bits; i++)
	{
		if (image[y][x] == 0)
		{							  // check for alignment marker hit
			if (image[y][x - 1] == 0) //hit alignment marker head=-on, skip over it
				y = y + dir * 5;
			else
			{ // hit left-hand edge of alignment marker, handle special case
				x = x - 1;
				for (j = 0; j < 5; j++)
				{
					if (y != 6)
					{ //skip over horitzonal timing line
						if (i % 8 == 0)
						{
							working_byte = interleaved_output[++interleaved_index];
						}
						else
						{
							working_byte = working_byte << 1;
						}
						if ((working_byte & 128) > 0)
							image[y][x] = 0;
						if (is_mask_applicable(y, x, mask_number))
							image[y][x] = ~image[y][x];
						i++;
					}
					y = y + dir;
				}
				x = x + 1;
			}
		}
		if (i < primary_bits)
		{
			if (i % 8 == 0)
			{
				working_byte = interleaved_output[++interleaved_index];
			}
			else
			{
				working_byte = working_byte << 1;
			}
			if ((working_byte & 128) > 0)
				image[y][x] = 0;
		}
		if (is_mask_applicable(y, x, mask_number))
			image[y][x] = ~image[y][x]; // handle masking for primary or remainder bit
		i++;
		x = x - 1;
		if (i < primary_bits)
		{
			if (i % 8 == 0)
			{
				working_byte = interleaved_output[++interleaved_index];
			}
			else
			{
				working_byte = working_byte << 1;
			}
			if ((working_byte & 128) > 0)
				image[y][x] = 0;
		}
		if (is_mask_applicable(y, x, mask_number))
			image[y][x] = ~image[y][x];
		y = y + dir;
		x = x + 1;
		if (((x < 9) && (y == 8)) || ((x > max_pixels - 8) && (y == 8)) || (y < 0))
		{ // hit top-left or top-right finder patterns
			dir = +1;
			y = y + 1;
			x = x - 2;
		}
		else if ((qr_version > 5) && (x == max_pixels - 9) && (y == 6))
		{		 //skip over top 3x6 version info block for large QR Version>=7
			i++; //because of the position of this in if/then rats nest, need to advance bit count, since i wasn't inc'ed yet after the second write
			dir = +1;
			y = 0;
			x = x - 3;
			for (j = 0; j < 6; j++)
			{
				if (i % 8 == 0)
				{
					working_byte = interleaved_output[++interleaved_index];
				}
				else
				{
					working_byte = working_byte << 1;
				}
				if ((working_byte & 128) > 0)
					image[y][x] = 0;
				if (is_mask_applicable(y, x, mask_number))
					image[y][x] = ~image[y][x];
				i++;
				y = y + dir;
			}
			i--; //because of the position of this in if/then rats nest, need to take back an i, since i gets inc'ed by the overall for loop at the end
				 // i tried moving the block around, but ran into a segfault, and didn't have time to investigate too closely
			x = x + 1;
		}
		else if ((x == 10) && (y == max_pixels))
		{ //hit bottom row around "dark module"
			dir = -1;
			y = max_pixels - 9;
			x = x - 2;
		}
		else if (y == max_pixels)
		{ // hit bottom row
			dir = -1;
			y = max_pixels - 1;
			x = x - 2;
		}
		else if ((x < 10) && (y > max_pixels - 9))
		{ //hit bottom-left finder pattern (near dark module)
			dir = -1;
			y = max_pixels - 9;
			x = x - 2;
		}
		else if ((qr_version > 5) && (x < 7) && (y > max_pixels - 12))
		{ //skip over bottom 6x3 version info block for large QR Version>=7
			dir = -1;
			y = max_pixels - 12;
			x = x - 2;
		}
		if (y == 6) //skip vertical timing lines
			y += dir;
		else if (x == 6) //skip horizontal timing line
			x = x - 1;
	}
	if (qr_version < 3)
	{
		for (i = 0; i < max_pixels; i++)
		{
			for (j = 0; j < max_pixels; j++)
			{
				if (image[i][j] == 0)
				{
					x0 = 64 - max_pixels + 2 * j;
					y0 = 32 - max_pixels + 2 * i;
					Bdisp_SetPoint_VRAM(x0, y0, 1);
					Bdisp_SetPoint_VRAM(x0 + 1, y0, 1);
					Bdisp_SetPoint_VRAM(x0, y0 + 1, 1);
					Bdisp_SetPoint_VRAM(x0 + 1, y0 + 1, 1);
					//Bdisp_SetPoint_VRAM(2*j,2*i,1);
					//Bdisp_SetPoint_VRAM(2*j+1,2*i,1);
					//Bdisp_SetPoint_VRAM(2*j,2*i+1,1);
					//Bdisp_SetPoint_VRAM(2*j+1,2*i+1,1);
				}
			}
		}
	}
	else
	{
		x0 = 64 - .5 * max_pixels;
		y0 = 32 - .5 * max_pixels;
		for (i = 0; i < max_pixels; i++)
		{
			for (j = 0; j < max_pixels; j++)
			{
				if (image[i][j] == 0)
				{
					Bdisp_SetPoint_VRAM(x0 + j, y0 + i, 1);
				}
			}
		}
	}
	for (i = 0; i < 64; i++)
	{
		free(image[i]);
	}
}


// Show the CSV in QR
// By Myth
int QRShowCSV(int col_amount, int *col, int max_row)
{
	char *str = (char *)malloc(sizeof(char) * (col_amount * max_row * 14 + 1));

	int i;
    for (i = 1; i <= max_row; i++)
    {
        // use \n to end a CSV line
        char *line = GenerateCSVLine(col_amount, col, i, LINE_END_TYPE_1);

        strcat(str, line);

		free(line);
    }

	parseMessage(str, 0);

	free(str);

	return 1;
}




#ifdef __cplusplus
}
#endif