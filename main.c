#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int month;
    int year;
} publication_date;

typedef struct
{
    long long int ISBN;
    char title[200];
    char author_name[200];
    int quantity;
    float price;
    publication_date pd;
} books;

books b[200];
int count = 0;

void login()
{
    printf("LOGIN\n");
    char str[100],str2[100],fstr[100],fstr2[100];
    FILE *flogin;
    flogin=fopen("credentials.txt", "r");
    if(flogin== NULL)
    {
        printf("file does not exist\n");
        exit(1);
    }
    while(1)
    {
        printf("Please enter the username:\n");
        gets(str);
        printf("Please enter the password:\n");
        gets(str2);
        fscanf(flogin,"%s", fstr);
        fscanf(flogin,"%s", fstr2);
        if(strcmp(str,fstr)==0 && strcmp(str2,fstr2)==0)
        {
            printf("Login Successful\n");
            break;
        }
        else
        {
            printf("Wrong user name or password try again\n");

        }
    }
    fclose(flogin);
}

void load()
{

    int i;
    FILE *fload;
    fload = fopen("books.txt", "r");
    if(fload == NULL)
    {
        printf("error in opening the file!");
        exit(1);
    }
    i=0;
    while(!feof(fload))
    {
        fscanf(fload, "%lld , %200[^,] , %200[^,] , %d , %f , %d-%d",
               &b[i].ISBN, b[i].title, b[i].author_name, &b[i].quantity, &b[i].price, &b[i].pd.month, &b[i].pd.year);
        i++;
        count ++;
    }
    fclose(fload);
}

char* convertmonth(int m)
{
    switch (m)
    {
    case 1:
        return "January";
        break;
    case 2:
        return "February";
        break;
    case 3:
        return "March";
        break;
    case 4:
        return "April";
        break;
    case 5:
        return "May";
        break;
    case 6:
        return "June";
        break;
    case 7:
        return "July";
        break;
    case 8:
        return "August";
        break;
    case 9:
        return "September";
        break;
    case 10:
        return "October";
        break;
    case 11:
        return "November";
        break;
    case 12:
        return "December";
        break;
    default:
        return "Invalid month";
        break;
    }
}

void printarray(int i)
{
    printf("\nISBN: %lld\n", b[i].ISBN);
    printf("title: %s\n", b[i].title);
    printf("author name: %s\n", b[i].author_name);
    printf("quantity: %d\n", b[i].quantity);
    printf("price: %f$\n", b[i].price);
    printf("published:%s %d\n", convertmonth(b[i].pd.month), b[i].pd.year);
}

long long int isvalid()
{
    int i, flag=0;
    long long int x;
    char isbn[13];
    printf("Please enter following information of the book: \n");
    printf("ISBN:");
    gets(isbn);
    if (strlen(isbn) != 13)
        flag++;
    for (i = 0; i < 13; i++)
    {
        if (!isdigit(isbn[i]))
        {
            flag++;
            break;
        }
    }
    if (flag != 0)
    {
        printf("invalid ISBN.\n");
        isvalid();
    }
    else
    {
        x = atoll(isbn);
        return x;
    }
}

void validmonth(int i)
{
    int k,flag1;
    char month[2];
    printf("month:");
    gets(month);
    for (k = 0; k < 2; k++)
    {
        if (!isdigit(month[k]))
        {
            flag1++;
            break;
        }
    }
    b[i].pd.month = atoi(month);
    if(b[i].pd.month<1 || b[i].pd.month>12)
    {
        flag1++;
        if (flag1!=0)
        {
            printf("Wrong input\nPlease input a number from 1 to 12 ");
            validmonth(i);
        }
    }
}

void validyear(int i)
{
    int k,flag1;
    char year[4];
    printf("year:");
    gets(year);
    for (k = 0; k < 4; k++)
    {
        if (!isdigit(year[k]))
        {
            flag1++;
            break;
        }
    }
    b[i].pd.year = atoi(year);
    if(b[i].pd.year<1 || b[i].pd.year>2022)
    {
        flag1++;
        if (flag1!=0)
        {
            printf("Wrong input\nPlease input a number from 1 to 2022 ");
            validyear(i);
        }
    }
}

