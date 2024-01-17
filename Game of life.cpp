#include <iostream>

using namespace std;

constexpr size_t MAX_ROWS = 24;
constexpr size_t MAX_COLS = 80;

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

unsigned myStrlen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str) //is the same as (*str) != '\0'
	{
		result++;
		str++;
	}
	return result;
}

int convertCharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return -1;
}

unsigned convertStrToUnsigned(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		int digit = convertCharToDigit(*str);
		if (digit == -1)
			return 0;
		(result *= 10) += digit;
		str++;
	}
	return result;
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

	cout << endl << endl;
}

void printOptionsInGame()
{
	constexpr unsigned lineLength = 65;
	const char lineSymbol = '-';

	cout << endl << endl;
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

void printGameBoard(bool** arr, const unsigned n, const unsigned m)
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

int inputNatural(const unsigned maxInput)
{
	const unsigned MAX_SIZE = 100;
	char input[MAX_SIZE];

	cin.getline(input, MAX_SIZE);
	unsigned len = myStrlen(input);
	if (len > countDigits(maxInput)) 
		return -1;

	unsigned uInput = convertStrToUnsigned(input);
	if (uInput == 0 || maxInput < uInput) return -1;

	return uInput;
}

void fillArray(bool* arr, const size_t size, bool value)
{
	for (unsigned i = 0;i < size;i++)
		arr[i] = value;
}

bool** createEmptyBoard(const size_t rows, const size_t cols)
{
	bool** board = new bool* [rows];
	for (unsigned i = 0;i < rows;i++)
	{
		board[i] = new bool[cols];
		fillArray(board[i], cols, false);
	}
	return board;
}

void deleteBoard(bool** board, const size_t rows)
{
	for (int i = 0;i < rows;i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

void copyRow(bool* rowTo, const size_t sizeTo, bool* rowFrom, const size_t sizeFrom, unsigned fromPosition)
{
	if (fromPosition + sizeFrom > sizeTo) return;

	for (int i = 0;i < sizeFrom;i++)
	{
		rowTo[fromPosition + i] = rowFrom[i];
	}
}

bool expandBoard(bool**& board, size_t& rows, size_t& cols, const size_t addRowsBeg, const size_t addRowsEnd, const size_t addColsBeg, const size_t addColsEnd)
{
	if (rows + addRowsBeg + addRowsEnd > MAX_ROWS || cols + addColsBeg + addColsEnd > MAX_COLS) return false;

	bool** newBoard = createEmptyBoard(rows + addRowsBeg + addRowsEnd, cols + addColsBeg + addColsEnd);

	for (unsigned i = 0;i < rows;i++)
	{
		copyRow(newBoard[addRowsBeg + i], cols + addColsBeg + addColsEnd, board[i], cols, addColsBeg);
	}

	deleteBoard(board, rows);

	board = newBoard;
	rows = rows + addRowsBeg + addRowsEnd;
	cols = cols + addColsBeg + addColsEnd;

	return true;
}

bool shrinkBoard(bool**& board, size_t& rows, size_t& cols, const size_t removeRowsBeg, const size_t removeRowsEnd, const size_t removeColsBeg, const size_t removeColsEnd)
{
	if (rows - removeRowsBeg - removeRowsEnd < 2 || cols - removeColsBeg - removeColsEnd < 2) return false;

	bool** newBoard = createEmptyBoard(rows - removeRowsBeg - removeRowsEnd, cols - removeColsBeg - removeColsEnd);

	for (unsigned i = removeRowsBeg;i < rows - removeRowsEnd;i++)
	{
		
	}

	return true;
}

void toggleCell(bool** board, size_t rows, size_t cols)
{
	const int MAX_INT = 2147483647;

	int inputX = 0, inputY = 0;
	cout << "X> ";
	inputX = inputNatural(MAX_INT);
	cout << "Y> ";
	inputY = inputNatural(MAX_INT);
	cout << endl;

	inputX--;
	inputY--;

	board[inputX][inputY] = !board[inputX][inputY];

}

void runGameLoop(bool** board, size_t rows, size_t cols)
{
	while (true)
	{
		printGameBoard(board, rows, cols);

		printOptionsInGame();

		cout << endl << "> ";
		int input = inputNatural(7);
		cout << endl;

		switch (input)
		{
		case 1: break;
		case 2: break;
		case 3: toggleCell(board, rows, cols); break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: return;
			default: cout << "Invalid input\n\n\n"; break;
		}
	}
}

void newGame()
{
	size_t rows = 8, cols = 16;
	bool** board = createEmptyBoard(rows, cols);

	runGameLoop(board, rows, cols);

	deleteBoard(board, rows);
}

void start()
{
	while (true)
	{
		printStartMenu();

		cout << "> ";
		int input = inputNatural(3);
		cout << endl;

		switch (input)
		{
			case 1: newGame(); break;
			case 2:break;
			case 3:	return;
			default: cout << "Invalid input\n"; break;
		}

	}
}

int main()
{
	start();
}