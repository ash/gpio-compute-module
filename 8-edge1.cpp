// Falling edge detection

#include <bcm2835.h>
#include <iostream>
#include <bitset>

using namespace std;

int pin = 32;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);

    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);

    // This is needed to prevent theinfluence of other experiments
    bcm2835_peri_write(gpioBASE + BCM2835_GPHEN1 / 4, 0);
    bcm2835_peri_write(gpioBASE + BCM2835_GPLEN1 / 4, 0);
    bcm2835_peri_write(gpioBASE + BCM2835_GPREN1 / 4, 0);
    bcm2835_peri_write(gpioBASE + BCM2835_GPFEN1 / 4, 0);
    bcm2835_peri_write(gpioBASE + BCM2835_GPAREN1 / 4, 0);
    bcm2835_peri_write(gpioBASE + BCM2835_GPAFEN1 / 4, 0);

    bcm2835_peri_write(gpioBASE + BCM2835_GPFEN1 / 4, 1 << (pin - 32));

    int c = 0;
    while(1) {
        int x = bcm2835_peri_read(gpioBASE + BCM2835_GPEDS1 / 4);
        cout << bitset<32>(x) << endl;
        bcm2835_delay(200);
        
        if (x) c++;
        if (c == 4) {
            bcm2835_peri_write(gpioBASE + BCM2835_GPEDS1 / 4, 1 << (pin - 32));
            c = 0;
        }
        bcm2835_delay(200);
    }

    return 0;
}
