/*
 *    file:             keyboard.h
 *    creation date:    2020-10-06
 *    last update:      2020-10-06
 *    author:           kaoru kakinuma
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <linux/input.h>

typedef struct Keyboard Keyboard;

int keyboard_GetKeyState( Keyboard *pSelf, int key );
Keyboard * keyboard_Open( const char *pPathname );
int keyboard_Close( Keyboard *pSelf );

#endif /* _KEYBOARD_H_ */
