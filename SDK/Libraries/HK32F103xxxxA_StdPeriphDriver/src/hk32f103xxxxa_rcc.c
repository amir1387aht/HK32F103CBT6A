/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_rcc.c
* @brief:     RCC initialization and configuration
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_rcc.h"
#include "hk32f103xxxxa_conf.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @brief RCC driver modules
  * @{
  @verbatim
   ===============================================================================
                        ##### RCC specific features #####
   ===============================================================================
    [..] After reset the device is running from HSI (8 MHz) with Flash 0 WS,
         all peripherals are off except internal SRAM, Flash and SWD.
         (#)Each clock source can be switched on or off independently when it is not used, to
            optimize power consumption.
         (#) Several prescalers can be used to configure the frequency of the AHB and the APB
             domains. The AHB and APB2 domains maximum frequency is 110 MHz.The APB1 domains
             maximum frequency is 55 MHz.
         (#) The clock for all peripherals is switched off, except the SRAM and FLASH.
         (#) All GPIOs are in input floating state, except the SWD pins which
             are assigned to be used for debug purpose.
    [..] Once the device started from reset, the user application has to:
         (#) Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         (#) Configure the System clock frequency and Flash settings
         (#) Configure the AHB and APB busses prescalers
         (#) Enable the clock for the peripheral(s) to be used
         (#) Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, I2C, UART and IWDG etc)

  *  @endverbatim
  */

/** @defgroup RCC_Private_Macro_Define RCC_Private_Macro_Define
  * @brief   RCC Macro Define table
  * @{
  */

/** @defgroup RCC_Group Private macro define
  * @{
  */

/* RCC Flag Mask */
#define FLAG_Mask                 ((uint8_t)0x1F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};
static __I uint8_t ADCPrescTable2[6] = {0, 10, 12, 14, 16, 20};
static __I uint8_t SAIxPrescTable[8] = {2, 4, 6, 8, 10, 12, 14, 16};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Functions RCC_Private_Functions
  * @{
  */

/** @defgroup RCC_Group1 Internal and external clocks, PLL, CSS and MCO configuration functions
 *  @brief   Internal and external clocks, PLL, CSS and MCO configuration functions
 *
    @verbatim
     ===============================================================================
     ##### Internal-external clocks, PLL, CSS and MCO configuration functions #####
     ===============================================================================
    [..] This section provides functions allowing to configure the internal/external clocks,
         PLL, CSS and MCO.
         (#) HSI (high-speed internal), 8 MHz factory-trimmed RC used directly
             or divided 2 through the PLL as System clock source.Divided 7 from HSI56MHz frequency.
             The HSI clock can be used also to clock the FLITF, I2C1/2 and USART1/2/3 peripherals.
         (#) HSI28, 128 MHz factory-trimmed RC used to clock,Divided 2 from HSI56MHz frequency.
             The HSI28 clock can be used also as System clock.
         (#) HSI56(high-speed internal RC oscillator 56MHz),used as System clock.
         (#) LSI (low-speed internal), 40KHz low consumption RC used as IWDG, RTC clock.
         (#) HSE (high-speed external), 4 to 32 MHz crystal oscillator used directly or
             through the PLL as System clock source.
         (#) LSE (low-speed external), 32.768KHz oscillator.
         (#) PLL (clocked by HSI or HSE), for System clock.
         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M0 NMI (Non-Maskable Interrupt)
             exception vector.
         (#) MCO (microcontroller clock output), used to output LSE, LSI, SYSCLK, HSE,
             HSI28, HSI or PLL lock or PLL CLL/2 on MCO pin.

    @endverbatim
  * @{
  */


/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note   HSI ON and used as system clock source
  * @note   HSI28, HSE and PLL OFF
  * @note   AHB, APB prescaler set to 1.
  * @note   CSS and MCO OFF
  * @note   All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the
  * @note   Peripheral clocks LSI, LSE and clocks.
  * @retval None
  */
void RCC_DeInit(void)
{
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;
    /* Reset USBPRE, PLLMULL, PLLXTPRE, PLLSRC, ADCPRE[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], SW[1:0] and MCO bits */
    RCC->CFGR &= (uint32_t)0xF880000C;
    /* Reset HSEON, CSSON, HSEBYP and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF2FFFF;
    /*Reset PREDIV[3:0] bits*/
    RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;
    /*Reset ADC3SW, ADC2SW, ADC1SW, USBIFSE, USBCLKEN, USBSE, I2C1SW, I2C2SW*/
    RCC->CFGR3 &= (uint32_t)0xE00FC0FF;
    /*Reset HSI28 bit*/
    RCC->CR2 &= (uint32_t)0xFFFBFFFF;
    /*Reset PPSS, PLLMULH bit*/
    RCC->CFGR4 &= (uint32_t)0xFFFFFFE8;
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP  modes.
  * @note   This function resets the CSSON bit, so if the Clock security system(CSS)
  *         was previously enabled you have to enable it again after calling this
  *         function.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                 1 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator
  *            @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_HSE));
    /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
    RCC->CR &= ~RCC_CR_HSEON;
    /* Reset HSEBYP bit */
    RCC->CR &= ~RCC_CR_HSEBYP;

    /* Set the new HSE configuration -------------------------------------------*/
    if (RCC_HSE == RCC_HSE_OFF)
    {
        RCC->CR &= ~RCC_CR_HSEON;
    }
    else if (RCC_HSE == RCC_HSE_ON)
    {
        RCC->CR |= RCC_CR_HSEON;
    }
    else
    {
        RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
    }
}

/**
  * @brief  Waits for HSE start-up.
  * @note   This function waits on HSERDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSE_STARTUP_TIMEOUT in hk32aspin02x.h file. You can tailor it depending
  *         on the HSE crystal used in your application.
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: HSE oscillator is stable and ready to use
  *         - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSEStatus = RESET;

    /* Wait till HSE is ready and if timeout is reached exit */
    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        StartUpCounter++;
    } while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    return (status);
}


/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN4067 for more details on how to
  *         calibrate the HSI.
  * @param  HSITrimValue: specifies the HSI calibration trimming value.
  *         This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_HSITrimValue(uint8_t HSITrimValue)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_CALIBRATION_VALUE(HSITrimValue));
    tmpreg = RCC->CR;
    /* Clear HSITRIM[4:0] bits */
    tmpreg &= ~RCC_CR_HSITRIM;
    /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
    tmpreg |= (uint32_t)HSITrimValue << 3;
    /* Store the new value */
    RCC->CR = tmpreg;
}

/**
  * @brief  Adjusts the Internal Low Speed oscillator (LSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal LSI RC.
  * @param  LSITRIMValue: specifies the LSI Coarse trimming value.
  *         It is loaded automatically from flashoption when the MCU is power-on.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_LSITRIM(uint16_t LSITRIMValue)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_LSI_TRIM_VALUE(LSITRIMValue));
    tmpreg = RCC->LSICTL;
    /* Clear LSITRIM[7:0] bits */
    tmpreg &= ~RCC_LSICTL_LSITRIM;
    /* Set the LSITRIM[7:0] bits according to LSICalibrationValue value */
    tmpreg |= (uint32_t)LSITRIMValue << 8;
    /* Store the new value */
    RCC->LSICTL = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI, the application software should wait on
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the PLL and/or system clock.
  * @note   HSI can not be stopped if it is used directly or through the PLL
  *         as system clock. In this case, you have to select another source
  *         of the system clock then stop the HSI.
  * @note   The HSI is stopped by hardware when entering STOP  modes.
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 1 HSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_HSION;
    }
    else
    {
        RCC->CR &= ~RCC_CR_HSION;
    }
}


/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI28).
  * @note   After enabling the HSI28, the application software should wait on
  *         HSI28RDY flag to be set indicating that HSI28 clock is stable.
  * @note   The HSI28 is stopped by hardware when entering STOP  modes.
  * @param  NewState: new state of the HSI28.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI28 is stopped, HSI28RDY flag goes low after 1 HSI28 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI28Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 |= RCC_CR2_HSI28ON;
    }
    else
    {
        RCC->CR2 &= ~RCC_CR2_HSI28ON;
    }
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator(HSI56).
  * @note   After enabling the HSI56, the application software should wait on
  *         HSI56RDY flag to be set indicating that HSI clock is stable.
  * @note   The HSI56 is stopped by hardware when entering STOP modes.
  * @param  NewState: new state of the HSI56.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI56 is stopped, HSI56RDY flag HSI56 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI56Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 |= RCC_CR2_HSI56ON;
    }
    else
    {
        RCC->CR2 &= ~RCC_CR2_HSI56ON;
    }
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_PLLSource_HSI8M_Div2: HSI oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_HSI56M: HSI clock selected as PLL clock source
  *            @arg RCC_PLLSource_HSE:HSE clock selected as PLL clock source
  * @param  RCC_PLLMul: specifies the PLL entry clock source.
  *         RCC_PLLMul: 2-127
  * @note   The minimum input clock frequency for PLL is 2 MHz (when using HSE as
  *         PLL source).
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
    uint32_t tmp = 0;
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
    assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));
    /* Clear PLLMULL[3:0], PLLXTPRE, and PLLSRC bits */
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE);
    /* Clear PLLMULH bits */
    RCC->CFGR4 &= ~RCC_CFGR4_PLLMULH ;
    tmp = RCC_PLLSource >> 4;

    /* Set the PLL Source and Multiplier */
    if (tmp == 0)
    {
        /* Set the PLL Source and Multiplier */
        RCC->CFGR |= (uint32_t)((uint32_t)RCC_PLLSource << RCC_CFGR_PLLSRC_Pos);
    }
    else
    {
        /* Clear PPSS bits */
        RCC->CFGR4 &= ~RCC_CFGR4_PPSS;
        /* The PLL clock source is determined by the PPSS bits in the CFGR4 register */
        tmpreg = (uint32_t)(RCC_PLLSource & 0x0F) << RCC_CFGR4_PPSS_Pos;
        RCC->CFGR4 |= tmpreg;
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
    }

    if (RCC_PLLMul <= 15)
    {
        tmpreg = (uint32_t)(RCC_PLLMul - 2) << RCC_CFGR_PLLMULL_Pos;
        RCC->CFGR |= tmpreg;
    }
    else
    {
        tmpreg = (uint32_t)(RCC_PLLMul & 0x0F) << RCC_CFGR_PLLMULL_Pos;
        tmp = (uint32_t)(RCC_PLLMul >> 4 ) << RCC_CFGR4_PLLMULH_Pos;
        RCC->CFGR |= tmpreg;
        RCC->CFGR4 |= tmp;
    }
}

