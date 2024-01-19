#include <iostream>
#include <cstdlib>

/*
	step forward
		-kod
		-proverka za resize
	resize
		-izpishi tekusht razmer, pitai za nov
	save
		-clear empty rows/columns
		-dobavi v faila s imena ako go nqma
		-zapishi infoto
	load file
		-fail s imena na failove, zaredi ako ima
*/

using namespace std;

constexpr size_t MAX_ROWS = 24;
constexpr size_t MAX_COLS = 80;

//ok
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
//ok
unsigned myStrlen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}
//ok
double absolute(double x)
{
	if (x < 0)return -x;
	return x;
}
//ok
int convertCharToDigit(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return -1;
}
//ok
int convertStrToUnsigned(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		int digit = convertCharToDigit(*str);
		if (digit == -1)
			return -1;
		(result *= 10) += digit;
		str++;
	}
	return result;
}

void calculateChance(double prob, int& posibility, int& all)
{
	if (prob <= 0)
	{
		posibility = 0;
		all = 1;
		return;
	}
	if (prob >= 1)
	{
		posibility = 1;
		all = 1;
		return;
	}

	const int MAX = 10000;

	posibility = 0;
	all = 1;

	while (all < MAX)
	{
		all *= 10;
		prob *= 10;
		int temp = (int)prob;
		prob -= temp;
		posibility *= 10;
		posibility += temp;
	}
}

