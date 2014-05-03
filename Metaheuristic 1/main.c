#include <stdlib.h>
#include <stdio.h>

// List of allowed characters for a value
#define VALID_CHAR(c) ((c >= '0' && c <= '9') \
        || (c >= 'a' && c <= 'z') \
        || (c >= 'A' && c <= 'Z') \
        || c == '.' || c == '-')

enum Index
{
    // Common to Bin and Item
    IDENTIFIER = 0, LENGTH = 1, WIDTH = 2, WEIGHT = 3,
    // Item only
    PACKAGE_MATERIAL = 4, ORIENTATION_CONSTRAINED = 5, PRODUCT = 6
};

enum Material
{
    // Item package material
    WOOD = 0, CARDBOARD = 0, METAL = 1
};

enum Parameter
{
    // Parameters
    TOLERANCE_ITEM_PRODUCT_DEMANDS = 0, MAXIMUM_DENSITY_ALLOWED = 1, MAX_NUMBER_OF_ROWS_IN_A_LAYER = 2
};

int string_compare(char* a, char* b)
{
    int i = 0;
    while(a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
        ++i;
    return i;
}

/*!
    Reads a line and extract the values it contains.
    \param line [in] The line to read.
    \param values [out] Array that will contain the values from the line.
    \param size_values [in/out] Size of the values array.
    \param values_cursor [in] Index to the cell of the values array that will contain the extracted value.
    \param dictionary [in/out] 
*/
void parse_line(const char* line, int** values, int* size_values, int values_cursor, char*** dictionary, dictionary size)
{
    // Cursors pointing to the beginning and the end of the value
    int line_cursor_begin = 0;
    int line_cursor_end;

    // For a value (e.g. an item) we have several values (e.g. code, length, width, etc...)
    int value_cursor = 0;

    // The value is Not a Number
    short nan;

    // Possible non-numeric values
    char wood[] = "WOOD";
    char cardboard[] = "CARDBOARD";
    char metal[] = "METAL";
    char lengthwise[] = "LENGTHWISE";
    
    // Increase the size of the array, if necessary
    if(values_cursor >= *size_values)
    {
        *size_values *= 2;
        realloc(values, sizeof(int*) * (*size_values));
    }

    while(line[line_cursor_begin] != '\0')
    {
        // If we have spotted a value
        if(VALID_CHAR(line[line_cursor_begin]))
        {
            nan = 0;

            // Goto the end of the value
            line_cursor_end = line_cursor_begin;
            while(VALID_CHAR(line[++line_cursor_end]))
                if(line[line_cursor_end] < '0' || line[line_cursor_end] > '9')
                    nan = 1;

            // If the value is not a number
            if(nan)
            {
                // Either it is a value we can understand
                if(string_compare(line + line_cursor_begin, wood) == 4)
                    values[values_cursor] = WOOD;
                else if(string_compare(line + line_cursor_begin, cardboard) == 9)
                    values[values_cursor] = CARDBOARD;
                else if(string_compare(line + line_cursor_begin, metal) == 5)
                    values[values_cursor] = CARDBOARD;
                else if(string_compare(line + line_cursor_begin, lengthwise) == 10)
                    values[values_cursor] = 1;
                // or it is an identifier
                else
                {
                    d
                }
            }
            
            // goto the next value
            while(line[line_cursor_begin] != '\0' && line[line_cursor_begin] !=';')
            ++line_cursor_begin;
        }
        // If no value is given, the default value is 0
        else if(line[line_cursor_begin] == ';')
            values[values_cursor] = 0;

        ++line_cursor_begin;
    }
    ++values_cursor;
}

/*!
    Reads an input file (bin.txt, items.txt or parameters.txt).
    \param filename [in] Name of the file to read.
    \param values [out] Array that will contain the values from the file.
    \param size_values [in/out] Number of cells of values.
    \param nb_values [in] Number of integer values per value.

    \warning Expects values to be clean, i.e. all values[i] are unallocated.
*/
void read_file(const char* filename, int** values, int* size_values, int nb_values)
{
    FILE* input_file;
    input_file = fopen(filename, "r");

    ////////////
    // ERRORS //
    ////////////
    
    // ERROR - File does not exist
    if(!input_file)
    {
        printf("Can't open input file ");
        printf(filename);
        printf(".\n");
        exit(1);
    }

    /////////////////////
    // INITIALIZATIONS //
    /////////////////////

    // Initialize the array to have at least one cell
    if(*size_values < 1)
    {
        *size_values = 1;
        values = malloc(sizeof(int));
    }

    // Values iterator
    int values_cursor = 0;

    // Prepare to read line by line
    char file_cursor;
    char* line = malloc(sizeof(char));
    int size_line = 1;
    int line_cursor = 0;

    ///////////////////
    // READ THE FILE //
    ///////////////////

    // Skip the first line
    while((file_cursor = fgetc(input_file)) != "\n" && file_cursor != EOF);

    while(file_cursor != EOF)
    {
        ///////////////
        // READ LINE //
        ///////////////

        // Read the line and put it into the line array
        file_cursor = fgetc(input_file);
        while(file_cursor != "\n" && file_cursor != EOF)
        {
            // The array is not big enough, double its size
            if(line_cursor >= size_line)
                realloc(line, sizeof(char) * (size_line * = 2));

            line[line_cursor++] = file_cursor;
            file_cursor = fgetc(input_file);
        }
        // End the line
        if(line_cursor >= size_line)
            realloc(line, sizeof(char) * (size_line * = 2));
        line[line_cursor++] = '\0';

        ////////////////
        // PARSE LINE //
        ////////////////

        // Extract the values from the line and place them in the values array at the position values_cursor
        parse_line(line, values, size_values, nb_values, values_cursor++);
    }

    free(line);
}

int main(int argc, char** argv)
{
    read_file()

    return 0;
}