void validquantity(i)
{
    int k,flag=0;
    char quantity[4];
    printf("quantity:");
    gets(quantity);
    for (k = 0; k < 4; k++)
    {
        if (!isdigit(quantity[k]))
        {
            flag++;
            break;
        }
    }
    b[i].quantity = atoi(quantity);
    if(b[i].quantity<1 || b[i].quantity>1000)
    {
        flag++;
        if (flag!=0)
        {
            printf("Wrong input\nPlease input a number from 1 to 1000\n");
            validquantity(i);
        }
    }
}

void validprice(i)
{
    int k,flag=0;
    char price[4];
    printf("price:");
    gets(price);
    for (k = 0; k < 4; k++)
    {
        if (!isdigit(price[k]))
        {
            flag++;
            break;
        }
    }
    b[i].price = atof(price);
    if(b[i].price<1 || b[i].price>100000)
    {
        flag++;
        if (flag!=0)
        {
            printf("Wrong input\nPlease input a number from 1 to 100000\n");
            validprice(i);
        }
    }
}

int isint(char x[])
{
    int i=0;
    while(x[i]!='\0')
    {
        if(!(x[i] >= '0' && x[i] <= '9'))
        {
            printf("wrong input.\n");
            return 0;
        }
        i++;
    }
    return 1;
}

void search()
{
    printf("SEARCH\n");
    long long int isbn;
    int i, flag=0;
    isbn = isvalid();
    for(i=0 ; i<count ; i++)
    {
        if(isbn == b[i].ISBN)
        {
            flag++;
            printarray(i);
            printf("\n");
        }
    }
    if(flag==0)
    {
        printf("Specified ISBN is not found.\n");
        search();
    }
}

void adv_search()
{
    printf("ADVANCED SEARCH\n");
    char str[50];
    int i,flag;
    printf("Enter keyword: ");
    scanf("%s",str);
    getchar();
    printf("\nSearch results: \n\n");
    flag=0;
    for(i=0; i<count; i++)
    {
        if(strstr(b[i].title,str) || strstr(b[i].author_name,str))
        {
            flag++;
            printarray(i);
            printf("\n");
        }
    }
    if(flag==0)
        printf("No result matching the keyword entered.\n");
}

void add()
{
    printf("ADD BOOK\n");
    int i=0, flag=0;
    while(b[i].ISBN!=0)
    {
        i++;
    }
    count++;
    b[i].ISBN = isvalid();
    printf("title:");
    gets(b[i].title);
    printf("author name:");
    gets(b[i].author_name);
    validquantity(i);
    validprice(i);
    validmonth(i);
    validyear(i);
    printf("Book added succefuly\n");
}

void del()
{
    printf("DELETE BOOK\n");
    books temp;
    int i,j, flag=0;
    long long int isbn;
    isbn = isvalid();

    for(i=0 ; i<count ; i++)
    {
        if(isbn == b[i].ISBN)
        {
            flag++;
        }
    }
    if(flag==0)
    {
        printf("Specified ISBN is not found.\n");
        del();
    }
    else
    {
        for(i=0 ; i<count ; i++)
        {
            if(isbn == b[i].ISBN)
            {
                temp = b[i];
                b[i] = b[count-1];
                b[count-1] = temp;
            }
        }
        count--;
    }
    printf("Book deleted succefully\n");
}

void modify()
{
    printf("MODIFY BOOK\n");
    long long int isbn;
    int i, flag=0;
    isbn = isvalid();

    for(i=0 ; i<count ; i++)
    {
        if(isbn == b[i].ISBN)
        {
            flag++;
            break;
        }
    }
    if(flag == 0)
    {
        printf("book not found.\n");
        modify();
    }
    else
    {
        printf("modify title:");
        gets(b[i].title);
        printf("modify author name:");
        gets(b[i].author_name);
        printf("modify ");
        validquantity(i);
        printf("modify ");
        validprice(i);
        printf("modify ");
        validmonth(i);
        printf("modify ");
        validyear(i);
        printf("Book modified succefully\n");
    }
}

