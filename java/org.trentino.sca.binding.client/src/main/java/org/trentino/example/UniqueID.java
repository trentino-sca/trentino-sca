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

public class UniqueID implements org.apache.thrift.TBase<UniqueID, UniqueID._Fields>, java.io.Serializable, Cloneable {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("UniqueID");

  private static final org.apache.thrift.protocol.TField UNIT_ID_FIELD_DESC = new org.apache.thrift.protocol.TField("UnitID", org.apache.thrift.protocol.TType.I64, (short)1);
  private static final org.apache.thrift.protocol.TField COMPONENT_ID_FIELD_DESC = new org.apache.thrift.protocol.TField("ComponentID", org.apache.thrift.protocol.TType.I64, (short)2);
  private static final org.apache.thrift.protocol.TField PORT_ID_FIELD_DESC = new org.apache.thrift.protocol.TField("PortID", org.apache.thrift.protocol.TType.I64, (short)3);

  private static final Map<Class<? extends IScheme>, SchemeFactory> schemes = new HashMap<Class<? extends IScheme>, SchemeFactory>();
  static {
    schemes.put(StandardScheme.class, new UniqueIDStandardSchemeFactory());
    schemes.put(TupleScheme.class, new UniqueIDTupleSchemeFactory());
  }

  public long UnitID; // optional
  public long ComponentID; // optional
  public long PortID; // optional

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    UNIT_ID((short)1, "UnitID"),
    COMPONENT_ID((short)2, "ComponentID"),
    PORT_ID((short)3, "PortID");

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
        case 1: // UNIT_ID
          return UNIT_ID;
        case 2: // COMPONENT_ID
          return COMPONENT_ID;
        case 3: // PORT_ID
          return PORT_ID;
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
  private static final int __UNITID_ISSET_ID = 0;
  private static final int __COMPONENTID_ISSET_ID = 1;
  private static final int __PORTID_ISSET_ID = 2;
  private BitSet __isset_bit_vector = new BitSet(3);
  private _Fields optionals[] = {_Fields.UNIT_ID,_Fields.COMPONENT_ID,_Fields.PORT_ID};
  public static final Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.UNIT_ID, new org.apache.thrift.meta_data.FieldMetaData("UnitID", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    tmpMap.put(_Fields.COMPONENT_ID, new org.apache.thrift.meta_data.FieldMetaData("ComponentID", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    tmpMap.put(_Fields.PORT_ID, new org.apache.thrift.meta_data.FieldMetaData("PortID", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    metaDataMap = Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(UniqueID.class, metaDataMap);
  }

  public UniqueID() {
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public UniqueID(UniqueID other) {
    __isset_bit_vector.clear();
    __isset_bit_vector.or(other.__isset_bit_vector);
    this.UnitID = other.UnitID;
    this.ComponentID = other.ComponentID;
    this.PortID = other.PortID;
  }

  public UniqueID deepCopy() {
    return new UniqueID(this);
  }

  @Override
  public void clear() {
    setUnitIDIsSet(false);
    this.UnitID = 0;
    setComponentIDIsSet(false);
    this.ComponentID = 0;
    setPortIDIsSet(false);
    this.PortID = 0;
  }

  public long getUnitID() {
    return this.UnitID;
  }

  public UniqueID setUnitID(long UnitID) {
    this.UnitID = UnitID;
    setUnitIDIsSet(true);
    return this;
  }

  public void unsetUnitID() {
    __isset_bit_vector.clear(__UNITID_ISSET_ID);
  }

  /** Returns true if field UnitID is set (has been assigned a value) and false otherwise */
  public boolean isSetUnitID() {
    return __isset_bit_vector.get(__UNITID_ISSET_ID);
  }

  public void setUnitIDIsSet(boolean value) {
    __isset_bit_vector.set(__UNITID_ISSET_ID, value);
  }

  public long getComponentID() {
    return this.ComponentID;
  }

  public UniqueID setComponentID(long ComponentID) {
    this.ComponentID = ComponentID;
    setComponentIDIsSet(true);
    return this;
  }

  public void unsetComponentID() {
    __isset_bit_vector.clear(__COMPONENTID_ISSET_ID);
  }

  /** Returns true if field ComponentID is set (has been assigned a value) and false otherwise */
  public boolean isSetComponentID() {
    return __isset_bit_vector.get(__COMPONENTID_ISSET_ID);
  }

  public void setComponentIDIsSet(boolean value) {
    __isset_bit_vector.set(__COMPONENTID_ISSET_ID, value);
  }

  public long getPortID() {
    return this.PortID;
  }

  public UniqueID setPortID(long PortID) {
    this.PortID = PortID;
    setPortIDIsSet(true);
    return this;
  }

  public void unsetPortID() {
    __isset_bit_vector.clear(__PORTID_ISSET_ID);
  }

  /** Returns true if field PortID is set (has been assigned a value) and false otherwise */
  public boolean isSetPortID() {
    return __isset_bit_vector.get(__PORTID_ISSET_ID);
  }

  public void setPortIDIsSet(boolean value) {
    __isset_bit_vector.set(__PORTID_ISSET_ID, value);
  }

  public void setFieldValue(_Fields field, Object value) {
    switch (field) {
    case UNIT_ID:
      if (value == null) {
        unsetUnitID();
      } else {
        setUnitID((Long)value);
      }
      break;

    case COMPONENT_ID:
      if (value == null) {
        unsetComponentID();
      } else {
        setComponentID((Long)value);
      }
      break;

    case PORT_ID:
      if (value == null) {
        unsetPortID();
      } else {
        setPortID((Long)value);
      }
      break;

    }
  }

  public Object getFieldValue(_Fields field) {
    switch (field) {
    case UNIT_ID:
      return Long.valueOf(getUnitID());

    case COMPONENT_ID:
      return Long.valueOf(getComponentID());

    case PORT_ID:
      return Long.valueOf(getPortID());

    }
    throw new IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new IllegalArgumentException();
    }

    switch (field) {
    case UNIT_ID:
      return isSetUnitID();
    case COMPONENT_ID:
      return isSetComponentID();
    case PORT_ID:
      return isSetPortID();
    }
    throw new IllegalStateException();
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof UniqueID)
      return this.equals((UniqueID)that);
    return false;
  }

  public boolean equals(UniqueID that) {
    if (that == null)
      return false;

    boolean this_present_UnitID = true && this.isSetUnitID();
    boolean that_present_UnitID = true && that.isSetUnitID();
    if (this_present_UnitID || that_present_UnitID) {
      if (!(this_present_UnitID && that_present_UnitID))
        return false;
      if (this.UnitID != that.UnitID)
        return false;
    }

    boolean this_present_ComponentID = true && this.isSetComponentID();
    boolean that_present_ComponentID = true && that.isSetComponentID();
    if (this_present_ComponentID || that_present_ComponentID) {
      if (!(this_present_ComponentID && that_present_ComponentID))
        return false;
      if (this.ComponentID != that.ComponentID)
        return false;
    }

    boolean this_present_PortID = true && this.isSetPortID();
    boolean that_present_PortID = true && that.isSetPortID();
    if (this_present_PortID || that_present_PortID) {
      if (!(this_present_PortID && that_present_PortID))
        return false;
      if (this.PortID != that.PortID)
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  public int compareTo(UniqueID other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;
    UniqueID typedOther = (UniqueID)other;

    lastComparison = Boolean.valueOf(isSetUnitID()).compareTo(typedOther.isSetUnitID());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetUnitID()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.UnitID, typedOther.UnitID);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetComponentID()).compareTo(typedOther.isSetComponentID());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetComponentID()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.ComponentID, typedOther.ComponentID);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetPortID()).compareTo(typedOther.isSetPortID());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetPortID()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.PortID, typedOther.PortID);
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
    StringBuilder sb = new StringBuilder("UniqueID(");
    boolean first = true;

    if (isSetUnitID()) {
      sb.append("UnitID:");
      sb.append(this.UnitID);
      first = false;
    }
    if (isSetComponentID()) {
      if (!first) sb.append(", ");
      sb.append("ComponentID:");
      sb.append(this.ComponentID);
      first = false;
    }
    if (isSetPortID()) {
      if (!first) sb.append(", ");
      sb.append("PortID:");
      sb.append(this.PortID);
      first = false;
    }
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
      // it doesn't seem like you should have to do this, but java serialization is wacky, and doesn't call the default constructor.
      __isset_bit_vector = new BitSet(1);
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class UniqueIDStandardSchemeFactory implements SchemeFactory {
    public UniqueIDStandardScheme getScheme() {
      return new UniqueIDStandardScheme();
    }
  }

  private static class UniqueIDStandardScheme extends StandardScheme<UniqueID> {

    public void read(org.apache.thrift.protocol.TProtocol iprot, UniqueID struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // UNIT_ID
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.UnitID = iprot.readI64();
              struct.setUnitIDIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // COMPONENT_ID
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.ComponentID = iprot.readI64();
              struct.setComponentIDIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // PORT_ID
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.PortID = iprot.readI64();
              struct.setPortIDIsSet(true);
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

    public void write(org.apache.thrift.protocol.TProtocol oprot, UniqueID struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.isSetUnitID()) {
        oprot.writeFieldBegin(UNIT_ID_FIELD_DESC);
        oprot.writeI64(struct.UnitID);
        oprot.writeFieldEnd();
      }
      if (struct.isSetComponentID()) {
        oprot.writeFieldBegin(COMPONENT_ID_FIELD_DESC);
        oprot.writeI64(struct.ComponentID);
        oprot.writeFieldEnd();
      }
      if (struct.isSetPortID()) {
        oprot.writeFieldBegin(PORT_ID_FIELD_DESC);
        oprot.writeI64(struct.PortID);
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class UniqueIDTupleSchemeFactory implements SchemeFactory {
    public UniqueIDTupleScheme getScheme() {
      return new UniqueIDTupleScheme();
    }
  }

  private static class UniqueIDTupleScheme extends TupleScheme<UniqueID> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, UniqueID struct) throws org.apache.thrift.TException {
      TTupleProtocol oprot = (TTupleProtocol) prot;
      BitSet optionals = new BitSet();
      if (struct.isSetUnitID()) {
        optionals.set(0);
      }
      if (struct.isSetComponentID()) {
        optionals.set(1);
      }
      if (struct.isSetPortID()) {
        optionals.set(2);
      }
      oprot.writeBitSet(optionals, 3);
      if (struct.isSetUnitID()) {
        oprot.writeI64(struct.UnitID);
      }
      if (struct.isSetComponentID()) {
        oprot.writeI64(struct.ComponentID);
      }
      if (struct.isSetPortID()) {
        oprot.writeI64(struct.PortID);
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, UniqueID struct) throws org.apache.thrift.TException {
      TTupleProtocol iprot = (TTupleProtocol) prot;
      BitSet incoming = iprot.readBitSet(3);
      if (incoming.get(0)) {
        struct.UnitID = iprot.readI64();
        struct.setUnitIDIsSet(true);
      }
      if (incoming.get(1)) {
        struct.ComponentID = iprot.readI64();
        struct.setComponentIDIsSet(true);
      }
      if (incoming.get(2)) {
        struct.PortID = iprot.readI64();
        struct.setPortIDIsSet(true);
      }
    }
  }

}

