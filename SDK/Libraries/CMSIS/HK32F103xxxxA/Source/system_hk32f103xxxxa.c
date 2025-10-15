/*******************************************************************************
* @copyright:  Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:   system_hk32f103xxxxa.c
* @brief:      config system clock
* @author:     AE Team
* @version:    V1.0.0/2023-10-18
*                     1.Initial version
* @log:
*******************************************************************************/
#include "hk32f103xxxxa.h"

/*system clock source*/
#define SYSCLK_SRC_PLL          0x1
#define SYSCLK_SRC_HSI8M        0x2
#define SYSCLK_SRC_HSI28M       0x3
#define SYSCLK_SRC_HSI56M       0x4
#define SYSCLK_SRC_HSE          0x5
#define SYSCLK_SRC_HSE_BYPASS   0x6
#define SYSCLK_SRC_EXTCLK_IO    0x7
#define SYSCLK_SRC_LSI          0x8
#define SYSCLK_SRC_LSE          0x9

/* select sysclk source here */
#define SYSCLK_SOURCE   SYSCLK_SRC_PLL


/* Uncomment the following line if you need to use sysclk freq*/
#if(SYSCLK_SOURCE==SYSCLK_SRC_PLL)
    //#define SYSCLK_HSE8M_PLL_FREQ_24MHz       24000000
    //#define SYSCLK_HSE8M_PLL_FREQ_48MHz       48000000
    #define SYSCLK_HSE8M_PLL_FREQ_72MHz         72000000
    //#define SYSCLK_HSE8M_PLL_FREQ_96MHz       96000000
    //#define SYSCLK_HSE8M_PLL_FREQ_120MHz      120000000

    //#define SYSCLK_HSI_PLL_FREQ_64MHz         64000000
    //#define SYSCLK_HSI_PLL_FREQ_72MHz         72000000
    //#define SYSCLK_HSI_PLL_FREQ_96MHz         96000000
    //#define SYSCLK_HSI_PLL_FREQ_120MHz          120000000

    //CLK config for sai module
    //if config SAI clocl frequency 44.1kHz*256=11.289Mhz
    //HSE8M_pll mode, sysclk=8Mhz/Prediv7*PLLMUL79=90.285Mhz sai_freq=90.285Mhz/8=11.285Mhz
    //HSI56M_Pll mode, sysclk=56M/prediv5*pllmul8=89.6Mhz sai_freq=89.6Mhz/8=11.2Mhz
    //#define SYSCLK_HSE8M_PLL_FREQ_90MHz       90285000
    //#define SYSCLK_HSI_PLL_FREQ_89MHz             89600000

    //if config SAI clocl frequency 192kHz*256=49.152Mhz
    //HSE8M_pll mode, sysclk=8Mhz/Prediv4*PLLMUL49=98Mhz sai_freq=98Mhz/2=49Mhz
    //HSI56M_Pll mode, sysclk=56M/prediv16*pllmu28=98Mhz sai_freq=98Mhz/2=49Mhz
    //#define SYSCLK_HSE8M_PLL_FREQ_98MHz       98000000
    //#define SYSCLK_HSI_PLL_FREQ_98MHz         98000000

    #elif(SYSCLK_SOURCE == SYSCLK_SRC_HSE |SYSCLK_SOURCE == SYSCLK_SRC_HSE_BYPASS)
    #define SYSCLK_FREQ_HSE                 HSE_VALUE
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI8M)
    #define SYSCLK_FREQ_HSI_8M              8000000
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI28M)
    #define SYSCLK_FREQ_HSI_28M             28000000
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_HSI56M)
    #define SYSCLK_FREQ_HSI_56M             56000000
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_EXTCLK_IO)
    #define SYSCLK_FREQ_EXTCLK              EXTCLK_VALUE
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_LSI)
    #define SYSCLK_FREQ_LSI             LSI_VALUE
    #elif(SYSCLK_SOURCE == SYSCLK_SRC_LSE)
    #define SYSCLK_FREQ_LSE             LSE_VALUE
#endif

/* Uncomment the following line if you need to use external SRAM as data memory */
//#define DATA_IN_ExtSRAM


/* start  */