/**
  * @brief  Configures the PREDIV division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PREDIV_Div: specifies the PREDIV1 clock division factor.
  *         This parameter can be RCC_PREDIV1_Divx where x:[1,16]
  * @retval None
  */
void RCC_PREDIVConfig(uint32_t RCC_PREDIV_Div)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_PLL_PREDIV(RCC_PREDIV_Div));
    tmpreg = RCC->CFGR2;
    /* Clear PREDIV[3:0] bits */
    tmpreg &= ~(RCC_CFGR2_PREDIV);
    /* Set the PREDIV1 division factor */
    tmpreg |= RCC_PREDIV_Div;
    /* Store the new value */
    RCC->CFGR2 = tmpreg;
}

/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP modes.
  * @param  NewState: new state of the PLL.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_PLLON;
    }
    else
    {
        RCC->CR &= ~RCC_CR_PLLON;
    }
}
/**
  * @}
  */

/** @defgroup RCC_Group2 System AHB and APB busses clocks configuration functions
 *  @brief   System, AHB and APB busses clocks configuration functions
 *
    @verbatim
 ===============================================================================
     ##### System, AHB and APB busses clocks configuration functions #####
 ===============================================================================

    [..] This section provide functions allowing to configure the System, AHB and
         APB busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             and APB (PCLK) clocks are derived from AHB clock through
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
             (+@) The I2C1 clock which is derived from HSI ,PCLK2 or system clock (SYSCLK).
             (+@) The USARTx clock which is derived from HSI14, LSI, APB or LSE.
             (+@) IWDG clock which is always the LSI clock.

         (#) The maximum frequency of the SYSCLK, HCLK and PCLK is 72 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be
             adapted accordingly:
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 30         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       30 < HCLK <= 60        |
        |---------------|------------------------------|
        |2WS(3CPU cycle)|       60 < HCLK <= 90        |
        +----------------------------------------------+
        |4WS(3CPU cycle)|       90 < HCLK <= 120       |
        +----------------------------------------------+

         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and
             prefetch is disabled.

    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
         (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)"
              function
         (++) Check that Flash Prefetch buffer activation is taken into account by
              reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
         (++) Program Flash WS to 1, using "FLASH_SetLatency(FLASH_Latency_1)" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (+) Decreasing the CPU frequency
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (++) Program the new number of WS, using "FLASH_SetLatency()" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)"
              function
         (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
              using the FLASH_GetPrefetchBufferStatus() function.
   @endverbatim
  * @{
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from STOP mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready.
  *         You can use RCC_GetSYSCLKSource() function to know which clock is
  *         currently used as system clock source.
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source
  *         This parameter can be one of the following values:
  *            @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  *            @arg RCC_SYSCLKSource_LSE:    LSE selected as system clock source
  *            @arg RCC_SYSCLKSource_LSI:    LSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI56:  HSI56 selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI28:  HSI28 selected as system clock source
  *            @arg RCC_SYSCLKSource_EXTCLK: EXTCLK selected as system clock source
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t tmpreg = 0, tmp = 0;
    uint32_t StartUpCounter = 0;
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

    /* wait for CLK Ready*/
    do
    {
        switch (RCC_SYSCLKSource)
        {
            case RCC_SYSCLKSource_HSI:
                tmp = RCC->CR & RCC_CR_HSIRDY;
                break;

            case RCC_SYSCLKSource_HSE:
                tmp = RCC->CR & RCC_CR_HSERDY;
                break;

            case RCC_SYSCLKSource_PLLCLK:
                tmp = RCC->CR & RCC_CR_PLLRDY;
                break;

            case RCC_SYSCLKSource_LSE:
                tmp = RCC->BDCR & RCC_BDCR_LSERDY;
                break;

            case RCC_SYSCLKSource_LSI:
                tmp = RCC->CSR & RCC_CSR_LSIRDY;
                break;

            case RCC_SYSCLKSource_HSI56:
                tmp = RCC->CR2 & RCC_CR2_HSI56RDY;
                break;

            case RCC_SYSCLKSource_HSI28:
                tmp = RCC->CR2 & RCC_CR2_HSI28RDY;
                break;
        }

        StartUpCounter++;
    } while ((tmp == 0) && (StartUpCounter != 0xFFFF));

    /* Clear ESSS bits */
    RCC->CFGR5 &= ~RCC_CFGR5_ESSS;
    tmp = RCC_SYSCLKSource >> 4;

    if (tmp == 0)
    {
        tmpreg = RCC->CFGR;
        /* Clear SW[1:0] bits */
        tmpreg &= ~RCC_CFGR_SW;
        /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
        tmpreg |= RCC_SYSCLKSource;
        /* Store the new value */
        RCC->CFGR = tmpreg;
    }
    else
    {
        tmpreg = RCC->CFGR5;
        /* Clear SW[1:0] bits */
        tmpreg &= ~RCC_CFGR5_ESW;
        /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
        tmpreg |= (RCC_SYSCLKSource & 0x0F) | RCC_CFGR5_ESSS;
        /* Store the new value */
        RCC->CFGR5 = tmpreg;
    }
}
/**
  * @brief  Returns the clock source used as system clock.
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following values:
  *            @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  *            @arg RCC_SYSCLKSource_LSE:    LSE selected as system clock source
  *            @arg RCC_SYSCLKSource_LSI:    LSI selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI56:  HSI56 selected as system clock source
  *            @arg RCC_SYSCLKSource_HSI28:  HSI28 selected as system clock source
  *            @arg RCC_SYSCLKSource_EXTCLK: EXTCLK selected as system clock source
  */
