#include "minifplib.h"
#include "font6x9.h"
#include <time.h>
#include "UART6531.h"
#include <wchar.h>

int main(int argc, char **argv){
	hagl_backend_t *surface = fp_init_all();
    fp_clear_fast();
    hagl_fill_rectangle_xywh(surface, 0,0,128,160,RGB(0,0,255));
	fp_update();
	sys_brightness(25);
	uart_init();
	while(1){
		uart_putc('A');
		uart_putc('B');
		uart_putc('C');
		sys_wait_ms(500);
	}

    return 0;
 }

//0x0d CENTER, 0x07 >, 0x06 <, 0x05  down, 0x04 up