/* 由于39a.h 文件变更， RCC时钟部分的宏值定义被移除，后续是否移植到rcc.h暂不明晰
   此处为了快速调通39Atriming, 将代码涉及的宏定义拷贝到此                  */

#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */


#define  RCC_CFGR_PPRE1_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE1_DIV2                 ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE1_DIV8                 ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE1_DIV16                ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_PPRE2_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00002000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE2_DIV4                 ((uint32_t)0x00002800)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE2_DIV8                 ((uint32_t)0x00003000)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE2_DIV16                ((uint32_t)0x00003800)        /*!< HCLK divided by 16 */

#define  RCC_CFGR2_PREDIV_NONE              ((uint32_t)0x00000000)
//#define  RCC_CFGR2_PREDIV_2                   ((uint32_t)0x00000001)
//#define  RCC_CFGR2_PREDIV_3                   ((uint32_t)0x00000002)
#define  RCC_CFGR2_PREDIV_4                 ((uint32_t)0x00000003)
#define  RCC_CFGR2_PREDIV_5                 ((uint32_t)0x00000004)
#define  RCC_CFGR2_PREDIV_6                 ((uint32_t)0x00000005)
#define  RCC_CFGR2_PREDIV_7                 ((uint32_t)0x00000006)
#define  RCC_CFGR2_PREDIV_8                 ((uint32_t)0x00000007)
#define  RCC_CFGR2_PREDIV_9                 ((uint32_t)0x00000008)
#define  RCC_CFGR2_PREDIV_10                ((uint32_t)0x00000009)
#define  RCC_CFGR2_PREDIV_11                ((uint32_t)0x0000000A)
#define  RCC_CFGR2_PREDIV_12                ((uint32_t)0x0000000B)
#define  RCC_CFGR2_PREDIV_13                ((uint32_t)0x0000000C)
#define  RCC_CFGR2_PREDIV_14                ((uint32_t)0x0000000D)
#define  RCC_CFGR2_PREDIV_15                ((uint32_t)0x0000000E)
#define  RCC_CFGR2_PREDIV_16                ((uint32_t)0x0000000F)

#define  RCC_CFGR4_PLLMULL_Mask             ((uint32_t)0x00000007)
#define  RCC_CFGR4_PLLMULL16                ((uint32_t)0x00000001)        /*!< PLL input clock*2 */
#define  RCC_CFGR4_PLLMULL32                ((uint32_t)0x00000002)        /*!< PLL input clock*3 */
#define  RCC_CFGR4_PLLMULL48                ((uint32_t)0x00000003)        /*!< PLL input clock*4 */
#define  RCC_CFGR4_PLLMULL64                ((uint32_t)0x00000004)        /*!< PLL input clock*5 */
#define  RCC_CFGR4_PLLMULL80                ((uint32_t)0x00000005)        /*!< PLL input clock*6 */
#define  RCC_CFGR4_PLLMULL96                ((uint32_t)0x00000006)        /*!< PLL input clock*7 */
#define  RCC_CFGR4_PLLMULL112               ((uint32_t)0x00000007)        /*!< PLL input clock*7 */

//#define  RCC_CFGR4_PPSS_Mask              ((uint32_t)0x00000010)
#define  RCC_CFGR4_PPSS_HSI56M              ((uint32_t)0x00000010)
#define  RCC_CFGR4_PPSS_HSE                 ((uint32_t)0x00000000)

#define  RCC_CFGR_PLLMULL2                  ((uint32_t)0x00000000)        /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMULL3                  ((uint32_t)0x00040000)        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMULL4                  ((uint32_t)0x00080000)        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMULL5                  ((uint32_t)0x000C0000)        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMULL6                  ((uint32_t)0x00100000)        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMULL7                  ((uint32_t)0x00140000)        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMULL8                  ((uint32_t)0x00180000)        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMULL9                  ((uint32_t)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMULL10                 ((uint32_t)0x00200000)        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMULL11                 ((uint32_t)0x00240000)        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMULL12                 ((uint32_t)0x00280000)        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMULL13                 ((uint32_t)0x002C0000)        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMULL14                 ((uint32_t)0x00300000)        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMULL15                 ((uint32_t)0x00340000)        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMULL16                 ((uint32_t)0x00380000)        /*!< PLL input clock*16 */

