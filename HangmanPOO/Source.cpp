#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;


class Hangman {
protected:
	string incercari;
	string cuvant;
	string incercarimax;
	bool castig;
	string ghicite;
public: 
	Hangman() {
		ifstream reader("cuvinte.txt");
		reader >> incercarimax;
		vector<string> v;
		if (reader.is_open())
		{
			while (getline(reader, cuvant))
				v.push_back(cuvant);

			int randomLine = rand() % v.size();

			this->cuvant = v.at(randomLine);
		}
		this->castig = false;
		this->incercari = incercarimax;
	}
	void Play() {
		do {
			system("cls");
			Print("HangMan");
			LitereDisponibile(ghicite);
			Print("Numar de incercari");
			Print(incercari, false, false);
			Print("Ghiceste cuvantul");
			castig = CuvantVWin(cuvant, ghicite);
			if (castig)
				break;
			char c;
			cout << ">";
			cin >> c;

			if (ghicite.find(c) == string::npos)
			{
				ghicite += c;
				incercari = incercariRamase(cuvant, ghicite, incercarimax);
			}
		} while (stoi(incercari) >0);
		if (castig)
			Print("Ai castigat!");
		else
			Print("Ai pierdut!");
	}
	void Print(string mesaj, bool sus = true, bool jos = true)
	{
		if (sus)
		{
			cout << "+---------------------------------+" << endl;
			cout << "|";
		}
		else
		{
			cout << "|";
		}
		bool front = true;
		for (int i = mesaj.length(); i < 33; i++)
		{
			if (front)
			{
				mesaj = " " + mesaj;
			}
			else
			{
				mesaj = mesaj + " ";
			}
			front = !front;
		}
		cout << mesaj.c_str();

		if (jos)
		{
			cout << "|" << endl;
			cout << "+---------------------------------+" << endl;
		}
		else
		{
			cout << "|" << endl;
		}
	}

	void litere(string input, char from, char to)
	{
		string s;
		for (char i = from; i <= to; i++)
		{
			if (input.find(i) == string::npos)
			{
				s += i;
				s += " ";
			}
			else
				s += "  ";
		}
		Print(s, false, false);
	}
	void LitereDisponibile(string taken)
	{
		Print("Litere Disponibile");
		litere(taken, 'a', 'm');
		litere(taken, 'n', 'z');
	}
	bool CuvantVWin(string cuvant, string ghicite)
	{
		bool castig = true;
		string s;
		for (int i = 0; i < cuvant.length(); i++)
		{
			if (ghicite.find(cuvant[i]) == string::npos)
			{
				castig = false;
				s += "_ ";
			}
			else
			{
				s += cuvant[i];
				s += " ";
			}
		}
		Print(s, false);
		return castig;
	}
	string incercariRamase(string cuvant, string ghicite,string incercari)
	{
		int error = stoi(incercari);
		for (int i = 0; i < ghicite.length(); i++)
		{
			if (cuvant.find(ghicite[i]) == string::npos)
				error--;
		}
		return to_string(error);
		
	}
};

int main() {
	Hangman joc;
	joc.Play();
	system("Pause");
	return 0;
}