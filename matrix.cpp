#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

bool stringIsMadeOfWhiteSpaces(string line)
{
    for (char a : line)
    {
        if (a != ' ')
        {
            return false;
        }
    }
    return true;
}

//Return the index directly after the first matrix
int findOperatorIndex(string line)
{
    int borderCount = 0;
    int operatorIndex = 0;
    for (char a : line)
    {
        if (a == '|')
        {
            borderCount++;
        }
        operatorIndex++;

        if (borderCount == 2)
        {
            break;
        }
    }

    return operatorIndex;
}

int doubleLength(double num)
{
    string doubleStr = to_string(num);

    //Removes trailing 0s at the end of a double
    doubleStr.erase(doubleStr.find_last_not_of('0') + 1, string::npos);

    //Return the length of the double and removes on if the last symbol is a '.' since it's not a number
    if (doubleStr.back() == '.')
    {
        return doubleStr.size() - 1;
    }
    return doubleStr.size();
}

string convertDoubleToString(double num)
{
    string doubleStr = to_string(num);

    //Removes trailing 0s at the end of a double
    doubleStr.erase(doubleStr.find_last_not_of('0') + 1, string::npos);

    //Removes the . if there are no numbers after it
    if (doubleStr.back() == '.')
    {
        doubleStr.pop_back();
    }
    return doubleStr;
}

int colCount(string row)
{
    //Removes the empty space before a row
    row = row.substr(row.find_first_not_of(" "));

    //Keeps track of the count of numbers in the row
    int count = 0;

    //Cycles trough two for cycles
    //The first one keeps track of the starting index of a number and the second one the last index of a number
    for (int i = 0; i < row.size(); i++)
    {
        //Starts tracking index
        if (row[i] != ' ')
        {
            int j;

            //Increases j until the next space (end of the number)
            for (j = i; row[j] != ' ' && j < row.size(); j++);
            count++;

            //Increases the starting index to the last index of the last word + 1
            i = j;
        }
    }

    return count;
}

void parseString(string row, double array[], int rows, int cols)
{
    //Removes the empty space before a row
    row = row.substr(row.find_first_not_of(" "));

    //Keeps track of the index of the number that would be added next
    int currentNumIndex = 0;

    //Cycles trough two for cycles
    //The first one keeps track of the starting index of a number and the second one the last index of a number
    for (int i = 0; i < row.size(); i++)
    {
        //Starts tracking index
        if (row[i] != ' ')
        {
            int j = i;

            //Increases j until the next space (end of the number)
            for (j; row[j] != ' ' && j < row.size(); j++);

            //Converts the string for i to j to a double and adds it to the array
            array[currentNumIndex] = stod(row.substr(i, j - i));
            currentNumIndex++;

            //Increases the starting index to the last index of the last word + 1
            i = j;
        }
    }
}

bool readFile(string lines[101], int &lineCount)
{
    cout << "Enter file name: ";

    string fileName;
    cin >> fileName;

    //Opens conncetion to file
    ifstream matrixFile(fileName);

    //Checks if file exists (connection is open)
    if (!matrixFile.is_open())
    {
        matrixFile.close();
        return false;
    }

    lineCount = 0;

    //Reads trough all the lines of the file
    while (getline(matrixFile, lines[lineCount]))
    {
        lineCount++;

        //If the file is too big stops reading the lines before the array gets filled
        if (lineCount > 100)
        {
            break;
        }
    }

    //Closes connection with file
    matrixFile.close();
    return true;
}

void displayError(string operation[], int lineCount)
{
    //Prints out the first line of the operation with an error after it
    cout << operation[0] << " = Error" << endl;

    //Prints out the rest of the operation
    for (int i = 1; i < lineCount; i++)
    {
        cout << operation[i] << endl;
    }
}

