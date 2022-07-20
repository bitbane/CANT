/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL_MASK 0x0C000000U /*!< GPIO1 and GPIO6 share same IO MUX function, GPIO_MUX1 selects one GPIO function: affected bits mask */
#define BOARD_INITPINS_IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL_MASK 0xC0031C05U /*!< GPIO2 and GPIO7 share same IO MUX function, GPIO_MUX2 selects one GPIO function: affected bits mask */
#define BOARD_INITPINS_IOMUXC_GPR_GPR29_GPIO_MUX4_GPIO_SEL_MASK 0x0170U /*!< GPIO4 and GPIO9 share same IO MUX function, GPIO_MUX4 selects one GPIO function: affected bits mask */

/* GPIO_EMC_04 (coord F2), CAN2_SW */
/* Routed pin properties */
#define BOARD_INITPINS_CAN2_SW_PERIPHERAL                                  GPIO4   /*!< Peripheral name */
#define BOARD_INITPINS_CAN2_SW_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN2_SW_CHANNEL                                        4U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN2_SW_GPIO                                        GPIO4   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN2_SW_GPIO_PIN                                       4U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN2_SW_GPIO_PIN_MASK                          (1U << 4U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN2_SW_PORT                                        GPIO4   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN2_SW_PIN                                            4U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN2_SW_PIN_MASK                               (1U << 4U)   /*!< PORT pin mask */

/* GPIO_EMC_05 (coord G5), CAN2_LED */
/* Routed pin properties */
#define BOARD_INITPINS_CAN2_LED_PERIPHERAL                                 GPIO4   /*!< Peripheral name */
#define BOARD_INITPINS_CAN2_LED_SIGNAL                                   gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN2_LED_CHANNEL                                       5U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN2_LED_GPIO                                       GPIO4   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN2_LED_GPIO_PIN                                      5U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN2_LED_GPIO_PIN_MASK                         (1U << 5U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN2_LED_PORT                                       GPIO4   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN2_LED_PIN                                           5U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN2_LED_PIN_MASK                              (1U << 5U)   /*!< PORT pin mask */

