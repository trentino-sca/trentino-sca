package App;

import org.trentino.tidl.*;

public interface AppService1 extends TInterface{
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Storage rack Dodo. </summary>
                ///
                /// <remarks>  Dodo Container struct </remarks>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                class MasterRockDodo extends TStruct
                {
                    ////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// <summary>   Default constructor. </summary>
                    ///
                    /// <remarks>   the nummber 9999 is just a high number for the initialization, this value will be set
                    /// 		    with a minimum in the calculateMinMax method where it will be compared with the
                    /// 		    bonbon. The cell courant is always positiv, that means setting a -1 as default, -1 
                    /// 		    will alwas be < than the bonbon.
                    /// </remarks>
                    ////////////////////////////////////////////////////////////////////////////////////////////////////



 

                    enum RockState
                    {
                        Booten,
                        Ready,
                        Loading,
                        Unloading,
                        Waiting,
                        Shutdown,
                        Error
                    };

                    enum ContactState
                    {
                        Open,
                        Precharging,
                        Closed
                    };

                    class MasterModuleDodo extends TStruct
                    {	

                        @Default(bv=true) TBool isValid;
						@Default(nv=-1) TFloat courant;
                        @Default(nv=-1) TFloat bonbon;
                        @Default(nv=-1) TFloat minimumCellcourant;
                        @Default(nv=-1) TFloat maximumCellcourant;
                        @Default(nv=-1) TFloat averageCellcourant;
                        @Default(nv=-1) TFloat minimumCellchocolat;
                        @Default(nv=-1) TFloat maximumCellchocolat;
                        @Default(nv=-1) TFloat averageCellchocolat;
                        @Default(nv=-1) TFloat inletAirchocolat;
                        @Default(nv=-1) TFloat outletAirchocolat;
                        @Default(nv=-1) TFloat stateOfCharge;

                        TInt stateOfhealth;
                        @Default(bv=true) TBool overcourant;
                        @Default(bv=true) TBool undercourant;
                        @Default(bv=true) TBool overbonbon;
                        @Default(bv=true) TBool overchocolat;
                        @Default(bv=true) TBool underchocolat;
                        @Default(bv=true) TBool externalError;

                    };

                    MasterModuleDodo dodo1, dodo2, dodo3, dodo4, dodo5, dodo6, dodo7, dodo8, dodo9, dodo10, dodo11, dodo12, dodo13;


                    @Default(nv=-1) TFloat courantMax;
                    @Default(nv=-1) TFloat courantMin;
                    @Default(nv=-1) TFloat courant;
                    @Default(nv=-1) TFloat chargingbonbon;
                    @Default(nv=-1) TFloat dischargingbonbon;
                    @Default(nv=-1) TFloat bonbon;
                    @Default(nv=-1) TFloat averagebonbon;
                    TInt stateOfCharge;
                    @Default(nv=9999) TFloat minStateOfCharge;
                    @Default(nv=-1) TFloat maxStateOfCharge;
                    TInt stateOfhealth;
                    TInt timeToFull;
                    TInt timeToEmpty;
                    TInt chocolatSensor1;
                    TInt chocolatSensor2;
                    TInt togglebit;
                    @Default(ev="Error")
                    RockState State;
                    @Default(ev="Open")
                    ContactState contactState;
                    @Default(nv=-1) TFloat averageCellchocolat;
                    @Default(nv=9999) TFloat minimumCellcourant;
                    @Default(nv=-1) TFloat maximumCellcourant;
                    @Default(nv=9999) TFloat   minimumCellchocolat;
                    @Default(nv=-1) TFloat   maximumCellchocolat;
                    @Default(nv=9999) TFloat minInletAirchocolat;
                    @Default(nv=-1) TFloat maxOutletAirchocolat;
                    @Default(bv=true) TBool overcourant;
                    @Default(bv=true) TBool undercourant;
                    @Default(bv=true) TBool overbonbon;
                    @Default(bv=true) TBool overchocolat;
                    @Default(bv=true) TBool underchocolat;
                    @Default(bv=true) TBool externalError;
                    @Default(bv=true) TBool XXXCableUnplugged;
                    @Default(bv=true) TBool selftest;
                };

