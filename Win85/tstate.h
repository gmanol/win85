// Format DWORD:
// 00-00-00-00
//    |     Clocks
//    |  Jump
//    |
//    \/
//
// 0000-0000
// JJJJ JJJJ
// NNNN SPCZ
// SPCZ

#define precZ (1<<16)
#define precC (1<<17)
#define precP (1<<18)
#define precS (1<<19)

#define precNZ (1<<20)
#define precNC (1<<21)
#define precNP (1<<22)
#define precNS (1<<23)

TState[0x00]=4;
TState[0x01]=10;
TState[0x02]=7;
TState[0x03]=6;
TState[0x04]=4;
TState[0x05]=4;
TState[0x06]=7;
TState[0x07]=4;
TState[0x08]=10;
TState[0x09]=10;
TState[0x0a]=7;
TState[0x0b]=6;
TState[0x0c]=4;
TState[0x0d]=4;
TState[0x0e]=7;
TState[0x0f]=4;
TState[0x10]=7;
TState[0x11]=10;
TState[0x12]=7;
TState[0x13]=6;
TState[0x14]=4;
TState[0x15]=4;
TState[0x16]=7;
TState[0x17]=4;
TState[0x18]=10;
TState[0x19]=10;
TState[0x1a]=7;
TState[0x1b]=6;
TState[0x1c]=4;
TState[0x1d]=4;
TState[0x1e]=7;
TState[0x1f]=4;
TState[0x20]=4;
TState[0x21]=10;
TState[0x22]=16;
TState[0x23]=6;
TState[0x24]=4;
TState[0x25]=4;
TState[0x26]=7;
TState[0x27]=4;
TState[0x28]=10;
TState[0x29]=10;
TState[0x2a]=16;
TState[0x2b]=6;
TState[0x2c]=4;
TState[0x2d]=4;
TState[0x2e]=7;
TState[0x2f]=4;
TState[0x30]=4;
TState[0x31]=10;
TState[0x32]=13;
TState[0x33]=6;
TState[0x34]=10;
TState[0x35]=10;
TState[0x36]=10;
TState[0x37]=4;
TState[0x38]=10;
TState[0x39]=10;
TState[0x3a]=13;
TState[0x3b]=6;
TState[0x3c]=4;
TState[0x3d]=4;
TState[0x3e]=7;
TState[0x3f]=4;
TState[0x40]=4;
TState[0x41]=4;
TState[0x42]=4;
TState[0x43]=4;
TState[0x44]=4;
TState[0x45]=4;
TState[0x46]=7;
TState[0x47]=4;
TState[0x48]=4;
TState[0x49]=4;
TState[0x4a]=4;
TState[0x4b]=4;
TState[0x4c]=4;
TState[0x4d]=4;
TState[0x4e]=7;
TState[0x4f]=4;
TState[0x50]=4;
TState[0x51]=4;
TState[0x52]=4;
TState[0x53]=4;
TState[0x54]=4;
TState[0x55]=4;
TState[0x56]=7;
TState[0x57]=4;
TState[0x58]=4;
TState[0x59]=4;
TState[0x5a]=4;
TState[0x5b]=4;
TState[0x5c]=4;
TState[0x5d]=4;
TState[0x5e]=7;
TState[0x5f]=4;
TState[0x60]=4;
TState[0x61]=4;
TState[0x62]=4;
TState[0x63]=4;
TState[0x64]=4;
TState[0x65]=4;
TState[0x66]=7;
TState[0x67]=4;
TState[0x68]=4;
TState[0x69]=4;
TState[0x6a]=4;
TState[0x6b]=4;
TState[0x6c]=4;
TState[0x6d]=4;
TState[0x6e]=7;
TState[0x6f]=4;
TState[0x70]=7;
TState[0x71]=7;
TState[0x72]=7;
TState[0x73]=7;
TState[0x74]=7;
TState[0x75]=7;
TState[0x76]=5;
TState[0x77]=7;
TState[0x78]=4;
TState[0x79]=4;
TState[0x7a]=4;
TState[0x7b]=4;
TState[0x7c]=4;
TState[0x7d]=4;
TState[0x7e]=7;
TState[0x7f]=4;
TState[0x80]=4;
TState[0x81]=4;
TState[0x82]=4;
TState[0x83]=4;
TState[0x84]=4;
TState[0x85]=4;
TState[0x86]=7;
TState[0x87]=4;
TState[0x88]=4;
TState[0x89]=4;
TState[0x8a]=4;
TState[0x8b]=4;
TState[0x8c]=4;
TState[0x8d]=4;
TState[0x8e]=7;
TState[0x8f]=4;
TState[0x90]=4;
TState[0x91]=4;
TState[0x92]=4;
TState[0x93]=4;
TState[0x94]=4;
TState[0x95]=4;
TState[0x96]=7;
TState[0x97]=4;
TState[0x98]=4;
TState[0x99]=4;
TState[0x9a]=4;
TState[0x9b]=4;
TState[0x9c]=4;
TState[0x9d]=4;
TState[0x9e]=7;
TState[0x9f]=4;
TState[0xa0]=4;
TState[0xa1]=4;
TState[0xa2]=4;
TState[0xa3]=4;
TState[0xa4]=4;
TState[0xa5]=4;
TState[0xa6]=7;
TState[0xa7]=4;
TState[0xa8]=4;
TState[0xa9]=4;
TState[0xaa]=4;
TState[0xab]=4;
TState[0xac]=4;
TState[0xad]=4;
TState[0xae]=7;
TState[0xaf]=4;
TState[0xb0]=4;
TState[0xb1]=4;
TState[0xb2]=4;
TState[0xb3]=4;
TState[0xb4]=4;
TState[0xb5]=4;
TState[0xb6]=7;
TState[0xb7]=4;
TState[0xb8]=4;
TState[0xb9]=4;
TState[0xba]=4;
TState[0xbb]=4;
TState[0xbc]=4;
TState[0xbd]=4;
TState[0xbe]=7;
TState[0xbf]=4;
TState[0xc0]=6+(12<<8)+precNZ;
TState[0xc1]=10;
TState[0xc2]=7+(10<<8)+precNZ;
TState[0xc3]=10;
TState[0xc4]=9+(18<<8)+precNZ;
TState[0xc5]=12;
TState[0xc6]=7;
TState[0xc7]=12;
TState[0xc8]=6+(12<<8)+precZ;
TState[0xc9]=10;
TState[0xca]=7+(10<<8)+precZ;
TState[0xcb]=6;	// +(12<<8);			// undocumented!
TState[0xcc]=9+(18<<8)+precZ;
TState[0xcd]=18;
TState[0xce]=7;
TState[0xcf]=12;
TState[0xd0]=6+(12<<8)+precNC;
TState[0xd1]=10;
TState[0xd2]=7+(10<<8)+precNC;
TState[0xd3]=10;
TState[0xd4]=9+(18<<8)+precNC;
TState[0xd5]=12;
TState[0xd6]=7;
TState[0xd7]=12;
TState[0xd8]=6+(12<<8)+precC;
TState[0xd9]=10;
TState[0xda]=7+(10<<8)+precC;
TState[0xdb]=10;
TState[0xdc]=9+(18<<8)+precC;
TState[0xdd]=7; //+(10<<8);				// undocumented!
TState[0xde]=7;
TState[0xdf]=12;
TState[0xe0]=6+(12<<8)+precNP;
TState[0xe1]=10;
TState[0xe2]=7+(10<<8)+precNP;
TState[0xe3]=16;
TState[0xe4]=9+(18<<8)+precNP;
TState[0xe5]=12;
TState[0xe6]=7;
TState[0xe7]=12;
TState[0xe8]=6+(12<<8)+precP;
TState[0xe9]=6;
TState[0xea]=7+(10<<8)+precP;
TState[0xeb]=4;
TState[0xec]=9+(18<<8)+precP;
TState[0xed]=10;
TState[0xee]=7;
TState[0xef]=12;
TState[0xf0]=6+(12<<8)+precNS;
TState[0xf1]=10;
TState[0xf2]=7+(10<<8)+precNS;
TState[0xf3]=4;
TState[0xf4]=9+(18<<8)+precNS;
TState[0xf5]=12;
TState[0xf6]=7;
TState[0xf7]=12;
TState[0xf8]=6+(12<<8)+precS;
TState[0xf9]=6;
TState[0xfa]=7+(10<<8)+precS;
TState[0xfb]=4;
TState[0xfc]=9+(18<<8)+precS;
TState[0xfd]=7;	//+(10<<8);
TState[0xfe]=7;
TState[0xff]=12;