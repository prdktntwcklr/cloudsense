#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void) {
    printk("Hello from CloudSense!\n");

    while (1) {
        printk("Heartbeat: %lld ms\n", k_uptime_get());
        k_msleep(1000);
    }

    return 0;
}
