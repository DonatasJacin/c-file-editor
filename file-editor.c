#include <stdio.h>
#include <string.h>

/*Start of changelog operations*/

void AppendChangeLog(char *operation, char *fileModified1, char *fileModified2){
  FILE *file; //Pointer of type file is declared so file can be interacted with by program
  file = fopen("Changelog.txt", "a"); //Changelog file is opened in append mode
  fprintf(file, "%s %s     %s %s %s" "\n", "Operation:", operation, "File(s):", fileModified1, fileModified2);
  //Line is printed in format: "Operation: (operation)     File(s): (file1) (file2)"
  fclose(file); //File is closed
}

void ShowChangeLog(){
  char ch; //Character ch is declared
  FILE *file; //Pointer of type file is declared so file can be interacted with by program
  file = fopen("Changelog.txt", "r"); //Changelog file is opened in read mode
  ch = fgetc(file); //Next character of file is taken and put in ch
  printf("\n"); //New line is printed for cleaner presentation
  while (ch != EOF){ //Loop runs until EOF character is reached
    printf("%c", ch); //Current character is printed to terminal
    ch = fgetc(file); //Next character of file is taken and put in ch
  }
  printf("\n"); //New line is printed for cleaner presentation
  fclose(file); //File is closed
}

/*End of changelog operations*/
/*Start of file operations*/

void CreateFile(){
  char *fileName =  NULL; //New string is declared using a pointer of type character
  size_t length = 0; //Unsigned integer declared which will be used for length of string fileName
  char ch; //Character ch is declared
  printf("Enter name for new file"); //User asked for input
  getline(&fileName, &length, stdin); //Takes user input from stdin, stores in fileName, and size of input is stored in length
  strtok(fileName, "\n"); //Splits string fileName with delimiter \n. Used to remove newline character from end of string
  FILE *file; //Pointer of type file is declared so file can be interacted with by program
  file = fopen(fileName, "w"); //File is opened in write mode
  AppendChangeLog("Create File", fileName, ""); //Change log is appended with operation and file
  fclose(file); //File is closed
}

void CopyFile(){
  char *fileName1 = NULL; //New strings are declared using pointers of type character
  char *fileName2 = NULL;
  size_t length1 = 0; //Unsigned integers declared which are used for lengths of string fileName1 and fileName2
  size_t length2 = 0;
  char ch; //Character ch is declared
  FILE *file1; //Pointers of type file declared so files can be interacted with by program
  FILE *file2;
  printf("Enter name of file to be copied "); //User asked for input
  getline(&fileName1, &length1, stdin); //Takes user input from stdin, stored in fileName1, and size of input stored in length1
  strtok(fileName1, "\n"); //Splits string fileName2 with delimiter \n. Used to remove newline character from string
  printf("Enter name of new file "); //User asked for input
  getline(&fileName2, &length2, stdin); //Takes user input from stdin, stored in fileName2, and size of input stored in length2
  strtok(fileName2, "\n"); //Splits string fileName2 with delimiter \n. Used to remove newline character from string
  file1 = fopen(fileName1, "r"); //File to be copied opened in read mode
  if (file1 == NULL){ //Exception handling if the file is unable to be opened
    printf("Error: File does not exist or insufficient permissions\n");
    return;
  }
  file2 = fopen(fileName2, "w"); //File to be copied to is opened in write mode
  ch = fgetc(file1); // Next character of file1 is stored in ch
  while (ch != EOF){ //Loop runs until EOF is reached
    fputc(ch, file2); //Writes ch into file2
    ch = fgetc(file1); //Next character of file1 is stored in ch
  }
  AppendChangeLog("Copy File", fileName1, fileName2); //Changelog appended with operation and files used
  fclose(file1); //Files are closed
  fclose(file2);
}

void DeleteFile(){
  char *fileName = NULL; //New string is declared using pointer of type character
  size_t length = 0; //Unsigned integer declared which is used for length of string fileName
  printf("Enter name of file to be deleted "); //User asked for input
  getline(&fileName, &length, stdin); //Takes user input from stdin, stored in filename, and size of input stored in length1
  strtok(fileName, "\n"); //Splits string fileName with delimiter \n. Used to remove newline character
  int removed = remove(fileName); //Deletes file with name fileName, and stored 0 in removed upon success, -1 otherwise
  if (removed == 0){ //Exception handling in the event that the file does not exist
    printf("Success\n");
  } else if (removed == -1){
    printf("Error: Could not remove file, maybe file does not exist or insufficient permissions\n");
    return;
  }
  AppendChangeLog("Delete File", fileName, ""); //Changelog appended with operation and file deleted
}

