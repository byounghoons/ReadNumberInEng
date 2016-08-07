// ReadNumberInEng.cpp : read given numbers in English text
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

static const long long RANGE_BILLION = 1000000000;

static const string table_units[] = { "billion", "million", "thousand", "" };

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
		result = str_hundreds + " hundred";
		if (hundreds > 1)
			result += "s";
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

string print_number_in_english(long long input, long long max_range)
{
	string result = "";
	int idx_unit = 0;
	long long source = input;

	while (max_range > 0)
	{
		int div = (int)(source / max_range);
		if (div > 0)
		{
			result += print_number_lessthan_thousand(div);
			
			string unit = table_units[idx_unit];
			if (unit != "")
			{ 
				result += " " + unit;
				if (div > 1)
					result += "s";
			}
		}

		source = source % max_range;
		max_range = max_range / 1000;
		idx_unit++;

		if (div > 0 && max_range > 0)
			result += " ";
	}

	return result;
}

typedef struct 
{ 
	long long number; 
	string reading;
} NUMBER_READING;

// tests

static const NUMBER_READING test_data[] =
{
	{1, "one"},
	{15, "fifteen"},
	{1001, "one thousand one"},
	{2311116, "two millions three hundreds eleven thousands one hundred sixteen"}
};

bool run_tests(long long max_input)
{
	bool is_fail = false;

	cout << "test mode\n";
	for (int i = 0; i < sizeof(test_data) / sizeof(NUMBER_READING); i++)
	{
		string result = print_number_in_english(test_data[i].number, max_input);
		if (result.compare(test_data[i].reading) != 0)
		{
			is_fail = true;

			cout << "error:";
			cout << test_data[i].number << ",";
			cout << test_data[i].reading;
			cout << "(result:" << result;
			cout << ")\n";
		}
	}
	
	return is_fail;
}

int main(int argc, char *argv[])
{
	long long input = 0;
	long long MAX_INPUT = RANGE_BILLION; // billion

	// test mode
	if (argc > 1 && strcmp(argv[1], "test") == 0)
	{
		run_tests(MAX_INPUT);
		return 0;
	}

	cout << "Please input numbers to read (max is" << MAX_INPUT * 1000 - 1 << ")\n";
	cin >> input;
	if (cin.fail())
	{
		cout << "Error happens\n";
		return 0;
	}

	if (input >= MAX_INPUT * 1000)
	{
		cout << "It's too big number. Sorry we can't handle it\n";
		return 0;
	}

	string result = print_number_in_english(input, MAX_INPUT);
	cout << result << "\n";

	return 0;
}

