#include <allegro.h>
#include <locale.h>
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)
#include "LittleCow.h"
#include "Player.h"

void init();
void deinit();
void gameOver();
int mainMenu(BITMAP *buffer);
int initGame(BITMAP *buffer);
int insertName(BITMAP *buffer,char *name);

volatile int milisegundos;
void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

volatile int timer;
void timerIncrement(){ timer++; }
END_OF_FUNCTION(timerIncrement);

volatile int stunTimer;
void stunTimerIncrement() { stunTimer++; }
END_OF_FUNCTION(stunTimerIncrement);

FONT* verdana;
FONT* constantia;
Player player;


int main(){
  init();
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

  verdana = load_font("fonts/verdana.pcx",NULL,NULL);
  constantia = load_font("fonts/constantia.pcx",NULL,NULL);

  while(mainMenu(buffer) != 2 || key[KEY_ESC]){
    if(mainMenu(buffer) == 0){
      clear_bitmap(buffer);
      char *name;
      name = malloc(sizeof(char)*100);
      name[0] = '\0';
      if(insertName(buffer,name) == 1){
        player = newPlayer(name);
        if(initGame(buffer) == 1){
          allegro_message("GAME OVER!!!\nYour score was %d!",getPlayerScore(player));
        }
      }
    }
  }

  deinit();

  return 0;
}
END_OF_MAIN();

void init(){
  allegro_init();
  install_timer();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  setlocale(LC_ALL, "Portuguese");
  set_window_title("RanchoBreak!");
}

void deinit() {
  clear_keybuf();
}

int mainMenu(BITMAP *buffer){
  BITMAP *logo = load_bitmap("imgs/logo.bmp", NULL);
  BITMAP* fundo = load_bitmap("imgs/background-menu.bmp", NULL);

  int opcao_menu = 0;

  while(!key[KEY_ESC]){
    clear_bitmap(buffer);
    draw_sprite(buffer, fundo, 0, 0);
    draw_sprite(buffer, logo, 120, 80);

    if (key[KEY_UP]){
      rest(140);
      opcao_menu = ((opcao_menu-1)+3)%3;
    }else if(key[KEY_DOWN]){
      rest(140);
      opcao_menu = (opcao_menu+1)%3;
    }

    if ( opcao_menu == 0 ){
      textprintf_ex(buffer,constantia,280,300,WHITE,-1,"NEW GAME");
      textprintf_ex(buffer,constantia,300,380,BLACK,-1,"RANKING");
      textprintf_ex(buffer,constantia,350,460,BLACK,-1,"EXIT");
    }else if(opcao_menu == 1){
      textprintf_ex(buffer,constantia,280,300,BLACK,-1,"NEW GAME");
      textprintf_ex(buffer,constantia,300,380,WHITE,-1,"RANKING");
      textprintf_ex(buffer,constantia,350,460,BLACK,-1,"EXIT");
    }else if( opcao_menu == 2 ){
      textprintf_ex(buffer,constantia,280,300,BLACK,-1,"NEW GAME");
      textprintf_ex(buffer,constantia,300,380,BLACK,-1,"RANKING");
      textprintf_ex(buffer,constantia,350,460,WHITE,-1,"EXIT");
    }

     if(key[KEY_ENTER]){
      remove_keyboard();
      install_keyboard();
      return opcao_menu;
    }

    draw_sprite(screen, buffer, 0, 0);
  }

  return 2;
}

