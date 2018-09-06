	case 0xd3:				// OUT

		switch (byte2)	
		{

		case 0x80:
	
		break;

		case 0x81:

		break;

		case 0x82:

		break;

		case 0x83:
		break;
 		}

	clocks=clocks+3;
	PC=PC+2;
	break;


	case 0xdb:
		switch(byte2)
		{
		case 0x80:
		
		break;

		case 0x81:

		break;

		}
	clocks=clocks+3;
	PC=PC+2;
	break;