void ShowFile(){
  char *fileName = NULL; //New string is declared using pointer of type character
  size_t length = 0; //Unsigned integer declared which is used for length of string fileName
  char ch; //Character ch is declared
  FILE *file; //Pointer of type file declared so file can be interacted with by program
  printf("Enter name of file to be displayed "); //User asked for input
  getline(&fileName, &length, stdin); //Takes user input from stdin, stored in fileName, and size of input stored in length
  strtok(fileName, "\n"); //Splits string fileName with delimiter \n, Used to remove newline character
  file = fopen(fileName, "r"); //File is opened in read mode
  if (file == NULL){ //Exception handling in event that file could not be opened
    printf("Error: File does not exist or insufficient permissions\n");
    return;
  }
  ch = fgetc(file); //Next character of file is stored in ch
  while (ch != EOF){ //Loop runs until EOF
    printf("%c", ch); //Prints ch to the terminal
    ch = fgetc(file); //Next character of file is stored in ch
  }
  printf("\n"); //New line printed to cleaner presentation
  fclose(file); //File is closed
}

void RenameFile(){
  char *fileName1 = NULL; //New strings are declared using pointers of type character
  char *fileName2 = NULL;
  size_t length1 = 0; //Unsigned integers declared which are used for length of strings fileName1 fileName2
  size_t length2 = 0;
  FILE *file; //Pointer of type file declared so file can be interacted with by program
  printf("Enter name of file to rename "); //User asked for input
  getline(&fileName1, &length1, stdin); //Takes user input from stdin, stored in fileName1, and size of input stored in length1
  strtok(fileName1, "\n"); //Splits string fileName1 using delimiter \n. Used to remove new line character
  printf("Enter new name of file "); //User asked for input
  getline(&fileName2, &length2, stdin); //Takes user input from stdin, stored in fileName2, and size of input stored in length2
  strtok(fileName2, "\n"); //Splits string fileName2 using delimiter \n. Used to remove new line character
  int renamed = rename(fileName1, fileName2); //Renames file fileName1 to fileName2 and returns 0 on success, 1 otherwise
  if (renamed == 0){ //Exception handling in event that file could not be renamed
    printf("File renamed successfully\n");
  } else if (renamed == -1){
    printf("Error: Could not rename file, perhaps file does not exist or insufficient permissions\n");
    return;
  }
  AppendChangeLog("Rename File", fileName1, fileName2); //Changelog appended with operation and file that was renamed
}

void ListFiles(){
  char command[20] = "ls -l -p | grep -v /"; //String containing command to list files and their permissions is defined
  char *choice = NULL; //New strings are declared using pointers of type character
  char *fileName = NULL;
  char *newPermissions = NULL;
  char chmod[7] = "chmod "; //String containing chmod command is defined
  char space[2] = " "; //String containing space is defined for later use in strcat
  size_t length1 = 0; //Unsigned integers are declared which are used for length of strings choice, fileName, and newPermissions
  size_t length2 = 0;
  size_t length3 = 0;
  printf("All files in working directory: \n");
  system(command); //Executes linux command to list all files in directory and their permissions
  printf("Change any permissions? (Y/N)"); //User asked for input
  getline(&choice, &length1, stdin); //User input is taken from stdin, stored in choice, and size of input stored in length1
  strtok(choice, "\n"); //String choice is split with delimiter \n. Used to remove newline character
  if (choice[0] == 'Y'){ //Selection for user input
    printf("Enter filename to change permissions\n"); //User asked for input
    getline(&fileName, &length2, stdin); //User input taken from stdin, stored in fileName, and size of input stored in length2
    strtok(fileName, "\n"); //String fileName is split with delimiter \n. Used to remove newline character
    printf("Enter new permissions in format: ugo\n"); //User asked for input, examples given
    printf("u - user, g - group, o - other\n");
    printf("Example input to give all permissions (read, write, and execute) to user: 700\n");
    getline(&newPermissions, &length3, stdin); //User input taken from stdin, stored in newPermissions, and size of input stored in length3
    strtok(newPermissions, "\n"); //String newPermissions is split with delimiter \n. Used to remove newline character
    char *start = strcat(chmod, newPermissions); //Strings chmod and  newPermissions are concatenated
    char *end = strcat(space, fileName); //Strings space and fileName are concatenated
    char *command = strcat(start, end); //Strings start and end are concatenated
    system(command); //Executes linux command for changing permissions of file
  }
  return;
}

