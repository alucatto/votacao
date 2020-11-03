/*
Este programa contém:
----------------------------------------------------------------
1) Leitura das entradas codificadas:
Para diminuir a quantidade de entradas utilizadas, foi implementada uma codificação
para detectar o botão acionado:

Tabela:
D1 D0 Informação/Botão
0  0  OK
0  1  Calor
1  0  Frio
1  1  Saúde 

Objetivo: Ler essas entradas codificadas
-------------------------------------------------------------------
2) Decodificação das entradas usadas pelas botoeiras:

Objetivo: Decodificar as entradas D0 e D1 e captar a informação de qual botão foi acionado.

Tabela:
D1 D0 Informação/Botão
0  0  OK
0  1  Calor
1  0  Frio
1  1  Saúde 
------------------------------------------------------------------
3) Contabilizar os votos por X tempo e apresentar resultados

-------------------------------------------------------------------
*/

/*---------------------
Variáveis globais
---------------------*/

/* Constantes de configuração (para calibração)*/
int intervalo = 10; //a cada X segundos -> intervalo de contabilização de votos

/*---------------------
 Parte 1 - Leitura das entradas*/
//Botoeira 1
int pinobot1L = 2; //Pino da entrada com o digito menos significativo (D0) da botoeira 1
int pinobot1H = 3; //Pino da entrada com o digito mais significativo (D1) da botoeira 1
bool latch1 = LOW; //Selo da botoeira 1
bool latch1Saude = LOW; //Selo do botão de Saúde da botoeira 1
bool bot1L = LOW; //Estado do dígito menos significativo (D0) da botoeira 1
bool bot1H = LOW; //Estado do digito mais significativo (D1) da botoeira 1

//Botoeira 2
int pinobot2L = 4; //Pino da entrada com o digito menos significativo (D0) da botoeira 2
int pinobot2H = 5; //Pino da entrada com o dígito mais significativo (D1) da botoeira 2
bool latch2 = LOW; //Selo da botoeira 2
bool latch2Saude = LOW; //Selo do botão de Saúde da botoeira 2
bool bot2L = LOW; //Estado do dígito menos significativo (D0) da botoeira 2
bool bot2H = LOW; //Estado do digito mais significativo (D1) da botoeira 2

//Botoeira 3
int pinobot3L = 6; //Pino da entrada com o digito menos significativo (D0) da botoeira 3
int pinobot3H = 7; //Pino da entrada com o dígito mais significativo (D1) da botoeira 3
bool latch3 = LOW; //Selo da botoeira 3
bool latch3Saude = LOW; //Selo do botão de Saúde da botoeira 3
bool bot3L = LOW; //Estado do dígito menos significativo (D0) da botoeira 3
bool bot3H = LOW; //Estado do digito mais significativo (D1) da botoeira 3

//Botoeira 4
int pinobot4L = 8; //Pino da entrada com o digito menos significativo (D0) da botoeira 4
int pinobot4H = 9; //Pino da entrada com o dígito mais significativo (D1) da botoeira 4
bool latch4 = LOW; //Selo da botoeira 4
bool latch4Saude = LOW; //Selo do botão de Saúde da botoeira 4
bool bot4L = LOW; //Estado do dígito menos significativo (D0) da botoeira 4
bool bot4H = LOW; //Estado do digito mais significativo (D1) da botoeira 4

//Botoeira 5
int pinobot5L = 10; //Pino da entrada com o digito menos significativo (D0) da botoeira 5
int pinobot5H = 11; //Pino da entrada com o dígito mais significativo (D1) da botoeira 5
bool latch5 = LOW; //Selo da botoeira 5
bool latch5Saude = LOW; //Selo do botão de Saúde da botoeira 5
bool bot5L = LOW; //Estado do dígito menos significativo (D0) da botoeira 5
bool bot5H = LOW; //Estado do digito mais significativo (D1) da botoeira 5

//Botoeira 6
int pinobot6L = 12; //Pino da entrada com o digito menos significativo (D0) da botoeira 6
int pinobot6H = 13; //Pino da entrada com o dígito mais significativo (D1) da botoeira 6
bool latch6 = LOW; //Selo da botoeira 6
bool latch6Saude = LOW; //Selo do botão de Saúde da botoeira 6
bool bot6L = LOW; //Estado do dígito menos significativo (D0) da botoeira 6
bool bot6H = LOW; //Estado do digito mais significativo (D1) da botoeira 6

//Botoeira 7
int pinobot7L = A0; //Pino da entrada com o digito menos significativo (D0) da botoeira 6
int pinobot7H = A1; //Pino da entrada com o dígito mais significativo (D1) da botoeira 6
bool latch7 = LOW; //Selo da botoeira 6
bool latch7Saude = LOW; //Selo do botão de Saúde da botoeira 6
bool bot7L = LOW; //Estado do dígito menos significativo (D0) da botoeira 6
bool bot7H = LOW; //Estado do digito mais significativo (D1) da botoeira 6

