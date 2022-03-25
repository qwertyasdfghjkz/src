#ifndef __RC522_FUNCTION_H
#define	__RC522_FUNCTION_H


#include "stm32f10x_it.h"


#define          macDummy_Data              0x00


void             PcdReset                   ( void );                       //¸´Î»
void             M500PcdConfigISOType       ( u8 type );                    //¹¤×÷·½Ê½
char             PcdRequest                 ( u8 req_code, u8 * pTagType ); //Ñ°¿¨
char             PcdAnticoll                ( u8 * pSnr);                   //¶Á¿¨ºÅ
char             PcdHalt                    ( void );
char             PcdSelect                  ( uint8_t * pSnr );
char             PcdAuthState               ( uint8_t ucAuth_mode, uint8_t ucAddr, uint8_t * pKey, uint8_t * pSnr );
char             WriteAmount                ( uint8_t ucAddr, uint32_t pData );
char             ReadAmount                 ( uint8_t ucAddr, uint32_t *pData );

char PcdWrite ( uint8_t ucAddr, uint8_t * pData );
char PcdRead ( uint8_t ucAddr, uint8_t * pData );


char IsDataBlock( uint8_t ucAddr );
char PcdWriteString( uint8_t ucAddr, uint8_t *pData);
char PcdReadString( uint8_t ucAddr, uint8_t *pData);

char ChangeKeyA( uint8_t ucAddr, uint8_t *pKeyA );
char WriteDataBlock( uint8_t ucAddr, uint8_t *pData, uint8_t Len);
char ReadDataBlock( uint8_t ucAddr, uint8_t *pData);

char ReadCardID(uint8_t *ID);//¶Á³öID¿¨ºÅ


char Check_IC_Card(uint8_t * ID);
void Verify_IC_Card(void);
void Del_IC_Card(void);
void Add_IC_Card(void);

extern uint8_t ICPassswd[16];//ÃÜÂë


#endif /* __RC522_FUNCTION_H */

