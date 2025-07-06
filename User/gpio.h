
void GPIO_Config(void);

// PC3: Relay
#define RELAY_GPIO_PORT         GPIOC
#define RELAY_GPIO_CLK          RCC_AHBPeriph_GPIOC
#define RELAY_GPIO_PIN          GPIO_Pin_3

// PC4: LED Backlight
#define BACKLIGHT_GPIO_PORT     GPIOC
#define BACKLIGHT_GPIO_CLK      RCC_AHBPeriph_GPIOC
#define BACKLIGHT_GPIO_PIN      GPIO_Pin_4

// PC5: LCD_DATA
#define LCD_DATA_GPIO_PORT      GPIOC
#define LCD_DATA_GPIO_CLK       RCC_AHBPeriph_GPIOC
#define LCD_DATA_GPIO_PIN       GPIO_Pin_5

// PC6: LCD_WR
#define LCD_WR_GPIO_PORT        GPIOC
#define LCD_WR_GPIO_CLK         RCC_AHBPeriph_GPIOC
#define LCD_WR_GPIO_PIN         GPIO_Pin_6

// PC7: LCD_CS
#define LCD_CS_GPIO_PORT        GPIOC
#define LCD_CS_GPIO_CLK         RCC_AHBPeriph_GPIOC
#define LCD_CS_GPIO_PIN         GPIO_Pin_7

// PB4: BTN_DOWN
#define BTN_DOWN_GPIO_PORT      GPIOB
#define BTN_DOWN_GPIO_CLK       RCC_AHBPeriph_GPIOB
#define BTN_DOWN_GPIO_PIN       GPIO_Pin_4

// PA2: BTN_SET
#define BTN_SET_GPIO_PORT       GPIOA
#define BTN_SET_GPIO_CLK        RCC_AHBPeriph_GPIOA
#define BTN_SET_GPIO_PIN        GPIO_Pin_2

// PA3: BTN_SET
#define BTN_UP_GPIO_PORT        GPIOA
#define BTN_UP_GPIO_CLK         RCC_AHBPeriph_GPIOA
#define BTN_UP_GPIO_PIN         GPIO_Pin_3