/*-------------------
 Parte 3 - Contabilizar os votos*/
int qtCalor = 0; //Contabilidade de votos de calor
int qtFrio = 0; //Contabilidade de votos de frio
int qtSaude = 0; //Contabilidade de votos de problemas de saúde
int qtOK = 0; //Contabilidade de pessoas confortáveis
int total = 0; //Quantidade total de pessoas;

float percentOK = 0; //Percentual de pessoas confortáveis

char rx_byte = 0; //Leitura da quantidade de botoeiras ativas pela porta serial

/*Configuração*/
void setup() {
  //Parte 1 - Leitura das entradas codificadas
  
  //Botoeira 1
  pinMode(pinobot1L,INPUT);
  pinMode(pinobot1H,INPUT);
  //Botoeira 2
  pinMode(pinobot2L,INPUT);
  pinMode(pinobot2H,INPUT);
  //Botoeira 3
  pinMode(pinobot3L,INPUT);
  pinMode(pinobot3H,INPUT);
  //Botoeira 4
  pinMode(pinobot4L,INPUT);
  pinMode(pinobot4H,INPUT);
  //Botoeira 5
  pinMode(pinobot5L,INPUT);
  pinMode(pinobot5H,INPUT);
  //Botoeira 6
  pinMode(pinobot6L,INPUT);
  pinMode(pinobot6H,INPUT);
  //Botoeira 7
  pinMode(pinobot7L,INPUT);
  pinMode(pinobot7H,INPUT);
  
  Serial.begin(9600);
}

//Função de leitura e contabilização
void contabiliza (unsigned long tempo) {
  //Variáveis locais
  unsigned long inicio = millis();

  //Le e contabiliza entradas por X tempo
  while(millis()-inicio < tempo){
    //Botoeira 1
    bot1L = digitalRead(pinobot1L);
    bot1H = digitalRead(pinobot1H);

    //Botoeira 2
    bot2L = digitalRead(pinobot2L);
    bot2H = digitalRead(pinobot2H);

    //Botoeira 3
    bot3L = digitalRead(pinobot3L);
    bot3H = digitalRead(pinobot3H);

    //Botoeira 4
    bot4L = digitalRead(pinobot4L);
    bot4H = digitalRead(pinobot4H);

    //Botoeira 5
    bot5L = digitalRead(pinobot5L);
    bot5H = digitalRead(pinobot5H);

    //Botoeira 6
    bot6L = digitalRead(pinobot6L);
    bot6H = digitalRead(pinobot6H);

    //Botoeira 7
    bot7L = digitalRead(pinobot7L);
    bot7H = digitalRead(pinobot7H);


    //Botoeira 1
    if(bot1L || bot1H){
      //11 -> Saude
      if ((bot1H && bot1L) && !latch1Saude){
        qtSaude++;
        Serial.println("Botoeira 1 -> Saude");
        //latch1 = HIGH;
        latch1Saude = HIGH;
      }
      else if ((!bot1H && bot1L) && !latch1 && !latch1Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 1 -> Calor");
        latch1 = HIGH;
      }
      else if ((bot1H && !bot1L) && !latch1 && !latch1Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 1 -> Frio");
        latch1 = HIGH;
      }
     }

     //Botoeira 2
     if(bot2L || bot2H){
      //11 -> Saude
      if ((bot2H && bot2L) && !latch2Saude){
        qtSaude++;
        Serial.println("Botoeira 2 -> Saude");
        //latch2 = HIGH;
        latch2Saude = HIGH;
      }
      else if ((!bot2H && bot2L) && !latch2 && !latch2Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 2 -> Calor");
        latch2 = HIGH;
      }
      else if ((bot2H && !bot2L) && !latch2 && !latch2Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 2 -> Frio");
        latch2 = HIGH;
      }
     }

     //Botoeira 3
     if(bot3L || bot3H){
      //11 -> Saude
      if ((bot3H && bot3L) && !latch3Saude){
        qtSaude++;
        Serial.println("Botoeira 3 -> Saude");
        //latch3 = HIGH;
        latch3Saude = HIGH;
      }
      else if ((!bot3H && bot3L) && !latch3 && !latch3Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 3 -> Calor");
        latch3 = HIGH;
      }
      else if ((bot3H && !bot3L) && !latch3 && !latch3Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 3 -> Frio");
        latch3 = HIGH;
      }
     }

     //Botoeira 4
     if(bot4L || bot4H){
      //11 -> Saude
      if ((bot4H && bot4L) && !latch4Saude){
        qtSaude++;
        Serial.println("Botoeira 4 -> Saude");
        //latch4 = HIGH;
        latch4Saude = HIGH;
      }
      else if ((!bot4H && bot4L) && !latch4 && !latch4Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 4 -> Calor");
        latch4 = HIGH;
      }
      else if ((bot4H && !bot4L) && !latch4 && !latch4Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 4 -> Frio");
        latch4 = HIGH;
      }
     }
     
     //Botoeira 5
     if(bot5L || bot5H){
      //11 -> Saude
      if ((bot5H && bot5L) && !latch5Saude){
        qtSaude++;
        Serial.println("Botoeira 5 -> Saude");
        //latch5 = HIGH;
        latch5Saude = HIGH;
      }
      else if ((!bot5H && bot5L) && !latch5 && !latch5Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 5 -> Calor");
        latch5 = HIGH;
      }
      else if ((bot5H && !bot5L) && !latch5 && !latch5Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 5 -> Frio");
        latch5 = HIGH;
      }
     }

     //Botoeira 6
     if(bot6L || bot6H){
      //11 -> Saude
      if ((bot6H && bot6L) && !latch6Saude){
        qtSaude++;
        Serial.println("Botoeira 6 -> Saude");
        //latch6 = HIGH;
        latch6Saude = HIGH;
      }
      else if ((!bot6H && bot6L) && !latch6 && !latch6Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 6 -> Calor");
        latch6 = HIGH;
      }
      else if ((bot6H && !bot6L) && !latch6 && !latch6Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 6 -> Frio");
        latch6 = HIGH;
      }
     }
     
     //Botoeira 7
     if(bot7L || bot7H){
      //11 -> Saude
      if ((bot7H && bot7L) && !latch7Saude){
        qtSaude++;
        Serial.println("Botoeira 7 -> Saude");
        //latch7 = HIGH;
        latch7Saude = HIGH;
      }
      else if ((!bot7H && bot7L) && !latch7 && !latch7Saude){
        //01 -> Calor
        qtCalor++;
        Serial.println("Botoeira 7 -> Calor");
        latch7 = HIGH;
      }
      else if ((bot7H && !bot7L) && !latch7 && !latch7Saude){
        //10 -> Frio
        qtFrio++;
        Serial.println("Botoeira 7 -> Frio");
        latch7 = HIGH;
      }
     }
  }
}

