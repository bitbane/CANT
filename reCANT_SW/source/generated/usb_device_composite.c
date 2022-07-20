/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))
#include "usb_hsdcd.h"
#elif (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
#include "usb_phydcd.h"
#endif

#include "usb_device_composite.h"
        
#include "usb_device_interface_0_cic_vcom.h"

#if ((defined(FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U)) && \
    ((defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)) || \
     (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U))))
#include "usb_phy.h"
#endif
#if (defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U))
#include "fsl_power.h"
#endif
#if (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U))
#if !((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#include "fsl_mrt.h"
#endif
#include "fsl_power.h"
#endif
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
#include "fsl_adapter_timer.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
#define TIMER_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_OscClk)
#endif

#if (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)) && \
	!(defined(FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#define CHIRP_ISSUE_WORKAROUND_NEEDED 1
#else
#define CHIRP_ISSUE_WORKAROUND_NEEDED 0
#endif


/* USB PHY configuration */
#ifndef BOARD_USB_PHY_D_CAL
#define BOARD_USB_PHY_D_CAL (0x0CU)
#endif
#ifndef BOARD_USB_PHY_TXCAL45DP
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#endif
#ifndef BOARD_USB_PHY_TXCAL45DM
#define BOARD_USB_PHY_TXCAL45DM (0x06U)
#endif

/* Undefined class type for the empty definition of the device class structure. */
#define UNDEFINED_CLASS_TYPE ((usb_device_class_type_t)(-1))
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void USB_DeviceIsrEnable(void);
#if USB_DEVICE_CONFIG_USE_TASK
void USB_DeviceTaskFn(void *deviceHandle);
#endif

static void USB_DeviceClockInit(void);

#if CHIRP_ISSUE_WORKAROUND_NEEDED
void USB_DeviceHsPhyChirpIssueWorkaround(void);
void USB_DeviceDisconnected(void);
#endif

#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))

#elif (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
extern void HW_TimerControl(uint8_t enable);
#endif



static usb_status_t USB_DeviceCallback(usb_device_handle handle, uint32_t event, void *param);
static usb_status_t USB_UpdateInterfaceSetting(uint8_t interface, uint8_t alternateSetting);

extern usb_status_t USB_DeviceInterface0CicVcomInit(usb_device_composite_struct_t *deviceComposite);
extern usb_status_t USB_DeviceInterface0CicVcomCallback(class_handle_t handle, uint32_t event, void *param);
extern usb_status_t USB_DeviceInterface0CicVcomSetConfiguration(class_handle_t handle, uint8_t configuration_index);
extern usb_status_t USB_DeviceInterface0CicVcomSetInterface(class_handle_t handle, uint8_t alternateSetting);

extern usb_status_t USB_DeviceInterface1DicVcomSetInterface(class_handle_t handle, uint8_t alternateSetting);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
uint32_t g_halTimerHandle[(HAL_TIMER_HANDLE_SIZE + 3) / 4];
#endif

#if CHIRP_ISSUE_WORKAROUND_NEEDED
volatile uint32_t hwTick;
uint32_t timerInterval;
uint32_t isConnectedToFsHost = 0U;
uint32_t isConnectedToHsHost = 0U;
#endif

usb_device_composite_struct_t g_UsbDeviceComposite;

extern usb_device_class_struct_t g_UsbDeviceInterface0CicVcomConfig;

static usb_device_class_struct_t s_UsbDeviceInterfaceNullConfig = {
    (usb_device_interface_list_t *)NULL,
	UNDEFINED_CLASS_TYPE,
    0,
};

/* Set class configurations. */
usb_device_class_config_struct_t g_CompositeClassConfig[USB_COMPOSITE_INTERFACE_COUNT] = {
    {
        USB_DeviceInterface0CicVcomCallback, (class_handle_t)NULL, &g_UsbDeviceInterface0CicVcomConfig,
    },
    {
        (usb_device_class_callback_t)NULL, (class_handle_t)NULL, &s_UsbDeviceInterfaceNullConfig,
    },
};

/* Set class configuration list. */
usb_device_class_config_list_struct_t g_UsbDeviceCompositeConfigList = {
    g_CompositeClassConfig, USB_DeviceCallback, USB_COMPOSITE_INTERFACE_COUNT,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
void HW_TimerCallback(void *param)
{
    g_UsbDeviceComposite.hwTick++;
    USB_DeviceUpdateHwTick(g_UsbDeviceComposite.deviceHandle, g_UsbDeviceComposite.hwTick);
}

void HW_TimerInit(void)
{
    hal_timer_config_t halTimerConfig;
    halTimerConfig.timeout            = 1000;
    halTimerConfig.srcClock_Hz        = TIMER_SOURCE_CLOCK;
    halTimerConfig.instance           = 0U;
    hal_timer_handle_t halTimerHandle = &g_halTimerHandle[0];
    HAL_TimerInit(halTimerHandle, &halTimerConfig);
    HAL_TimerInstallCallback(halTimerHandle, HW_TimerCallback, NULL);
}
void HW_TimerControl(uint8_t enable)
{
    if (enable)
    {
        HAL_TimerEnable(g_halTimerHandle);
    }
    else
    {
        HAL_TimerDisable(g_halTimerHandle);
    }
}
#endif


#if CHIRP_ISSUE_WORKAROUND_NEEDED
/*!
 * @brief Initialization on MRT timer
 *
 * @param uint8_t Instance of timer.
 * @interval uint32_t Interrupt interval.
 *
 */
void USB_TimerInit(uint8_t instance, uint32_t interval)
{
    MRT_Type *instanceList[] = MRT_BASE_PTRS;
    IRQn_Type instanceIrq[] = MRT_IRQS;
    /* Structure of initialize MRT */
    mrt_config_t mrtConfig;
    /* mrtConfig.enableMultiTask = false; */
    MRT_GetDefaultConfig(&mrtConfig);
    /* Init mrt module */
    MRT_Init(instanceList[instance], &mrtConfig);
    /* Setup Channel 0 to be repeated */
    MRT_SetupChannelMode(instanceList[instance], kMRT_Channel_0, kMRT_RepeatMode);
    /* Enable timer interrupts for channel 0 */
    MRT_EnableInterrupts(instanceList[instance], kMRT_Channel_0, kMRT_TimerInterruptEnable);
    timerInterval = interval;
    /* Enable at the NVIC */
    EnableIRQ(instanceIrq[instance]);
}

/*!
 * @brief Function used to start/stop the MRT timer
 *
 * @param uint8_t MRT timer instance.
 * @param uint8_t Set to 0 to disable the timer. Other values enable the timer.
 */
void USB_TimerInt(uint8_t instance, uint8_t enable)
{
    MRT_Type *instanceList[] = MRT_BASE_PTRS;
    uint32_t mrt_clock;
    mrt_clock = CLOCK_GetFreq(kCLOCK_BusClk);
    if (enable)
    {
        /* Start channel 0 */
        MRT_StartTimer(instanceList[instance], kMRT_Channel_0, USEC_TO_COUNT(timerInterval, mrt_clock));
    }
    else
    {
        /* Stop channel 0 */
        MRT_StopTimer(instanceList[instance], kMRT_Channel_0);
        /* Clear interrupt flag.*/
        MRT_ClearStatusFlags(instanceList[instance], kMRT_Channel_0, kMRT_TimerInterruptFlag);
    }
}

/*!
 * @brief MRT0 interrupt service routine
 */
void MRT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);
    if (hwTick)
    {
        hwTick--;
        if (!hwTick)
        {
            USB_TimerInt(0, 0);
        }
    }
    else
    {
        USB_TimerInt(0, 0);
    }
}

/*!
 * @brief Clears device connected flag for chirp issue
 */
void USB_DeviceDisconnected(void)
{
    isConnectedToFsHost = 0U;
}

/*!
 * @brief Chirp issue workaround
 *
 * This is a work-around to fix the HS device Chirping issue.
 * The device (IP3511HS controller) will sometimes not work when the cable
 * is attached first time after a Power-on Reset.
 */
void USB_DeviceHsPhyChirpIssueWorkaround(void)
{
    uint32_t startFrame = USBHSD->INFO & USBHSD_INFO_FRAME_NR_MASK;
    uint32_t currentFrame;
    uint32_t isConnectedToFsHostFlag = 0U;

    if ((!isConnectedToHsHost) && (!isConnectedToFsHost))
    {
        if (((USBHSD->DEVCMDSTAT & USBHSD_DEVCMDSTAT_Speed_MASK) >> USBHSD_DEVCMDSTAT_Speed_SHIFT) == 0x01U)
        {
            USBHSD->DEVCMDSTAT = (USBHSD->DEVCMDSTAT & (~(0x0F000000U | USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK))) |
                                 USBHSD_DEVCMDSTAT_PHY_TEST_MODE(0x05U);
            hwTick = 100;
            USB_TimerInt(0, 1);

            while (hwTick)
            {
            }

            currentFrame = USBHSD->INFO & USBHSD_INFO_FRAME_NR_MASK;

            if (currentFrame != startFrame)
            {
                isConnectedToHsHost = 1U;
            }
            else
            {
                hwTick = 1;
                USB_TimerInt(0, 1);

                while (hwTick)
                {
                }

                currentFrame = USBHSD->INFO & USBHSD_INFO_FRAME_NR_MASK;

                if (currentFrame != startFrame)
                {
                    isConnectedToHsHost = 1U;
                }
                else
                {
                    isConnectedToFsHostFlag = 1U;
                }
            }

            USBHSD->DEVCMDSTAT = (USBHSD->DEVCMDSTAT & (~(0x0F000000U | USBHSD_DEVCMDSTAT_PHY_TEST_MODE_MASK)));
            USBHSD->DEVCMDSTAT = (USBHSD->DEVCMDSTAT & (~(0x0F000000U | USBHSD_DEVCMDSTAT_DCON_MASK)));
            hwTick = 510;
            USB_TimerInt(0, 1);

            while (hwTick)
            {
            }

            USBHSD->DEVCMDSTAT = (USBHSD->DEVCMDSTAT & (~(0x0F000000U))) | USB_DEVCMDSTAT_DCON_C_MASK;
            USBHSD->DEVCMDSTAT =
                (USBHSD->DEVCMDSTAT & (~(0x0F000000U))) | USBHSD_DEVCMDSTAT_DCON_MASK | USB_DEVCMDSTAT_DRES_C_MASK;

            if (isConnectedToFsHostFlag)
            {
                isConnectedToFsHost = 1U;
            }
        }
    }
}
#endif

/*!
 * @brief USB Interrupt service routine.
 *
 * This function serves as the USB interrupt service routine.
 *
 * @return None.
 */
void USB_OTG1_IRQHandler(void)
{
    USB_DeviceEhciIsrFunction(g_UsbDeviceComposite.deviceHandle);

#if (defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)) || (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U))
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
    exception return operation might vector to incorrect interrupt */
    __DSB();
#endif
}

/*!
 * @brief Initializes USB specific setting that was not set by the Clocks tool.
 */
static void USB_DeviceClockInit(void)
{
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL, BOARD_USB_PHY_TXCAL45DP, BOARD_USB_PHY_TXCAL45DM,
    };
    uint32_t notUsed = 0;
	
    if (USB_DEVICE_CONTROLLER_ID == kUSB_ControllerEhci0)
    {
        CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);
    }
    else
    {
        CLOCK_EnableUsbhs1PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs1Clock(kCLOCK_Usb480M, 480000000U);
    }

    USB_EhciPhyInit(USB_DEVICE_CONTROLLER_ID, notUsed, &phyConfig);
}

