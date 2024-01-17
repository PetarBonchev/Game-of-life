#include <iostream>

using namespace std;

constexpr size_t MAX_ROWS = 80;
constexpr size_t MAX_COLS = 24;

unsigned countDigits(int x)
{
	if (x == 0) return 1;

	unsigned ans = 0;
	while (x)
	{
		ans++;
		x /= 10;
	}

	return ans;
}

void printSymbols(const unsigned size, const char symbol)
{
	for (unsigned i = 0; i < size; i++)
		cout << symbol;
}

void printStartMenu()
{
	constexpr unsigned lineLength = 65;
	const char lineSymbol = '-';

	cout << endl << endl;
	cout << "\t\t\t";
	printSymbols(16, lineSymbol);
	cout << endl;
	cout << "\t\t\t| GAME OF LIFE |\n";
	cout << "\t\t\t";
	printSymbols(16, lineSymbol);
	cout << endl;
	cout << endl;

	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "|\t\t\t   MAIN MENU\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;


	cout << "| 1 |   New game\t\t\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "| 2 |   Load file\t\t\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "| 3 |   Exit\t\t\t\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
}

void printOptionsInGame()
{
	constexpr unsigned lineLength = 65;
	const char lineSymbol = '-';

	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "|\t\t\t     OPTIONS\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;

	cout << "| 1 |   Step forward\t\t";
	cout << "| 2 |   Resize\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "| 3 |   Toggle cell\t\t";
	cout << "| 4 |   Clear\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "| 5 |   Randomize\t\t";
	cout << "| 6 |   Save to file\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
	cout << "| 7 |   End\t\t\t\t\t\t\t|\n";
	printSymbols(lineLength, lineSymbol);
	cout << endl;
}

void printGameRow(const bool* row, const unsigned n)
{
	const char aliveSymbol = '@';
	const char deadSymbol = '-';

	for (unsigned i = 0; i < n; i++)
	{
		if (row[i]) cout << aliveSymbol;
		else cout << deadSymbol;
	}
	cout << endl;
}

void printGameBoard(const bool arr[MAX_ROWS][MAX_COLS], const unsigned n, const unsigned m)
{
	unsigned offsetX = countDigits(n);

	printSymbols(offsetX + 1, ' ');
	cout << 1;
	printSymbols(m - 2, ' ');
	cout << m << endl;

	for (unsigned i = 0; i < n; i++)
	{
		if (i == 0) { printSymbols(offsetX - 1, ' ');cout << "1 "; }
		else if (i == n - 1) { cout << n << " "; }
		else printSymbols(offsetX + 1, ' ');
		printGameRow(arr[i], m);
	}
}

int main()
{
	bool arr[5][24] = { { 1},{0,0,0,0,1},{0,1} };

	printGameBoard(arr, 12, 7);
}