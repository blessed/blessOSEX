unsigned int user_stack[4096 >> 2];
struct {
    unsigned int *a;
    unsigned short b;
} stack_start = { &user_stack[4096 >> 2], 0x10 };


void main(void)
{
    while (1)
        __asm__("nop");
}
