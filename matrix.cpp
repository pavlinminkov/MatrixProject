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
    doubleStr.erase(doubleStr.find_last_not_of('0') + 1, string::npos);
    if (doubleStr.back() == '.')
    {
        return doubleStr.size() - 1;
    }
    return doubleStr.size();
}

string convertDoubleToString(double num)
{
    string doubleStr = to_string(num);
    doubleStr.erase(doubleStr.find_last_not_of('0') + 1, string::npos);
    if (doubleStr.back() == '.')
    {
        doubleStr.pop_back();
    }
    return doubleStr;
}

int colCount(string row)
{
    row = row.substr(row.find_first_not_of(" "));
    int count = 0;

    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] != ' ')
        {
            int j;
            for (j = i; row[j] != ' ' && j < row.size(); j++)
                ;
            count++;
            i = j;
        }
    }

    return count;
}

void parseString(string row, double array[], int rows, int cols)
{
    row = row.substr(row.find_first_not_of(" "));
    int currentNumIndex = 0;

    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] != ' ')
        {
            int j = i;
            for (j; row[j] != ' ' && j < row.size(); j++)
                ;
            array[currentNumIndex] = stod(row.substr(i, j - i));
            currentNumIndex++;
            i = j;
        }
    }
}

void readFile(string lines[100], int &lineCount)
{
    // cout << "Enter file name: ";

    // string fileName;
    // cin >> fileName;

    ifstream matrixFile("file.txt");

    lineCount = 0;

    while (getline(matrixFile, lines[lineCount]))
    {
        lineCount++;
    }
}

void displayError(string operation[], int lineCount)
{
    cout << operation[0] << " = Error" << endl;
    for (int i = 1; i < lineCount; i++)
    {
        cout << operation[i] << endl;
    }
}