uint8_t RCC_GetSYSCLKSource(void)
{
    uint32_t tmp = 0;
    /* Determine the clock source */
    tmp = (RCC->CFGR5 & RCC_CFGR5_ESSS) >> 11;
    
    if (tmp == 0) 
    {
        /* use RCC_CFGR.SWS to set SYSCLK */
        return ((uint8_t)(RCC->CFGR & RCC_CFGR_SWS)) >> 2;
    }
    else
    {
        /* use RCC_CFGR5.ESWS to set SYSCLK */
        return ((uint8_t)((RCC->CFGR5 & RCC_CFGR5_ESWS)) >> 4 | 0x10);
    }
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from
  *         the system clock (SYSCLK).
  *         This parameter can be one of the following values:
  *            @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  *            @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  *            @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  *            @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  *            @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  *            @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  *            @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *            @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *            @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_HCLK(RCC_SYSCLK));
    tmpreg = RCC->CFGR;
    /* Clear HPRE[3:0] bits */
    tmpreg &= ~RCC_CFGR_HPRE;
    /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
    tmpreg |= RCC_SYSCLK;
    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB1 clock (PCLK1).Software must ensure that APB1
  *         clock frequency does not exceed HCLK(Max)/2=60MHz
  * @param  RCC_HCLK: defines the APB1 clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *         This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1: APB1 clock = HCLK
  *            @arg RCC_HCLK_Div2: APB1 clock = HCLK/2
  *            @arg RCC_HCLK_Div4: APB1 clock = HCLK/4
  *            @arg RCC_HCLK_Div8: APB1 clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @retval None
  */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_PCLK(RCC_HCLK));
    tmpreg = RCC->CFGR;
    /* Clear PPRE[2:0] bits */
    tmpreg &= ~RCC_CFGR_PPRE1;
    /* Set PPRE[2:0] bits according to RCC_HCLK value */
    tmpreg |= RCC_HCLK;
    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB2 clock (PCLK2).
  * @param  RCC_HCLK: defines the APB2 clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *         This parameter can be one of the following values:
  *            @arg RCC_HCLK_Div1: APB2 clock = HCLK
  *            @arg RCC_HCLK_Div2: APB2 clock = HCLK/2
  *            @arg RCC_HCLK_Div4: APB2 clock = HCLK/4
  *            @arg RCC_HCLK_Div8: APB2 clock = HCLK/8
  *            @arg RCC_HCLK_Div16: APB2 clock = HCLK/16
  * @retval None
  */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_PCLK(RCC_HCLK));
    tmpreg = RCC->CFGR;
    /* Clear PPRE[2:0] bits */
    tmpreg &= ~RCC_CFGR_PPRE2;
    /* Set PPRE[2:0] bits according to RCC_HCLK value */
    tmpreg |= RCC_HCLK;
    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_PLLRDY: PLL ready interrupt
  * @param  NewState: new state of the specified RCC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /*Enable the selected interrupts */
        RCC->CIR |= (uint32_t)RCC_IT << 8;
    }
    else
    {
        /*Disable the selected interrupts */
        RCC->CIR &= ~((uint32_t)RCC_IT) << 8;
    }
}

