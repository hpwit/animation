



#include "FastLED.h"
#inlcude "animation.h"
FASTLED_USING_NAMESPACE

#define NUM_LEDS 68

CRGB leds[NUM_LEDS];




class myAnimation2 : public Animation
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
      fill_solid(ledsa,num_leds,CRGB::Blue);
      k=300;
    }
    void animation() override //this is the function that will be executed each time
    {
      //change the code below
      for(int i=0;i<=num_leds;i++)
      {
        ledsa[i]=CHSV((i+k)*255/num_leds,255,255);
      }  
      k=(k+10)%num_leds;
    } 
    
 };


//a second animation 
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
      for(int i=0;i<=k;i++)
      {
        ledsa[i]=CRGB::Red;
      }  
      
      k=(k+1)%num_leds;
    } 
    
 };



 myAnimation anim=myAnimation(leds,0,20); // we initialize the animation (the global led strip, the first led, the last led)
myAnimation2 anim2=myAnimation2(leds,21,67);

void setup() {

  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
    anim.setup();
   anim2.setup();
}

void loop() {
  anim.loop(); //to execute the animation
  anim2.loop();

}