/*Programa contínuo*/
void loop() {
  qtSaude = 0;
  qtCalor = 0;
  qtFrio = 0;
  qtOK = 0;

  //Leitura do input da porta serial
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
  
    // check if a number was received
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      Serial.print("Number received: ");
      Serial.println(rx_byte);
    }
    else {
      Serial.println("Not a number.");
    }
  }
  
 
  contabiliza(intervalo*1000); //Le as entradas por X=intervalo segundos
  
  //Se não teve voto na botoeira 1, conta como OK
  if(!latch1){
    qtOK++;
  }
  
  //Se não teve voto na botoeira 2, conta como OK
  if(!latch2){
    qtOK++;
  }
  
  //Se não teve voto na botoeira 3, conta como OK
  if(!latch3){
    qtOK++;
  }

  //Se não teve voto na botoeira 4, conta como OK
  if(!latch4){
    qtOK++;
  }

  //Se não teve voto na botoeira 5, conta como OK
  if(!latch5){
    qtOK++;
  }

  //Se não teve voto na botoeira 6, conta como OK
  if(!latch6){
    qtOK++;
  }

  //Se não teve voto na botoeira 7, conta como OK
  if(!latch7){
    qtOK++;
  }
  total = 7; /*Total de botoeiras ativas (mais tarde será inserida uma lógica para
  descartar botoeiras que não tem pessoas*/

  //Apresenta resultados
  percentOK = (qtOK*100)/total;
  
  Serial.print("Qtd com Calor =");
  Serial.println(qtCalor);

  Serial.print("Qtd com Frio = ");
  Serial.println(qtFrio);

  Serial.print("Qtd com problemas de saúde = ");
  Serial.println(qtSaude);

  Serial.print("Qtd confortável = ");
  Serial.println(qtOK);

  Serial.print("Qtd total = ");
  Serial.println(total);

  Serial.print("Percentual de conforto = ");
  Serial.print(percentOK);
  Serial.println("%");

  //Libera os selos
  latch1 = LOW;
  latch1Saude = LOW;
  
  latch2 = LOW;
  latch2Saude = LOW;
  
  latch3 = LOW;
  latch3Saude = LOW;
  
  latch4 = LOW;
  latch4Saude = LOW;
  
  latch5 = LOW;
  latch5Saude = LOW;

  latch6 = LOW;
  latch6Saude = LOW;

  latch7 = LOW;
  latch7Saude = LOW;
}
