#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "epd2in13.h"
#include "epdpaint.h"
#include "imagedata.h"

static const char *TAG = "E-paper";

extern "C" void app_main()
{
  static unsigned char image[8192];
  Paint paint(image, 0, 0);
  Epd epd;

  if (epd.Init(lut_full_update) != 0)
  {
    ESP_LOGI(TAG, "EPD Init OK!");
  }
  else
  {
    ESP_LOGI(TAG, "EPD Init Error");
    while (1)
    {
      ESP_LOGI(TAG, ".");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }

  paint.SetWidth(EPD_PHYSICAL_WIDTH);
  paint.SetHeight(EPD_PHYSICAL_HEIGHT);
  paint.SetRotate(ROTATE_0);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "0", &Font16, COLORED);
  paint.DrawStringAt(0, 16, "16", &Font16, COLORED);
  paint.DrawStringAt(0, 32, "32", &Font16, COLORED);
  paint.DrawStringAt(0, 48, "48", &Font16, COLORED);
  paint.DrawStringAt(0, 64, "64", &Font16, COLORED);
  paint.DrawStringAt(0, 80, "80", &Font16, COLORED);
  paint.DrawStringAt(0, 96, "96", &Font16, COLORED);
  paint.DrawStringAt(0, 112, "112", &Font16, COLORED);
  paint.DrawStringAt(0, 128, "128", &Font16, COLORED);
  paint.DrawString_CN(0, 150, "微雪电子", &Font32x32CN_Black, COLORED, UNCOLORED);
  paint.DrawString_CN(0, 182, "温湿度", &Font32x32CN_Black, UNCOLORED, COLORED);

  paint.DrawStringAt(0, 234, "234", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  // epd.Sleep();
  vTaskDelay(5000 / portTICK_PERIOD_MS);


  if (epd.Init(lut_partial_update) != 0)
  {
    ESP_LOGI(TAG, "EPD Init OK!");
  }
  else
  {
    ESP_LOGI(TAG, "EPD Init Error");
    while (1)
    {
      ESP_LOGI(TAG, ".");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }

  static unsigned char pic[512];
  Paint pict(pic, 0, 0);
  pict.SetWidth(40);
  pict.SetHeight(16);
  pict.SetRotate(ROTATE_0);

  pict.Clear(UNCOLORED);
  pict.DrawStringAt(0, 0, "Akako", &Font16, COLORED);

  epd.SetFrameMemory(pict.GetImage(), 20, 20, pict.GetWidth(), pict.GetHeight());
  epd.DisplayFrame();
  epd.Sleep();

  while (true)
  {
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}