/*End of file operations*/
/*Start of line operations*/

void AppendLine(){
  char *fileName = NULL; //Strings are declared using pointers of type character
  char *line = NULL;
  size_t length1 = 0; //Unsigned integers used to store length of strings fileName and line
  size_t length2 = 0;
  FILE *file; //Pointer of type file declared so file can be interacted with by program
  printf("Enter name of file to append line to "); //User asked for input
  getline(&fileName, &length1, stdin); //User input taken from stdin, stored in fileName, and size of input stored length1
  strtok(fileName, "\n"); //String fileName split with delimiter \n. Used to remove new line character
  printf("Enter content of line to append to file "); //User asked for input
  getline(&line, &length2, stdin); //User input taken from stdin, stored in line, and size of input stored in length2
  strtok(line, "\n"); //String line split with delimiter \n. Used to remove new line character
  file = fopen(fileName, "a+"); //File opened in append/read mode
  if (file == NULL){ //Exception handling in event that file cannot be opened
    printf("Error: File does not exist or insufficient permissions or insufficient permissions\n");
    return;
  }
  if (fgetc(file) == EOF){ //If the file is empty, line is appended without a newline previous
    fprintf(file, "%s", line);
  } else { //If file is not empty, line is appended with a newline previous
    fprintf(file, "\n" "%s", line);
  }
  fclose(file); //File is closed
  AppendChangeLog("Append Line", fileName, ""); //Changelog is appended with operation and file
}

void DeleteLine(){
  char *fileName = NULL; //Strings are declared using pointers of type character
  char *stringInt = NULL;
  size_t length1 = 0; //Unsigned integers declared and used to store length of strings fileName and stringInt
  size_t length2 = 0;
  char temp[8] = "copy.txt"; //String declared which stored name of temporary file
  char ch; //Character ch is declared
  int lineNumber = 1; //Integer lineNumber is declared and defined as 1
  int deleteLine; //Integer deleteLine is declared
  FILE *file1; //Pointers of type file declared so files can be interacted with by program
  FILE *file2;
  printf("Enter name of file to delete line from "); //User asked for input
  getline(&fileName, &length1, stdin); //User input taken from stdin, stored in fileName, size of input stored in length1
  strtok(fileName, "\n"); //String fileName is split using delimiter \n. Used to remove new line character
  printf("Enter line number to delete "); //User asked for input
  getline(&stringInt, &length2, stdin); //User input taken from stdin, stored in stringInt, size of input stored in length2
  strtok(stringInt, "\n"); //String stringInt split using delimiter \n. Used to remove new line character
  deleteLine = strtol(stringInt, NULL, 10); //stringInt is converted to integer and stored in deleteLine
  file1 = fopen(fileName, "r"); //Original file is opened in read mode
  if (file1 == NULL){ //Exception handling in event that file could not be opened
    printf("Error: File does not exist or insufficient permissions or insufficient permissions\n");
    return;
  }
  file2 = fopen(temp, "w"); //New temporary file opened in write mode
  ch = fgetc(file1); //Next character of file1 stored in ch
  while (ch != EOF){ //Loop runs until EOF reached
    if (ch == '\n'){ //If newline character reached, lineNumber incremented
      if (lineNumber == 1 && deleteLine == 1){ //Also if the lineNumber is 1 and deleteLine is 1, get next character in file1
        ch = fgetc(file1);
      }
      lineNumber++;
    }
    if (lineNumber != deleteLine){ //If current line is not the delete line
      putc(ch, file2); //Write ch to temporary file, file2
    }
    ch = fgetc(file1); //Get next character in file1 and store in ch
  }
  fclose(file1); //Close original file
  remove(fileName); //Delete original file
  rename(temp, fileName); //Rename new file to original file
  fclose(file2); //Close new file
  AppendChangeLog("Delete Line", fileName, ""); //Append changelog with operaion and file name
}

