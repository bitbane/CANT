/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v11.0
processor: MIMXRT1062xxxxA
package_id: MIMXRT1062DVJ6A
mcu_data: ksdk2_0
processor_version: 12.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 79d326a4-2624-4b13-9fbd-fe2b0f998566
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * MPU initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'MPU'
- type: 'mpu_utility'
- mode: 'MPU'
- custom_name_enabled: 'false'
- type_id: 'mpu_utility_bc3ea1f6add76edb6050f698d423d163'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'MPU'
- config_sets:
  - mpu_init:
    - mpuInit: 'disabled'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void MPU_init(void) {
} */

/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table:
      - 0: []
      - 1: []
      - 2: []
      - 3: []
      - 4: []
      - 5: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * GPIO2 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO2'
- type: 'igpio'
- mode: 'GPIO'
- custom_name_enabled: 'false'
- type_id: 'igpio_b1c1fa279aa7069dca167502b8589cb7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIO2'
- config_sets:
  - fsl_gpio:
    - enable_irq_comb_0_15: 'true'
    - gpio_interrupt_comb_0_15:
      - IRQn: 'GPIO2_Combined_0_15_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_comb_16_31: 'true'
    - gpio_interrupt_comb_16_31:
      - IRQn: 'GPIO2_Combined_16_31_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void GPIO2_init(void) {
  /* Make sure, the clock gate for GPIO2 is enabled (e. g. in pin_mux.c) */
  /* Interrupt GPIO2_Combined_0_15_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO2_GPIO_COMB_0_15_IRQN);  function call. */
  /* Interrupt GPIO2_Combined_16_31_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO2_GPIO_COMB_16_31_IRQN);  function call. */
}

/***********************************************************************************************************************
 * GPIO4 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO4'
- type: 'igpio'
- mode: 'GPIO'
- custom_name_enabled: 'false'
- type_id: 'igpio_b1c1fa279aa7069dca167502b8589cb7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIO4'
- config_sets:
  - fsl_gpio:
    - enable_irq_comb_0_15: 'true'
    - gpio_interrupt_comb_0_15:
      - IRQn: 'GPIO4_Combined_0_15_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_comb_16_31: 'true'
    - gpio_interrupt_comb_16_31:
      - IRQn: 'GPIO4_Combined_16_31_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void GPIO4_init(void) {
  /* Make sure, the clock gate for GPIO4 is enabled (e. g. in pin_mux.c) */
  /* Interrupt GPIO4_Combined_0_15_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO4_GPIO_COMB_0_15_IRQN);  function call. */
  /* Interrupt GPIO4_Combined_16_31_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO4_GPIO_COMB_16_31_IRQN);  function call. */
}

