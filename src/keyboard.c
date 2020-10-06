/*
 *    file:             keyboard.c
 *    creation date:    2020-10-06
 *    last update:      2020-10-06
 *    author:           kaoru kakinuma
 */
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include "keyboard.h"

#define KEYNUM (256)

struct Keyboard {
    bool         running;
    pthread_t    thread;
    int          fd;
    char         aKeyState[KEYNUM];
};

static void * MainThread( void *pArg )
{
    Keyboard *pSelf = (Keyboard *)pArg;

    while ( pSelf->running ) {

        struct input_event event;
        ssize_t size = read( pSelf->fd, &event, sizeof(event) );
        if ( size != sizeof(event) ) {
            continue;
        }

        if ( event.type == EV_KEY ) {
            pSelf->aKeyState[event.code] = event.value;
        }
    }

    pthread_exit( NULL );
}

int keyboard_GetKeyState( Keyboard *pSelf, int key )
{
    if ( pSelf == NULL ) {
        return -1;
    }

    if ( key < 0 || key >= KEYNUM ) {
        return -1;
    }

    return pSelf->aKeyState[key];
}

Keyboard * keyboard_Open( const char *pPathname )
{
    if ( pPathname == NULL ) {
        return NULL;
    }

    Keyboard *pSelf = (Keyboard *)malloc( sizeof(Keyboard) );
    if ( pSelf == NULL ) {
        return NULL;
    }

    int fd = open( pPathname, O_RDWR );
    if ( fd < 0 ) {
        free( pSelf );
        return NULL;;
    }

    pthread_t thread;
    int ret = pthread_create( &thread, NULL, MainThread, pSelf );
    if ( ret != 0 ) {
        close( fd );
        free( pSelf );
        return NULL;
    }

    pSelf->running = true;
    pSelf->thread  = thread;
    pSelf->fd      = fd;
    memset( pSelf->aKeyState, 0, KEYNUM );

    return pSelf;
}

int keyboard_Close( Keyboard *pSelf )
{
    if ( pSelf == NULL ) {
        return -1;
    }

    pSelf->running = false;
    pthread_join( pSelf->thread, NULL );
    close( pSelf->fd );
    free( pSelf );

    return 0;
}