void InsertLine(){
  char *fileName = NULL; //Strings are declared using pointers of type character
  char *line = NULL;
  char *stringInt  = NULL;
  size_t length1 = 0; //Unsigned integers are declared to store length of strings fileName, line, and stringInt
  size_t length2 = 0;
  size_t length3 = 0;
  char temp[8] = "copy.txt"; //String containing name of temporary file declared and defined
  char ch; //Character ch is declared
  int lineNumber = 1; //Integer lineNumber is declared and defined
  int insertLine; //Integer insertLine is declared
  int alreadyWritten = 0; //Integer alreadyWritten is declared and defined
  FILE *file1; //Pointer of type file are declared so files can be interacted with by program
  FILE *file2;
  printf("Enter content to insert to file "); //User asked for input
  getline(&line, &length2, stdin); //User input taken from stdin, stored in line, size of input stored in length2
  strtok(line, "\n"); //String line is split using delimiter \n. Used to remove newline character
  printf("Enter name of file to insert line to "); //User asked for input
  getline(&fileName, &length1, stdin); //User input taken from stdin, stored in fileName, size of input stored in length1
  strtok(fileName, "\n"); //String fileName is split using delimiter \n. Used to remove newline character
  printf("Enter line number to insert content "); //User asked for input
  getline(&stringInt, &length3, stdin); //User input taken from stdin, stored in stringInt, size of input stored in length3
  strtok(stringInt, "\n"); //String stringInt is split using delimited \n. Used to remove newline character
  insertLine = strtol(stringInt, NULL, 10); //String stringInt is converted to integer and stored in insertLine
  file1 = fopen(fileName, "r"); //Original file is opened in read mode
  if (file1 == NULL){ //Exception handling in event that file cannot be opened
    printf("Error: File does not exist or insufficient permissions or insufficient permissions\n");
    return;
  }
  file2 = fopen(temp, "w"); //New temporary file is opened in write mode
  ch = fgetc(file1); //Next character of original file is stored in ch
  while (ch != EOF){ //Loop runs until EOF is reached
    if (ch == '\n'){ //If the character is a newline character, lineNumber is incremented
      lineNumber++;
    }
    if (lineNumber == insertLine){ //If lineNumber is equal to insertLine
      if (insertLine == 1){ //If also insertLine is the first line
        fprintf(file2, "%s" "\n", line); //String line is written to file2 with a newline after
        putc(ch, file2); //Character written to file2
      } else{ //Also insertLine is not the first line
        fprintf(file2, "\n" "%s" "\n", line); //String line is written to file2 with a newline previous and after
      }
      alreadyWritten = 1; //Sets alreadyWritten to 1
      lineNumber++; //lineNumber incremented
    } else{ //lineNumber not equal to insertLine
      putc(ch, file2); //Writes character to file2
    }
    ch = fgetc(file1); //Gets next character from file1 and stores in ch
  }
  if (alreadyWritten == 0){ //If alreadyWritten is equal to 0, i.e. EOF reached but insertLine is not reached
    fprintf(file2, "\n"); //Writes a newline to file2
    while (lineNumber != insertLine){ //Loop runs until the lineNumber is equal to insertLine
      lineNumber++; //lineNumber incremented
      if (lineNumber == insertLine){ //If lineNumber is equal to insertLine
        fprintf(file2, "%s", line); //String line is written to file2
      } else { //Not equal
        fprintf(file2, "\n"); //Newline is written to file2
      }
    }
  }
  fclose(file1); //Original file closed
  remove(fileName); //Original file deleted
  rename(temp, fileName); //New file renamed to original file
  fclose(file2); //New file closed
  AppendChangeLog("Insert Line", fileName, ""); //Changelog appended with operation and file name
}

void ShowLine(){
  char *fileName = NULL; //Strings are declared using pointers of type character
  char *stringInt = NULL;
  size_t length1 = 0; //Unsigned integers used to store lengths of strings fileName and stringInt
  size_t length2 = 0;
  char ch; //Character ch is declared
  int lineNumber = 1; //Integer lineNumber is declared and defined
  int showLine; //Integer showLine is declared
  FILE *file; //Pointer of type file is declared so that file can be interacted with by program
  printf("Enter name of file to show line from "); //User asked for input
  getline(&fileName, &length1, stdin); //User input taken from stdin, stored in fileName, and size of input stored in length1
  strtok(fileName, "\n"); //String fileName is split using delimiter \n. Used to remove newline character
  printf("Enter line number to display"); //User asked for input
  getline(&stringInt, &length2, stdin); //User input taken from stdin, stored in stringInt, and size of input stored in length2
  strtok(stringInt, "\n"); //String stringInt is split using delimiter \n. Used to remove newline character
  showLine = strtol(stringInt, NULL, 10); //String stringInt is converted to integer and stored in showLine
  file = fopen(fileName, "r"); //File is opened in read mode
  if (file == NULL){ //Exception handling in the event that file cannot be opened
    printf("Error: File does not exist or insufficient permissions or insufficient permissions\n");
    return;
  }
  ch = fgetc(file); //Next character of file is taken and stored in ch
  while (ch != EOF){ //Loop runs until EOF is reached
    if (ch == '\n'){ //If current character is the newline character
      lineNumber++; //lineNumber incremented
      ch = fgetc(file); //Next character taken from file and stored in ch
      if (ch == '\n'){ //If current character is newline charcter
        if (lineNumber == showLine){ //If also lineNumber is equal to showLine
          printf("Line was empty"); //Line must be empty
          printf("%c", ch); //Prints current character to terminal
          break; //Breaks while loop
        }
        lineNumber++; //lineNumber incremented again if previous if statement was not satisfied
      }
    }
    if (lineNumber == showLine){ //If lineNumber is eqaul to showLine
      printf("%c", ch); //Prints current character to terminal
    }
    ch = fgetc(file); //Gets next character of file and stores in ch
  }
  printf("\n"); //Prints newline for cleaner presentation
  fclose(file); //Closes file
}

