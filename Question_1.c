// Write a C code to group incoming bytes of serial data into an array of message strings.

/*  available functions
 *
 *   bool serial_available();
 *   returns True if Bytes are available in the buffer, False Otherwise
 *
 *   char serial_read();
 *   returns a single char(if available) and then deletes that char from the buffer
 *   blocks the code until a byte is not available
 *
 *   Bit-Flip Errors could be present in the message
 *
 *   Message structure (Comma Seprate ASCII)
 *   "$$,001,010,343,775,##"
 *   "$$" -> start, "##" -> end
 *   4 data strings of 3 digit "char"
 *   all messages of 21 - bytes
 */

#include <string.h>
#include <stdbool.h>

#define data_array_max_size 500

typedef struct
{
    int top;
    unsigned capacity;
    char *char_array;
} Channel_Stack;

Channel_Stack *createStack(unsigned capacity)
{
    Channel_Stack *stack = (struct Channel_Stack *)malloc(sizeof(Channel_Stack));
    if (stack == NULL)
    {
        pritnf("ERR : memory not allocated");
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->char_array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Channel_Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(Channel_Stack *stack)
{
    return stack->top == -1;
}

void push(Channel_Stack *stack, char item)
{
    if (isFull(stack))
        return;
    stack->char_array[++stack->top] = item;
}

char pop(Channel_Stack *stack)
{
    if (isEmpty(stack))
        return;
    return stack->char_array[stack->top--];
}

typedef struct
{
    char data[3]; // string
} channel[data_array_max_size];

channel channel1;
int channel1_current_length = -1;

bool serial_available();
char serial_read();

void loop(); // Assumed Superloop design pattern
void read_channel();    //Read the serial data unblockingly

Channel_Stack *channel1_stack;

int main()
{

    channel1_stack = createStack(43);

    while (1)
    {
        void loop();
    }
    return 0;
}

void loop()
{

    read_channel(channel1_stack);
}

void read_channel(Channel_Stack *stack)
{
    if (serial_available())
    {
        push(stack, serial_read());
    }
    if (stack->top >= 20)
    {
        if (('#' != stack->char_array[stack->top]) && ('#' != stack->char_array[stack->top - 1]))
        {
            channel1[channel1_current_length + 1].data[0] = stack->char_array[stack->top - 17];
            channel1[channel1_current_length + 1].data[1] = stack->char_array[stack->top - 16];
            channel1[channel1_current_length + 1].data[2] = stack->char_array[stack->top - 15];

            channel1[channel1_current_length + 2].data[0] = stack->char_array[stack->top - 13];
            channel1[channel1_current_length + 2].data[1] = stack->char_array[stack->top - 12];
            channel1[channel1_current_length + 2].data[2] = stack->char_array[stack->top - 11];

            channel1[channel1_current_length + 3].data[0] = stack->char_array[stack->top - 9];
            channel1[channel1_current_length + 3].data[1] = stack->char_array[stack->top - 8];
            channel1[channel1_current_length + 3].data[2] = stack->char_array[stack->top - 7];

            channel1[channel1_current_length + 3].data[0] = stack->char_array[stack->top - 5];
            channel1[channel1_current_length + 3].data[1] = stack->char_array[stack->top - 4];
            channel1[channel1_current_length + 3].data[2] = stack->char_array[stack->top - 3];

            channel1_current_length += 4;
            stack->top = -1;
        }

        if (stack->top == 42)
        {
            printf("Unexpected Error found");
            stack->top = -1;
        }
    }
}