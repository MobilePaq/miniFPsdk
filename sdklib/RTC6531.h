#ifndef RTC6531_H
#define RTC6531_H
#include <stdint.h>
#include "syscode.h" 

#define RTC_BASE_ADDR 0x82001180

#define REG_RTC_SEC_CNT      0x00
#define REG_RTC_MIN_CNT      0x04
#define REG_RTC_HOUR_CNT     0x08
#define REG_RTC_DAY_CNT      0x0C

#define REG_RTC_SEC_UPD      0x10
#define REG_RTC_MIN_UPD      0x14
#define REG_RTC_HOUR_UPD     0x18
#define REG_RTC_DAY_UPD      0x1C

#define REG_RTC_CTL          0x20 

typedef struct {
    uint16_t day;
    uint8_t  hour;
    uint8_t  min;
    uint8_t  sec;
} time65_t;

static inline void rtc_get_time(time65_t *t) {
    if (!t) return;
    t->sec  = (uint8_t)(adi_read(RTC_BASE_ADDR + REG_RTC_SEC_CNT)  & 0x3F);
    t->min  = (uint8_t)(adi_read(RTC_BASE_ADDR + REG_RTC_MIN_CNT)  & 0x3F);
    t->hour = (uint8_t)(adi_read(RTC_BASE_ADDR + REG_RTC_HOUR_CNT) & 0x1F);
    t->day  = (uint16_t)(adi_read(RTC_BASE_ADDR + REG_RTC_DAY_CNT) & 0xFFFF);
}

static inline void rtc_set_time(uint16_t d, uint8_t h, uint8_t m, uint8_t s) {
    adi_write(RTC_BASE_ADDR + REG_RTC_SEC_UPD,  (uint32_t)(s & 0x3F));
    adi_write(RTC_BASE_ADDR + REG_RTC_MIN_UPD,  (uint32_t)(m & 0x3F));
    adi_write(RTC_BASE_ADDR + REG_RTC_HOUR_UPD, (uint32_t)(h & 0x1F));
    adi_write(RTC_BASE_ADDR + REG_RTC_DAY_UPD,  (uint32_t)(d & 0xFFFF));
}

static inline void rtc_init() {
    adi_write_or(0x82001408, 1);
}

static inline const char* rtc_format_time(char *buf) {
    time65_t t;
    rtc_get_time(&t);
    
    char *p = buf;
    uint32_t d = t.day;
    
    *p++ = 'T'; *p++ = 'I'; *p++ = 'M'; *p++ = 'E'; *p++ = ':';
    p[3] = (d % 10) + '0'; d /= 10;
    p[2] = (d % 10) + '0'; d /= 10;
    p[1] = (d % 10) + '0'; d /= 10;
    p[0] = (d % 10) + '0';
    p += 4;
    *p++ = ' ';
    *p++ = (t.hour / 10) + '0'; *p++ = (t.hour % 10) + '0'; *p++ = ':';
    *p++ = (t.min / 10)  + '0'; *p++ = (t.min % 10)  + '0'; *p++ = ':';
    *p++ = (t.sec / 10)  + '0'; *p++ = (t.sec % 10)  + '0';
    *p++ = '\n';
    *p++ = '\0';
    
    return buf;
}

#endif
