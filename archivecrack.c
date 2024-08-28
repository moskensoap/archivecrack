#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PASSWORD_LENGTH 100

char words[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}\\|;:,.<>?/'\"`~ ";

char command_7z[] = "7z t \"";
char command_p[] = "\" -p\"";
char command_out[] = "\" > /dev/null 2>&1";

void generate_passwords(char *password, int current_length, int max_length, char *argv, char *password_string, char *merged_string)
{
    if (current_length == max_length)
    {
        password[current_length] = '\0';

        printf("\r\033[KTrying password: %s", password);
        fflush(stdout);

        int k = 0;
        for (int j = 0; j < current_length; j++)
        {
            if (password[j] == '\\' || password[j] == '\"' || password[j] == '`')
            {
                password_string[k++] = '\\';
                password_string[k++] = password[j];
            }
            else
            {
                password_string[k++] = password[j];
            }
        }

        password_string[k] = '\0';

        strcpy(merged_string, command_7z);
        strcat(merged_string, argv);
        strcat(merged_string, command_p);
        strcat(merged_string, password_string);
        strcat(merged_string, command_out);

        // Debug print statements
        // printf("\n\r\033[K%s\n", merged_string);

        int ret = system(merged_string);

        if (WIFEXITED(ret))
        {
            if (!WEXITSTATUS(ret))
            {
                printf("\r\033[KPassword is: %s\n", password);
                fflush(stdout);
                free(password);
                free(password_string);
                free(merged_string);
                exit(0);
            }
        }
        else
        {
            free(password);
            free(password_string);
            free(merged_string);
            fprintf(stderr, "Command did not terminate normally.\n");
            exit(1);
        }

        return;
    }

    for (int i = 0; i < strlen(words); i++)
    {
        password[current_length] = words[i];
        generate_passwords(password, current_length + 1, max_length, argv, password_string, merged_string);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <ArchiveFile.Format>\n", argv[0]);
        return 1;
    }

    // If argv[1] is not a file, then exit
    if (access(argv[1], F_OK) == -1)
    {
        fprintf(stderr, "File does not exist.\n");
        return 1;
    }

    char *password = malloc(MAX_PASSWORD_LENGTH + 1);
    if (password == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    char *password_string = malloc(MAX_PASSWORD_LENGTH * 2 + 1);
    if (password_string == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(password);
        return 1;
    }

    size_t required_size = strlen(command_7z) + strlen(argv[1]) + strlen(command_p) + MAX_PASSWORD_LENGTH * 2 + strlen(command_out) + 1;
    char *merged_string = malloc(required_size);
    if (merged_string == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(password);
        free(password_string);
        return 1;
    }

    for (int i = 1; i <= MAX_PASSWORD_LENGTH; i++)
    {
        generate_passwords(password, 0, i, argv[1], password_string, merged_string);
    }

    free(password);
    free(password_string);
    free(merged_string);

    printf("\nNo password matched.\n");
    return 0;
}
