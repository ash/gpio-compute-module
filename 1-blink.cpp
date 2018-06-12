#include <bcm2835.h>

const int pin = 42;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

    while(1) {
        bcm2835_gpio_write(pin, 1);
        bcm2835_delay(500);
        bcm2835_gpio_write(pin, 0);
        bcm2835_delay(500);
    }

    return 0;
}
