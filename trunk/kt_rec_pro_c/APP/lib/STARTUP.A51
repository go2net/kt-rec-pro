$NOMOD51

STACK_START     EQU     0x3600

#include "AC309N.h"
#include "config.h"
#include "dac.h"

                NAME    ?C_STARTUP


?C_C51STARTUP   SEGMENT   CODE


                EXTRN CODE (_PLL_init)
                EXTRN CODE (?C_START)
				EXTRN CODE (_dac_on1)
#if (INPUT_OSC_SELECT == PLL_IN_HPRC)
                EXTRN CODE (deal_clk)    
#endif
                PUBLIC  ?C_STARTUP

                CSEG    AT      0x0

?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:
////////////////////////////////////////
				ORL     PCON, #0x08						//OTP CLOCK / 2
                MOV     SP,#low(STACK_START - 1)
				MOV     SPH,#high(STACK_START - 1)

				MOV 	DPTR, #LVDCON
				MOV 	A, #03BH 	   //0x38:2.2V;0x39:2.4V;0x3A:2.6V;0x3B:2.8V;
				MOVX 	@DPTR,A

				MOV     P0PD, #0
				MOV     P0PU, #0
				ORL     USBCON0, #1
				ORL     P3PD, #0xC0
				ANL     P3PU, #~0xC0
				MOV     P4HD, #0
				MOV     P3HD, #0
				MOV     R7, #0
				CALL    _dac_on1

				MOV     R7, #INPUT_OSC_SELECT
				MOV     R5, #SHARE_32768_PERIPHERALS
                CALL    _PLL_init
#if (INPUT_OSC_SELECT == PLL_IN_HPRC)
                call    deal_clk
#endif
				MOV		DPCON, #0x20		//DPTR0 AUTO DEC
                MOV     DPTR,#0x37FF		
XDATALOOP:
                CLR     A
      			MOVX    @DPTR,A
      			MOVX    @DPTR,A
      			MOVX    @DPTR,A
      			MOVX    @DPTR,A
				MOVX    @DPTR,A
      			MOVX    @DPTR,A
      			MOVX    @DPTR,A
      			MOVX    @DPTR,A

				MOV     A,DPL
				XRL     A,#0xFF
				JNZ     XDATALOOP
				MOV     A,DPH
				XRL     A,#0xFF
				JNZ     XDATALOOP

                CLR     A
				MOV		DPCON, A
                MOV     PSW,A
////////////////////////////////////////
				MOV     SP,#low(STACK_START - 1)
				MOV     SPH,#high(STACK_START - 1)               
				
           
		        LJMP    ?C_START

                END
