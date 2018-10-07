
#define MAX_LOC   10  //numarul maxim de locuri de parcare
volatile int nr_locuri=0;  //vaiabila care reprezinta numarul de locuri disponibile
const int pin_in=2;   //pinul 2 la care este legat senzorul de distanta
const int pin_out=3;  //pinul 3 la care este legat senzorul de distanta
char nr_locuri_char[10]; //un string de 10 caractere in care punem valoare pe care vrem sa o afisam pe display
long debouncing_time = 15; //debounce time de 15 milisecunde
int flag=0; //flagul in functie de care stingem sau prindem cele 2 leduri
volatile unsigned long last_micros; // variabila in care retinem ultima intrerupere
void setup() {                
  Serial2.begin(115200); //setam bound rate pentru lcd
  pinMode(13, OUTPUT); //setam pinul 13 ca output
  pinMode(12, OUTPUT);//setam pinul 12 ca output
  pinMode(pin_in,INPUT); //setam pinul 2 ca input
  pinMode(pin_out,INPUT); //setam pinul 3 ca input
  attachInterrupt(digitalPinToInterrupt(pin_in), interrupt_in, RISING); // setam inrerupere la pinul 2 pe frontul crescator
  attachInterrupt(digitalPinToInterrupt(pin_out), interrupt_out, RISING); // setam inrerupere la pinul 3 pe frontul crescator
  digitalWrite(13, LOW); // stingem ledul 
  digitalWrite(12, LOW); // stingem ledul 
  clearScreen(); // facem clear la lcd
  delay(100);  //delay pentru a se realiza stergerea
  
}

void loop() {
  if(flag == 1) // daca flagul este 1 atunci aprindem ledul albastru si il stingem pe cel rosu, altfel cel rosu va fi aprins, iar albastru stins
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  else
  {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);    
  }
  itoa(nr_locuri,nr_locuri_char,10); // folosim functia de conversie din ascii in int a locurilor de parcare
  setX(30); //setam pozitia cursorului
  setY(25); //setam pozitia cursorului
  print(nr_locuri_char); // afisat locuri de parcare ocupate
  delay(100);  // delay petru scriere
}

void interrupt_in(){ //rutina de itnrerupere pentru masinile care intra
  if((millis() - last_micros) >= debouncing_time) { //folosim debounce, altfel variabila noastra nr_locuri se va incrementa de 3-4 ori pe toate periaoda tranzitiei de la 0 la 1
    isr_in(); //apelam functia in care incrementam locurile ocupate
    last_micros = millis(); // last_micros ia valoare timpului sistemelui de la momentul actual
  }
}

void isr_in(){
  static int cnt=0;
  if(nr_locuri < MAX_LOC){ // verificam daca numarul de locuri ocupate este mai mic decat numarul maxim
  nr_locuri++; //incrementam numarul de locuri
  cnt++;
   if(cnt==2)
  {
    cnt=0;
    nr_locuri=nr_locuri-1;
  }
  }
  
   if (nr_locuri == MAX_LOC) //daca numarul de locuri a ajung la numarul maxim, atunci setam falgul pe 1 pentru a aprinde ledul rosu
  {
    flag=1;
  }
}

void interrupt_out(){ //rutina de itnrerupere pentru masinile care ies din parcare
  if((millis() - last_micros) >= debouncing_time) { //folosim debounce, altfel variabila noastra nr_locuri se va incrementa de 3-4 ori pe toate periaoda tranzitiei de la 0 la 1
    isr_out(); //apelam functia in care decrementam locurile ocupate
    last_micros = millis(); // last_micros ia valoare timpului sistemelui de la momentul actual
  }
}

void isr_out(){
  static int cnt=0;
  flag=0; //setam flagul pe 0
  if(nr_locuri == MAX_LOC){  // daca numarul de locuri este cel maxim, atunci facem clearscreen pentru a nu ramane cifra zecimala 1
  clearScreen();
    delay(50);
  }
  if(nr_locuri > 0){ // daca numarul de locuri este mai mare decat 0 atunci il decrementam
  nr_locuri--;
  cnt++;
    if(cnt==2)
  {
    cnt=0;
    nr_locuri=nr_locuri+1;
  }
 }
}

void print(char *data){ //printam data pe interfata seriala 2
 
  Serial2.print(data);
 
}
 
void clearScreen(){ // functia de stergere a datelor de pe lcd
 
  Serial2.write(byte(0x7C)); // byte de comanda
 
  Serial2.write(byte(0x00)); // comanda 0 pentru stergere display 
 
}
 
 
void setX(byte value){ // functia cu care setam cursorul la pozitia care dorim
 
  Serial2.write(byte(0x7C)); // byte de comanda
 
  Serial2.write(byte(0x18)); // byte pentru a specifica cursorul X
 
  Serial2.write(byte(value)); //valoarea la care sa se pozitioneze X
 
}
 
 
 
void setY(byte value){ // functia cu care setam cursorul la pozitia care dorim
 
  Serial2.write(byte(0x7C)); // byte de comanda
 
  Serial2.write(byte(0x19)); // byte pentru a specifica cursorul Y
 
  Serial2.write(byte(value)); //valoarea la care sa se pozitioneze Y
 
}
 

