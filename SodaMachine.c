// Graphic Serial LCD 128x64
 
// Arduino Pin 9 (TX) to LCD Pin RX
 
// Arduino Pin Vin to LCD Vin (Assuming you're powering Arduino externally with 9 VDC)
 
// Arduino Pin Gnd to LCD Pin Gnd
char cC[4],cF[4],s[4];
char Name[10];
char Credit[10];
int option;
 char ID[4];
 
const int buttonPinCola = 2;
const int buttonPinFanta = 4;
const int buttonPinOk = 8;  // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
short buttonStateCola = 0;       // variable for reading the pushbutton status
short buttonStateFanta = 0;
short buttonStateOk = 0;
short buttonCola = 0;
short buttonFanta = 0;
short buttonOk = 0;
short ok=0,buttonMain=-1;
short MOTOR2_PIN1 = 3;
short MOTOR2_PIN2 = 5;
short MOTOR1_PIN1 = 6;
short MOTOR1_PIN2 = 9;
short updateSuma;
short UserSold;
int contor1 = 0;
int contor2 = 0;
void setup() {
  Serial2.begin(115200);
  Serial.begin(9600);
  setX(0);
  setY(0);
  clearScreen();
  pinMode(buttonPinCola, INPUT);
  pinMode(buttonPinFanta, INPUT);
  pinMode(buttonPinOk, INPUT);
    pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
 
  setBackgroundBrightness(150);

}

 
void loop()
{ 
initVar();
 clearScreen();
LCD_State1_Idle();
delay(5000);
 clearScreen();
GetData_State2();
 delay(5000);

// clearScreen();
// LCD_State4_TakeCup();
 
}

void initVar()
{
 contor1=0;
 contor2=0;
 ok=0;
}

void updateSold()
{
   UserSold= UserSold-3;
  
}
 void Juice(short x)
{
   if (x==0)
  {
  if (contor1 == 0) 
  {
    analogWrite(MOTOR2_PIN1,255 );
    delay(5000);
    contor1 = 1;

  }
  else
  {
    analogWrite(MOTOR2_PIN1,0);
    delay(1000);
  }
  }

  else if ( x==1)
  {
     if (contor2 == 0) 
  {
    analogWrite(MOTOR1_PIN1,255 );
    delay(30000);
    contor2 = 1;

  }
  else
  {
    analogWrite(MOTOR1_PIN1,0);
    delay(1000);
  }
  }

  analogWrite(MOTOR2_PIN1,0);
  analogWrite(MOTOR1_PIN1,0);
}


 void LCD_State1_Idle(){
  setX(50); 
  setY(0);
  print("FEV");
    int valC = analogRead(0);
    int valF = analogRead(1);
  delay(50); 
  setX(0); 
  setY(20);
  print("Cantitate Cola:");
    if (valC > 0) {
  itoa(valC,cC,10);
   print(cC);
  }
  delay(100); 

   setX(0); 
  setY(30);
  print("Cantitate Fanta:");
    if (valF > 0) {
  itoa(valF,cF,10);
   print(cF);
  }
  delay(100);
  
   setX(0); 
  setY(40);
  print("Pret Cola:3 lei");
  delay(100);

  setX(0); 
  setY(50);
  print("Pret Fanta:3 lei");
  delay(100);
 }
 void GetData_State2()
 {
   getAll("0/Cata/32/-1");
   LCD_State2_Fps(Name,Credit,option);
  
 }
 void LCD_State2_Fps(char *nume,char *sold,int valid){
  setX(35);
  setY(0);
  print("Hello ");
  delay(60);
  print (nume);
  delay(60);

  setX(0);
  setY(20);
  print("Sold:");
  itoa(UserSold,s,10);
  print (s);
  delay(60);
 
  if(valid == -1)
  { 
  setX(0);
  setY(40);
  print("Choose your");
  delay(80); 
  setX(70);
  setY(40);
  print("option:");
  delay(80);
  ChooseBottom();
   delay(200);
  if(buttonMain==0) {
     clearScreen();
 LCD_State3_Wait();
    Juice(0);
    updateSold();
    delay(500);
     clearScreen();
 LCD_State4_TakeCup();
 delay(5000);
  }
  else if(buttonMain==1){ 
    clearScreen();
 LCD_State3_Wait();
    Juice(1);
    updateSold();
  clearScreen();
 LCD_State4_TakeCup();
 delay(5000);
  }
  else {
     clearScreen();
  setX(30);
  setY(25);
  print("Wrong input");
 delay(5000);
  }
  
  } 
  else if(valid == 0)
  {
   setX(0);
  setY(40);
  print("You want");
  delay(80); 
  setX(55);
  setY(40);
  print("Cola?");
 delay(80);
  }
  else {
  setX(0);
  setY(40);
  print("You want");
  delay(80); 
  setX(55);
  setY(40);
  print("Fanta?");
 delay(80);
 }
 }

 void LCD_State3_Wait()
 {
  setX(30);
  setY(30);
  print("Waiting");
  delay(70);
  setX(73);
  setY(30);
  print("...");
  delay(40);
 }

 void LCD_State4_TakeCup()
 {

  setX(30);
  setY(25);
  print("Take the");
  delay(70);
  setX(77);
  setY(25);
  print(" cup!");
  delay(40);
 }