/*!
 * @brief Enables interrupt service routines for device.
 */
void USB_DeviceIsrEnable(void)
{
    uint8_t irqNumber;
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)
    uint8_t usbDeviceKhciIrq[] = USB_IRQS;
    irqNumber = usbDeviceKhciIrq[USB_DEVICE_CONTROLLER_ID - kUSB_ControllerKhci0];
#endif
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
    uint8_t usbDeviceEhciIrq[] = USBHS_IRQS;
    irqNumber = usbDeviceEhciIrq[USB_DEVICE_CONTROLLER_ID - kUSB_ControllerEhci0];
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)
    uint8_t usbDeviceIP3511Irq[] = USB_IRQS;
    irqNumber = usbDeviceIP3511Irq[USB_DEVICE_CONTROLLER_ID - kUSB_ControllerLpcIp3511Fs0];
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
    uint8_t usbDeviceIP3511Irq[] = USBHSD_IRQS;
    irqNumber = usbDeviceIP3511Irq[USB_DEVICE_CONTROLLER_ID - kUSB_ControllerLpcIp3511Hs0];
#endif
/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_DEVICE_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_DEVICE_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

#if USB_DEVICE_CONFIG_USE_TASK
/*!
 * @brief USB device task. When USB device does not use interrupt service routines, this function should be called periodically.
 *
 * @param *deviceHandle Pointer to device handle.
 */
