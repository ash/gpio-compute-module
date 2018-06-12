#include <bcm2835.h>
#include <iostream>

using namespace std;

const int pin = 32;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);

    while(1) {
        int lev = bcm2835_gpio_lev(pin);
        cout << lev << endl;
        bcm2835_delay(100);
    }

    return 0;
}