void multiplyMatrixWithNum(double **&array, int rowCount, int colCount, int operatorIndex, string operation[])
{
    string firstLine = operation[0];

    //Takes the number after the operator
    double num = stod(firstLine.substr(operatorIndex + 1));

    //Keeps track of the largest length of the numbers in each column (used to make the printed array easier to read)
    int maxLengthsPerCol[colCount];
    for (int i = 0; i < colCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    //Multiplies each member of the matrix with the given number
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int numLength = doubleLength(array[i][j] *= num);
            if (numLength > maxLengthsPerCol[j])
            {
                maxLengthsPerCol[j] = numLength;
            }
        }
    }

    //Calculates how much space the number after the operator takes
    int numberLength = firstLine.substr(operatorIndex + 1).size();

    //Cycles trough all the elements of the matrix and prints them out
    for (int i = 0; i < rowCount; i++)
    {
        cout << operation[i];

        //Adds equal sign to the first line and adequate space for the other ones
        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            //Adds empty space below the operator and number after it
            for (int j = 0; j <= numberLength; j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < colCount; j++)
        {
            //Setw insures that there will be space for each number in the printed matrix
            cout << setw(maxLengthsPerCol[j]) << array[i][j];

            //Ensures that there won't be unnecessary space at the end of the matrix
            if (j < colCount - 1)
            {
                cout << ' ';
            }
        }

        cout << '|' << endl;
    }
}

void divideMatrixByNum(double **&array, int rowCount, int colCount, int operatorIndex, string operation[])
{
    string firstLine = operation[0];

    //Takes the number after the operator
    double num = stod(firstLine.substr(operatorIndex + 1));

    //If the number to divide with is 0 prints out error
    if (num == 0)
    {
        displayError(operation, rowCount);
        return;
    }

    //Keeps track of the largest length of the numbers in each column (used to make the printed array easier to read)
    int maxLengthsPerCol[colCount];
    for (int i = 0; i < colCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    //Divides each member of the matrix with the given number
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int numLength = doubleLength(array[i][j] /= num);

            //Checks if there is the length of the current number is larger than that of the others in the column
            if (numLength > maxLengthsPerCol[j])
            {
                maxLengthsPerCol[j] = numLength;
            }
        }
    }

    //Calculates how much space the number after the operator takes
    int numberLength = firstLine.substr(operatorIndex + 1).size();

    //Cycles trough all the elements of the matrix and prints them out
    for (int i = 0; i < rowCount; i++)
    {
        cout << operation[i];

        //Adds equal sign to the first line and adequate space for the other ones
        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            //Adds empty space below the operator and number after it
            for (int j = 0; j <= numberLength; j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < colCount; j++)
        {
            //Setw insures that there will be space for each number in the printed matrix
            //The method ensures that the number won't be longer than expected
            cout << setw(maxLengthsPerCol[j]) << convertDoubleToString(array[i][j]);

            //Ensures that there won't be unnecessary space at the end of the matrix
            if (j < colCount - 1)
            {
                cout << ' ';
            }
        }

        cout << '|' << endl;
    }
}

void transposeMatrix(double **&array, int rowCount, int colCount, string operation[])
{
    //Keeps track of the largest length of the numbers in each column (used to make the printed array easier to read)
    int maxLengthsPerCol[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    //Calculates what the max length for every column should be
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int numLength = doubleLength(array[i][j]);
            if (maxLengthsPerCol[i] < numLength)
            {
                maxLengthsPerCol[i] = numLength;
            }
        }
    }

    //Prints out the matrix in a transposed oreder
    for (int i = 0; i < colCount; i++)
    {
        //Ensures that if the transposed matrix has more rows than the original one it would be printed correctly
        if (i > rowCount - 1)
        {
            for (int j = 0; j < operation[0].size() - 1; j++)
            {
                cout << ' ';
            }
        }

        cout << operation[i];

        //Prints equal sign on the first row and spaces between the original matrix and the result after that
        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            //Prints the same amount of spaces that the operator takes up
            for (int j = 0; j < operation[0].size() - operation[1].size(); j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < rowCount; j++)
        {
            //Setw insures that there will be space for each number in the printed matrix
            //Prints out the matrix in a transposed order
            cout << setw(maxLengthsPerCol[j]) << convertDoubleToString(array[j][i]);
            if (j < rowCount - 1)
            {
                cout << ' ';
            }
        }

        cout << '|' << endl;
    }

    //If the original matrix has more rows than the transposed one they get printed
    if (rowCount > colCount)
    {
        for (int i = colCount; i < rowCount; i++)
        {
            cout << operation[i] << endl;
        }
    }
}