void USB_DeviceTaskFn(void *deviceHandle)
{
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)
        USB_DeviceKhciTaskFunction(deviceHandle);
#endif
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
        USB_DeviceEhciTaskFunction(deviceHandle);
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)
    USB_DeviceLpcIp3511TaskFunction(deviceHandle);
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
    USB_DeviceLpcIp3511TaskFunction(deviceHandle);
#endif
}
#endif

/*!
 * @brief Standard device callback function.
 *
 * This function handle the USB standard event. For more information, please refer to usb spec chapter 9.
 * @param handle          The USB device handle.
 * @param event           The USB device event type.
 * @param *param          The parameter of the device specific request.
 * @return usb_status_t Returns status of operation.
 */
static usb_status_t USB_DeviceCallback(usb_device_handle handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint16_t *temp16 = (uint16_t *)param;
    uint8_t *temp8 = (uint8_t *)param;
    uint8_t count = 0U;

    switch (event)
    {
        case kUSB_DeviceEventBusReset:
            /* USB bus reset signal detected */
            for (count = 0U; count < USB_COMPOSITE_INTERFACE_COUNT; count++)
            {
                g_UsbDeviceComposite.currentInterfaceAlternateSetting[count] = 0U;
            }
            g_UsbDeviceComposite.attach = 0U;
            g_UsbDeviceComposite.currentConfiguration = 0U;
            error = kStatus_USB_Success;
#if CHIRP_ISSUE_WORKAROUND_NEEDED
            /* The work-around is used to fix the HS device Chirping issue.
             * Please refer to the implementation for the detail information.
             */
            USB_DeviceHsPhyChirpIssueWorkaround();
#endif
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U) || \
    (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U))
            /* Get USB speed to configure the device, including max packet size and interval of the endpoints. */
            if (kStatus_USB_Success == USB_DeviceClassGetSpeed(USB_DEVICE_CONTROLLER_ID, &g_UsbDeviceComposite.speed))
            {
                USB_DeviceSetSpeed(handle, g_UsbDeviceComposite.speed);
            }
