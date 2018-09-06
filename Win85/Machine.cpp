// Machine.cpp: implementation of the CMachine class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "cpudef.h"
#include "Win85.h"
#include "Machine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "win85doc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMachine::CMachine()
{
	pSPL=(BYTE*) &SP;pSPH=pSPL+1;
	pPCL=(BYTE*) &PC;pPCH=pPCL+1;
	pC=(BYTE*) &BC;pB=pC+1;
	pE=(BYTE*) &DE;pD=pE+1;
	pL=(BYTE*) &HL;pH=pL+1;

	pTEMPWL=(BYTE*) &TEMPW;pTEMPWH=pTEMPWL+1;
	Hold=FALSE;

	int	j,k,m,i;

	for (i=0;i<256;i++)
	{
	k=0;m=i;
	for (j=0;j<8;j++)
		{
		k=k+(m & 1);
		m=m>>1;
		}
	k=k & 1;
	if (k==0) ParityTable[i]=1; else ParityTable[i]=0;
	}


	for (i=0;i<256;i++)
	{
		OpcodeLength[i]=1;
	}

	OpcodeLength[0x01]=3;	OpcodeLength[0x06]=2;
	OpcodeLength[0x0e]=2;	OpcodeLength[0x11]=3;
	OpcodeLength[0x16]=2;	OpcodeLength[0x1e]=2;
	OpcodeLength[0x21]=3;	OpcodeLength[0x22]=3;
	OpcodeLength[0x26]=2;	OpcodeLength[0x28]=2;
	OpcodeLength[0x2a]=3;	OpcodeLength[0x2e]=2;
	OpcodeLength[0x31]=3;	OpcodeLength[0x32]=3;
	OpcodeLength[0x36]=2;	OpcodeLength[0x38]=2;
	OpcodeLength[0x3a]=3;	OpcodeLength[0x3e]=2;
	OpcodeLength[0xc2]=3;	OpcodeLength[0xc3]=3;
	OpcodeLength[0xc4]=3;	OpcodeLength[0xc6]=2;
	OpcodeLength[0xca]=3;	OpcodeLength[0xcc]=3;
	OpcodeLength[0xcd]=3;	OpcodeLength[0xce]=2;
	OpcodeLength[0xd2]=3;	OpcodeLength[0xd3]=2;
	OpcodeLength[0xd4]=3;	OpcodeLength[0xd6]=2;
	OpcodeLength[0xda]=3;	OpcodeLength[0xdb]=2;
	OpcodeLength[0xdc]=3;	OpcodeLength[0xdd]=3;
	OpcodeLength[0xde]=2;	OpcodeLength[0xe2]=3;
	OpcodeLength[0xe4]=3;	OpcodeLength[0xe6]=2;
	OpcodeLength[0xea]=3;	OpcodeLength[0xec]=3;
	OpcodeLength[0xee]=2;	OpcodeLength[0xf2]=3;
	OpcodeLength[0xf4]=3;	OpcodeLength[0xf6]=2;
	OpcodeLength[0xfa]=3;	OpcodeLength[0xfc]=3;
	OpcodeLength[0xfd]=3;	OpcodeLength[0xfe]=2;

#include "optable.h"
#include "asmtable.h"
#include "tstate.h"
	
	Reset();
}

CMachine::~CMachine()
{
}

void CMachine::Reset()
{
	Hold=TRUE;
	Irq_Enable=FALSE;
	Irq_Mask=7;		// all irqs disabled
	CWin85App::gIRQMap[1]=0;	// reset ff
	A=0;FLAGS=0;BC=0;DE=0;HL=0;SP=0x0000;PC=0x0000;	
	clocks=0;
	Hold=FALSE;
}

int CMachine::ReadBit(BYTE bit){if ((FLAGS&bit)!=0) return(1);return(0);}

void CMachine::SetBit(BYTE bit,int status){
	if (status==1) {FLAGS=FLAGS | bit;}
	else {FLAGS=FLAGS & ((BYTE) ~bit);}
	}


void CMachine::Fetch()
{
	fOpcode=Memory.Peek(PC);
	fByte2=Memory.Peek(PC+1);
	fByte3=Memory.Peek(PC+2);

}

