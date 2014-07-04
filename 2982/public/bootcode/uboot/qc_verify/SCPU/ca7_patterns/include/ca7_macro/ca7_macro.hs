
#Cores 0 power up others
.macro POWER_UP_CORES

PUSH    {r0,r1,r2}
##For CA7

#0x1fb0_4080
## CS3_CPU_CTRL1
##clkcore_off              <4:0>       5'b1111       0X20[4:0] //clkcore_off[4] is for L2 and debug clock 
##clkatb_off                           1'b1          0X20[8:8] 
##clkapb_off                           1'b1          0X20[9:9] 
##clktrace_off                         1'b1          0X20[10:10] 
##clkts_off                            1'b1          0X20[11:11] 

#0x1fb0_4084
## CS3_CPU_CTRL2
##nCOREPORESET_i           <3:0>       4'b0000      0X21[3:0] 
##nCORERESET_i             <3:0>       4'b0000      0X21[7:4] 
##nETMRESET_i              <3:0>       4'b0000      0X21[11:8] 
##nDBGRESET_i              <3:0>       4'b0000      0X21[ 15: 12] 
##nL2RESET_i                           1'b0         0X21[16:16] 
##nSOCDBGRESET_i                       1'b0         0X21[17:17] 
##RESETPORn_0_i                        1'b0         0X21[18:18] 
##RESETATn_3_i                         1'b0         0X21[19:19] 
##RESETAPBn_4_i                        1'b0         0X21[20:20] 
##RESETTRCn_5_i                        1'b0         0X21[21:21] 

#0x1fb0_4088
## CS3_CPU_CTRL3
##PWRUP_HAMMER_i           <3:0>       4'b0000      0X22[3 : 0] 
##PWRUP_TRICKLE_i          <3:0>       4'b0000      0X22[7:4] 
##ISOLATE_i                <3:0>       4'b0000      0X22[11:8] 

#0x1fb0_40C0
##  CS3_CPU_STATUS1
##PWRUP_HAMMER_READY_o     <3:0>       4'b0000      0X30[3:0] 
##PWRUP_TRICKLE_READY_o    <3:0>       4'b0000      0X30[7:4] 
##STANDBYWFI_o             <3:0>       4'b0000      0X30[15:12] 

#only cpu0 do powering up
        MRC     p15,0,r0,c0,c0,5
        AND     r0, r0, #0xf
        CMP     r0, #0
        BNE     skip_power_up

        #clock off
        LDR     r1, =CS3_CTRL1_ADDR
        LDR     r2, =0xf0e
        STR     r2, [r1]
        #reset assert
        LDR     r1, =CS3_CTRL2_ADDR
        LDR     r2, =0x10011
        STR     r2, [r1]

       #skip iso/psw when it is phoenix
       # Read bit[25:24] of L2CTLR register to determine the number of CPU 
       # supported by the SCU.
        MRC     p15, 1, r0, c9, c0, 2
        UBFX    r0, r0, #24, #2
        ADD     r0, r0, #1
        #phoenix:2 cores, no iso/psw
        CMP     r0, #4
        BNE     skip_iso_psw

        #iso on
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0xe11
        STR     r2, [r1]
        #power sw on
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0xeff
        STR     r2, [r1]


      #dealy to avoid CPU read unknown in gatesim
      #need to delay about 600ns
        LDR r2, =0x32

#delay_loop
delay_loop:
        SUB r2, #1
        CMP r2, #0
        BNE delay_loop

wait_psw_ready:
        #wait power sw ready
        LDR     r1, =CS3_STS1_ADDR
        LDR     r2, [r1]
        AND     r2, r2 , #0xff
        CMP     r2, #0xff
        BNE     wait_psw_ready

        #iso off
        LDR     r1, =CS3_CTRL3_ADDR
        LDR     r2, =0x0ff
        STR     r2, [r1]

skip_iso_psw :
        #clock on
        LDR     r1, =CS3_CTRL1_ADDR
        MOV     r2, #0x0
        STR     r2, [r1]
        #clock off
        LDR     r1, =CS3_CTRL1_ADDR
        LDR     r2, =0xf0e
        STR     r2, [r1]
        #reset de-assert
        LDR     r1, =CS3_CTRL2_ADDR
        LDR     r2, =0x3fffff
        STR     r2, [r1]
        #clock on
        LDR     r1, =CS3_CTRL1_ADDR
        MOV     r2, #0x0
        STR     r2, [r1]

skip_power_up:

POP    {r0,r1,r2}
.endm
