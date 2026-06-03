#include "minifplib.h"
#include "font6x9.h"
#include <time.h>
#include "RTC6531.h"
#include <wchar.h>
time65_t t;
int presskey=0;
uint8_t timemode=0; //0 - show, 1 - edit min, 2 - edit h, 3 - edit d
int main(int argc, char **argv){
	hagl_backend_t *surface = fp_init_all();
    fp_clear_fast();
    hagl_fill_rectangle_xywh(surface, 0,0,128,160,RGB(0,0,255));
	fp_update();
	sys_brightness(25);
	
	while(1){
		fp_clear_fast();
		presskey=get_pressed_key();
		if(presskey==0x0d){
			timemode++;
			if(timemode==4) {timemode =0; rtc_set_time(t.day,t.hour,t.min,t.sec);}
		}
		if(timemode==0){
			rtc_get_time(&t);
			draw_textf(surface, 5,5, RGB(255,255,255), font6x9,"%04d %02d:%02d:%02d",t.day, t.hour, t.min, t.sec);
		}
		if(timemode==1){
			switch (presskey){
				case 0x04:
				t.min++;
				break;
				case 0x05:
				t.min--;
				break;
			}
			draw_textf(surface, 5,5, RGB(255,255,255), font6x9,"%04d %02d:%02d<-:%02d",t.day, t.hour, t.min, t.sec);
		
		}
		if(timemode==2){
			switch (presskey){
				case 0x04:
				t.hour++;
				break;
				case 0x05:
				t.hour--;
				break;
			}
			draw_textf(surface, 5,5, RGB(255,255,255), font6x9,"%04d %02d<-:%02d:%02d",t.day, t.hour, t.min, t.sec);
		
		}
		if(timemode==3){
			switch (presskey){
				case 0x04:
				t.day++;
				break;
				case 0x05:
				t.day--;
				break;
			}
			draw_textf(surface, 5,5, RGB(255,255,255), font6x9,"%04d<- %02d:%02d:%02d",t.day, t.hour, t.min, t.sec);
		
		}
		fp_update();
		sys_wait_ms(50);
	}

    return 0;
 }

bool check_collision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2) {
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}
//0x0d CENTER, 0x07 >, 0x06 <, 0x05  down, 0x04 up
