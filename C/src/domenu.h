/*---------------------------------------------*/
/* Modul: domenu.h           Version 1.0       */
/*                                             */
/* contains definition of menu structure       */
/*                                             */
/* Datum : 31 . August 1991                    */
/*                                             */
/*---------------------------------------------*/
struct menu {
    int m_height;               /* menu height */
    int m_width;                /* menu width */
    char *m_title;              /* menu title */
    char **m_data;              /* pointer to data */
};