int initGame(BITMAP *buffer){
  BITMAP* cerca = load_bitmap("imgs/cerca.bmp",NULL);
  BITMAP* cena = load_bitmap("imgs/floor1.bmp",NULL);
  BITMAP* cena2 = load_bitmap("imgs/floor2.bmp",NULL);
  BITMAP* life = load_bitmap("imgs/life.bmp",NULL);
  BITMAP* butcher[6];
  BITMAP* butcherAttack[3];
  butcher[0] = load_bitmap("imgs/butcher1.bmp",NULL);
  butcher[1] = load_bitmap("imgs/butcher2.bmp",NULL);
  butcher[2] = load_bitmap("imgs/butcher3.bmp",NULL);
  butcher[3] = load_bitmap("imgs/butcher4.bmp",NULL);
  butcher[4] = load_bitmap("imgs/butcher5.bmp",NULL);
  butcher[5] = load_bitmap("imgs/butcher6.bmp",NULL);
  butcherAttack[0] = load_bitmap("imgs/attack1.bmp",NULL);
  butcherAttack[1] = load_bitmap("imgs/attack2.bmp",NULL);
  butcherAttack[2] = load_bitmap("imgs/attack3.bmp",NULL);


  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  timer = 0;
  LOCK_FUNCTION(timerIncrement);
  LOCK_VARIABLE(timer);
  install_int_ex(timerIncrement, MSEC_TO_TIMER(1000));

  stunTimer = 0;
  LOCK_FUNCTION(stunTimerIncrement);
  LOCK_VARIABLE(stunTimer);
  install_int_ex(stunTimerIncrement, SECS_TO_TIMER(1));

  float x=0.0,xButcher=0.0;
  int pulo = 0, stun = 0;
  int frame_atual,frameButcher;
  int tempo_troca = 100;
  int x_cerca;
  int vida=0,x_vida;
  int flag_cerca = 0,death=0;
  int score=0,aux=0;
  Cow cow = newCow();

  while(!key[KEY_ESC]){
    if(key[KEY_ESC]){
      clear_bitmap(buffer);
      return 0;
    }

    //UPDATE
    if(!death){
      frameButcher = (milisegundos/tempo_troca) % 6;
    }else{
      frameButcher = (milisegundos/tempo_troca) % 3;
    }
    if(key[KEY_SPACE] && getCowCoordY(cow) == 500) pulo = 1;
    if(getCowLifes(cow)) frame_atual = (milisegundos / tempo_troca) % 4;
    if(!getCowLifes(cow)) frame_atual = (milisegundos / 400) % 4;
    if(x < -2362) x = 0;
    if(!stun && getCowLifes(cow)) x-=0.4;
    if(pulo) setCowCoordY(cow,-0.2);
    if(getCowCoordY(cow) < 400 || stun) pulo = 0;
    if(!pulo && getCowCoordY(cow)  < 500) setCowCoordY(cow,0.2);

    if(!stun) score = timer*10;

    if(x > -1000 && !flag_cerca){
      x_cerca = (rand() % 300 + 1400)*(-1);
      flag_cerca = 1;
    }

    if(x < x_cerca) flag_cerca = 0;


    if( x + getCowCoordX(cow) >= x_cerca+580 &&  x+getCowCoordX(cow) <= x_cerca + 600 && getCowCoordY(cow) >= 450 && !stun && !death){
      stun = 1;
      setCowLifes(cow,-1);
      if(getCowLifes(cow)){
        x_cerca = 0;
      }else{
        frame_atual = 0;
      }
      stunTimer=0;
    }

    if(!getCowLifes(cow) && !death){
      xButcher+=0.2;
    }

    if(xButcher > 180 && !death){
      death = 1;
      stunTimer =0;
    }

    if(stunTimer == 2){
      if(stun) stun = 0;
    }

    if(stunTimer == 3 && aux){
      setPlayerScore(player,score);
      return 1;
    }

    if(stunTimer%60 == 0 && stunTimer && getCowLifes(cow) != 3 && !vida){
      vida = 2;

      if(x < -1255){
        x_vida = (rand() % 400 + 1400)*(-1);
        while(x_vida >= x_cerca+120 && x_vida <= x_cerca-120){
          x_vida = (rand() % 400 + 1400)*(-1);
        }
      }
      stunTimer = 0;
    }

    if(x + getCowCoordX(cow) >= x_vida+580 &&  x+getCowCoordX(cow) <= x_vida + 600 && vida && getCowCoordY(cow) >= 490){
      x_vida = 0;
      setCowLifes(cow,1);
      vida = 0;
    }

    //DRAW
    textprintf_ex(buffer,verdana,10,10,makecol(255,255,255),-1,"SCORE: %d",score);
    draw_sprite(buffer,cow->animationSprites[4][getCowLifes(cow)],10,40);
    draw_sprite(buffer,cena,x,458);
    draw_sprite(buffer,cena2,x+1255,458);
    draw_sprite(buffer,cena,x+2362,458);
    draw_sprite(buffer,cerca,x+abs(x_cerca),440);
    draw_sprite(buffer,life,x+abs(x_vida),520);
    
    if(!death) draw_sprite(buffer,butcher[frameButcher],xButcher,480);
    if(getCowCoordY(cow) == 500 && !stun && getCowLifes(cow)) draw_sprite(buffer, cow->animationSprites[0][frame_atual], getCowCoordX(cow), getCowCoordY(cow));
    if(getCowCoordY(cow) < 500 && !stun && getCowLifes(cow)) draw_sprite(buffer, cow->animationSprites[1][frame_atual], getCowCoordX(cow), getCowCoordY(cow));
    if(stun && !death) draw_sprite(buffer,cow->animationSprites[3][frame_atual],getCowCoordX(cow)-30,getCowCoordY(cow)-30);
    if(death){
      draw_sprite(buffer,butcherAttack[frameButcher],xButcher,450);
      if(frame_atual > 2 && !aux){
        draw_sprite(buffer,cow->animationSprites[2][frame_atual],getCowCoordX(cow)-30,getCowCoordY(cow)-10);
      }else{
        draw_sprite(buffer,cow->animationSprites[2][3],getCowCoordX(cow)-30,getCowCoordY(cow)-10);
        aux = 1;
      }
    } 

    draw_sprite(screen, buffer, 0, 0);
    clear_to_color(buffer, makecol(0,0,255));
  }
  return 0;
}

int insertName(BITMAP *buffer,char *name){
  clear_keybuf();
  clear_bitmap(buffer);

  BITMAP *background = load_bitmap("imgs/background-menu.bmp",NULL);
  BITMAP *logo = load_bitmap("imgs/logo.bmp", NULL);
  BITMAP *input = load_bitmap("imgs/template.bmp",NULL);

  clear_to_color(buffer, makecol(0,0,255));
  draw_sprite(buffer,background,0,0);
  draw_sprite(buffer, logo, 120, 80);
  draw_sprite(buffer, input, 250, 350);

  int i=0;

  do{
    draw_sprite(screen, buffer, 0, 0);
    int newKey = readkey();
    char ASCII = (newKey & 0xff);

    if(ASCII >= 32 && ASCII <= 126 && (newKey >> 8) != KEY_SPACE && !key[KEY_BACKSPACE] && i < 32){
      name[i] = ASCII;
      name[i+1] = '\0';
      i++;
    }else if(key[KEY_BACKSPACE] && i > 0){
        name[i-1] = '\0';
        if(i > 1) i--;
        clear_bitmap(buffer);
        clear_to_color(buffer, makecol(0,0,255));
        draw_sprite(buffer, background, 0, 0);
        draw_sprite(buffer, logo, 120, 80);
        draw_sprite(buffer, input, 250, 350);
    }

    textprintf_ex(buffer,verdana,260,385,WHITE,-1,"%s",name);

    if(key[KEY_ENTER]){
      if(i > 0) 
        return 1;
      else
        allegro_message("Name invalid!!");
    }

    if(key[KEY_ESC]) break;
  }while(1);

  return 0;
}
