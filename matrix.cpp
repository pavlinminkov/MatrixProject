#include <iostream>
#include <fstream>
#include <string>

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
            int j;
            for (j = i; row[j] != ' ' && j < row.size(); j++)
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

void calculateOperation(string operation[101], int lineCount)
{
    string firstLine = operation[0];
    int borderCount = 0;
    int operatorIndex = 0;
    for (char a : firstLine)
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
            rows2[i] = operation[i].substr(operatorIndex + 3, rows2[i].size() - 1);
        }

        int colCount1 = colCount(rows1[0]);
        int colCount2 = colCount(rows2[0]);

        double array1[rowCount1][colCount1];
        double array2[rowCount2][colCount2];

        for (int i = 0; i < rowCount1; i++)
        {
            parseString(rows1[i], array1[i], rowCount1, colCount1);
        }

        for (int i = 0; i < rowCount2; i++)
        {
            parseString(rows2[i], array2[i], rowCount2, colCount2);
        }

        if (firstLine[operatorIndex] == 'X')
        {
        }
        else if (firstLine[operatorIndex] == '+')
        {
        }
        else
        {
            //Error
        }
    }
    else
    {
        int rowCount1 = lineCount;
        string rows[rowCount1];
        for (int i; i < rowCount1; i++)
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

        double array[rowCount1][colCount1];

        for (int i = 0; i < rowCount1; i++)
        {
            parseString(rows[i], array[i], rowCount1, colCount1);
        }

        for (int i = 0; i < rowCount1; i++)
        {
            for (int j = 0; j < colCount1; j++)
            {
                cout << array[i][j] << ' ';
            }
            cout << endl;
        }
        

        switch (firstLine[operatorIndex])
        {
        case 'X':
            //Multiply with number
            break;
        case 'D':
            //Determinant
            break;
        case '/':
            //Divide by num
            break;
        case 'T':
            //Transpolate
            break;
        case 'i':
            //Reverse
            break;
        default:
            //Add Error
            break;
        }
    }
}

void readOperations(string lines[101], int lineCount)
{
    string currenOperation[101];
    currenOperation[lineCount + 1] = " ";
    int operationLineCount = 0;

    for (int i = 0; i < lineCount + 1; i++)
    {
        if (stringIsMadeOfWhiteSpaces(lines[i]))
        {
            calculateOperation(currenOperation, operationLineCount);

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