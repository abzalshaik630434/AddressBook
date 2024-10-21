/*Name   :Shaik Abzal
 batch No: 24021G
 description:AdressBook project work same as like phone contact */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <stdio_ext.h>
void listContacts(AddressBook *addressBook) 
{
   // printf("abzal\n");
    // Sort contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%20s\t",addressBook->contacts[i].name);
        printf("%20s\t",addressBook->contacts[i].phone);
        printf("%20s\n",addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) { //for dummy contacts
    addressBook->contactCount = 0;
   populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
   // saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validateName(char *name)                   //name validation
{
   for(int i=0;name[i] != '\0';i++)
   {
    if(isdigit(name[i]))                  
     {
        printf("Please enter alphabets only.\n");
        return 0;
     }
   }
   return 1;
}
int uniq(char *phone, AddressBook *addressBook) //checking for same number presnt or not
{
    for(int i=0;i< addressBook->contactCount;i++)  //for loop to run upto contact count
    {
        if(strcmp(addressBook->contacts[i].phone,phone)== 0) //comparision b/w searched name with stored contacts name if found the value becomes 0.
        {
            return 1;                   
        } 
    }
    return 0;
}
int validatePhone(char *phone)       //phone number validation
{
    int len = strlen(phone);
    if(len != 10)
    {
       printf("Please enter 10 digits.\n");
       return 0;
    }
    for(int i=0;phone[i] != '\0';i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("Please enter digits only.\n");
            return 0;
        }
    }
    return 1;
}
int uniq_email(char *email, AddressBook *addressBook) //checking for same mail present or not
{
    for(int i=0;i< addressBook->contactCount;i++)  //for loop to run upto contact count
    {
        if(strcmp(addressBook->contacts[i].email,email)== 0) //comparision b/w searched name with stored contacts name if found the value becomes 0.
        {
            return 1;                   
        } 
    }
    return 0;
}
int validateMail(char *email)     //email validation
{
  // Make sure to include this for strstr()

//int validate_email(char *email)
    int count = 0,flag=0;
    int count1 = 0;

    // Check if the email contains '@'
    char *temp1=strchr(email,'@');
    char *temp2=strstr(email,".com");
    if(temp2 - temp1 < 2)
    {
        printf("Invalid email formate please check\n");
        return 0;
    }
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            count++;
            
        }
    }
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i]>= 'A' && email[i]<='Z')
         {
            printf("Please enter lowercase only\n");
            flag=1;
            break;
               
        }
    }
    if(flag==1)
    {
        return 0;
    }
    // Check if the email contains ".com"
    if (strstr(email, ".com") != NULL) {
       count1++;
    }
    if (count ==1 && count1==1) {
        return 1; // Valid email
    } else {
        printf("Invalid email format. Please include '@' and end with '.com'.\n");
        return 0; // Invalid email
    }


}

void createContact(AddressBook *addressBook)
{
    int flag=0;
    if(addressBook->contactCount >= MAX_CONTACTS)   //checking contact count
    {
        printf("You reached MAX contacts.No space!");
        return;
    }

	Contact newcon;
    //getchar();

    printf("Enter the name:");
    do{
        getchar();
    scanf("%[^\n]",newcon.name);
    }while(!validateName(newcon.name));  
    flag = 1;
    do {
    printf("Enter the phone number:");
    getchar();
    scanf("%s",newcon.phone);
    if(validatePhone(newcon.phone)==1)
    {
        
         flag=0;
    }
    if( uniq(newcon.phone,addressBook))
    {
          printf("Already number existed.please enter new number\n");
        flag=1;
    }
    } while(flag);
    do {
        getchar();
    printf("Enter the mail id:");
    scanf("%s",newcon.email);

    if(validateMail(newcon.email)==1)
     {
        flag=0;
     }
     else
     {
        flag=1;
     }
     if(uniq_email(newcon.email,addressBook))
     {
        printf("Already email existed.Please enter new mail\n");
        flag=1;
     }
    } while(flag);
    
    addressBook->contacts[addressBook->contactCount] = newcon;  
    addressBook->contactCount++;

    printf("Your Contact Saved Successfully.\n");
}

