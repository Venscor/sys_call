#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

/*system call ID ,233 in 32-bit machine is not in use,
  while in 64-bit machine none found,so this is just like hacking system call
  find it->cat /proc/kallsyms | grep sys_call_table
*/
#define CALL_ID 316   
/*address for sys_call_table,varies from different system
  find it: $ locate unistd_64
 */
#define SYS_CALL_TABLE_ADDRESS 0xffffffff81801680 
unsigned int clear_and_return_cr0(void);
void setback_cr0(unsigned int val);

int orig_cr0;
unsigned long *sys_call_table = 0;
static int (*anything_saved)(void);
 
MODULE_AUTHOR("Venscor");
MODULE_LICENSE("GPL");

unsigned int clear_and_return_cr0(void)
{
    unsigned int cr0 = 0;
    unsigned int ret;

    asm volatile ("movq %%cr0, %%rax": "=a"(cr0));
    ret = cr0;

    /*clear the 20th bit of CR0,*/
    cr0 &= 0xfffeffff;
    asm volatile ("movq %%rax, %%cr0":: "a"(cr0));
    return ret;
}

void setback_cr0(unsigned int val)
{
    asm volatile ("movq %%rax, %%cr0"::"a"(val));
}

void pstreea(struct task_struct* p,int b){
	int i;
	struct list_head* l;	
	for(i=1;i<=b;i++)
		printk("           ");
	printk("|----------%s\n",p->comm);
	for (l = p->children.next; l!= &(p->children);l = l->next){
		/*used for get task_struct,deal from parent to children*/
		struct task_struct*t=list_entry(l,struct task_struct,sibling);
		pstreea(t,b+1);                                         
	}
}

asmlinkage void sys_mycall(void)
{
   struct task_struct* p;
	int b=0;
	printk("\n		********Kernel:print ps tree********\n");
	/*traverse from child to parent,finally init*/
	for ( p = current; p != &init_task; p = p->parent ) ;
		pstreea(p,b);
   	printk("\n		***********************over***********************\n");
}


int __init init_addsyscall(void)
{
    printk("\n****By Venscor:Come in Kernel*****\n");
    sys_call_table = (unsigned long *)SYS_CALL_TABLE_ADDRESS;

    anything_saved = (int(*)(void))(sys_call_table[CALL_ID]);
    orig_cr0 = clear_and_return_cr0();
    sys_call_table[CALL_ID] = (unsigned long)&sys_mycall;
    setback_cr0(orig_cr0);
    return 0;
}

void __exit exit_addsyscall(void)
{
    orig_cr0 = clear_and_return_cr0();
    sys_call_table[CALL_ID] = (unsigned long)anything_saved;
    setback_cr0(orig_cr0);
    printk("\n****By Venscor:system_call exit!****\n");
}
module_init(init_addsyscall);
module_exit(exit_addsyscall);
