#include <Pin.h>
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"

void initClk();
void initLed();
void delay(uint32_t delay);

Pin *led;

int main() {
    initClk();
    initLed();

    while (true) {
        led->toggle();
        delay(1000000);
    }
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

void initLed() {
    led = new Pin(MDR_PORTC, PORT_Pin_0);
    led->init()->oe(PORT_OE_OUT)->speed(PORT_SPEED_MAXFAST)->mode(PORT_MODE_DIGITAL);
}

void delay(uint32_t delay) {
    for (int i = 0; i < delay; ++i);
}

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C" block end
#endif