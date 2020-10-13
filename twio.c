//twio.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define                                               r \
                                                    return
#define                                           err(...)fprintf\
                                       (stderr, __VA_ARGS__) /****/
                              #define dsp(...)  printf(__VA_ARGS__)/**/
  #define ofo(t,e) ((size_t) &(((t *)0)->e))  /*        ****           ***/ 
typedef        char c;           typedef const          void*            cvp;
typedef          int i;             typedef              char*             cp;
typedef           struct              {c t[64]           ;c                   a
[0x40];              c d               [0x40];           }E;                  E* 
 ntrz;                i                 off[3]           ;                    c 
  asc                 =                  0; c no=0;i j,k,                     l, 
    m;                i                  cmpfunc(cvp a,cvp                     b
      ){             for                  (j =0;j<no;j++)                      { 
       cp          t1=(                 (cp)((E*)a)+off[j]); cp t2=((cp)((E*)b)+
      off        [j]);  for(;(*t1)&&(*t1==*t2);      t1++,t2     ++)  ;
      l=*(         cp)t1     /**/-*(cp)            t2;/*####*/      m=(
      asc >>     j)?1:      /*#####*/-1;           if/*#####*/       (l
      !=    0)  r l         /*######*/*m;          }r/*#####*/       0;
     }      i   par         /*#######*/(i          n,/*#####*/       cp 
     v     []   ) {          /*#######*/k          =/*######*/       0;
     l     =0    ;m           /*######*/=          0/*#####*/        ;;
    for    (j    =2             /*####*/;          j/*###*/         <n;
    j        ++   ){                    i          e               = 0;
    if        ( v  [j]                 [0           ]           !='-') 
    continue      ;    switch ( tolower              ( v [j][1]))   {
    case           't'                    :        k++             ;
    e               =                                            ofo
    (E               ,                 t             )           ;
    break             ;                 case      'a'          :
     l++;               e=                 ofo(E,a)          ;
      break               ;case                           'd'
       :m++;                  e =                     ofo
         (E,d);                   break ; default : err
         ("Unknown classifier '%c'"   ,            v[j]
          [1]);                    r 0;              }
           if (k > 1 || l > 1 || m > 1)             {err
           ("Duplicate categorization");            r 0;
            }i a=(islower(v[j][1]))?1:0;            off
[j-2] = e; asc |= a << (j-2); no++; } r 1; } i main(i n, char* v[]) { if (n<3) {
err("Not enough arguments\n"); r-1; } FILE*f; if((f = fopen(v[1],"r")) == NULL){
err           ("Error opening file\n") ;     r -1; } cp line = NULL ;     size_t
l=0/*  /*S*/   ;i ne=0; for(c C=getc(f);    C !=EOF;C=getc(f) ) if (C    =='\n')  
ne++;  /*P*/   ntrz = malloc(sizeof(E) *    ne) ;fseek(f, 0, SEEK_SET)   ;j = 0;
while  /*I*/   (getline(&line,&l,f)!=-1)    { sscanf(line, "%[^/]/%[^"   "/]/%["
"^/]"          ,ntrz     [j].t,     ntrz    [j]     .a,ntrz    [j].d);   for(l=0
;ntrz          [j]  /**/   .d  /**/  [l]          !='\0';          l++   ); ntrz
[j].d  /*K*/   [l-  /**/   1]  /**/  =0;        j++ ; } ;    fclose(f)   ; if (!
par(n  /*E*/   ,v)  /**/   )r  /**/  -1;          qsort(ntrz ,      ne   ,sizeof
(E)/*  /*!*/   /*\      .*/,/*.    OWLC$    36*/    cmpfunc);for   ( j=0;j < ne;
j++           ){dsp("%s/%s/%s\n",ntrz[j].t, ntrz[j].a,ntrz       [j].d   );}free
(ntrz);r 0;}/* Library Program; (c) Anonymous. License: http://www.wtfpl.net/ */