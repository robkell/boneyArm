#!/bin/bash


MUX_PREFIX=/sys/kernel/debug/omap_mux/ 


#PWMS
#echo 0x03 > ${MUX_PREFIX}spi0_sclk
#echo 0x03 > ${MUX_PREFIX}spi0_d0
#echo 0x06 > ${MUX_PREFIX}gpmc_a2 #ehrpwm1A
#echo 0x06 > ${MUX_PREFIX}gpmc_a3 #ehrpwm1b
#echo 0x00 > ${MUX_PREFIX}ecap0_in_pwm0_out
echo 0x04 > ${MUX_PREFIX}gpmc_ad9
echo 0x04 > ${MUX_PREFIX}gpmc_ad8
echo 0x04 > ${MUX_PREFIX}mcasp0_ahclkr
echo 0x01 > ${MUX_PREFIX}mcasp0_fsx
echo 0x01 > ${MUX_PREFIX}mcasp0_aclkx

#PWM GPIOS
echo 0x07 > ${MUX_PREFIX}gpmc_csn1
#echo 0x07 > ${MUX_PREFIX}spi0_d0
echo 0x07 > ${MUX_PREFIX}mcasp0_ahclkx
echo 0x07 > ${MUX_PREFIX}gpmc_ad3


#DIRECTION GPIOS
echo 0x07 > ${MUX_PREFIX}gpmc_ad11
echo 0x07 > ${MUX_PREFIX}gpmc_clk
echo 0x07 > ${MUX_PREFIX}gpmc_csn2
echo 0x07 > ${MUX_PREFIX}gpmc_ad5
echo 0x07 > ${MUX_PREFIX}gpmc_ad4
echo 0x07 > ${MUX_PREFIX}gpmc_ad1
echo 0x07 > ${MUX_PREFIX}gpmc_ad0
echo 0x07 > ${MUX_PREFIX}gpmc_csn0


#SENSE GPIOS
echo 0x3F > ${MUX_PREFIX}gpmc_ad6
echo 0x3F > ${MUX_PREFIX}gpmc_ad7
echo 0x3F > ${MUX_PREFIX}gpmc_ad2
echo 0x3F > ${MUX_PREFIX}gpmc_advn_ale
echo 0x3F > ${MUX_PREFIX}gpmc_oen_ren
echo 0x3F > ${MUX_PREFIX}gpmc_ben0_cle
echo 0x3F > ${MUX_PREFIX}gpmc_wen
echo 0x3F > ${MUX_PREFIX}gpmc_ad13
echo 0x3F > ${MUX_PREFIX}gpmc_ad12
echo 0x3F > ${MUX_PREFIX}gpmc_ad10
echo 0x3F > ${MUX_PREFIX}gpmc_ad15
echo 0x3F > ${MUX_PREFIX}gpmc_ad14
echo 0x3F > ${MUX_PREFIX}gpmc_wait0
echo 0x3F > ${MUX_PREFIX}gpmc_wpn
echo 0x3F > ${MUX_PREFIX}spi0_sclk
echo 0x3F > ${MUX_PREFIX}uart1_rxd
