/* Steven Volocyk, Lecture 001
This program calculates if a number is a prime number
while demonstrating how alarm interrupts are handled in C
by the usage of alarms, and handleres for said alarms that print out
the current time. 
*/

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

time_t currTime; // global variable for current time.

// catch for Ctrl + C keyboard command.
void handle_SIGINT()
{
  printf("\nProgram will now teriminate\n");
  exit(1);
}
// handler function for the alarm that prints the time
// and re-arms the alarm.
void handle_SIGALRM(int sig) {
    currTime = time(0);
    printf("\nCurrent time = %s", ctime(&currTime));
    alarm(1);
}

int main(int argc, char* argv[]) {
    int first = 1;  // used to determine first iteration of while loop
    int hugeNumber = 1000001; // given starting number.
    int divisor = 0, prime = 1, next_num = 0;
    int result = 0;

    if (argc != 1) {
        fprintf(stderr, "Invalid Input. Correct Usage: simplealarm\n");
        exit(1);
    }  
    
    struct sigaction new_handler, alarm_handler; //sigactions for alarm + ctrlC

    new_handler.sa_handler = handle_SIGINT; //handler declare for sigint
    if (sigemptyset(&new_handler.sa_mask) != 0) { 
        printf("sigemptyset failure, will now exit.");
        exit(1);
    }
    if ((sigaction(SIGINT, &new_handler, NULL) != 0)) {
        printf("sigaction failure, will now exit.");
        exit(1);
    }

    if (sigemptyset(&alarm_handler.sa_mask) != 0) {
        printf("sigaction failure, will now exit.");
        exit(1);
    }
    alarm_handler.sa_flags = 0;
    alarm_handler.sa_handler = handle_SIGALRM;
    if ((sigaction(SIGALRM, &alarm_handler, NULL) != 0)) {
        printf("sigaction failure, will now exit.");
        exit(1);
    }
    
    divisor = (hugeNumber - 1);
    alarm(1); // initial alarm priming.

    //loop for calculating prime number. 
    while (1) {
        if (first == 1) {
            fprintf(stderr, "Enter ^C to end the program:\n");
        }
        if (next_num == 1) {
            hugeNumber = hugeNumber + 1;
            divisor = (hugeNumber - 1);
            next_num = 0;
            prime = 1;
        }
        result = (hugeNumber % divisor);
        if (result == 0) {
            prime = 0; 
            next_num = 1;
        }
        divisor = divisor - 1; 
        if(divisor == 1) {
            next_num = 1;
            if (prime == 1) {
            printf("%d", hugeNumber);
            printf(" ");
            }
        } 
        first = 0; 
    }
    return(0);
}