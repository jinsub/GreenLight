#include "AscendingEmployeeNumber.h"
#include <algorithm>

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
vector<EmployeeInfo> AscendingEmployeeNumber::Sort_partial(const vector<EmployeeInfo>& info, const int max) {
	vector<EmployeeInfo> result(max);
	if (info.size() < max) {
		result.resize(info.size());
	}
	std::partial_sort_copy(info.begin(), info.end(), result.begin(), result.end(), std::greater<EmployeeInfo>());

	return result;
}