#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long int fast_mod(unsigned long int a, unsigned long long int b, unsigned int mod, unsigned int n = 0)
{
	unsigned long long int temp = 1;
	if (n > 0)
	{
		if ((temp << n - 1) > b) return 1;
		a = (a * a) % mod;
	}
	n++;
	if ((b >> n - 1) & 1) return (a * fast_mod(a, b, mod, n)) % mod;
	return fast_mod(a, b, mod, n);
}

bool is_prime(unsigned long int number)
{
	const unsigned long long int SIZE = number + 2;
	bool* temp_array = new bool[SIZE]; // tablica booleanów 

	for (int i = 2; i < SIZE; i++) // zerowanie tablicy
		temp_array[i] = 0;

	for (int i = 2; i*i < SIZE; i++)
	{
		if (!temp_array[i])
		{
			for (int j = i * i; j < SIZE; j += i)
				temp_array[j] = 1;
		}
	}
	if (temp_array[number])
	{
		return false;
	}
	return true;
}

vector<unsigned int> operator+(vector<unsigned int> lhs, vector<unsigned int> rhs)
{
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}

vector<unsigned int> Fermat_Part2(unsigned int a)
{
	int y = 0;
	unsigned int x = static_cast<unsigned int>(sqrt(a));
	if (x == sqrt(a))
	{
		return  Fermat_Part2(x) + Fermat_Part2(x);
	}
	while (++x < (a + 1) / 2)
	{
		y = x * x - a;
		if (y > 0 && (static_cast<unsigned int>(sqrt(y)) == sqrt(y)))
		{
			y = static_cast<unsigned int>(sqrt(y));
			return Fermat_Part2(x + y) + Fermat_Part2(x - y);
		}
	}
	return vector<unsigned int>{ a };
}

vector<unsigned int> Fermat(unsigned int a)
{
	vector<unsigned int> result;
	result.reserve(128);
	while (!((a >> 0) & 1) && a > 7)
	{
		result.emplace_back(2);
		a >>= 1;
	}
	result = result + Fermat_Part2(a);
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

int main()
{
	unsigned int r, k, j, t, n, a, temp; 
	cin >> n;
	cin >> r;
	cin >> k;
	if (!is_prime(n))
	{
		cout << "n is not a prime number!" << endl;
		system("pause");
		return 1;
	}
	for (auto& v : Fermat(n-1))
	{
		if (fast_mod(r, (n-1)/v, n) == 1)
		{
			cout << "r is not pierwiastek pierwotny!" << endl;
			system("pause");
			return 2;
		}
	}
	a = fast_mod(r, k, n);
	cout << "Klucz pubcliczny (" << n << ", " << r << ", " << a << ")" << endl;
	cout << "Klucz prywatny (" << n << ", " << r << ", " << a << ", " << k << ")" << endl;
	cin >> j;
	cin >> t;
						//	 {         c1      }		  {				c2	   }
	cout << "Szyfrogram (" << fast_mod(r, j, n) << ", " << (t * fast_mod(a, j, n))%n << ")" << endl;
						//	({		   c2		  } * {	   	 (c1 ^ (n - 1 - k)) % n }	 ) % n	   
	cout << "Deszyfacja " << (t * fast_mod(a, j, n) * fast_mod(fast_mod(r, j, n), n-1-k, n)) % n << endl;
	return 0;
}