//#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
//#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
//#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  RCC_CFGR_SW_HSI                     ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFGR_SW_HSE                     ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)        /*!< PLL selected as system clock */

/*!< SWS configuration */
//#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)        /*!< PLL used as system clock */


#define  RCC_CFGR_PLLSRC_HSI                ((uint32_t)0x00000000)       /*!< HSI clock selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSE                ((uint32_t)0x00010000)        /*!< HSE clock selected as PLL entry clock source */


#define RCC_CFGR5_ESW_LSE                   ((uint32_t)0x00000000)
#define RCC_CFGR5_ESW_LSI                   ((uint32_t)0x00000001)
#define RCC_CFGR5_ESW_HSI56M                ((uint32_t)0x00000002)
#define RCC_CFGR5_ESW_HSI28M                ((uint32_t)0x00000003)
#define RCC_CFGR5_ESW_EXTCLK                ((uint32_t)0x00000004)

#define RCC_CFGR5_ESSS_SET                  ((uint32_t)0x00000800)

#define RCC_CFGR5_ESW_LSE                   ((uint32_t)0x00000000)
#define RCC_CFGR5_ESW_LSI                   ((uint32_t)0x00000001)
#define RCC_CFGR5_ESW_HSI56M                ((uint32_t)0x00000002)
#define RCC_CFGR5_ESW_HSI28M                ((uint32_t)0x00000003)
#define RCC_CFGR5_ESW_EXTCLK                ((uint32_t)0x00000004)

#define RCC_CFGR5_ESWS_LSE                  ((uint32_t)0x00000000)
#define RCC_CFGR5_ESWS_LSI                  ((uint32_t)0x00000010)
#define RCC_CFGR5_ESWS_HSI56                ((uint32_t)0x00000020)
#define RCC_CFGR5_ESWS_HSI28                ((uint32_t)0x00000030)
#define RCC_CFGR5_ESWS_EXTCLK               ((uint32_t)0x00000040)

#define RCC_CFGR5_EXTCLK_SEL_PA1            ((uint32_t)0x00000000)
#define RCC_CFGR5_EXTCLK_SEL_PB1            ((uint32_t)0x00000100)
#define RCC_CFGR5_EXTCLK_SEL_PC7            ((uint32_t)0x00000200)
#define RCC_CFGR5_EXTCLK_SEL_PB7            ((uint32_t)0x00000300)

#define  RCC_CFGR_PLLXTPRE_HSE              ((uint32_t)0x00000000)        /*!< HSE clock not divided for PLL entry */
#define  RCC_CFGR_PLLXTPRE_HSE_Div2         ((uint32_t)0x00020000)        /*!< HSE clock divided by 2 for PLL entry */

#define  RCC_CFGR_Remaider1                 ((uint32_t)0x00040000)
#define  RCC_CFGR_Remaider2                 ((uint32_t)0x00080000)
#define  RCC_CFGR_Remaider3                 ((uint32_t)0x000C0000)
#define  RCC_CFGR_Remaider4                 ((uint32_t)0x00100000)
#define  RCC_CFGR_Remaider5                 ((uint32_t)0x00140000)
#define  RCC_CFGR_Remaider6                 ((uint32_t)0x00180000)
#define  RCC_CFGR_Remaider7                 ((uint32_t)0x001C0000)
#define  RCC_CFGR_Remaider8                 ((uint32_t)0x00200000)
#define  RCC_CFGR_Remaider9                 ((uint32_t)0x00240000)
#define  RCC_CFGR_Remaider10                ((uint32_t)0x00280000)
#define  RCC_CFGR_Remaider11                ((uint32_t)0x002C0000)
#define  RCC_CFGR_Remaider12                ((uint32_t)0x00300000)
#define  RCC_CFGR_Remaider13                ((uint32_t)0x00340000)
#define  RCC_CFGR_Remaider14                ((uint32_t)0x00380000)
#define  RCC_CFGR_Remaider15                ((uint32_t)0x003c0000)

/* end */



