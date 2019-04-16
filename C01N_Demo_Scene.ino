#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>

const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 25;
const int vsyncPin = 26;

VGA3BitI vga;

struct particle {
  float x, y, vx, vy;
  int r,g,b;
};

#define NUMPARTICLES 2000
particle particles[NUMPARTICLES];
String advert = "    C01N does VGA!  |  DANK ASF  |  r we 31337 yet?  |  Topkek  |  REEEEEEEEEEEEEEEEEEEEE    ";
float offset = 0;



void setup() {
  vga.setFrameBufferCount(2);
	vga.init(vga.MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
	vga.setFont(Font6x8);

  for(int p=0;p<NUMPARTICLES;p++) particles[p] = {160,120,0,0,0,0,0};
}

void c01nlogo(){
  vga.fillCircle(160, 120, 50, vga.RGB(255,255,255)); // Base
  vga.fillRect(200, 111, 11, 20, vga.RGB(0,0,0)); // USB
  vga.rect(140, 80, 40, 40, vga.RGB(0,0,0)); // OLED Frame
  vga.fillRect(140, 87, 40, 25, vga.RGB(0,0,0)); // OLED Screen
  vga.fillRect(175, 130, 10, 10, vga.RGB(0,0,0)); // BTNU
  vga.fillRect(175, 150, 10, 10, vga.RGB(0,0,0)); // BTND
  vga.fillRect(165, 140, 10, 10, vga.RGB(0,0,0)); // BTNL
  vga.fillRect(185, 140, 10, 10, vga.RGB(0,0,0)); // BTNR
  vga.fillRect(125, 140, 10, 10, vga.RGB(0,0,0)); // BTNA
  vga.fillRect(135, 150, 10, 10, vga.RGB(0,0,0)); // BTNB
  vga.fillRect(130, 90, 7, 7, vga.RGB(0,0,0)); // NP0
}

void loop() {
  vga.clear(0);

  for(auto &p: particles){
    if(p.x < 0 || p.y < 0 || p.x > 320 || p.y > 240 || (p.vx == 0 && p.vy == 0)){
      p.x = 160;
      p.y = 120;
      p.vx = random(-100,100)/100.0;
      p.vy = random(-100,100)/100.0;
      p.r = random(255);
      p.g = random(255);
      p.b = random(255);
    }
    p.x += p.vx;
    p.y += p.vy;
    vga.fillRect(p.x, p.y, 2, 2, vga.RGB(p.r, p.g, p.b));
  }

  c01nlogo();

  for(int i=0;i<advert.length();i++){
    vga.setCursor(((int)(i*8+offset*20))%960, 35+int(30.0*sin((millis()+100*i)/500.0)));
    vga.print(advert[(i)%advert.length()]);
  }
  offset+=0.05;
  
  vga.show();
}
