// ReadNumberInEng.cpp : read given numbers in English text
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

static const long long RANGE_BILLION = 1000000000;

static const string table_units[] = { "billions", "millions", "thousands", "" };
static const string table_units_one[] = { "billion", "million", "thousand", "" };

static const string table_single_digits[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
static const string table_ten_to_twenty[] = { "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
static const string table_second_digits[] = { "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };

string print_number_lessthan_thousand(int number_lessthan_thousand)
{
	string result = "";
	string str_hundreds = "";
	string str_tens = "";

	if (number_lessthan_thousand >= 1000)
		return result;

	int hundreds = number_lessthan_thousand / 100;
	if (hundreds > 0)
	{
		str_hundreds = table_single_digits[hundreds - 1];
		result = str_hundreds + " " + (hundreds == 1 ? "hundred" : "hundreds");
	}

	int tens = number_lessthan_thousand % 100;
	if (tens == 0)
		return result;

	if (tens < 10)
	{
		str_tens = table_single_digits[tens - 1];
	}
	else if (tens < 20) // >= 11
	{
		str_tens = table_ten_to_twenty[tens - 11];
	}
	else // >= 21
	{
		int second_digit = tens / 10;
		int digit = tens % 10;
		str_tens = table_second_digits[second_digit - 2] + " " + table_single_digits[digit - 1];
	}

	if (hundreds > 0)
		result += " ";
	result += str_tens;

	return result;
}

int main()
{
	long long input = 0;
	long long max_range = RANGE_BILLION; // billion

	cout << "Please input numbers to read (max is" << max_range * 1000 - 1 << ")\n";
	cin >> input;
	if (cin.fail())
	{
		cout << "Error happens\n";
		return 0;
	}

	if (input >= max_range * 1000)
	{
		cout << "It's too big number. Sorry we can't handle it\n";
		return 0;
	}

	string result;
	int idx_unit = 0;
	long long source = input;

	while (max_range > 0)
	{
		int div = (int)(source / max_range);
		if (div > 0)
		{
			result += print_number_lessthan_thousand(div);
			result += " ";
			result += div == 1 ? table_units_one[idx_unit] : table_units[idx_unit];
			result += " ";
		}
		source = source % max_range;
		max_range = max_range / 1000;
		idx_unit++;
	}

	cout << result << "\n";

	return 0;
}

