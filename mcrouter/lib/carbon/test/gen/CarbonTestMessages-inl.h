/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */

namespace carbon {
namespace test {

template <class Writer>
void TestRequest::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(-1 /* field id */, asBase());
  writer.writeField(1 /* field id */, key());
  writer.writeField(2 /* field id */, testEnum());
  writer.writeField(3 /* field id */, testBool());
  writer.writeField(4 /* field id */, testChar());
  writer.writeField(5 /* field id */, testInt8());
  writer.writeField(6 /* field id */, testInt16());
  writer.writeField(7 /* field id */, testInt32());
  writer.writeField(8 /* field id */, testInt64());
  writer.writeField(9 /* field id */, testUInt8());
  writer.writeField(10 /* field id */, testUInt16());
  writer.writeField(11 /* field id */, testUInt32());
  writer.writeField(12 /* field id */, testUInt64());
  writer.writeField(13 /* field id */, testFloat());
  writer.writeField(14 /* field id */, testDouble());
  writer.writeField(15 /* field id */, testShortString());
  writer.writeField(16 /* field id */, testLongString());
  writer.writeField(17 /* field id */, testIobuf());
  writer.writeField(18 /* field id */, testStruct());
  writer.writeField(19 /* field id */, testList());
  writer.writeField(20 /* field id */, testOptionalString());
  writer.writeField(21 /* field id */, testOptionalIobuf());
  writer.writeField(22 /* field id */, testEnumVec());
  writer.writeField(23 /* field id */, testUnion());
  writer.writeField(24 /* field id */, testNestedVec());
  writer.writeField(25 /* field id */, testUMap());
  writer.writeField(26 /* field id */, testMap());
  writer.writeField(27 /* field id */, testComplexMap());
  writer.writeField(28 /* field id */, testUSet());
  writer.writeField(29 /* field id */, testSet());
  writer.writeField(30 /* field id */, testOptionalBool());
  writer.writeField(31 /* field id */, testOptionalVec());
  writer.writeField(32 /* field id */, testIOBufList());
  writer.writeField(33 /* field id */, testF14FastMap());
  writer.writeField(34 /* field id */, testF14NodeMap());
  writer.writeField(35 /* field id */, testF14ValueMap());
  writer.writeField(36 /* field id */, testF14VectorMap());
  writer.writeField(37 /* field id */, testF14FastSet());
  writer.writeField(38 /* field id */, testF14NodeSet());
  writer.writeField(39 /* field id */, testF14ValueSet());
  writer.writeField(40 /* field id */, testF14VectorSet());
  writer.writeField(41 /* field id */, testOptionalKeywordString());
  writer.writeField(42 /* field id */, testOptionalKeywordIobuf());
  writer.writeField(43 /* field id */, testOptionalKeywordBool());
  writer.writeField(44 /* field id */, testCastable());
  writer.writeField(100 /* field id */, testType());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestRequest::visitFields(V&& v) {
  if (v.enterMixin(1, "Base", _carbon_simplestruct_)) {
    this->_carbon_simplestruct_.visitFields(std::forward<V>(v));
  }
  if (!v.leaveMixin()) {
    return;
  }
  if (!v.visitField(1, "key", this->key())) {
    return;
  }
  if (!v.visitField(2, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(3, "testBool", this->testBool())) {
    return;
  }
  if (!v.visitField(4, "testChar", this->testChar())) {
    return;
  }
  if (!v.visitField(5, "testInt8", this->testInt8())) {
    return;
  }
  if (!v.visitField(6, "testInt16", this->testInt16())) {
    return;
  }
  if (!v.visitField(7, "testInt32", this->testInt32())) {
    return;
  }
  if (!v.visitField(8, "testInt64", this->testInt64())) {
    return;
  }
  if (!v.visitField(9, "testUInt8", this->testUInt8())) {
    return;
  }
  if (!v.visitField(10, "testUInt16", this->testUInt16())) {
    return;
  }
  if (!v.visitField(11, "testUInt32", this->testUInt32())) {
    return;
  }
  if (!v.visitField(12, "testUInt64", this->testUInt64())) {
    return;
  }
  if (!v.visitField(13, "testFloat", this->testFloat())) {
    return;
  }
  if (!v.visitField(14, "testDouble", this->testDouble())) {
    return;
  }
  if (!v.visitField(15, "testShortString", this->testShortString())) {
    return;
  }
  if (!v.visitField(16, "testLongString", this->testLongString())) {
    return;
  }
  if (!v.visitField(17, "testIobuf", this->testIobuf())) {
    return;
  }
  if (!v.visitField(18, "testStruct", this->testStruct())) {
    return;
  }
  if (!v.visitField(19, "testList", this->testList())) {
    return;
  }
  if (!v.visitField(20, "testOptionalString", this->testOptionalString())) {
    return;
  }
  if (!v.visitField(21, "testOptionalIobuf", this->testOptionalIobuf())) {
    return;
  }
  if (!v.visitField(22, "testEnumVec", this->testEnumVec())) {
    return;
  }
  if (!v.visitField(23, "testUnion", this->testUnion())) {
    return;
  }
  if (!v.visitField(24, "testNestedVec", this->testNestedVec())) {
    return;
  }
  if (!v.visitField(25, "testUMap", this->testUMap())) {
    return;
  }
  if (!v.visitField(26, "testMap", this->testMap())) {
    return;
  }
  if (!v.visitField(27, "testComplexMap", this->testComplexMap())) {
    return;
  }
  if (!v.visitField(28, "testUSet", this->testUSet())) {
    return;
  }
  if (!v.visitField(29, "testSet", this->testSet())) {
    return;
  }
  if (!v.visitField(30, "testOptionalBool", this->testOptionalBool())) {
    return;
  }
  if (!v.visitField(31, "testOptionalVec", this->testOptionalVec())) {
    return;
  }
  if (!v.visitField(32, "testIOBufList", this->testIOBufList())) {
    return;
  }
  if (!v.visitField(33, "testF14FastMap", this->testF14FastMap())) {
    return;
  }
  if (!v.visitField(34, "testF14NodeMap", this->testF14NodeMap())) {
    return;
  }
  if (!v.visitField(35, "testF14ValueMap", this->testF14ValueMap())) {
    return;
  }
  if (!v.visitField(36, "testF14VectorMap", this->testF14VectorMap())) {
    return;
  }
  if (!v.visitField(37, "testF14FastSet", this->testF14FastSet())) {
    return;
  }
  if (!v.visitField(38, "testF14NodeSet", this->testF14NodeSet())) {
    return;
  }
  if (!v.visitField(39, "testF14ValueSet", this->testF14ValueSet())) {
    return;
  }
  if (!v.visitField(40, "testF14VectorSet", this->testF14VectorSet())) {
    return;
  }
  if (!v.visitField(41, "testOptionalKeywordString", this->testOptionalKeywordString())) {
    return;
  }
  if (!v.visitField(42, "testOptionalKeywordIobuf", this->testOptionalKeywordIobuf())) {
    return;
  }
  if (!v.visitField(43, "testOptionalKeywordBool", this->testOptionalKeywordBool())) {
    return;
  }
  if (!v.visitField(44, "testCastable", this->testCastable())) {
    return;
  }
  if (!v.visitField(100, "testType", this->testType())) {
    return;
  }
}

template <class V>
void TestRequest::visitFields(V&& v) const {
  if (v.enterMixin(1, "Base", _carbon_simplestruct_)) {
    this->_carbon_simplestruct_.visitFields(std::forward<V>(v));
  }
  if (!v.leaveMixin()) {
    return;
  }
  if (!v.visitField(1, "key", this->key())) {
    return;
  }
  if (!v.visitField(2, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(3, "testBool", this->testBool())) {
    return;
  }
  if (!v.visitField(4, "testChar", this->testChar())) {
    return;
  }
  if (!v.visitField(5, "testInt8", this->testInt8())) {
    return;
  }
  if (!v.visitField(6, "testInt16", this->testInt16())) {
    return;
  }
  if (!v.visitField(7, "testInt32", this->testInt32())) {
    return;
  }
  if (!v.visitField(8, "testInt64", this->testInt64())) {
    return;
  }
  if (!v.visitField(9, "testUInt8", this->testUInt8())) {
    return;
  }
  if (!v.visitField(10, "testUInt16", this->testUInt16())) {
    return;
  }
  if (!v.visitField(11, "testUInt32", this->testUInt32())) {
    return;
  }
  if (!v.visitField(12, "testUInt64", this->testUInt64())) {
    return;
  }
  if (!v.visitField(13, "testFloat", this->testFloat())) {
    return;
  }
  if (!v.visitField(14, "testDouble", this->testDouble())) {
    return;
  }
  if (!v.visitField(15, "testShortString", this->testShortString())) {
    return;
  }
  if (!v.visitField(16, "testLongString", this->testLongString())) {
    return;
  }
  if (!v.visitField(17, "testIobuf", this->testIobuf())) {
    return;
  }
  if (!v.visitField(18, "testStruct", this->testStruct())) {
    return;
  }
  if (!v.visitField(19, "testList", this->testList())) {
    return;
  }
  if (!v.visitField(20, "testOptionalString", this->testOptionalString())) {
    return;
  }
  if (!v.visitField(21, "testOptionalIobuf", this->testOptionalIobuf())) {
    return;
  }
  if (!v.visitField(22, "testEnumVec", this->testEnumVec())) {
    return;
  }
  if (!v.visitField(23, "testUnion", this->testUnion())) {
    return;
  }
  if (!v.visitField(24, "testNestedVec", this->testNestedVec())) {
    return;
  }
  if (!v.visitField(25, "testUMap", this->testUMap())) {
    return;
  }
  if (!v.visitField(26, "testMap", this->testMap())) {
    return;
  }
  if (!v.visitField(27, "testComplexMap", this->testComplexMap())) {
    return;
  }
  if (!v.visitField(28, "testUSet", this->testUSet())) {
    return;
  }
  if (!v.visitField(29, "testSet", this->testSet())) {
    return;
  }
  if (!v.visitField(30, "testOptionalBool", this->testOptionalBool())) {
    return;
  }
  if (!v.visitField(31, "testOptionalVec", this->testOptionalVec())) {
    return;
  }
  if (!v.visitField(32, "testIOBufList", this->testIOBufList())) {
    return;
  }
  if (!v.visitField(33, "testF14FastMap", this->testF14FastMap())) {
    return;
  }
  if (!v.visitField(34, "testF14NodeMap", this->testF14NodeMap())) {
    return;
  }
  if (!v.visitField(35, "testF14ValueMap", this->testF14ValueMap())) {
    return;
  }
  if (!v.visitField(36, "testF14VectorMap", this->testF14VectorMap())) {
    return;
  }
  if (!v.visitField(37, "testF14FastSet", this->testF14FastSet())) {
    return;
  }
  if (!v.visitField(38, "testF14NodeSet", this->testF14NodeSet())) {
    return;
  }
  if (!v.visitField(39, "testF14ValueSet", this->testF14ValueSet())) {
    return;
  }
  if (!v.visitField(40, "testF14VectorSet", this->testF14VectorSet())) {
    return;
  }
  if (!v.visitField(41, "testOptionalKeywordString", this->testOptionalKeywordString())) {
    return;
  }
  if (!v.visitField(42, "testOptionalKeywordIobuf", this->testOptionalKeywordIobuf())) {
    return;
  }
  if (!v.visitField(43, "testOptionalKeywordBool", this->testOptionalKeywordBool())) {
    return;
  }
  if (!v.visitField(44, "testCastable", this->testCastable())) {
    return;
  }
  if (!v.visitField(100, "testType", this->testType())) {
    return;
  }
}

template <class Writer>
void TestReply::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, result());
  writer.writeField(2 /* field id */, valInt32());
  writer.writeField(3 /* field id */, valInt64());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestReply::visitFields(V&& v) {
  if (!v.visitField(1, "result", this->result())) {
    return;
  }
  if (!v.visitField(2, "valInt32", this->valInt32())) {
    return;
  }
  if (!v.visitField(3, "valInt64", this->valInt64())) {
    return;
  }
}

template <class V>
void TestReply::visitFields(V&& v) const {
  if (!v.visitField(1, "result", this->result())) {
    return;
  }
  if (!v.visitField(2, "valInt32", this->valInt32())) {
    return;
  }
  if (!v.visitField(3, "valInt64", this->valInt64())) {
    return;
  }
}

template <class Writer>
void TestRequestStringKey::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, key());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestRequestStringKey::visitFields(V&& v) {
  if (!v.visitField(1, "key", this->key())) {
    return;
  }
}

template <class V>
void TestRequestStringKey::visitFields(V&& v) const {
  if (!v.visitField(1, "key", this->key())) {
    return;
  }
}

template <class Writer>
void TestReplyStringKey::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, result());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestReplyStringKey::visitFields(V&& v) {
  if (!v.visitField(1, "result", this->result())) {
    return;
  }
}

template <class V>
void TestReplyStringKey::visitFields(V&& v) const {
  if (!v.visitField(1, "result", this->result())) {
    return;
  }
}

template <class Writer>
void TestOptionalBool::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, optionalBool());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestOptionalBool::visitFields(V&& v) {
  if (!v.visitField(1, "optionalBool", this->optionalBool())) {
    return;
  }
}

