#include <bcm2835.h>
#include <iostream>

using namespace std;

const int size = 6;
int pin[size] = {39, 40, 41, 42, 43, 44};

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    for (int c = 0; c != size; c++) {
        bcm2835_gpio_fsel(pin[c], BCM2835_GPIO_FSEL_OUTP);
    }

    int p = 0;
    while(1) {
        bcm2835_gpio_clr(pin[p]);
        p = (p + 1) % size;
        bcm2835_gpio_set(pin[p]);

        bcm2835_delay(100);
    }

    return 0;
}
