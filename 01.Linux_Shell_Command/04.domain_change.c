#include <stdio.h>
#include <string.h>


int isEmailUpdated(const char* email) {
    const char* oldDomain = "@kaaj.com";
    int emailLength = strlen(email);
    int oldDomainLength = strlen(oldDomain);
    
    if (emailLength < oldDomainLength) {
        return 1; 
    }
    const char* emailDomain = email + emailLength - oldDomainLength; // const char cannnot be modified
    if (strcmp(emailDomain, oldDomain) == 0) {
        printf(emailDomain);
        return 0; 
    }
    return 1;
}

int main() {
    char email[100];
    
    printf("Enter email address: ");
    scanf("%s", email);
    
    int isUpdated = isEmailUpdated(email);
    if (isUpdated) {
        printf("Email address is okay\n");
    } else {
        printf("Email address is outdated\n");
    }
    
    return 0;
}

