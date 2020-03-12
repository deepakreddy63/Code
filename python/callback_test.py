#!/usr/bin/env python3

## To experiment with callback functionality
## 10/30/2019

# Function to use as callback in main function

#print(__name__) # Test to see what __name__ is assigned by interpreter
def callback_fn(i=0):
    """
    Simple function which prints the integer passed to it
    """
    print("Passed integer to callback:", i)

# Function which uses callback function
def main(callback_func):
    """
    main function to execute callback fn
    """
    count_print = 10
    for i in range(count_print):
        callback_func(i)

    print("Finished")

if __name__ == '__main__':
    main(callback_fn)