#endif
            break;
#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
        case kUSB_DeviceEventAttach:
            g_UsbDeviceComposite.connectStateChanged = 1U;
            g_UsbDeviceComposite.connectState        = 1U;
            error                                    = kStatus_USB_Success;
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (((defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))) ||  \
     (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U)))
            g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionInit;

#else
#if (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)) || \
    (defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U))
#else
            /*Add one delay here to make the DP pull down long enough to allow host to detect the previous disconnection.*/
            SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
            error = USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
#endif
#endif
            break;
        case kUSB_DeviceEventDetach:
            g_UsbDeviceComposite.connectStateChanged = 1U;
            g_UsbDeviceComposite.connectState        = 0U;
            g_UsbDeviceComposite.attach              = 0U;
            error                                   = kStatus_USB_Success;
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (((defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))) ||  \
     (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U)))
            g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionInit;
#else
            g_UsbDeviceComposite.attach = 0;
#if (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)) || \
    (defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U))
			error = USB_DeviceStop(g_UsbDeviceComposite.deviceHandle);
#else
#if (defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U))
            USB_DeviceDisconnected();
#endif
#endif
#endif
            break;
#endif
        case kUSB_DeviceEventSetConfiguration:
            if (0 == (*temp8))
            {
                g_UsbDeviceComposite.attach = 0U;
                g_UsbDeviceComposite.currentConfiguration = 0U;
                /* The device is detached - the zero configuration is set. */
                USB_DeviceInterface0CicVcomSetConfiguration(g_UsbDeviceComposite.interface0CicVcomHandle, *temp8);
                error = kStatus_USB_Success;
            }
            else if (USB_COMPOSITE_CONFIGURATION_INDEX == (*temp8))
            {
                /* Set device configuration request */
                g_UsbDeviceComposite.attach = 1U;
                g_UsbDeviceComposite.currentConfiguration = *temp8;
                USB_DeviceInterface0CicVcomSetConfiguration(g_UsbDeviceComposite.interface0CicVcomHandle, *temp8);
                error = kStatus_USB_Success;
            }
            else
            {
                error = kStatus_USB_InvalidRequest;
            }
            break;
        case kUSB_DeviceEventSetInterface:
            if (g_UsbDeviceComposite.attach)
            {
                /* Set device interface request */
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                uint8_t alternateSetting = (uint8_t)(*temp16 & 0x00FFU);

                if (interface < USB_COMPOSITE_INTERFACE_COUNT)
                {
                    error = USB_UpdateInterfaceSetting(interface, alternateSetting);
                }
                else
                {
                    error = kStatus_USB_InvalidRequest;
                }
            }
            break;
        case kUSB_DeviceEventGetConfiguration:
            if (param)
            {
                /* Get current configuration request */
                *temp8 = g_UsbDeviceComposite.currentConfiguration;
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceEventGetInterface:
            if (param)
            {
                /* Get current alternate setting of the interface request */
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                if (interface < USB_COMPOSITE_INTERFACE_COUNT)
                {
                    *temp16 = (*temp16 & 0xFF00U) | g_UsbDeviceComposite.currentInterfaceAlternateSetting[interface];
                    error = kStatus_USB_Success;
                }
                else
                {
                    error = kStatus_USB_InvalidRequest;
                }
            }
            break;
        case kUSB_DeviceEventGetDeviceDescriptor:
            if (param)
            {
                /* Get device descriptor request */
                error = USB_DeviceGetDeviceDescriptor(handle, (usb_device_get_device_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetConfigurationDescriptor:
            if (param)
            {
                /* Get device configuration descriptor request */
                error = USB_DeviceGetConfigurationDescriptor(handle,
                                                             (usb_device_get_configuration_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetStringDescriptor:
            if (param)
            {
                /* Get device string descriptor request */
                error = USB_DeviceGetStringDescriptor(handle, (usb_device_get_string_descriptor_struct_t *)param);
            }
            break;
#if (USB_DEVICE_CONFIG_HID > 0U)
        case kUSB_DeviceEventGetHidDescriptor:
            if (param)
            {
                /* Get hid descriptor request */
                error = USB_DeviceGetHidDescriptor(handle, (usb_device_get_hid_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidReportDescriptor:
            if (param)
            {
                /* Get hid report descriptor request */
                error =
                    USB_DeviceGetHidReportDescriptor(handle, (usb_device_get_hid_report_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetHidPhysicalDescriptor:
            if (param)
            {
                /* Get hid physical descriptor request */
                error = USB_DeviceGetHidPhysicalDescriptor(handle,
                                                           (usb_device_get_hid_physical_descriptor_struct_t *)param);
            }
            break;
#endif /* USB_DEVICE_CONFIG_HID */
#if (defined(USB_DEVICE_CONFIG_CV_TEST) && (USB_DEVICE_CONFIG_CV_TEST > 0U))
        case kUSB_DeviceEventGetDeviceQualifierDescriptor:
            if (param)
            {
                /* Get Qualifier descriptor request */
                error = USB_DeviceGetDeviceQualifierDescriptor(
                    handle, (usb_device_get_device_qualifier_descriptor_struct_t *)param);
            }
            break;
#endif
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (((defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))) ||  \
     (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U)))
        case kUSB_DeviceEventDcdDetectionfinished:
            /*temp pointer point to detection result*/
            if (param)
            {
                error = kStatus_USB_Success;
                if (kUSB_DcdSDP == *temp8)
                {
                    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionSDP;
                }
                else if (kUSB_DcdCDP == *temp8)
                {
                    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionCDP;
                }
                else if (kUSB_DcdDCP == *temp8)
                {
                    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionDCP;
                }
                else if (kUSB_DcdTimeOut == *temp8)
                {
                    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionTimeOut;
                }
                else if (kUSB_DcdError == *temp8)
                {
                    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionError;
                }
                else
                {
                    error = kStatus_USB_InvalidRequest;
                }
            }
            break;
#endif
        default:
            break;
    }
    return error;
}

/*!
 * @brief Select interface and call setInterface callback.
 *
 * @param interface          Number of interface to be set to.
 * @param alternateSetting    Alternate setting to be used.
 * @return usb_status_t Returns status of operation.
 */
usb_status_t USB_UpdateInterfaceSetting(uint8_t interface, uint8_t alternateSetting)
{
    usb_status_t ret = kStatus_USB_Error;

    /* select appropriate interface to be updated*/
    switch (interface)
    {

    case USB_INTERFACE_0_CIC_VCOM_INDEX:
        ret = USB_DeviceInterface0CicVcomSetInterface(g_UsbDeviceComposite.interface0CicVcomHandle, alternateSetting);
        break;
    case USB_INTERFACE_1_DIC_VCOM_INDEX:
        ret = USB_DeviceInterface1DicVcomSetInterface(g_UsbDeviceComposite.interface0CicVcomHandle, alternateSetting);
        break;
    }

    if (ret == kStatus_USB_Success)
    {
        //interface setting was set
        g_UsbDeviceComposite.currentInterfaceAlternateSetting[interface] = alternateSetting;
    }

    return ret;
}

/*!
 * @brief Completely initializes USB device.
 *
 * This function calls other USB device functions and directly initializes following: USB specific clocks, g_UsbDeviceComposite values, USB stack, class drivers and device isr.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceApplicationInit(void)
{
	usb_status_t status;

    USB_DeviceClockInit();

    g_UsbDeviceComposite.speed = USB_SPEED_FULL;
    g_UsbDeviceComposite.attach = 0U;
    g_UsbDeviceComposite.interface0CicVcomHandle = (class_handle_t)NULL;
    g_UsbDeviceComposite.deviceHandle = NULL;

    /* Initialize the usb stack and class drivers. */
    status = USB_DeviceClassInit(USB_DEVICE_CONTROLLER_ID, &g_UsbDeviceCompositeConfigList, &g_UsbDeviceComposite.deviceHandle);

    if (kStatus_USB_Success != status)
    {
        return status;
    }

    /* Get the class handle. */
    g_UsbDeviceComposite.interface0CicVcomHandle = g_UsbDeviceCompositeConfigList.config[0].classHandle;
    USB_DeviceInterface0CicVcomInit(&g_UsbDeviceComposite);


#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (((defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))) ||  \
     (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U)))
    g_UsbDeviceComposite.dcdDectionStatus = kUSB_DeviceDCDDectionInit;
#endif

    USB_DeviceIsrEnable();

#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
    /*USB_DeviceRun could not be called here to avoid DP/DM confliction between DCD function and USB function in case
      DCD is enabled. Instead, USB_DeviceRun should be called after the DCD is finished immediately*/
#if (defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U))
    /* Start USB device HID mouse */
    /*Add one delay here to make the DP pull down long enough to allow host to detect the previous disconnection.*/
    SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
#endif
#else
    /*Add one delay here to make the DP pull down long enough to allow host to detect the previous disconnection.*/
    SDK_DelayAtLeastUs(5000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
#endif
    return status;
}

/*!
 * @brief USB device charger task function.
 *
 * This function handles the USB device charger events.
 * @param usbDeviceCompositeDcd Device charger configuration.
 * @return None.
 */
#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
void USB_DeviceChargerTask(usb_device_composite_struct_t *usbDeviceCompositeDcd)
{
    if (usbDeviceCompositeDcd->connectStateChanged)
    {
        usbDeviceCompositeDcd->connectStateChanged = 0;
        if (g_UsbDeviceComposite.connectState)
        {
            /*user need call USB_DeviceRun here to usb function run if dcd function is disabled*/
            /*USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);*/
            usb_echo("USB device attached.\r\n");
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))

#elif (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
            HW_TimerControl(1U);
#endif
        }
        else
        {
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U))
            /*USB_DeviceStop should be called here to avoid DP/DM confliction between DCD function and USB function in
             * case next time DCD dection. */
            USB_DeviceStop(g_UsbDeviceComposite.deviceHandle);
#endif
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))

#elif (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U))
            HW_TimerControl(0U);
#endif
            usb_echo("USB device detached.\r\n");
        }
    }
#if (defined(USB_DEVICE_CONFIG_CHARGER_DETECT) && (USB_DEVICE_CONFIG_CHARGER_DETECT > 0U)) && \
    (((defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))) ||  \
     (defined(FSL_FEATURE_SOC_USB_ANALOG_COUNT) && (FSL_FEATURE_SOC_USB_ANALOG_COUNT > 0U)))
    if ((kUSB_DeviceDCDDectionInit != usbDeviceCompositeDcd->dcdDectionStatus) &&
        (kUSB_DeviceDCDDectionFinished != usbDeviceCompositeDcd->dcdDectionStatus))
    {
        switch (usbDeviceCompositeDcd->dcdDectionStatus)
        {
            case kUSB_DeviceDCDDectionSDP:
            {
                usb_echo("SDP(standard downstream port) is detected.\r\n");
                /* Start USB device HID mouse */
                USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
            }
            break;
            case kUSB_DeviceDCDDectionDCP:
            {
                usb_echo("DCP (dedicated charging port) is detected.\r\n");
#if (defined(FSL_FEATURE_USBPHY_HAS_DCD_ANALOG) && (FSL_FEATURE_USBPHY_HAS_DCD_ANALOG > 0U))
                /*
                 * This is a work-around to fix the DCP device detach event missing issue.
                 * The device (IP3511HS controller) VBUSDEBOUNCED bit is not updated on time before softeware read this
                 * bit, so when DCP is detached from usb port, softeware can't detect DCP disconnection.
                 */
                USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
#endif
            }
            break;
            case kUSB_DeviceDCDDectionCDP:
            {
                usb_echo("CDP(charging downstream port) is detected.\r\n");
                /* Start USB device HID mouse */
                USB_DeviceRun(g_UsbDeviceComposite.deviceHandle);
            }
            break;
            case kUSB_DeviceDCDDectionTimeOut:
            {
                usb_echo("Timeout error.\r\n");
            }
            break;
            case kUSB_DeviceDCDDectionError:
            {
                usb_echo("Detect error.\r\n");
            }
            break;
            default:
                break;
        }
        usbDeviceCompositeDcd->dcdDectionStatus = kUSB_DeviceDCDDectionFinished;
    }
#endif
}
#endif

/*!
 * @brief USB device tasks function.
 *
 * This function runs the tasks for USB device.
 *
 * @return None.
 */
void USB_DeviceTasks(void)
{  
        
    USB_DeviceInterface0CicVcomTask();
#if USB_DEVICE_CONFIG_USE_TASK
    USB_DeviceTaskFn(g_UsbDeviceComposite.deviceHandle);
#endif
#if (defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U))
    USB_DeviceChargerTask(&g_UsbDeviceComposite);
#endif
}
