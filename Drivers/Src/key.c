#include "key.h"
#include "gpio.h"


u8 Trg=0;
u8 Cont=0;

void keyRead(void)
{
	u8 ReadData=((KEY_UP<<UP_Press)+(!KEY_DOWN<<DOWN_Press)+(!KEY_LEFT<<LEFT_Press)+(!KEY_RIGHT<<RIGHT_Press))^0xFF;
	Trg=ReadData&(ReadData^Cont);
	Cont=ReadData;
}
















