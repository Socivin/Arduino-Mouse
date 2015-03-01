#include <SoftwareSerial.h>

#include <ps2.h>



PS2 mouse(9, 10);

SoftwareSerial bt = SoftwareSerial(2, 3);
/*
 * initialize the mouse. Reset it, and place it into remote
 * mode, so we can get the encoder data on demand. Uses Magic to setup microsoft intelimouse 0x03
 */
 
void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
  
  //Magic Sequence
  mouse.write(0xF3); //Set Sample Rate
  mouse.read(); //ack
  mouse.write(0xC8); // send 200
  mouse.read();
  mouse.write(0x64); // send 100
  mouse.read();
  mouse.write(0x50); //send 80
  mouse.read(); 
  
  
  mouse.write(0xF2);  //Asks for mouse type
  unsigned char mstat = mouse.read(); //ack
  unsigned char mtype = mouse.read();  //type
  //Serial.print(mstat, HEX);
  Serial.print("Mouse type: 0x");
  Serial.print(mtype, HEX);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  mouse_init();
  bt.println("TESTE");
}

void loop()
{
  char mstat, mx, my, ms; //dx, dy, scr;
  
  mouse.write(0xeb); //ask for data
  mouse.read(); //ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();
  ms = mouse.read();
  
    if (mx != 0 || my != 0 || mstat != 8 || ms != 0)
  {
  /* send the data back up */
    bt.print(mstat, HEX);
    bt.print("\tmX=");
    bt.print(mx, DEC);
    bt.print("\tmY=");
    bt.print(my, DEC);
    bt.print("\tms=");
    bt.print(ms, DEC); 
    bt.println();

    Serial.print(mstat, HEX);
    Serial.print("\tdX=");
    Serial.print(mx, DEC);
    Serial.print("\tdY=");
    Serial.print(my, DEC);
    Serial.print("\tms=");
    Serial.print(ms, DEC);     
    
    Serial.println();
    delay(50);
    
   
  }
     
    
   
}



