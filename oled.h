#define I2C_BUS_AVAILABLE       (          1 )              // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME       ( "ETX_OLED" )              // Device and Driver Name
#define SSD1306_SLAVE_ADDR      (       0x3C )              // SSD1306 OLED Slave Address
#define SSD1306_MAX_SEG         (        128 )              // Maximum segment
#define SSD1306_MAX_LINE        (          7 )              // Maximum line
#define SSD1306_DEF_FONT_SIZE   (          5 )              // Default font size

extern int  I2C_Write( unsigned char *buf, unsigned int len );


void SSD1306_PrintChar( unsigned char c );
void SSD1306_String( unsigned char *str );
void SSD1306_InvertDisplay(bool need_to_invert);
void SSD1306_SetBrightness(uint8_t brightnessValue);

int  SSD1306_DisplayInit( void );
void SSD1306_Fill( unsigned char data );
void SSD1306_GoToNextLine( void );
void SSD1306_SetCursor( uint8_t lineNo, uint8_t cursorPos );
void oled_cmd(unsigned char data);
void oled_data(unsigned char data);
void oled_print_logo(unsigned char* logo_data);
