#include <SDHCI.h>
#include <Audio.h>

SDClass theSD;
AudioClass *theAudio;

File myFile;

bool ErrEnd = false;
float sensorValue = 0;              
float distance = 3;
int analog = 0;
int counter=0;
int counter2=201;
bool flag= false;

static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");
  
  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
    {
      ErrEnd = true;
   }
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

void setup()
{
  pinMode(2,INPUT);
  digitalWrite(2,HIGH);
  theAudio = AudioClass::getInstance();
  theAudio->begin(audio_attention_cb);
  puts("initialization Audio Library");
  theAudio->setRenderingClockMode(AS_CLKMODE_NORMAL);
  theAudio->setPlayerMode(AS_SETPLAYER_OUTPUTDEVICE_SPHP, AS_SP_DRV_MODE_LINEOUT);
  err_t err = theAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_MP3, "/mnt/sd0/BIN", AS_SAMPLINGRATE_AUTO, AS_CHANNEL_STEREO);

  if (err != AUDIOLIB_ECODE_OK)
    {
      printf("Player0 initialize error\n");
      exit(1);
    }
    
  myFile = theSD.open("Sound.mp3");

  if (!myFile)
    {
      printf("File open error\n");
      exit(1);
    }
    
  printf("Open! %d\n",myFile);

  err = theAudio->writeFrames(AudioClass::Player0, myFile);

  if ((err != AUDIOLIB_ECODE_OK) && (err != AUDIOLIB_ECODE_FILEEND))
    {
      printf("File Read Error! =%d\n",err);
      myFile.close();
      exit(1);
    }
    
  theAudio->setVolume(-160);
}

void loop()
{
  if (digitalRead(2)==LOW)
  {
    delay(10);
    if((digitalRead(2)==LOW))
    {
      puts("Calling Drone");
      delay(3000);
    }
  }
    

  if (distance<2 && counter2==201)
  {
    theAudio->startPlayer(AudioClass::Player0);
    puts("Play!"); 
    counter2=0;
  }
  if (counter2<200)
  {
    counter2++;
  }
  else if (counter2==200)
  {
  counter2++;
  theAudio->stopPlayer(AudioClass::Player0);
  myFile.close();
  myFile = theSD.open("Sound.mp3");
  puts("Reset Audio");
  }
  
  sensorValue += analogRead(A1);
  
  if(counter==9)
  {
   sensorValue/=10;  
   distance=((sensorValue*0.00976*3)/0.3858); 
   counter=0;
   sensorValue=0;
   puts(string2char(String(distance)));
  }
  
  counter++;
  analog=analogRead(A0);
  analog = map(analog, 0, 1023, -800, -100);
  theAudio->setVolume(analog);

  int err = theAudio->writeFrames(AudioClass::Player0, myFile);

  if (err == AUDIOLIB_ECODE_FILEEND)
    {
      printf("Main player File End!\n");
    }

  if (err)
    {
      printf("Main player error code: %d\n", err);
      goto stop_player;
    }

  if (ErrEnd)
    {
      printf("Error End\n");
      goto stop_player;
    }
  usleep(40000);
  return;

stop_player:
  sleep(1);
  theAudio->stopPlayer(AudioClass::Player0);
  myFile.close();
  exit(1);
}
