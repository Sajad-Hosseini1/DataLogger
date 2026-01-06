#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "RTC.h"
#include "spi.h"
#include "i2c.h"
#include "fatfs.h"
#include "sd_driver.h"
#include "ssd1306.h"
#include "fonts.h"


uint8_t cmd[2] = {0x24, 0x00};
uint8_t data[6];
char strCopy[15];
FATFS fs;
FRESULT fresult;
FIL fil;
UINT byteswritten;
char buffer[200];
float temperature;
float humidity;


void SHT3X_ReadTempHum(void);


int main(void)
{
    HAL_Init();
    rcc_systemClockConfig();
    //UART1-Printf
    uart_UART1_GPIO_config();
    uart_UART1_config();
    //GPIO
    gpio_LED_config();
    gpio_PB_config();
    gpio_SW_config();

    //SD Card
    spi_GPIO_config();
    spi_config();
    MX_FATFS_Init();

    //RTC
    rtc_config();
    ClockTime_t timeDef;
    timeDef.hrs24 = 15;
    timeDef.minutes = 46;
    timeDef.seconds = 31;
    rtc_setTime(&timeDef);

    ClockDate_t dateDef;
    dateDef.day = 05;
    dateDef.month = 01;
    dateDef.year = 2026;
    rtc_setDate(&dateDef);

    //Mount SD Card
   fresult = f_mount(&fs, "", 1);
   if(fresult != FR_OK)
         {
         	printf("Failed to Mount SD card\n");
         }
         else{
         	printf("Successfully Mounted \n");
         }


   //Write text file to SD Card
     fresult = f_open(&fil,"Data.CSV", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
       if(fresult != FR_OK)
       {
       	printf("Failed to Open file\n");
       }
       else{
       	printf("Successfully opened file\n");
       }

    //I2C Configuration
    i2c_GPIO_config();
    i2c_config();
    SSD1306_Init();

    if(HAL_I2C_IsDeviceReady(&hi2c1, (0x44 << 1), 1, 100) == HAL_OK)
    {
    	printf("Detected successfully\n");
    	gpio_LED_writeGreen(1);
    }
    else
    {
    	 printf("Not Detected\n");
    	 gpio_LED_writeRed(1);
    }


	while(1)
	{
		SHT3X_ReadTempHum();
		rtc_get_TimeDate(&timeDef, &dateDef);

		sprintf(buffer, "%04u-%02u-%02u,%02u:%02u:%02u,Temp: %.1f C, Hum: %.1f %% \r\n",
				dateDef.year,dateDef.month, dateDef.day,
				timeDef.hrs24, timeDef.minutes, timeDef.seconds,
				temperature, humidity);

		f_write(&fil, buffer, strlen(buffer), &byteswritten);
		f_sync(&fil);
		HAL_Delay(1000);



	}
}


void SHT3X_ReadTempHum(void)
{
    // 1) Send measurement command
    HAL_I2C_Master_Transmit(&hi2c1, (0x44 << 1), cmd, 2, 100);

    // 2) Wait the measurement time
    HAL_Delay(20);

    // 3) Read 6 bytes
    HAL_I2C_Master_Receive(&hi2c1, (0x44 << 1), data, 6, 100);

    // 4) Combine temperature bytes
    uint16_t rawTemp = (data[0] << 8) | data[1];

    // 5) Combine humidity bytes
    uint16_t rawHum  = (data[3] << 8) | data[4];

    // 6) Convert to °C and %RH
    temperature = -45 + (175 * (float)rawTemp) / 65535.0;
    humidity = 100 * (float)rawHum/65535.0;

    SSD1306_GotoXY (0, 0);
    sprintf(strCopy, "Temp:%.1f C", temperature);
    SSD1306_Puts(strCopy, &Font_11x18, 1);

    SSD1306_GotoXY(0, 25);
    sprintf(strCopy, "Hum:%.1f %% ",humidity);
    SSD1306_Puts(strCopy, &Font_11x18, 1);



    SSD1306_UpdateScreen();
}
