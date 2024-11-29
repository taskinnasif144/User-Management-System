#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <ctype.h>

void mainmenu()
{
    printf("****************************\n");
    printf(" Gym Management System\n ");
    printf("*****************************\n");
    printf("\n");
    printf("--------------------------\n");
    printf("| 1.Add User             |\n");
    printf("| 2.Get All Users        |\n");
    printf("| 3.Search Users         |\n");
    printf("| 4.Delete Users         | \n");
    printf("| 5.Update user          |\n");
    printf("--------------------------\n");
    printf("\n");
}

struct memberRecords
{
    char name[50];
    int age;
    char gender;
    int weight;
    int height;
} memberRecord;

void createUser()
{
    printf("\n");
    printf("Enter Username ");
    getchar();
    fgets(memberRecord.name, 50, stdin);
    memberRecord.name[strcspn(memberRecord.name, "\n")] = '\0';
    printf("Enter Age ");
    scanf("%d", &memberRecord.age);
    printf("Enter Gender ");
    scanf("%s", &memberRecord.gender);
    printf("Enter Weight ");
    scanf("%d", &memberRecord.weight);
    printf("Enter Height ");
    scanf("%d", &memberRecord.height);
    FILE *userFile;
    userFile = fopen("users.txt", "a");
    fprintf(userFile, "%s, %d, %c, %d, %d\n", memberRecord.name, memberRecord.age, memberRecord.gender, memberRecord.weight, memberRecord.height);
    fclose(userFile);
    printf("\n\n");
}

void getAllUsers()
{

    struct memberRecords members[1000];
    FILE *readFile = fopen("users.txt", "r");
    if (readFile == NULL)
    {
        puts("Error Getting File");
    }

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(readFile, "%49[^,], %d, %c, %d, %d\n", &members[records].name, &members[records].age, &members[records].gender, &members[records].weight, &members[records].height);

        if (read == 5)
            records++;
        if (read != 5 && !feof(readFile))
        {
            printf("File format incorrect\n");
        }
        if (ferror(readFile))
        {
            printf("Error Reading File. \n");
        }
    } while (!feof(readFile));

    fclose(readFile);

    printf("--------------------\n");
    printf("| %d Records Read.  |\n", records);
    printf("--------------------\n");

    for (int i = 0; i < records; i++)
    {
        printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
    }

    printf("\n\n\n");
}

void searchUserByName()
{
    printf("*********************************\n");
    printf("What do you want to search by?\n ");
    printf("*********************************\n");
    printf("\n");
    printf("--------------\n");
    printf("| 1.Name    |\n");
    printf("| 2.Age      |\n");
    printf("| 3.Gender   |\n");
    printf("| 4.Weight   |\n");
    printf("| 5.Height   |\n");
    printf("--------------\n");
    int searchType;
    printf("Enter Search Type: ");
    scanf("%d", &searchType);

    struct memberRecords members[1000];
    FILE *readFile = fopen("users.txt", "r");
    if (readFile == NULL)
    {
        puts("Error Getting File");
    }

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(readFile, "%49[^,], %d, %c, %d, %d\n", &members[records].name, &members[records].age, &members[records].gender, &members[records].weight, &members[records].height);

        if (read == 5)
            records++;
        if (read != 5 && !feof(readFile))
        {
            printf("File format incorrect\n");
        }
        if (ferror(readFile))
        {
            printf("Error Reading File. \n");
        }
    } while (!feof(readFile));

    int searchCount = 0;
    char strSearchType[50];
    char genderSearchType;
    int numSearchTypeUpper;
    int numSearchTypeLower;

    switch (searchType)
    {
    case 1:

        printf("Enter Name: ");
        scanf("%s", &strSearchType);

        for (int i = 0; i < records; i++)
        {
            for (int j = 0; j < strlen(strSearchType); j++)
            {
                strSearchType[j] = tolower(strSearchType[j]);
            }
            char tempName[100];
            strcpy(tempName, members[i].name);
            for (int j = 0; j < strlen(members[i].name); j++)
            {
                tempName[j] = tolower(tempName[j]);
            }

            char *isValid = strstr(tempName, strSearchType);
            if (isValid != NULL)
            {
                searchCount++;
            }
        }
        fclose(readFile);
        printf("--------------------\n");
        printf("| %d Records Read.  |\n", searchCount);
        printf("--------------------\n");

        for (int i = 0; i < records; i++)
        {
            for (int j = 0; j < strlen(strSearchType); j++)
            {
                strSearchType[j] = tolower(strSearchType[j]);
            }
            char tempName[100];
            strcpy(tempName, members[i].name);
            for (int j = 0; j < strlen(members[i].name); j++)
            {
                tempName[j] = tolower(tempName[j]);
            }
            char *isValid = strstr(tempName, strSearchType);
            if (isValid != NULL)
            {
                printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            }
        }
        break;

    case 2:

        printf("Enter Age Upper Limit ");
        scanf("%d", &numSearchTypeUpper);
        printf("Enter Age Lower Limit ");
        scanf("%d", &numSearchTypeLower);

        for (int i = 0; i < records; i++)
        {
            if (members[i].age <= numSearchTypeUpper && members[i].age >= numSearchTypeLower)
            {
                searchCount++;
            }
        }
        fclose(readFile);
        printf("--------------------\n");
        printf("| %d Records Read.  |\n", searchCount);
        printf("--------------------\n");
        for (int i = 0; i < records; i++)
        {
            if (members[i].age <= numSearchTypeUpper && members[i].age >= numSearchTypeLower)
            {
                printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            }
        }
        break;

    case 3:
        printf("Enter Gender only M/F: ");
        scanf("%s", &genderSearchType);
        if (genderSearchType == 'F' || genderSearchType == 'M')
        {

            for (int i = 0; i < records; i++)
            {
                if (members[i].gender == genderSearchType)
                {
                    searchCount++;
                }
            }
            fclose(readFile);
            printf("--------------------\n");
            printf("| %d Records Read.  |\n", searchCount);
            printf("--------------------\n");
            for (int i = 0; i < records; i++)
            {
                if (members[i].gender == genderSearchType)
                {
                    printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
                }
            }
        }
        else
        {
            printf("Invalid Gender Input");
        }
        break;

    case 4:
        printf("Enter Weight Upper Limit ");
        scanf("%d", &numSearchTypeUpper);
        printf("Enter Weight Lower Limit ");
        scanf("%d", &numSearchTypeLower);

        for (int i = 0; i < records; i++)
        {
            if (members[i].weight <= numSearchTypeUpper && members[i].weight >= numSearchTypeLower)
            {
                searchCount++;
            }
        }
        fclose(readFile);
        printf("--------------------\n");
        printf("| %d Records Read.  |\n", searchCount);
        printf("--------------------\n");
        for (int i = 0; i < records; i++)
        {
            if (members[i].weight <= numSearchTypeUpper && members[i].weight >= numSearchTypeLower)
            {
                printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            }
        }
        break;
    case 5:
        printf("Enter Height Upper Limit ");
        scanf("%d", &numSearchTypeUpper);
        printf("Enter Height Lower Limit ");
        scanf("%d", &numSearchTypeLower);

        for (int i = 0; i < records; i++)
        {
            if (members[i].height <= numSearchTypeUpper && members[i].height >= numSearchTypeLower)
            {
                searchCount++;
            }
        }
        fclose(readFile);
        printf("--------------------\n");
        printf("| %d Records Read.  |\n", searchCount);
        printf("--------------------\n");
        for (int i = 0; i < records; i++)
        {
            if (members[i].height <= numSearchTypeUpper && members[i].height >= numSearchTypeLower)
            {
                printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            }
        }
        break;

    default:
        printf("\nInput Not in Range");
        break;
    }

    printf("\n\n\n");
}