void getAll(char*vector)
{
 unsigned int i,k;
 int separator=0;
 char Option[2];
 int count=0;
 int n=strlen(vector);
 if(n==2)
 {
  if(strcmp(vector,"DA")==0)
        option=4;
 }
 else
{
  if(n>5)
 {
     for(i=0;i<n;i++)
    {
        if((vector[i]!='/')&&(separator==0))
        {
            ID[count++]=vector[i];
        }
        else
       {
            if((vector[i]=='/')&&(separator==0))
            {
                  k=i;separator++;
            }
       }
    }
    count=0;
    separator=0;
    k++;
    for(i=k;i<n;i++)
    {
          if((separator==0)&&(vector[i]!='/'))
          {
              Name[count++]=vector[i];
          }
          else
          {
                if((vector[i]=='/')&&(separator==0))
              {
                    k=i;separator++;
              }
          }
    }
    count=0;
    separator=0;
    k++;
    for(i=k;i<n;i++)
    {
        if((separator==0)&&(vector[i]!='/'))
        {
             Credit[count++]=vector[i];
        }
        else
        {
             if((vector[i]=='/')&&(separator==0))
            {
                 k=i;separator++;
            }
        }
    }
    count=0;
    for(i=k+1;i<n;i++)
    {
       Option[count++]=vector[i];
    }
    option=atoi(Option);
}
else
{
  option=3;
  for(i=2;i<n;i++)
  {
    ID[count++]=vector[i];
  }
}
}
UserSold=atoi(Credit);
}

void ChooseBottom()
{
  Serial.println("Choose bottoms");
   while(ok==0){
  buttonStateCola = digitalRead(buttonPinCola);
  buttonStateFanta = digitalRead(buttonPinFanta);
  buttonStateOk = digitalRead(buttonPinOk);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  
  if (buttonStateCola != LOW) {
    buttonMain=0;
    Serial.println("Cola");
    while(buttonStateCola==LOW);  
    ok=1; 
  } 
  if(buttonStateFanta !=LOW){
   buttonMain=1;
   Serial.println("fanta");
   while(buttonStateFanta==LOW);
   ok=1; 
  }
  if(buttonStateOk != LOW)
  {
    buttonOk=3;
    Serial.println("OK");
    while(buttonStateOk==0);
    ok=1; 
  }
  switch(buttonMain){
   case 0: Serial.println("Cola"); break;
   case   1: Serial.println("Fanta"); break;
   case   3: Serial.println("Ok"); break;
  }
  }
}

void print(char *data){
 
  Serial2.print(data);
 
}
 
 
 
void clearScreen(){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x00));
 
}
 
 
 
void demo(){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x04)); 
 
}
 
 
 
void toggleSplashScreen(){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x13)); 
 
}
 
 
 
void setBackgroundBrightness(byte value){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x02));
 
  Serial2.write(byte(value));
 
}
 
 
 
void setBaudRate(long value){
 
  // Get the internal reference for this baud rate
 
  char *ref = " ";
 
  if(value == 4800) 
 
    ref = "1";
 
  else if(value == 9600)
 
    ref = "2";
 
  else if(value == 19200)
 
    ref = "3";
 
  else if(value == 38400)
 
    ref = "4";
 
  else if(value == 57600)
 
    ref = "5";
 
  else if(value == 115200)
 
    ref = "6";
 
  else
 
    return;
 
 
 
  // Since it often rolls back to 115200, try setting it via 115200 first
 
  Serial2.begin(115200);
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x07));
 
  Serial2.print(ref);
 
 
 
  // Now change the serial port to the desired rate, and set it again.
 
  Serial2.begin(value);
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x07));
 
  Serial2.print(ref);
 
}
 
 
 
void setX(byte value){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x18));
 
  Serial2.write(byte(value));
 
}
 
 
 
void setY(byte value){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x19));
 
  Serial2.write(byte(value));
 
}
 
 
 
void setPixel(byte state){
 
  Serial2.write(byte(0x50));
 
  Serial2.write(byte(0x40));
 
  Serial2.write(byte(state));
 
}
 
 
 
void drawLine(byte startX, byte startY, byte endX, byte endY, byte state){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x0C));
 
  Serial2.write(byte(startX));
 
  Serial2.write(byte(startY));
 
  Serial2.write(byte(endX));
 
  Serial2.write(byte(endY));
 
  Serial2.write(byte(state));
 
}
 
 
 
void drawCircle(byte startX, byte startY, byte radius, byte state){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x03));
 
  Serial2.write(byte(startX));
 
  Serial2.write(byte(startY));
 
  Serial2.write(byte(radius));
 
  Serial2.write(byte(state));
 
}
 
 
 
void drawBox(byte topLeftX, byte topLeftY, byte bottomRightX, byte bottomRightY, byte state){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x0F));
 
  Serial2.write(byte(topLeftX));
 
  Serial2.write(byte(topLeftY));
 
  Serial2.write(byte(bottomRightX));
 
  Serial2.write(byte(bottomRightY));
 
  Serial2.write(byte(state));
 
}
 
 
 
void eraseBox(byte topLeftX, byte topLeftY, byte bottomRightX, byte bottomRightY, byte state){
 
  Serial2.write(byte(0x7C));
 
  Serial2.write(byte(0x05));
 
  Serial2.write(byte(topLeftX));
 
  Serial2.write(byte(topLeftY));
 
  Serial2.write(byte(bottomRightX));
 
  Serial2.write(byte(bottomRightY));
 
  Serial2.write(byte(state));
 
}