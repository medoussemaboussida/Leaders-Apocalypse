char BYTE;
int buttonR = 6;
int buttonL = 7;
int droite =0;
int gauche =0;
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);//1 diode branchée à la pin 13 
  pinMode(11,OUTPUT); // une deuxième diode branchée à la pin 12
  Serial.begin(9600);
  digitalWrite(10,LOW);//initialiser les deux diodes à un état éteint au debut
  digitalWrite(11,LOW);
  pinMode(buttonR, INPUT);
  pinMode(buttonL, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
//traitement des deux boutons

  droite = digitalRead(buttonR);
  gauche = digitalRead(buttonL);
if(droite==0){
  Serial.write(1);
  Serial.println("deplacement droite "); 
  delay(500);
    }
else if(gauche==0){
  Serial.write(2);
  Serial.println("deplacement gauche"); 
  delay(500);
  }
else {
  Serial.write(0);
  Serial.println("pas deplacement");  
  delay(500);
  }
  // traitement des deux diodes led
if(Serial.available()>0)
{
  BYTE=Serial.read();// on va lire l'information venant du SDL (une collision par exemple)
  if(BYTE=='1') //(Si la collision du coté droite on reçoi 1 alors on allume la première diode qui est sur la pin 13)
  {
    digitalWrite(10,HIGH);// allumer une première diode 
    digitalWrite(11,LOW);// la deuxième est éteinte
    Serial.write(1);
    Serial.println("collision droite\n");// afficher un message sur le moniteur serie
  }
  else if(BYTE=='2')// (Si la collision coté gauche on reçoi 2 on allume la deuxième diode branchée sur la pin 12)
  {
    digitalWrite(11,HIGH);// allumer la deuxième diode
    digitalWrite(10,LOW);//la première diode est eteinte
    Serial.write(2);
    Serial.println("collision gauche\n");// afficher un message sur le moniteur serie
  }
else {// c'est à dire pas de collision on reçoi 0
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    Serial.write(0);
    Serial.println("pas de collision \n");
  }
}

}
