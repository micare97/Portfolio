//Given a natural number n (1 <= n <= 500000), please output the summation of all its proper divisors.
//Definition: A proper divisor of a natural number is the divisor that is strictly less than the number.
//e.g. number 20 has 5 proper divisors: 1, 2, 4, 5, 10, and the divisor summation is: 1 + 2 + 4 + 5 + 10 = 22.
//
//Input
//An integer stating the number of test cases (equal to about 200000), and that many lines follow, each containing one integer between 1 and 500000 inclusive.
//
//Output
//One integer each line: the divisor summation of the integer given respectively.

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	unsigned int n, g, sum, tmp1, tmp2;
	scanf ("%d", &n);
	while(n--)
	{
		cin >> g;
		sum=0;
		if(g==1)
		{
			printf ("0\n");
			continue;
		}
		tmp1 = 1;
		tmp2 = sqrt(g);
		while(tmp1 <= tmp2)
		{
			if(g%tmp1 == 0)
			{
				sum += tmp1;
				if (g/tmp1 != g && g/tmp1 != tmp1)
					sum += g/tmp1;
			}
			++tmp1;
		}
		printf ("%d\n", sum);
	}
	return 0;
}
