#include <msp430.h> 
#include <lcd.h>

unsigned int num;
unsigned int den;
long int res;

char x,y,z;
int c,t;

    void primera_conf()
    {
        P3DIR=0x0f;
        P3REN=0Xf0;
        P3OUT=0xf0;
    }

    void segunda_conf()
    {
        P3DIR=0Xf0;
        P3REN=0X0f;
        P3OUT=0X0f;
    }

    unsigned char lcd(unsigned char c)
    {
          switch(c){
                                    case 0x77: t=49;   break;
                                    case 0x7B: t=50;   break;
                                    case 0x7D: t=51;   break;
                                    case 0x7E: t=65;   break;
                                    case 0xB7: t=52;   break;
                                    case 0xBB: t=53;   break;
                                    case 0xBD: t=54;   break;
                                    case 0xBE: t=66;   break;
                                    case 0xD7: t=55;   break;
                                    case 0xDB: t=56;   break;
                                    case 0xDD: t=57;   break;
                                    case 0xDE: t=67;   break;
                                    case 0xE7: t=42;   break;
                                    case 0xEB: t=48;   break;
                                    case 0xED: t=35;   break;
                                    case 0xEE: t=68;   break;
                                    default: t=0;
                      }
          return t;

    }

unsigned char teclado()
    {
        primera_conf();
        while(1)
        {
            if((P3IN&0xf0)!=0xf0)
            {
            __delay_cycles(100);
                if((P3IN&0xf0)!=0xf0)
                {
                  x=(P3IN&0xf0);
                  segunda_conf();
                  __delay_cycles(1000);
                  x=x | (P3IN&0x0f);
                  x=lcd(x);
                  while((P3IN&0x0f)!=0x0f);
                  primera_conf();
                  __delay_cycles(1000);
                  return x;
                }
            }

        }

    }

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	unsigned char x;
    unsigned char operador;
    unsigned int y=10000;
    unsigned int z=0;

    LCDinit();
    LCDclear();
    LCDline1();
    num=0; den=0; res=0; operador=0;

    while(1){

       x=teclado();

        if(x!=0){

            if(x>=48 && x<=57 && operador==0 )
            {
                LCDputChar(x);
                num=num*10+(x-48);

            }

            if(x>=48 && x<=57 && operador!=0)
            {
                            LCDputChar(x);
                            den=den*10+(x-48);

                        }

            if(x>=65 && x<=68)
            {
                operador=x;
                switch(operador)
                {
                case 65: LCDputChar(43); break;
                case 66: LCDputChar(45); break;
                case 67: LCDputChar(42); break;
                case 68: LCDputChar(47); break;
                }
            }

            if(x==35)
            { LCDline2();
                LCDputChar('=');

                switch(operador){

                case 65: res=num+den; break;
                case 66:
                    if(num>den)
                        res=num-den;
                        if(den>num)
                        {
                            LCDputChar('-');
                            res=den-num;
                        }
                break;

                case 67: res=num*den; break;
                case 68: res=num/den; break;
            }
                if(res!=0){
                while(res<y)
                    y=y/10;

                 while(y!=0){
                     z=res/y;
                     res=res%y;
                     LCDputChar(z+48);
                     y=y/10;
                 }
             }
                else
                    LCDputChar(48);
        }
            if(x==42)
            {
                LCDclear();
                LCDline1();
                res=0;
                num=0;
                den=0;
                operador=0;
                y=10000;
            }
        }
      }
    }






