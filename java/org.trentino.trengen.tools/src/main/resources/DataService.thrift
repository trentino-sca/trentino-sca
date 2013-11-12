namespace java org.trentino.example
namespace cpp org.trentino.example

	enum Action {CREATEA, UPDATEA, DELETEA}
	
	enum Location {PRIVATEL, PUBLICL}

	struct UniqueID {
		1:optional i64  UnitID;
		2:optional i64  ComponentID;
		3:optional i64  PortID;
	}
	
    struct ObjectIdentifier {
		1:UniqueID ID;
		2:string type;
	}
	
    struct IdentifiedObject {

	}
	
	struct Motor  {
	    1:UniqueID ID;
		2:string Description;
		3:string Name;
		4:string Parameter1;
		5:string Parameter2;
	}
	
	struct Sensor {
		1:UniqueID ID;
		2:string Description;
		3:string Name;
		4:string Parameter1;
		5:string Parameter2;
	}
	
    
    exception ObjectNotFoundError {
		1:UniqueID id;
	}
	
	exception PersistanceError{
		1:string Reason;
	}
	
	exception WorkflowError{
		1:string Reason;
	}
	
	struct ObjectIdentifierList{
	1:list<ObjectIdentifier> values;
	}
	
	service DataService {
		UniqueID createUniqueID(),
		void dismissUniqueID(1:UniqueID id),
		void commitCreated(1:IdentifiedObject entity) throws (1:PersistanceError persistanceError),
		void commitUpdated(1:IdentifiedObject entity) throws (1:ObjectNotFoundError objectNotFoundError),
		void commitDeleted(1:UniqueID id) throws (1:PersistanceError persistanceError),
		void activate(1:IdentifiedObject entity) throws (1:PersistanceError persistanceError),
		string getTypeOfObject(1:UniqueID id) throws (1:ObjectNotFoundError objectNotFoundError),
		IdentifiedObject getObject(1:UniqueID id) throws (1:ObjectNotFoundError objectNotFoundError),
		ObjectIdentifierList getAllObjects(),
		string getTopic(1:string Name)
	}
	
	
	service SpecificDataService {
		/** create an Identified Object 
		@param typeId subtype of IdentifiedObject for created Object
		**/
		IdentifiedObject createEntity(1:string typeId); //::EMAP::IdentifiedObject , ::EMAP::Motor ... ///creates Identified Object of type typeId and stores it in memory
		
		/** store an IdentifiedObject locally
		@param entity IdentifiedObject to store
		**/
		void save(1:IdentifiedObject entity); /// stores the object locally;
		
		/** dismiss an IdentifiedObject locally. This must not succeed if the IdentifiedObject has been committed
		@param id ID of IdentifiedObject to dismiss
		**/
		void dismiss(1:UniqueID id) throws (1:WorkflowError workflowError);
		
		/** publish an IdentifiedObject to the DataService
		@param entity IdentifiedObject to publish
		**/
		void publish(1:IdentifiedObject entity); /// commits IdentifiedObject to the CDS
		
		/** revoke an IdentifiedObject from the DataService
		@param id id of the IdentifiedObject to revoke
		**/
		void revoke(1:UniqueID id);
	
		/** get a local IdentifiedObject
		@param id UniqueID of the IdentifiedObject to retrieve
		**/
		IdentifiedObject getObject(1:UniqueID id, 2:Location storageLocation) throws (1:ObjectNotFoundError objectNotFoundError);
	
		/** get a list of all Objects in form of an ObjectIdentifierList
		**/
		ObjectIdentifierList getAllObjects();
		
		/** get a list of all local Objects in form of an ObjectIdentifierList
		**/
		ObjectIdentifierList getObjects(1:Location storageLocation);
		
		/** get the name of the NotificationTopic **/
		string getTopic()
		
	}
	
	service ConfigurationNotification {
		void notificationTriggered(1:UniqueID ID, 2:Action what);
	}
	