/* Uncomment the following line if you need to relocate your vector Table in Internal SRAM. */
// #define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#if( SYSCLK_SOURCE == SYSCLK_SRC_HSE |SYSCLK_SOURCE == SYSCLK_SRC_HSE_BYPASS)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;                           /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSE(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_PLL)
    #if defined SYSCLK_HSE8M_PLL_FREQ_24MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_24MHz;           /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo24_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
        uint32_t SystemCoreClock           = SYSCLK_HSE8M_PLL_FREQ_48MHz;           /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo48_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_72MHz
        uint32_t SystemCoreClock         = SYSCLK_HSE8M_PLL_FREQ_72MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo72_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_90MHz
        uint32_t SystemCoreClock     = SYSCLK_HSE8M_PLL_FREQ_90MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo90_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_98MHz
        uint32_t SystemCoreClock     = SYSCLK_HSE8M_PLL_FREQ_98MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo98_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_96MHz
        uint32_t SystemCoreClock         = SYSCLK_HSE8M_PLL_FREQ_96MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo96_HSE8M_PLL(void);
    #elif defined SYSCLK_HSE8M_PLL_FREQ_120MHz
        uint32_t SystemCoreClock         = SYSCLK_HSE8M_PLL_FREQ_120MHz;            /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo120_HSE8M_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_64MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_64MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo64_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_72MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_72MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo72_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_89MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_89MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo89_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_98MHz
        uint32_t SystemCoreClock           = SYSCLK_HSI_PLL_FREQ_98MHz;             /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo98_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_96MHz
        uint32_t SystemCoreClock             = SYSCLK_HSI_PLL_FREQ_96MHz;           /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo96_HSI_PLL(void);
    #elif defined SYSCLK_HSI_PLL_FREQ_120MHz
        uint32_t SystemCoreClock             = SYSCLK_HSI_PLL_FREQ_120MHz;          /*!< System Clock Frequency (Core Clock) */
        static void SetSysClockTo120_HSI_PLL(void);
    #endif
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI8M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_8M;                      /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_8M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI28M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_28M;                     /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_28M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_HSI56M)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSI_56M;                     /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToHSI_56M(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_EXTCLK_IO)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_EXTCLK;                      /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToEXTCLK(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_LSI)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_LSI;                     /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToLSI(void);
    #elif( SYSCLK_SOURCE == SYSCLK_SRC_LSE)
    uint32_t SystemCoreClock         = SYSCLK_FREQ_LSE;                     /*!< System Clock Frequency (Core Clock) */
    static void SetSysClockToLSE(void);
#endif

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

static void SetSysClock(void);


#ifdef DATA_IN_ExtSRAM
    static void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM */


/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;
    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF8FF0000;
    /* Select SW config as sysclk */
    RCC->CFGR5 &= (~RCC_CFGR5_ESSS);
    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;
    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;
    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
#ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM */
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
}


/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#if defined SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_HSE8M_PLL_FREQ_24MHz
    SetSysClockTo24_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
    SetSysClockTo48_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_72MHz
    SetSysClockTo72_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_90MHz
    SetSysClockTo90_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_98MHz
    SetSysClockTo98_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_96MHz
    SetSysClockTo96_HSE8M_PLL();
#elif defined SYSCLK_HSE8M_PLL_FREQ_120MHz
    SetSysClockTo120_HSE8M_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_64MHz
    SetSysClockTo64_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_72MHz
    SetSysClockTo72_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_89MHz
    SetSysClockTo89_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_98MHz
    SetSysClockTo98_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_96MHz
    SetSysClockTo96_HSI_PLL();
#elif defined SYSCLK_HSI_PLL_FREQ_120MHz
    SetSysClockTo120_HSI_PLL();
#elif defined SYSCLK_FREQ_HSI_8M
    SetSysClockToHSI_8M();
#elif defined SYSCLK_FREQ_HSI_28M
    SetSysClockToHSI_28M();
#elif defined SYSCLK_FREQ_HSI_56M
    SetSysClockToHSI_56M();
#elif defined SYSCLK_FREQ_EXTCLK
    SetSysClockToEXTCLK();
#elif defined SYSCLK_FREQ_LSI
    SetSysClockToLSI();
#elif defined SYSCLK_FREQ_LSE
    SetSysClockToLSE();