void deleteUser()
{
    char name[50];

    printf("Enter Name: ");
    scanf("%s", &name);

    struct memberRecords members[1000];
    FILE *readFile = fopen("users.txt", "r");
    if (readFile == NULL)
    {
        puts("Error Getting File");
    }

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(readFile, "%49[^,], %d, %c, %d, %d\n", &members[records].name, &members[records].age, &members[records].gender, &members[records].weight, &members[records].height);

        if (read == 5)
            records++;
        if (read != 5 && !feof(readFile))
        {
            printf("File format incorrect\n");
        }
        if (ferror(readFile))
        {
            printf("Error Reading File. \n");
        }
    } while (!feof(readFile));

    int searchCount = 0;
    for (int i = 0; i < records; i++)
    {
        for (int j = 0; j < strlen(name); j++)
        {
            name[j] = tolower(name[j]);
        }
        char tempName[100];
        strcpy(tempName, members[i].name);
        for (int j = 0; j < strlen(members[i].name); j++)
        {
            tempName[j] = tolower(tempName[j]);
        }

        char *isValid = strstr(tempName, name);
        if (isValid != NULL)
        {
            searchCount++;
        }
    }
    fclose(readFile);
    printf("--------------------\n");
    printf("| %d Records Read.  |\n", searchCount);
    printf("--------------------\n");

    for (int i = 0; i < records; i++)
    {
        for (int j = 0; j < strlen(name); j++)
        {
            name[j] = tolower(name[j]);
        }
        char tempName[100];
        strcpy(tempName, members[i].name);
        for (int j = 0; j < strlen(members[i].name); j++)
        {
            tempName[j] = tolower(tempName[j]);
        }
        char *isValid = strstr(tempName, name);
        if (isValid != NULL)
        {
            printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
    }

    char deleteUser;

    printf("Do you want to delete this/these user? y/n: ");
    getchar();
    scanf("%c", &deleteUser);

    if (deleteUser == 'y')
    {
        FILE *deleteFile = fopen("users.txt", "w");
        if (deleteFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            for (int j = 0; j < strlen(name); j++)
            {
                name[j] = tolower(name[j]);
            }
            char tempName[100];
            strcpy(tempName, members[i].name);
            for (int j = 0; j < strlen(members[i].name); j++)
            {
                tempName[j] = tolower(tempName[j]);
            }
            char *isValid = strstr(tempName, name);
            if (isValid == NULL)
            {
                fprintf(deleteFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            }
        }
        printf("\nUser deletion Successfull\n\n\n");
        fclose(deleteFile);
    }
    else
    {
        printf("\nUser deletion Canceled\n\n\n");
    }
}

void updateUser()
{
    char name[50];

    printf("Enter Name: ");
    scanf("%s", &name);

    struct memberRecords members[1000];
    FILE *readFile = fopen("users.txt", "r");
    if (readFile == NULL)
    {
        puts("Error Getting File");
    }

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(readFile, "%49[^,], %d, %c, %d, %d\n", &members[records].name, &members[records].age, &members[records].gender, &members[records].weight, &members[records].height);

        if (read == 5)
            records++;
        if (read != 5 && !feof(readFile))
        {
            printf("File format incorrect\n");
        }
        if (ferror(readFile))
        {
            printf("Error Reading File. \n");
        }
    } while (!feof(readFile));

    int searchCount = 0;
    for (int i = 0; i < records; i++)
    {
        for (int j = 0; j < strlen(name); j++)
        {
            name[j] = tolower(name[j]);
        }
        char tempName[100];
        strcpy(tempName, members[i].name);
        for (int j = 0; j < strlen(members[i].name); j++)
        {
            tempName[j] = tolower(tempName[j]);
        }

        char *isValid = strstr(tempName, name);
        if (isValid != NULL)
        {
            searchCount++;
        }
    }
    fclose(readFile);
    printf("--------------------\n");
    printf("| %d Records Read.  |\n", searchCount);
    printf("--------------------\n");
    int index;
    for (int i = 0; i < records; i++)
    {
        for (int j = 0; j < strlen(name); j++)
        {
            name[j] = tolower(name[j]);
        }
        char tempName[100];
        strcpy(tempName, members[i].name);
        for (int j = 0; j < strlen(members[i].name); j++)
        {
            tempName[j] = tolower(tempName[j]);
        }
        char *isValid = strstr(tempName, name);
        if (isValid != NULL)
        {
            printf("%d. Name: %s, Age: %d Gender: %c Weight: %d Height: %d \n", i, members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
            index = i;
            break;
        }
    }

    printf("*********************************\n");
    printf(" Which Field Needs to be Updated?\n ");
    printf("*********************************\n");
    printf("\n");
    printf("--------------\n");
    printf("| 1.Name    |\n");
    printf("| 2.Age      |\n");
    printf("| 3.Gender   |\n");
    printf("| 4.Weight   |\n");
    printf("| 5.Height   |\n");
    printf("--------------\n");

    int updateType;
    char newField[50];
    int newDigitField;
    FILE *updateFile;
    printf("\n Enter Update Type: ");
    scanf("%d", &updateType);

    switch (updateType)
    {
    case 1:
        printf("Provide New Name: ");
        getchar();
        fgets(members[index].name, 50, stdin);
        members[index].name[strcspn(members[index].name, "\n")] = '\0';
        updateFile = fopen("users.txt", "w");
        if (updateFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            fprintf(updateFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
        printf("\nUser Updated Successfully\n\n\n");
        fclose(updateFile);
        break;
    case 2:
        printf("Provide New Age: ");
        scanf("%d", &members[index].age);
        updateFile = fopen("users.txt", "w");
        if (updateFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            fprintf(updateFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
        printf("\nUser Updated Successfully\n\n\n");
        fclose(updateFile);
        break;
    case 3:
        printf("Provide New Gender: ");
        scanf("%s", &members[index].gender);
        updateFile = fopen("users.txt", "w");
        if (updateFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            fprintf(updateFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
        printf("\nUser Updated Successfully\n\n\n");
        fclose(updateFile);
        break;
    case 4:
        printf("Provide New Weight: ");
        scanf("%d", &members[index].weight);
        updateFile = fopen("users.txt", "w");
        if (updateFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            fprintf(updateFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
        printf("\nUser Updated Successfully\n\n\n");
        fclose(updateFile);
        break;
    case 5:
        printf("Provide New Height: ");
        scanf("%d", &members[index].height);
        updateFile = fopen("users.txt", "w");
        if (updateFile == NULL)
        {
            puts("Error Getting File");
        }
        for (int i = 0; i < records; i++)
        {
            fprintf(updateFile, "%s, %d, %c, %d, %d\n", members[i].name, members[i].age, members[i].gender, members[i].weight, members[i].height);
        }
        printf("\nUser Updated Successfully\n\n\n");
        fclose(updateFile);
        break;

    default:
        printf("\nInput Not in Range");
        break;
    }

    printf("\n\n\n");
}

int main()
{
    while (true)
    {
        mainmenu();
        char operationType;
        printf("Enter Operation Type Number: ");
        scanf("%d", &operationType);

        switch (operationType)
        {

        case 1:
            createUser();
            break;
        case 2:
            getAllUsers();
            break;
        case 3:
            searchUserByName();
            break;
        case 4:
            deleteUser();
            break;
        case 5:
            updateUser();
            break;

        default:
            printf("\nInput Not in Range");
            break;
        }
    }
    return 0;
}