void multiplyMatrixWithNum(double **&array, int rowCount, int colCount, int operatorIndex, string operation[])
{
    string firstLine = operation[0];
    double num = stod(firstLine.substr(operatorIndex + 1));
    int maxLengthsPerCol[colCount];
    for (int i = 0; i < colCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

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

    for (int i = 0; i < rowCount; i++)
    {
        cout << operation[i];
        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            for (int j = 0; j <= firstLine.substr(operatorIndex + 1).size(); j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < colCount; j++)
        {
            cout << setw(maxLengthsPerCol[j]) << array[i][j];
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
    double num = stod(firstLine.substr(operatorIndex + 1));
    int maxLengthsPerCol[colCount];
    for (int i = 0; i < colCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int numLength = doubleLength(array[i][j] /= num);
            if (numLength > maxLengthsPerCol[j])
            {
                maxLengthsPerCol[j] = numLength;
            }
        }
    }

    for (int i = 0; i < rowCount; i++)
    {
        cout << operation[i];
        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            for (int j = 0; j <= firstLine.substr(operatorIndex + 1).size(); j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < colCount; j++)
        {
            cout << setw(maxLengthsPerCol[j]) << convertDoubleToString(array[i][j]);
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
    int maxLengthsPerCol[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

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

    for (int i = 0; i < colCount; i++)
    {
        if (i + 1 > rowCount)
        {
            for (int j = 0; j < operation[0].size() - 1; j++)
            {
                cout << ' ';
            }
        }

        cout << operation[i];

        if (i == 0)
        {
            cout << " = |";
        }
        else
        {
            for (int j = 0; j < operation[0].size() - operation[1].size(); j++)
            {
                cout << ' ';
            }
            cout << "   |";
        }

        for (int j = 0; j < rowCount; j++)
        {
            cout << setw(maxLengthsPerCol[j]) << convertDoubleToString(array[j][i]);
            if (j < rowCount - 1)
            {
                cout << ' ';
            }
        }

        cout << '|' << endl;
    }
}

void calculateAjungated(double **&array, int rowCount, int row, int column, double **&result)
{
    int tempColIndex = 0;
    int tempRowIndex = 0;

    for (int j = 0; j < rowCount; j++)
    {
        tempColIndex = 0;

        for (int k = 0; k < rowCount; k++)
        {
            if (j != row && k != column)
            {
                result[tempRowIndex][tempColIndex] = array[j][k];
                tempColIndex++;
            }
        }

        if (j != row)
        {
            tempRowIndex++;
        }
    }
}

double determinant(double **&array, int rowCount)
{
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

    int tempRowCount = rowCount - 1;
    double **tempArray;
    tempArray = new double *[tempRowCount];
    for (int i = 0; i < tempRowCount; ++i)
    {
        tempArray[i] = new double[tempRowCount];
    }

    double tempDeterminant = 0;

    for (int i = 0; i < rowCount; i++)
    {
        calculateAjungated(array, rowCount, 0, i, tempArray);

        if (i % 2 == 0)
        {
            tempDeterminant += array[0][i] * determinant(tempArray, tempRowCount);
        }
        else
        {
            tempDeterminant -= array[0][i] * determinant(tempArray, tempRowCount);
        }
    }

    for (int i = 0; i < tempRowCount; ++i)
    {
        delete[] tempArray[i];
    }
    delete[] tempArray;

    return tempDeterminant;
}

void calculateDeterminant(double **&array, int rowCount, int colCount, string operation[])
{
    if (rowCount != colCount)
    {
        displayError(operation, rowCount);
        return;
    }

    cout << operation[0] << " = " << determinant(array, rowCount) << endl;
    for (int i = 1; i < rowCount; i++)
    {
        cout << operation[i] << endl;
    }
}

void multiplyMatrixWithMatrix(double **&array1, double **&array2, int rowCount1, int colCount1, int rowCount2, int colCount2, int lineCount, int operatorIndex, string operation[])
{
    if (colCount1 != rowCount2)
    {
        operation[0] += " = Error";
        for (int i = 0; i < lineCount; i++)
        {
            cout << operation[i] << endl;
        }
    }

    else
    {
        double resultArr[rowCount1][colCount2];
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
                    double result = array1[i][z] * array2[z][j];
                    resultArr[i][j] += result;
                    int length = doubleLength(resultArr[i][j]);
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
                cout << setw(maxLengthsPerCol[j]) << resultArr[i][j];
                if (j != colCount2 - 1)
                {
                    cout << " ";
                }
            }
            cout << '|' << endl;
        }
    }
}

void addMatrixToMatrix(double **&array1, double **&array2, int rowCount1, int colCount1, int rowCount2, int colCount2, int lineCount, int operatorIndex, string operation[])
{
    if (colCount1 != colCount2 || rowCount1 != rowCount2)
    {
        operation[0] += " = Error";
        for (int i = 0; i < lineCount; i++)
        {
            cout << operation[i] << endl;
        }
        return;
    }

    double resultArr[rowCount1][colCount1];
    int maxLengthsPerCol[colCount1];
    for (int i = 0; i < colCount1; i++)
    {
        maxLengthsPerCol[i] = 0;
    }

    for (int i = 0; i < rowCount1; i++)
    {
        for (int j = 0; j < colCount1; j++)
        {
            double result = array1[i][j] + array2[i][j];
            int resLength = doubleLength(result);
            if (resLength > maxLengthsPerCol[j])
            {
                maxLengthsPerCol[j] = resLength;
            }
            resultArr[i][j] = result;
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

        cout << '|';
        for (int j = 0; j < colCount2; j++)
        {
            cout << setw(maxLengthsPerCol[j]) << resultArr[i][j];
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
    if (rowCount != colCount)
    {
        displayError(operation, rowCount);
        return;
    }

    double arrDeterminant = determinant(array, rowCount);

    if (arrDeterminant == 0)
    {
        cout << operation[0] << " - Matrix doesn't have an inverse matrix.";
        for (int i = 1; i < rowCount; i++)
        {
            cout << operation[i];
        }
        return;
    }

    double **inverseArray;
    inverseArray = new double *[rowCount];
    for (int i = 0; i < rowCount; ++i)
    {
        inverseArray[i] = new double[colCount];
    }

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
            calculateAjungated(array, rowCount, i, j, tempArray);
            double multiplier = (i + j) % 2 == 0 ? 1 : -1;
            inverseArray[i][j] = multiplier * determinant(tempArray, rowCount - 1) / arrDeterminant;
        }
    }

    for (int i = 0; i < rowCount - 1; ++i)
    {
        delete[] tempArray[i];
    }
    delete[] tempArray;

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

        for (int i = 0; i < lineCount; i++)
        {
            if (operation[i][0] == '|')
            {
                rowCount1++;
            }
        }

        int rowCount2 = 0;

        for (int i = 0; i < lineCount; i++)
        {
            if (operation[i][operatorIndex + 3] == '|')
            {
                rowCount2++;
            }
        }
        operatorIndex++;

        string rows1[rowCount1];
        string rows2[rowCount2];

        for (int i = 0; i < rowCount1; i++)
        {
            rows1[i] = operation[i].substr(1, operatorIndex - 3);
        }

        for (int i = 0; i < rowCount2; i++)
        {
            rows2[i] = operation[i].substr(operatorIndex + 3);
            rows2[i].pop_back();
        }

        int colCount1 = colCount(rows1[0]);
        int colCount2 = colCount(rows2[0]);

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
            displayError(operation, lineCount);
            break;
        }

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
        int rowCount1 = lineCount;
        string rows[rowCount1];
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

        double **array;

        array = new double *[rowCount1];
        for (int i = 0; i < rowCount1; ++i)
        {
            array[i] = new double[colCount1];
        }

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
            displayError(operation, lineCount);
            break;
        }

        //Frees memory from pointer
        for (int i = 0; i < rowCount1; ++i)
        {
            delete[] array[i];
        }
        delete[] array;
    }
}

void readOperations(string lines[], int lineCount)
{
    string currenOperation[101];
    currenOperation[lineCount + 1] = " ";
    int operationLineCount = 0;

    for (int i = 0; i < lineCount + 1; i++)
    {
        if (stringIsMadeOfWhiteSpaces(lines[i]))
        {
            try
            {
                calculateOperation(currenOperation, operationLineCount);
            }
            catch (const std::exception &e)
            {
                displayError(currenOperation, operationLineCount);
            }

            cout << endl;

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

int main()
{
    string lines[100];
    int lineCount;
    readFile(lines, lineCount);
    if (lineCount > 100)
    {
        cout << "Number of lines must not be over 100" << endl;
        return 0;
    }
    readOperations(lines, lineCount);
    return 0;
}