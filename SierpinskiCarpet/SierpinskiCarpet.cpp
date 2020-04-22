// SierpinskiCarpet.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdio.h>
#include <math.h>
#include <thread>
#include <vector>
#include <iostream>
//dywan
//rdzen kodu z trojkata sierpinskiego
int N = 1024;
using namespace std;
FILE* fp;
const int iYmax = 900;
/* screen ( integer) coordinate */
const int iXmax = 900;
unsigned char ImageMatrix[iXmax][iYmax][3];
char filename[] = "sierpinski.ppm";
char comment[] = "# ";/* comment should start with # */
const int MaxColorComponentValue = 255;

void zeros() //tworzenie bialego obrazu
{
	for (int i = 0;i < iYmax;i++)
	{
		for (int j = 0;j < iXmax;j++)
		{
			for (int c = 0;c < 3;c++)
			{
				ImageMatrix[j][i][c] = 0;
			}
		}
	}
}
void sierpinski(int size, int X, int Y, int depth)
{
	if (depth == 5)
	{
		return;
	}
	for (int i = Y;i < Y + size;i++)
	{
		for (int j = X;j < X + size;j++)
		{
			for (int c = 0;c < 3;c++)
			{
				ImageMatrix[j][i][c] = 255;
			}
		}
	}
	
	depth++;
	int oldSize = size;
	size = int(size / 3);

	thread tr1(sierpinski, size, X-size*2, Y+size , depth);	//lewo
	tr1.join();

	thread tr2(sierpinski, size, X + oldSize +size, Y + size, depth);	//prawo
	tr2.join();

	thread tr3(sierpinski, size, X + size, Y - size*2, depth);	//gora
	tr3.join();

	thread tr4(sierpinski, size, X + size, Y + size +oldSize, depth);	//dol
	tr4.join();

	thread tr5(sierpinski, size, X - size * 2, Y - size * 2, depth);	//lewy gorny rog
	tr5.join();

	thread tr6(sierpinski, size, X + oldSize + size, Y - size * 2, depth);	//prawy gorny rog
	tr6.join();

	thread tr7(sierpinski, size, X - size * 2 ,Y + size + oldSize, depth);	//lewy dolny rog
	tr7.join();

	thread tr8(sierpinski, size, X + oldSize + size, Y + size + oldSize, depth);	//prawy dolny rog
	tr8.join();
}
int main()
{
	/*create new file,give it a name and open it in binary mode  */
	fp = fopen(filename, "wb"); /* b -  binary mode */
	/*write ASCII header to the file*/
	fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, iXmax, iYmax, MaxColorComponentValue);
	/* compute and write image data bytes to the file*/
	zeros();
	thread firstCh(sierpinski, 300, 300, 300, 1);
	firstCh.join();

	for (int i = 0;i < iYmax;i++)
	{
		for (int j = 0;j < iXmax;j++)
		{
			fwrite(ImageMatrix[j][i], 1, 3, fp);
		}
	}
	fclose(fp);
	return 0;
}


