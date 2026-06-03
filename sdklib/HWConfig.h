#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#define DISABLE_USB_WAIT  1       // 1 - не ждать USB (мгновенный старт), 0 - ждать fdl_ack
#define USE_HARDCODED_CFG 1
// --- Основные параметры дисплея ---
#define CFG_LCD_ID        0x333025  // Твой ID из лога
#define CFG_BRIGHTNESS    25        // Яркость (0-100)
#define CFG_SCALER        0         // 0 - выкл, >0 - масштаб
#define CFG_ROTATE        0x00      // Ориентация экрана и кнопок
#define CFG_LCD_CS        0         // Chip Select дисплея (0-3)
#define CFG_PAGE_RESET    0xff      // Reset режим (0, 1 или 0xff)

// --- Интерфейсы и GPIO ---
#define CFG_SPI           0         // Настройки SPI (0 - дефолт)
#define CFG_SPI_MODE      3         // SPI Mode (1-4)
#define CFG_BL_GPIO       45        // Пин подсветки (0xff - авто)
#define CFG_GPIO_INIT     1         // 1 - принудительно инициализировать GPIO
#define CFG_CHARGE        -1        // Параметры зарядки

// --- Клавиатура (Кнопки) ---
#define CFG_KEYROWS       5         // Количество строк матрицы
#define CFG_KEYCOLS       8         // Количество столбцов
#define CFG_KEYFLAGS      0         // Флаги инверсии кнопок (0 - дефолт)

// --- Сеть/Прочее ---
#define CFG_MAC           0         // MAC адрес (если есть)

#endif
