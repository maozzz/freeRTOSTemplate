#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <Pin.h>

void initClk();
void initLed();

Pin *led;
Pin *led2;
void task(void *arg);
void task2(void *arg);

int main() {
    initClk();
    initLed();

    xTaskCreate(task, "1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(task2, "2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Запускаем диспетчер и понеслась.
    vTaskStartScheduler();

    while (true) {
        asm("nop");
    }
}

void task(void *arg) {
    while (true) {
        led->toggle();
        vTaskDelay(1000);
    }
}

void task2(void *arg) {
    while (true) {
        led2->toggle();
        vTaskDelay(2000);
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
    led2 = new Pin(MDR_PORTC, PORT_Pin_1);
    led2->init()->oe(PORT_OE_OUT)->speed(PORT_SPEED_MAXFAST)->mode(PORT_MODE_DIGITAL);
}

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C" block end
#endif