/*End of line operations*/

/*Start of general operations*/

void ShowNumberOfLines(){
  char *fileName = NULL; //String declared using pointer of type character
  size_t length = 0; //Unsigned integer used to store length of string fileName
  char ch; //Character ch is declared
  int lineNumber = 1; //Integer lineNumber is declared
  FILE *file; //Pointer of type file is declared so file can be interacted with by program
  printf("Enter name of file to count lines from "); //User asked for input
  getline(&fileName, &length, stdin); //User input taken from stdin, stored in fileName, and size of input stored in length
  strtok(fileName, "\n"); //String fileName is split using delimtier \n. Used to remove newline character
  file = fopen(fileName, "r"); //File opened in read mode
  if (file == NULL){ //Exception handling in event that file could not be opened
    printf("Error: File does not exist or insufficient permissions or insufficient permissions or insufficient permissions\n");
    return;
  }
  ch = fgetc(file); //Gets next character of file and stores in ch
  while (ch != EOF){ //Loop runs until EOF is reached
    if (ch == '\n'){ //If current character is the newline character
      lineNumber++; //lineNumber is incremented
    }
    ch = fgetc(file); //Gets next character of file and stores in ch
  }
  fclose(file); //Closes file
  printf("\n %d \n \n", lineNumber); //Prints the amount of lines counted to terminal with new lines for cleaner presentation
}

/*End of general operations*/

void Menu(){
  int selection; //Integer selection declared
  char *stringInt = NULL; //String declared using pointer of type character
  size_t length = 0; //Unsigned integer used to store length of string stringInt
  printf("Select from options below by typing option number: \n"); //User asked for input
  printf("1. Create a file\n"); //Options listed
  printf("2. Copy a file\n");
  printf("3. Delete a file\n");
  printf("4. Show a file\n");
  printf("5. Append a line to end of file\n");
  printf("6. Delete a line from file\n");
  printf("7. Insert a line to file\n");
  printf("8. Show a line from file\n");
  printf("9. Rename a file\n");
  printf("10. List all files in current directory and/or change permissions\n");
  printf("11. Show change log\n");
  printf("12. Show number of lines in file\n");
  printf("13. Quit\n");
  getline(&stringInt, &length, stdin); //Used input taken from stdin, stored in stringInt, size of input stored in length
  strtok(stringInt, "\n"); //String stringInt is split using delimiter \n. Used to remove newline character
  selection = strtol(stringInt, NULL, 10); //String stringInt is turned into integer and stored in selection
  if (selection == 1){ //Check is done for each selection
    CreateFile(); //Corresponding function called
    Menu(); //Menu called recursively
  } else if (selection == 2){
    CopyFile();
    Menu();
  } else if (selection == 3){
    DeleteFile();
    Menu();
  } else if (selection == 4){
    ShowFile();
    Menu();
  } else if (selection == 5){
    AppendLine();
    Menu();
  } else if (selection == 6){
    DeleteLine();
    Menu();
  } else if (selection == 7){
    InsertLine();
    Menu();
  } else if (selection == 8){
    ShowLine();
    Menu();
  } else if (selection == 9){
    RenameFile();
    Menu();
  } else if (selection == 10){
    ListFiles();
    Menu();
  } else if (selection == 11){
    ShowChangeLog();
    Menu();
  } else if (selection == 12){
    ShowNumberOfLines();
    Menu();
  } else if( selection == 13){ //If quit is selected do not call menu recursively
    return;
  } else{ //If none of the options are selected
    printf("Not a valid option, try again\n");
    Menu();
  }
}

int main(){
  Menu(); //Call initial Menu function
}