/**
  * @brief  Configures the USB clock (USBCLK).
  * @param  RCC_USBCLKSource: specifies the USB clock source. This clock is
  *         derived from the PLL output to 48MHz
  *         This parameter can be one of the following values:
  *            @arg RCC_USBCLKSource_PLLCLK_1Div5:PLL clock(72MHz) divided by 1.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_1Div :PLL clock(48MHz) divided by 1 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_2Div:PLL clock(96MHz) divided by 2 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_2Div5:PLL clock(120MHz) divided by 2.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_3Div :PLL clock(144MHz) divided by 3 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_3Div5:PLL clock(168MHz) divided by 3.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_4Div :PLL clock(192MHz) divided by 4 selected as USB clock source
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
    uint32_t tmpreg = 0, tmp = 0;
    /* Check the parameters */
    assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));
    /* Clear USBSWbits */
    RCC->CFGR3 &= ~RCC_CFGR3_USBSW;
    /* Clear USBPPRE bits */
    RCC->CFGR &= ~RCC_CFGR_USBPRE;
    tmp = RCC_USBCLKSource >> 4;

    if (tmp == 0)
    {
        tmpreg |= ((uint32_t)(RCC_USBCLKSource & 0x1)) << RCC_CFGR_USBPRE_Pos;
        RCC->CFGR |= tmpreg;
    }
    else
    {
        tmpreg |= ((uint32_t)(RCC_USBCLKSource & 0x07)) << RCC_CFGR3_USBSW_Pos;
        RCC->CFGR3 |= tmpreg;
    }
}

/**
  * @brief  Configures the USBIF clock (USBIFCLK).
  * @param  RCC_USBIFCLKSource: specifies the USB clock source. This clock is
  *         derived from the PLL output to 48MHz
  *         This parameter can be one of the following values:
  *            @arg RCC_USBCLKSource_PLLCLK_1Div5:PLL clock(72MHz) divided by 1.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_1Div :PLL clock(48MHz) divided by 1 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_2Div:PLL clock(96MHz) divided by 2 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_2Div5:PLL clock(120MHz) divided by 2.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_3Div :PLL clock(144MHz) divided by 3 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_3Div5:PLL clock(168MHz) divided by 3.5 selected as USB clock source
  *            @arg RCC_USBCLKSource_PLLCLK_4Div :PLL clock(192MHz) divided by 4 selected as USB clock source
  * @retval None
  */
void RCC_USBIFCLKConfig(uint32_t RCC_USBIFCLKSource)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_RCC_USBIFCLK_SOURCE(RCC_USBIFCLKSource));
    tmpreg = RCC->CFGR3 ;
    /* Reset RTCSEL[1:0] bits */
    tmpreg &= ~RCC_CFGR3_USBIFSW;
    tmpreg |= RCC_USBIFCLKSource;
    /* Select the RTC clock source */
    RCC->CFGR3 = tmpreg;
}

/**
  * @brief  Configures the ADC3 clock (ADC3CLK).
  * @param  RCC_ADCCLK: defines the ADC clock divider. This clock is derived from
  *         the APB2 clock (PCLK2).
  *         This parameter can be one of the following values:
  *            @arg RCC_PCLK2_Div2: ADC clock = PCLK2/2
  *            @arg RCC_PCLK2_Div4: ADC clock = PCLK2/4
  *            @arg RCC_PCLK2_Div6: ADC clock = PCLK2/6
  *            @arg RCC_PCLK2_Div8: ADC clock = PCLK2/8
  *            @arg RCC_PCLK2_Div10: ADC clock = PCLK2/10
  *            @arg RCC_PCLK2_Div12: ADC clock = PCLK2/12
  *            @arg RCC_PCLK2_Div14: ADC clock = PCLK2/14
  *            @arg RCC_PCLK2_Div16: ADC clock = PCLK2/16
  *            @arg RCC_PCLK2_Div20: ADC clock = PCLK2/20
  * @retval None
  */
void RCC_ADC3CLKConfig(uint32_t RCC_ADCCLK)
{
    uint32_t tmpreg = 0, tmp = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADCPRE(RCC_ADCCLK));
    tmp = RCC_ADCCLK >> 4;

    if (tmp == 0)
    {
        tmpreg = RCC->CFGR ;
        /* Clear ADCPRE[1:0] bits */
        tmpreg &= ~RCC_CFGR_ADCPRE;
        /* Set ADCPRE[1:0] bits */
        tmpreg |=  RCC_ADCCLK << RCC_CFGR_ADCPRE_Pos  ;
        /* Store the new value */
        RCC->CFGR = tmpreg;
    }
    else
    {
        tmpreg = RCC->CFGR3;
        /* Clear ADC3SW[2:0] bits */
        tmpreg &= ~RCC_CFGR3_ADC3SW;
        /* Set ADC3SW[2:0] bits */
        tmpreg |=  (RCC_ADCCLK & 0x0F) << RCC_CFGR3_ADC3SW_Pos  ;
        /* Store the new value */
        RCC->CFGR3 = tmpreg;
    }
}