CString CMachine::Disassembly(BYTE opcode,BYTE b2,BYTE b3)
{
	CString ts,Byte2,Byte32,s,x;
	DWORD i;
	WORD w;
	BOOL jcon;

	CString SPrec(' ',32);

	ts=OpcodeTable[opcode];

	if (OpcodeLength[opcode]==2)
	{
	Byte2=CWin85App::Byte2Hex(b2)+"h";
	ts.Replace("@",Byte2);
	}

	if (OpcodeLength[opcode]==3)
	{
	Byte32=CWin85App::Word2Hex(b3,b2)+"h";
	ts.Replace("#",Byte32);
	}

	x="";

	ts=ts+SPrec.Left(14-ts.GetLength());


	i=TState[opcode];

	if ((i>>8)==0)
	{
		s=Byte2Dec(BYTE (i&0xff));
		x="         ";
	}
	else
	{
		w=(WORD) (i>>16);

		jcon=FALSE;

		switch(w)
		{
		case 1:
			if (ReadBit(Z)==1) {x="   (Jump)";jcon=TRUE;} else x="(No Jump)";
		break;
		case 2:
			if (ReadBit(CY)==1) {x="   (Jump)";jcon=TRUE;} else x="(No Jump)";
		break;
		case 4:
			if (ReadBit(P)==1) {x="   (Jump)";jcon=TRUE;} else x="(No Jump)";
		break;
		case 8:
			if (ReadBit(S)==1) {x="   (Jump)";jcon=TRUE;} else x="(No Jump)";
		break;
		case 16:
			if (ReadBit(Z)==1) x="(No Jump)"; else {x="   (Jump)";jcon=TRUE;}
		break;
		case 32:
			if (ReadBit(CY)==1) x="(No Jump)"; else {x="   (Jump)";jcon=TRUE;}
		break;
		case 64:
			if (ReadBit(P)==1) x="(No Jump)"; else {x="   (Jump)";jcon=TRUE;}
		break;
		case 128:
			if (ReadBit(S)==1) x="(No Jump)"; else {x="   (Jump)";jcon=TRUE;}
		break;
		}

		w=(WORD) i;
		if (jcon==FALSE)
		{
			s=Byte2Dec(w & 0xff);
		}
		else
		{
			s=Byte2Dec(w>>8);
		}

	}

	s=SPrec.Left(7-s.GetLength())+s;

	ts=ts+" "+x+" "+s;

return (ts);
}

int CMachine::Assembly(CString text, WORD address)
{
	BYTE opcode,b2,b3;
	int length,i;
	int b;
	bool found;
	BOOL Status;

	text.TrimLeft();
	text.TrimRight();
	text.MakeLower();

	if (text.GetLength() < 2) return (-1);

	found=false;
	for (i=0;i<256;i++)
	{
		if ( text.Find(AsmTable[i]) == 0) {opcode=i;found=true;}
	}

	if (found==false) return (-1);

	text.Delete(0,AsmTable[opcode].GetLength());
	length=OpcodeLength[opcode];

	if (text.GetLength()==0 && length!=1) return (-1);
	
	switch (length)
	{
	case 3:
	b=CWin85App::Str2Val(text,&Status);
	if (b>0xffff || Status==FALSE) return -1;
	b2=b & 0xff;
	b3=b >> 8;
	Memory.ForcePoke(address,opcode);
	Memory.ForcePoke(address+1,b2);
	Memory.ForcePoke(address+2,b3);
	break;

	case 2:
	b=CWin85App::Str2Val(text,&Status);
	if (b>0xff || Status==FALSE) return -1;
	b2=b;
	Memory.ForcePoke(address,opcode);
	Memory.ForcePoke(address+1,b2);
	break;

	case 1:
	Memory.ForcePoke(address,opcode);
	break;
	}
	
	return (0);
}


CString CMachine::ReadMemoryBlock16(WORD start)
{
	CString x,y;
	int i;
	BYTE m;
	x=CWin85App::Word2Hex(start)+" ";
	y="";

	for (i=start;i<start+16;i=i+2)
	{
	m=Memory.Peek(i);
	x=x+CWin85App::Byte2Hex(m)+"  ";

	if (m<32 || m>127){
		y=y+". ";
	}
	else
	{
		CString ss;
		ss.Format("%c", m);
		y=y+ss+" ";
	}

	}
	
	x=x+" "+y;

return (x);
}

CString CMachine::ReadMemoryBlock16i(WORD start)
{
	CString x,y;
	int i;
	BYTE m;
	x="       ";
	y="";

	for (i=start+1;i<start+16;i=i+2)
	{
	m=Memory.Peek(i);
	x=x+CWin85App::Byte2Hex(m)+"  ";

	if (m<32 || m>127){
		y=y+". ";
	}
	else
	{
		CString ss;
		ss.Format("%c", m);
		y=y+ss+" ";
	}

	}
	
	x=x+y;

return (x);
}

CString CMachine::ReadMemoryBlockSolid(WORD start)
{
	CString x,y;
	int i;
	BYTE m;
	x="";
	y="";

	for (i=start;i<start+17;i++)
	{
	m=Memory.Peek(i);
	x=x+CWin85App::Byte2Hex(m);

	if (m<32 || m>127){
		y=y+".";
	}
	else
	{
		CString ss;
		ss.Format("%c", m);
		y=y+ss;
	}

	}
	
	x=x+" "+y;

return (x);

}

CString CMachine::ReadMemoryBlock(WORD start)
{
	CString x,y;
	int i;
	BYTE m;
	x=CWin85App::Word2Hex(start)+" ";
	y="";

	for (i=start;i<start+16;i++)
	{
	m=Memory.Peek(i);
	x=x+CWin85App::Byte2Hex(m);

	if (m<32 || m>127){
		y=y+".";
	}
	else
	{
		CString ss;
		ss.Format("%c", m);
		y=y+ss;
	}

	}
	
	x=x+" "+y;

return (x);

}


