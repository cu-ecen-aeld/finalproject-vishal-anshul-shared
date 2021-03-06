#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>


#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

//#define SIGALRM_HANDLER     1

static int timer_up = 0;
//char *sensor_data[] = {"T:15.40,H:10.0","T:15.50,H:11.0","T:15.60,H:12.0","T:16.12,H:13.0","T:17.54,H:14.0","T:18.12,H:15.0"};
char *sensor_data[] ={"T:15.40,H:10.00,IR:65530,FULL:65531,VIS:65532", "T:16.12,H:13.00,IR:65533,FULL:65534,VIS:65535"};
/***********************************************************************************************
* Name          : func
* Description   : function for server- client communication 
* Parameters    : sockfd
* RETURN        : N/A
***********************************************************************************************/
void func(int sockfd)
{
    int rt = 0;
 
    while(1) 
    {
    	
         for(int i = 0; i < 2; i++){   
            
            rt = write(sockfd, sensor_data[i], strlen(sensor_data[i])); // send the message to client
            if(rt < 0){
                perror("Server_Error:");
                return;
            }else if(rt != strlen(sensor_data[i])){
                printf("partial sent bytes:%d\r\n",rt);
            }

            printf("sent bytes:%d\r\n",rt);

            timer_up = 0;
            
            sleep(3);

            //delay
            // for(int i=0;i<100000;i++){
            //     for(int j=0;j<100000;j++){
            //         ;
            //     }
            // }



        }

    }
}

/***********************************************************************************************
* Name          : timer_handler
* Description   : function for SIGALRM handler 
* Parameters    : signal no.
* RETURN        : N/A
***********************************************************************************************/
#ifdef SIGALRM_HANDLER
static void timer_handler(int sig_no){

    /*first store the local time in a buffer*/
    char time_string[200];
    time_t ti;
    struct tm *tm_ptr;
    int timer_len = 0;

    ti = time(NULL);
    tm_ptr = localtime(&ti);
    if(tm_ptr == NULL){
        perror("Local timer error!");
        exit(EXIT_FAILURE);
    }

    timer_len = strftime(time_string,sizeof(time_string),"timestamp:%d.%b.%y - %k:%M:%S\n",tm_ptr);
    if(timer_len == 0){
        perror("strftimer returned 0!");
        exit(EXIT_FAILURE);
    }

    printf("time value:%s\n",time_string);

    timer_up = 1;
    printf("timer_up_1:%d\r\n",timer_up);

} 
#endif       
 /***********************************************************************************************
* Name          : Main
* Description   : Entry point function
* Parameters    : N/A
* RETURN        : N/A
***********************************************************************************************/
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    printf("***Starting Server program Version Humidity...***\n");

    #ifdef SIGALRM_HANDLER

    /*Registering SIGARM */
    signal(SIGALRM,timer_handler);

    /*Timer handler part*/
    struct itimerval inter_timer;

    inter_timer.it_interval.tv_sec = 5; //timer interval of 10 secs
    inter_timer.it_interval.tv_usec = 0;
    inter_timer.it_value.tv_sec = 5; //time expiration of 10 secs
    inter_timer.it_value.tv_usec = 0;

    //arming the timer, choosing wall clock, not storing in old_value
    int tm_ret = setitimer(ITIMER_REAL, &inter_timer, NULL);
    if(tm_ret == -1){
        printf("timer error:%s\n",strerror(errno));
        syslog(LOG_DEBUG,"timer error:%s",strerror(errno));
    }

    #endif
   
    // 1. create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    {
        printf("Error! socket() creation failed\n");
        exit(0);
    }
    else
    {
        printf("socket() creation succeeded \n");
    }
    bzero(&servaddr, sizeof(servaddr)); // reset string
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // 2. Bind the socket
    
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))) == -1) {
        printf("socket opt failed...\n");
        exit(0);
    }
    else
        printf("Socket opt succeeded..\n");
        
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf("Error! bind() socket failed\n");
        exit(0);
    }
    else
    {
        printf("bind() socket succeeded\n");
    }
   
    // 3. Listen on the socket
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Error! Socket Listen failed\n");
        exit(0);
    }
    else
    {
         printf("Socket Listen succeeded. Server Listening..\n");
    }

    len = sizeof(cli);
   
    //4. Accept the socket  
    connfd = accept(sockfd, (SA*)&cli, (unsigned int *)&len);
    if (connfd < 0) 
    {
        printf("Error: accept() socket failed\n");
        exit(0);
    }
    else
    {
        printf("accept() socket succeeded\n");
    }
   
    //5. Call to function for server- client communication
    func(connfd);
   
    //6. Close the socket
    close(sockfd);
}
