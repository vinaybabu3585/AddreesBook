#include<stdio.h>
#include<string.h>
void copying(FILE*,FILE*);
void printing();
void add_contact();
void deleting();
void searching();
void editing();
struct address
{
    char name[20];
    char mobile[12];
    char email[20];
    char address[15];
};
int main()
{
    char ch='y';
    char opt;
    while(ch=='y' || ch== 'Y')
    {
        printf("1.Add details\n2.Search details\n3.Printing deatils\n4.Edit details\n5.Delete details\n6.Program terminate\nEnter the option: ");
        scanf(" %hhd",&opt);
        switch(opt)
        {
            case 1:add_contact();
                   break;
            case 2: searching();
                    break;
            case 3:printing();
                   break;
            case 4: editing();
                    break;
            case 5: deleting();
                    break;
            case 6: return 0;
            default: printf("Invalid!\n");
        }
        printf("Do you want to continue?(Y/N) ");
        scanf(" %c",&ch);
    }
}

void add_contact()
{
    FILE* fptr=fopen("data.csv","r");
    FILE* fptr1=fopen("temp.csv","w");
    struct address details;
    int count;
    fscanf(fptr,"%d\n",&count);
    count++;
    fprintf(fptr1,"%d\n",count);
    for(int i=0; i<count-1; i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
        fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);
    }
    char name_dup[30],email_dup[30];
    char mob_dup[12];
    printf("Enter the name: ");
    scanf(" %[^\n]",name_dup);
    int repeat=1;
    while(repeat)
    {

        printf("Enter the mobile: ");
        scanf(" %[^\n]",details.mobile);
        if(strlen(details.mobile)==10)
        {
            int i=0,flag=0;
            while(details.mobile[i]!='\0')
            {
                if(details.mobile[i]>='0'&& details.mobile[i]<='9')
                    flag++;
                i++;
            }
            if(flag==10)
            {
                strcpy(mob_dup,details.mobile);
                rewind(fptr);
                fscanf(fptr,"%d\n",&count);
                int record=0,k=0;
                for(int i=0; i<count; i++)
                {
                    k++;
                    fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                    if(strcmp(details.mobile,mob_dup)==0)
                    {
                        record=1;
                        break;
                    }
                }

                if(record==0)
                    repeat=0;
                else
                    printf("mobile number already exits\n");
            }
            else
                printf("Enter numbers only(0-9)\n");
        }
        else
            printf("Mobile number should be 10 digits and enter numbers(0-9) only\n");

    }
    repeat=1;
    while(repeat)
    {
        printf("Enter the Email: ");
        scanf(" %[^\n]",details.email);
        strcpy(email_dup,details.email);
        if(strstr(details.email,"@")!=NULL && strstr(details.email,".com")!=NULL)
        {
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            int record=0;
            for(int i=0; i<count; i++)
            {
                fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(strcmp(details.email,email_dup)==0)
                {
                    record=1;
                    break;
                }
            }
            if(record==0)
                repeat=0;
            else
                printf("Email number already exits\n");
        }
        else
            printf("Enter valid emial\n");
    }
    printf("Enter the Address: ");
    scanf(" %[^\n]",details.address);
    fprintf(fptr1,"%s,%s,%s,%s\n",name_dup,mob_dup,email_dup,details.address);
    fclose(fptr);
    fclose(fptr1);
    fptr=fopen("data.csv","w");
    fptr1=fopen("temp.csv","r");
    copying(fptr,fptr1);
    printf("Contact details added successfully!!\n");
    fclose(fptr);
    fclose(fptr1);
}