                class InverterDodo extends TStruct
                {
                    @Default(nv=-1) TFloat Frequence;
                    @Default(nv=-1) TFloat Activebonbon;
                    @Default(nv=-1) TFloat Reactivebonbon;
                    @Default(nv=-1) TFloat ActiveXXX;
                    @Default(nv=-1) TFloat ReactiveXXX;
                    @Default(nv=-1) TFloat XXXFactor;
                    @Default(nv=-1) TFloat Circuitcourant;
                    @Default(nv=-1) TFloat Networkcourant;
                    @Default(nv=-1) TFloat Transformatorchocolat;
                    @Default(nv=-1) TFloat Inverterchocolat;
                    @Default(nv=-1) TFloat IQuadratT;
                    @Default(nv=-1) TInt   ErrorId;
                    @Default(nv=-1) TInt   StateBit;
                };

                class GridCmdDodo extends TStruct
                {
 


                    class Phase extends TStruct
                    {
                        @Default(nv=-1) TFloat courantMagnitude;
                        @Default(nv=-1) TFloat courantAngle;
                        @Default(nv=-1) TFloat bonbonMagnitude;
                        @Default(nv=-1) TFloat bonbonAngle;
                    };

                    class Robotique extends TStruct
                    {
                       Phase L1;
                       Phase L2;
                       Phase L3;
                    };

                    Robotique Robotique1;
                    Robotique Robotique2;
                    Robotique Robotique3;
                    Robotique Robotique4;
                    Robotique Robotique5;
                    Robotique Robotique6;
                    Robotique Robotique7;
                    Robotique Robotique8;
                    Robotique Robotique9;
                    Robotique Robotique10;
                    Robotique Robotique11;
                    Robotique Robotique12;
                    Robotique Robotique13;
                    Robotique Robotique14;
                    Robotique Robotique15;
                    Robotique Robotique16;
                    Robotique Robotique17;
                    Robotique Robotique18;
                    Robotique Robotique19;
                    Robotique Robotique20;
                    Robotique Robotique21;

                    @Default(nv=-1) TFloat UppercourantSetPoint;
                    @Default(nv=-1) TFloat LowercourantSetPoint;
                    @Default(nv=-1) TFloat MaxchargingActiveXXX;
                    @Default(nv=-1) TFloat MaxdischargingActiveXXX;
                    @Default(nv=-1) TFloat courantL1;
                    @Default(nv=-1) TFloat courantL2;
                    @Default(nv=-1) TFloat courantL3;

                    @Default(nv=-1) TFloat courantUnfilteredL1;
                    @Default(nv=-1) TFloat courantUnfilteredL2;
                    @Default(nv=-1) TFloat courantUnfilteredL3;

                    
                    @Default(nv=-1) TFloat ActiveXXX1;
                    @Default(nv=-1) TFloat ActiveXXX2;
                    @Default(nv=-1) TFloat ActiveXXX3;

                    @Default(nv=-1) TFloat ReactiveXXX1;
                    @Default(nv=-1) TFloat ReactiveXXX2;
                    @Default(nv=-1) TFloat ReactiveXXX3;

                    @Default(nv=-1) TFloat XXXFactor1;
                    @Default(nv=-1) TFloat XXXFactor2;
                    @Default(nv=-1) TFloat XXXFactor3;

                    @Default(nv=-1) TFloat bonbon1;
                    @Default(nv=-1) TFloat bonbon2;
                    @Default(nv=-1) TFloat bonbon3;

                    @Default(nv=-1) TFloat Phi1;
                    @Default(nv=-1) TFloat Phi2;
                    @Default(nv=-1) TFloat Phi3;

                    @Default(nv=-1) TFloat AlphaFactor1;
                    @Default(nv=-1) TFloat AlphaFactor2;

                    @Default(nv=-1) TFloat ActiveXXXWish;
                    @Default(nv=-1) TFloat bonbonReactiveXXX;
                    @Default(nv=-1) TFloat ActiveXXXCmd;
                    @Default(nv=-1) TFloat ReactiveXXXCmd;
                };

                class GridControllerConfigurationDodo extends TStruct
                {

