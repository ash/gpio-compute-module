#include <bcm2835.h>
#include <iostream>
#include <bitset>

using namespace std;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    for (int c = 28; c <= 45; c++) {
        bcm2835_gpio_fsel(c, BCM2835_GPIO_FSEL_INPT);
        bcm2835_gpio_set_pud(c, BCM2835_GPIO_PUD_UP);
    }

    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);

    while(1) {
        uint32_t reg1 = bcm2835_peri_read(gpioBASE + BCM2835_GPLEV0 / 4);
        uint32_t reg2 = bcm2835_peri_read(gpioBASE + BCM2835_GPLEV1 / 4);

        cout << bitset<32>(reg1) << ' ' << bitset<32>(reg2) << endl;

        bcm2835_delay(100);
    }

    return 0;
}
