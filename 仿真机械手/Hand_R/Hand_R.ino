#include<Servo.h>
Servo servol_1;
Servo servol_2;
Servo servol_3;
Servo servol_4;
Servo servol_5;

int thumbs = 'l';
int index_finger = 'a';
int middle_finger = 'a';
int ring_finger = 'a';
int little_finger = 'a';

int bendVal[5];

int mode;
int zheng;
int fan;

void Recieve();
void transVal(); 
void Test();
void servo(int a,int b,int c,int d,int e);

void setup()
{
  Serial.begin(57600);
  servol_1.attach(3);
  servol_2.attach(4);
  servol_3.attach(5);
  servol_4.attach(6);
  servol_5.attach(7);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  servo(40,90,0,10,110);
  delay(2000);
  
}

void loop() 
{
  Recieve();
  transVal();
  servo(bendVal[0], bendVal[1], bendVal[2], bendVal[3], bendVal[4]);
  if(mode == 't')
  {
    if(zheng == 'a')
    {
      digitalWrite(8,0);
      digitalWrite(9,1);
    }
    else if(fan == 'a')
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
    }
    else
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
    }
  }  
  if(mode == 'z efft  //cij')
  {
    if(zheng == 'a')
    {
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
    else if(fan == 'a')
    {
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    else
    {
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
  }
  Test();
}

void Recieve()
{
  if('C' == Serial.read())
  {
    while(!Serial.available());
    thumbs = Serial.read();
    while(!Serial.available());
    index_finger = Serial.read();
    while(!Serial.available());
    middle_finger = Serial.read();
    while(!Serial.available());
    ring_finger = Serial.read();
    while(!Serial.available());
    little_finger = Serial.read();
    while(!Serial.available());
    mode = Serial.read();
    while(!Serial.available());
    zheng = Serial.read();
    while(!Serial.available());
    fan = Serial.read();
  }
}
void transVal()
{
  if(thumbs == 'a')
  {
    bendVal[0] = 150;
  }
  if(thumbs =='b')
  {
    bendVal[0] = 140;
  }
  if(thumbs == 'c')
  {
    bendVal[0] = 130;
  }
  if(thumbs == 'd')
  {
    bendVal[0] = 120;
  }
  if(thumbs == 'e')
  {
    bendVal[0] = 110;
  }
  if(thumbs == 'f')
  {
    bendVal[0] = 100;
  }
  if(thumbs == 'g')
  {
    bendVal[0] = 90;
  }
  if(thumbs == 'h')
  {
    bendVal[0] = 80;
  }
  if(thumbs == 'i')
  {
    bendVal[0] = 70;
  }
  if(thumbs == 'j')
  {
   bendVal[0] = 60;
  }
  if(thumbs == 'k')
  {
    bendVal[0] = 50;
  }
  if(thumbs == 'l')
  {
    bendVal[0] = 40;
  }

  if(index_finger == 'a')
  {
    bendVal[1] = 90;
  }
  if(index_finger == 'b')
  {
    bendVal[1] = 100;
  }
  if(index_finger == 'c')
  {
    bendVal[1] = 110;
  }
  if(index_finger == 'd')
  {
    bendVal[1] = 120;
  }
  if(index_finger == 'e')
  {
    bendVal[1] = 130;
  }
  if(index_finger == 'f')
  {
    bendVal[1] = 140;
  }
  if(index_finger == 'g')
  {
    bendVal[1] = 150;
  }
  if(index_finger == 'h')
  {
    bendVal[1] = 160;
  }
  if(index_finger == 'i')
  {
    bendVal[1] = 170;
  }
  if(index_finger == 'j')
  {
    bendVal[1] = 180;
  }

  if(middle_finger == 'a')
  {
    bendVal[2] = 0;
  }
  if(middle_finger == 'b')
  {
    bendVal[2] = 10;
  }
  if(middle_finger == 'c')
  {
    bendVal[2] = 20;
  }
  if(middle_finger == 'd')
  {
    bendVal[2] = 30;
  }
  if(middle_finger == 'e')
  {
    bendVal[2] = 40;
  }
  if(middle_finger == 'f')
  {
    bendVal[2] = 50;
  }
  if(middle_finger == 'g')
  {
    bendVal[2] = 60;
  }
  if(middle_finger == 'h')
  {
    bendVal[2] = 70;
  }
  if(middle_finger == 'i')
  {
    bendVal[2] = 80;
  }
  if(middle_finger == 'j')
  {
    bendVal[2] = 85;
  }

  if(ring_finger ==  'a')
  {
    bendVal[3] = 10;
  }
  if(ring_finger == 'b')
  {
    bendVal[3] = 20;
  }
  if(ring_finger == 'c')
  {
    bendVal[3] = 30;
  }
  if(ring_finger == 'd')
  {
    bendVal[3] = 40;
  }
  if(ring_finger == 'e')
  {
    bendVal[3] = 50;
  }
  if(ring_finger == 'f')
  {
    bendVal[3] = 60;
  }
  if(ring_finger == 'g')
  {
    bendVal[3] = 70;
  }
  if(ring_finger == 'h')
  {
    bendVal[3] = 80;
  }
  if(ring_finger == 'i')
  {
    bendVal[3] = 90;
  }
  if(ring_finger == 'j')
  {
    bendVal[3] = 100;
  }
  if(ring_finger == 'k')
  {
    bendVal[3] = 110;
  }

  if(little_finger == 'a')
  {
    bendVal[4] = 90;
  }
  if(little_finger == 'b')
  {
    bendVal[4] = 100;
  }
  if(little_finger == 'c')
  {
    bendVal[4] = 110;
  }
  if(little_finger == 'd')
  {
    bendVal[4] = 120;
  }
  if(little_finger == 'e')
  {
    bendVal[4] = 130;
  }
  if(little_finger == 'f')
  {
    bendVal[4] = 140;
  }
  if(little_finger == 'g')
  {
    bendVal[4] = 150;
  } 
}

void servo(int a,int b,int c,int d,int e)
{
  servol_1.write(a);
  servol_2.write(b);
  servol_3.write(c);
  servol_4.write(d);
  servol_5.write(e);
}
void Test()
{
   Serial.print("thumbs;");
   Serial.println(bendVal[0]);
   Serial.print("index_finger;");
   Serial.println(bendVal[1]);
   Serial.print("middle_finger;");
   Serial.println(bendVal[2]);
   Serial.print("ring_finger;");
   Serial.println(bendVal[3]);
   Serial.print("little_finger;");
   Serial.println(bendVal[4]);
}



