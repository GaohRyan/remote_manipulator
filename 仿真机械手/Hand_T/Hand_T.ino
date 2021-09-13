#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define KEY1 5
#define KEY2 6
#define KEY3 7
#define LED 8

int mode = 't';
int zheng = 'b';
int fan = 'b';
int anglex,angley;
void Kalmen_Init();
void Kalmen();

 ////////////////////////MPU 6050变量////////////
MPU6050 accelgyro;
unsigned long now, lastTime = 0;
float dt;                                   //微分时间
int16_t ax, ay, az, gx, gy, gz;             //加速度计陀螺仪原始数据 
float aax=0, aay=0, agx=0, agy=0, agz=0;    //角度变量
long axo = 0, ayo = 0, azo = 0;             //加速度计偏移量
long gxo = 0, gyo = 0,
gzo = 0;             //陀螺仪偏移量
float pi = 3.1415926;
float AcceRatio = 16384.0;                  //加速度计比例系数
float GyroRatio = 131.0;                    //陀螺仪比例系数
uint8_t n_sample = 8;                       //加速度计滤波算法采样个数
float aaxs[8] = {0}, aays[8] = {0};         //x,y轴采样队列
long aax_sum, aay_sum;                      //x,y轴采样和
float a_x[10]={0}, a_y[10]={0} ,g_x[10]={0} ,g_y[10]={0}; //加速度计协方差计算队列
float Px=1, Rx, Kx, Sx, Vx, Qx;             //x轴卡尔曼变量
float Py=1, Ry, Ky, Sy, Vy, Qy;             //y轴卡尔曼变量
 //////////////MPU6050  end ///////////////////////////////////////

int bend_thumbs = A0;
int bend_index_finger = A1;
int bend_middle_finger = A2;
int bend_ring_finger = A3;
int bend_little_finger = A6;

int thumbs = 0;
int index_finger = 0;
int middle_finger = 0;
int ring_finger = 0;
int little_finger = 0;

byte bendVal[5];

void getVal();
void transVal();
void ScanKey();
void sendVal();
void test();

