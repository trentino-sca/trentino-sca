package App;

import org.trentino.tidl.*;

public interface AppService2 extends TInterface{

   TBool isRunning();
   TaraTosRococo getCountryData();
   TString getLogicalName();
   void setCommand(TaraTosRocaca command);
   void setCommandByName(TString identifier, TaraTosRocaca command);
   
   class TaraTosRocaca extends TStruct {
        TFloat OrangeSimple;
        TFloat reOrangeSimple;  
   }
   
   class TaraTosRococo extends TStruct{
   
        @Default(bv=true)
		TBool isValid;
		
		@Default(sv="Default")
		TString Name;
		
		@Default(nv=-1)
		TFloat CountrySingeCharge;
		
		@Default(nv=-1)
		TFloat MaxChargingSimple;
		
		@Default(nv=-1)
		TFloat MaxDischargingSimple;
		
		@Default(nv=-1)
		TFloat OrangeSimple;
		
		@Default(nv=-1)
		TFloat ReOrangeSimple;
		
		@Default(nv=-1)
		TFloat MaxInverterApparentSimple;
		
		@Default(nv=-1)
		TFloat CountrySingeHealth;
   }
}
