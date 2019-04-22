/*СQ��X�׳���ΪA�Ĳ�ͬ�ĸ��Y�׳���ΪB�Ĳ�ͬ�ĸ裬����СQ������Щ�����һ���ܳ�������ΪK�ĸ赥��
ÿ�׸����ֻ���ڸ赥�г���һ�Σ��ڲ����Ǹ赥�ڸ������Ⱥ�˳�������£������ж�������ɸ赥�ķ����� 

��������:
ÿ���������һ������������
ÿ�����������ĵ�һ�а���һ����������ʾ�赥���ܳ���K(1<=K<=1000)��
��������һ�а����ĸ����������ֱ��ʾ��ĵ�һ�ֳ���A(A<=10)������X(X<=100)�Լ���ĵڶ��ֳ���B(B<=10)������Y(Y<=100)��
��֤A������B��

�������:
���һ������,��ʾ��ɸ赥�ķ���ȡģ����Ϊ�𰸿��ܻ�ܴ�,�����1000000007ȡģ�Ľ����
��������1:
5
2 3 3 3

�������1:
9*/

#include <iostream>
#include <vector>
#include <stdio.h>

struct Song {
	int numx;
	int numy;
	Song() :numx(0), numy(0) {}
	Song(int nx, int ny) :numx(nx), numy(ny) {}
};

int Permutation(int m, int n);//A(m,n)
int Factorial(int n);//n!
int Combination(int m, int n);//C(m.n)

std::vector<Song> FindCombination(int x, int y, int a, int b, int k)
{
	std::vector<Song>songnum;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
			//printf("%d * %d + %d * %d = %d\n", a, i, b, j, a*i + b * j);
			if (a * i + b * j == k)
				songnum.push_back(Song(i, j));
		}
	}
	return songnum;
}

int main()
{
	int K, A, X, B, Y;
	std::cin >> K;
	std::cin >> A >> X >> B >> Y;//����ΪA�ĸ�����X�ף�����ΪB�ĸ�����Y��

	std::vector<Song> songs = FindCombination(X, Y, A, B, K);
	int sum = 0;
	for (int i = 0, size = songs.size(); i < size; i++)
	{
		//printf("song[%d] = Song(%d,%d)\n", i, songs[i].numx, songs[i].numy);
		sum += Combination(X, songs[i].numx)*Combination(Y, songs[i].numy);
	}
	printf("sum: %d\n", sum);

	//std::cout << Permutation(5, 2) << std::endl;
	//std::cout << Factorial(3) << std::endl;
	//std::cout << Combination(5, 2) << std::endl;
	while (1);
}

int Permutation(int m,int n)//A(m,n)
{
	int end = m - n + 1;
	int p = 1;
	for (int i = m; i >= end; i--)
		p *= i;
	return p;
}

int Factorial(int n)//n!
{
	if (n == 0)
		return 1;
	int f = 1;
	for (int i = 1; i <= n; i++)
		f *= i;
	return f;
}
int Combination(int m, int n)//C(m.n)
{
	return Permutation(m, n) / Factorial(n);
}