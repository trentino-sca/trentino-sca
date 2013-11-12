/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.trentino.example;

import org.apache.thrift.scheme.IScheme;
import org.apache.thrift.scheme.SchemeFactory;
import org.apache.thrift.scheme.StandardScheme;

import org.apache.thrift.scheme.TupleScheme;
import org.apache.thrift.protocol.TTupleProtocol;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.EnumMap;
import java.util.Set;
import java.util.HashSet;
import java.util.EnumSet;
import java.util.Collections;
import java.util.BitSet;
import java.nio.ByteBuffer;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Motor implements org.apache.thrift.TBase<Motor, Motor._Fields>, java.io.Serializable, Cloneable {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("Motor");

  private static final org.apache.thrift.protocol.TField ID_FIELD_DESC = new org.apache.thrift.protocol.TField("ID", org.apache.thrift.protocol.TType.STRUCT, (short)1);
  private static final org.apache.thrift.protocol.TField DESCRIPTION_FIELD_DESC = new org.apache.thrift.protocol.TField("Description", org.apache.thrift.protocol.TType.STRING, (short)2);
  private static final org.apache.thrift.protocol.TField NAME_FIELD_DESC = new org.apache.thrift.protocol.TField("Name", org.apache.thrift.protocol.TType.STRING, (short)3);
  private static final org.apache.thrift.protocol.TField PARAMETER1_FIELD_DESC = new org.apache.thrift.protocol.TField("Parameter1", org.apache.thrift.protocol.TType.STRING, (short)4);
  private static final org.apache.thrift.protocol.TField PARAMETER2_FIELD_DESC = new org.apache.thrift.protocol.TField("Parameter2", org.apache.thrift.protocol.TType.STRING, (short)5);

  private static final Map<Class<? extends IScheme>, SchemeFactory> schemes = new HashMap<Class<? extends IScheme>, SchemeFactory>();
  static {
    schemes.put(StandardScheme.class, new MotorStandardSchemeFactory());
    schemes.put(TupleScheme.class, new MotorTupleSchemeFactory());
  }

  public UniqueID ID; // required
  public String Description; // required
  public String Name; // required
  public String Parameter1; // required
  public String Parameter2; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    ID((short)1, "ID"),
    DESCRIPTION((short)2, "Description"),
    NAME((short)3, "Name"),
    PARAMETER1((short)4, "Parameter1"),
    PARAMETER2((short)5, "Parameter2");

    private static final Map<String, _Fields> byName = new HashMap<String, _Fields>();

    static {
      for (_Fields field : EnumSet.allOf(_Fields.class)) {
        byName.put(field.getFieldName(), field);
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, or null if its not found.
     */
    public static _Fields findByThriftId(int fieldId) {
      switch(fieldId) {
        case 1: // ID
          return ID;
        case 2: // DESCRIPTION
          return DESCRIPTION;
        case 3: // NAME
          return NAME;
        case 4: // PARAMETER1
          return PARAMETER1;
        case 5: // PARAMETER2
          return PARAMETER2;
        default:
          return null;
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, throwing an exception
     * if it is not found.
     */
    public static _Fields findByThriftIdOrThrow(int fieldId) {
      _Fields fields = findByThriftId(fieldId);
      if (fields == null) throw new IllegalArgumentException("Field " + fieldId + " doesn't exist!");
      return fields;
    }

    /**
     * Find the _Fields constant that matches name, or null if its not found.
     */
    public static _Fields findByName(String name) {
      return byName.get(name);
    }

    private final short _thriftId;
    private final String _fieldName;

    _Fields(short thriftId, String fieldName) {
      _thriftId = thriftId;
      _fieldName = fieldName;
    }

    public short getThriftFieldId() {
      return _thriftId;
    }

    public String getFieldName() {
      return _fieldName;
    }
  }

  // isset id assignments
  public static final Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.ID, new org.apache.thrift.meta_data.FieldMetaData("ID", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.StructMetaData(org.apache.thrift.protocol.TType.STRUCT, UniqueID.class)));
    tmpMap.put(_Fields.DESCRIPTION, new org.apache.thrift.meta_data.FieldMetaData("Description", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.NAME, new org.apache.thrift.meta_data.FieldMetaData("Name", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.PARAMETER1, new org.apache.thrift.meta_data.FieldMetaData("Parameter1", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.PARAMETER2, new org.apache.thrift.meta_data.FieldMetaData("Parameter2", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    metaDataMap = Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(Motor.class, metaDataMap);
  }

  public Motor() {
  }

  public Motor(
    UniqueID ID,
    String Description,
    String Name,
    String Parameter1,
    String Parameter2)
  {
    this();
    this.ID = ID;
    this.Description = Description;
    this.Name = Name;
    this.Parameter1 = Parameter1;
    this.Parameter2 = Parameter2;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public Motor(Motor other) {
    if (other.isSetID()) {
      this.ID = new UniqueID(other.ID);
    }
    if (other.isSetDescription()) {
      this.Description = other.Description;
    }
    if (other.isSetName()) {
      this.Name = other.Name;
    }
    if (other.isSetParameter1()) {
      this.Parameter1 = other.Parameter1;
    }
    if (other.isSetParameter2()) {
      this.Parameter2 = other.Parameter2;
    }
  }

  public Motor deepCopy() {
    return new Motor(this);
  }

  @Override
  public void clear() {
    this.ID = null;
    this.Description = null;
    this.Name = null;
    this.Parameter1 = null;
    this.Parameter2 = null;
  }

  public UniqueID getID() {
    return this.ID;
  }

  public Motor setID(UniqueID ID) {
    this.ID = ID;
    return this;
  }

  public void unsetID() {
    this.ID = null;
  }

  /** Returns true if field ID is set (has been assigned a value) and false otherwise */
  public boolean isSetID() {
    return this.ID != null;
  }

  public void setIDIsSet(boolean value) {
    if (!value) {
      this.ID = null;
    }
  }

  public String getDescription() {
    return this.Description;
  }

  public Motor setDescription(String Description) {
    this.Description = Description;
    return this;
  }

  public void unsetDescription() {
    this.Description = null;
  }

  /** Returns true if field Description is set (has been assigned a value) and false otherwise */
  public boolean isSetDescription() {
    return this.Description != null;
  }

  public void setDescriptionIsSet(boolean value) {
    if (!value) {
      this.Description = null;
    }
  }

  public String getName() {
    return this.Name;
  }

  public Motor setName(String Name) {
    this.Name = Name;
    return this;
  }

  public void unsetName() {
    this.Name = null;
  }

  /** Returns true if field Name is set (has been assigned a value) and false otherwise */
  public boolean isSetName() {
    return this.Name != null;
  }

  public void setNameIsSet(boolean value) {
    if (!value) {
      this.Name = null;
    }
  }

  public String getParameter1() {
    return this.Parameter1;
  }

  public Motor setParameter1(String Parameter1) {
    this.Parameter1 = Parameter1;
    return this;
  }

  public void unsetParameter1() {
    this.Parameter1 = null;
  }

  /** Returns true if field Parameter1 is set (has been assigned a value) and false otherwise */
  public boolean isSetParameter1() {
    return this.Parameter1 != null;
  }

  public void setParameter1IsSet(boolean value) {
    if (!value) {
      this.Parameter1 = null;
    }
  }

  public String getParameter2() {
    return this.Parameter2;
  }

  public Motor setParameter2(String Parameter2) {
    this.Parameter2 = Parameter2;
    return this;
  }

  public void unsetParameter2() {
    this.Parameter2 = null;
  }

  /** Returns true if field Parameter2 is set (has been assigned a value) and false otherwise */
  public boolean isSetParameter2() {
    return this.Parameter2 != null;
  }

  public void setParameter2IsSet(boolean value) {
    if (!value) {
      this.Parameter2 = null;
    }
  }

  public void setFieldValue(_Fields field, Object value) {
    switch (field) {
    case ID:
      if (value == null) {
        unsetID();
      } else {
        setID((UniqueID)value);
      }
      break;

    case DESCRIPTION:
      if (value == null) {
        unsetDescription();
      } else {
        setDescription((String)value);
      }
      break;

    case NAME:
      if (value == null) {
        unsetName();
      } else {
        setName((String)value);
      }
      break;

    case PARAMETER1:
      if (value == null) {
        unsetParameter1();
      } else {
        setParameter1((String)value);
      }
      break;

    case PARAMETER2:
      if (value == null) {
        unsetParameter2();
      } else {
        setParameter2((String)value);
      }
      break;

    }
  }

  public Object getFieldValue(_Fields field) {
    switch (field) {
    case ID:
      return getID();

    case DESCRIPTION:
      return getDescription();

    case NAME:
      return getName();

    case PARAMETER1:
      return getParameter1();

    case PARAMETER2:
      return getParameter2();

    }
    throw new IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new IllegalArgumentException();
    }

    switch (field) {
    case ID:
      return isSetID();
    case DESCRIPTION:
      return isSetDescription();
    case NAME:
      return isSetName();
    case PARAMETER1:
      return isSetParameter1();
    case PARAMETER2:
      return isSetParameter2();
    }
    throw new IllegalStateException();
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof Motor)
      return this.equals((Motor)that);
    return false;
  }

  public boolean equals(Motor that) {
    if (that == null)
      return false;

    boolean this_present_ID = true && this.isSetID();
    boolean that_present_ID = true && that.isSetID();
    if (this_present_ID || that_present_ID) {
      if (!(this_present_ID && that_present_ID))
        return false;
      if (!this.ID.equals(that.ID))
        return false;
    }

    boolean this_present_Description = true && this.isSetDescription();
    boolean that_present_Description = true && that.isSetDescription();
    if (this_present_Description || that_present_Description) {
      if (!(this_present_Description && that_present_Description))
        return false;
      if (!this.Description.equals(that.Description))
        return false;
    }

    boolean this_present_Name = true && this.isSetName();
    boolean that_present_Name = true && that.isSetName();
    if (this_present_Name || that_present_Name) {
      if (!(this_present_Name && that_present_Name))
        return false;
      if (!this.Name.equals(that.Name))
        return false;
    }

    boolean this_present_Parameter1 = true && this.isSetParameter1();
    boolean that_present_Parameter1 = true && that.isSetParameter1();
    if (this_present_Parameter1 || that_present_Parameter1) {
      if (!(this_present_Parameter1 && that_present_Parameter1))
        return false;
      if (!this.Parameter1.equals(that.Parameter1))
        return false;
    }

    boolean this_present_Parameter2 = true && this.isSetParameter2();
    boolean that_present_Parameter2 = true && that.isSetParameter2();
    if (this_present_Parameter2 || that_present_Parameter2) {
      if (!(this_present_Parameter2 && that_present_Parameter2))
        return false;
      if (!this.Parameter2.equals(that.Parameter2))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  public int compareTo(Motor other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;
    Motor typedOther = (Motor)other;

    lastComparison = Boolean.valueOf(isSetID()).compareTo(typedOther.isSetID());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetID()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.ID, typedOther.ID);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetDescription()).compareTo(typedOther.isSetDescription());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetDescription()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.Description, typedOther.Description);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetName()).compareTo(typedOther.isSetName());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetName()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.Name, typedOther.Name);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetParameter1()).compareTo(typedOther.isSetParameter1());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetParameter1()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.Parameter1, typedOther.Parameter1);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetParameter2()).compareTo(typedOther.isSetParameter2());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetParameter2()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.Parameter2, typedOther.Parameter2);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    return 0;
  }

  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  public void read(org.apache.thrift.protocol.TProtocol iprot) throws org.apache.thrift.TException {
    schemes.get(iprot.getScheme()).getScheme().read(iprot, this);
  }

  public void write(org.apache.thrift.protocol.TProtocol oprot) throws org.apache.thrift.TException {
    schemes.get(oprot.getScheme()).getScheme().write(oprot, this);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("Motor(");
    boolean first = true;

    sb.append("ID:");
    if (this.ID == null) {
      sb.append("null");
    } else {
      sb.append(this.ID);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("Description:");
    if (this.Description == null) {
      sb.append("null");
    } else {
      sb.append(this.Description);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("Name:");
    if (this.Name == null) {
      sb.append("null");
    } else {
      sb.append(this.Name);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("Parameter1:");
    if (this.Parameter1 == null) {
      sb.append("null");
    } else {
      sb.append(this.Parameter1);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("Parameter2:");
    if (this.Parameter2 == null) {
      sb.append("null");
    } else {
      sb.append(this.Parameter2);
    }
    first = false;
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws org.apache.thrift.TException {
    // check for required fields
  }

  private void writeObject(java.io.ObjectOutputStream out) throws java.io.IOException {
    try {
      write(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(out)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
    try {
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class MotorStandardSchemeFactory implements SchemeFactory {
    public MotorStandardScheme getScheme() {
      return new MotorStandardScheme();
    }
  }

  private static class MotorStandardScheme extends StandardScheme<Motor> {

    public void read(org.apache.thrift.protocol.TProtocol iprot, Motor struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // ID
            if (schemeField.type == org.apache.thrift.protocol.TType.STRUCT) {
              struct.ID = new UniqueID();
              struct.ID.read(iprot);
              struct.setIDIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // DESCRIPTION
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.Description = iprot.readString();
              struct.setDescriptionIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // NAME
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.Name = iprot.readString();
              struct.setNameIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 4: // PARAMETER1
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.Parameter1 = iprot.readString();
              struct.setParameter1IsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 5: // PARAMETER2
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.Parameter2 = iprot.readString();
              struct.setParameter2IsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          default:
            org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
        }
        iprot.readFieldEnd();
      }
      iprot.readStructEnd();

      // check for required fields of primitive type, which can't be checked in the validate method
      struct.validate();
    }

    public void write(org.apache.thrift.protocol.TProtocol oprot, Motor struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.ID != null) {
        oprot.writeFieldBegin(ID_FIELD_DESC);
        struct.ID.write(oprot);
        oprot.writeFieldEnd();
      }
      if (struct.Description != null) {
        oprot.writeFieldBegin(DESCRIPTION_FIELD_DESC);
        oprot.writeString(struct.Description);
        oprot.writeFieldEnd();
      }
      if (struct.Name != null) {
        oprot.writeFieldBegin(NAME_FIELD_DESC);
        oprot.writeString(struct.Name);
        oprot.writeFieldEnd();
      }
      if (struct.Parameter1 != null) {
        oprot.writeFieldBegin(PARAMETER1_FIELD_DESC);
        oprot.writeString(struct.Parameter1);
        oprot.writeFieldEnd();
      }
      if (struct.Parameter2 != null) {
        oprot.writeFieldBegin(PARAMETER2_FIELD_DESC);
        oprot.writeString(struct.Parameter2);
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class MotorTupleSchemeFactory implements SchemeFactory {
    public MotorTupleScheme getScheme() {
      return new MotorTupleScheme();
    }
  }

  private static class MotorTupleScheme extends TupleScheme<Motor> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, Motor struct) throws org.apache.thrift.TException {
      TTupleProtocol oprot = (TTupleProtocol) prot;
      BitSet optionals = new BitSet();
      if (struct.isSetID()) {
        optionals.set(0);
      }
      if (struct.isSetDescription()) {
        optionals.set(1);
      }
      if (struct.isSetName()) {
        optionals.set(2);
      }
      if (struct.isSetParameter1()) {
        optionals.set(3);
      }
      if (struct.isSetParameter2()) {
        optionals.set(4);
      }
      oprot.writeBitSet(optionals, 5);
      if (struct.isSetID()) {
        struct.ID.write(oprot);
      }
      if (struct.isSetDescription()) {
        oprot.writeString(struct.Description);
      }
      if (struct.isSetName()) {
        oprot.writeString(struct.Name);
      }
      if (struct.isSetParameter1()) {
        oprot.writeString(struct.Parameter1);
      }
      if (struct.isSetParameter2()) {
        oprot.writeString(struct.Parameter2);
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, Motor struct) throws org.apache.thrift.TException {
      TTupleProtocol iprot = (TTupleProtocol) prot;
      BitSet incoming = iprot.readBitSet(5);
      if (incoming.get(0)) {
        struct.ID = new UniqueID();
        struct.ID.read(iprot);
        struct.setIDIsSet(true);
      }
      if (incoming.get(1)) {
        struct.Description = iprot.readString();
        struct.setDescriptionIsSet(true);
      }
      if (incoming.get(2)) {
        struct.Name = iprot.readString();
        struct.setNameIsSet(true);
      }
      if (incoming.get(3)) {
        struct.Parameter1 = iprot.readString();
        struct.setParameter1IsSet(true);
      }
      if (incoming.get(4)) {
        struct.Parameter2 = iprot.readString();
        struct.setParameter2IsSet(true);
      }
    }
  }

}
