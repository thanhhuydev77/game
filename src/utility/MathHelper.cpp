#include "MathHelper.h"

int MathHelper::getsign(float x)
{
	if (x >= 0)
		return 1;
	else
		return -1;
}

bool MathHelper::isvectorhaselement(vector<int> v, int element)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (element == v[i])
			return true;
	}
	return false;
}
