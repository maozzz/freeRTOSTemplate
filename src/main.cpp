#include <MDR32F9Qx_StdPeriph_Driver/inc/MDR32F9Qx_uart.h>
#include "main.h"

void initClk();
void initLed();
void initGlcd();

// UART
void PortsInit();
void UARTInit();


Pin *led;
LcdKs0108 *glcd;
void uartTask(void *arg);
void glcdTask(void *arg);

int main() {
    initClk();

//    xTaskCreate(task, "1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(Uart::task, "uart", 32, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(glcdTask, "3", 300, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Запускаем диспетчер и понеслась.
    vTaskStartScheduler();

    while (true) {
        asm("nop");
    }
}

void glcdTask(void *arg) {
    initGlcd();
    glcd->test2();
}


void initGlcd() {
    glcd = new LcdKs0108();
    glcd->init(
            new Pin(MDR_PORTA, PORT_Pin_0, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTA, PORT_Pin_1, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTA, PORT_Pin_2, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTA, PORT_Pin_3, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTA, PORT_Pin_4, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTA, PORT_Pin_5, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTF, PORT_Pin_2, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTF, PORT_Pin_3, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTB, PORT_Pin_7, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTB, PORT_Pin_8, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTB, PORT_Pin_9, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTB, PORT_Pin_10, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTC, PORT_Pin_0, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN),
            new Pin(MDR_PORTC, PORT_Pin_1, PORT_OE_OUT, PORT_SPEED_MAXFAST, PORT_MODE_DIGITAL, PORT_FUNC_PORT,
                    PIN_PULL_DOWN)
    );
}

void initClk(void) {
    // HSE ON
    RST_CLK_DeInit();
    SystemInit();

    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while (RST_CLK_HSEstatus() != SUCCESS);

    // FLASH MEMORY
    MDR_EEPROM->CMD |= 0b111000;

    // PLL ON
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);
    RST_CLK_CPU_PLLcmd(ENABLE);
    while (RST_CLK_CPU_PLLstatus() != SUCCESS);

    RST_CLK_CPU_PLLuse(ENABLE);
    RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

    SystemCoreClockUpdate();
}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C" block end
#endif