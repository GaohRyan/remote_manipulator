


int bend_thumbs = A0;
int bend_index_finger = A1;
int bend_middle_finger = A2;
int bend_ring_finger = A3;
int bend_little_finger = A6;

int mode=1;
const int LED=8;

const int KEY2=6;
const int KEY3=7;
int key2,key3;


void getval();
void sendval1();
void sendval2();


int bendval[5];

void setup() {
  Serial.begin(57600);
   pinMode(2,INPUT_PULLUP);
   pinMode(KEY2,INPUT_PULLUP);
   pinMode(KEY3,INPUT_PULLUP);
   pinMode(LED,OUTPUT);
   attachInterrupt(0, state, CHANGE);

}

void loop() {
   

 
  
   

  getval();
  //test();
 sendval1();
 


}



void getval()
{
  bendval[0] =  analogRead(bend_middle_finger);//analogRead(bend_thumbs);
  bendval[1] = analogRead(bend_middle_finger);//analogRead(bend_index_finger);
  bendval[2] = analogRead(bend_middle_finger);
  bendval[3] = analogRead(bend_middle_finger);                                    //analogRead(bend_ring_finger);
  bendval[4] = analogRead(bend_middle_finger);//analogRead(bend_little_finger);
  key2=digitalRead(KEY2);
  key3=digitalRead(KEY3);

  constrain(bendval[0],190,400);
  constrain(bendval[1],320,600);
  constrain(bendval[2],390,650);
  constrain(bendval[3],330,610);
  constrain(bendval[4],360,605);

  bendval[0]=map( bendval[0],190,400,150,80);
  bendval[1]=map( bendval[1],320,600,150,85);
  bendval[2]=map( bendval[2],390,650,60,0);
  bendval[3]=map( bendval[3],330,610,80,20);
  bendval[4]=map( bendval[4],360,605,150,90);
 }


 void sendval1()
 {
 Serial.print('C');
  Serial.print(bendval[0],DEC);
  Serial.write('a');

  Serial.print(bendval[1],DEC);
  Serial.write('a');

  Serial.print(bendval[2],DEC);
  Serial.write('a');

  Serial.print(bendval[3],DEC);
  Serial.write('a');

  Serial.print(bendval[4],DEC);
  Serial.write('a');

  Serial.print(mode,DEC);
  Serial.write('a');

  Serial.print(key2,DEC);
  Serial.write('a');

  Serial.print(key3,DEC);
  Serial.write('a');

  
   delay(20);
 
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
  delay(500);
}




void state()
{
  mode++;
  if (mode>3)
  mode=1;

  if(mode==3)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  
}



 
