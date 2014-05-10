#include <stdlib.h>
#include <stdio.h>

// List of allowed characters for a value
#define VALID_CHAR(c) ((c >= '0' && c <= '9') \
        || (c >= 'a' && c <= 'z') \
        || (c >= 'A' && c <= 'Z') \
        || c == '.' || c == '-')

//#define DEBUG

#ifdef DEBUG
#define BEGIN printf("===== ")
#define END printf(" =====\n")
#endif

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

enum Orientation
{
    FREE = 0, LENGTHWISE = 1, WIDTHWISE = 2
};

// Compares two strings and return the index of the character that differs from one string to the other.
int string_compare(const char* a, const char* b)
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
    \param dictionary [in/out] Adresse of the array that contains the list of product identifier so that we can replace them by integer indexes.
    \param dictionary_size [in/out] Pointer to the dictionary's size.

    \warning The values[value_cursor] cell is supposed to be already allocated and ready to be filled.
*/
void parse_line(const char* line, int* values, char*** dictionary, size_t* dictionary_size)
{
    // Cursors pointing to the beginning and the end of the value
    size_t line_cursor_begin = 0;
    size_t line_cursor_end;

    // For a value (e.g. an item) we have several values (e.g. code, length, width, etc...)
    size_t values_cursor = 0;

    // The value is Not a Number
    short nan;
    // The value has a decimal part (separated with '.')
    short is_float;

    // Possible non-numeric values
    char wood[] = "WOOD";
    char cardboard[] = "CARDBOARD";
    char metal[] = "METAL";
    char lengthwise[] = "LENGTHWISE";
    char widthwise[] = "WIDTHWISE";

    int i, j;
    
    while(line[line_cursor_begin] != '\0')
    {
        // If we have spotted a value
        if(VALID_CHAR(line[line_cursor_begin]))
        {
            nan = 1;
            is_float = 0;
            if((line[line_cursor_begin] >= '0' && line[line_cursor_begin] <= '9') || line[line_cursor_begin] == '-')
                nan = 0;
            else if(line[line_cursor_begin] == '.')
            {
                is_float = 1;
                nan = 0;
            }

            // Goto the end of the value
            line_cursor_end = line_cursor_begin + 1;
            while(VALID_CHAR(line[line_cursor_end]))
            {
                // If the value is still believed to be a number and has not yet contained a '.', set it as a float.
                // if another '.' character is found, the value will be set as NaN
                if(!nan && !is_float && line[line_cursor_end] == '.')
                    is_float = 1;
                else if(line[line_cursor_end] < '0' || line[line_cursor_end] > '9')
                    nan = 1;
                ++line_cursor_end;
            }

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
                    values[values_cursor] = LENGTHWISE;
                else if(string_compare(line + line_cursor_begin, widthwise) == 9)
                    values[values_cursor] = WIDTHWISE;
                // or it is an identifier
                else
                {
                    // Search the identifier in the dictionary
                    i = 0;
                    while(i < *dictionary_size &&
                            (*dictionary)[i][string_compare(line + line_cursor_begin, (*dictionary)[i])] != '\0') // the identifier is different from the current one
                        ++i;
                    
#ifdef DEBUG
                        BEGIN; printf("\npositions : %u - %u", line_cursor_begin, line_cursor_end); END;
#endif
                    // The identifier has not been used yet
                    if(i == *dictionary_size)
                    {
                        // Add it to the dictionary
                        *dictionary = realloc(*dictionary, sizeof(char*) * (*dictionary_size + 1));
                        (*dictionary)[*dictionary_size] = malloc(sizeof(char) * (line_cursor_end - line_cursor_begin + 1));
                        // Copy the identifier
                        j = 0;
                        while(j < line_cursor_end - line_cursor_begin)
                        {
                            (*dictionary)[*dictionary_size][j] = line[line_cursor_begin + j];
                            ++j;
                        }
                        (*dictionary)[*dictionary_size][j] = '\0';
#ifdef DEBUG
                        BEGIN; printf("\nNew identifier : %s\n", (*dictionary)[*dictionary_size]); END;
#endif
                        ++(*dictionary_size);
                    }
#ifdef DEBUG
                    else
                    {
                        BEGIN; printf("\nidentifier already known : %s\n", (*dictionary)[i]); END;
                    }
#endif
                    values[values_cursor] = i;
                }
            }
            else if(is_float) // if it is a float, then it is a weight, we convert weights in grams instead of kilograms and keep it as an integer
                values[values_cursor] = atof(line + line_cursor_begin) * 1000;
            else
                values[values_cursor] = atof(line + line_cursor_begin);

            line_cursor_begin = line_cursor_end;
            // Goto the next value
            while(line[line_cursor_begin] != '\0' && line[line_cursor_begin] !=';')
                ++line_cursor_begin;

            if(line[line_cursor_begin] == '\0')
                --line_cursor_begin; // Compensate the following incrementation so that we do not read too far

            //printf("value found : %d \n", values[values_cursor]);
            //printf("remaing : %s\n", line + line_cursor_begin);
            printf("%d ", values[values_cursor]);

            ++values_cursor;
        }
        // If no value is given, the default value is 0
        else if(line[line_cursor_begin] == ';')
        {
            values[values_cursor] = 0;

            //printf("value found : %d \n", values[values_cursor]);
            //printf("remaing : %s\n", line + line_cursor_begin);
            printf("%d ", values[values_cursor]);

            ++values_cursor;
        }

        ++line_cursor_begin;
    }
}