void editing()
 {
    FILE* fptr = fopen("data.csv", "r");
    FILE* fptr1 = fopen("temp.csv", "w");
    if (!fptr || !fptr1)
        {
        printf("Error opening files.\n");
        return;
    }

    char name[20];
    struct address details;
    printf("Enter the name: ");
    scanf(" %[^\n]", name);

    int count, flag = 0;
    fscanf(fptr, "%d\n", &count);
    fprintf(fptr1, "%d\n", count);

    char ch;
    for (int i = 0; i < count; i++)
        {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
        if (strcmp(details.name, name) == 0)
                {
            flag = 1;
            printf("What you want to change?\n1. Name\n2. Mobile\n3. Email\n4. Address\nEnter your choice: ");
            scanf(" %hhd", &ch);
            switch (ch)
                        {
                case 1:
                    printf("Previous Name: %s\n", details.name);
                    printf("Enter new name: ");
                    scanf(" %[^\n]", details.name);
                    break;
                case 2:
                    printf("Previous mobile number: %s\n", details.mobile);
                    int repeat = 1;
                    while (repeat)
                                        {
                        printf("Enter the new mobile: ");
                        scanf(" %[^\n]", details.mobile);
                        if (strlen(details.mobile) == 10 && strspn(details.mobile, "0123456789") == 10)
                                                {
                            repeat = 0;
                        }
                                                else
                                                {
                            printf("Mobile number should be 10 digits and consist of numbers (0-9) only.\n");
                        }
                    } while (1);
                    break;
                case 3:
                    printf("Previous Email: %s\n", details.email);
                    int rep = 1;
                    while (rep)
                                        {
                        printf("Enter the new Email: ");
                        scanf(" %[^\n]", details.email);
                        if (strstr(details.email, "@") != NULL && strstr(details.email, ".com") != NULL)
                                                {
                            rep = 0;
                        }
                                                else
                                                {
                            printf("Enter a valid email.\n");
                        }
                    }while (1);
                    break;
                case 4:
                    printf("Previous Address: %s\n", details.address);
                    printf("Enter the new Address: ");
                    scanf(" %[^\n]", details.address);
                    break;
                default:
                    printf("INVALID ENTRY\n");
                    fclose(fptr);
                    fclose(fptr1);
                    return;
            }
            fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile, details.email, details.address);
            printf("Changes saved successfully!\n");
        }
                else
                {
            fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile, details.email, details.address);
        }
    }

    fclose(fptr);
    fclose(fptr1);

    if (flag == 0)
        {
        printf("Name not found\n");
    }
        else
        {
        fptr = fopen("data.csv", "w");
        fptr1 = fopen("temp.csv", "r");
        if (fptr && fptr1)
                {
            copying(fptr, fptr1);
        }
        fclose(fptr);
        fclose(fptr1);
    }
}

