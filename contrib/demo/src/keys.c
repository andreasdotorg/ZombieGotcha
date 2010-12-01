
#include "term.h"


//8 rows, 10 columns
const char keychars[]={
  //gnd 0_1   1_2   1_3   1_4   1_5   1_6   1_7   0_6   0_7

  //row 0, gnd
  0x00, 0x00, 'O',  'K',  'N',  'M',  KPWR, 'P',  0x00, 0x00,
  //row 1
  0x00, 0x00, 'Y',  'G',  'C',  ' ',  '<',  ',',  KMNU, '>',
  //row 2
  0x00, 0x00, 0x00, 'Q',  'W',  'E',  'R',  'T',  'U',  'I',
  //row 3
  0x00, 0x00, 0x00, 0x00, 'A',  'S',  'D',  'F',  'H',  'J',
  //row 4
  0x00, 0x00, 0x00, 0x00, 0x00, KCAP, 'Z',  'X',  'V', 'B',
  //row 5
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KSPK, KALT, KONL, KBACK,
  //row 6
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, KBYE, '^',  KDWN,
  //row 7
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '\n', 'L'
};

#define KEY(row,col) keychars[row*10+col]
//#define KEY(row,col) '0'+col;


u16 realkeyscan(){
  u8 row, col;
  
  LED_GREEN=HIGH;
  LED_RED=HIGH;
  
  //All input
  P0DIR &= ~(BIT1+BIT6+BIT7);
  P1DIR &= ~(BIT2+BIT3+BIT4+BIT5+BIT6+BIT7);
  P0 |= BIT1+BIT6+BIT7;
  P1 |= BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;
  
  for(row=0;row<8;row++){
    col=row;//nothing
    switch(row){
    case 0://ground
    default:
      break;
    case 1: //P0_1
      P0DIR|=BIT1;
      P0&=~BIT1;
      break;
    case 2: //P1_2
      P1DIR|=BIT2;
      P1&=~BIT2;
      break;
    case 3: //P1_3
      P1DIR|=BIT3;
      P1&=~BIT3;
      break;
    case 4: //p1_4
      P1DIR|=BIT4;
      P1&=~BIT4;
      break;
    case 5: //p1_5
      P1DIR|=BIT5;
      P1&=~BIT5;
      break;
    case 6: //P1_6
      P1DIR|=BIT6;
      P1&=~BIT6;
      break;
    case 7: //P1_7
      P1DIR|=BIT7;
      P1&=~BIT7;
      break;
    }
    
    if(~P0&BIT1)
      col=1;
    
    if(~P1&BIT2) col=2;
    if(~P1&BIT3) col=3;
    if(~P1&BIT4) col=4;
    if(~P1&BIT5) col=5;
    if(~P1&BIT6) col=6;
    if(~P1&BIT7) col=7;
    
    if(~P0&BIT6)
      col=8;
    if(~P0&BIT7)
      col=9;
    
    if(col!=row) return KEY(row,col);
  }
  
  
  return '\0';
}

//! Returns the debounced character press.
u16 keyscan(){
  u16 key=realkeyscan();
  //debounce
  while(key!=realkeyscan())
    key=realkeyscan();
  
  //All input
  P0DIR &= ~(BIT1+BIT6+BIT7);
  P1DIR &= ~(BIT2+BIT3+BIT4+BIT5+BIT6+BIT7);
  P0 |= BIT1+BIT6+BIT7;
  P1 |= BIT2+BIT3+BIT4+BIT5+BIT6+BIT7;
  
  
  return key;
}

