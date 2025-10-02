

#include <iostream>
#include <cmath>
#include <windows.h>


using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	float x;
	float y;
	cout << "введите X  и Y " << endl;
	cin >> x;
	cin >> y;
	if (y == 0) {
		cout << "Error";
		return 1;
	}
	double pi = 2 * acos(0.0);
	float R = cos(pi / 4 * x);
	float S = pow(exp(y), 1.0 / 8.0) * (1.0 / pow(5, y));
	cout << "C = " << max(R, S) << endl;
	cin.get();
	system ("pause");
	return 0;


	

}