template <class V>
void TestOptionalBool::visitFields(V&& v) const {
  if (!v.visitField(1, "optionalBool", this->optionalBool())) {
    return;
  }
}

template <class Writer>
void TestOptionalUnion::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  switch (_which_) {
    case 1: {
      writer.writeFieldAlways(1 /* field id */, umember1());
      break;
    }
    case 2: {
      writer.writeFieldAlways(2 /* field id */, umember2());
      break;
    }
    case 3: {
      writer.writeFieldAlways(3 /* field id */, umember3());
      break;
    }
    default:
      break;
  }
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestOptionalUnion::visitFields(V&& v) {
  switch (_which_) {
    case 1:
      v.visitField(1, "umember1", umember1());
      break;
    case 2:
      v.visitField(2, "umember2", umember2());
      break;
    case 3:
      v.visitField(3, "umember3", umember3());
      break;
    default:
      break;
  }
}

template <class V>
void TestOptionalUnion::visitFields(V&& v) const {
  switch (_which_) {
    case 1:
      v.visitField(1, "umember1", umember1());
      break;
    case 2:
      v.visitField(2, "umember2", umember2());
      break;
    case 3:
      v.visitField(3, "umember3", umember3());
      break;
    default:
      break;
  }
}

template <class V>
void TestOptionalUnion::foreachMember(V&& v) {
  if (!v.template visitUnionMember<folly::Optional<int64_t>>("umember1", [this]() -> folly::Optional<int64_t>& {return this->emplace<1>();})) {
    return;
  }
  if (!v.template visitUnionMember<folly::Optional<bool>>("umember2", [this]() -> folly::Optional<bool>& {return this->emplace<2>();})) {
    return;
  }
  if (!v.template visitUnionMember<folly::Optional<std::string>>("umember3", [this]() -> folly::Optional<std::string>& {return this->emplace<3>();})) {
    return;
  }
}

