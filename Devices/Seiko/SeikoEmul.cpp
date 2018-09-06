// SeikoEmul.cpp: implementation of the CSeikoEmul class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SeikoEmul.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSeikoEmul::CSeikoEmul()
{
	for (int i=0;i<128*8;i++)
	{
		SeikoOFF[i]=0;
		SeikoRAM[i]=rand();
	}

	Reset();
}


CSeikoEmul::~CSeikoEmul()
{

}

void CSeikoEmul::Write(BYTE port, BYTE data) 
{
	// TODO: Add your dispatch handler code here
	BYTE d,cs;

	BYTE mask1,mask2;
	BYTE bytcol,bitcol;
	unsigned int x;


	if (port==m_data_port)	{

	if ((Seiko_CS & 1)==0)
		{
		m_update=TRUE;
		bytcol=Seiko_Y1 >> 3;
		bitcol=Seiko_Y1 & 7;
		x=bytcol+(Seiko_X1 << 7);

		mask1= ~(0x80 >> bitcol);
		mask2= 7-bitcol;

	SeikoRAM[x+0]=(SeikoRAM[x+0] & mask1) | ((data & 1) << mask2);
	SeikoRAM[x+16]=(SeikoRAM[x+16] & mask1) | (((data & 2) >> 1) << mask2);
	SeikoRAM[x+32]=(SeikoRAM[x+32] & mask1) | (((data & 4) >> 2) << mask2);
	SeikoRAM[x+48]=(SeikoRAM[x+48] & mask1) | (((data & 8) >> 3) << mask2);
	SeikoRAM[x+64]=(SeikoRAM[x+64] & mask1) | (((data & 16) >> 4) << mask2);
	SeikoRAM[x+80]=(SeikoRAM[x+80] & mask1) | (((data & 32) >> 5) << mask2);
	SeikoRAM[x+96]=(SeikoRAM[x+96] & mask1) | (((data & 64) >> 6) << mask2);
	SeikoRAM[x+112]=(SeikoRAM[x+112] & mask1) | ((data >> 7) << mask2);

		Seiko_Y1++;
		if (Seiko_Y1==64) Seiko_Y1=0;
		}

	if ((Seiko_CS & 2)==0)
		{
	m_update=TRUE;
	bytcol=Seiko_Y2 >> 3;
	bitcol=Seiko_Y2 & 7;
	x=bytcol+(Seiko_X2 << 7);

	mask1= ~(0x80 >> bitcol);
	mask2= 7-bitcol;

	SeikoRAM[x+8]=(SeikoRAM[x+8] & mask1) | ((data & 1) << mask2);
	SeikoRAM[x+24]=(SeikoRAM[x+24] & mask1) | (((data & 2) >> 1) << mask2);
	SeikoRAM[x+40]=(SeikoRAM[x+40] & mask1) | (((data & 4) >> 2) << mask2);
	SeikoRAM[x+56]=(SeikoRAM[x+56] & mask1) | (((data & 8) >> 3) << mask2);
	SeikoRAM[x+72]=(SeikoRAM[x+72] & mask1) | (((data & 16) >> 4) << mask2);
	SeikoRAM[x+88]=(SeikoRAM[x+88] & mask1) | (((data & 32) >> 5) << mask2);
	SeikoRAM[x+104]=(SeikoRAM[x+104] & mask1) | (((data & 64) >> 6) << mask2);
	SeikoRAM[x+120]=(SeikoRAM[x+120] & mask1) | ((data >> 7) << mask2);

	Seiko_Y2++;
	if (Seiko_Y2==64) Seiko_Y2=0;
		}
	}

	else if (port==m_instr_port)

	{
	d=data;
	cs=Seiko_CS;
	
	if ((cs & 1)==0)
		{
	if ((d & 0xc0)==0xc0) Seiko_Z1=(d & 0x3f);
	if ((d & 0xf8)==0xb8) Seiko_X1=(d & 0x7);
	if ((d & 0xc0)==0x40) {Seiko_Y1=(d & 0x3f);Seiko_bug=TRUE;}
		}

	if ((cs & 2)==0)
		{
	if ((d & 0xc0)==0xc0) Seiko_Z2=(d & 0x3f);
	if ((d & 0xf8)==0xb8) Seiko_X2=(d & 0x7);
	if ((d & 0xc0)==0x40) {Seiko_Y2=(d & 0x3f);Seiko_bug=TRUE;}
		}
	}

	else if (port==m_cs_port)
	{
	Seiko_CS=data & 3;
	}
}


BYTE CSeikoEmul::Read(BYTE port)
{
	// TODO: Add your dispatch handler code here
	BYTE p,r;

	p=(BYTE) port & 0xff;

	
	BYTE mask1;
	int mask2;
	BYTE bytcol,bitcol;
	WORD x;

	if (p==m_instr_port)
	{
	return (0);
	}


	else if (p==m_data_port)
	{

		if (Seiko_bug==TRUE) {Seiko_bug=FALSE;return(0);}

	if ((Seiko_CS & 1)==0)
		{
		bytcol=Seiko_Y1 >> 3;
		bitcol=Seiko_Y1 & 7;

		x=bytcol+(Seiko_X1 << 7);

		mask1= (0x80 >> bitcol);
		mask2= 7-bitcol;

		r=0;

	r=r | ((SeikoRAM[x+112] & mask1) >> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+96] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+80] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+64] & mask1)>> mask2);r=r<<1;

	r=r | ((SeikoRAM[x+48] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+32] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+16] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+0] & mask1)>> mask2);
	
		Seiko_Y1++;
		if (Seiko_Y1==64) Seiko_Y1=0;
		}

	else if ((Seiko_CS & 2)==0)
		{
		bytcol=Seiko_Y2 >> 3;
		bitcol=Seiko_Y2 & 7;

		x=bytcol+(Seiko_X2 << 7);

		mask1= (0x80 >> bitcol);
		mask2= 7-bitcol;

		r=0;

	r=r | ((SeikoRAM[x+120] & mask1) >> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+104] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+88] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+72] & mask1)>> mask2);r=r<<1;

	r=r | ((SeikoRAM[x+56] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+40] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+24] & mask1)>> mask2);r=r<<1;
	r=r | ((SeikoRAM[x+8] & mask1)>> mask2);
	
		Seiko_Y2++;
		if (Seiko_Y2==64) Seiko_Y2=0;
		}

	}
	return (r);

}

void CSeikoEmul::Reset()
{
	Seiko_CS=0;
	Seiko_X1=0;Seiko_X2=0;
	Seiko_Y1=0;Seiko_Y2=0;
	Seiko_Z1=0;Seiko_Z2=0;
	Seiko_Display1=TRUE;
	Seiko_Display2=TRUE;
	Seiko_bug=FALSE;
	m_update=TRUE;

}