void searching()
{
    FILE* fptr=fopen("data.csv","r");

    char name[20];
    printf("Enter the name: ");
    scanf(" %[^\n]",name);

    int count,count2=0,record=0;
    struct address details,dup;

    fscanf(fptr,"%d\n",&count);
    for(int i=0;i<count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
        if(strcmp(details.name,name)==0)
            count2++;
        if(count2==1 && record==0)
        {
            dup=details;
            record=i+1;
        }
        else if(count2>1)
        {
            record=i;
            printf("Similar name found\n");
            break;
        }
    }
    if(count2==0)
    {
        printf("Name not found!!\n");

    }
    else if(count2==1)
    {

        printf("\n---------------------------- Available Details ----------------------------\n");
        printf(" %-7s%-15s%-15s%-25s%-30s\n", "Sl.No.","Name", "Mobile", "Email", "Address");
        printf("---------------------------------------------------------------------------\n");
        printf(" %-7d%-15s%-15s%-25s%-30s\n",record, dup.name, dup.mobile, dup.email, dup.address);
        printf("---------------------------------------------------------------------------\n");
    }

    else
    {

        printf("Search by:\n1.Mobile number\n2.Email ID\nEnter choice: ");
        int ch1;
        scanf(" %d",&ch1);
        switch(ch1)
        {
            case 1: char mobile[12];
                    int v=1;
                    while(v)
                    {
                        printf("Enter the mobile number: ");
                        scanf(" %[^\n]",mobile);
                        if(strlen(mobile)==10)
                        {
                            int i=0,flag=0;
                            while(details.mobile[i]!='\0')
                            {
                                if(mobile[i]>='0'&& mobile[i]<='9')
                                    flag++;
                                i++;
                            }
                            if(flag==10)
                                v=0;
                            else
                                printf("Enter numbers only\n");

                        }
                        else
                            printf("Enter 10 digits only\n");
                    }
                    rewind(fptr);
                    fscanf(fptr,"%d\n",&count);
                    for(int i=0;i<count; i++)
                    {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
                        if(strcmp(details.mobile,mobile)==0 && strcmp(details.name,name)==0)
                        {
                            printf("\n---------------------------- Available Details ----------------------------\n");
                            printf(" %-7s%-15s%-15s%-25s%-30s\n", "Sl.No.","Name", "Mobile", "Email", "Address");
                            printf("---------------------------------------------------------------------------\n");
                            printf(" %-7d%-15s%-15s%-25s%-30s\n",i+1, details.name, details.mobile, details.email, details.address);
                            printf("---------------------------------------------------------------------------\n");
                                                        fclose(fptr);
                                                        return;
                                                }
                                        }

                                                break;

            case 2: char email[30];
                    int x=1;
                    while(x)
                    {
                        printf("Enter the Email: ");
                        scanf(" %[^\n]",email);
                        if(strstr(email,"@")!=NULL && strstr(email,".com")!=NULL)
                                                {
                            x=0;
                                                }
                        else
                                                {
                            printf("Enter valid emial\n");
                                                }
                    }

                    rewind(fptr);
                    fscanf(fptr,"%d\n",&count);
                    for(int i=0;i<count; i++)
                    {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
                        if(strcmp(details.email,email)==0 && strcmp(details.name,name)==0)
                        {
                            printf("\n---------------------------- Available Details ----------------------------\n");
                            printf(" %-7s%-15s%-15s%-25s%-30s\n", "Sl.No.","Name", "Mobile", "Email", "Address");
                            printf("---------------------------------------------------------------------------\n");
                            printf(" %-7d%-15s%-15s%-25s%-30s\n",i+1, details.name, details.mobile, details.email, details.address);
                            printf("---------------------------------------------------------------------------\n");
                                                        fclose(fptr);
                                                        return;
                        }
                                                else
                                                {
                                printf("Data not found!!\n");
                                break;
                                                }
                                        }
                                        break;
            default: printf("Invlaid choice\n");
                     break;
        }
    }

    fclose(fptr);
}

void printing()
{
    FILE* fptr=fopen("data.csv","r");
    int count;
    fscanf(fptr,"%d\n",&count);
    struct address details;
    printf("\n---------------------------- Available Details ----------------------------\n");
    printf(" %-7s%-15s%-15s%-25s%-30s\n","Sl.No.","Name", "Mobile", "Email", "Address");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
        printf(" %-7d%-15s%-15s%-25s%-30s\n",i+1, details.name, details.mobile, details.email, details.address);
    }
    printf("---------------------------------------------------------------------------\n");
    fclose(fptr);
}

