#pragma once
#include "MemAlloc.h"
#include <iostream>
class IntegerPartition
{
public:
	enum Type {
		k1,//��n����Ϊ����������֮�͵Ļ����� (���ֵĶ������������ͬ)
		k2,//��n����Ϊ����������֮�͵Ļ����� (���ֵ����������벻ͬ)
		k3,//��n����Ϊk�������Ļ�����
		k4//��n����Ϊ����������֮�͵Ļ�����
	}type;
	IntegerPartition(int i, Type type);
	~IntegerPartition();
	int PartitionK1(int i);
	int PartitionK2(int i);
	int PartitionK3(int i);
	int PartitionK4(int i);
private:
	int Partition(int i, int k);
};
