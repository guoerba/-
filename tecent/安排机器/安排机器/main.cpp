#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
/*����ʱ��͵ȼ�����������֤ȡ����һ�����������Ľ⣨��Ϊʱ��������ϸ���ڵȼ���
����ʱ����Ϊ��һ�ؼ��֣���������������������Ȼ����ȥ�������͵����񣩣�Ȼ����
�˻����ϣ������й���ʱ����ڵ�������Ļ�������һ���ȼ������У�ȡ���ȼ���ӽ�����ȼ�
�ģ��Ҵ��ڵ�������ȼ��ģ��������ޣ��������Ա�֤��ɵ�����һ�������ģ�������©����
��Ϊ����ͻ���������ʱ����й�������ô�ڵȼ������л�����ʱ��һ���ǿ�����ɺ�������
�ģ������Ǳ�ʱ�����������ѡ������ģ������ڴ˲���Ҫ���ǻ����Ĺ���ʱ���ˣ��ں�������
��ʱ�䲻����������һ���ģ�Ϊ�˷�ֹ������ֵȼ������������ô�϶�Ҫѡ��ȼ��պô�
������Ļ����ˣ�����������̰�������õ��ľ���һ�������Ž��ˣ����ҵڶ���̰�Ŀ��Զ��֣�
���ᳬʱ��
--------------------- 
���ߣ�weixin_33836874 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/weixin_33836874/article/details/87040827 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�*/
struct Machine {
	int longgestWorkTime;
	int rank;
	bool isable;
	Machine():longgestWorkTime(0),rank(0){}
	Machine(int lwt,int r):longgestWorkTime(lwt),rank(r){}
};

struct Task {
	int time;
	int rank;
	Task():time(0),rank(0){}
	Task(int t,int r):time(t),rank(r){}
};
int main()
{
	int n, m;
	std::cin >> n >> m;

	std::vector<Machine>machines(n);
	std::vector<Task>tasks(m);
	for (int i = 0; i < n; i++)
	{
		int lwt, r;
		std::cin >> lwt >> r;
		machines[i] = Machine(lwt, r);
	}
	for (int i = 0; i < m; i++)
	{
		int t, r;
		std::cin >> t >> r;
		tasks[i] = Task(t, r);
	}
		
	std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)->bool {
		return a.time > b.time;
	});
	printf("size of task %d\n", tasks.size());
	for (auto i : tasks)
	{
		
	}

	
	while (1);
	return 0;
}