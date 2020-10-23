#include <unistd.h> 
#include <stdio.h> 
#include <pwd.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char const *argv[]) 
{   
    int valread;
    char buffer[1024] = {0}; 
    char *hello = "Hello from server";
    int setid;
    struct passwd* pwd;
    long uid = 65534; // user nobody in Unix systems 

    // Getting the user id for nobody user
    pwd = getpwnam("nobody");
    if (pwd != NULL) {
      uid = (long)pwd->pw_uid;
    }

    printf("inside child process after exec\n");

    printf("The nobody user is uid:%ld\n",uid);

    setid = setuid(uid); 
    if(uid == -1){
	printf("Error in setting the user to nobody user while dropping privileges\n");
        exit(0);
    }

    valread = read( *argv[1] , buffer, 1024);
    printf("%s\n",buffer ); 
    send( *argv[1] , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    printf("Finished exec process by child\n");
    return 0; 
} 
