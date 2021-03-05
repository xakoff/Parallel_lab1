#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;


inline double func(double x) {
	return 6/(sqrt(x*(2-x)));
}


void simpson(int n) {

	double sum = 0;
	double a = 0.5;
	double b = 1;
	double h = (b - a) / n;

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	double *mass = new double[n];

	for (int i = 0; i < n; i++)
	{
		double at = a + i * h;
		double bt = a + (i + 1) * h;
		mass[i] = (bt - at) / 6 * (func(at) + 4 * func((bt + at) / 2) + func(bt));
	}

	for (int i = 0; i < n; i++)
	{
		sum += mass[i];
	}

	free(mass);

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	cout << "n = " << n << endl;
	cout << "sum = " << sum << endl;

	chrono::duration<double> duration = (t2 - t1);
	cout << "Duration is: " << duration.count() << " seconds" << endl;
}


int main()
{
	
	std::thread t1(simpson, 100);
	std::thread t2(simpson, 1000);
	std::thread t3(simpson, 10000);
	std::thread t4(simpson, 100000);
	std::thread t5(simpson, 1000000);
	
	chrono::high_resolution_clock::time_point time1 = chrono::high_resolution_clock::now();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	chrono::high_resolution_clock::time_point time2 = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = (time2 - time1);
	system("cls");
	cout << "Duration is: " << duration.count() << " seconds" << endl << endl << endl;

	int n = 100;

	cout << "Vectorization" << endl << endl;
	time1 = chrono::high_resolution_clock::now();
	for (int j = 1; j <= 5; j++)
	{
		simpson(n);
		cout << endl;
		n *= 10;
	}
	time2 = chrono::high_resolution_clock::now();
	duration = (time2 - time1);
	cout << "Duration is: " << duration.count() << " seconds" << endl << endl << endl;

	n = 100;

	cout << "Without vectorization" << endl << endl;
	time1 = chrono::high_resolution_clock::now();

	#pragma loop(no_vector)
	for (int j = 1; j <= 5; j++)
	{
		simpson(n);
		cout << endl;
		n *= 10;
	}
	time2 = chrono::high_resolution_clock::now();
	duration = (time2 - time1);
	cout << "Duration is: " << duration.count() << " seconds" << endl << endl << endl;

	n = 100;

	cout << "Parallel" << endl << endl;

	time1 = chrono::high_resolution_clock::now();

	#pragma loop(hint_parallel(2))
	for (int j = 1; j <= 5; j++)
	{
		simpson(n);
		cout << endl;
		n *= 10;
	}
	time2 = chrono::high_resolution_clock::now();
	duration = (time2 - time1);
	cout << "Duration is: " << duration.count() << " seconds" << endl << endl << endl;



	return 0;
}