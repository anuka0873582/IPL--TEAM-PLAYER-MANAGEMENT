
#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 11

struct player
{
char name[50];
int jersey;
char type[20];
};

void selectTeam(char *filename)
{
int team;
printf("\nSelect Team\n");
printf("1. RCB\n");
printf("2. KKR\n");
printf("3. LSG\n");
printf("Enter Team: ");
scanf("%d", &team);

if (team == 1)
    strcpy(filename, "rcb.txt");
else if (team == 2)
    strcpy(filename, "kkr.txt");
else if (team == 3)
    strcpy(filename, "lsg.txt");
else
{
    printf("Invalid Team.\n");
    filename[0] = '\0';
}

}

int countPlayers(char *filename)
{
FILE *fp;
struct player p;
int count = 0;


fp = fopen(filename, "r");

if (fp == NULL)
    return 0;

while (fscanf(fp, " %49[^|]|%d|%19[^\n]",
              p.name, &p.jersey, p.type) == 3)
{
    count++;
}

fclose(fp);

return count;


}

int duplicateJersey(char *filename, int jersey)
{
FILE *fp;
struct player p;


fp = fopen(filename, "r");

if (fp == NULL)
    return 0;

while (fscanf(fp, " %49[^|]|%d|%19[^\n]",
              p.name, &p.jersey, p.type) == 3)
{
    if (p.jersey == jersey)
    {
        fclose(fp);
        return 1;
    }
}

fclose(fp);

return 0;


}

void addPlayer()
{
FILE *fp;
struct player p;
char filename[20];
int count;


selectTeam(filename);

if (filename[0] == '\0')
    return;

count = countPlayers(filename);

if (count >= MAX_PLAYERS)
{
    printf("Maximum 11 players allowed in this team.\n");
    return;
}

printf("\nEnter Player Name: ");
scanf(" %49[^\n]", p.name);

printf("Enter Jersey Number: ");
scanf("%d", &p.jersey);

printf("Enter Player Type: ");
scanf(" %19[^\n]", p.type);

if (duplicateJersey(filename, p.jersey))
{
    printf("Player with Jersey Number %d already exists.\n",
           p.jersey);
    return;
}

fp = fopen(filename, "a");

if (fp == NULL)
{
    printf("File opening failed.\n");
    return;
}

fprintf(fp, "%s|%d|%s\n",
        p.name, p.jersey, p.type);

fclose(fp);

printf("Player Added Successfully.\n");


}

void printPlayers()
{
FILE *fp;
struct player p;
char filename[20];
int count = 0;


selectTeam(filename);

if (filename[0] == '\0')
    return;

fp = fopen(filename, "r");

if (fp == NULL)
{
    printf("No players found.\n");
    return;
}

printf("\n---------------------------------------------\n");
printf("%-20s %-10s %-10s\n",
       "Name", "Jersey", "Type");
printf("---------------------------------------------\n");

while (fscanf(fp, " %49[^|]|%d|%19[^\n]",
              p.name, &p.jersey, p.type) == 3)
{
    printf("%-20s %-10d %-10s\n",
           p.name, p.jersey, p.type);

    count++;
}

fclose(fp);

if (count == 0)
    printf("No players found.\n");


}

void deletePlayer()
{
FILE *fp;
FILE *temp;
struct player p;
char filename[20];
char tempFile[] = "temp.txt";
int jersey;
int found = 0;

selectTeam(filename);

if (filename[0] == '\0')
    return;

fp = fopen(filename, "r");

if (fp == NULL)
{
    printf("No players found.\n");
    return;
}

printf("Enter Jersey Number to Delete: ");
scanf("%d", &jersey);

temp = fopen(tempFile, "w");

if (temp == NULL)
{
    fclose(fp);
    printf("File opening failed.\n");
    return;
}

while (fscanf(fp, " %49[^|]|%d|%19[^\n]",
              p.name, &p.jersey, p.type) == 3)
{
    if (p.jersey == jersey)
    {
        found = 1;
    }
    else
    {
        fprintf(temp, "%s|%d|%s\n",
                p.name, p.jersey, p.type);
    }
}

fclose(fp);
fclose(temp);

remove(filename);
rename(tempFile, filename);

if (found)
    printf("Player Deleted Successfully.\n");
else
    printf("Player with Jersey Number %d not found.\n",
           jersey);


}

int main()
{
int choice;


while (1)
{
    printf("\n========== MENU ==========\n");
    printf("1. Add Player\n");
    printf("2. Print Players\n");
    printf("3. Delete Player\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input.\n");
        break;
    }

    switch (choice)
    {
        case 1:
            addPlayer();
            break;

        case 2:
            printPlayers();
            break;

        case 3:
            deletePlayer();
            break;

        case 4:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
    }
}

return 0;

}
