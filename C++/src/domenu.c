/*---------------------------------------------*/
/* Modul: domenu.c           Version 1.0       */
/*                                             */
/* Menusystem unter CURSES                     */
/*                                             */
/* Datum : 31 . August 1991                    */
/*                                             */
/*---------------------------------------------*/
#include <curses.h>
#include "domenu.h"
#include <string.h>

int GA_domenu_isblank(s)
char *s;
{
    while(*s == ' ')
      s++;

    return *s == '\0' ? 1: 0;
}

int GA_domenu_main(m)
struct menu *m;
{

  int option, lastoption, j, c, y, x;
  char *p;

  /* save current terminal state, then set required modes */
  savetty();

  cbreak(); nonl(); noecho(); standend();

  /* empty screen */
  clear();

  /* initialize keypad, TRUE is defined in curses. h */
  keypad (stdscr , TRUE) ;

  /* print centred title on line one */
  move(0, (COLS - strlen(m->m_title))/2);
  addstr(m->m_title);

  /* work out position for top left corner of nenu */
  y = (LINES - m->m_height)/2 + 1;
  x = (COLS  - m->m_width)/2;

  /* display menu */
  for (j = 0; j < m->m_height; j++)
    mvaddstr( y+j, x, m->m_data[j]);

  /* initial values for cursor pos. and option setting */
  move( y, x);

  /* this assumes first line in nenu isn't blank */
  lastoption = option = 0;

  for (;;) {

    /* renove highlight bar from last option */
    if (lastoption != option)
      mvaddstr( lastoption+y, x, m->m_data[lastoption]) ;

      /* put highlight bar on current option */
      standout();
      mvaddstr( option + y, x, m->m_data[option] );
      standend();
      move(option +y, x);

      /*save current option */
      lastoption = option;

      refresh();

      /* process input */
      switch( (c = getch()) ) {

        case '\r':              /* option selected, so return */ 
        case '\n':
          if (option < 0) {
             beep();
             break;
          }

          /* restore initial state and return */
          resetty();
          return option;

        case KEY_DOWN:            /* move current down, if possible */
        case KEY_RIGHT:           /* or wrap around */
            do {
               option = (++option < m->m_height) ? option : 0;
            } while (GA_domenu_isblank(m->m_data[option]));
            break;

        case KEY_UP:              /* move current line up or wrap */
        case KEY_LEFT:            /* around */
          do {
             option = (--option >= 0) ? option : m->m_height - 1;
          } while (GA_domenu_isblank(m->m_data[option]));

        default:
          for (j = 0; j < m->m_height; j++) {
            for (p = m->m_data[j]; *p == ' '; p++)
              ;
            if ( *p == '\0')      /* blank line */
              continue;

            if ( *p == c){
              option = j;
              break;  
            }
          }  
          if (j >= m->m_height)
            beep();
          break;
      }
  }
}