/**
  * @brief  Configures the ADC2 clock (ADC2CLK).
  * @param  RCC_ADCCLK: defines the ADC clock divider. This clock is derived from
  *         the APB2 clock (PCLK2).
  *         This parameter can be one of the following values:
  *            @arg RCC_PCLK2_Div2: ADC clock = PCLK2/2
  *            @arg RCC_PCLK2_Div4: ADC clock = PCLK2/4
  *            @arg RCC_PCLK2_Div6: ADC clock = PCLK2/6
  *            @arg RCC_PCLK2_Div8: ADC clock = PCLK2/8
  *            @arg RCC_PCLK2_Div10: ADC clock = PCLK2/10
  *            @arg RCC_PCLK2_Div12: ADC clock = PCLK2/12
  *            @arg RCC_PCLK2_Div14: ADC clock = PCLK2/14
  *            @arg RCC_PCLK2_Div16: ADC clock = PCLK2/16
  *            @arg RCC_PCLK2_Div20: ADC clock = PCLK2/20
  * @retval None
  */
void RCC_ADC2CLKConfig(uint32_t RCC_ADCCLK)
{
    uint32_t tmpreg = 0, tmp = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADCPRE(RCC_ADCCLK));
    tmp = RCC_ADCCLK >> 4;

    if (tmp == 0)
    {
        tmpreg = RCC->CFGR ;
        /* Clear ADCPRE[1:0] bits */
        tmpreg &= ~RCC_CFGR_ADCPRE;
        /* Set ADCPRE[1:0] bits */
        tmpreg |=  RCC_ADCCLK << RCC_CFGR_ADCPRE_Pos  ;
        /* Store the new value */
        RCC->CFGR = tmpreg;
    }
    else
    {
        tmpreg = RCC->CFGR3;
        /* Clear ADC2SW[2:0] bits */
        tmpreg &= ~RCC_CFGR3_ADC2SW;
        /* Set ADC2SW[2:0] bits */
        tmpreg |=  (RCC_ADCCLK & 0x0F) << RCC_CFGR3_ADC2SW_Pos  ;
        /* Store the new value */
        RCC->CFGR3 = tmpreg;
    }
}

/**
  * @brief  Configures the ADC1 clock (ADC1CLK).
  * @param  RCC_ADCCLK: defines the ADC clock divider. This clock is derived from
  *         the APB2 clock (PCLK2).
  *         This parameter can be one of the following values:
  *            @arg RCC_PCLK2_Div2: ADC clock = PCLK2/2
  *            @arg RCC_PCLK2_Div4: ADC clock = PCLK2/4
  *            @arg RCC_PCLK2_Div6: ADC clock = PCLK2/6
  *            @arg RCC_PCLK2_Div8: ADC clock = PCLK2/8
  *            @arg RCC_PCLK2_Div10: ADC clock = PCLK2/10
  *            @arg RCC_PCLK2_Div12: ADC clock = PCLK2/12
  *            @arg RCC_PCLK2_Div14: ADC clock = PCLK2/14
  *            @arg RCC_PCLK2_Div16: ADC clock = PCLK2/16
  *            @arg RCC_PCLK2_Div20: ADC clock = PCLK2/20
  * @retval None
  */
void RCC_ADC1CLKConfig(uint32_t RCC_ADCCLK )
{
    uint32_t tmpreg = 0, tmp = 0;
    /* Check the parameters */
    assert_param(IS_RCC_ADCPRE(RCC_ADCCLK));
    tmp = RCC_ADCCLK >> 4;

    if (tmp == 0)
    {
        tmpreg = RCC->CFGR ;
        /* Clear ADCPRE[1:0] bits */
        tmpreg &= ~RCC_CFGR_ADCPRE;
        /* Set ADCPRE[1:0] bits */
        tmpreg |=  RCC_ADCCLK << RCC_CFGR_ADCPRE_Pos  ;
        /* Store the new value */
        RCC->CFGR = tmpreg;
    }
    else
    {
        tmpreg = RCC->CFGR3;
        /* Clear ADC1SW[2:0] bits */
        tmpreg &= ~RCC_CFGR3_ADC1SW;
        /* Set ADC1SW[2:0] bits */
        tmpreg |=  (RCC_ADCCLK & 0x0F) << RCC_CFGR3_ADC1SW_Pos  ;
        /* Store the new value */
        RCC->CFGR3 = tmpreg;
    }
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note   As the LSE is in the LSE Control domain and write access is denied to this
  *         domain after reset, you have to enable write access using
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                 0 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator
  *            @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_LSE));
    /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
    RCC->BDCR  &= ~(RCC_BDCR_LSEON);
    RCC->BDCR  &= ~(RCC_BDCR_LSEBYP);

    /* Set the new LSE configuration -------------------------------------------*/
    if (RCC_LSE == RCC_LSE_OFF)
    {
        RCC->BDCR &= ~RCC_BDCR_LSEON;
    }
    else if (RCC_LSE == RCC_LSE_ON)
    {
        RCC->BDCR |= RCC_BDCR_LSEON;
    }
    else
    {
        RCC->BDCR |= RCC_BDCR_LSEON | RCC_BDCR_LSEBYP;
    }
}
/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG.
  * @note   LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 3 LSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Set the LSI configuration -------------------------------------------*/
    if (NewState != DISABLE)
    {
        RCC->CSR |= RCC_CSR_LSION;
    }
    else
    {
        RCC->CSR &= ~RCC_CSR_LSION;
    }
}

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it can't be changed unless the RTC
  *         is reset using RCC_BackupResetCmd function, or by a Power On Reset.
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *         This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_HSE_Div128: HSE divided by 32 selected as RTC clock
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
    /* Select the RTC clock source */
    RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |= RCC_BDCR_RTCEN;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_RTCEN;
    }
}

