#ifndef DHT11_H
#define DHT11_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#include <xc.h>

#ifndef _XTAL_FREQ
#error Macro _XTAL_FREQ must be set to MCU clock base frecuency for DHT11 lib to work properly
#endif

#define bitSet(byte, nbit) ((byte) |= (1 << nbit))
#define bitClear(byte, nbit) ((byte) &= ~(1 << nbit))
#define bitCheck(byte, nbit) ((byte >> nbit) & 0x01)
#define bitToggle(byte, nbit) (byte ^= (1 << nbit))

char LeerHT11(char *DHT_TRIS, char *DHT_PORT, char DHT_PIN);
unsigned char LeerByte(char *DHT_PORT, char DHT_PIN);
// unsigned char LeerBit(char *DHT_PORT, char DHT_PIN);

// char *DHT_TRIS = &TRISC;
// char *DHT_PORT = &PORTC;
// char DHT_PIN = 5;

char LeerHT11(char *DHT_TRIS, char *DHT_PORT, char DHT_PIN)
{
  unsigned char i, contr = 0;
  bitClear(*DHT_TRIS, DHT_PIN);
  bitClear(*DHT_PORT, DHT_PIN);
  __delay_ms(18);
  bitSet(*DHT_TRIS, DHT_PIN);
  while (bitCheck(*DHT_PORT, DHT_PIN))
    ;
  __delay_us(40);
  if (bitCheck(*DHT_PORT, DHT_PIN) == 0)
    contr++;
  __delay_us(80);
  if (bitCheck(*DHT_PORT, DHT_PIN))
    contr++;
  while (bitCheck(*DHT_PORT, DHT_PIN))
    ;
  LeerByte(DHT_PORT, DHT_PIN);
  LeerByte(DHT_PORT, DHT_PIN);
  char temp = LeerByte(DHT_PORT, DHT_PIN);
  LeerByte(DHT_PORT, DHT_PIN);
  LeerByte(DHT_PORT, DHT_PIN);
  return temp;
}
unsigned char LeerByte(char *DHT_PORT, char DHT_PIN)
{
  unsigned char resx = 0, i;
  for (i = 8; i > 0; i--)
  {
    unsigned char res = 0;
    while (bitCheck(*DHT_PORT, DHT_PIN) == 0)
      ;
    __delay_us(13);
    if (bitCheck(*DHT_PORT, DHT_PIN))
      res = 0;
    __delay_us(22);
    if (bitCheck(*DHT_PORT, DHT_PIN))
    {
      res = 1;
      while (bitCheck(*DHT_PORT, DHT_PIN))
        ;
    }
    resx = (resx << 1) | res;
  }
  return resx;
}
// unsigned char LeerBit(char *DHT_PORT, char DHT_PIN)
// {
//   unsigned char res = 0;
//   while (bitCheck(*DHT_PORT, DHT_PIN) == 0)
//     ;
//   __delay_us(13);
//   if (bitCheck(*DHT_PORT, DHT_PIN))
//     res = 0;
//   __delay_us(22);
//   if (bitCheck(*DHT_PORT, DHT_PIN))
//   {
//     res = 1;
//     while (bitCheck(*DHT_PORT, DHT_PIN))
//       ;
//   }
//   return res;
// }
#endif