void calculateAjungated(double **&array, int rowCount, int row, int column, double **&result)
{
    //Keep track of what the index of the next member of the adjungated matrix should be
    int tempColIndex = 0;
    int tempRowIndex = 0;

    //Cycles trough all the elements of the original matrix and adds them to the new adjungated one
    for (int j = 0; j < rowCount; j++)
    {
        //Resets the column index on each new row
        tempColIndex = 0;

        for (int k = 0; k < rowCount; k++)
        {
            if (j != row && k != column)
            {
                result[tempRowIndex][tempColIndex] = array[j][k];
                tempColIndex++;
            }
        }

        //Makes sure that the row index isn't increased if the row was not copied
        if (j != row)
        {
            tempRowIndex++;
        }
    }
}

double determinant(double **&array, int rowCount)
{
    //Base cases for determinants which have concise formulas
    if (rowCount == 1)
    {
        return array[0][0];
    }
    if (rowCount == 2)
    {
        return array[0][0] * array[1][1] - array[0][1] * array[1][0];
    }
    if (rowCount == 3)
    {
        return array[0][0] * array[1][1] * array[2][2] + array[0][1] * array[1][2] * array[2][0] + array[0][2] * array[1][0] * array[2][1] - (array[2][0] * array[1][1] * array[0][2] + array[2][1] * array[1][2] * array[0][0] + array[2][2] * array[1][0] * array[0][1]);
    }

    //Square array for storting ajungated matrix
    int tempRowCount = rowCount - 1;
    double **tempArray;
    tempArray = new double *[tempRowCount];
    for (int i = 0; i < tempRowCount; ++i)
    {
        tempArray[i] = new double[tempRowCount];
    }

    double tempDeterminant = 0;
    int firstRowIndex = 0;

    for (int i = 0; i < rowCount; i++)
    {
        //Fills the array with the adjungated
        calculateAjungated(array, rowCount, firstRowIndex, i, tempArray);

        //Multiplies the determinant of the adjungated matrix with the member from the original matrix and adds/subtracts them
        if (i % 2 == 0)
        {
            tempDeterminant += array[firstRowIndex][i] * determinant(tempArray, tempRowCount);
        }
        else
        {
            tempDeterminant -= array[firstRowIndex][i] * determinant(tempArray, tempRowCount);
        }
    }

    //Frees memeory from the adjungated matrix
    for (int i = 0; i < tempRowCount; ++i)
    {
        delete[] tempArray[i];
    }
    delete[] tempArray;

    return tempDeterminant;
}

void calculateDeterminant(double **&array, int rowCount, int colCount, string operation[])
{
    //Checks if the matrix is square
    if (rowCount != colCount)
    {
        displayError(operation, rowCount);
        return;
    }

    //Calculates the determinant and prints out the first row with it
    cout << operation[0] << " = " << determinant(array, rowCount) << endl;

    //Prints out the rest of the rows
    for (int i = 1; i < rowCount; i++)
    {
        cout << operation[i] << endl;
    }
}