/**
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
  * @note   The frequency returned by this function is not the real frequency
  *         in the chip. It is calculated based on the predefined constant and
  *         the source selected by RCC_SYSCLKConfig():
  * @note   If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
  * @note   If SYSCLK source is PLL, function returns constant HSE_VALUE(**)
  *         or HSI_VALUE(*) multiplied by the PLL factors.
  * @note   If SYSCLK source is HSI56, function returns constant HSI56_VALUE(***)
  * @note   (*) HSI_VALUE is a constant defined in system_hk32f103xxxxa.c file (default value
  *         8 MHz) but the real value may vary depending on the variations
  *         in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().
  * @note   (**) HSE_VALUE is a constant defined in system_hk32f103xxxxa.c file (default value
  *         8 MHz), user has to ensure that HSE_VALUE is same as the real
  *         frequency of the crystal used. Otherwise, this function may
  *         return wrong result.
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK, HCLK and/or PCLK clock changes, this function
  *         must be called to update the structure's field. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull1 = 0, pllsource = 0, presc = 0, pllclk = 0;
    uint32_t prediv1factor = 0,  temp = 0 ;
    uint32_t  pllmull = 0, pllmull2 = 0 ;
    /* Get PLL clock source and multiplication factor ----------------------*/
    pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;

    if (pllsource == 0)
    {
        pllclk = HSI_VALUE >> 1;
    }
    else
    {
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;
        pllsource = (RCC->CFGR4 & RCC_CFGR4_PPSS) >> RCC_CFGR4_PPSS_Pos;

        if (pllsource == 0x00)
        {
            /* HSE oscillator clock selected as PREDIV1 clock entry */
            pllclk = HSE_VALUE / prediv1factor;
        }
        else if (pllsource == 0x01)
        {
            /* HSI oscillator clock selected as PREDIV1 clock entry */
            pllclk = HSI56M_VALUE / prediv1factor;
        }
    }

    pllmull1 = RCC->CFGR4 & RCC_CFGR4_PLLMULH;

    if (pllmull1 == 0x000)
    {
        pllmull = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> RCC_CFGR_PLLMULL_Pos) + 2 ;
        pllclk = pllclk * pllmull;
    }
    else
    {
        pllmull2 = (RCC->CFGR & RCC_CFGR_PLLMULL) >> RCC_CFGR_PLLMULL_Pos;
        pllmull = (((RCC->CFGR4 & RCC_CFGR4_PLLMULH) << 4) + pllmull2);
        pllclk = pllclk * pllmull;
    }

    /* Get SYSCLK source -------------------------------------------------------*/
    if (((RCC->CFGR5 & RCC_CFGR5_ESSS) >> RCC_CFGR5_ESSS_Pos) != 0)
    {
        tmp = (RCC->CFGR5 & RCC_CFGR5_ESWS) >> RCC_CFGR5_ESWS_Pos;
        tmp = tmp | 0x10;
    }
    else
    {
        tmp = (RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos;
    }

    switch (tmp)
    {
        case 0x00:  /* HSI used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;

        case 0x01:  /* HSE used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;

        case 0x02:  /* PLL used as system clock */
            RCC_Clocks->SYSCLK_Frequency = pllclk;
            break;

        case 0x10:  /* LSE used as system clock */
            RCC_Clocks->SYSCLK_Frequency = LSE_VALUE;
            break;

        case 0x11:  /* LSI used as system clock */
            RCC_Clocks->SYSCLK_Frequency = LSI_VALUE;
            break;

        case 0x12:  /* HSI56 used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI56M_VALUE;
            break;

        case 0x13:  /* HSI28 used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI28M_VALUE;
            break;

        case 0x14:  /* EXTCLK_GPIOINPUT used as system clock */
            RCC_Clocks->SYSCLK_Frequency = EXTCLK_VALUE;
            break;

        default: /* HSI used as system clock */
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
    }

    /* Compute HCLK, PCLK clocks frequencies -----------------------------------*/
    /* Get HCLK prescaler */
    tmp = RCC->CFGR & RCC_CFGR_HPRE;
    tmp = tmp >> RCC_CFGR_HPRE_Pos;
    presc = APBAHBPrescTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
    /* Get PCLK1(APB1) prescaler */
    tmp = RCC->CFGR & RCC_CFGR_PPRE1;
    tmp = tmp >> RCC_CFGR_PPRE1_Pos;
    presc = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    /* Get PCLK2(APB2) prescaler; max 60MHz */
    tmp = RCC->CFGR & RCC_CFGR_PPRE2;
    tmp = tmp >> RCC_CFGR_PPRE2_Pos;
    presc = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    /* ADC3CLK clock frequency */
    tmp = (RCC->CFGR3 &  RCC_CFGR3_ADC3SW) >> RCC_CFGR3_ADC3SW_Pos ;

    if (tmp == 0)
    {
        /* Get ADC3CLK prescaler */
        temp = RCC->CFGR & RCC_CFGR_ADCPRE;
        temp = temp >> RCC_CFGR_ADCPRE_Pos;
        presc = ADCPrescTable[temp];
        /* ADCCLK clock frequency */
        RCC_Clocks->ADC3CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }
    else
    {
        presc = ADCPrescTable2[tmp];
        /* ADCCLK clock frequency */
        RCC_Clocks->ADC3CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }

    /* ADC2CLK clock frequency */
    tmp = (RCC->CFGR3 &  RCC_CFGR3_ADC2SW) >> RCC_CFGR3_ADC2SW_Pos ;

    if (tmp == 0)
    {
        /* Get ADC2CLK prescaler */
        temp = RCC->CFGR & RCC_CFGR_ADCPRE;
        temp = temp >> RCC_CFGR_ADCPRE_Pos;
        presc = ADCPrescTable[temp];
        /* ADCCLK clock frequency */
        RCC_Clocks->ADC2CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }
    else
    {
        presc = ADCPrescTable2[tmp];
        /* ADC2CLK clock frequency */
        RCC_Clocks->ADC2CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }

    /* ADC1CLK clock frequency */
    tmp = (RCC->CFGR3 &  RCC_CFGR3_ADC1SW) >> RCC_CFGR3_ADC1SW_Pos ;

    if (tmp == 0)
    {
        /* Get ADC1CLK prescaler */
        temp = RCC->CFGR & RCC_CFGR_ADCPRE;
        temp = temp >> RCC_CFGR_ADCPRE_Pos;
        presc = ADCPrescTable[temp];
        /* ADC1CLK clock frequency */
        RCC_Clocks->ADC1CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }
    else
    {
        presc = ADCPrescTable2[tmp];
        /* ADC1CLK clock frequency */
        RCC_Clocks->ADC1CLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
    }

    /* USBIF clock frequency */
    tmp = (RCC->CFGR3 &  RCC_CFGR3_USBIFSW) >> RCC_CFGR3_USBIFSW_Pos ;

    switch (tmp)
    {
        case 0x0:
            /* USBIF clock frequency */
            RCC_Clocks->USBIF_Frequency = RCC_Clocks->PCLK1_Frequency ;
            break;

        case 0x1:
            /* USBIF clock frequency */
            RCC_Clocks->USBIF_Frequency = RCC_Clocks->PCLK1_Frequency / 2;
            break;

        case 0x2:
            /* USBIF clock frequency */
            RCC_Clocks->USBIF_Frequency = RCC_Clocks->PCLK1_Frequency / 3 ;
            break;

        case 0x3:
            /* USBIF clock frequency */
            RCC_Clocks->USBIF_Frequency = RCC_Clocks->PCLK1_Frequency / 4 ;
            break;

        default:
            /* USBIF clock frequency */
            RCC_Clocks->USBIF_Frequency = RCC_Clocks->PCLK1_Frequency ;
            break;
    }
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *            @arg RCC_AHBPeriph_DMA1
  *            @arg RCC_AHBPeriph_DMA2
  *            @arg RCC_AHBPeriph_SRAM
  *            @arg RCC_AHBPeriph_FLITF
  *            @arg RCC_AHBPeriph_CRC
  *            @arg RCC_AHBPeriph_FSMC
  *            @arg RCC_AHBPeriph_SDIO
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHBENR |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBENR &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_AFIO
  *            @arg RCC_APB2Periph_GPIOA
  *            @arg RCC_APB2Periph_GPIOB
  *            @arg RCC_APB2Periph_GPIOC
  *            @arg RCC_APB2Periph_GPIOD
  *            @arg RCC_APB2Periph_GPIOE
  *            @arg RCC_APB2Periph_ADC1
  *            @arg RCC_APB2Periph_ADC2
  *            @arg RCC_APB2Periph_TIM1
  *            @arg RCC_APB2Periph_SPI1
  *            @arg RCC_APB2Periph_TIM8
  *            @arg RCC_APB2Periph_USART1
  *            @arg RCC_APB2Periph_ADC3
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2ENR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2
  *            @arg RCC_APB1Periph_TIM3
  *            @arg RCC_APB1Periph_TIM4
  *            @arg RCC_APB1Periph_TIM5
  *            @arg RCC_APB1Periph_TIM6
  *            @arg RCC_APB1Periph_TIM7
  *            @arg RCC_APB1Periph_WWDG
  *            @arg RCC_APB1Periph_SPI2
  *            @arg RCC_APB1Periph_SPI3
  *            @arg RCC_APB1Periph_USART2
  *            @arg RCC_APB1Periph_USART3
  *            @arg RCC_APB1Periph_USART4
  *            @arg RCC_APB1Periph_USART5
  *            @arg RCC_APB1Periph_I2C1
  *            @arg RCC_APB1Periph_I2C2
  *            @arg RCC_APB1Periph_USB
  *            @arg RCC_APB1Periph_CAN1
  *            @arg RCC_APB1Periph_BKP
  *            @arg RCC_APB1Periph_PWR
  *            @arg RCC_APB1Periph_DAC
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1ENR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_AFIO
  *            @arg RCC_APB2Periph_GPIOA
  *            @arg RCC_APB2Periph_GPIOB
  *            @arg RCC_APB2Periph_GPIOC
  *            @arg RCC_APB2Periph_GPIOD
  *            @arg RCC_APB2Periph_GPIOE
  *            @arg RCC_APB2Periph_ADC1
  *            @arg RCC_APB2Periph_ADC2
  *            @arg RCC_APB2Periph_TIM1
  *            @arg RCC_APB2Periph_SPI1
  *            @arg RCC_APB2Periph_TIM8
  *            @arg RCC_APB2Periph_USART1
  *            @arg RCC_APB2Periph_ADC3
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2RSTR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2RSTR &= ~RCC_APB2Periph;
    }
}


