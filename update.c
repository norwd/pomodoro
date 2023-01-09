/*
//         .             .              .		    
//         |             |              |           .	    
// ,-. ,-. |-. ,-. . ,-. |  ,_, ,-. ,-. |-. ,-,-. . |- ,_,  
// | | ,-| | | |   | |-' |   /  `-. |   | | | | | | |   /   
// `-| `-^ ^-' '   ' `-' `' '"' `-' `-' ' ' ' ' ' ' `' '"'  
//  ,|							    
//  `'							    
// util.c
*/
#include "util.h"
#include "input.h"
#include "update.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

/* Update variables */
void doUpdate(appData * app){

    /* Mode 0 (Main Menu) */
    if(app->currentMode == 0){
        frameTimer(app);

        /* Tomato Animation */
        if(app->frameTimer == (1 * 16)) app->logoFrame = 1;
        else if(app->frameTimer == (2 * 16)) app->logoFrame = 2;
        else if(app->frameTimer == (3 * 16)) app->logoFrame = 3;
        else if(app->frameTimer == (4 * 16)) app->logoFrame = 4;
        else if(app->frameTimer == (5 * 16)) app->logoFrame = 5;
        else if(app->frameTimer == (6 * 16)) app->logoFrame = 6;
        else if(app->frameTimer == (7 * 16)) app->logoFrame = 7;
        else if(app->frameTimer == (8 * 16)){
            app->logoFrame = 0;
            app->frameTimer = 0;
        }
    }

    /* Mode 1 (Work Time) */
    if(app->currentMode == 1){
        timer(app);
        frameTimer(app);
        if(app->timer == 0){
            if(app->pomodoroCounter == app->pomodoros){
                app->timer = (app->longPause * 60 * 16);
                app->pomodoroCounter = 0;
                app->frameTimer = 0;
                app->currentMode = 3;
                system("notify-send -t 5000 -c cpomo ' Pause Break' 'You have some time to chill'");
            }else{
                app->timer = (app->shortPause * 60 * 16);
                app->frameTimer = 0;
                app->currentMode = 2;
                system("notify-send -t 5000 -c cpomo ' Pause Break' 'You have some time chill'");
            }
        }

        /* Coffee Animation */
        if(app->frameTimer == (3 * 16)) app->coffeeFrame = 1;
        else if(app->frameTimer == (6 * 16)){
            app->coffeeFrame = 0;
            app->frameTimer = 0;
        }
    }

    /* Mode 2 (Short Pause) */
    if(app->currentMode == 2){
        timer(app);
        frameTimer(app);
        if(app->timer == 0){
            app->timer = (app->workTime * 60 * 16);
            app->frameTimer = 0;
            app->currentMode = 1;
            app->pomodoroCounter = app->pomodoroCounter + 1;
            system("notify-send -t 5000 -c cpomo '華 Work!' 'You need to focus'");
        }

        /* Machine Animation */
        if(app->frameTimer == (2 * 16)) app->machineFrame = 1;
        else if(app->frameTimer == (4 * 16)) app->machineFrame = 2;
        else if(app->frameTimer == (6 * 16)){
            app->machineFrame = 0;
            app->frameTimer = 0;
        }
    }

    /* Mode 3 (Long Pause) */
    if(app->currentMode == 3){
        timer(app);
        frameTimer(app);
        if(app->timer == 0)
            app->currentMode = 0;
        
        /* Beach Animation */
        if(app->frameTimer == (3 * 16)) app->beachFrame = 1;
        else if(app->frameTimer == (6 * 16)){
            app->beachFrame = 0;
            app->frameTimer = 0;
        }
    }

    /*Get X and Y window size*/
    getWindowSize(app);
}
