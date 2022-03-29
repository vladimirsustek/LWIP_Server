/*
 * convaysanimation.c
 *
 *  Created on: Mar 18, 2022
 *      Author: z004f3nw
 */
#include "convayanimation.h"

#define MAT_SIZE 17

#if MAT_SIZE == 17
char pattern[MAT_SIZE][MAT_SIZE] =
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
};
#elif MAT_SIZE == 9
char pattern[MAT_SIZE][MAT_SIZE] =
{
	{ ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ' },
	{ '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
};
#else
char pattern[MAT_SIZE][MAT_SIZE] =
{
	{ ' ', '#', ' ' },
	{ ' ', '#', ' ' },
	{ ' ', '#', ' ' }
};
#endif



char next[MAT_SIZE][MAT_SIZE] = {0};

void PrintMatrix(char *pMat, int max, int may, uint16_t COLOR)
{
	for (int idy = 0; idy < may; idy++)
	{
		for (int idx = 0; idx < max; idx++)
		{
			char c =  (char)*((pMat + (idy*max + idx)));
			if (c == '#')
			{
				fillRect((idx)*3 + 140, (idy)*3 + 220, 3, 3, COLOR);
			}
		}

	}


}

void Check8Ways(char * const pCurr, char * pNext, int max, int may)
{
	for (int idy = 0; idy < may; idy++)
	{
		for (int idx = 0; idx < max; idx++)
		{
			int neighbours = 0;

			/* Assigning address and content of auxiliary pointer*/
			char *pNextAux = pNext + idy*max + idx;
			*pNextAux = *(pCurr + idy*max + idx);

			/* Check the all 8 adjacent cells (if possible) and count neighbours */
			if (idx > 0 && idy > 0 && '#' == *(pCurr + (idy - 1)*max + idx - 1)) neighbours++; // (-1, -1)
			if (idy > 0 && '#' == *(pCurr + (idy - 1)*max + idx + 0)) neighbours++; // ( 0, -1)
			if (idy > 0 && idx < (max-1) && '#' == *(pCurr + (idy - 1)*max + idx + 1)) neighbours++; // ( 1, -1)
			if (idx < (max-1) && '#' == *(pCurr + (idy)*max + idx + 1)) neighbours++; // (1, 0)
			if (idx < (max-1) && idy < may && '#' == *(pCurr + (idy + 1)*max + idx + 1)) neighbours++; // (1, 1)
			if (idy < (may-1) && '#' == *(pCurr + (idy + 1)*max + idx + 0)) neighbours++; // (0, 1)
			if (idx > 0 && idy < (may-1) && '#' == *(pCurr + (idy + 1)*max + idx -1)) neighbours++; // (0, 1)
			if (idx > 0 && '#' == *(pCurr + (idy)*max + idx - 1)) neighbours++; // (-1, 0)

			char current_char = *(pCurr + (idy*max + idx));

			/*
			* Upon the neighbours decide whether the cell:
			* survives (2 >= neighbours >= 3),
			* dies  (2 < neighbours > 3)
			* revives ( 3 = neighbours)
			*/
			switch (neighbours)
			{
			case 2: *pNextAux = (current_char == '#') ? '#' : ' ';
			break;
			case 3: *pNextAux = '#';
			break;
			default: *pNextAux = ' ';
			break;
			}
		}
	}
}


int animation(fn_t fn, uint32_t generations) {


	char pPrevMat[MAT_SIZE*MAT_SIZE] = { 0 };
	char pNextMat[MAT_SIZE*MAT_SIZE] = { 0 };

	memcpy(pPrevMat, pattern, MAT_SIZE*MAT_SIZE);
	PrintMatrix(pPrevMat, MAT_SIZE, MAT_SIZE, WHITE);

	while(generations)
	{
		Check8Ways(pPrevMat, pNextMat, MAT_SIZE, MAT_SIZE);
		PrintMatrix(pPrevMat, MAT_SIZE, MAT_SIZE, BLACK);
		memcpy(pPrevMat, pNextMat, MAT_SIZE*MAT_SIZE);
		PrintMatrix(pPrevMat, MAT_SIZE, MAT_SIZE, WHITE);
		fn(400);
		generations--;
	}

	return 0;
}