/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2
  *            @arg RCC_APB1Periph_TIM3
  *            @arg RCC_APB1Periph_TIM4
  *            @arg RCC_APB1Periph_TIM5
  *            @arg RCC_APB1Periph_TIM6
  *            @arg RCC_APB1Periph_TIM7
  *            @arg RCC_APB1Periph_WWDG
  *            @arg RCC_APB1Periph_SPI2
  *            @arg RCC_APB1Periph_SPI3
  *            @arg RCC_APB1Periph_USART2
  *            @arg RCC_APB1Periph_USART3
  *            @arg RCC_APB1Periph_USART4
  *            @arg RCC_APB1Periph_USART5
  *            @arg RCC_APB1Periph_I2C1
  *            @arg RCC_APB1Periph_I2C2
  *            @arg RCC_APB1Periph_USB
  *            @arg RCC_APB1Periph_CAN1
  *            @arg RCC_APB1Periph_BKP
  *            @arg RCC_APB1Periph_PWR
  *            @arg RCC_APB1Periph_DAC
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1RSTR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1RSTR &= ~RCC_APB1Periph;
    }
}
/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_AHBPeriph_DMA1: DMA1 clock
  *            @arg RCC_AHBPeriph_DMA2: DMA2 clock
  *            @arg RCC_AHBPeriph_CRC: CRC clock
  *            @arg RCC_AHBPeriph_FSMC: FSMC clock
  *            @arg RCC_AHBPeriph_SDIO: SDIO clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHBRST2 |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBRST2 &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph2: specifies the AHB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *            @arg RCC_AHBPeriph2_CACHE: CACHE clock
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriph2ResetCmd(uint32_t RCC_AHBPeriph2, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH2(RCC_AHBPeriph2));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHBRST3 |= RCC_AHBPeriph2;
    }
    else
    {
        RCC->AHBRST3 &= ~RCC_AHBPeriph2;
    }
}