template <class Writer>
void TestUnion::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  switch (_which_) {
    case 1: {
      writer.writeFieldAlways(1 /* field id */, a());
      break;
    }
    case 2: {
      writer.writeFieldAlways(2 /* field id */, b());
      break;
    }
    case 3: {
      writer.writeFieldAlways(3 /* field id */, c());
      break;
    }
    default:
      break;
  }
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestUnion::visitFields(V&& v) {
  switch (_which_) {
    case 1:
      v.visitField(1, "a", a());
      break;
    case 2:
      v.visitField(2, "b", b());
      break;
    case 3:
      v.visitField(3, "c", c());
      break;
    default:
      break;
  }
}

template <class V>
void TestUnion::visitFields(V&& v) const {
  switch (_which_) {
    case 1:
      v.visitField(1, "a", a());
      break;
    case 2:
      v.visitField(2, "b", b());
      break;
    case 3:
      v.visitField(3, "c", c());
      break;
    default:
      break;
  }
}

template <class V>
void TestUnion::foreachMember(V&& v) {
  if (!v.template visitUnionMember<uint64_t>("a", [this]() -> uint64_t& {return this->emplace<1>();})) {
    return;
  }
  if (!v.template visitUnionMember<uint32_t>("b", [this]() -> uint32_t& {return this->emplace<2>();})) {
    return;
  }
  if (!v.template visitUnionMember<uint16_t>("c", [this]() -> uint16_t& {return this->emplace<3>();})) {
    return;
  }
}

