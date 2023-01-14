/**
 * @file graphicalGame.c
 * @author Lucas CAGINICOLAU, Brandon CODAN
 * @brief contains the graphical game structures and functions.
*/
#include "graphicalGame.h"

/**
 * @brief create and manage the screen of the game
 * 
 * @param game all the graphical game data
 *  
*/
void GameScreen(graphical *game){
    windowManager_assignTexture(game->window, 0, 0, game->width, game->height, game->board->pixels,game->width,game->height);
    int x,y,tx,end=0,i=0;
    int divx=game->width/7;
    while(game->status==GAME){
        i++;
        //printf("player = %d\n",board->player);
        if(!game->board->player&&game->ia->ai1>0){
            tx=ai_player(game->board,game->ia->ai1);
        }else if(game->board->player&&game->ia->ai2>0){
            tx=ai_player(game->board,game->ia->ai2);
        }else{
            waitGetEvent(&x,&y,&end);
        if(x>0&&x<divx){
            tx=0;
        }else if( x>divx&&x<divx*2){
            tx=1;
        }else if( x>divx*2&&x<divx*3){
            tx=2;
        }else if( x>divx*3&&x<divx*4){
            tx=3;
        }else if( x>divx*4&&x<divx*5){
            tx=4;
        }else if( x>divx*5&&x<divx*6){
            tx=5;
        }else if( x>divx*6){
            tx=6;
        }
        }
        played(game->board,tx);
        windowManager_assignTexture(game->window, 0, 0, game->width, game->height, game->board->pixels,game->width,game->height);
        if(slash(game->board->data)||backslash(game->board->data)||vertical(game->board->data)||horizontal(game->board->data)){
            game->status=GAMEOVER;
        }else if(i==42){
            game->status=GAMEOVER;
            game->board->tie=1;
        }else{
            msleep(200);
        }
        if(end){
            game->status=END;
        }
    }
    msleep(500);
    msleep(500);
}