void deleting()
{

    FILE* fptr=fopen("data.csv","r");
    FILE* fptr1=fopen("temp.csv","w");
    char name[20];
    printf("Enter the name: ");
    scanf(" %[^\n]",name);
    int count,save,flag=0;
    struct address details;
    fscanf(fptr,"%d\n",&count);
    for(int i=0; i<count;i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
        if(strcmp(name,details.name)==0)
            flag++;
    }
    if(flag==0)
    {
        fclose(fptr);
        fclose(fptr1);
        printf("Name not found\n");
    }
    else if(flag==1)
    {
        rewind(fptr),rewind(fptr1);
        fscanf(fptr,"%d\n",&count);
        fprintf(fptr1,"%d\n",count-1);
        int copy=0;
        for(int i=0;i<count; i++)
        {
            fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
            if(strcmp(details.name,name)==0)
            {
                printf("Do you want to delete?(Y/N) : ");
                char a;
                scanf(" %c",&a);
                if(a=='N'|| a=='n')
                {
                    fclose(fptr);
                    fclose(fptr1);
                    return;
                }
                copy=1;
            }
            else
                fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);

        }
        fclose(fptr);
        fclose(fptr1);
        FILE* fptr=fopen("data.csv","w");
        FILE* fptr1=fopen("temp.csv","r");
        copying(fptr,fptr1);
        fclose(fptr);
        fclose(fptr1);

        printf("Contact deleted successfully\n");

    }
    else
    {
        printf("Similar name found\nSearch by\n1.Mobile number\n2.Email Id\nEnter choice: ");
        int opt;
        scanf(" %d",&opt);
        switch(opt)
        {
            case 1: char mob[12];
                    int a=1;
                    while(a)
                    {
                        printf("Enter mobile number: ");
                        scanf(" %[^\n]",mob);
                        int i=0,flag=0;
                        if(strlen(mob)==10)
                        {
                            while(mob[i]!='\0')
                            {
                                if(mob[i]>='0'&& mob[i]<='9')
                                flag++;
                                i++;
                            }
                            if(flag==10)
                                a=0;
                            else
                                printf("Enter number only\n");
                        }
                        else
                            printf("Entry should be 10 digit number\n");
                    }
                    rewind(fptr),rewind(fptr1);
                    flag=0;
                    fscanf(fptr,"%d\n",&count);
                    fprintf(fptr1,"%d\n",count-1);
                    for(int i=0; i<count;i++)
                    {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
                        if((strcmp(mob,details.mobile)==0)&&(strcmp(name,details.name)==0))
                        {
                            flag=1;
                            printf("Do you want to delete?(Y/N) ");
                            char a;
                            scanf(" %c",&a);
                            if(a=='N'|| a=='n')
                            {
                                fclose(fptr);
                                fclose(fptr1);
                                return;
                            }
                        }
                        else
                            fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);

                    }
                    fclose(fptr);
                    fclose(fptr1);
                    if(flag==0)
                        printf("Contact not found\n");

                    else
                    {
                        FILE* fptr=fopen("data.csv","w");
                        FILE* fptr1=fopen("temp.csv","r");
                        copying(fptr,fptr1);
                        fclose(fptr);
                        fclose(fptr1);
                        printf("Contact deleted successfully\n");
                    }
                    break;
            case 2: char emai[30];
                    int y=1;
                    while(y)
                    {
                        printf("Enter the Email: ");
                        scanf(" %[^\n]",emai);
                        if(strstr(emai,"@")!=NULL && strstr(emai,".com")!=NULL)
                            y=0;

                        else
                            printf("Enter valid emial\n");
                    }
                    rewind(fptr),rewind(fptr1);
                    flag=0;
                    fscanf(fptr,"%d\n",&count);
                    fprintf(fptr1,"%d\n",count-1);
                    for(int i=0; i<count;i++)
                    {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
                        if((strcmp(emai,details.email)==0)&&(strcmp(name,details.name)==0))
                        {

                            flag=1;
                            printf("Do you want to delete?(Y/N) ");
                            char a;
                            scanf(" %c",&a);
                            if(a=='N'|| a=='n')
                            {
                                fclose(fptr);
                                fclose(fptr1);
                                return;
                            }
                        }
                        else
                            fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);

                    }
                    fclose(fptr);
                    fclose(fptr1);
                    if(flag==0)
                        printf("Contact not found\n");
                    else
                    {
                        FILE* fptr=fopen("data.csv","w");
                        FILE* fptr1=fopen("temp.csv","r");
                        copying(fptr,fptr1);
                        fclose(fptr);
                        fclose(fptr1);
                        printf("Contact deleted successfully\n");
                    }
                    break;

            default:printf("Invald uption\n");
                    break;
        }
    }
}
void copying(FILE* fptr,FILE* fptr1)     //copyind data from temp file to data file
{
    char ch;
    while((ch=fgetc(fptr1))!=EOF)
    {
        fputc(ch,fptr);
        }
}