void sortbytitle()
{
    int i,j;
    books temp;
    for(j=0; j<count; j++)
    {
        for(i=0; i<count-1; i++)
        {
            if(strcmp(b[i].title,b[i+1].title) > 0)
            {
                temp = b[i];
                b[i] = b[i+1];
                b[i+1] = temp;
            }
        }

    }
}

void sortbyprice()
{
    int i,j;
    books temp;
    for(j=0; j<count; j++)
    {
        for(i=0; i<count-1; i++)
        {
            if(b[i].price > b[i+1].price)
            {
                temp = b[i];
                b[i] = b[i+1];
                b[i+1] = temp;
            }
        }
    }
}

void sortbydate()
{
    int i,j;
    books temp;
    for(j=0; j<count; j++)
    {
        for(i=0; i<count-1; i++)
        {
            if( b[i].pd.year < b[i+1].pd.year)
            {
                temp = b[i];
                b[i] = b[i+1];
                b[i+1] = temp;
            }
            else if(b[i].pd.year == b[i+1].pd.year)
            {
                if(b[i].pd.month < b[i+1].pd.month)
                {
                    temp = b[i];
                    b[i] = b[i+1];
                    b[i+1] = temp;
                }
            }
        }
    }
}

void print()
{
    printf("PRINT BOOKS\n");
    int x,i;
    printf("1 for Sort by title.\n2 for Sort by price.\n3 for Sort by date.\n");
    printf("Please enter number of sort you want to use:");
    scanf("%d",&x);
    getchar();
    printf("\n");
    while(x <=0 || x >= 4)
    {
        printf("Please enter number of sort you want to use:");
        scanf("%d",&x);
    }
    switch (x)
    {
    case 1:
        sortbytitle();
        break;
    case 2:
        sortbyprice();
        break;
    case 3:
        sortbydate();
        break;
    default:
        return;
        break;
    }
    for(i=0; i<count; i++)
    {
        printarray(i);
        printf("\n");
    }
}

void save()
{
    printf("SAVE\n");
    int i;
    FILE *fsave;
    fsave = fopen("books.txt", "w");

    if(fsave == NULL)
    {
        printf("error in opening the file!");
        exit(1);
    }
    for(i=0 ; i<count ; i++)
    {
        fprintf(fsave, "%lld,%s,%s,%d,%f,%d-%d\n",
                b[i].ISBN, b[i].title, b[i].author_name, b[i].quantity, b[i].price, b[i].pd.month, b[i].pd.year);
    }
    printf("Your changes have been saved succesfuly/n");
    fclose(fsave);
}

void quit()
{
    char x[100];
    int check;
    do
    {
        printf("Quit\nAny unsaved changes will be discarded.\n");
        printf("1.Yes 2.No\nInput 1 or 2\n");
        gets(x);
        check = isint(x);
        if(check)
        {
            switch(atoi(x))
            {
            case 1:
                exit(1);
                break;
            case 2:
                return;
                break;
            default:
                check = 0;
                printf("Invalid Input\n");

            }
        }
    }
    while(check == 0 );
}



void menu()
{

    char x[100], y[100];
    int check;
    do
    {
        printf("MENU\n");
        printf("1.LOGIN 2.QUIT\nInput 1 or 2\n");
        gets(x);
        check = isint(x);
        if(check)
        {
            switch(atoi(x))
            {
            case 1:
                login();
                load();
                break;
            case 2:
                exit(1);
                break;
            default:
                check = 0;
                printf("Invalid Input\n");

            }
        }
    }
    while(check == 0 );

    while(1){
    do
    {
        printf("MENU");
        printf("\nInput the number of your choice:\n1.ADD\n2.DELETE\n3.MODIFY\n4.SEARCH\n5.ADVANCED SEARCH\n6.PRINT\n7.SAVE\n8.QUIT\n\n");
        gets(y);
        check = isint(y);
        if(check)
        {
            switch(atoi(y))
            {
            case 1:
                add();
                break;
            case 2:
                del();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                adv_search();
                break;
            case 6:
                print();
                break;
            case 7:
                save();
                break;
            case 8:
                quit();
                break;
            default:
                check = 0;
                printf("Wrong input please try again\n");
            }
        }
    }
    while(check == 0);}


}



int main()
{
    printf("WELCOME\n");
    menu();
    return 0;
}
