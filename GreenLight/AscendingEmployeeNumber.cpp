#include "AscendingEmployeeNumber.h"

vector<EmployeeInfo> AscendingEmployeeNumber::Sort(const vector<EmployeeInfo>& info)
{
	priority_queue<EmployeeInfo, vector<EmployeeInfo>, less<EmployeeInfo>> pq;
	vector<EmployeeInfo> result;

	for (auto iter : info)
	{
		pq.push(iter);
	}

	int pqSize = pq.size();

	for (auto iter = 0; iter < pqSize; ++iter)
	{
		result.push_back(pq.top()); pq.pop();
	}

	return result;
}