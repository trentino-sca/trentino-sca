package Trentino.Example;

import org.trentino.tidl.*;

public interface MilkTankControlBox extends TInterface{

 void setMaxTemperatureThreshold(TInt threshold);
 void setMinTemperatureThreshold(TInt threshold);
 void openAirVentilation(TUint percentage);
 void startCleaning();
 State getCleaningState();
 
 
 class State extends TStruct {
 TInt state;
 TString description;
 TUInt percentageFinished;
 }
}
