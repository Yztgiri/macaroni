#include <stdlib.h>
#include <stdio.h>

enum Index
{
    // Common to Bin and Item
    LENGTH = 0, WIDTH = 1, WEIGHT = 2,
    // Item only
    PACKAGE_MATERIAL = 3, ORIENTATION_CONSTRAINED = 4, PRODUCT = 5
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

/*!
    Reads a line and extract the values it contains.
    \param line [in] The line to read.
    \param values [out] Array that will contain the values from the line.
    \param size_values [in/out] Size of the values array.
    \param values_cursor [in] Index to the cell of the values array that will contain the extracted value.
*/
void parse_line(const char* line, int** values, int* size_values, int values_cursor);
{
    if(values_cursor >= *size_values)
    {
        *size_values *= 2;
        realloc(values, sizeof(int*) * (*size_values));
    }

    // Cursors pointing to the beginning and the end of the value
    int line_cursor_begin = 0;
    int line_cursor_end;

    int i = 0;
    while(i < *size_values)
        
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

    // Error - File does not exist
    if(!input_file)
    {
        printf("Can't open input file ");
        printf(filename);
        printf(".\n");
        exit(1);
    }

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

    // Skip the first line
    while((file_cursor = fgetc(input_file)) != "\n" && file_cursor != EOF);

    while(file_cursor != EOF)
    {
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
