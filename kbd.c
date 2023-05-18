#include "types.h"
#include "x86.h"
#include "defs.h"
#include "kbd.h"

int flag_ALT = 0;

int
kbdgetc(void)
{
	
	static uint shift;
	static uchar *charcode[4] = {
		normalmap, shiftmap, ctlmap, ctlmap
	};
	uint st, data, c;
	

	st = inb(KBSTATP);
	if((st & KBS_DIB) == 0)
		return -1;
	data = inb(KBDATAP);

	if(data == 0xE0){
		shift |= E0ESC;
		return 0;
	} else if(data & 0x80){
		// Key released
		// reset flag
		if (shiftcode[data] == 4) {
	            flag_ALT = 0;
	        }
		data = (shift & E0ESC ? data : data & 0x7F);
		shift &= ~(shiftcode[data] | E0ESC);		
		return 0;
	} else if(shift & E0ESC){
		// Last character was an E0 escape; or with 0x80
		data |= 0x80;
		shift &= ~E0ESC;
	}

	shift |= shiftcode[data];
	shift ^= togglecode[data];
	c = charcode[shift & (CTL | SHIFT)][data];

	
	// ako je pritisnut ALT palimo flag
	if (shiftcode[data] == 4){
		flag_ALT = 1;		
	}
	// ako je trenutni karakter c i flag upaljen, palimo meni
	if (c == 'c' && flag_ALT == 1){
		return 257;
	}


	


	if(shift & CAPSLOCK){
		if('a' <= c && c <= 'z')
			c += 'A' - 'a';
		else if('A' <= c && c <= 'Z')
			c += 'a' - 'A';
	}
	return c;
}

void
kbdintr(void)
{
	consoleintr(kbdgetc);
}










/**
 * case 257 :
			 consputc(c);
			 break;
		case 'w':
            if(flagOpened){
                consputc(c);
                break;
            }
        case 's':
            if(flagOpened){
                consputc(c);
                break;
            }
*/