#endif
    /* If none of the define above is enabled, the HSI is used as System clock
       source (default after reset) */
}


/**
  * @brief  Setup the external memory controller. Called in startup_hk32f103xxxxa.s
  *          before jump to __main
  * @param  None
  * @retval None
  */
#ifdef DATA_IN_ExtSRAM
/**
  * @brief  Setup the external memory controller.
  *         Called in startup_hk32f103xxxxa_xx.s/.c before jump to main.
  *           This function configures the external SRAM mounted on HK3210E-EVAL
  *         board (HK32 High density devices). This SRAM will be used as program
  *         data memory (including heap and stack).
  * @param  None
  * @retval None
  */
void SystemInit_ExtMemCtl(void)
{
    /*!< FSMC Bank1 NOR/SRAM3 is used for the HK3210E-EVAL, if another Bank is
      required, then adjust the Register Addresses */
    /* Enable FSMC clock */
    RCC->AHBENR = 0x00000114;
    /* Enable AFIO GPIOA, GPIOB, GPIOC, GPIOD and GPIOE clocks */
    RCC->APB2ENR = 0x0000007D;
    //enable FSMC 100 PIN remap
    AFIO->MAPR2 = 0x80000000;
    /* ---------------  SRAM Data lines, NOE and NWE configuration ---------------*/
    /*----------------  SRAM Address lines configuration -------------------------*/
    /*----------------  NOE and NWE configuration --------------------------------*/
    /*----------------  NE3 configuration ----------------------------------------*/
    /*----------------  NBL0, NBL1 configuration ---------------------------------*/
    GPIOA->CRL = 0xB4444444;
    GPIOA->CRH = 0xBBB44BBB;
    GPIOB->CRL = 0x44444BBB;
    GPIOB->CRH = 0x44444444;
    GPIOC->CRL = 0xBBBB4444;
    GPIOC->CRH = 0x444444BB;
    GPIOD->CRL = 0x44BB4BBB;
    GPIOD->CRH = 0xBBBBBBBB;
    GPIOE->CRL = 0xB444B4BB;
    GPIOE->CRH = 0xBBBBBBBB;
    /*----------------  FSMC Configuration ---------------------------------------*/
    /*----------------  Enable FSMC Bank1_SRAM Bank ------------------------------*/
    FSMC_Bank1->BTCR[4] = 0x00001091;
    FSMC_Bank1->BTCR[5] = 0x00000200;
}
#endif /* DATA_IN_ExtSRAM */



#if( SYSCLK_SOURCE == SYSCLK_SRC_HSE|SYSCLK_SOURCE ==SYSCLK_SRC_HSE_BYPASS)
/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
#if  (SYSCLK_SOURCE ==SYSCLK_SRC_HSE_BYPASS)
    RCC->CR |= ((uint32_t)RCC_CR_HSEON | RCC_CR_HSEBYP);
#else
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
#endif

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);

        if (HSE_VALUE <= 24000000)
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        }
        else if (HSE_VALUE <= 48000000)
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_1;
        }
        else
        {
            FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        }

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select HSE as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;

        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_24MHz
/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo24_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_48MHz
/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 1 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSE * 6 = 48 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL6);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up */
    }
}


#elif defined SYSCLK_HSE8M_PLL_FREQ_72MHz
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_90MHz
/**
  * @brief  Sets System clock frequency to 90MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
  *         HSE8M_pll mode, sysclk=8Mhz/Prediv7*PLLMUL79=90.285Mhz sai_freq=90.285Mhz/8=11.285Mhz
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo90_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_3;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = 8Mhz/Prediv7*PLLMUL79 */
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_7);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSE | RCC_CFGR4_PLLMULL64);
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_Remaider15);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSE8M_PLL_FREQ_98MHz
/**
  * @brief  Sets System clock frequency to 98MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
  *         HSE8M_pll mode, sysclk=8Mhz/Prediv4*PLLMUL49=98Mhz sai_freq=98Mhz/2=49Mhz
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo98_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_4;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = 8Mhz/Prediv4*PLLMUL49 */
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_4);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSE | RCC_CFGR4_PLLMULL48);
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_Remaider1);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}


