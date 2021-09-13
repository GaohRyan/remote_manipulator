#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;



void serve();
void recieve();
void test();

int bendval[5];
int mode,key2,key3;

int thumbs;
int index_finger;
int middle_finger;
int ring_finger;
int little_finger;

void setup() {
 Serial.begin(57600);
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);
  servo(40,90,0,10,110);
 
  delay(1000);

}

void loop() {
  
 
 recieve1();
 servo(bendval[0], bendval[1], bendval[2], bendval[3], bendval[4]);
 // test();
 if (mode==2)
 {
  if(key2==0)
  {
     digitalWrite(8,0);
     digitalWrite(9,1);  
  }
  else
  {
    digitalWrite(8,0);
    digitalWrite(9,0); 
  }
  
  if(key3==0)
  {
    digitalWrite(8,1);
    digitalWrite(9,0);  
  }
 
 }

 
  if (mode==3)
 {
  if(key2==0)
  {
     digitalWrite(10,0);
     digitalWrite(11,1);  
  }
  else
  {
    digitalWrite(10,0);
    digitalWrite(11,0); 
  }
  
  if(key3==0)
  {
    digitalWrite(10,1);
    digitalWrite(11,0);  
  }
 
 }



 


 
  

}





void recieve1()
{
   if(Serial.available())
   {
  if('C'==Serial.read())
  {
     while(!Serial.available());
     bendval[0]=Serial.parseInt();
     while(!Serial.available());
     int a=Serial.read();

     while(!Serial.available());
     bendval[1]=Serial.parseInt();
     while(!Serial.available());
     int b=Serial.read();

     while(!Serial.available());
     bendval[2]=Serial.parseInt();
     while(!Serial.available());
     int c=Serial.read();

     while(!Serial.available());
     bendval[3]=Serial.parseInt();
     while(!Serial.available());
     int d=Serial.read();
                                                                                            
     while(!Serial.available());
     bendval[4]=Serial.parseInt();
     while(!Serial.available());
     int e=Serial.read();

     while(!Serial.available());
     mode=Serial.parseInt();
     while(!Serial.available());
     int f=Serial.read();

     while(!Serial.available());
     key2=Serial.parseInt();
     while(!Serial.available());
     int g=Serial.read();

     while(!Serial.available());
     key3=Serial.parseInt();
     while(!Serial.available());
     int h=Serial.read();
    
  }
  if(bendval[1]<0) bendval[1]=85;
  constrain(bendval[0],80,150);
  constrain(bendval[1],85,150);
  constrain(bendval[2],0,60);
  constrain(bendval[3],20,80);
  constrain(bendval[4],90,150);
   }
  
}

void recieve2()
{
   if(Serial.available())
   {
    if('W'==Serial.read())
    {
     while(!Serial.available());
     if(100==Serial.parseInt())
     {
       digitalWrite(8,0);
       digitalWrite(9,1);
      // Serial.println(100);
     }
     else
     {
      digitalWrite(8,0);
       digitalWrite(9,0);
     }

      if(200==Serial.parseInt())
     {
       digitalWrite(8,1);
       digitalWrite(9,0);
     //   Serial.println(200);
     }
      else
     {
      digitalWrite(8,0);
       digitalWrite(9,0);
     }
    
    }
   }
  
}



void servo(int a,int b,int c,int d,int e)
{
  servo1.write(a);
  servo2.write(b);
  servo3.write(c);
  servo4.write(d);
  servo5.write(e);
}


 void test()
{
  Serial.print("thumbs:");
  Serial.println(bendval[0]);
  Serial.print("index_finger:");
  Serial.println(bendval[1]);
  Serial.print("middle_finger:");
  Serial.println(bendval[2]);
  Serial.print("ring_finger:");
  Serial.println(bendval[3]);
  Serial.print("little_finger:");
  Serial.println(bendval[4]);
  Serial.println();
  Serial.println();
 // delay();
}
