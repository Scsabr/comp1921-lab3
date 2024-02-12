# COMP1921 Lab 3 - Functions

You can see in `code.c` you have a basic library system. You can compile and run this - it should work.

Feel free to test it out now

```bash
# reminder

gcc code.c -o library
./library
```

You might also want to make yourself a little bash script to compile and run the code for you as you will be recompiling it a lot - or you could go and grab the makefile I gave you in the mini-lesson and adapt it for this code.

This week will be less from me, more from you - you've seen functions before, and you should have some familiarity with them. There will be a short section below explaining how functions work in C, but this is more a refresher and less new content.

# Task

`code.c` is a program which would benefit from some **functions**. Right now, it's very long and has a lot of repeated code.

Your task is to improve the code by moving some of the code out into new functions. You should ensure that the code still works at the end. Aim for 3-10 functions, with a main() about 50 lines long (not including comments).

You might also want to make some tests (unit tests with assert() if you're really feeling fancy), find some of the weaknesses in the code, and add a bit of extra validation as it's not very robust at the moment.

If you want some more C practice, you could also:
- let it read in books from file
- write out the books to file so they're saved

## Top Tips

- Do one function at a time, and recompile and rerun every time.
- Don't try and do too much in 1 function - remember single responsibility
- **make a backup of the original code!**

You will almost certainly at some point realise you have gone wrong and want to remind yourself of the previous code - make yourself a copy:
```bash
cp code.c backup.c
```

C expects your functions to be declared before you use them - but you might want to put functions below the main() to keep things tidy.

To do this, you should put a **function declaration** at the top of your code:

```c
// these are declarations
int add(int x, int y);
int subtract(int x, int y);

int main()
{
    ...
}

// then you can define the function later - just make sure you use the same argument names.
int add (int x, int y)
{
    return x+y;
}
```


## Refresher

Functions are pieces of code which you can run multiple times by calling them in your code.

A function has three things:
- Arguments (inputs): what you need to give the function for it to work on
- Functionality (what it does): the code inside the function, which will do something to whatever arguments you give it
- Return (output): a single value (int, char, struct- any variable) which the function will send back as its value when it finishes running

```c
/*
 * A basic function which returns the sum of two numbers, passed to it as arguments.
 */
int add(int x, int y)
{
    int sum = x+y;
    return sum;
}
```

Above is a simple function, `add()`. When you pass in two numbers, it will add them together and return the result:

```c
int main()
{
    int num1 = 5, num2 = 7;
    int answer = add(5,7);
}
```

So if this code was run, `answer` would hold the value 12, as that is what has been **returned** from `add()`.

You're allowed to have functions with **no** arguments or **no** return, for example:
```c
void show_menu()
{
    printf("Option 1\nOption 2\nOption 3");
}
```

`void` means that the function doesn't have a return value- this is what we call a procedure, a function with no return. This is fine, and is mostly used for things like display functions.

Empty brackets `()` after the function name mean it has no arguments. This is almost exclusively used for display functions or for the main() - you usually want to be passing some data in to a function.

## Making a function

First of all, think about what you're putting into the function.
- What data does it need? Are there any variables it is working on?
- What does it actually do?
- Does it return something which you need in the rest of your code?

Then come up with a good name for the function. This should be descriptive, and follow whatever case you have used in your code (snake_case for the python_enjoyers, camelCase for the cFans).

When you're working with existing code, it's basically a case of working out what chunk you want to grab. Let's take one from the task:

```c
fgets(inventory[numBooks].title, 100, stdin);
len = strlen(inventory[numBooks].title);
if (len > 0 && inventory[numBooks].title[len - 1] == '\n')
{
    inventory[numBooks].title[len - 1] = '\0';
}
```

This is a classic example, as it's something which is used about 5 times in the code and has a variable name in 4 places.

First, we think about a name, what goes in, and what comes out:
- for the name, I just describe the function - it gets a string, so getString() seems sensible
- for the arguments, there's two things:
    1. the max length is different in places, so we should pass that in
    2. because of how strings are in C, it's usually better to pass in where you want the string to end up rather than trying to return it - alternative version provided below to show why this is more difficult.
- and we don't need a return, so we make it a `void`

(If I was being fancy, I would make it return an int for validation as a user could potentially enter nothing - feel free to add this!)

```c
void getString(int max_lengt, char* destination)
{
    ...
}
```

Now we just slightly adapt the code - **this always involves trial and error!**.

```c
void getString(int max_length, char* destination)
{
    fgets(destination, max_length, stdin);
    int len = strlen(destination);
    if (len > 0 && destination[len - 1] == '\n')
    {
        destination[len - 1] = '\0';
    }
}
```

You can see this is actually pretty straightforward - we need to add `int` to the first use of len because it's now a local variable, and change the variable name to match our arguments. Then we just replace the chunk of code in our main() and test it out:

```c
    printf("Enter book title: ");
    getString(100,inventory[numBooks].title );
```

I always start by **replacing one use** of the code with the function, compiling it, and running it. Once I am confident it works (debugging with GDB where I need to), I can replace it in other places.


**This is an alternative version where we return the string instead:**

```c
char* getString(int max_length)
{
    char* line = malloc(max_length);

    fgets(line, 100, stdin);
    int len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }

    return line;
}


// and the in-code call:
printf("Enter book title: ");
// we have to use strcpy() because you can't use = with strings..
strcpy(inventory[numBooks].title,getString(100);
```

In this version, we dynamically allocate the string using `malloc()`. This is required because `char line[max_length];` clears after the function closes and will cause a segmentation fault. This is because when a function stops running (when it returns), it gets cleaned out of your memory to prevent memory leaks (more on that next week!) and all its local values are deleted. Dynamically allocated variables aren't deleted as you have to clear those manually with `free()`.

Other than that, the changes are the same. The other key difference is how we call the function- we need to use `strcpy()`.

I personally prefer to pass in the pointer to the string as I feel it's simpler, but either of these functions does the job!