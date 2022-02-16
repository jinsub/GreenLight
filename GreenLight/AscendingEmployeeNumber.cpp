#include "AscendingEmployeeNumber.h"

vector<EmployeeInfo> AscendingEmployeeNumber::Sort(const vector<EmployeeInfo>& info)
{
	priority_queue<EmployeeInfo, vector<EmployeeInfo>, less<EmployeeInfo>> pq;
	vector<EmployeeInfo> result;

	for (auto iter : info)
	{
		pq.push(iter);
	}

	while(!pq.empty())
	{
		result.push_back(pq.top()); pq.pop();
	}
	
	return result;
}