bool nInRow(bool** board, size_t rows, size_t cols, int startX, int startY, int moveX, int moveY, bool value, unsigned count)
{
	if (startX < 0 || rows <= startX || startY < 0 || cols <= startY) return false;

	int consecCount = 0;
	while (startX >= 0 && rows > startX && startY >= 0 && cols > startY)
	{
		if (board[startX][startY] == value) consecCount++;
		else consecCount = 0;
		if (count <= consecCount) return true;

		startX += moveX;
		startY += moveY;
	}

	return false;
}
//ok
void printSymbols(const unsigned size, const char symbol)
{
	for (unsigned i = 0; i < size; i++)
		cout << symbol;
}
//ok
void printStartMenu()
{
	constexpr unsigned lineLength = 64;

	printSymbols(2, '\n');
	printSymbols(24, ' ');
	printSymbols(16, '-');
	cout << endl;
	printSymbols(24, ' ');
	cout << "| GAME OF LIFE |\n";
	printSymbols(24, ' ');
	printSymbols(16, '-');
	printSymbols(2, '\n');

	printSymbols(lineLength, '-');
	cout << endl;
	cout << "|";
	printSymbols(29, ' ');
	cout<<"MENU";
	printSymbols(29, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;


	cout << "| 1 |   New game";
	printSymbols(47, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
	cout << "| 2 |   Load file";
	printSymbols(46, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
	cout << "| 3 |   Exit";
	printSymbols(51, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;

	cout << endl << endl;
}
//ok
void printOptionsInGame()
{
	constexpr unsigned lineLength = 65;

	printSymbols(2, '\n');
	printSymbols(lineLength, '-');
	cout << "\n|";
	printSymbols(28, ' ');
	cout << "OPTIONS";
	printSymbols(28, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;

	cout << "| 1 |   Step forward";
	printSymbols(12, ' ');
	cout << "| 2 |   Resize";
	printSymbols(18, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
	cout << "| 3 |   Toggle cell";
	printSymbols(13, ' ');
	cout << "| 4 |   Clear";
	printSymbols(19, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
	cout << "| 5 |   Randomize";
	printSymbols(15, ' ');
	cout << "| 6 |   Save to file";
	printSymbols(12, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
	cout << "| 7 |   End";
	printSymbols(53, ' ');
	cout << "|\n";
	printSymbols(lineLength, '-');
	cout << endl;
}
//ok
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
//ok
void printGameBoard(bool** arr, const unsigned n, const unsigned m)
{
	cout << endl;

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

	cout << endl;
}

//maybe inputString?
//ok 
int inputNatural(const unsigned maxInput)
{
	const unsigned MAX_SIZE = 100;
	char input[MAX_SIZE];

	cin.getline(input, MAX_SIZE);

	unsigned uInput = convertStrToUnsigned(input);
	if (uInput == 0 || maxInput < uInput) return -1;

	return uInput;
}
//ok
int inputWholeNumber(const int minNumber, const int maxNumber, bool& valid)
{
	const unsigned MAX_SIZE = 100;
	char input[MAX_SIZE];

	cin.getline(input, MAX_SIZE);

	bool negative = false;
	int iInput = 0;
	if (input[0] == '-')
	{
		negative = true;
		iInput = convertStrToUnsigned(input + 1);
	}
	else iInput = convertStrToUnsigned(input);

	if (iInput == -1 || iInput < minNumber || maxNumber < iInput)
	{
		valid = false;
		return 0;
	}

	valid = true;

	if (negative) iInput = -iInput;

	return iInput;
}
//ok
double inputPositiveDouble(const double maxNumber)
{
	const unsigned MAX_SIZE = 100;
	char input[MAX_SIZE];

	cin.getline(input, MAX_SIZE);

	unsigned len = myStrlen(input);
	bool pointPassed = false;
	double res = 0;
	double multiplyer = 1;

	for (unsigned i = 0;i < len;i++)
	{
		int digit = convertCharToDigit(input[i]);
		if (digit != -1)
		{
			if (!pointPassed)
			{
				res *= 10;
				res += digit;
			}
			else
			{
				multiplyer /= 10;
				res += multiplyer * digit;
			}
		}
		else if (input[i] == '.' && !pointPassed)
		{
			pointPassed = true;
		}
		else return -1;
	}

	if (res > maxNumber) return -1;

	return res;
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

void copyRow(bool* rowTo, const size_t sizeTo, bool* rowFrom, const size_t sizeFrom, unsigned pasteFromPosition)
{
	if (pasteFromPosition + sizeFrom > sizeTo) return;

	for (int i = 0;i < sizeFrom;i++)
	{
		rowTo[pasteFromPosition + i] = rowFrom[i];
	}
}

void copyPartOfRow(bool* rowTo, const size_t toSize,bool* rowFrom,const size_t fromSize,const unsigned start,const unsigned end)
{
	if (end >= fromSize || fromSize - start - end > toSize) return;

	for (int i = 0;i < fromSize - start - end;i++)
	{
		rowTo[i] = rowFrom[i + start];
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

	for (unsigned i = 0;i < rows - removeRowsBeg - removeRowsEnd;i++)
	{
		copyPartOfRow(newBoard[i], cols - removeColsBeg - removeColsEnd, board[i + removeRowsBeg], cols, removeColsBeg, removeColsEnd);
	}

	deleteBoard(board, rows);

	board = newBoard;
	rows = rows - removeRowsBeg - removeRowsEnd;
	cols = cols - removeColsBeg - removeColsEnd;

	return true;
}

bool resizeBoard(bool**& board, size_t& rows, size_t& cols, const size_t newSizeRows, const size_t newSizeCols)
{
	if (newSizeRows > MAX_ROWS || newSizeCols > MAX_COLS || newSizeCols < 2 || newSizeRows < 2) return false;

	if (rows < newSizeRows) expandBoard(board, rows, cols, 0, newSizeRows - rows, 0, 0);
	else if (rows > newSizeRows) shrinkBoard(board, rows, cols, 0, rows - newSizeRows, 0, 0);

	if (cols < newSizeCols) expandBoard(board, rows, cols, 0, 0, 0, newSizeCols - cols);
	else if (cols > newSizeCols) shrinkBoard(board, rows, cols, 0, 0, 0, cols - newSizeCols);

	return true;
}

void setSizeBoard(bool**& board, size_t& rows, size_t& cols)
{
	const int MAX_INT = 2147483647;

	int inputX = 0, inputY = 0;
	cout << "X> ";
	inputX = inputNatural(MAX_INT);
	cout << "Y> ";
	inputY = inputNatural(MAX_INT);
	cout << endl;

	resizeBoard(board, rows, cols, inputX, inputY);
}

void toggleCell(bool** &board, size_t &rows, size_t &cols)
{
	int inputX = 0, inputY = 0;
	bool validX = false, validY = false;
	cout << "X> ";
	inputX = inputWholeNumber(rows - MAX_ROWS + 1, MAX_ROWS, validX);
	cout << "Y> ";
	inputY = inputWholeNumber(cols - MAX_COLS + 1, MAX_COLS, validY);
	cout << endl;

	if (!validX || !validY) return;

	inputX--;
	inputY--;

	if (inputX < 0)
	{
		expandBoard(board, rows, cols, -inputX, 0, 0, 0);
		inputX = 0;
	}
	else if (inputX >= rows)
		expandBoard(board, rows, cols, 0, inputX - rows + 1, 0, 0);

	if (inputY < 0)
	{
		expandBoard(board, rows, cols, 0, 0, -inputY, 0);
		inputY = 0;
	}
	else if (inputY >= cols)
		expandBoard(board, rows, cols, 0, 0, 0, inputY - cols + 1);

	board[inputX][inputY] = !board[inputX][inputY];
}

void clearBoard(bool** board, const size_t rows, const size_t cols)
{
	for (int i = 0;i < rows;i++)
	{
		fillArray(board[i], cols, false);
	}
}

void randomizeBoolArray(bool* arr, const size_t size, int prob, int one)
{
	for (unsigned i = 0;i < size;i++)
	{
		arr[i] = (rand() % one < prob);
	}
}

void randomizeBoard(bool** board, const size_t rows, const size_t cols)
{
	double probability = inputPositiveDouble(1);

	if (probability == -1) return;

	int prob = 0, one = 1;

	calculateChance(probability, prob, one);

	for (unsigned i = 0;i < rows;i++)
	{
		randomizeBoolArray(board[i], cols, prob, one);
	}
}

unsigned getAliveCountAround(bool** board, const size_t rows, const size_t cols, const unsigned i, const unsigned j)
{
	unsigned ans = 0;

	if (i > 0)
	{
		ans += board[i - 1][j];
		if (j > 0) ans += board[i - 1][j - 1];
		if (j + 1 < cols) ans += board[i - 1][j + 1];
	}

	if (j > 0) ans += board[i][j - 1];
	if (j + 1 < cols) ans += board[i][j + 1];

	if (i + 1 < rows)
	{
		ans += board[i + 1][j];
		if (j > 0) ans += board[i + 1][j - 1];
		if (j + 1 < cols) ans += board[i + 1][j + 1];
	}

	return ans;
}

void stepForwardRow(bool**& board, size_t rows, size_t cols, const unsigned row,bool** newBoard)
{
	for (unsigned j = 0;j < cols;j++)
	{
		unsigned alive = getAliveCountAround(board, rows, cols, row, j);
		if (board[row][j])
		{
			if (alive < 2 || 3 < alive) newBoard[row][j] = false;
			else newBoard[row][j] = true;
		}
		else
		{
			if (alive == 3) newBoard[row][j] = true;
			else newBoard[row][j] = false;
		}
	}
}

void stepForward(bool** &board, size_t &rows, size_t &cols)
{
	bool** newBoard = createEmptyBoard(rows, cols);
	size_t newRows = rows, newCols = cols;

	unsigned addXB = nInRow(board, rows, cols, 0, 0, 0, 1, true, 3);
	unsigned addXE = nInRow(board, rows, cols, rows - 1, 0, 0, 1, true, 3);
	unsigned addYB = nInRow(board, rows, cols, 0, 0, 1, 0, true, 3);
	unsigned addYE = nInRow(board, rows, cols, 0, cols - 1, 1, 0, true, 3);

	expandBoard(newBoard, newRows, newCols, addXB, addXE, addYB, addYE);

	expandBoard(board, rows, cols, addXB, addXE, addYB, addYE);

	for (unsigned i = 0;i < rows;i++)
	{
		stepForwardRow(board, rows, cols, i, newBoard);
	}

	deleteBoard(board, rows);

	board = newBoard;
}

void runGameLoop(bool** board, size_t rows, size_t cols)
{
	bool exit = false;
	while (!exit)
	{
		printGameBoard(board, rows, cols);

		printOptionsInGame();

		cout << endl << "> ";
		int input = inputNatural(7);
		cout << endl;

		switch (input)
		{
		case 1: stepForward(board, rows, cols); break;
		case 2: setSizeBoard(board, rows, cols); break;
		case 3: toggleCell(board, rows, cols); break;
		case 4: clearBoard(board, rows, cols); break;
		case 5: randomizeBoard(board, rows, cols); break;
		case 6: break;
		case 7: exit = true; break;
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
	srand(time(0));
	start();
}