/**
 * @brief create and manage the screen of the menu
 * 
 * @param game all the graphical game data
 *  
*/
void menuScreen(graphical *game){
    int x,y,end=0;
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    int top=(game->height/2)-(game->bheight/2);
    int side=(game->width/2)-(game->bwidth/2);
    window_addImage(game->window,"./img/title.bmp",game->width/2-(game->twidth/2),10,game->twidth,game->theight );
    window_addImage(game->window,"./img/start.bmp",side,top-(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/settings.bmp",side,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",side,top+(game->height/5),game->bwidth,game->bheight);
    
    while(game->status==MENU){
        waitGetEvent(&x,&y,&end);
        if(x>=side&&x<=side+game->bwidth){
            if(y>=top-(game->height/5)&&y<=(top-(game->height/5))+game->bheight){
                game->status=GAMEMODE;
            }else if(y>=top&&y<=top+game->bheight){
                game->status=SETTING;
            }else if(y>=top+(game->height/5)&&y<=(top+(game->height/5))+game->bheight){
                game->status=END;
            }
        }
        if(end){
            game->status=END;
        }
    }
}

/**
 * @brief create and manage the screen of the game over
 * 
 * @param game all the graphical game data
 *  
*/
void gameOverScreen(graphical *game){
    int x,y,end=0;
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    int side=((game->width/4)-game->bwidth)/2;
    int top=game->height-game->bheight-10;
    int div=game->width/4;
    if(game->board->tie){
        window_addImage(game->window,"./img/tie.bmp",(game->width/2)-(game->twidth/2),10,game->twidth,game->theight );
    }else if(game->board->player){
        if(!game->board->red){
            window_addImage(game->window,"./img/p1w_r.bmp",(game->width/2)-(game->twidth/2),10,game->twidth,game->theight );
        }else{
            window_addImage(game->window,"./img/p1w_y.bmp",(game->width/2)-(game->twidth/2),10,game->twidth,game->theight );
        }
    }else{
        if(game->board->red){
            window_addImage(game->window,"./img/p2w_r.bmp",(game->width/2)-(game->twidth/2),10,game->twidth,game->theight );
        }else{
            window_addImage(game->window,"./img/p2w_y.bmp",(game->width/2)-(game->twidth/2),10,game->twidth,game->theight );
        }
    }
    windowManager_assignTexture(game->window,game->width/5,game->height/6,game->width,game->height, game->board->pixels,game->width*0.6,game->height*0.6);
    reset(game->board);
    window_addImage(game->window,"./img/restart.bmp",side,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/mode.bmp",side+div,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/menu.bmp",side+(div*2),top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",side+(div*3),top,game->bwidth,game->bheight);
    while(game->status==GAMEOVER){
        waitGetEvent(&x,&y,&end);
        if(y>=top&&y<=game->height-10){
            if(x>=side&&x<=side+game->bwidth){
                game->status =GAME;
            } else if(x>=side+div&&x<=side+div+game->bwidth){
                game->status =GAMEMODE;
            } else if(x>=side+(div*2)&&x<=side+(div*2)+game->bwidth){
                game->status =MENU;
            } else if(x>=side+(div*3)&&x<=side+(div*3)+game->bwidth){
                game->status =END;
            }
        }
        if(end){
            game->status=END;
        }
    }

}

/**
 * @brief create and manage the screen of the ai difficulty selection when there is only one ai player
 * 
 * @param game all the graphical game data
 *  
*/
void AIScreen1(graphical *game){
    int x,y,end=0,p1=0,c=0;
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    int top=game->height/2-20;
    int side1=(game->width/2)-(game->bwidth/2);
    window_addImage(game->window,"./img/difficulty1.bmp",game->width/2-(game->twidth/2),10,game->twidth,game->theight );
    window_addImage(game->window,"./img/ai_difficulty.bmp",side1,top-((game->height/5)*2),game->bwidth,game->bheight);
    if((game->ia->nb==1&&(game->red)==0)||(game->ia->nb==2&&(game->red)==1)){
        window_addImage(game->window,"./img/r_easy.bmp",side1,top-(game->height/5),game->bwidth,game->bheight);
        window_addImage(game->window,"./img/r_normal.bmp",side1,top,game->bwidth,game->bheight);
        window_addImage(game->window,"./img/r_hard.bmp",side1,top+(game->height/5),game->bwidth,game->bheight);
    }else{
        window_addImage(game->window,"./img/y_easy.bmp",side1,top-(game->height/5),game->bwidth,game->bheight);
        window_addImage(game->window,"./img/y_normal.bmp",side1,top,game->bwidth,game->bheight);
        window_addImage(game->window,"./img/y_hard.bmp",side1,top+(game->height/5),game->bwidth,game->bheight);
    }
    window_addImage(game->window,"./img/back.bmp",10,game->height-game->bheight-10,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/menu.bmp",20+game->bwidth,game->height-game->bheight-10,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",(game->width/2)-(game->bwidth/2),game->height-game->bheight-10,game->bwidth,game->bheight);
    
    while(game->status==AISCREEN){
        waitGetEvent(&x,&y,&end);
        if(y>=top&&y<=top+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=2;
                window_addImage(game->window,"./img/normal.bmp",side1+135,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=top+(game->height/5)&&y<=top+(game->height/5)+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=3;
                window_addImage(game->window,"./img/hard.bmp",side1+135,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=top-(game->height/5)&&y<=top-(game->height/5)+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=1;
                window_addImage(game->window,"./img/easy.bmp",side1+135,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=game->height-game->bheight-10&&y<=game->height-10){
            if(x>=10&&x<=game->bwidth+10){
                game->status=GAMEMODE;
            }else if(x>=20+game->bwidth&&x<=(2*game->bwidth)+20){
                game->status=MENU;
            }else if(x>=(game->width/2)-(game->bwidth/2)&&x<=(game->width/2)+(game->bwidth/2)){
                game->status=END;
            }else if(c==1&&x<=game->width-10&&x>=game->width-10-game->bwidth){
                game->status=GAME;
            }
        }
        if(p1>0&&c==0){
            c=1;
            window_addImage(game->window,"./img/confirm.bmp",game->width-game->bwidth-10,game->height-game->bheight-10,game->bwidth,game->bheight);
        }
        if(end){
            game->status=END;
        }
    }
    if(game->ia->nb==1){
        game->ia->ai1=p1;
    }else{
        game->ia->ai2=p1;
    }
}

/**
 * @brief create and manage the screen of the ai difficulty selection when there are two ai player
 * 
 * @param game all the graphical game data
 *  
*/
void AIScreen2(graphical *game){
    int x,y,t,end,p1=-1,p2=-1,c=0;
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    int top=game->height/2-20;
    int side1=(game->width/4)-(game->bwidth/2);
    int side2=(game->width/2)+side1;
    window_addImage(game->window,"./img/difficulty2.bmp",game->width/2-(game->twidth/2),10,game->twidth,game->theight );
    window_addImage(game->window,"./img/ai1_difficulty.bmp",side1,top-((game->height/5)*2),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/ai2_difficulty.bmp",side2,top-((game->height/5)*2),game->bwidth,game->bheight);
    if(game->red){
        t=side1;
        side1=side2;
        side2=t;
    }
    window_addImage(game->window,"./img/r_easy.bmp",side1,top-(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/r_normal.bmp",side1,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/r_hard.bmp",side1,top+(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y_easy.bmp",side2,top-(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y_normal.bmp",side2,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y_hard.bmp",side2,top+(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/back.bmp",10,game->height-game->bheight-10,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/menu.bmp",20+game->bwidth,game->height-game->bheight-10,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",(game->width/2)-(game->bwidth/2),game->height-game->bheight-10,game->bwidth,game->bheight);
    if(game->red){
        t=side1;
        side1=side2;
        side2=t;
    }
    while(game->status==AISCREEN){
        waitGetEvent(&x,&y,&end);
        if(y>=top&&y<=top+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=2;
                window_addImage(game->window,"./img/normal.bmp",side1+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }else if(x>=side2&&x<=side2+game->bwidth){
                p2=2;
                window_addImage(game->window,"./img/normal.bmp",side2+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=top+(game->height/5)&&y<=top+(game->height/5)+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=3;
                window_addImage(game->window,"./img/hard.bmp",side1+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }else if(x>=side2&&x<=side2+game->bwidth){
                p2=3;
                window_addImage(game->window,"./img/hard.bmp",side2+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=top-(game->height/5)&&y<=top-(game->height/5)+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=1;
                window_addImage(game->window,"./img/easy.bmp",side1+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }else if(x>=side2&&x<=side2+game->bwidth){
                p2=1;
                window_addImage(game->window,"./img/easy.bmp",side2+140,top-((game->height/5)*2),game->bwidth,game->bheight);
            }
        }else if(y>=game->height-game->bheight-10&&y<=game->height-10){
            if(x>=10&&x<=game->bwidth+10){
                game->status=GAMEMODE;
            }else if(x>=20+game->bwidth&&x<=(2*game->bwidth)+20){
                game->status=MENU;
            }else if(x>=(game->width/2)-(game->bwidth/2)&&x<=(game->width/2)+(game->bwidth/2)){
                game->status=END;
            }else if(c==1&&x<=game->width-10&&x>=game->width-10-game->bwidth){
                game->status=GAME;
            }
        }
        if(p1>0&&p2>0&&c==0){
            c=1;
            window_addImage(game->window,"./img/confirm.bmp",game->width-game->bwidth-10,game->height-game->bheight-10,game->bwidth,game->bheight);
        }
        if(end){
            game->status=END;
        }
    }
    game->ia->ai1=p1;
    game->ia->ai2=p2;
}

/**
 * @brief create and manage the screen of the gamemode selection
 * 
 * @param game all the graphical game data
 *  
*/
void gamemodeScreen(graphical *game){
    int x,y,t,end=0,p1=0,p2=0,c=0;
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    int top=game->height/2-10;
    int side1=(game->width/4)-(game->bwidth/2);
    int side2=(game->width/2)+side1;
    window_addImage(game->window,"./img/gamemode.bmp",game->width/2-(game->twidth/2),10,game->twidth,game->theight );
    if(game->red){
        window_addImage(game->window,"./img/y_p1.bmp",side1,top-(game->height/5),game->bwidth,game->bheight);
        window_addImage(game->window,"./img/r_p2.bmp",side2,top-(game->height/5),game->bwidth,game->bheight);
        t=side1;
        side1=side2;
        side2=t;

    }else{
        window_addImage(game->window,"./img/r_p1.bmp",side1,top-(game->height/5),game->bwidth,game->bheight);
        window_addImage(game->window,"./img/y_p2.bmp",side2,top-(game->height/5),game->bwidth,game->bheight);
    }
    window_addImage(game->window,"./img/r_human.bmp",side1,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/r_computer.bmp",side1,top+(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y_human.bmp",side2,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y_computer.bmp",side2,top+(game->height/5),game->bwidth,game->bheight);
    window_addImage(game->window,"./img/back.bmp",10,game->height-game->bheight-10,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",(game->width/2)-(game->bwidth/2),game->height-game->bheight-10,game->bwidth,game->bheight);
    if(game->red){
        t=side1;
        side1=side2;
        side2=t;
    }
    while(game->status==GAMEMODE){
        waitGetEvent(&x,&y,&end);
        if(y>=top&&y<=top+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=1;
            }else if(x>=side2&&x<=side2+game->bwidth){
                p2=1;
            }
        }else if(y>=top+(game->height/5)&&y<=top+(game->height/5)+game->bheight){
            if(x>=side1&&x<=side1+game->bwidth){
                p1=2;
            }else if(x>=side2&&x<=side2+game->bwidth){
                p2=2;
            }
        }else if(y>=game->height-game->bheight-10&&y<=game->height-10){
            if(x>=10&&x<=game->bwidth+10){
                game->status=MENU;
            }else if(x>=(game->width/2)-(game->bwidth/2)&&x<=(game->width/2)+(game->bwidth/2)){
                game->status=END;
            }else if(c==1&&x<=game->width-10&&x>=game->width-10-game->bwidth){
                game->status=GAME;
            }
        }
        if(p1>0&&p2>0&&c==0){
            c=1;
            window_addImage(game->window,"./img/confirm.bmp",game->width-game->bwidth-10,game->height-game->bheight-10,game->bwidth,game->bheight);
        }
        if(end){
            game->status=END;
        }
    }
    if(p1==2){
        if(p2==2){
            game->ia->nb=3;
        }else{
            game->ia->nb=1;
        }
        game->status=AISCREEN;
    }else if(p2==2){
        game->ia->nb=2;
        game->status=AISCREEN;
    }
}

/**
 * @brief create and manage the setting screen
 * 
 * @param game contains all of the graphical game info
 *  
*/
void settingScreen(graphical *game){
    windowManager_assignBackground(game->window,0,0,game->width,game->height,COLOR_BLACK);
    window_addImage(game->window,"./img/color_setting.bmp",game->width/2-200,10,400,110);
    int top=(game->height/2)-(game->bheight/2);
    int top2=game->height-10-game->bheight;
    int side=(game->width/4)-(game->bwidth/2);
    window_addImage(game->window,"./img/r.bmp",side,top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/y.bmp",side+(game->width/2),top,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/back.bmp",side,top2,game->bwidth,game->bheight);
    window_addImage(game->window,"./img/quit.bmp",side+(game->width/2),top2,game->bwidth,game->bheight);
    int x,y,end=0;
    while(game->status==SETTING){
        waitGetEvent(&x,&y,&end);
        if(y>=top&&y<=top+game->bheight){
            if(x>=side&&x<=side+game->bwidth){
                game->red=0;
            }else if(x>=side+(game->width/2)&&x<=side+(game->width/2)+game->bwidth){
                game->red=1;
            }
        }else if(y>=top2&&y<=top2+game->bheight){
            if(x>=side&&x<=side+game->bwidth){
                game->status=MENU;
            }else if(x>=side+(game->width/2)&&x<=side+(game->width/2)+game->bwidth){
                game->status=END;
            }
        }
        if(end){
            game->status=END;
        }
    }
}


void initGraphical(graphical *game,windowManager *window,ai *ia,connect4 *board,int height,int width){
    game->board=board;
    game->ia=ia;
    game->status=MENU;
    game->window=window;
    game->red=board->red;
    game->height=height;
    game->width=width;
    game->bwidth=width/8.2;
    game->bheight=height/8.745;
    game->twidth=width/4.305;
    game->theight=height/8.745;
}

void graphicalGame(graphical *game){
    while (game->status!=END)
    {
        switch (game->status)
        {
            case MENU:
                menuScreen(game);
                break;
            case GAMEMODE:
                gamemodeScreen(game);
                break;
            case SETTING:
                settingScreen(game);
                break;
            case AISCREEN:
                if(game->ia->nb==3){
                    AIScreen2(game);
                }else{
                    AIScreen1(game);
                }
                break;
            case GAME:
                GameScreen(game);
                break;
            case GAMEOVER:
                gameOverScreen(game);
                break;
            default:
                game->status=MENU;
                break;
        }
    }
}

void destroyGraph(graphical *game){
    destroy(game->board);
    windowManager_destroy(game->window);
}