#include <bcm2835.h>
#include <iostream>

using namespace std;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(42, BCM2835_GPIO_FSEL_OUTP); // GPIO 42

    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);

    int p = 0;
    while(1) {
        bcm2835_peri_write(gpioBASE + BCM2835_GPSET1 / 4, 1 << 10);
        bcm2835_delay(500);
        bcm2835_peri_write(gpioBASE + BCM2835_GPCLR1 / 4, 1 << 10);
        bcm2835_delay(500);
    }

    return 0;
}
