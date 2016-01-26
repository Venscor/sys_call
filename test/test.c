#include<stdio.h>
/**
 *wrap system call for user;
 */
void print_pid()
{
    syscall(316);
    printf("*********sys_call to print ps tree*********\n");
    system("dmesg |tail -500|grep \"\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*over\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\" -B 500|grep \"\*\*\*\*\*\*\*\*Kernel:print ps tree\*\*\*\*\*\*\*\*\" -A 500");	
}
int main()
{
    print_pid();
    return 0;
}        
