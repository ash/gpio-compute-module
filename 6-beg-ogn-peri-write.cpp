#include <bcm2835.h>
#include <iostream>

using namespace std;

const int size = 6;
const int half = size / 2;
int pin[size] = {39, 40, 41, 42, 43, 44};

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    for (int c = 0; c != size; c++) {
        bcm2835_gpio_fsel(pin[c], BCM2835_GPIO_FSEL_OUTP);
    }

    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);        

    int p = 0;
    while(1) {
        int offset = pin[p] - 32;
        int mask = (1 << offset) + (1 << (offset + half));
                
        bcm2835_peri_write(gpioBASE + BCM2835_GPSET1 / 4, mask);
        bcm2835_delay(200);
        bcm2835_peri_write(gpioBASE + BCM2835_GPCLR1 / 4, mask);

        p = (p + 1) % half;
    }

    return 0;
}
