#include "comment_remover.h"

FILE *comment_remover(FILE *file)
{
    if (file == NULL)
    {
        return NULL;
    }

    FILE *temp_file = tmpfile();
    if (temp_file == NULL)
    {
        perror("Error creating temporary file");
        return NULL;
    }

    int ch;
    int next_ch;
    int in_single_line_comment = 0;
    int in_multi_line_comment = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (in_single_line_comment)
        {
            if (ch == '\n')
            {
                in_single_line_comment = 0;
                fputc(ch, temp_file);
            }
        }
        else if (in_multi_line_comment)
        {
            if (ch == '*' && (next_ch = fgetc(file)) == '/')
                in_multi_line_comment = 0;
            else
                ungetc(next_ch, file);
        }
        else
        {
            if (ch == '/')
            {
                next_ch = fgetc(file);
                if (next_ch == '/')
                    in_single_line_comment = 1;
                else if (next_ch == '*')
                    in_multi_line_comment = 1;
                else
                {
                    fputc(ch, temp_file);
                    fputc(next_ch, temp_file);
                }
            }
            else
                fputc(ch, temp_file);
        }
    }

    rewind(temp_file);

    fclose(file);

    return temp_file;
}