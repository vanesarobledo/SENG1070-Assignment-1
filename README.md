# SENG1070 Assignment 1
## File Processing & Function Pointers in C

This was an assignment for my C Programming II class to demonstrate file input and output functions securely, the use of function pointers for increased modularity, and the use of Makefiles to automate the building process.

This program allows for file processing operations - filtering, transforming, summarizing and saving the changes to a `.txt` file.

## Usage

You may either type a number from the menu:

1. filterLines
2. transformLines
3. summarize
4. viewLines
5. loadFile
6. saveFile
7. exit

or use one of the following keyword commands

File Processing Commands:
------------------------------------------------------
`load`:           This option loads data from a .txt file after you provide the name.
                If there is nothing in the file, then data will not be loaded. The maximum line size is 256 characters.

`save`:           This option saves any filtered or transformed lines to a file.
                If you specify the name of a file that already exists, it will overwrite the data.


File Commands:
------------------------------------------------------
`view`:           This option displays the data loaded from the .txt file.

`filter`:         This option allows you to enter one or two keywords to filter the lines of the file.
                If one of the keyword(s) is present in the line, the line is deleted.

`transform`:      This option allows you to transform each line of the file depending on a transformation rule:
                uppercase (u/U), lowercase (l/L), or reverse. (r/R).

`summarize`:      This option allows you to enter a keyword and displays the total number of lines in the file,
                the frequency of the keyword you specified, and the average length of each line.


`test`:           Shows testing-related commands.

`secret`:         Shows secret commands.

`exit`:           This option exits the program.