template <class Writer>
void TestF14Containers::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, fastMap());
  writer.writeField(2 /* field id */, nodeMap());
  writer.writeField(3 /* field id */, valueMap());
  writer.writeField(4 /* field id */, vectorMap());
  writer.writeField(5 /* field id */, fastSet());
  writer.writeField(6 /* field id */, nodeSet());
  writer.writeField(7 /* field id */, valueSet());
  writer.writeField(8 /* field id */, vectorSet());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestF14Containers::visitFields(V&& v) {
  if (!v.visitField(1, "fastMap", this->fastMap())) {
    return;
  }
  if (!v.visitField(2, "nodeMap", this->nodeMap())) {
    return;
  }
  if (!v.visitField(3, "valueMap", this->valueMap())) {
    return;
  }
  if (!v.visitField(4, "vectorMap", this->vectorMap())) {
    return;
  }
  if (!v.visitField(5, "fastSet", this->fastSet())) {
    return;
  }
  if (!v.visitField(6, "nodeSet", this->nodeSet())) {
    return;
  }
  if (!v.visitField(7, "valueSet", this->valueSet())) {
    return;
  }
  if (!v.visitField(8, "vectorSet", this->vectorSet())) {
    return;
  }
}

template <class V>
void TestF14Containers::visitFields(V&& v) const {
  if (!v.visitField(1, "fastMap", this->fastMap())) {
    return;
  }
  if (!v.visitField(2, "nodeMap", this->nodeMap())) {
    return;
  }
  if (!v.visitField(3, "valueMap", this->valueMap())) {
    return;
  }
  if (!v.visitField(4, "vectorMap", this->vectorMap())) {
    return;
  }
  if (!v.visitField(5, "fastSet", this->fastSet())) {
    return;
  }
  if (!v.visitField(6, "nodeSet", this->nodeSet())) {
    return;
  }
  if (!v.visitField(7, "valueSet", this->valueSet())) {
    return;
  }
  if (!v.visitField(8, "vectorSet", this->vectorSet())) {
    return;
  }
}