void multiplyMatrixWithMatrix(double **&array1, double **&array2, int rowCount1, int colCount1, int rowCount2, int colCount2, int lineCount, int operatorIndex, string operation[])
{
    //Checks for the requirement for multiplying matricies
    if (colCount1 != rowCount2)
    {
        displayError(operation, lineCount);
        return;
    }

    double resultArr[rowCount1][colCount2];

    //Keeps track of the largest length of the numbers in each column (used to make the printed array easier to read)
    int maxLengthsPerCol[colCount2];
    for (int i = 0; i < colCount2; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    for (int i = 0; i < rowCount1; i++)
    {
        for (int j = 0; j < colCount2; j++)
        {
            resultArr[i][j] = 0;
            for (int z = 0; z < colCount1; z++)
            {
                //Formula for calculating matrix multiplication (Multiplies each row of the first matrix with each column of the second one)
                double result = array1[i][z] * array2[z][j];
                resultArr[i][j] += result;
                int length = doubleLength(resultArr[i][j]);

                //Checks if there is the length of the current number is larger than that of the others in the column
                if (length > maxLengthsPerCol[j])
                {
                    maxLengthsPerCol[j] = length;
                }
            }
        }
    }

    for (int i = 0; i < rowCount1; i++)
    {
        cout << operation[i];
        if (i == 0)
        {
            cout << " = ";
        }
        else
        {
            cout << "   ";
        }

        //If the first matrix has more rows than the second one adds spaces so the resul matrix is cut off
        if (i > rowCount2 - 1)
        {
            int spaceCount = operation[0].size() - operation[i].size();
            for (int j = 0; j < spaceCount; j++)
            {
                cout << ' ';
            }
        }

        cout << '|';
        for (int j = 0; j < colCount2; j++)
        {
            //Setw insures that there will be space for each number in the printed matrix
            cout << setw(maxLengthsPerCol[j]) << resultArr[i][j];

            //Ensures that there won't be unnecessary space at the end of the matrix
            if (j != colCount2 - 1)
            {
                cout << " ";
            }
        }
        cout << '|' << endl;
    }
}

void addMatrixToMatrix(double **&array1, double **&array2, int rowCount1, int colCount1, int rowCount2, int colCount2, int lineCount, int operatorIndex, string operation[])
{
    //Both matrices must have the same amount of rows and columns to be added toughether
    if (colCount1 != colCount2 || rowCount1 != rowCount2)
    {
        displayError(operation, lineCount);
        return;
    }

    double resultArr[rowCount1][colCount1];

    //Keeps track of the largest length of the numbers in each column (used to make the printed array easier to read)
    int maxLengthsPerCol[colCount1];
    for (int i = 0; i < colCount1; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    //Cycles trough both arrays and calculates the sum of each pair of numbers
    for (int i = 0; i < rowCount1; i++)
    {
        for (int j = 0; j < colCount1; j++)
        {
            double result = array1[i][j] + array2[i][j];
            int resLength = doubleLength(result);

            //Checks if there is the length of the current number is larger than that of the others in the column
            if (resLength > maxLengthsPerCol[j])
            {
                maxLengthsPerCol[j] = resLength;
            }

            resultArr[i][j] = result;
        }
    }

    //Prints out the final matrix
    for (int i = 0; i < rowCount1; i++)
    {
        cout << operation[i];

        //Adds an equal sign to the first row of the result and space between the others
        if (i == 0)
        {
            cout << " = ";
        }
        else
        {
            cout << "   ";
        }

        cout << '|';
        for (int j = 0; j < colCount2; j++)
        {
            //Setw insures that there will be space for each number in the printed matrix
            cout << setw(maxLengthsPerCol[j]) << resultArr[i][j];

            //Ensures that there won't be unnecessary space at the end of the matrix
            if (j != colCount2 - 1)
            {
                cout << " ";
            }
        }
        cout << '|' << endl;
    }
}

void inverseMatrix(double **&array, int rowCount, int colCount, string operation[])
{
    //Case for non-square matrix
    if (rowCount != colCount)
    {
        displayError(operation, rowCount);
        return;
    }

    //Calculates the determinant of the original matrix for use in the calculations
    double arrDeterminant = determinant(array, rowCount);

    //If the determinant is 0 there is no inverse matrix
    if (arrDeterminant == 0)
    {
        cout << operation[0] << " - Matrix doesn't have an inverse matrix.";
        for (int i = 1; i < rowCount; i++)
        {
            cout << operation[i];
        }
        return;
    }

    //Initialize inverse matrix
    double **inverseArray;
    inverseArray = new double *[rowCount];
    for (int i = 0; i < rowCount; ++i)
    {
        inverseArray[i] = new double[colCount];
    }

    //Array to temporary store adjugated matrix
    double **tempArray;
    tempArray = new double *[rowCount - 1];
    for (int i = 0; i < rowCount - 1; ++i)
    {
        tempArray[i] = new double[colCount - 1];
    }

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            //Fill the temparray with the adjungated matrix on i and j row and
            calculateAjungated(array, rowCount, i, j, tempArray);
            //Calculates the sign in front of the given member
            double multiplier = (i + j) % 2 == 0 ? 1 : -1;
            //Formula to calculate members of an inverse array
            inverseArray[i][j] = multiplier * determinant(tempArray, rowCount - 1) / arrDeterminant;
        }
    }

    //Frees memory
    for (int i = 0; i < rowCount - 1; ++i)
    {
        delete[] tempArray[i];
    }
    delete[] tempArray;

    //Transposes the inverse matrix and prints it out which is the last step of the formula
    transposeMatrix(inverseArray, rowCount, colCount, operation);

    for (int i = 0; i < rowCount; ++i)
    {
        delete[] inverseArray[i];
    }
    delete[] inverseArray;
}