/***********************************************************************************************************************
 * LPUART7 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPUART7'
- type: 'lpuart'
- mode: 'polling'
- custom_name_enabled: 'false'
- type_id: 'lpuart_bf01db7d964092f3cf860852cba17f7e'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPUART7'
- config_sets:
  - lpuartConfig_t:
    - lpuartConfig:
      - clockSource: 'LpuartClock'
      - lpuartSrcClkFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '9600'
      - parityMode: 'kLPUART_ParityDisabled'
      - dataBitsCount: 'kLPUART_EightDataBits'
      - isMsb: 'false'
      - stopBitCount: 'kLPUART_OneStopBit'
      - enableMatchAddress1: 'false'
      - matchAddress1: '0'
      - enableMatchAddress2: 'false'
      - matchAddress2: '0'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - enableRxRTS: 'false'
      - enableTxCTS: 'false'
      - txCtsSource: 'kLPUART_CtsSourcePin'
      - txCtsConfig: 'kLPUART_CtsSampleAtStart'
      - rxIdleType: 'kLPUART_IdleTypeStartBit'
      - rxIdleConfig: 'kLPUART_IdleCharacter1'
      - enableTx: 'true'
      - enableRx: 'true'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpuart_config_t LPUART7_config = {
  .baudRate_Bps = 9600UL,
  .parityMode = kLPUART_ParityDisabled,
  .dataBitsCount = kLPUART_EightDataBits,
  .isMsb = false,
  .stopBitCount = kLPUART_OneStopBit,
  .txFifoWatermark = 0U,
  .rxFifoWatermark = 1U,
  .enableRxRTS = false,
  .enableTxCTS = false,
  .txCtsSource = kLPUART_CtsSourcePin,
  .txCtsConfig = kLPUART_CtsSampleAtStart,
  .rxIdleType = kLPUART_IdleTypeStartBit,
  .rxIdleConfig = kLPUART_IdleCharacter1,
  .enableTx = true,
  .enableRx = true
};

static void LPUART7_init(void) {
  LPUART_Init(LPUART7_PERIPHERAL, &LPUART7_config, LPUART7_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * GPIO1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO1'
- type: 'igpio'
- mode: 'GPIO'
- custom_name_enabled: 'false'
- type_id: 'igpio_b1c1fa279aa7069dca167502b8589cb7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIO1'
- config_sets:
  - fsl_gpio:
    - enable_irq_comb_0_15: 'true'
    - gpio_interrupt_comb_0_15:
      - IRQn: 'GPIO1_Combined_0_15_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_comb_16_31: 'true'
    - gpio_interrupt_comb_16_31:
      - IRQn: 'GPIO1_Combined_16_31_IRQn'
      - enable_interrrupt: 'noInit'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int0: 'false'
    - gpio_interrupt_int0:
      - IRQn: 'GPIO1_INT0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int1: 'false'
    - gpio_interrupt_int1:
      - IRQn: 'GPIO1_INT1_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int2: 'false'
    - gpio_interrupt_int2:
      - IRQn: 'GPIO1_INT2_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int3: 'false'
    - gpio_interrupt_int3:
      - IRQn: 'GPIO1_INT3_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int4: 'false'
    - gpio_interrupt_int4:
      - IRQn: 'GPIO1_INT4_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int5: 'false'
    - gpio_interrupt_int5:
      - IRQn: 'GPIO1_INT5_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int6: 'false'
    - gpio_interrupt_int6:
      - IRQn: 'GPIO1_INT6_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_int7: 'false'
    - gpio_interrupt_int7:
      - IRQn: 'GPIO1_INT7_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void GPIO1_init(void) {
  /* Make sure, the clock gate for GPIO1 is enabled (e. g. in pin_mux.c) */
  /* Interrupt GPIO1_Combined_0_15_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO1_GPIO_COMB_0_15_IRQN);  function call. */
  /* Interrupt GPIO1_Combined_16_31_IRQn request in the NVIC is not initialized (disabled by default). */
  /* It can be enabled later by EnableIRQ(GPIO1_GPIO_COMB_16_31_IRQN);  function call. */
}

/***********************************************************************************************************************
 * PIT initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'PIT'
- type: 'pit'
- mode: 'LPTMR_GENERAL'
- custom_name_enabled: 'false'
- type_id: 'pit_ab54f91356454adb874dafbb69e655fd'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'PIT'
- config_sets:
  - fsl_pit:
    - enableRunInDebug: 'false'
    - enableSharedInterrupt: 'false'
    - sharedInterrupt:
      - IRQn: 'PIT_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - timingConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'BOARD_BootClockRUN'
    - channels:
      - 0:
        - channel_id: 'CHANNEL_0'
        - channelNumber: '0'
        - enableChain: 'false'
        - timerPeriod: '1s'
        - startTimer: 'false'
        - enableInterrupt: 'false'
      - 1:
        - channel_id: 'CHANNEL_1'
        - channelNumber: '1'
        - enableChain: 'false'
        - timerPeriod: '1s'
        - startTimer: 'false'
        - enableInterrupt: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const pit_config_t PIT_config = {
  .enableRunInDebug = false
};

static void PIT_init(void) {
  /* Initialize the PIT. */
  PIT_Init(PIT_PERIPHERAL, &PIT_config);
  /* Set channel 0 period to 1 s (75000000 ticks). */
  PIT_SetTimerPeriod(PIT_PERIPHERAL, PIT_CHANNEL_0, PIT_CHANNEL_0_TICKS);
  /* Set channel 1 period to 1 s (75000000 ticks). */
  PIT_SetTimerPeriod(PIT_PERIPHERAL, PIT_CHANNEL_1, PIT_CHANNEL_1_TICKS);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Global initialization */
  ARM_MPU_Disable();

  /* Initialize components */
  GPIO2_init();
  GPIO4_init();
  LPUART7_init();
  GPIO1_init();
  PIT_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