void searchContact(AddressBook *addressBook) //for searching contact presnt or not
{
    int opt,flag=0;
    printf("Please choose one option to search by:\n");
    printf("1.Name\n2.Phone Number\n3.Email id:\n");
    printf("Enter your choice : ");
    scanf("%d",&opt);
    
    switch(opt)
    {
        case 1: 
        {
            char searchName[50];
                getchar();
                printf("Enter the name to search:");
                scanf("%[^\n]",searchName);
                if(!validateName(searchName)) 
                {
                    return;
                }
                for(int i=0;i< addressBook->contactCount;i++)  //for loop to run upto contact count
                {
                if(strcmp(addressBook->contacts[i].name,searchName)== 0) //comparision b/w searched name with stored contacts name if found the value becomes 0.
                {
                    printf("%s\t",addressBook->contacts[i].name);
                    printf("%s\t",addressBook->contacts[i].phone);
                    printf("%s\t",addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
                }
                break;
        }
        case 2: 
        {       char searchPhone[15];
                getchar();
                printf("Enter the phone number to search:");
                scanf("%s",searchPhone);
                if(!validatePhone(searchPhone))
                {
                    return;
                }

                 for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, searchPhone) == 0) 
                {
                    printf("%s\t", addressBook->contacts[i].name);
                    printf("%s\t", addressBook->contacts[i].phone);
                    printf("%s\t", addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        case 3: 
        {       char searchMail[50];
                getchar();
                printf("Enter the email id to search:");
                scanf("%s",searchMail);
                if(!validateMail(searchMail))
                {
                    return;
                }

                for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, searchMail) == 0) 
                {
                    printf("%s\t", addressBook->contacts[i].name);
                    printf("%s\t", addressBook->contacts[i].phone);
                    printf("%s\t", addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        default: printf("Invalid choice. please select above choices only.\n");
        break;
    }
    if(flag == 0)
    {
        printf("Your searching contact is not available.\n");
    }
}

void validate_editName(Contact *contact)   //editing contact name
{
    printf("Enter the new name to save: ");
    getchar(); 
    scanf("%[^\n]", contact->name);

    if (!validateName(contact->name))
    {
        printf("Invalid name format. Name not updated.\n");
        return;
    }
    printf("Name successfully modified.\n");
}

void validate_editPhone(Contact *contact)   //editing contact phone number
{
    do {
        printf("Enter the new mobile number to save: ");
        scanf("%s", contact->phone);
    } while (!validatePhone(contact->phone));

    printf("Phone number successfully modified.\n");
}

void validate_editEmail(Contact *contact)   //editing contact email
{
    do {
        printf("Enter the new email ID to save: ");
        scanf("%s", contact->email);
    } while (!validateMail(contact->email));

    printf("Email ID successfully modified.\n");
}

void editContact(AddressBook *addressBook) // for contact
{
    int opt, flag = 0;
    printf("Please select an option to edit contact:\n");
    printf("1. Name\n2. Phone Number\n3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    
    switch (opt)
    {
        case 1: 
        {       
            char searchName[50];
            getchar();
            printf("Enter the name of the contact you want to edit: ");
            scanf("%[^\n]", searchName);
            
            if (!validateName(searchName))
            {
                printf("Invalid name format.\n");
                return;
            }
            
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, searchName) == 0)
                {
                    validate_editName(&addressBook->contacts[i]);
                    flag = 1; 
                    break;
                }
            }
            
            if (!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        case 2: 
        {       
            char searchPhone[15];
            getchar();
            do {
                printf("Enter the phone number of the contact you want to edit: ");
                scanf("%s", searchPhone);
            } while (!validatePhone(searchPhone));
            
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
                {
                    validate_editPhone(&addressBook->contacts[i]);
                    flag = 1; 
                    break;
                }
            }
            
            if (!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        case 3: 
        {       
            char searchMail[50];
            getchar();
            do {
                printf("Enter the email ID of the contact you want to edit: ");
                scanf("%s", searchMail);
            } while (!validateMail(searchMail));
            
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, searchMail) == 0)
                {
                    validate_editEmail(&addressBook->contacts[i]);
                    flag = 1; 
                    break;
                }
            }
            
            if (!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        default: 
            printf("Invalid option, please select one of the above options only.\n");
    }
}

void deleteContact(AddressBook *addressBook) //for deleting contact 
{
    int opt, flag = 0;
    printf("Please choose one option to Delete by:\n");
    printf("1. Name\n2. Mobile Number\n3. Email Id:\n");
    printf("Your choice: ");
    scanf("%d", &opt);
    // getchar();
    __fpurge(stdin) ;
    switch (opt)
    {
        case 1: 
        {
            char searchName[50];
            //getchar();
            // printf("Name of the Contact you want to delete: ");
           //scanf("%[^\n]", searchName);

             do {
                printf("Enter name of the contact you want to delete: ");
               // getchar();
               __fpurge(stdin);
                scanf("%[^\n]", searchName);

            } while (!validateName(searchName)); //for name

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, searchName) == 0)
                {
                    for (int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1; 
                    break;
                }
            }
            if (flag)
            {
                printf("Contact deleted successfully.\n");
            }
        }
        break;

        case 2: 
        {
            char searchPhone[15];
            do {
                printf("Phone number of the contact you want to delete: ");
                scanf("%s", searchPhone);
            } while (!validatePhone(searchPhone)); //for phone

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
                {
                    for (int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1; 
                    break;
                }
            }
            if (flag)
            {
                printf("Contact deleted successfully.\n");
            }
        } break;

        case 3: 
        {
            char searchMail[30];
            do {
                printf("Enter the Email id of the contact you want to delete: ");
                scanf("%s", searchMail);
            } while (!validateMail(searchMail)); //for email

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, searchMail) == 0)
                {
                    for (int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1; 
                    break;
                }
            }
            if (flag)
            {
                printf("Contact deleted successfully.\n");
            }
        } break;
        default:
            printf("Invalid option! Please select from the above options only.\n");
            break;
}
}