/* GPIO_EMC_06 (coord H5), RUN_CANCAT */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_CANCAT_PERIPHERAL                               GPIO4   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_CANCAT_SIGNAL                                 gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_CANCAT_CHANNEL                                     6U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_CANCAT_GPIO                                     GPIO4   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_CANCAT_GPIO_PIN                                    6U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_CANCAT_GPIO_PIN_MASK                       (1U << 6U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_CANCAT_PORT                                     GPIO4   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_CANCAT_PIN                                         6U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_CANCAT_PIN_MASK                            (1U << 6U)   /*!< PORT pin mask */

/* GPIO_EMC_08 (coord H3), RUN_CANT */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_CANT_PERIPHERAL                                 GPIO4   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_CANT_SIGNAL                                   gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_CANT_CHANNEL                                       8U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_CANT_GPIO                                       GPIO4   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_CANT_GPIO_PIN                                      8U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_CANT_GPIO_PIN_MASK                         (1U << 8U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_CANT_PORT                                       GPIO4   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_CANT_PIN                                           8U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_CANT_PIN_MASK                              (1U << 8U)   /*!< PORT pin mask */

/* GPIO_B0_10 (coord D9), RUN_SOCKETCAN */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_SOCKETCAN_PERIPHERAL                            GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_SOCKETCAN_SIGNAL                              gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_SOCKETCAN_CHANNEL                                 10U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_SOCKETCAN_GPIO                                  GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_SOCKETCAN_GPIO_PIN                                10U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_SOCKETCAN_GPIO_PIN_MASK                   (1U << 10U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_SOCKETCAN_PORT                                  GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_SOCKETCAN_PIN                                     10U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_SOCKETCAN_PIN_MASK                        (1U << 10U)   /*!< PORT pin mask */

/* GPIO_B1_01 (coord B11), RUN_TRUCKDEVIL */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_PERIPHERAL                           GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_SIGNAL                             gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_CHANNEL                                17U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_GPIO                                 GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_GPIO_PIN                               17U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_GPIO_PIN_MASK                  (1U << 17U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_PORT                                 GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_PIN                                    17U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_TRUCKDEVIL_PIN_MASK                       (1U << 17U)   /*!< PORT pin mask */

/* GPIO_B1_00 (coord A11), RUN_SW5 */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_SW5_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_SW5_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_SW5_CHANNEL                                       16U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_SW5_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_SW5_GPIO_PIN                                      16U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_SW5_GPIO_PIN_MASK                         (1U << 16U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_SW5_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_SW5_PIN                                           16U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_SW5_PIN_MASK                              (1U << 16U)   /*!< PORT pin mask */

/* GPIO_B0_11 (coord A10), RUN_SW6 */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_SW6_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_SW6_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_SW6_CHANNEL                                       11U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_SW6_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_SW6_GPIO_PIN                                      11U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_SW6_GPIO_PIN_MASK                         (1U << 11U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_SW6_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_SW6_PIN                                           11U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_SW6_PIN_MASK                              (1U << 11U)   /*!< PORT pin mask */

/* GPIO_B0_00 (coord D7), RUN_SW7 */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_SW7_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_SW7_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_SW7_CHANNEL                                        0U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_SW7_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_SW7_GPIO_PIN                                       0U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_SW7_GPIO_PIN_MASK                          (1U << 0U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_SW7_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_SW7_PIN                                            0U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_SW7_PIN_MASK                               (1U << 0U)   /*!< PORT pin mask */

/* GPIO_B0_02 (coord E8), RUN_SW8 */
/* Routed pin properties */
#define BOARD_INITPINS_RUN_SW8_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_RUN_SW8_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_RUN_SW8_CHANNEL                                        2U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_RUN_SW8_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_RUN_SW8_GPIO_PIN                                       2U   /*!< GPIO pin number */
#define BOARD_INITPINS_RUN_SW8_GPIO_PIN_MASK                          (1U << 2U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_RUN_SW8_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_RUN_SW8_PIN                                            2U   /*!< PORT pin number */
#define BOARD_INITPINS_RUN_SW8_PIN_MASK                               (1U << 2U)   /*!< PORT pin mask */

/* GPIO_B1_14 (coord C14), PWR_LED */
/* Routed pin properties */
#define BOARD_INITPINS_PWR_LED_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_PWR_LED_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_PWR_LED_CHANNEL                                       30U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_PWR_LED_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_PWR_LED_GPIO_PIN                                      30U   /*!< GPIO pin number */
#define BOARD_INITPINS_PWR_LED_GPIO_PIN_MASK                         (1U << 30U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_PWR_LED_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_PWR_LED_PIN                                           30U   /*!< PORT pin number */
#define BOARD_INITPINS_PWR_LED_PIN_MASK                              (1U << 30U)   /*!< PORT pin mask */

/* GPIO_B1_15 (coord B14), CAN3_LED */
/* Routed pin properties */
#define BOARD_INITPINS_CAN3_LED_PERIPHERAL                                 GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_CAN3_LED_SIGNAL                                   gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN3_LED_CHANNEL                                      31U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN3_LED_GPIO                                       GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN3_LED_GPIO_PIN                                     31U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN3_LED_GPIO_PIN_MASK                        (1U << 31U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN3_LED_PORT                                       GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN3_LED_PIN                                          31U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN3_LED_PIN_MASK                             (1U << 31U)   /*!< PORT pin mask */

/* GPIO_B0_12 (coord C10), CAN3_SW */
/* Routed pin properties */
#define BOARD_INITPINS_CAN3_SW_PERIPHERAL                                  GPIO2   /*!< Peripheral name */
#define BOARD_INITPINS_CAN3_SW_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN3_SW_CHANNEL                                       12U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN3_SW_GPIO                                        GPIO2   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN3_SW_GPIO_PIN                                      12U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN3_SW_GPIO_PIN_MASK                         (1U << 12U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN3_SW_PORT                                        GPIO2   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN3_SW_PIN                                           12U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN3_SW_PIN_MASK                              (1U << 12U)   /*!< PORT pin mask */

/* GPIO_AD_B1_11 (coord J13), CAN1_SW */
/* Routed pin properties */
#define BOARD_INITPINS_CAN1_SW_PERIPHERAL                                  GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_CAN1_SW_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN1_SW_CHANNEL                                       27U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN1_SW_GPIO                                        GPIO1   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN1_SW_GPIO_PIN                                      27U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN1_SW_GPIO_PIN_MASK                         (1U << 27U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN1_SW_PORT                                        GPIO1   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN1_SW_PIN                                           27U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN1_SW_PIN_MASK                              (1U << 27U)   /*!< PORT pin mask */

/* GPIO_AD_B1_10 (coord L13), CAN1_LED */
/* Routed pin properties */
#define BOARD_INITPINS_CAN1_LED_PERIPHERAL                                 GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_CAN1_LED_SIGNAL                                   gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN1_LED_CHANNEL                                      26U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN1_LED_GPIO                                       GPIO1   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN1_LED_GPIO_PIN                                     26U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN1_LED_GPIO_PIN_MASK                        (1U << 26U)   /*!< GPIO pin mask */
#define BOARD_INITPINS_CAN1_LED_PORT                                       GPIO1   /*!< PORT peripheral base pointer */
#define BOARD_INITPINS_CAN1_LED_PIN                                          26U   /*!< PORT pin number */
#define BOARD_INITPINS_CAN1_LED_PIN_MASK                             (1U << 26U)   /*!< PORT pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