CString CMachine::ReadStackBlock(WORD start)
{
	CString x;

	x="STACK:"+CWin85App::Word2Hex(start)+" "+CWin85App::Word2Hex(Memory.Peek(start+1),Memory.Peek(start));

return (x);
}

int CMachine::ExecuteNext()
{
	int i;
	fOpcode=Memory.Peek(PC);
	fByte2=Memory.Peek(PC+1);
	fByte3=Memory.Peek(PC+2);

	if (Hold==FALSE) i=Execute(fOpcode,fByte2,fByte3);

	return(i);
}

inline int CMachine::Execute(BYTE opcode,BYTE byte2,BYTE byte3)
{
	BYTE xA,xB,xC;
	int idev;
	WORD w;
	DWORD dw;

	int rtn=-1;

	WORD byte32;
	byte32=(byte3<<8)+byte2;

#define m_push(rh,rl)\
Memory.Poke(--SP,rh);\
Memory.Poke(--SP,rl);


#define m_pop(rh,rl)\
rl=Memory.Peek(SP++);\
rh=Memory.Peek(SP++);


	BOOL ContCheck=FALSE;

	switch (opcode)
    {
    	case 0x00:			 // NOP
		PC++;
      	break;

#define MOV(OPCODE,DEST,SRC,SIZE,CLK)\
case OPCODE:\
DEST=SRC;\
PC+=SIZE;\
break;

    MOV(0x7f,A,A,1,1)
    MOV(0x78,A,B,1,1)
    MOV(0x79,A,C,1,1)
    MOV(0x7a,A,D,1,1)
    MOV(0x7b,A,E,1,1)
    MOV(0x7c,A,H,1,1)
    MOV(0x7d,A,L,1,1)

    MOV(0x47,B,A,1,1)
    MOV(0x40,B,B,1,1)
    MOV(0x41,B,C,1,1)
    MOV(0x42,B,D,1,1)
    MOV(0x43,B,E,1,1)
    MOV(0x44,B,H,1,1)
    MOV(0x45,B,L,1,1)

    MOV(0x4f,C,A,1,1)
    MOV(0x48,C,B,1,1)
    MOV(0x49,C,C,1,1)
    MOV(0x4a,C,D,1,1)
    MOV(0x4b,C,E,1,1)
    MOV(0x4c,C,H,1,1)
    MOV(0x4d,C,L,1,1)

    MOV(0x57,D,A,1,1)
    MOV(0x50,D,B,1,1)
    MOV(0x51,D,C,1,1)
    MOV(0x52,D,D,1,1)
    MOV(0x53,D,E,1,1)
    MOV(0x54,D,H,1,1)
    MOV(0x55,D,L,1,1)

    MOV(0x5f,E,A,1,1)
    MOV(0x58,E,B,1,1)
    MOV(0x59,E,C,1,1)
    MOV(0x5a,E,D,1,1)
    MOV(0x5b,E,E,1,1)
    MOV(0x5c,E,H,1,1)
    MOV(0x5d,E,L,1,1)

    MOV(0x67,H,A,1,1)
    MOV(0x60,H,B,1,1)
    MOV(0x61,H,C,1,1)
    MOV(0x62,H,D,1,1)
    MOV(0x63,H,E,1,1)
    MOV(0x64,H,H,1,1)
    MOV(0x65,H,L,1,1)

    MOV(0x6f,L,A,1,1)
    MOV(0x68,L,B,1,1)
    MOV(0x69,L,C,1,1)
    MOV(0x6a,L,D,1,1)
    MOV(0x6b,L,E,1,1)
    MOV(0x6c,L,H,1,1)
    MOV(0x6d,L,L,1,1)

    MOV(0x7e,A,Memory.Peek(HL),1,2)   // MOV A,M
    MOV(0x46,B,Memory.Peek(HL),1,2)	  // MOV B,M
    MOV(0x4e,C,Memory.Peek(HL),1,2)
    MOV(0x56,D,Memory.Peek(HL),1,2)
    MOV(0x5e,E,Memory.Peek(HL),1,2)
    MOV(0x66,H,Memory.Peek(HL),1,2)
    MOV(0x6e,L,Memory.Peek(HL),1,2)

    MOV(0x3e,A,byte2,2,2)             // MVI A,byte2
    MOV(0X06,B,byte2,2,2)             // MVI B,byte2
    MOV(0x0e,C,byte2,2,2)             // MVI C,byte2
    MOV(0x16,D,byte2,2,2)             // MVI D,byte2
    MOV(0x1e,E,byte2,2,2)             // MVI E,byte2
    MOV(0x26,H,byte2,2,2)             // MVI H,byte2
    MOV(0x2e,L,byte2,2,2)             // MVI L,byte2

#define MOV_MS(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
Memory.Poke(HL,SRC);\
PC+=SIZE;\
break;

    MOV_MS(0x77,A,1,2)			// MOV M,A
    MOV_MS(0x70,B,1,2)			// MOV M,B
    MOV_MS(0x71,C,1,2)
    MOV_MS(0x72,D,1,2)
    MOV_MS(0x73,E,1,2)
    MOV_MS(0x74,H,1,2)
	MOV_MS(0x75,L,1,2)

	MOV_MS(0x36,byte2,2,3)		// MVI M,byte2


#define LXI(OPCODE,RD)\
case OPCODE:\
RD=byte32;\
PC+=3;\
break;

      LXI(0x01,BC)
      LXI(0x11,DE)
      LXI(0x21,HL)
	
	case 0x31:
	SP=byte32;
	PC+=3;
	rtn=1;
	break;


      case 0x3a:				  // LDA addr
      A=Memory.Peek(byte32);
      PC+=3;
      break;

      case 0x32:				  // STA addr
      Memory.Poke(byte32,A);
      PC+=3;
      break;

      case 0x2a:				  // LHLD addr
      L=Memory.Peek(byte32);
      H=Memory.Peek(byte32+1);
      PC+=3;
      break;

      case 0x22:				  // SHLD addr
      Memory.Poke(byte32,L);
      Memory.Poke(byte32+1,H);
      PC+=3;
      break;

#define LDAX(OPCODE,RD)\
case OPCODE:\
A=Memory.Peek(RD);\
PC++;\
break;

      LDAX(0x0a,BC)
      LDAX(0x1a,DE)

#define STAX(OPCODE,RD)\
case OPCODE:\
Memory.Poke(RD,A);\
PC++;\
break;

      STAX(0x02,BC)
      STAX(0x12,DE)

      case 0xeb:				// XCHG
	  TEMPW=HL;HL=DE;DE=TEMPW;
      PC++;
      break;

// -----------------------------------------------------------------------------------

#define PUSH(OPCODE,RH,RL)\
case OPCODE:\
m_push(RH,RL)\
PC++;\
break;


      PUSH(0xc5,B,C)
      PUSH(0xd5,D,E)
      PUSH(0xe5,H,L)
      PUSH(0xf5,A,FLAGS)  // PUSH PSW

#define POP(OPCODE,RH,RL)\
case OPCODE:\
m_pop(RH,RL)\
PC++;\
break;

      POP(0xc1,B,C)
      POP(0xd1,D,E)
      POP(0xe1,H,L)
      POP(0xf1,A,FLAGS)	  // POP PSW


      case 0xe3:			  // XTHL
	  w=SP;
      TEMPB=Memory.Peek(w);
      Memory.Poke(w,L);L=TEMPB;
      TEMPB=Memory.Peek(++w);
      Memory.Poke(w,H);H=TEMPB;
      PC++;
      break;

      case 0xf9:			  // SPHL
	  SP=HL;
      PC++;
      break;

      case 0xe9:			  // PCHL
	  PC=HL;
      break;

// ---------------------------------------------------------------------------------

      case 0xc3:			  // JMP addr
	  PC=byte32;
      break;

	  case 0xc9:		      // RET
	  m_pop(PCH,PCL)
	  break;

      case 0xcd:			  // CALL addr
	  PC+=3;
	  m_push(PCH,PCL)
	  PC=byte32;
      break;

#define JCON(OPCODE,FLAG,STATUS)\
case OPCODE:\
if (ReadBit(FLAG)==STATUS)\
{ContCheck=TRUE;PC=byte32;}\
else\
{PC+=3;}\
break;

      JCON(0xc2,Z,0)			// JNZ
      JCON(0xd2,CY,0)			
      JCON(0xe2,P,0)			
      JCON(0xf2,S,0)			

      JCON(0xca,Z,1)
      JCON(0xda,CY,1)
      JCON(0xea,P,1)
      JCON(0xfa,S,1)


#define CALLCON(OPCODE,FLAG,STATUS)\
case OPCODE:\
if (ReadBit(FLAG)==STATUS)\
{m_push(PCH,PCL)\
ContCheck=TRUE;PC=byte32;}\
else\
{PC+=3;}\
break;

      CALLCON(0xc4,Z,0)
      CALLCON(0xd4,CY,0)
      CALLCON(0xe4,P,0)
      CALLCON(0xf4,S,0)

      CALLCON(0xcc,Z,1)
      CALLCON(0xdc,CY,1)
      CALLCON(0xec,P,1)
      CALLCON(0xfc,S,1)

#define RETCON(OPCODE,FLAG,STATUS)\
case OPCODE:\
if (ReadBit(FLAG)==STATUS)\
{ContCheck=TRUE;m_pop(PCH,PCL)}\
else\
{PC++;}\
break;

      RETCON(0xc0,Z,0)
      RETCON(0xd0,CY,0)
      RETCON(0xe0,P,0)
      RETCON(0xf0,S,0)

      RETCON(0xc8,Z,1)
      RETCON(0xd8,CY,1)
      RETCON(0xe8,P,1)
      RETCON(0xf8,S,1)

#define RST(OPCODE,ADDR)\
case OPCODE:\
m_push(PCH,PCL)\
PC=ADDR;\
break;

      RST(0xc7,0)
      RST(0xcf,0x8)
      RST(0xd7,0x10)
      RST(0xdf,0x18)
      RST(0xe7,0x20)
      RST(0xef,0x28)
      RST(0xf7,0x30)
      RST(0xff,0x38)


      case 0x37:			  // STC
      SetBit(CY,1);
      PC++;
      break;

      case 0x3f:			  // CMC
      SetBit(CY,(ReadBit(CY))^1);
      PC++;
      break;

      case 0x2f:			  // CMA
      A=~A;
      PC++;
	  break;


#define m_setS(VALUE) \
if ((VALUE & 0x80)==0x80) SetBit(S,1); else SetBit(S,0);

#define m_setZ(VALUE) \
if (VALUE==0) SetBit(Z,1); else SetBit(Z,0);

#define m_setCY(VALUE) \
if (VALUE!=0) SetBit(CY,1); else SetBit(CY,0);

#define m_setP(VALUE) \
SetBit(P,ParityTable[VALUE]);


#define m_setAC_PLUS(V1,V2) \
TEMPB=(V1 & 0x0f)+(V2 & 0x0f);\
if ((TEMPB & 0x10)!=0) SetBit(AC,1); else SetBit(AC,0);

#define m_setAC_PLUS_CY(V1,V2,VC) \
TEMPB=(V1 & 0x0f)+(V2 & 0x0f)+VC;\
if ((TEMPB & 0x10)!=0) SetBit(AC,1); else SetBit(AC,0);

#define m_setAC_MINUS(V1,V2) \
TEMPB=(V1 & 0x0f)+((~V2 & 0x0f)+1);\
if ((TEMPB & 0x10)!=0) SetBit(AC,1); else SetBit(AC,0);

#define m_setAC_MINUS_CY(V1,V2,VC) \
TEMPB=(V1 & 0x0f)+((~V2 & 0x0f)+1)+(~VC+1);\
if ((TEMPB & 0x10)!=0) SetBit(AC,1); else SetBit(AC,0);

// -------------------------------------------------------------------------------
#define ADD(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=A;\
xB=SRC;\
TEMPW=xA+xB;\
A=TEMPWL;\
m_setZ(A);\
m_setS(A);\
m_setCY(TEMPWH);\
m_setP(A);\
m_setAC_PLUS(xA,xB);\
PC+=SIZE;\
break;


	  ADD(0x87,A,1,1)
	  ADD(0x80,B,1,1)
	  ADD(0x81,C,1,1)
	  ADD(0x82,D,1,1)
	  ADD(0x83,E,1,1)
	  ADD(0x84,H,1,1)
	  ADD(0x85,L,1,1)

	  ADD(0x86,Memory.Peek(HL),1,2)	// ADD M

	  ADD(0xc6,byte2,2,2)	// ADI


#define ADC(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=A;\
xB=SRC;\
xC=ReadBit(CY);\
TEMPW=xA+xB+xC;\
A=TEMPWL;\
m_setZ(A);\
m_setS(A);\
m_setCY(TEMPWH);\
m_setP(A);\
m_setAC_PLUS_CY(xA,xB,xC);\
PC+=SIZE;\
break;


	ADC(0x8f,A,1,1)
	ADC(0x88,B,1,1)
	ADC(0x89,C,1,1)
	ADC(0x8a,D,1,1)
	ADC(0x8b,E,1,1)
	ADC(0x8c,H,1,1)
	ADC(0x8d,L,1,1)

	ADC(0x8e,Memory.Peek(HL),1,2)	// ADC M
	
	ADC(0xce,byte2,2,2)				// ACI


#define SUB(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=A;\
xB=SRC;\
TEMPW=xA-xB;\
A=TEMPWL;\
m_setZ(A);\
m_setS(A);\
m_setCY(TEMPWH);\
m_setP(A);\
m_setAC_MINUS(xA,xB);\
PC+=SIZE;\
break;

	SUB(0x97,A,1,1)
	SUB(0x90,B,1,1)
	SUB(0x91,C,1,1)
	SUB(0x92,D,1,1)
	SUB(0x93,E,1,1)
	SUB(0x94,H,1,1)
	SUB(0x95,L,1,1)

	SUB(0x96,Memory.Peek(HL),1,2)	// SUB M

    SUB(0xd6,byte2,2,2)	// SUI


#define SBB(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=A;\
xB=SRC;\
xC=ReadBit(CY);\
TEMPW=xA-xB-xC;\
A=TEMPWL;\
m_setZ(A);\
m_setS(A);\
m_setCY(TEMPWH);\
m_setP(A);\
m_setAC_MINUS_CY(xA,xB,xC);\
PC+=SIZE;\
break;


	SBB(0x9f,A,1,1)
	SBB(0x98,B,1,1)
	SBB(0x99,C,1,1)
	SBB(0x9a,D,1,1)
	SBB(0x9b,E,1,1)
	SBB(0x9c,H,1,1)
	SBB(0x9d,L,1,1)
	
	SBB(0x9e,Memory.Peek(HL),1,2) // SBB M
	
	SBB(0xde,byte2,2,2)			  // SBI


#define INR(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=SRC;\
xB=xA;\
xA++;\
m_setZ(xA);\
m_setS(xA);\
m_setP(xA);\
m_setAC_PLUS(xB,1);\
SRC=xA;\
PC+=SIZE;\
break;


	INR(0x3c,A,1,1)
	INR(0x04,B,1,1)
	INR(0x0c,C,1,1)
	INR(0x14,D,1,1)
	INR(0x1c,E,1,1)
	INR(0x24,H,1,1)
	INR(0x2c,L,1,1)


	case 0x34:				// INR M
	xA=Memory.Peek(HL);
	xB=xA;
	xA++;
	m_setZ(xA);
	m_setS(xA);
	m_setP(xA);
	m_setAC_PLUS(xB,1);\
	Memory.Poke(HL,xA);
	PC++;
	break;


#define DCR(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=SRC;\
xB=xA;\
xA--;\
m_setZ(xA);\
m_setS(xA);\
m_setP(xA);\
m_setAC_MINUS(xB,1);\
SRC=xA;\
PC+=SIZE;\
break;

	DCR(0x3d,A,1,1)
	DCR(0x05,B,1,1)
	DCR(0x0d,C,1,1)
	DCR(0x15,D,1,1)
	DCR(0x1d,E,1,1)
	DCR(0x25,H,1,1)
	DCR(0x2d,L,1,1)

	case 0x35:				// DCR M
	xA=Memory.Peek(HL);
	xB=xA;
	xA--;
	m_setZ(xA);
	m_setS(xA);
	m_setP(xA);
	m_setAC_MINUS(xB,1);
	Memory.Poke(HL,xA);
	PC++;
	break;


#define INX(OPCODE,RP)\
case OPCODE:\
RP++;\
PC++;\
break;

      INX(0x03,BC)
      INX(0x13,DE)
      INX(0x23,HL)
      INX(0x33,SP)

#define DCX(OPCODE,RP)\
case OPCODE:\
RP--;\
PC++;\
break;

      DCX(0x0b,BC)
      DCX(0x1b,DE)
      DCX(0x2b,HL)
      DCX(0x3b,SP)


#define DAD(OPCODE,SRC)\
case OPCODE:\
dw=HL+SRC;\
HL=(WORD) (dw & 0xffff);\
if ((dw & 0x10000)!=0) SetBit(CY,1); else SetBit(CY,0);\
PC++;\
break;

	DAD(0x09,BC)
	DAD(0x19,DE)
	DAD(0x29,HL)
	DAD(0x39,SP)


#define CMP(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
xA=A;\
xB=SRC;\
TEMPW=xA-xB;\
xC=TEMPWL;\
m_setZ(xC);\
m_setS(xC);\
m_setCY(TEMPWH);\
m_setP(xC);\
m_setAC_MINUS(xA,xB);\
PC+=SIZE;\
break;

	CMP(0xbf,A,1,1)
	CMP(0xb8,B,1,1)
	CMP(0xb9,C,1,1)
	CMP(0xba,D,1,1)
	CMP(0xbb,E,1,1)
	CMP(0xbc,H,1,1)
	CMP(0xbd,L,1,1)

	CMP(0xbe,Memory.Peek(HL),1,2)	// CMP M

	CMP(0xfe,byte2,2,2)				// CPI


#define ANA(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
A=A & SRC;\
m_setZ(A);\
m_setS(A);\
m_setP(A);\
SetBit(CY,0);\
SetBit(AC,1);\
PC+=SIZE;\
break;

	ANA(0xa7,A,1,1)
	ANA(0xa0,B,1,1)
	ANA(0xa1,C,1,1)
	ANA(0xa2,D,1,1)
	ANA(0xa3,E,1,1)
	ANA(0xa4,H,1,1)
	ANA(0xa5,L,1,1)


	ANA(0xa6,Memory.Peek(HL),1,2)	// ANA M

	ANA(0xe6,byte2,2,2)		// ANI


#define XRA(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
A=A ^ SRC;\
m_setZ(A);\
m_setS(A);\
m_setP(A);\
SetBit(CY,0);\
SetBit(AC,0);\
PC+=SIZE;\
break;

	XRA(0xaf,A,1,1)
	XRA(0xa8,B,1,1)
	XRA(0xa9,C,1,1)
	XRA(0xaa,D,1,1)
	XRA(0xab,E,1,1)
	XRA(0xac,H,1,1)
	XRA(0xad,L,1,1)

	XRA(0xae,Memory.Peek(HL),1,2)	// XRA M

	XRA(0xee,byte2,2,2)	// XRI


#define ORA(OPCODE,SRC,SIZE,CLK)\
case OPCODE:\
A=A | SRC;\
m_setZ(A);\
m_setS(A);\
m_setP(A);\
SetBit(CY,0);\
SetBit(AC,0);\
PC+=SIZE;\
break;

	ORA(0xb7,A,1,1)
	ORA(0xb0,B,1,1)
	ORA(0xb1,C,1,1)
	ORA(0xb2,D,1,1)
	ORA(0xb3,E,1,1)
	ORA(0xb4,H,1,1)
	ORA(0xb5,L,1,1)

	ORA(0xb6,Memory.Peek(HL),1,2)	// ORA M

	ORA(0xf6,byte2,2,2)		// ORI


	case 0x07:				// RLC
	xA=(A & 0x80)>>7;
	SetBit(CY,xA);
	A=(A<<1) | xA;
	PC++;
	break;
	
	case 0x0f:				// RRC
	xA=A & 1;
	SetBit(CY,xA);
	A=(A>>1) | (xA<<7);
	PC++;
	break;

	case 0x17:				// RAL
	xA=(A & 0x80)>>7;
	xB=ReadBit(CY);
	SetBit(CY,xA);
	A=(A<<1) | xB;
	PC++;
	break;

	case 0x1f:				// RAR
	xA=A & 1;
	xB=ReadBit(CY);
	SetBit(CY,xA);
	A=(A>>1) | (xB<<7);
	PC++;
	break;


	case 0x27:
	// DAA

	TEMPB = FLAGS;
	xA = A;
	TEMPW = A;

	if ( ( ReadBit( AC ) == 1 ) || ( ( TEMPW & 0x0f ) > 9 ) )
	{
		TEMPW += 6;
	}

	if ( ( ReadBit( CY ) == 1 ) || ( TEMPW & 0xf0 ) > 0x90 )
	{
		TEMPW += 0x60;
	}
	else if ( A > 0xf9 )
	{
		TEMPW += 0x60;
	}

	A = TEMPWL;

	m_setZ( A );
	m_setS( A );
	m_setP( A );

	SetBit( X3, 0 );

	if ( ( ReadBit( CY ) == 1 ) || ( xA > 0x99 ) )
	{
		SetBit( CY, 1 );
	}
	else
	{
		SetBit( CY, 0 );
	}

	if ( ( xA & 0xf ) > 9 )
	{
		SetBit( AC, 1 );
	}
	else
	{
		SetBit( AC, 0 );
	}

	if ( ( ( xA & 0x80 ) == 0x80 ) && ( ( A & 0x80 ) == 0x80 ) )
	{
		SetBit( X5, 1 );
	}
	else
	{
		SetBit( X5, 0 );
	}

	if ( ReadBit( S ) == 1 && ( ( ReadBit( CY ) == 1 || ReadBit( AC ) == 1 ) && ReadBit( X5 ) == 0 ) )
	{
		SetBit( V, 1 );
	}
	else
	{
		SetBit( V, 0 );
	}


	// DEBUG DAA DATA FILE
	/*
	// --------------------------
	//	DAA 00000000 --> A: 00000000	SW(SZXAXPXC): 00000000 --> 01000100 

		myfile.Open("w:\\test.txt",CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);

		myfile.SeekToEnd();

		szBuffer="DAA "+CWin85App::Byte2Bin(xA)+" --> A: "+CWin85App::Byte2Bin(A)+
			"    SW(SZXAXPXC): "+CWin85App::Byte2Bin(TEMPB)+" --> "+CWin85App::Byte2Bin(FLAGS)+" \n";

		myfile.WriteString(szBuffer);

		myfile.Close();
	*/

	PC++;
	break;


// -----------------------------------------------------------------------	
// HIDDEN INSTRUCTIONS

	JCON( 0xdd, X5, 0 )	// JNX5
	JCON( 0xfd, X5, 1 )	// JX5
	
	case 0x28:
		// LDHI
		DE = HL + byte2;
		PC = PC + 2;
		break;

	case 0x38:
		// LDSI
		DE = SP + byte2;
		PC = PC + 2;
		break;

	case 0xed:
		// LHLX
		L = Memory.Peek( DE );
		H = Memory.Peek( DE + 1 );
		PC++;
		break;

	case 0xd9:
		// SHLX
		Memory.Poke( DE, L );
		Memory.Poke( DE + 1, H );
		PC++;
		break;


	case (0xcb):
		// RSTV
		if ( ReadBit( V ) == 1 )
		{
			SP--;i = SP;Memory.Poke( i, PCH );
			SP--;i = SP;Memory.Poke( i, PCL );
			PC = 0x40;
		}
		else
		{
			PC++;
		}
		break;

	case 0x10:
		// ARHL
		TEMPW = HL & 1;
		SetBit( CY, TEMPW );
		TEMPW = HL & 0x8000;
		HL = ( HL >> 1 ) | TEMPW;
		PC++;
		break;

	case 0x18:
		// RDEL
		TEMPW = ( DE & 0x8000 ) >> 15;
		xB = ReadBit( CY );
		SetBit( CY, TEMPW );
		SetBit( V, TEMPW );
		DE = ( DE << 1 ) | xB;
		PC++;
		break;

	case 0x08:
		// DSUB
		TEMPD = HL - BC;
		TEMPW = ( WORD ) ( TEMPD & 0xffff );
		m_setZ( TEMPW );
		if ( ( TEMPW & 0x8000 ) == 0x8000 )
		{
			SetBit( S, 1 );
		}
		else
		{
			SetBit( S, 0 );
		}
		m_setCY( TEMPD >> 16 );
		xA = ( BYTE ) ( TEMPW & 0xff );
		xB = ( BYTE ) ( TEMPW >> 8 );
		SetBit( P, ( ParityTable[ xA ] + ParityTable[ xB ] ) & 1 );
		HL = TEMPW;
		PC++;
		break;


// ------------------------------------------------------------------------------

	case 0x20:			// RIM
	A=Irq_Mask & 7;

	if (Irq_Enable==TRUE) A=A | 8;

	if (CWin85App::gIRQMap[3]==1) A=A | 16;
	if (CWin85App::gIRQMap[2]==1) A=A | 32;
	if (CWin85App::gIRQMap[1]==1) A=A | 64;

	// SID ...		???
	PC++;
	break;

	case 0x30:			// SIM
		if ((A & 8)==8)	// Mask Set Enable
		{
		Irq_Mask=A & 7;
		}

		if ((A & 16)==16) // Reset RST7.5
		{
			CWin85App::gIRQMap[1]=0;
		}

	// SOD, SOE ...	???

	PC++;
	break;

	case 0x76:			// HLT
	break;

	
	case 0xfb:			// EI
	Irq_Enable=TRUE;
	PC++;
	break;

	case 0xf3:			// DI
	Irq_Enable=FALSE;
	PC++;
	break;

	case 0xd3:				// OUT

	idev=CWin85App::gWIOMap[byte2];
	if (idev!=-1)
	{
		CWin85App::gDeviceWrite[idev](byte2,A);
	}

	PC=PC+2;
	break;

	case 0xdb:				// IN

	idev=CWin85App::gRIOMap[byte2];
	if (idev!=-1)
	{
		A=CWin85App::gDeviceRead[idev](byte2);
	}

	PC=PC+2;
	break;
	}

	if (ContCheck==FALSE) OpcodeTime=(BYTE) TState[opcode];
	else OpcodeTime=(TState[opcode]>>8)&0xff;

	clocks=clocks+OpcodeTime;

	// IRQ Check

	if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=OpcodeTime;
	if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=OpcodeTime;
	if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=OpcodeTime;

		
		if (CWin85App::gIRQMap[0]==1 && opcode!=0xfb)			// TRAP
		{
		
			m_push(PCH,PCL);
			PC=0x24;
			CWin85App::gIRQMap[0]=0;
			Irq_Enable=FALSE;
			clocks=clocks+5;

		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=5;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=5;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=5;

			return(rtn);
		}

	if (Irq_Enable==TRUE && opcode!=0xfb)
	{
		if (CWin85App::gIRQMap[1]==1 && (Irq_Mask & 4)==0)		// RST 7.5
		{
			m_push(PCH,PCL);
			PC=0x3c;
			CWin85App::gIRQMap[1]=0;
			Irq_Enable=FALSE;
			clocks=clocks+5;

		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=5;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=5;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=5;

			return(rtn);
		}
		if (CWin85App::gIRQMap[2]>0 && (Irq_Mask & 2)==0)		// RST 6.5
		{
			m_push(PCH,PCL);
			PC=0x34;
			Irq_Enable=FALSE;
			clocks=clocks+5;

		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=5;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=5;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=5;

			return(rtn);
		}
		if (CWin85App::gIRQMap[3]>0 && (Irq_Mask & 1)==0)		// RST 5.5
		{
			m_push(PCH,PCL);
			PC=0x2c;
			Irq_Enable=FALSE;
			clocks=clocks+5;

		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=5;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=5;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=5;

			return(rtn);
		}
		if (CWin85App::gIRQMap[4]>0)			// INTR
		{
			m_push(PCH,PCL);

			switch (CWin85App::gIRQMap[5])
			{
			case (0xc7):
				PC=0x00;
				clocks=clocks+3;

		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xcf):
				PC=0x08;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xd7):
				PC=0x10;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xdf):
				PC=0x18;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xe7):
				PC=0x20;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xef):
				PC=0x28;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xf7):
				PC=0x30;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xff):
				PC=0x38;
				clocks=clocks+3;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=3;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=3;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=3;

			break;
			case (0xcd):
				PC=(WORD) CWin85App::gIRQMap[6];
				clocks=clocks+12;
		if (CWin85App::gIRQMap[2]>0) CWin85App::gIRQMap[2]-=12;
		if (CWin85App::gIRQMap[3]>0) CWin85App::gIRQMap[3]-=12;
		if (CWin85App::gIRQMap[4]>0) CWin85App::gIRQMap[4]-=12;

			break;

			default:
			AfxMessageBox("Device Error! check current INTR implementation");
			break;
			}

			Irq_Enable=FALSE;
			return(rtn);
		}

	}

	return (rtn);
 
}


CString CMachine::Byte2Dec(BYTE i)
{
	char txt[10];
	return(itoa(i,txt,10));
}


