#include <cstdio>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

const int size = 257;
const double dx = 1 / 32.;
const double dy = 1 / 32.;
const double eps = pow(10, -9);
double FI[size][size];
int iter = 0;

void inicjalizacja()
{
	int i = 0;
	int j = 0;
	for(double x=-4; x<=4; x+=dx)
	{
		j = 0;
		for(double y=-4; y<=4; y+=dy)
		{
			if(x == -4 || x == 4 || y == -4 || y == 4)
				FI[i][j] = pow(x, 2) - pow(y, 2);
			else
				FI[i][j] = 0;
			++j;
		}
		++i;
	}
	iter = 0;
}

void setFI(const int k)
{
	for(int i=k; i<size-k; i+=k)
	{
		for(int j=k; j<size-k; j+=k)
			FI[i][j] = (FI[i+k][j] + FI[i-k][j] + FI[i][j+k] + FI[i][j-k]) / 4.; 
	}
}

double calka(const int k)
{
	double suma = 0;
	for(int i=0; i<size-k; i+=k)
	{
		for(int j=0; j<size-k; j+=k) 
			suma += pow(FI[i+k][j] + FI[i+k][j+k] - FI[i][j] - FI[i][j+k], 2) + pow(FI[i][j+k] + FI[i+k][j+k] - FI[i][j] - FI[i+k][j], 2);
	}
	return suma /= 8.;
}

void metoda(const int k, const string &filename)
{
	string f1 = filename;

	ofstream myfile;
	myfile.open(string((f1+"_calka.txt").c_str()).c_str());

	double a1;
	double a2;
	do
	{
		a1 = a2 = calka(k);
		setFI(k);
		iter++;
		a2 = calka(k);
		myfile << iter << " " << a2 << "\n";
	} while(fabs(a1 - a2) > eps);
	myfile.close();
	string f2 = filename;
	myfile.open(string((f2+"_potencjal.txt").c_str()).c_str());
	for(int i=0; i<size; i+=k)
	{
		for(int j=0; j<size; j+=k)
			myfile << -4 + (i * 8) / 256 << " " << -4 + (j * 8) / 256. << " " << FI[i][j] << "\n";
		myfile << "\n";
	}
	myfile.close();	
}
tu dodaje jakas funkcjonalnosc
i zmienam licz na licznik
void licznik(const int k)
{
	const int k_tmp = k / 2;
	for(int i=k_tmp; i<size-k_tmp; i+=k_tmp)
	{
		for(int j=k_tmp; j<size-k_tmp; j+=k_tmp)
		{
			if(j % k)
			{
				if(i % k)
					FI[i][j] = (FI[i+k_tmp][j+k_tmp] + FI[i-k_tmp][j-k_tmp] + FI[i-k_tmp][j+k_tmp] + FI[i+k_tmp][j-k_tmp]) / 4.; 
				else
					FI[i][j] = (FI[i][j+k_tmp] + FI[i][j-k_tmp]) / 2.;
			}
			else if(i % k)
				FI[i][j] = (FI[i+k_tmp][j] + FI[i-k_tmp][j]) / 2.;
		}
	}
}

int main(void)
{
	inicjalizacja();
	metoda(1, "zad1");
	inicjalizacja();
	for(int k=32; k>=1; k/=2)
	{
		stringstream zad; 
		zad << "zad2_" << k;
		metoda(k, zad.str());
		if(k > 1)
			licz(k);
	}
	return 0;
}