void setup()
{
  Serial.begin(57600);
  pinMode(KEY1,INPUT_PULLUP);
  pinMode(KEY2,INPUT_PULLUP);
  pinMode(KEY3,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  Kalmen_Init();
}

void loop()
{
  Kalmen();
  getVal();
  transVal();
  ScanKey();  
  sendVal();
  //test();
}

void getVal()
{
  bendVal[0] = analogRead(bend_thumbs)/4;
  bendVal[1] = analogRead(bend_index_finger)/4;
  bendVal[2] = analogRead(bend_middle_finger)/4;
  bendVal[3] = analogRead(bend_ring_finger)/4;
  bendVal[4] = analogRead(bend_little_finger)/4;
}

void transVal()
{
  if(bendVal[0]>=120)
  {
    thumbs = 'a';//150;
  }
  if(bendVal[0]<120&&bendVal[0]>=115.8)
  {
    thumbs = 'b';//140;
  }
  if(bendVal[0]<115.8&&bendVal[0]>=111.6)
  {
    thumbs = 'c';//130;
  }
  if(bendVal[0]<111.6&&bendVal[0]>=107.4)
  {
    thumbs = 'd';//120;
  }
  if(bendVal[0]<107.4&&bendVal[0]>=103.2)
  {
    thumbs = 'e';//110;
  }
  if(bendVal[0]<103.2&&bendVal[0]>=99)
  {
    thumbs = 'f';//100;
  }
  if(bendVal[0]<99&&bendVal[0]>=94.8)
  {
    thumbs = 'g';//90;
  }
  if(bendVal[0]<94.8&&bendVal[0]>=90.6)
  {
    thumbs = 'h';//80;
  }
  if(bendVal[0]<90.6&&bendVal[0]>=86.4)
  {
    thumbs = 'i';//70;
  }
  if(bendVal[0]<86.4&&bendVal[0]>=82.2)
  {
    thumbs = 'j';//60;
  }
  if(bendVal[0]<82.2&&bendVal[0]>=79)
  {
    thumbs = 'k';//50;
  }
  if(bendVal[0]<79)
  {
    thumbs = 'l';//40;
  }

  if(bendVal[1]>=169)
  {
    index_finger = 'a';//90;
  }
  if(bendVal[1]<169&&bendVal[1]>=160.375)
  {
    index_finger = 'b';//100;
  }
  if(bendVal[1]<160.375&&bendVal[1]>=151.75)
  {
    index_finger = 'c';//110;
  }
  if(bendVal[1]<151.75&&bendVal[1]>=143.125)
  {
    index_finger = 'd';//120;
  }
  if(bendVal[1]<143.125&&bendVal[1]>=134.5)
  {
    index_finger = 'e';//130;
  }
  if(bendVal[1]<134.5&&bendVal[1]>=125.875)
  {
    index_finger = 'f';//140;
  }
  if(bendVal[1]<125.875&&bendVal[1]>=117.25)
  {
    index_finger = 'g';//150;
  }
  if(bendVal[1]<117.25&&bendVal[1]>=108.625)
  {
    index_finger = 'h';//160;
  }
  if(bendVal[1]<108.625&&bendVal[1]>=100)
  {
    index_finger = 'i';//170;
  }
  if(bendVal[1]<100)
  {
    index_finger = 'j';//180;
  }

  if(bendVal[2]>=173)
  {
    middle_finger = 'a';//0;
  }
  if(bendVal[2]<173&&bendVal[2]>=166.375)
  {
    middle_finger = 'b';//10;
  }
  if(bendVal[2]<166.375&&bendVal[2]>=159.75)
  {
    middle_finger = 'c';//20;
  }
  if(bendVal[2]<159.75&&bendVal[2]>=153.125)
  {
    middle_finger = 'd';//30;
  }
  if(bendVal[2]<153.125&&bendVal[2]>=146.5)
  {
    middle_finger = 'e';//40;
  }
  if(bendVal[2]<146.5&&bendVal[2]>=139.875)
  {
    middle_finger = 'f';//50;
  }
  if(bendVal[2]<139.875&&bendVal[2]>=133.25)
  {
    middle_finger = 'g';//60;
  }
  if(bendVal[2]<133.25&&bendVal[2]>=126.625)
  {
    middle_finger = 'h';//70;
  }
  if(bendVal[2]<126.625&&bendVal[2]>=120)
  {
    middle_finger = 'i';//80;
  }
  if(bendVal[2]<120)
  {
    middle_finger = 'j';//85;
  }

  if(bendVal[3]>=172)
  {
    ring_finger = 'a';//10;
  }
  if(bendVal[3]<172&&bendVal[3]>=164.6)
  {
    ring_finger = 'b';//20;
  }
  if(bendVal[3]<164.6&&bendVal[3]>=157.2)
  {
    ring_finger = 'c';//30;
  }
  if(bendVal[3]<157.2&&bendVal[3]>=149.8)
  {
    ring_finger = 'd';//40;
  }
  if(bendVal[3]<149.8&&bendVal[3]>=142.4)
  {
    ring_finger = 'e';//50;
  }
  if(bendVal[3]<142.4&&bendVal[3]>=135)
  {
    ring_finger = 'f';//60;
  }
  if(bendVal[3]<135&&bendVal[3]>=127.6)
  {
    ring_finger = 'g';//70;
  }
  if(bendVal[3]<127.6&&bendVal[3]>=120.2)
  {
    ring_finger = 'h';//80;
  }
  if(bendVal[3]<120.2&&bendVal[3]>=112.8)
  {
    ring_finger = 'i';//90;
  }
  if(bendVal[3]<112.8&&bendVal[3]>=105)
  {
    ring_finger = 'j';//100;
  }
  if(bendVal[3]<105)
  {
    ring_finger = 'k';//110;
  }

  if(bendVal[4]>=123)
  {
    little_finger = 'a';//90;
  }
  if(bendVal[4]<123&&bendVal[4]>=113.4)
  {
    little_finger = 'b';//100;
  }
  if(bendVal[4]<113.4&&bendVal[4]>=103.8)
  {
    little_finger = 'c';//110;
  }
  if(bendVal[4]<103.8&&bendVal[4]>=94.2)
  {
    little_finger = 'd';//120;
  }
  if(bendVal[4]<94.2&&bendVal[4]>=84.6)
  {
    little_finger = 'e';//130;
  }
  if(bendVal[4]<84.6&&bendVal[4]>=75)
  {
    little_finger = 'f';//140;
  }
  if(bendVal[4]<75)
  {
    little_finger = 'g';//150;
  }
}

void ScanKey()
{ 

  if(digitalRead(KEY1) == LOW)
  {
    mode =  'z';
    digitalWrite(LED,HIGH);
  }
  else
  {
    mode = 't'; 
    digitalWrite(LED,LOW);
  }
  
  anglex=agx+90;
  angley=agy+90;
  zheng = anglex>110?'a':'b';
  fan = anglex<60?'a':'b';
  
//  if(digitalRead(KEY2) == LOW)
//  {
//    zheng = 'a';
//    fan = 'b';
//  }
//  else if(digitalRead(KEY3) == LOW)
//  {
//    zheng = 'b';
//    fan = 'a';
//  }
//  else
//  {
//    zheng = 'b';
//    fan = 'b';
//  }
}

void sendVal()
{
  Serial.print('C');
  Serial.write(thumbs);
  Serial.write(index_finger);
  Serial.write(middle_finger);
  Serial.write(ring_finger);
  Serial.write(little_finger);
  Serial.write(mode);
  Serial.write(zheng);
  Serial.write(fan);
  delay(20);
}

void Kalmen_Init()
{
  Wire.begin();
  accelgyro.initialize();                 //初始化
  unsigned short times = 200;             //采样次数
  for(int i=0;i<times;i++)
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //读取六轴原始数值
    axo += ax; ayo += ay; azo += az;      //采样和
    gxo += gx; gyo += gy; gzo += gz;
  }
  axo /= times; ayo /= times; azo /= times; //计算加速度计偏移
  gxo /= times; gyo /= times; gzo /= times; //计算陀螺仪偏移  
}

