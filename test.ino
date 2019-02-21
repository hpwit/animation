



#include "FastLED.h"
#include "animation.h"
FASTLED_USING_NAMESPACE

#define NUM_LEDS 68

CRGB leds[NUM_LEDS];




class rainbowLeftRight : public Animation
 {
 
 /* 
 once in that class it's like being in a separate program
 where the led strip is 'ledsa' and the length of this strip is 'num_leds'
 you can see this strip as independant
 */
   private://do not touch
   //here define the 'global' variable that could change at every loop
    int k;
  
  public://do not touch
    using Animation::Animation; //do not touch
    
    void setup()
    { //put here the code if you need to initialized the variables this it not necessary
      
      k=0;
    }
    void animation() override //this is the function that will be executed each time
    {
      //change the code below
      for(int i=0;i<=num_leds;i++)
      {
        ledsa[i]=CHSV((i+k)*255/num_leds,255,255);
      }  
      k=(k+10)%255;
    } 
    
 };


//a second animation 
class rainbowRightLeft : public Animation
 {
   private:
    int k;
   public:
    using Animation::Animation;
    
     void setup()
    { //put here the code if you need to initialized the variables this it not necessary
      //fill_solid(ledsa,num_leds,CRGB::Blue);
      k=255;
    }
    void animation() override //this is the function that will be executed each time
    {
      //change the code below
      for(int i=0;i<=num_leds;i++)
      {
        ledsa[i]=CHSV((i+k)*255/num_leds,255,255);
      }  
      k=k-10;
      if(k<0)
       k=255;
    } 
    
 };



 rainbowRightLeft anim=rainbowRightLeft(leds,0,16); // we initialize the animation (the global led strip, the first led, the last led)
rainbowLeftRight anim2=rainbowLeftRight(leds,17,33);
 rainbowRightLeft anim3=rainbowRightLeft(leds,34,50); // we initialize the animation (the global led strip, the first led, the last led)
rainbowLeftRight anim4=rainbowLeftRight(leds,51,67);
void setup() {

  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
    anim.setup();
   anim2.setup();
     anim3.setup();
   anim4.setup();
}

void loop() {
  anim.loop(); //to execute the animation
  anim2.loop();
  anim3.loop(); //to execute the animation
  anim4.loop();
 FastLED.show();
}