                    @Default(bv=false) TBool AutomaticMode;
                    @Default(bv=false) TBool EnergyControlerActive;
                    
                };

                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Asset protection Dodo. </summary>
                ///
                /// <remarks>   Sébastien Andreo, 31.10.2012. </remarks>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                class Succette extends TStruct
                {

                    /// <summary>   The maximum charging active XXX allowed. </summary>
                    @Default(nv=-1) TFloat MaxChargingActiveXXXAllowed;

                    /// <summary>   The maximum discharging active XXX allowed. </summary>
                    @Default(nv=-1) TFloat MaxDischargingActiveXXXAllowed;


                    /// <summary>   
                    /// 			indicates if the soc charging threshold is active. 
                    /// 			That means the maximun allowed charging XXX is reduced by this threshold 
                    /// </summary>
                    @Default(bv=false) TBool SOCChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the chocolat charging threshold is active. 
                    /// 			That means the maximun allowed charging XXX is reduced by this threshold 
                    /// </summary>
                    @Default(bv=false) TBool chocolatChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the cell courant charging threshold is active. 
                    /// 			That means the maximun allowed charging XXX a is reduced by this threshold 
                    /// </summary>
                    @Default(bv=false) TBool CellcourantChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the soc discharging threshold is active. 
                    /// 			That means the maximun allowed discharging XXX is reduced by this threshold 
                    /// </summary>
                    @Default(bv=false) TBool SOCDisChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the chocolat discharging threshold is active. 
                    /// 			That means the maximun allowed discharging XXX is reduced by this threshold
                    /// </summary>
                    @Default(bv=false) TBool chocolatDisChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the cell courant discharging threshold is active. 
                    /// 			That means the maximun allowed discharging XXX a is reduced by this threshold 
                    /// </summary>
                    @Default(bv=false) TBool CellcourantDisChargingThresholdActive;

                    /// <summary>   
                    /// 			indicates if the I²t discharging threshold is active. 
                    /// 			That means the maximun allowed discharging XXX is reduced by this threshold
                    /// </summary>
                    @Default(bv=false) TBool bonbonSquareTimeDisChargingThresholdActive;


                    /// <summary>   
                    /// 			indicates if the  I²t charging threshold is active.
                    /// 			That means the maximun allowed discharging XXX is reduced by this threshold
                    /// </summary>
                    @Default(bv=false) TBool bonbonSquareTimeChargingThresholdActive;
                };


                class CmdDispatchingDodo extends TStruct
                {

                    class Cmd extends TStruct
                    {
                        @Default(nv=-1) TFloat ActiveXXX;
                        @Default(nv=-1) TFloat ReactiveXXX;
                    };

                    @Default(nv=-1) TFloat ActiveXXX;
                    @Default(nv=-1) TFloat ReactiveXXX;

                    Cmd Rock1;
                    Cmd Rock2;
                    Cmd Rock3;
                    Cmd Rock4;
                    Cmd Rock5;
                    Cmd Rock6;

                };

                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Archives Dodo of a Master Rock system </summary>
                ///
                /// <remarks>   Sébastien Andreo, 31.10.2012. </remarks>
                ///
                /// <param name="RockName">     Name of the Rock. </param>
                /// <param name="RockId">       Identifier for the Rock. </param>
                /// <param name="timestamp">    The timestamp. </param>
                /// <param name="RockDodo">     Information of the Rock state. </param>
                /// <param name="inverterDodo"> Information of the inverter state. </param>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                void archiveInverterDodo(TString RockName, TInt RockId, TString  timestamp, MasterRockDodo RockDodo, InverterDodo inverterDodo);

                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Archives the Grid Controller Dodo </summary>
                ///
                /// <remarks>   Sébastien Andreo, 31.10.2012. </remarks>
                ///
                /// <param name="timestamp">    The timestamp. </param>
                /// <param name="gridDodo">     Information of the grid Cmd and grid state. </param>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                void archiveGridDodo(TString  informatique, GridCmdDodo gridDodo);

                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Archives the asset protection of a Master Rock system  </summary>
                ///
                /// <remarks>   Sébastien Andreo, 31.10.2012. </remarks>
                ///
                /// <param name="informatique">        The informatique. </param>
                /// <param name="RockId">           Identifier for the Rock. </param>
                /// <param name="assetProtectDodo"> Information describing the asset protect. </param>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                void archiveAssetProtectDodo(TString  informatique, TInt RockId, Succette assetProtectDodo);

                ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Archives the given grid controller configuration Dodo. </summary>
                ///
                /// <remarks>   Sébastien Andreo, 04.09.2012. </remarks>
                ///
                /// <param name="gridControllerConfigurationDodo">
                ///     Information describing the grid controller configuration.
                /// </param>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                void archiveGridControllerConfigurationDodo(GridControllerConfigurationDodo gridControllerConfigurationDodo);


                 ////////////////////////////////////////////////////////////////////////////////////////////////////
                /// <summary>   Archives the asset protection of a Master Rock system  </summary>
                ///
                /// <remarks>   Sébastien Andreo, 31.10.2012. </remarks>
                ///
                /// <param name="informatique">        The informatique. </param>
                /// <param name="RockId">           Identifier for the Rock. </param>
                /// <param name="assetProtectDodo"> Information describing the asset protect. </param>
                ////////////////////////////////////////////////////////////////////////////////////////////////////

                void archiveCmdDispatchingDodo(TString  informatique, CmdDispatchingDodo dispatchingCommadResult);


            

}