void calculateOperation(string operation[], int lineCount)
{
    string firstLine = operation[0];
    int operatorIndex = findOperatorIndex(firstLine);

    //Operations with two or one arrays
    if (firstLine[operatorIndex] == ' ')
    {
        int rowCount1 = 0;

        //Calculates the rowCount of the first matrix
        for (int i = 0; i < lineCount; i++)
        {
            if (operation[i][0] == '|')
            {
                rowCount1++;
            }
        }

        //Calculates the rowCount of the second matrix
        int rowCount2 = 0;

        int indexOfBorderOfMatrix2 = operatorIndex + 3;

        for (int i = 0; i < lineCount; i++)
        {
            if (operation[i][indexOfBorderOfMatrix2] == '|')
            {
                rowCount2++;
            }
        }
        //If there are two arrays the operator is to the right of the last symbol after the matrix
        operatorIndex++;

        string rows1[rowCount1];
        string rows2[rowCount2];

        //Takes only the numbers from the matrices and puts them into string arrays
        int endOfMatrix1 = operatorIndex - 3;
        int startOfMatrix2 = operatorIndex + 3;

        for (int i = 0; i < rowCount1; i++)
        {
            rows1[i] = operation[i].substr(1, endOfMatrix1);
        }

        for (int i = 0; i < rowCount2; i++)
        {
            rows2[i] = operation[i].substr(startOfMatrix2);
            rows2[i].pop_back();
        }

        int colCount1 = colCount(rows1[0]);
        int colCount2 = colCount(rows2[0]);

        //Initialize matrices
        double **array1;
        double **array2;

        array1 = new double *[rowCount1];
        for (int i = 0; i < rowCount1; ++i)
        {
            array1[i] = new double[colCount1];
        }

        array2 = new double *[rowCount2];
        for (int i = 0; i < rowCount2; ++i)
        {
            array2[i] = new double[colCount2];
        }

        //Parses all the rows from string array to double array
        for (int i = 0; i < rowCount1; i++)
        {
            parseString(rows1[i], array1[i], rowCount1, colCount1);
        }

        for (int i = 0; i < rowCount2; i++)
        {
            parseString(rows2[i], array2[i], rowCount2, colCount2);
        }

        switch (firstLine[operatorIndex])
        {
        case 'X':
            multiplyMatrixWithMatrix(array1, array2, rowCount1, colCount1, rowCount2, colCount2, lineCount, operatorIndex, operation);
            break;
        case '+':
            addMatrixToMatrix(array1, array2, rowCount1, colCount1, rowCount2, colCount2, lineCount, operatorIndex, operation);
            break;
        default:
            //Case for wrong operator
            displayError(operation, lineCount);
            break;
        }

        //Frees meomory from matrices
        for (int i = 0; i < rowCount1; ++i)
        {
            delete[] array1[i];
        }
        delete[] array1;

        for (int i = 0; i < rowCount2; ++i)
        {
            delete[] array2[i];
        }
        delete[] array2;
    }
    else
    {
        //Operations with one matrix

        int rowCount1 = lineCount;
        string rows[rowCount1];

        //Takes all the lines from the operation without the | symbols (Only the numbers)
        for (int i = 0; i < rowCount1; i++)
        {
            rows[i] = operation[i].substr(1);
            string tempRow;

            for (int j = 0; j < rows[i].size(); j++)
            {
                if (rows[i][j] != '|')
                {
                    tempRow.push_back(rows[i][j]);
                }
                else
                {
                    break;
                }
            }

            rows[i] = tempRow;
        }
        int colCount1 = colCount(rows[0]);

        //Initialize matrix
        double **array;

        array = new double *[rowCount1];
        for (int i = 0; i < rowCount1; ++i)
        {
            array[i] = new double[colCount1];
        }

        //Parses all the rows from string array to double array
        for (int i = 0; i < rowCount1; i++)
        {
            parseString(rows[i], array[i], rowCount1, colCount1);
        }

        switch (firstLine[operatorIndex])
        {
        case 'X':
            multiplyMatrixWithNum(array, rowCount1, colCount1, operatorIndex, operation);
            break;
        case '/':
            divideMatrixByNum(array, rowCount1, colCount1, operatorIndex, operation);
            break;
        case 'D':
            calculateDeterminant(array, rowCount1, colCount1, operation);
            break;
        case 'T':
            transposeMatrix(array, rowCount1, colCount1, operation);
            break;
        case '-':
            inverseMatrix(array, rowCount1, colCount1, operation);
            break;
        default:
            //Case for wrong operator
            displayError(operation, lineCount);
            break;
        }

        //Frees memory from matrix
        for (int i = 0; i < rowCount1; ++i)
        {
            delete[] array[i];
        }
        delete[] array;
    }
}