/**
  * @brief  Forces or releases the Backup domain reset.
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |= RCC_BDCR_BDRST;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_BDRST;
    }
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
  * @param  NewState: new state of the Clock Security System.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_CSSON;
    }
    else
    {
        RCC->CR &= ~RCC_CR_CSSON;
    }
}

/**
  * @brief  Selects the clock source to output on MCO pin.
  * @param  RCC_MCO: specifies the clock source to output.
  *            @arg RCC_MCO can be one of the following values:
  *            @arg RCC_MCO_NoClock
  *            @arg RCC_MCO_SYSCLK
  *            @arg RCC_MCO_HSI8M
  *            @arg RCC_MCO_HSE
  *            @arg RCC_MCO_PLLCLK_Div2
  *            @arg RCC_MCO_LSI
  *            @arg RCC_MCO_LSE
  *            @arg RCC_MCO_HSI28
  * @param  RCC_MCOPRE :can be one of the following values:
  *            @arg RCC_MCOPrescaler_1
  *            @arg RCC_MCOPrescaler_2
  *            @arg RCC_MCOPrescaler_4
  *            @arg RCC_MCOPrescaler_8
  *            @arg RCC_MCOPrescaler_16
  *            @arg RCC_MCOPrescaler_32
  *            @arg RCC_MCOPrescaler_64
  *            @arg RCC_MCOPrescaler_128
  * @retval None
  */
void RCC_MCOConfig(uint32_t RCC_MCO, uint32_t RCC_MCOPRE)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0 ;
    /* Check the parameters */
    assert_param(IS_RCC_MCO(RCC_MCO));
    assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPRE));
    tmpreg1 = RCC->CFGR;
    tmpreg2 = RCC->CFGR5;
    /* Clear  MCO[2:0] bits */
    tmpreg1 &= ~RCC_CFGR_MCO;
    /* Clear  MCO3, MCOPRE[2:0] bits */
    tmpreg2 &= ~(RCC_CFGR5_MCOPRE | RCC_CFGR5_MCO) ;
    /* Set the RCC_MCOSource  */
    tmpreg1 |= (RCC_MCO & 0x07 ) << RCC_CFGR_MCO_Pos ;
    /* Set the RCC_MCOSource and RCC_MCOPrescaler */
    tmpreg2 |= ((RCC_MCO >> 3 ) & 0x01) << RCC_CFGR5_MCO_Pos ;
    /* Set the  RCC_MCOPrescaler */
    tmpreg2 |= RCC_MCOPRE ;
    /* Store the new value */
    RCC->CFGR = tmpreg1;
    RCC->CFGR5 = tmpreg2;
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLAG_HSIRDY
  *            @arg RCC_FLAG_HSERDY
  *            @arg RCC_FLAG_PLLRDY
  *            @arg RCC_FLAG_LSERDY
  *            @arg RCC_FLAG_LSIRDY
  *            @arg RCC_FLAG_PINRST
  *            @arg RCC_FLAG_PORRST
  *            @arg RCC_FLAG_SFTRST
  *            @arg RCC_FLAG_IWDGRST
  *            @arg RCC_FLAG_WWDGRST
  *            @arg RCC_FLAG_LPWRRST
  *            @arg RCC_FLAG_HSI28RDY
  *            @arg RCC_FLAG_HSI56RDY
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
    uint32_t tmp = 0;
    uint32_t statusreg = 0;
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RCC_FLAG(RCC_FLAG));
    /* Get the RCC register index */
    tmp = RCC_FLAG >> 5;

    if (tmp == 1)              
    {
        /* The flag to check is in CR register */
        statusreg = RCC->CR;
    }
    else if (tmp == 2)          
    {
        /* The flag to check is in BDCR register */
        statusreg = RCC->BDCR;
    }
    else if (tmp == 3)         
    {
        /* The flag to check is in CSR register */
        statusreg = RCC->CSR;
    }
    else                       
    {
        /* The flag to check is in CS2 register */
        statusreg = RCC->CR2;
    }

    /* Get the flag position */
    tmp = RCC_FLAG & FLAG_Mask;     //FLAG_Mask=0x1f

    if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Clears the RCC reset flags.
  *         The reset flags are: RCC_FLAG_OBLRST, RCC_FLAG_PINRST, RCC_FLAG_V18PWRRSTF,
  *         RCC_FLAG_PORRST, RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
  *         RCC_FLAG_LPWRRST.
  * @retval None
  */
void RCC_ClearFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_IT: specifies the RCC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_PLLRDY: PLL ready interrupt
  *            @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval The new state of RCC_IT (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint32_t RCC_IT)
{
    ITStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RCC_GET_IT(RCC_IT));

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the RCC_IT status */
    return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT: specifies the interrupt pending bit to clear.
  *         For this parameter can be any combination of the
  *         following values:
  *            @arg RCC_IT_LSIRDY: LSI ready interrupt
  *            @arg RCC_IT_LSERDY: LSE ready interrupt
  *            @arg RCC_IT_HSIRDY: HSI ready interrupt
  *            @arg RCC_IT_HSERDY: HSE ready interrupt
  *            @arg RCC_IT_PLLRDY: PLL ready interrupt
  *            @arg RCC_IT_CSS: Clock Security System interrupt
  * @retval None
  */
void RCC_ClearITPendingBit(uint32_t RCC_IT)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLEAR_IT(RCC_IT));
    /* Clear the selected interrupt pending bits */
    RCC->CIR |= (uint32_t)RCC_IT << 16;
}


/**
  * @brief  Adjusts the CSS counter threshold control.
  * @note   After the CSS function is enabled, RCC uses the HSI clock to sample the HSE frequency division waveform.
  *         If the FREQUENCY of HSE input is very low, CSS outages can be triggered even when the HSE is still working.
  *         You can adjust the value through CSS_THRESHOLD[6:0] to avoid. When different thresholds are configured,
  *         the lowest HSE frequency determined by the CSS is about 4M/ CSS_THRESHOLD[6:0].
  * @param  CSS_THRESHOLD_Value: specifies the CSS counter threshold control value.
  *         This parameter must be a number between 0 and 0x3F.
  * @retval None
  */
void RCC_CSSThresholdConfig(uint8_t CSS_THRESHOLD_Value)
{
    uint32_t tmpreg = 0;
    assert_param(IS_CSS_THRESHOLD_Value(CSS_THRESHOLD_Value));
    tmpreg = RCC->HSECTL ;
    tmpreg &= ~RCC_HSECTL_CSS_THRESHOLD;
    tmpreg |= (uint32_t)CSS_THRESHOLD_Value << 25 ;
    RCC->HSECTL = tmpreg;
}



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
