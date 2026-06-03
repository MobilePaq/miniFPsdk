#define UART0_BASE 0x85000000
#define REG_UART(off) (*(volatile uint32_t*)(UART0_BASE + (off)))

void uart_init() { //115200 only for now
    // MODE_SEL [15] = 0 (UART mode)
    REG_UART(0x0018) &= ~(1 << 15);

    // 26MHz -> 0xE1 gives 115200
    REG_UART(0x0024) = 0xE1;

    // STOP_BIT_NUM [5:4] = 1 (1 stop bit)
    // BYTE_LEN [3:2] = 3 (8 bits)
    // PARITY_EN [1] = 0 (Disabled)
    uint32_t ctrl0 = REG_UART(0x0018);
    ctrl0 &= ~0x3E;
    ctrl0 |= (1 << 4) | (3 << 2); 
    REG_UART(0x0018) = ctrl0;

    REG_UART(0x0014) = 0xFFFF;
}
#define UART_STS1    (*(volatile uint32_t*)(UART0_BASE + 0x000C))
#define UART_TXD     (*(volatile uint32_t*)(UART0_BASE + 0x0000))

void uart_putc(char c) {
    // Ждем, пока в TX FIFO станет меньше 127 байт (освободится место)
    // Маскируем биты 14:8 и сдвигаем
    while (((UART_STS1 >> 8) & 0x7F) >= 127);
    
    // Закидываем байт
    UART_TXD = (uint32_t)c;
}
void uart_write_fast(const char* s) {
    while (*s) {
        // Пока в FIFO есть место (меньше 127 байт) и строка не кончилась
        while (((UART_STS1 >> 8) & 0x7F) < 127 && *s) {
            UART_TXD = (uint32_t)(*s++);
        }
        // Если строка еще есть, а FIFO забит — тут уже ждем
    }
}
