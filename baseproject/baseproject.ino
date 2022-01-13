// flanc montant
class PositivEdge {
  private :
    boolean memPrevState;
    boolean out;
  public :
    PositivEdge(boolean condition);                      //constructor
    boolean eval(boolean condition);
    boolean get_out();
};
PositivEdge::PositivEdge(boolean condition) {
  this->memPrevState = condition;
}
boolean PositivEdge::eval(boolean condition) { //update positiv edge state must be done ONLY ONCE by loop cycle
  out = condition && !memPrevState;
  memPrevState = condition;
  return out;
}
boolean PositivEdge::get_out() {  //use get_out() to know positiv edge state (use more than once by cycle is possible)
  return this < - out;
} // fin flanc montant

class OnDelayTimer {

  private :
    unsigned long presetTime = 1000;
    unsigned long memStartTimer = 0;            //memory top timer activation
    unsigned long elpasedTime = 0;             //elapsed time from start timer activation
    boolean memStartActivation;                //for positive edge detection of the activation condition
    boolean outTimer;                          //timer's out : like normally open timer switch
  public :
    OnDelayTimer(unsigned long _presetTime);   //constructor
    boolean updtTimer(boolean activation);      //return tempo done must be executed on each program scan
    unsigned long get_elapsedTime();           //return
    set_presetTime(unsigned long _presetTime); //change defaut preset assigned when instance created
    boolean get_outTimer();

};//end class OnDelayTimer
//constructor
OnDelayTimer::OnDelayTimer(unsigned long presetTime) {
  this -> presetTime = presetTime;
}
boolean OnDelayTimer::updtTimer(boolean activation) {
  if (!activation) {
    elpasedTime = 0;
    memStartActivation = false;
    outTimer = false;
    return false;
  } else {

    if (!memStartActivation) {
      memStartTimer = millis();
      memStartActivation = true;
    }
    elpasedTime = millis() - memStartTimer;
    outTimer = elpasedTime >= this->presetTime; //update timer 's "switch"
    return  outTimer;

  }
}//end endTimer()
//constructor
boolean OnDelayTimer::get_outTimer() {

  return this->outTimer;
}
// ctrl-f => remplacer sortie out1 / out 2 / out3 / out4 / out5 / out6 / out7
// remplacer entrée no1 / no2 / no3 / no4 / no5 / no6  // nf1 / nf2 / nf3 / nf4

// pin de sortie 53->35

const int iPIN_out1 = 53; // marche
const int iPIN_out2 = 52; // warning
const int iPIN_out3 = 51; // stop
const int iPIN_out4 = 50;
const int iPIN_out5 = 49;
const int iPIN_out6 = 48;
const int iPIN_out7 = 47;
const int iPIN_out8 = 46;
const int iPIN_out9 = 45;
const int iPIN_out_10 = 44;
const int iPIN_out_11 = 43;
const int iPIN_out_12 = 42;
const int iPIN_out_13 = 41;
const int iPIN_out_14 = 40; // 1 led off
const int iPIN_out_15 = 39; // 1 led on
const int iPIN_out_16 = 38; // 2 led off
const int iPIN_out_17 = 37; // 2 led on
const int iPIN_out_18 = 36; // 3 led off
const int iPIN_out_19 = 35; // 3 led on

//pin entrée NO 15->26
const int iPIN_no1 = 15;
const int iPIN_no2 = 16;
const int iPIN_no3 = 17;
const int iPIN_no4 = 18;
const int iPIN_no5 = 19;
const int iPIN_no6 = 20;
const int iPIN_no7 = 21;
const int iPIN_no8 = 22;
const int iPIN_no9 = 23;

// pin entrée NF 27->34
const int iPIN_nf1 = 27;
const int iPIN_nf2 = 28;
const int iPIN_nf3 = 29;
const int iPIN_nf4 = 30;
const int iPIN_nf5 = 31;

boolean out1, out2, out3, out4, out5, out6, out7, out8, out9 = 0; //boolean sortie
boolean no1, no2, no3, no4, no5, no6, no7, no8, no9, nf1, nf2, nf3, nf4, nf5 = 0; //boolean entrée
//variable additionel


// nombre étapes et transistions
const unsigned int nbStepPr = X;
const unsigned int nbTransition = X;
boolean stepPr[nbStepPr];
boolean transition[nbTransition];

//déclaration débug
String strDebugLine;
int stp;// étape numéro x dans le debug

// déclaration des flanc montant à getter: PositivEdge nomDeVariable(nomDeVariable à évaluer)
PositivEdge posEdge_no1(no1);
// déclaration timer : OnDelayTimer nomDeVariable(temps en milliseconde);
OnDelayTimer timerstepPrX(3000);

