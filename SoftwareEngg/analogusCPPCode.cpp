#include <iostream>
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

const int MAX = 10;

using namespace std;
class solution
{
	// Access specifier
public:
	// Data Members
	string userinput_obj;
	double userinputd;
	int inputlength_obj;
	vector<double> entries;

	// Member Functions()
	void exitApp()
	{
		cout << "exiting..." << endl;
		exit(0);
	}
	bool isDigit(char ch) // Basically checks whether the char requested is a numerical digit or not.
	{
		if (ch >= '0' && ch <= '9')
			return true;
		return false;
	}

	bool verifyInputAllDigits()
	{
		string str;
		int len;
		// To mark the present digits
		str = userinput_obj;
		len = inputlength_obj;
		if (len > 16)
		{
			cout << "Input range exceeded!" << endl; // Because I am using double type. (yes, I am aware that the average might overflow while being calculated anyway)
			return false;
		}

		if (str == "-." || str == ".-")
		{
			cout << "What?" << endl;
			return false;
		}

		if (str == "quit")
		{
			exitApp();
		}

		int decimalpoint = 0;
		int negativeflag = 1;
		// For every character of the string
		for (int i = 0; i < len; i++)
		{
			if (str[i] == '.')
			{
				++decimalpoint;
				cout << "\n decimal space entered.\n"
					 << endl;
				if (decimalpoint > 1 || i == 0)
				{
					cout << "Additional decimal point entered./ Decimal point entered at the start.\n";
					return false;
				}
				else
				{
					continue;
				}
			}

			if (str[i] == '-')
			{
				negativeflag = negativeflag - 2;
				cout << "\n negative space entered.\n"
					 << endl;
				if (negativeflag < -2 || i != 0)
				{
					cout << "Additional negative symbol entered./ negative \'-\' not entered at the start.\n";
					return false;
				}
				else
				{
					continue;
				}
			}

			// If the current character is a digit
			if (isDigit(str[i]))
			{
				cout << str[i] << " is a valid digit.\n"
					 << endl;
				continue;
			}
			else
			{
				cout << str[i] << " is an invalid digit. Please check.\n"
					 << endl;
				return false;
			}
		}

		cout << "All clear!\nUpdated list:\n"
			 << endl;

		userinputd = stod(userinput_obj);
		entries.push_back(userinputd);
		for (auto i = entries.begin(); i != entries.end(); ++i)
			cout << *i << " ";
		cout << endl
			 << endl;

		return true;
	}

	void average()
	{
		cout << "Average: ";
		auto n = entries.size();
		if (n != 0)
		{
			double avrge = accumulate(entries.begin(), entries.end(), 0.0) / n;
			cout << avrge << endl;
		}
	}
	void standardDeviationSampled()
	{
		cout << "Sample standard deviation: ";
		auto n = entries.size();
		double vectorsum = accumulate(entries.begin(), entries.end(), 0.0);
		double avrge = vectorsum / n;
		double sumSq = 0.0;
		for_each(begin(entries), end(entries), [&](const double d) {
			sumSq += (d - avrge) * (d - avrge);
		});

		double samstd = sqrt(sumSq / (n - 1)); //sample standard deviation = squareroot(deviations/(size-1))
		cout << samstd << endl;
	}
	void median()
	{
		cout << "Median: ";
		auto n = entries.size();
		if (n == 0)
		{
			cout << "Invalid. Empty vector." << endl;
			return;
		}
		else
		{
			n = n / 2;
			nth_element(entries.begin(), entries.begin() + n, entries.end()); // Instead of sorting, I used the nth element
			cout << entries[n] << endl										  // method used in quicksort to find the median quickly.
				 << endl;
		}
	}
	void finishedEnteringAllInputs()
	{
		cout << "Final results as follows:\n"
			 << endl;
		cout << "Average:" << endl;
		average();
		cout << "Sample standard deviation:\n"
			 << endl;
		standardDeviationSampled();
		cout << "Median:\n"
			 << endl;
		median();
	}
};

int main()
{
	solution user;
	string userinput;
	while (1)
	{
		cout << "Type your input (integers, decimals only) tip: You can press Enter ⏎ to automatically input a \'0\': \n(type \"quit\" to quit giving input)\n";
		getline(cin, userinput); // get user input from the keyboard

		if (userinput == "")
		{
			userinput = "0"; //This was done to include empty entries.
		}

		cout << "verifying input...\n";

		int inputlen = userinput.length();
		user.userinput_obj = userinput;
		user.inputlength_obj = inputlen;

		if (user.verifyInputAllDigits())
		{
			cout << "Verified ✓. Proceeding...\n\n";
			user.average();
			user.standardDeviationSampled();
			user.median();
		}
		else
			cout << "Invaild entry ✘. Re-enter input:\n";
	}

//	user.finishedEnteringAllInputs(); // Though optional as final iteration of the while loop does
									  // the same, but it seems like a good way to summarize. To use this
									  // line, just comment the line 55 and modify the while loop accordingly
	return 0;
}