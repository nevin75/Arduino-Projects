//设置控制各段的数字IO脚
int a = 12;
int b = 11;
int c = 10;
int d = 9;
int e = 8;
int f = 7;
int g = 6;
int dp = 5;
int ls1 = 1;
int ls2 = 2;
int ls3 = 3;
int ls4 = 4;


//显示数字0  ,  11111100
void digital_0(void)
{
  unsigned char j;
  digitalWrite(dp,LOW);//给数字5引脚低电平，熄灭小数点DP段
  digitalWrite(g,LOW);//熄灭g段
  for(j=7;j<=12;j++)//点亮其余段
    digitalWrite(j,HIGH);
}
//显示数字1  , 01100000
void digital_1(void)
{
  unsigned char j;
  digitalWrite(a,LOW);
  for(j=5;j<=9;j++)
    digitalWrite(j,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}
//显示数字2
void digital_2(void)
{
  unsigned char j;
  digitalWrite(c,LOW);
  digitalWrite(f,LOW);
  digitalWrite(dp,LOW);
  for(j=11;j<=12;j++)
    digitalWrite(j,HIGH);
  for(j=8;j<=9;j++)
    digitalWrite(j,HIGH);
  digitalWrite(g,HIGH);
}
//显示数字3 22
void digital_3(void)
{
  unsigned char j;
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(dp,LOW);
  for(j=9;j<=13;j++)
    digitalWrite(j,HIGH);
  digitalWrite(g,HIGH);
}
//显示数字4
void digital_4(void)
{
  digitalWrite(a,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(dp,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);   
}
//显示数字5
void digital_5(void)
{
  unsigned char j;
  digitalWrite(b,LOW);
  digitalWrite(e,LOW);
  digitalWrite(dp,LOW);
  
  digitalWrite(a,HIGH);
  for(j=6;j<=7;j++)
    digitalWrite(j,HIGH);
  for(j=9;j<=10;j++)
    digitalWrite(j,HIGH);
}
//显示数字6
void digital_6(void)
{
  unsigned char j;
  digitalWrite(b,LOW);
  digitalWrite(dp,LOW);
  
  digitalWrite(a,HIGH);
  for(j=6;j<=10;j++)
    digitalWrite(j,HIGH); 
}
//显示数字7
void digital_7(void)
{
  unsigned char j;
  for(j=5;j<=9;j++)
    digitalWrite(j,LOW);
  for(j=10;j<=12;j++)
    digitalWrite(j,HIGH);
}
//显示数字8
void digital_8(void)
{
  unsigned char j;
  digitalWrite(dp,LOW);
  for(j=6;j<=12;j++)
    digitalWrite(j,HIGH);
}
//显示数字9
void digital_9(void)
{
  unsigned char j;
  digitalWrite(e,LOW);
  digitalWrite(dp,LOW);
  
  for(j=9;j<=12;j++)
    digitalWrite(j,HIGH);
  for(j=6;j<=7;j++)
    digitalWrite(j,HIGH);
}

//显示----------------------------
void Display(unsigned char mun)
{
  switch (mun) {
    case 0:
      digital_0();//显示数字0
      break;
    case 1:
      digital_1();
      break;
    case 2:
      digital_2();
      break;
    case 3:
      digital_3();
      break;
    case 4:
      digital_4();
      break;
    case 5:
      digital_5();
      break;
    case 6:
      digital_6();
      break;
    case 7:
      digital_7();
      break;
   case 8:
      digital_8();
      break;
   case 9:
      digital_9();
      break;  
    default: return;
      // if nothing else matches, do the default
      // default is optional
  }
}

void setup()
{
  int i;//定义变量
  for(i=1;i<=12;i++)
    pinMode(i,OUTPUT);//设置1～12引脚为输出模式
}
void loop()
{ 
  unsigned char i, j, t;
  while(1)
  {
    t = 1;
    for(j=0; j<4 ; j++)
    {
       digitalWrite(j,LOW); //熄灭数码管使能端
    }

    for(i=0; i<=9 ; i++)
    {
      if(t==1) //第一位数码管显示数字
      {
        digitalWrite(ls4,HIGH);
        digitalWrite(ls3,HIGH);
        digitalWrite(ls2,HIGH);
        digitalWrite(ls1,LOW);
      }
      if(t==2) //第二位数码管显示数字
      {
        digitalWrite(ls4,HIGH);
        digitalWrite(ls3,HIGH);
        digitalWrite(ls1,HIGH);
        digitalWrite(ls2,LOW);
      }
      if(t==3) //第三位数码管显示数字
      {
        digitalWrite(ls4,HIGH);
        digitalWrite(ls2,HIGH);
        digitalWrite(ls1,HIGH);
        digitalWrite(ls3,LOW);
      }
      if(t==4) //第四位数码管显示数字
      {
        t = 0;
        digitalWrite(ls3,HIGH);
        digitalWrite(ls2,HIGH);
        digitalWrite(ls1,HIGH);
        digitalWrite(ls4,LOW);
      }      
      Display(i);
      delay(2000);//延时2s
      t++;
      
      for(j=0; j<4 ; j++)
      {
         digitalWrite(j,LOW); //熄灭数码管使能端
      }
    }
  }
}
