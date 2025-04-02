#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

/*@ecenilkombak
Student Name: Ece Nil Kombak
Student Id:820220330
Date :21.10.2023 */

using namespace std;


int findlastId(string fileName)
{
    // This function returns the last Id on the list and later it'll be used for adding new employee.

    string id;
    string line;
    string prevLine;
    fstream adding;
    adding.open(fileName);

                while (getline(adding,line))
                {
                     prevLine = line;
                }

    istringstream lineToDivide(prevLine);

    getline(lineToDivide, id, ';');

    adding.close();

    return stoi(id);
}






 void addEmployee(int salary, int deptId, int *id, string fileName)
{
    string Id;
    string line;
    fstream adding;
    adding.open(fileName, ios::app);

    adding << ++*id <<";"<< salary <<";"<< deptId<< endl;
    adding.close();
}




 void updateData(int idToFind, int salary, int department, string fileName)
{
    // This function writes the new data to the temporary file that I've created and updates the info using it.

    string line, lineToDivide;
    string csvId;
    string readlinefromcsv;
    bool valid = false;

    fstream updating;
    updating.open(fileName, ios::in | ios::out);

    ofstream temp("temp.csv");

    getline(updating, readlinefromcsv);
    temp << readlinefromcsv << endl;
    while(getline(updating, readlinefromcsv))
    {
                istringstream linetodividecsv(readlinefromcsv);
                getline(linetodividecsv, csvId, ';');
                if (strtol(csvId.c_str(), nullptr, 10) == idToFind)
                {
                 //I used "strtol" instead of "stoi" because it causes error and it skips lines in my csv file.

                    valid = true;
                    temp << idToFind << ";" << salary << ";" << department << endl;

                }
                else
                {
                    temp << readlinefromcsv << endl;

                }
    }
    if (!valid)
    {
        cout<< "ERROR: An invalid ID to update" << endl;
    }

    temp.close();
    updating.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
}





 void deleteline(int idToFind, string fileName)
{
    //This function writes the data to the temporary file that I've created and deletes the lines when it encounters the picked ID.

    string line, lineToDivide;
    string csvId;
    string readlinefromcsv;
    bool found = false;

    fstream deleting;
    deleting.open(fileName, ios::in | ios::out);

    ofstream temp("temp.csv");


    getline(deleting, readlinefromcsv);
    temp << readlinefromcsv ;


    while(getline(deleting, readlinefromcsv))
    {

        istringstream linetodividecsv(readlinefromcsv);
        getline(linetodividecsv, csvId, ';');
        found = true;

        if (strtol(csvId.c_str(), nullptr, 10) == idToFind)
        {
            continue;
        }
        else
        {
            temp << readlinefromcsv << endl;
        }
    }

    if(!found)
    {
        cout<<"ERROR: There is no Employee"<< endl;
    }

    temp.close();
    deleting.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
}






int main(int argc, char *argv[])
{
    if (argc != 3 )
    {
        //Argument number error.
        cout<< "Error: Give proper amount of arguments\n";
        return EXIT_FAILURE;
    }
    string operationFileName = argv[2];
    string csvFile = argv[1];
    int lastId = findlastId(csvFile);
    string readLineFromOps;
    fstream operations;
    operations.open(operationFileName);

    while (getline(operations, readLineFromOps))
    {
        istringstream lineToDivide(readLineFromOps);
        string id,salary, operationType, department;

        // I split the data in the lines of operations.txt file, using delimiter.

        getline(lineToDivide, operationType, ';');

        if (operationType == "ADD")
        {
            getline(lineToDivide, salary, ';');
            getline(lineToDivide, department);

            addEmployee(stoi(salary), stoi(department), &lastId, csvFile);
        }
        else if(operationType == "UPDATE")
        {

            getline(lineToDivide, id, ';');
            getline(lineToDivide, salary, ';');
            getline(lineToDivide, department, ';');

            updateData(stoi(id), stoi(salary), stoi(department), csvFile);

        }
        else if (operationType == "DELETE")
        {
            getline(lineToDivide, id);
            deleteline(stoi(id),csvFile);

        }
    }
    operations.close();
    return 0;
}