void Kalmen()
{
  now = millis();             //当前时间(ms)
  dt = (now - lastTime) / 1000.0;           //微分时间(s)
  lastTime = now;                           //上一次采样时间(ms)
 
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //读取六轴原始数值
 
  float accx = ax / AcceRatio;              //x轴加速度
  float accy = ay / AcceRatio;              //y轴加速度
  float accz = az / AcceRatio;              //z轴加速度
 
  aax = atan(accy / accz) * (-180) / pi;    //x轴对于水平面的夹角
  aay = atan(accx / accz) * 180 / pi;       //y轴对于水平面的夹角
 
  aax_sum = 0;         // 对于加速度计原始数据的滑动加权滤波算法
  aay_sum = 0;
  for(int i=1;i<n_sample;i++)
  {
    aaxs[i-1] = aaxs[i];
    aax_sum += aaxs[i] * i;
    aays[i-1] = aays[i];
    aay_sum += aays[i] * i;
  }
  aaxs[n_sample-1] = aax;
  aax_sum += aax * n_sample;
  aax = (aax_sum / (11*n_sample/2.0)) * 9 / 7.0; //角度调幅至0-90°
  aays[n_sample-1] = aay;                        //此处应用实验法取得合适的系数
  aay_sum += aay * n_sample;                     //本例系数为9/7
  aay = (aay_sum / (11*n_sample/2.0)) * 9 / 7.0;

  float gyrox = - (gx-gxo) / GyroRatio * dt; //x轴角速度
  float gyroy = - (gy-gyo) / GyroRatio * dt; //y轴角速度
  agx += gyrox;                             //x轴角速度积分
  agy += gyroy;                             //x轴角速度积分
 
  /* kalmen start */
  Sx = 0; Rx = 0;
  Sy = 0; Ry = 0;
  for(int i=1;i<10;i++){                 //测量值平均值运算
    a_x[i-1] = a_x[i];                      //即加速度平均值
    Sx += a_x[i];
    a_y[i-1] = a_y[i];
    Sy += a_y[i];
  }
  a_x[9] = aax;
  Sx += aax;
  Sx /= 10;                                 //x轴加速度平均值
  a_y[9] = aay;
  Sy += aay;
  Sy /= 10;                                 //y轴加速度平均值
 
  for(int i=0;i<10;i++){
    Rx += sq(a_x[i] - Sx);
    Ry += sq(a_y[i] - Sy);
  }
  Rx = Rx / 9;                              //得到方差
  Ry = Ry / 9;                        
 
  Px = Px + 0.0025;                         // 0.0025在下面有说明...
  Kx = Px / (Px + Rx);                      //计算卡尔曼增益
  agx = agx + Kx * (aax - agx);             //陀螺仪角度与加速度计速度叠加
  Px = (1 - Kx) * Px;                       //更新p值
 
  Py = Py + 0.0025;
  Ky = Py / (Py + Ry);
  agy = agy + Ky * (aay - agy); 
  Py = (1 - Ky) * Py;
}

void test()
{
  Serial.print("thumbs:");
  Serial.println(bendVal[0]);
  Serial.print("index_finger:");
  Serial.println(bendVal[1]);
  Serial.print("middle_finger:");
  Serial.println(bendVal[2]);
  Serial.print("ring_finger:");
  Serial.println(bendVal[3]);
  Serial.print("little_finger:");
  Serial.println(bendVal[4]);
  delay(2000);
}

