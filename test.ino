
#include <WiFi.h>
//#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <Artnet.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#define INTERRUPT_THRESHOLD 1
#include "FastLED.h"
FASTLED_USING_NAMESPACE
#define FASTLED_SHOW_CORE 0


#define LED_WIDTH 123
#define LED_HEIGHT 48
#define NUM_LEDS LED_WIDTH*LED_HEIGHT
#define UNIVERSE_SIZE 170
CRGB leds[NUM_LEDS];


Artnet artnet;



static TaskHandle_t FastLEDshowTaskHandle2 = 0;
static TaskHandle_t userTaskHandle = 0;





void FastLEDshowESP322()
{
    if (userTaskHandle == 0) {
        const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
        // -- Store the handle of the current task, so that the show task can
        //    notify it when it's done
       // noInterrupts();
        userTaskHandle = xTaskGetCurrentTaskHandle();
        
        // -- Trigger the show task
        xTaskNotifyGive(FastLEDshowTaskHandle2);
        //to thge contrary to the other one we do not wait for the display task to come back
    }
}



void FastLEDshowTask2(void *pvParameters)
{
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 500 );
    // -- Run forever...
    for(;;) {
        // -- Wait for the trigger
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        
            
           
               // memcpy(leds,Tpic,LED_WIDTH*LED_HEIGHT*sizeof(CRGB));
            
           memcpy(leds,artnet.getframe(),NUM_LEDS*sizeof(CRGB));
            FastLED.show();
            
               userTaskHandle=0; //so we can't have two display tasks at the same time
                 
           }
}


void setup() {

   xTaskCreatePinnedToCore(FastLEDshowTask2, "FastLEDshowTask2", 1000, NULL,3, &FastLEDshowTaskHandle2, FASTLED_SHOW_CORE);
   WiFi.mode(WIFI_STA);
    
    Serial.printf("Connecting ");
    WiFi.begin("", "");

    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(WiFi.status());
   
      
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
artnet.begin(NUM_LEDS,UNIVERSE_SIZE,1); //the number of pixels and the maximum size of your iniverses 1 represent the buffer
}

void loop() {
  artnet.read();
  /* in artnet.getframe() you have the content of the frame
  for instance you can do*/
  
  
 FastLEDshowESP322();
  artnet.resetsync();
  // put your main code here, to run repeatedly:

}
