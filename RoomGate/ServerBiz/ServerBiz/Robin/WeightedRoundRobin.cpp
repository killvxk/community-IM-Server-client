

#include "WeightedRoundRobin.h"

CWeightedRoundRobin::CWeightedRoundRobin()
{
	i = -1;
	j = 0;
	cw = 0;
}

CWeightedRoundRobin::~CWeightedRoundRobin()
{
	list<CScheduledServerData*>::iterator iter;

	for (iter = ServerScheduledDataList_.begin(); iter != ServerScheduledDataList_.end(); iter++)
	{
		delete *iter;
	}
}

void CWeightedRoundRobin::Add(CScheduledServerData* info)
{
	ServerScheduledDataList_.push_back(info);
}

void CWeightedRoundRobin::Sort()
{
	ServerScheduledDataList_.sort();
}

int CWeightedRoundRobin::GetMaxWeight()
{
	int weight = 0;

	list<CScheduledServerData*>::iterator iter;

	for (iter = ServerScheduledDataList_.begin(); iter != ServerScheduledDataList_.end(); iter++)
	{
		if (weight < (*iter)->GetWeight())
		{
			weight = (*iter)->GetWeight();
		}
	}

	return weight;
}

int CWeightedRoundRobin::GetWeight(int index)
{
	int i = 0;

	list<CScheduledServerData*>::iterator iter;

	for (iter = ServerScheduledDataList_.begin(); iter != ServerScheduledDataList_.end(); iter++)
	{
		if (index == i++)
		{
			return (*iter)->GetWeight();
		}
	}
}

CScheduledServerData *CWeightedRoundRobin::GetServerData(int index)
{
	int i = 0;

	list<CScheduledServerData*>::iterator iter;

	for (iter = ServerScheduledDataList_.begin(); iter != ServerScheduledDataList_.end(); iter++)
	{
		if (index == i++)
		{
			return (*iter);
		}
	}
}

CScheduledServerData *CWeightedRoundRobin::ServiceRequest()
{
	while(1) 
	{
		i = (i + 1) % ServerScheduledDataList_.size();

		if (i == 0) 
		{
			cw = cw - 1;//ȡ ������Ȩֵ�����Լ��

			if (cw <= 0) 
			{
				cw = GetMaxWeight();//��������Ȩֵ����

				if (cw == 0)
				{
					return NULL;
				}
			}
		}

		if (GetWeight(i) >= cw)
		{
			return GetServerData(i);
		}
	}
}