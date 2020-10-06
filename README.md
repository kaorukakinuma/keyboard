# Keyboard

+ Dependencies: `lpthread`
+ Includes: `keyboard.h`


## How to build

```
$ git clone https://github.com/kaorukakinuma/keyboard.git
$ cd keyboard
$ sudo ./mk.sh
#snip
$ ls /home/lib
libkeyboard.a
$ ls /home/include
keyboard.h
```


## How to run a test

```
$ sudo ./test/run.sh
```


## Usage

```c
#include <stdio.h>
#include <keyboard.h>

int main( void )
{
    Keyboard *pKeyboard = keyboard_Open( "/dev/input/event2" );

    printf( "Press <A> and <B> to exit.\n" );
    while ( 1 ) {
        /* Second argument is a value defined in input.h */
        int keyA = keyboard_GetKeyState( pKeyboard, KEY_A );
        int keyB = keyboard_GetKeyState( pKeyboard, KEY_B );
        if ( keyA && keyB ) {
            break;
        }
    }

    keyboard_Close( pKeyboard );
}
```
