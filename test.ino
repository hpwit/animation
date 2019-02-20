



#include "FastLED.h"
FASTLED_USING_NAMESPACE

#define NUM_LEDS 68

CRGB leds[NUM_LEDS];




class myAnimation2 : public Animation
 {
   private:
    int k;
   public:
    using Animation::Animation;
    //myAnimation ( CRGB *ext_leds,int start_led,int end_led):Animation(  ext_leds ,start_led,end_led,&this->animation);
    void setup()
    {
      k=300;
    }
    void animation() override
    {
      //Serial.println("ee");
      for(int i=0;i<=num_leds;i++)
      {
        ledsa[i]=CHSV((i+k)*255/num_leds,255,255);
      }  
      k=(k+10)%num_leds;
    } 
    
 };
 
class myAnimation : public Animation
 {
   private:
    int k;
   public:
    using Animation::Animation;
    
    void setup()
    {
      k=0;
    }
    void animation() override
    {
      fill_solid(ledsa,num_leds,CRGB::Green);
      //Serial.println("ee");
      for(int i=0;i<=k;i++)
      {
        ledsa[i]=CRGB::Red;
      }  
      
      k=(k+1)%num_leds;
    } 
    
 };



 myAnimation anim=myAnimation(leds,0,20);
myAnimation2 anim2=myAnimation2(leds,21,49);

void setup() {

  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
    anim.setup():
   anim.setup():
}

void loop() {
  anim.lopp();
  anim.loop();

}
