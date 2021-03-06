#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>


using namespace std;


string file_write(int n, int k)
{
	string list;
	for (int i = 1; i <= n; i++)
	{
		list = list + "Thread " + to_string(k) + ": " + to_string(k*n*i) + "\n";
		if (i >= 1000000000) break;
	}
	return list;
}


void file_read()
{
	ifstream flow;
	flow.open("thread.txt");
	if (!flow.is_open())
		cout << "Unable to open file!\n";
	else
	{
		string line;
		int i = 0;
		while (getline(flow, line) && i<1000000000)
		{
			cout << line << "\n";
			i++;
		}
	}
	flow.close();
}


int main(int argc, char** argv)
{
	int number, p = 0;
	while (p == 0)
	{
		cout << "Enter the number of threads: ";
		cin >> number;
		if (cin.fail())
		{
			cout << "Incorrect input\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else if (number<1)
		{
			cout << "Incorrect number\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else p = 1;
	}
	ofstream flow;
	flow.open("thread.txt");
	thread *th = new thread[number];
	for (int k = 1; k <= number; k++)
	{
		th[k - 1] = thread([&flow, number, k]
		{
			flow << file_write(number, k);
		});
	}
	for (int k = 1; k <= number; k++)
	{
		th[k-1].join();
	}
	flow.close();
	file_read();
	system("pause");
	return 0;
}