#elif defined SYSCLK_HSE8M_PLL_FREQ_96MHz
/**
  * @brief  Sets System clock frequency to 96MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo96_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_4;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSE * 12 = 96 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL12);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}
#elif defined SYSCLK_HSE8M_PLL_FREQ_120MHz
/**
  * @brief  Sets System clock frequency to 120MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo120_HSE8M_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_6;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSE*15 = 120 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL15);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_64MHz
/**
  * @brief  Sets System clock frequency to 64MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo64_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSI4M * 16 = 64 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMULL16);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_72MHz
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSI56M/7 * 9 = 72 MHz */
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_7);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSI56M );
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_89MHz
/**
  * @brief  Sets System clock frequency to 89MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   sysclk=56M/prediv5*pllmul8=89.6Mhz sai_freq=89.6Mhz/8=11.2Mhz.
  * @param  None
  * @retval None
  */
static void SetSysClockTo89_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_3;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        //  PLL configuration:HSI56M_Pll mode, sysclk=56M/prediv5*pllmul8=89.6Mhz sai_freq=89.6Mhz/8=11.2Mhz
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_5);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSI56M );
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL8);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_98MHz
/**
  * @brief  Sets System clock frequency to 98MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   sysclk=56M/prediv16*pllmu28=98Mhz sai_freq=98Mhz/2=49Mhz.
  * @param  None
  * @retval None
  */
static void SetSysClockTo98_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_4;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        //HSI56M_Pll mode, sysclk=56M/prediv16*pllmu28=98Mhz sai_freq=98Mhz/2=49Mhz
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_16);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSI56M | RCC_CFGR4_PLLMULL16);
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL12);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_96MHz
/**
  * @brief  Sets System clock frequency to 96MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo96_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_3;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        /*  PLL configuration: PLLCLK = HSI56M/7 * 12 = 96 MHz */
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_7);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSI56M );
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL12);
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_HSI_PLL_FREQ_120MHz
/**
  * @brief  Sets System clock frequency to 120MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo120_HSI_PLL(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 4 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_6;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

        /*  PLL configuration: PLLCLK = HSI56M/7 * 15 = 120 MHz */
        RCC->CFGR2 &= (uint32_t)((uint32_t)~(RCC_CFGR2_PREDIV_Mask));
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV_7);
        RCC->CFGR4 &= (uint32_t)((uint32_t)~(RCC_CFGR4_PLLMULL_Mask | RCC_CFGR4_PPSS_Mask ));
        RCC->CFGR4 |= (uint32_t)(RCC_CFGR4_PPSS_HSI56M );
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL15);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
    }
}

