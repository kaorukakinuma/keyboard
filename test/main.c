#include <stdio.h>
#include "keyboard.h"

int main( void )
{
    Keyboard *pKeyboard = keyboard_Open( "/dev/input/event2" );

    printf( "Press <A> and <B> to exit.\n" );
    while ( 1 ) {
        int keyA = keyboard_GetKeyState( pKeyboard, KEY_A );
        int keyB = keyboard_GetKeyState( pKeyboard, KEY_B );
        if ( keyA && keyB ) {
            break;
        }
    }

    keyboard_Close( pKeyboard );
}