void setup() {
  Serial.begin(9600); // déclaration moniteur série
  // sortie
  pinMode(iPIN_out1, OUTPUT);
  pinMode(iPIN_out2, OUTPUT);
  pinMode(iPIN_out3, OUTPUT);
  pinMode(iPIN_out4, OUTPUT);
  pinMode(iPIN_out5, OUTPUT);
  pinMode(iPIN_out6, OUTPUT);
  pinMode(iPIN_out7, OUTPUT);
  pinMode(iPIN_out8, OUTPUT);
  pinMode(iPIN_out9, OUTPUT);
  //entrée
  pinMode(iPIN_no1, INPUT);
  pinMode(iPIN_no2, INPUT);
  pinMode(iPIN_no3, INPUT);
  pinMode(iPIN_no4, INPUT);
  pinMode(iPIN_no5, INPUT);
  pinMode(iPIN_no6, INPUT);
  pinMode(iPIN_no7, INPUT);
  pinMode(iPIN_no8, INPUT);
  pinMode(iPIN_no9, INPUT);

  pinMode(iPIN_nf1, INPUT);
  pinMode(iPIN_nf2, INPUT);
  pinMode(iPIN_nf3, INPUT);
  pinMode(iPIN_nf4, INPUT);
  pinMode(iPIN_nf5, INPUT);

  stepPr[0] = true; // début stepPr
}

void loop() {
  //lecture entrée
  no1 = digitalRead (iPIN_no1);
  no2 = digitalRead (iPIN_no2);
  no3 = digitalRead (iPIN_no3);
  no4 = digitalRead (iPIN_no4);
  no5 = digitalRead (iPIN_no5);
  no6 = digitalRead (iPIN_no6);
  no7 = digitalRead (iPIN_no7);
  no8 = digitalRead (iPIN_no8);
  no9 = digitalRead (iPIN_no9);
  nf1 = digitalRead (iPIN_nf1);
  nf2 = digitalRead (iPIN_nf2);
  nf3 = digitalRead (iPIN_nf3);
  nf4 = digitalRead (iPIN_nf4);
  nf5 = digitalRead (iPIN_nf5);

  //evaluation flanc montant: posEdge_nomDeVariable.eval(nomDeVariable)
  posEdge_no1.eval(no1);

  // déclaration des transitions
  transition[0] = stepPr[0] && ;
  transition[1] = stepPr[1] && ;
  transition[2] = stepPr[2] && ;

  /* stepPr linéraire
  for (int i = 0; i < nbStepPr - 1; i++) {
    if (Transition[i]) {
      stepPr[1] = false;
      stepPr[i + 1] = true;
      break;
    }
  }
  if (Transition[nbStepPr - 1]) {
    stepPr[1] = false;
    stepPr[0] = true;
  }
  */

  /* stepPr non linéraire
    if (transition[0]) {
      stepPr[0] = false;
      stepPr[1] = true;
    }
    if (transition[1]) {
      stepPr[1] = false;
      stepPr[2] = true;
    }
  */

  //déclaration code


  //sortie activée par Step (sortie = stepPr[x])
  out1 = stepPr[x];
  out2 = ;
  out3 = ;
  out4 = ;
  out5 = ;
  out6 = ;
  out7 = ;
  out8 = ;
  out9 = ;

  // timer update (s'active à l'étape x)
  timerstepPrX.updtTimer(stepPr[x]);

  //association Sortie-Pin
  digitalWrite (iPIN_out1, out1);
  digitalWrite (iPIN_out2, out2);
  digitalWrite (iPIN_out3, out3);
  digitalWrite (iPIN_out4, out4);
  digitalWrite (iPIN_out5, out5);
  digitalWrite (iPIN_out6, out6);
  digitalWrite (iPIN_out7, out7);
  digitalWrite (iPIN_out8, out8);
  digitalWrite (iPIN_out9, out9);

  //debug: étapes active
  for (int i = 0; i < nbStepPr; i++) {
    if (stepPr[i]) {
      stp = i;
      break;
    }
  }
  /*
    for (int i = 0; i < X; i++) {
      if (stepbis[i]) {
        stpbis = i;
        break;
      }
    }for (int i = 0; i < X; i++) {
      if (steptris[i]) {
        stptri = i;
        break;
      }
    }
  */

  // sortie debug
  strDebugLine = "stepPr:" + String(stp, DEC) + /*" stepbis:" + String(stpbis, DEC) +" steptri:" + String(stptri, DEC) +*/
                 " no1:" + String(no1, DEC) + " no2:" + String(no2, DEC) + " no3:" + String(no3, DEC) + " no4:" + String(no4, DEC) + " no5:" + String(no5, DEC) +
                 " no6:" + String(no6, DEC) +  " no7:" + String(no7, DEC) +  " no8:" + String(no8, DEC) +  " no9:" + String(no9, DEC) +
                 " nf1:" + String(nf1, DEC) + " nf2:" + String(nf2, DEC) + " nf3:" + String(nf3, DEC) + " nf4:" + String(nf4, DEC) + " nf5:" + String(nf5, DEC) +
                 " out1:" + String(out1, DEC) + " out2:" + String(out2, DEC) + " out3:" + String(out3, DEC) + " out4:" + String(out4, DEC) + " out5:" + String(out5, DEC) +
                 " out6:" + String(out6, DEC) + " out7:" + String(out7, DEC) + " out8:" + String(out8, DEC) + " out9:" + String(out9, DEC);
  Serial.println(strDebugLine);
}