void readOperations(string lines[], int lineCount)
{
    string currenOperation[102];
    currenOperation[lineCount + 1] = " ";
    int operationLineCount = 0;

    for (int i = 0; i < lineCount + 1; i++)
    {
        //Splits the text file into operations and each one is calculated and printed out
        if (stringIsMadeOfWhiteSpaces(lines[i]))
        {
            //Ensures that if a matrix is written down incorrectly it displays an error istead of ending the program
            try
            {
                calculateOperation(currenOperation, operationLineCount);
            }
            catch (const std::exception &e)
            {
                displayError(currenOperation, operationLineCount);
            }

            cout << endl;

            //Clears the current operation so the next one can be loaded
            for (int j = 0; j < 100; j++)
            {
                currenOperation[j].clear();
            }
            operationLineCount = 0;
        }
        else
        {
            currenOperation[operationLineCount] = lines[i];
            operationLineCount++;
        }
    }
}

void readOperationsFromFile()
{
    string lines[101];
    int lineCount = 0;
    if (readFile(lines, lineCount))
    {

        //Validation for the text file
        if (lineCount > 100)
        {
            cout << "Number of lines must not be over 100." << endl;
        }
        else
        {
            readOperations(lines, lineCount);
        }
    }
    else
    {
        cout << "Can not find file." << endl;
    }
}

int main()
{
    readOperationsFromFile();
    return 0;
}