template <class Writer>
void TestStdContainers::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, fastMap());
  writer.writeField(2 /* field id */, nodeMap());
  writer.writeField(3 /* field id */, valueMap());
  writer.writeField(4 /* field id */, vectorMap());
  writer.writeField(5 /* field id */, fastSet());
  writer.writeField(6 /* field id */, nodeSet());
  writer.writeField(7 /* field id */, valueSet());
  writer.writeField(8 /* field id */, vectorSet());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void TestStdContainers::visitFields(V&& v) {
  if (!v.visitField(1, "fastMap", this->fastMap())) {
    return;
  }
  if (!v.visitField(2, "nodeMap", this->nodeMap())) {
    return;
  }
  if (!v.visitField(3, "valueMap", this->valueMap())) {
    return;
  }
  if (!v.visitField(4, "vectorMap", this->vectorMap())) {
    return;
  }
  if (!v.visitField(5, "fastSet", this->fastSet())) {
    return;
  }
  if (!v.visitField(6, "nodeSet", this->nodeSet())) {
    return;
  }
  if (!v.visitField(7, "valueSet", this->valueSet())) {
    return;
  }
  if (!v.visitField(8, "vectorSet", this->vectorSet())) {
    return;
  }
}

template <class V>
void TestStdContainers::visitFields(V&& v) const {
  if (!v.visitField(1, "fastMap", this->fastMap())) {
    return;
  }
  if (!v.visitField(2, "nodeMap", this->nodeMap())) {
    return;
  }
  if (!v.visitField(3, "valueMap", this->valueMap())) {
    return;
  }
  if (!v.visitField(4, "vectorMap", this->vectorMap())) {
    return;
  }
  if (!v.visitField(5, "fastSet", this->fastSet())) {
    return;
  }
  if (!v.visitField(6, "nodeSet", this->nodeSet())) {
    return;
  }
  if (!v.visitField(7, "valueSet", this->valueSet())) {
    return;
  }
  if (!v.visitField(8, "vectorSet", this->vectorSet())) {
    return;
  }
}

template <class Writer>
void StructWithEnumUInt64::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumUInt64::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumUInt64::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumUInt32::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumUInt32::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumUInt32::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumUInt16::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumUInt16::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumUInt16::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumUInt8::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumUInt8::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumUInt8::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumInt64::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumInt64::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumInt64::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumInt32::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumInt32::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumInt32::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumInt16::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumInt16::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumInt16::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithEnumInt8::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithEnumInt8::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class V>
void StructWithEnumInt8::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumUInt64::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumUInt64::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumUInt64::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumUInt32::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumUInt32::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumUInt32::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumUInt16::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumUInt16::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumUInt16::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumUInt8::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumUInt8::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumUInt8::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumInt64::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumInt64::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumInt64::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumInt32::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumInt32::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumInt32::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumInt16::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumInt16::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumInt16::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class Writer>
void StructWithOptionalEnumInt8::serialize(Writer&& writer) const {
  writer.writeStructBegin();
  writer.writeField(1 /* field id */, testEnum());
  writer.writeField(2 /* field id */, testEmptyEnum());
  writer.writeFieldStop();
  writer.writeStructEnd();
}

template <class V>
void StructWithOptionalEnumInt8::visitFields(V&& v) {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}

template <class V>
void StructWithOptionalEnumInt8::visitFields(V&& v) const {
  if (!v.visitField(1, "testEnum", this->testEnum())) {
    return;
  }
  if (!v.visitField(2, "testEmptyEnum", this->testEmptyEnum())) {
    return;
  }
}
} // namespace test
} // namespace carbon
