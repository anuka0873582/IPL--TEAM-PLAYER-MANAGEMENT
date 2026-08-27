#include <stdio.h>
#include <string.h>

struct player
{
    char name[30];
    int jersey;
    char type[20];
};

int main()
{
    FILE *fp, *temp;
    struct player p;

    int choice, team, count;
    int delete_jersey;
    char filename[20];

    fp = fopen("rcb.txt", "a");
    fclose(fp);

    fp = fopen("kkr.txt", "a");
    fclose(fp);

    fp = fopen("lsg.txt", "a");
    fclose(fp);

    while(1)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Add Player\n");
        printf("2. Print Players\n");
        printf("3. Delete Player\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("\nSelect Team\n");
                printf("1. RCB\n");
                printf("2. KKR\n");
                printf("3. LSG\n");
                printf("Enter Team: ");
                scanf("%d", &team);

                if(team == 1)
                    strcpy(filename, "rcb.txt");
                else if(team == 2)
                    strcpy(filename, "kkr.txt");
                else if(team == 3)
                    strcpy(filename, "lsg.txt");
                else
                {
                    printf("Invalid Team\n");
                    break;
                }

                fp = fopen(filename, "a+");

                if(fp == NULL)
                {
                    printf("Unable to open file.\n");
                    break;
                }

                count = 0;

                rewind(fp);

                while(fscanf(fp, " %29[^|]|%d|%19[^\n]",
                             p.name, &p.jersey, p.type) == 3)
                {
                    count++;
                }

                if(count >= 11)
                {
                    printf("11 Players already exist in this team.\n");
                    fclose(fp);
                    break;
                }

                printf("\nEnter Player Name: ");
                scanf(" %29[^\n]", p.name);

                printf("Enter Jersey Number: ");
                scanf("%d", &p.jersey);

                printf("Enter Player Type: ");
                scanf(" %19[^\n]", p.type);

                fseek(fp, 0, SEEK_END);

                fprintf(fp, "%s|%d|%s\n",
                        p.name, p.jersey, p.type);

                fclose(fp);

                printf("Player Added Successfully.\n");

                break;

            case 2:

                printf("\nSelect Team\n");
                printf("1. RCB\n");
                printf("2. KKR\n");
                printf("3. LSG\n");
                printf("Enter Team: ");
                scanf("%d", &team);

                if(team == 1)
                    strcpy(filename, "rcb.txt");
                else if(team == 2)
                    strcpy(filename, "kkr.txt");
                else if(team == 3)
                    strcpy(filename, "lsg.txt");
                else
                {
                    printf("Invalid Team\n");
                    break;
                }

                fp = fopen(filename, "r");

                if(fp == NULL)
                {
                    printf("File not found.\n");
                    break;
                }

                rewind(fp);

                printf("\n---------------------------------------------\n");
                printf("%-20s %-10s %-10s\n",
                       "Name", "Jersey", "Type");
                printf("---------------------------------------------\n");

                while(fscanf(fp, " %29[^|]|%d|%19[^\n]",
                             p.name, &p.jersey, p.type) == 3)
                {
                    printf("%-20s %-10d %-10s\n",
                           p.name, p.jersey, p.type);
                }

                fclose(fp);

                break;

            case 3:

                printf("\nSelect Team\n");
                printf("1. RCB\n");
                printf("2. KKR\n");
                printf("3. LSG\n");
                printf("Enter Team: ");
                scanf("%d", &team);

                if(team == 1)
                    strcpy(filename, "rcb.txt");
                else if(team == 2)
                    strcpy(filename, "kkr.txt");
                else if(team == 3)
                    strcpy(filename, "lsg.txt");
                else
                {
                    printf("Invalid Team\n");
                    break;
                }

                fp = fopen(filename, "r");

                if(fp == NULL)
                {
                    printf("File not found.\n");
                    break;
                }

                temp = fopen("temp.txt", "w");

                if(temp == NULL)
                {
                    printf("Unable to create temporary file.\n");
                    fclose(fp);
                    break;
                }

                printf("Enter Jersey Number to Delete: ");
                scanf("%d", &delete_jersey);

                count = 0;

                while(fscanf(fp, " %29[^|]|%d|%19[^\n]",
                             p.name, &p.jersey, p.type) == 3)
                {
                    if(p.jersey == delete_jersey)
                    {
                        count++;
                    }
                    else
                    {
                        fprintf(temp, "%s|%d|%s\n",
                                p.name, p.jersey, p.type);
                    }
                }

                fclose(fp);
                fclose(temp);

                if(count == 0)
                {
                    printf("Player with Jersey Number %d not found.\n",
                           delete_jersey);

                    remove("temp.txt");
                }
                else
                {
                    remove(filename);
                    rename("temp.txt", filename);

                    printf("Player Deleted Successfully.\n");
                }

                break;

            case 4:

                printf("Thank You!\n");
                return 0;

            default:

                printf("Invalid Choice\n");
        }
    }

    return 0;
}