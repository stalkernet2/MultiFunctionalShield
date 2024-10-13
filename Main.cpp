#define LATCH_DIO 4 //линия синхронизации данных, защелка (LCHCLK)
#define CLK_DIO 7 //линия тактирования (SFTCLK)
#define DATA_DIO 8 //линия передачи данных(SDI)

int metrPin = A0; // динамический резистор
int inPin1 = A1; // кнопки
int inPin2 = A2;
int inPin3 = A3;

int val = 4123;
bool A1isPressed = false;

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90}; // байты чисел 0-9
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8}; // секции дисплея 1-4
 
void setup ()
{
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
}
 
void loop()
{
  val = analogRead(metrPin);
  delay(1000);
}

void yield()
{
  DrawNum();
  if(digitalRead(inPin1) == LOW)
  {
    AddNum();
  }
  else
  {
    A1isPressed = false;
  }
}

void AddNum()
{
  if(A1isPressed)
  {
    return;
  }

  val++;
  A1isPressed = true;
}
 
void DrawNum()
{
  if(val == 0 || val == 10000)
  {
    val = 1;
  }
  int tempValue = val;
  int thousandths = tempValue / 1000;
  tempValue = tempValue - thousandths * 1000;
  int hundredths = tempValue / 100;
  tempValue = tempValue - hundredths * 100;
  int tenths = tempValue / 10;
  tempValue = tempValue - tenths * 10;;
  int ones = tempValue;

  WriteNumberToSegment(0 , thousandths);
  WriteNumberToSegment(1 , hundredths);
  WriteNumberToSegment(2 , tenths);
  WriteNumberToSegment(3 , ones);
}

void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO,HIGH);
}
