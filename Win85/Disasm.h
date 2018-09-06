case 0x00:
ts="nop";
break;
case 0x01:
ts="lxi  B,"+Byte32;
break;
case 0x02:
ts="stax B";
break;
case 0x03:
ts="inx  B";
break;
case 0x04:
ts="inr  B";
break;
case 0x05:
ts="dcr  B";
break;
case 0x06:
ts="mvi  B,"+Byte2;
break;
case 0x07:
ts="rlc";
break;
case 0x08:
ts="dsub";
break;
case 0x09:
ts="dad  B";
break;
case 0x0A:
ts="ldax B";
break;
case 0x0B:
ts="dcx  B";
break;
case 0x0C:
ts="inr  C";
break;
case 0x0D:
ts="dcr  C";
break;
case 0x0E:
ts="mvi  C,"+Byte2;
break;
case 0x0F:
ts="rrc";
break;
case 0x10:
ts="arhl";
break;
case 0x11:
ts="lxi  D,"+Byte32;
break;
case 0x12:
ts="stax D";
break;
case 0x13:
ts="inx  D";
break;
case 0x14:
ts="inr  D";
break;
case 0x15:
ts="dcr  D";
break;
case 0x16:
ts="mvi  D,"+Byte2;
break;
case 0x17:
ts="ral";
break;
case 0x18:
ts="rdel";
break;
case 0x19:
ts="dad  D";
break;
case 0x1A:
ts="ldax D";
break;
case 0x1B:
ts="dcx  D";
break;
case 0x1C:
ts="inr  E";
break;
case 0x1D:
ts="dcr  E";
break;
case 0x1E:
ts="mvi  E,"+Byte2;
break;
case 0x1F:
ts="rar";
break;
case 0x20:
ts="rim";
break;
case 0x21:
ts="lxi  H,"+Byte32;
break;
case 0x22:
ts="shld ["+Byte32+"]";
break;
case 0x23:
ts="inx  H";
break;
case 0x24:
ts="inr  H";
break;
case 0x25:
ts="dcr  H";
break;
case 0x26:
ts="mvi  H,"+Byte2;
break;
case 0x27:
ts="daa";
break;
case 0x28:
ts="ldhi "+Byte2;
break;
case 0x29:
ts="dad  H";
break;
case 0x2A:
ts="lhld ["+Byte32+"]";
break;
case 0x2B:
ts="dcx  H";
break;
case 0x2C:
ts="inr  L";
break;
case 0x2D:
ts="dcr  L";
break;
case 0x2E:
ts="mvi  L,"+Byte2;
break;
case 0x2F:
ts="cma";
break;
case 0x30:
ts="sim";
break;
case 0x31:
ts="lxi  SP,"+Byte32;
break;
case 0x32:
ts="sta  ["+Byte32+"]";
break;
case 0x33:
ts="inx  SP";
break;
case 0x34:
ts="inr  M";
break;
case 0x35:
ts="dcr  M";
break;
case 0x36:
ts="mvi  M,"+Byte2;
break;
case 0x37:
ts="stc";
break;
case 0x38:
ts="ldsi "+Byte2;
break;
case 0x39:
ts="dad  SP";
break;
case 0x3A:
ts="lda  ["+Byte32+"]";
break;
case 0x3B:
ts="dcx  SP";
break;
case 0x3C:
ts="inr  A";
break;
case 0x3D:
ts="dcr  A";
break;
case 0x3E:
ts="mvi  A,"+Byte2;
break;
case 0x3F:
ts="cmc";
break;
case 0x40:
ts="mov  B,B";
break;
case 0x41:
ts="mov  B,C";
break;
case 0x42:
ts="mov  B,D";
break;
case 0x43:
ts="mov  B,E";
break;
case 0x44:
ts="mov  B,H";
break;
case 0x45:
ts="mov  B,L";
break;
case 0x46:
ts="mov  B,M";
break;
case 0x47:
ts="mov  B,A";
break;
case 0x48:
ts="mov  C,B";
break;
case 0x49:
ts="mov  C,C";
break;
case 0x4A:
ts="mov  C,D";
break;
case 0x4B:
ts="mov  C,E";
break;
case 0x4C:
ts="mov  C,H";
break;
case 0x4D:
ts="mov  C,L";
break;
case 0x4E:
ts="mov  C,M";
break;
case 0x4F:
ts="mov  C,A";
break;
case 0x50:
ts="mov  D,B";
break;
case 0x51:
ts="mov  D,C";
break;
case 0x52:
ts="mov  D,D";
break;
case 0x53:
ts="mov  D,E";
break;
case 0x54:
ts="mov  D,H";
break;
case 0x55:
ts="mov  D,L";
break;
case 0x56:
ts="mov  D,M";
break;
case 0x57:
ts="mov  D,A";
break;
case 0x58:
ts="mov  E,B";
break;
case 0x59:
ts="mov  E,C";
break;
case 0x5A:
ts="mov  E,D";
break;
case 0x5B:
ts="mov  E,E";
break;
case 0x5C:
ts="mov  E,H";
break;
case 0x5D:
ts="mov  E,L";
break;
case 0x5E:
ts="mov  E,M";
break;
case 0x5F:
ts="mov  E,A";
break;
case 0x60:
ts="mov  H,B";
break;
case 0x61:
ts="mov  H,C";
break;
case 0x62:
ts="mov  H,D";
break;
case 0x63:
ts="mov  H,E";
break;
case 0x64:
ts="mov  H,H";
break;
case 0x65:
ts="mov  H,L";
break;
case 0x66:
ts="mov  H,M";
break;
case 0x67:
ts="mov  H,A";
break;
case 0x68:
ts="mov  L,B";
break;
case 0x69:
ts="mov  L,C";
break;
case 0x6A:
ts="mov  L,D";
break;
case 0x6B:
ts="mov  L,E";
break;
case 0x6C:
ts="mov  L,H";
break;
case 0x6D:
ts="mov  L,L";
break;
case 0x6E:
ts="mov  L,M";
break;
case 0x6F:
ts="mov  L,A";
break;
case 0x70:
ts="mov  M,B";
break;
case 0x71:
ts="mov  M,C";
break;
case 0x72:
ts="mov  M,D";
break;
case 0x73:
ts="mov  M,E";
break;
case 0x74:
ts="mov  M,H";
break;
case 0x75:
ts="mov  M,L";
break;
case 0x76:
ts="hlt";
break;
case 0x77:
ts="mov  M,A";
break;
case 0x78:
ts="mov  A,B";
break;
case 0x79:
ts="mov  A,C";
break;
case 0x7A:
ts="mov  A,D";
break;
case 0x7B:
ts="mov  A,E";
break;
case 0x7C:
ts="mov  A,H";
break;
case 0x7D:
ts="mov  A,L";
break;
case 0x7E:
ts="mov  A,M";
break;
case 0x7F:
ts="mov  A,A";
break;
case 0x80:
ts="add  B";
break;
case 0x81:
ts="add  C";
break;
case 0x82:
ts="add  D";
break;
case 0x83:
ts="add  E";
break;
case 0x84:
ts="add  H";
break;
case 0x85:
ts="add  L";
break;
case 0x86:
ts="add  M";
break;
case 0x87:
ts="add  A";
break;
case 0x88:
ts="adc  B";
break;
case 0x89:
ts="adc  C";
break;
case 0x8A:
ts="adc  D";
break;
case 0x8B:
ts="adc  E";
break;
case 0x8C:
ts="adc  H";
break;
case 0x8D:
ts="adc  L";
break;
case 0x8E:
ts="adc  M";
break;
case 0x8F:
ts="adc  A";
break;
case 0x90:
ts="sub  B";
break;
case 0x91:
ts="sub  C";
break;
case 0x92:
ts="sub  D";
break;
case 0x93:
ts="sub  E";
break;
case 0x94:
ts="sub  H";
break;
case 0x95:
ts="sub  L";
break;
case 0x96:
ts="sub  M";
break;
case 0x97:
ts="sub  A";
break;
case 0x98:
ts="sbb  B";
break;
case 0x99:
ts="sbb  C";
break;
case 0x9A:
ts="sbb  D";
break;
case 0x9B:
ts="sbb  E";
break;
case 0x9C:
ts="sbb  H";
break;
case 0x9D:
ts="sbb  L";
break;
case 0x9E:
ts="sbb  M";
break;
case 0x9F:
ts="sbb  A";
break;
case 0xA0:
ts="ana  B";
break;
case 0xA1:
ts="ana  C";
break;
case 0xA2:
ts="ana  D";
break;
case 0xA3:
ts="ana  E";
break;
case 0xA4:
ts="ana  H";
break;
case 0xA5:
ts="ana  L";
break;
case 0xA6:
ts="ana  M";
break;
case 0xA7:
ts="ana  A";
break;
case 0xA8:
ts="xra  B";
break;
case 0xA9:
ts="xra  C";
break;
case 0xAA:
ts="xra  D";
break;
case 0xAB:
ts="xra  E";
break;
case 0xAC:
ts="xra  H";
break;
case 0xAD:
ts="xra  L";
break;
case 0xAE:
ts="xra  M";
break;
case 0xAF:
ts="xra  A";
break;
case 0xB0:
ts="ora  B";
break;
case 0xB1:
ts="ora  C";
break;
case 0xB2:
ts="ora  D";
break;
case 0xB3:
ts="ora  E";
break;
case 0xB4:
ts="ora  H";
break;
case 0xB5:
ts="ora  L";
break;
case 0xB6:
ts="ora  M";
break;
case 0xB7:
ts="ora  A";
break;
case 0xB8:
ts="cmp  B";
break;
case 0xB9:
ts="cmp  C";
break;
case 0xBA:
ts="cmp  D";
break;
case 0xBB:
ts="cmp  E";
break;
case 0xBC:
ts="cmp  H";
break;
case 0xBD:
ts="cmp  L";
break;
case 0xBE:
ts="cmp  M";
break;
case 0xBF:
ts="cmp  A";
break;
case 0xC0:
ts="rnz";
break;
case 0xC1:
ts="pop  B";
break;
case 0xC2:
ts="jnz  "+Byte32;
break;
case 0xC3:
ts="jmp  "+Byte32;
break;
case 0xC4:
ts="cnz  "+Byte32;
break;
case 0xC5:
ts="push B";
break;
case 0xC6:
ts="adi  "+Byte2;
break;
case 0xC7:
ts="rst  0";
break;
case 0xC8:
ts="rz";
break;
case 0xC9:
ts="ret";
break;
case 0xCA:
ts="jz   "+Byte32;
break;
case 0xCB:
ts="rstv";
break;
case 0xCC:
ts="cz   "+Byte32;
break;
case 0xCD:
ts="call "+Byte32;
break;
case 0xCE:
ts="aci  "+Byte2;
break;
case 0xCF:
ts="rst  1";
break;
case 0xD0:
ts="rnc";
break;
case 0xD1:
ts="pop  D";
break;
case 0xD2:
ts="jnc  "+Byte32;
break;
case 0xD3:
ts="out  "+Byte2;
break;
case 0xD4:
ts="cnc  "+Byte32;
break;
case 0xD5:
ts="push D";
break;
case 0xD6:
ts="sui  "+Byte2;
break;
case 0xD7:
ts="rst  2";
break;
case 0xD8:
ts="rc";
break;
case 0xD9:
ts="shlx";
break;
case 0xDA:
ts="jc  "+Byte32;
break;
case 0xDB:
ts="in   "+Byte2;
break;
case 0xDC:
ts="cc   "+Byte32;
break;
case 0xDD:
ts="jnx5 "+Byte32;
break;
case 0xDE:
ts="sbi  "+Byte2;
break;
case 0xDF:
ts="rst  3";
break;
case 0xE0:
ts="rpo";
break;
case 0xE1:
ts="pop  H";
break;
case 0xE2:
ts="jpo  "+Byte32;
break;
case 0xE3:
ts="xthl";
break;
case 0xE4:
ts="cpo  "+Byte32;
break;
case 0xE5:
ts="push H";
break;
case 0xE6:
ts="ani  "+Byte2;
break;
case 0xE7:
ts="rst  4";
break;
case 0xE8:
ts="rpe";
break;
case 0xE9:
ts="pchl";
break;
case 0xEA:
ts="jpe  "+Byte32;
break;
case 0xEB:
ts="xchg";
break;
case 0xEC:
ts="cpe  "+Byte32;
break;
case 0xED:
ts="lhlx";
break;
case 0xEE:
ts="xri  "+Byte2;
break;
case 0xEF:
ts="rst  5";
break;
case 0xF0:
ts="rp";
break;
case 0xF1:
ts="pop  PSW";
break;
case 0xF2:
ts="jp   "+Byte32;
break;
case 0xF3:
ts="di";
break;
case 0xF4:
ts="cp   "+Byte32;
break;
case 0xF5:
ts="push PSW";
break;
case 0xF6:
ts="ori  "+Byte2;
break;
case 0xF7:
ts="rst  6";
break;
case 0xF8:
ts="rm";
break;
case 0xF9:
ts="sphl";
break;
case 0xFA:
ts="jm   "+Byte32;
break;
case 0xFB:
ts="ei";
break;
case 0xFC:
ts="cm   "+Byte32;
break;
case 0xFD:
ts="jx5  "+Byte32;
break;
case 0xFE:
ts="cpi  "+Byte2;
break;
case 0xFF:
ts="rst  7";
break;
