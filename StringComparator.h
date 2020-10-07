#pragma once
#include <string>
using namespace std;
class StringComparator
{
public:
	bool operator()(string a, string b)
	{
		if (a.length() != b.length()) {

			return a.length() > b.length();//if the digits are longer than its pretty given that the number value is also longer
		}
		for (int i = 0; i < (int) a.length(); i++)
		{
			if (a[i] > b[i])//returns true if a is greater than b
			{
				return true;
			}
			else if (a[i] < b[i])
			{
				return false;
			}
		//the program does nothing if the digits are equal. this allows us to traverse down to the next digit.
		}
		//if the two strings are equal we return false
		return false;
	}
};