/*!
    Reads an input file (bin.txt, items.txt or parameters.txt).
    \param filename [in] Name of the file to read.
    \param values [out] Pointer to the array that will contain the values from the file.
    \param size_values [in/out] Number of cells of values.
    \param nb_values [in] Number of integer values per value (i.e. per item, bin,...).
    \param dictionary [out] Address of the array that will contain the list of product identifier so that we can replace them by integer indexes.
    \param dictionary_size [in/out] Pointer to the dictionary's size.
*/
void read_file(const char* filename, int*** values, size_t* size_values, const size_t nb_values, char*** dictionary, size_t* dictionary_size)
{
    FILE* input_file;
    input_file = fopen(filename, "r");

    int i; 
    size_t values_cursor = 0;

    *size_values = 1;
    *values = malloc(sizeof(int*));
    (*values)[0] = NULL;
    *dictionary_size = 0;
    *dictionary = NULL;

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

    // Prepare to read line by line
    char file_cursor;
    char* line = malloc(sizeof(char));
    int size_line = 1;
    int line_cursor = 0;

    ///////////////////
    // READ THE FILE //
    ///////////////////

    // Skip the first line
    while((file_cursor = fgetc(input_file)) != '\n' && file_cursor != EOF);

    while(file_cursor != EOF)
    {
        ///////////////
        // READ LINE //
        ///////////////

        // Read the line and put it into the line array
        file_cursor = fgetc(input_file);
        while(file_cursor != '\n' && file_cursor != EOF)
        {
            // The array is not big enough, double its size
            if(line_cursor >= size_line)
                line = realloc(line, sizeof(char) * (size_line *= 2));

            line[line_cursor++] = file_cursor;
            file_cursor = fgetc(input_file);
        }
        // End the line
        if(line_cursor >= size_line)
        {
            size_line *= 2;
            line = realloc(line, sizeof(char) * size_line);
        }
        line[line_cursor++] = '\0';
        line_cursor = 0;

        // If there was a \r before the \n (which is quite common), replace \r with \n
        // Note : we could have detected '\r' directly in the loop condition (line 261 ATM), but then we would have to deal with the '\n' for the next line, which means next line will be empty while we ask for a line containing all the data for one value (item, bin,...)
        while(line[line_cursor] != '\r' && line[line_cursor] != '\0')
            ++line_cursor;
        line[line_cursor++] = '\0';

        ////////////////
        // PARSE LINE //
        ////////////////

        if(values_cursor > *size_values - 1)
        {
            i = *size_values;
            *size_values *= 2;
            *values = realloc(*values, sizeof(int*) * (*size_values));
            while(i < *size_values)
                (*values)[i++] = NULL;
        }
        (*values)[values_cursor] = malloc(sizeof(int) * nb_values);
        // Extract the values from the line and place them in the values array at the position values_cursor
        parse_line(line, (*values)[values_cursor++], dictionary, dictionary_size);
        putchar('\n');

        line_cursor = 0;
    }

    free(line);
}

int main(int argc, char** argv)
{
    char filename[] = "input_items.csv";
    int** values = NULL;
    size_t size_values = 0;
    size_t nb_values = 8;
    char** dictionary = NULL;
    size_t dictionary_size = 0;

    read_file(filename, &values, &size_values, nb_values, &dictionary, &dictionary_size);

    int i;
    if(values != NULL)
    {
        i = 0;
        while(i < size_values)
            free(values[i++]);
        free(values);
    }
    if(dictionary != NULL)
    {
        i = 0;
        while(i < dictionary_size)
            free(dictionary[i++]);
        free(dictionary);
    }

    return 0;
}
