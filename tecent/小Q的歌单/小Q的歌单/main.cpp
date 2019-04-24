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
#include <functional>

const int MOD = ((int)1e9 + 7);

typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;


template<class T>
T **CreateArray2D(int row, int col, T initialize);
template<class T>
std::vector<T> **CreateArray2D(int row, int col);
template<class T>
T **CreateArray2D(int row, int col, std::function<T(int, int)> f);
template<class T>
T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f);
template<class T>
void DeleteArray2D(T **p);
template<class T>
T Combination_YangHuiTriangle(T **c, int m, int n);

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
	/*int sum = 0;
	for (int i = 0, size = songs.size(); i < size; i++)
	{
		//printf("song[%d] = Song(%d,%d)\n", i, songs[i].numx, songs[i].numy);
		sum += Combination(X, songs[i].numx)*Combination(Y, songs[i].numy);
	}
	printf("sum: %d\n", sum);*/

	auto init = [](int m, int n)->long long {
		if (m < n)
			return 0;
		if (n == 0)
			return 1;
		else
			return 0;
	};
	int len = X > Y ? X + 1 : Y + 1;
	long long **c = CreateArray2D<long long>(len,len,init);
	Combination_YangHuiTriangle(c, len - 1, len - 1);
	long long sum = 0;
	for (int i = 0, size = songs.size(); i < size; i++)
	{
		long long combx = c[X][songs[i].numx],comby = c[Y][songs[i].numy];
		printf("song[%d]=Song(%d,%d) combx:%lld comby:%lld sum[%d]:%lld\n", i, songs[i].numx, songs[i].numy,combx,comby,i,combx*comby);
		sum += combx * comby;
	}
	DeleteArray2D(c);
	printf("sum: %lld\n", sum % MOD);
	
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

template<class T>
T Combination_YangHuiTriangle(T **c,int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			c[i][j] %= MOD;
		}
	}
	return c[m][n];
}//���Դ���
/*auto init = [](int m, int n)->int {
		if (m < n)
			return 0;
		if (n == 0)
			return 1;
		else
			return 0;
	};

	int **c = CreateArray2D<int>(10+1, 10+1, init);
	Combination_YangHuiTriangle(c, 10, 10);
	for (int i = 0;i<11;i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//printf("C(%d,%d)=%d|", i, j, c[i][j]);
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}*/

template<class T>
T **CreateArray2D(int row, int col, T initialize)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = initialize;
	return p;
}

template<class T>
std::vector<T> **CreateArray2D(int row, int col)
{
	std::vector<T> **p = new std::vector<T>*[row];
	*p = new std::vector<T>[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = std::vector<T>();
	return p;
}

template<class T>
T **CreateArray2D(int row, int col, std::function<T(int, int)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j);
	return p;
}

template<class T>
T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j, a);
	return p;
}


template<class T>
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}