#elif defined SYSCLK_FREQ_EXTCLK
static void SetSysClockToEXTCLK(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable EXCLK */
    //enable EXTIO PA1/PB1/PB7/PC7
    /* Configure PA1  as CLOCK input */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*CLOCK select */
    RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_EXTCLK_SEL_Mask));
    RCC->CFGR5 |= (uint32_t)RCC_CFGR5_EXTCLK_SEL_PA1;
    /* Enable Prefetch Buffer */
    //    FLASH->ACR |= FLASH_ACR_PRFTBE;
    /* Flash wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);

    if (EXTCLK_VALUE <= 24000000)
    {
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;
    }
    else if (EXTCLK_VALUE <= 48000000)
    {
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;
    }
    else if (EXTCLK_VALUE <= 72000000)
    {
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
    }
    else if (EXTCLK_VALUE <= 96000000)
    {
        FLASH->ACR |= (uint32_t)FLASH_Latency_3;
    }
    else
    {
        FLASH->ACR |= (uint32_t)FLASH_Latency_5;
    }

    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
    /* Select EXTCLK as system clock source */
    RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_ESW_Mask));
    RCC->CFGR5 |= (uint32_t)RCC_CFGR5_ESW_EXTCLK;
    RCC->CFGR5 |= RCC_CFGR5_ESSS_SET;

    /* Wait till EXTCLK is used as system clock source */
    while ((RCC->CFGR5 & (uint32_t)RCC_CFGR5_ESWS_Mask) != RCC_CFGR5_ESWS_EXTCLK)
    {
    }
}
#elif defined SYSCLK_FREQ_HSI_56M
static void SetSysClockToHSI_56M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR2 |= ((uint32_t)RCC_CR2_HSI56ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR2 & RCC_CR2_HSI56RDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR2 & RCC_CR2_HSI56RDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_2;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select HSI56 as system clock source */
        RCC->CFGR5 |= RCC_CFGR5_ESSS_SET;
        RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_ESW_Mask));
        RCC->CFGR5 |= (uint32_t)RCC_CFGR5_ESW_HSI56M;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR5 & (uint32_t)RCC_CFGR5_ESWS_Mask) != RCC_CFGR5_ESWS_HSI56)
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_HSI_28M
static void SetSysClockToHSI_28M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR2 |= ((uint32_t)RCC_CR2_HSI28ON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR2 & RCC_CR2_HSI28RDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR2 & RCC_CR2_HSI28RDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_1;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select HSI28 as system clock source */
        RCC->CFGR5 |= RCC_CFGR5_ESSS_SET;
        RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_ESW_Mask));
        RCC->CFGR5 |= (uint32_t)RCC_CFGR5_ESW_HSI28M;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR5 & (uint32_t)RCC_CFGR5_ESWS_Mask) != RCC_CFGR5_ESWS_HSI28)
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}
#elif defined SYSCLK_FREQ_HSI_8M
static void SetSysClockToHSI_8M(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select HSI as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;

        /* Wait till HSI is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI)
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}
#elif defined SYSCLK_FREQ_LSI
/* Alias word address of LSION bit */
static void SetSysClockToLSI(void)
{
    __IO uint32_t StartUpCounter = 0, LSIStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable LSI */
    RCC->CSR |= RCC_CSR_LSION;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        LSIStatus = RCC->CSR & RCC_CSR_LSIRDY;
        StartUpCounter++;
    } while ((LSIStatus == 0) && (StartUpCounter != 0xFFFF));

    if ((RCC->CSR & RCC_CSR_LSIRDY) != RESET)
    {
        LSIStatus = (uint32_t)0x01;
    }
    else
    {
        LSIStatus = (uint32_t)0x00;
    }

    if (LSIStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select LSI as system clock source */
        RCC->CFGR5 |= RCC_CFGR5_ESSS_SET;
        RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_ESW_Mask));
        RCC->CFGR5 |= (uint32_t)RCC_CFGR5_ESW_LSI;

        /* Wait till LSI is used as system clock source */
        while ((RCC->CFGR5 & (uint32_t)RCC_CFGR5_ESWS_Mask) != RCC_CFGR5_ESWS_LSI)
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}

#elif defined SYSCLK_FREQ_LSE
static void SetSysClockToLSE(void)
{
    __IO uint32_t StartUpCounter = 0, LSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */
    /* Enable LSE */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE );
    PWR->CR |= PWR_CR_DBP;
    * (uint32_t *) 0x40006C3C = (uint32_t)0x103F ;
    //RCC->BDCR |= RCC_LSE_Bypass | RCC_LSE_ON;
    RCC->BDCR |= RCC_LSE_ON;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        LSEStatus = RCC->BDCR & RCC_BDCR_LSERDY;
        StartUpCounter++;
    } while ((LSEStatus == 0) && (StartUpCounter != 0xFFFFF));

    if ((RCC->BDCR & RCC_BDCR_LSERDY) != RESET)
    {
        LSEStatus = (uint32_t)0x01;
    }
    else
    {
        LSEStatus = (uint32_t)0x00;
    }

    if (LSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        //    FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_Latency_0;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        /* Select LSE as system clock source */
        RCC->CFGR5 |= RCC_CFGR5_ESSS_SET;
        RCC->CFGR5 &= (uint32_t)((uint32_t)~(RCC_CFGR5_ESW_Mask));
        RCC->CFGR5 |= (uint32_t)RCC_CFGR5_ESW_LSE;

        /* Wait till LSE is used as system clock source */
        while ((RCC->CFGR5 & (uint32_t)RCC_CFGR5_ESWS_Mask) != RCC_CFGR5_ESWS_LSE)
        {
        }
    }
    else
    {
        /* If fails to start-up */
    }
}


#endif

