// This example show the erratic behavious of the FT6336U touch library
// for the WT32-SCO1 display
// Especially the TD status changes without any external touch influence.
//Furthermore the Wight signal remains at zero.
// Created by PA0ESH on 13/2/2022 as an example to the FT6336U library:


#include <TFT_eSPI.h>
#include "FT6336U.h"

#define I2C_SDA 18
#define I2C_SCL 19
#define RST_N_PIN 21
#define INT_N_PIN 34

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite Slider    = TFT_eSprite(&tft);
TFT_eSprite AZ_Needle = TFT_eSprite(&tft); // Sprite object for AZ_Needle
TFT_eSprite AZ_spr    = TFT_eSprite(&tft); // Sprite for meter reading
TFT_eSprite EL_Needle = TFT_eSprite(&tft); // Sprite object for AZ_Needle
TFT_eSprite EL_spr    = TFT_eSprite(&tft); // Sprite for meter reading


FT6336U ft6336u(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
int Counter_1 = 0;
int Counter_2 = 0;
int Counter_3 = 0;
int x_pos = 240;
int y_pos = 20;
String SKETCH = "FT636 Touch Test programme";
int length = SKETCH.length();

int changes[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  // start the touchscreen
  ft6336u.begin();

  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_PINK);
  tft.setTextPadding(3);
  tft.drawString("RANDOM TOUCH TEST", x_pos , y_pos, 4);
  tft.drawString("using TFT_eSPI", x_pos , y_pos + 20, 2);
  tft.drawString("and FT6336U   ", x_pos , y_pos + 40, 2);
  tft.drawString("on WT32-SCO1  ", x_pos , y_pos + 60, 2);
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("Pin                 Status     Changes     Last value", x_pos + 29  , y_pos + 95, 2);
  tft.setTextColor(TFT_WHITE);
  Serial.print("FT6336U Firmware Version: ");
  Serial.println(ft6336u.read_firmware_id());
  Serial.print("FT6336U Device Mode: ");
  Serial.println(ft6336u.read_device_mode());

  pinMode(INT_N_PIN, OUTPUT);
  digitalWrite(INT_N_PIN, HIGH);

  digitalWrite(INT_N_PIN, LOW);
  

}

void loop() {
  tft.setTextDatum(MR_DATUM);
  x_pos = 160;
  y_pos = 50;
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  int padding = tft.textWidth("9999", 2); // get the width of the text in pixels
  tft.setTextPadding(padding);

  tft.drawString("INT_N_PIN ", x_pos , y_pos + 90, 2);
  tft.drawNumber(digitalRead(INT_N_PIN),  x_pos + 90 , y_pos + 90, 2 );

  if (digitalRead(INT_N_PIN) != -1) {


    changes[0] = ft6336u.read_td_status();
    tft.drawString("TD Status  ", x_pos , y_pos + 120, 2);
    tft.drawNumber(changes[0], x_pos + 90 , y_pos + 120, 2 );

    if (changes[1] != changes[0]) {
      Counter_3++;
      tft.drawNumber(Counter_3,  x_pos+170  , y_pos + 120, 2 );
      if (ft6336u.read_td_status() != 0) {
        tft.drawNumber(changes[1],  x_pos + 250 , y_pos + 120, 2 );
      }
      //tft.drawNumber(changes[1],  x_pos + 250 , y_pos + 120, 2 );
    }
    changes[1] = changes[0];



    

    tft.drawString("TOUCH EVENT 1  ", x_pos , y_pos + 150, 2);
    tft.drawNumber(ft6336u.read_touch1_event(),  x_pos + 90 , y_pos + 150, 2 );

    changes[2] = ft6336u.read_touch1_event();
    delay(10);
    changes[3] = ft6336u.read_touch1_event();
    if (changes[2] != changes[3]) {
      Counter_3++;
      tft.drawNumber(Counter_3,  x_pos + 170 , y_pos + 150, 2 );
    }


    tft.drawString("TP-X  ", x_pos , y_pos + 180, 2);
    tft.drawNumber(ft6336u.read_touch1_x(),  x_pos + 90 , y_pos + 180, 2 );


    tft.drawString("TP-Y  ", x_pos ,  y_pos + 210, 2);
    tft.drawNumber(ft6336u.read_touch1_y(),  x_pos + 90 , y_pos + 210, 2 );



    changes[4] = ft6336u.read_touch1_weight();
    tft.drawString("TOUCH WEIGHT 1 ", x_pos ,  y_pos + 240, 2);
    tft.drawNumber(changes[4],  x_pos + 90 , y_pos + 240, 2 );
    if (changes[5] != changes[4]) {
      Counter_3++;
      tft.drawNumber(Counter_3,  x_pos + 170 , y_pos + 240, 2 );
      if (ft6336u.read_touch1_weight() != 0) {
        tft.drawNumber(changes[5],  x_pos + 250 , y_pos + 240, 2 );
      }
      //tft.drawNumber(changes[5],  x_pos + 250 , y_pos + 240, 2 );
    }
    changes[5] = changes[4];




    /*

        Serial.print("FT6336U TD Status  : ");
        Serial.println(ft6336u.read_td_status());
        Serial.print("FT6336U Touch Event/ID 1: (");
        Serial.print(ft6336u.read_touch1_event()); Serial.print(" / "); Serial.print(ft6336u.read_touch1_id()); Serial.println(")");
        Serial.print("FT6336U Touch Position 1: (");
        Serial.print(ft6336u.read_touch1_x()); Serial.print(" , "); Serial.print(ft6336u.read_touch1_y()); Serial.println(")");
        Serial.print("FT6336U Touch Weight/MISC 1: (");
        Serial.print(ft6336u.read_touch1_weight()); Serial.print(" / "); Serial.print(ft6336u.read_touch1_misc()); Serial.println(")");
        Serial.print("FT6336U Touch Event/ID 2: (");
        Serial.print(ft6336u.read_touch2_event()); Serial.print(" / "); Serial.print(ft6336u.read_touch2_id()); Serial.println(")");
        Serial.print("FT6336U Touch Position 2: (");
        Serial.print(ft6336u.read_touch2_x()); Serial.print(" , "); Serial.print(ft6336u.read_touch2_y()); Serial.println(")");
    */
    Serial.print("FT6336U Touch Weight/MISC 2: (");
    Serial.print(ft6336u.read_touch2_weight()); Serial.print(" / "); Serial.print(ft6336u.read_touch2_misc()); Serial.println(")");

  }

}
