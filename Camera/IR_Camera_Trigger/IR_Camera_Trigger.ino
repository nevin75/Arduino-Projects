#define IR_IN  8  //红外接收


int shutter = 9;
int Pulse_Width=0;//存储脉宽 
int adr_code=0x00;// 用户编码值
char comL_code=0x00;//命令码
char comH_code=0x00;//命令码反码

void timer1_init(void)//定时器初始化函数
{
  TCCR1A = 0X00; 
  TCCR1B = 0X05;//给定时器时钟源  
  TCCR1C = 0X00;
  TCNT1 = 0X00;
  TIMSK1 = 0X00;	//禁止定时器溢出中断
}
void remote_deal(void)//执行译码结果函数
{ 
      //数据显示
    Serial.println("");
    Serial.print("the Address Code is : "); 
    Serial.print(adr_code, HEX);//16进制显示
    Serial.println("");
    Serial.print("the Command code is : ");
    Serial.print(comL_code, HEX);//16进制显示
}
char logic_value()//判断逻辑值“0”和“1”子函数
{
  TCNT1 = 0X00;
  while(!(digitalRead(IR_IN))); //低等待
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=7&&Pulse_Width<=10)//低电平560us
  {
    while(digitalRead(IR_IN));//是高就等待
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=7&&Pulse_Width<=10)//接着高电平560us
      return 0;
   else if(Pulse_Width>=25&&Pulse_Width<=27) //接着高电平1.7ms
      return 1;
  }
  return -1;
}
void pulse_deal()//接收地址码和命令码脉冲函数
{
  int i;
  int j;
  adr_code=0x00;// 清零
  comL_code=0x00;// 清零
  comH_code=0x00;// 清零

  //解析遥控器编码中的用户编码值  
  for(i = 0 ; i < 16; i++)
  {
    if(logic_value() == 1) //是1
        adr_code |= (1<<i);//保存键值
  }
  //解析遥控器编码中的命令码
  for(i = 0 ; i < 8; i++)
  {
    if(logic_value() == 1) //是1
      digitalWrite(shutter, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(50);               // wait for 50 milliseconds
        digitalWrite(shutter, LOW);    // turn the LED off by making the voltage LOW
   comL_code |= (1<<i);//保存键值
  }
  //解析遥控器编码中的命令码反码 
  for(j = 0 ; j < 8; j++)
  {
    if(logic_value() == 1) //是1
        comH_code |= (1<<j);//保存键值
  }
}
void remote_decode(void)//译码函数
{
  TCNT1=0X00;       
  while(digitalRead(IR_IN))//是高就等待
  {
    if(TCNT1>=1563)  //当高电平持续时间超过100ms，表明此时没有按键按下
    {
      adr_code=0x00ff;// 用户编码值
      comL_code=0x00;//键码前一个字节值
      comH_code=0x00;//键码后一个字节值
      return;
    }  
  }

  //如果高电平持续时间不超过100ms
  TCNT1=0X00;

  while(!(digitalRead(IR_IN))); //低等待
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=140&&Pulse_Width<=141)//9ms
  {

    while(digitalRead(IR_IN));//是高就等待
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=68&&Pulse_Width<=72)//4.5ms
    {  
      pulse_deal();
      return;
    }
    else if(Pulse_Width>=34&&Pulse_Width<=36)//2.25ms
    {
      while(!(digitalRead(IR_IN)));//低等待
      Pulse_Width=TCNT1;
      TCNT1=0;
      if(Pulse_Width>=7&&Pulse_Width<=10)//560us
      {
        return; 
      }
    }
  }
}
void setup()
{
    pinMode(shutter, OUTPUT);     

  unsigned char i;
  pinMode(IR_IN,INPUT);//设置红外接收引脚为输入
  // start serial port at 9600 bps:
  Serial.begin(9600);
}
void loop()
{  
  timer1_init();//定时器初始化
  while(1)
  {
    remote_decode();  //译码
    remote_deal();   //执行译码结果
   
  }  
}
