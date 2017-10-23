//Opis na dole
#include <iostream>
#include <vector>

using namespace std;
struct pokoj
{
	int wiersz, ID;
	int xMax,
		xMin;
};
int main()
{
	int n;
	scanf("%d", &n);
	while(n--)
	{
		int M, N, iHumans, iRooms, rol[120] = {0};
		char m[120][120];
		double avrg;
		vector<pokoj> pokoje;
		pokoj tmp_pokoj;
		iRooms = 0;
		iHumans = 0;
		scanf("%d", &M);
		scanf("%d", &N);
		for(int i = 0; i < M; i++)			//CZYTA MAPE
		{
			for(int j = 0; j < N; j++)
			{
				//scanf("%c", &m[j][i]);
				scanf(" %c",&m[j][i]);
			}
		}
		int i = 0, j = 0, g;
		for(int l = 1; l < M-1; l++)
		{
			for(int k = 1; k < N-1; k++)	//LICZY ILOSC OSOB, USTALA ILOSC POKOJOW W WIERSZU
			{
				if (m[k][l] == '#')
					continue;
				else
				{
					tmp_pokoj.wiersz = l;
					if (m[k-1][l] == '#')
					{
						iRooms++;
						rol[l]++;
						tmp_pokoj.ID = iRooms;
						tmp_pokoj.xMin = k;
					}
			
					if (m[k][l] == '*')
						iHumans++;
						
					if (m[k+1][l] == '#')
					{
						tmp_pokoj.xMax = k;
						pokoje.push_back(tmp_pokoj);
					}					
				}
			}
			if(l-1)
			{
				g += rol[l-2];
				i += rol[l-1];
				j = i;
				for(int h = i; h<i+rol[l]; h++)
				{
					cout<<i<<endl;
					for(g = i-rol[l-1]; g<i; g++)
					{
						cout<<g<<" : "<<h<<endl;
						cout<<pokoje[g].xMin << "<" << pokoje[h].xMax << " : " << pokoje[g].xMax << ">" << pokoje[h].xMin <<endl;
						if(pokoje[g].xMin <= pokoje[h].xMax && pokoje[g].xMax >= pokoje[h].xMin)
							//if(pokoje[g].ID!=pokoje[i].ID)
							{
								iRooms--;
								cout<<"r"<<iRooms<<endl;
								pokoje[i].ID = pokoje[g].ID;
							}
					}
				}
			}
		}
		cout<<iHumans<<" : "<<iRooms<<endl;
		avrg = (double)iHumans/(double)iRooms;
		if(iHumans==0) avrg=0;
		printf("%.2f\n", avrg);
	}
	return 0;
}

//We are given a top view of a hotel floor, which is represented by an MxN matrix of characters, composed of (only) the following:
//
//'#' is a Wall
//'-' is Free Space
//'*' is an occupied space (by a single person).
//
//We are required to evaluate the average number of people living in a room.
//
//Constraints: 
//M, N <= 100
//Number of test-cases<= 10
//All border edges of the map will be walls.
//There will be at least one room.
//
//Input
//
//The 1st line contains the number of test inputs, with each test case consisting of:
//M N
//MxN matrix of characters
//
//Output
//
//For each test case output a line with the average number of people living per room, rounded to exactly two decimal places.
//
//Example
//
//Input:
//2
//5 5
//#####
//#**##
//###*#
//#**##
//#####
//6 10
//##########
//#---*--*##
//###-*----#
//#**#######
//##***---##
//##########
//
//Output:
//1.67
//4.00
//
//*Nie dziala na spoj
