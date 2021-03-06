/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <sys/uio.h>

#include <cstring>
#include <string>

#include <gtest/gtest.h>
#include <string.h>

#include "mcrouter/lib/IOBufUtil.h"
#include "mcrouter/lib/carbon/CarbonProtocolWriter.h"
#include "mcrouter/lib/carbon/test/Util.h"
#include "mcrouter/lib/carbon/test/gen/CarbonTest.h"
#include "mcrouter/lib/carbon/test/gen/CarbonThriftTest.h"
#include "mcrouter/lib/carbon/test/gen/CompactTest.h"
#include "mcrouter/lib/network/MessageHelpers.h"

using namespace carbon::test::util;

using carbon::test::DummyThriftReply;
using carbon::test::DummyThriftRequest;
using carbon::test::SimpleStruct;
using carbon::test::TestOptionalUnion;
using carbon::test::TestReply;
using carbon::test::TestRequest;
using carbon::test::TestRequestStringKey;
using carbon::test::ThriftTestRequest;
using carbon::test2::util::SimpleEnum;
using facebook::memcache::coalesceAndGetRange;

namespace {

constexpr auto kKeyLiteral =
    "/region/cluster/abcdefghijklmnopqrstuvwxyz|#|afterhashstop";

template <class Key>
void checkKeyEmpty(const Key& key) {
  const auto emptyRoutingKeyHash = TestRequest().key_ref()->routingKeyHash();

  EXPECT_TRUE(key.empty());
  EXPECT_EQ(0, key.size());
  EXPECT_EQ("", key.fullKey());
  EXPECT_EQ("", key.routingKey());
  EXPECT_EQ("", key.routingPrefix());
  EXPECT_EQ("", key.keyWithoutRoute());
  EXPECT_FALSE(key.hasHashStop());
  EXPECT_EQ(emptyRoutingKeyHash, key.routingKeyHash());
}

template <class Key>
void checkKeyFilledProperly(const Key& key) {
  EXPECT_FALSE(key.empty());
  EXPECT_EQ(std::strlen(kKeyLiteral), key.size());
  EXPECT_EQ(kKeyLiteral, key.fullKey());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop", key.keyWithoutRoute());
  EXPECT_EQ("/region/cluster/", key.routingPrefix());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", key.routingKey());
  EXPECT_NE(0, key.routingKeyHash());
  EXPECT_TRUE(key.hasHashStop());
}

template <class T>
void checkStructWithEnum(
    const T& a,
    const T& b,
    bool equal,
    const std::string& msg) {
  if (equal) {
    EXPECT_EQ(*a.testEnum_ref(), *b.testEnum_ref()) << msg;
  } else {
    EXPECT_NE(*a.testEnum_ref(), *b.testEnum_ref()) << msg;
  }
}

template <class T>
void checkStructWithOptionalEnum(
    const T& a,
    const T& b,
    bool equal,
    const std::string& msg) {
  if (equal) {
    EXPECT_EQ(*a.testEnum_ref(), *b.testEnum_ref()) << msg;
  } else {
    EXPECT_NE(*a.testEnum_ref(), *b.testEnum_ref()) << msg;
  }
  EXPECT_FALSE(
      a.testEmptyEnum_ref().has_value() | b.testEmptyEnum_ref().has_value())
      << msg;
}

template <class T1, class T2>
void testEnumCompatibility(bool expectCompatible) {
  T1 struct1;
  struct1.testEnum() = decltype(struct1.testEnum_ref())::value_type::BBB;

  T2 struct2;
  struct2.testEnum() = decltype(struct2.testEnum_ref())::value_type::BBB;

  checkStructWithEnum(
      struct1,
      serializeAndDeserialize<T2, T1>(struct2),
      expectCompatible,
      folly::sformat("{} to {}", typeid(T2).name(), typeid(T1).name()));
  checkStructWithEnum(
      struct2,
      serializeAndDeserialize<T1, T2>(struct1),
      expectCompatible,
      folly::sformat("{} to {}", typeid(T1).name(), typeid(T2).name()));
}

template <class T1, class T2>
void testOptionalEnumCompatibility(bool expectCompatible) {
  T1 struct1;
  struct1.testEnum() = decltype(struct1.testEnum_ref())::value_type::BBB;

  T2 struct2;
  struct2.testEnum() = decltype(struct2.testEnum_ref())::value_type::BBB;

  checkStructWithOptionalEnum(
      struct1,
      serializeAndDeserialize<T2, T1>(struct2),
      expectCompatible,
      folly::sformat("{} to {}", typeid(T2).name(), typeid(T1).name()));
  checkStructWithOptionalEnum(
      struct2,
      serializeAndDeserialize<T1, T2>(struct1),
      expectCompatible,
      folly::sformat("{} to {}", typeid(T1).name(), typeid(T2).name()));
}

template <class Type>
class TestUnionBuilder {
 public:
  explicit TestUnionBuilder(const folly::StringPiece name, Type val)
      : fieldName_(name), fieldVal_(val) {}

  template <class T, class F>
  bool visitUnionMember(folly::StringPiece fieldName, F&& emplaceFn) {
    if (fieldName == fieldName_) {
      auto& itemRef = emplaceFn();
      itemRef = fieldVal_;
    }
    return true;
  }

 private:
  folly::StringPiece fieldName_;
  Type fieldVal_;
};
} // namespace

TEST(CarbonBasic, staticAsserts) {
  static_assert(!facebook::memcache::HasExptimeTrait<TestRequest>::value, "");
  static_assert(!facebook::memcache::HasFlagsTrait<TestRequest>::value, "");
  static_assert(facebook::memcache::HasKeyTrait<TestRequest>::value, "");
  static_assert(!facebook::memcache::HasValueTrait<TestRequest>::value, "");
  static_assert(TestRequest::typeId == 69, "");

  static_assert(!facebook::memcache::HasExptimeTrait<TestReply>::value, "");
  static_assert(!facebook::memcache::HasFlagsTrait<TestReply>::value, "");
  static_assert(!facebook::memcache::HasKeyTrait<TestReply>::value, "");
  static_assert(!facebook::memcache::HasValueTrait<TestReply>::value, "");
  static_assert(TestReply::typeId == 70, "");

  static_assert(carbon::IsCarbonStruct<TestRequest>::value, "");
  static_assert(!carbon::IsCarbonStruct<int>::value, "");
}

TEST(CarbonBasic, defaultConstructed) {
  TestRequest req;
  TestRequestStringKey req2;

  // key
  checkKeyEmpty(*req.key_ref());
  checkKeyEmpty(*req2.key_ref());

  // bool
  EXPECT_FALSE(req.testBool());
  // char
  EXPECT_EQ('\0', req.testChar());
  // enum member
  EXPECT_EQ(SimpleEnum::Twenty, req.testEnum());

  // int8_t
  EXPECT_EQ(0, req.testInt8());
  // int16_t
  EXPECT_EQ(0, req.testInt16());
  // int32_t
  EXPECT_EQ(0, req.testInt32());
  // int64_t
  EXPECT_EQ(0, req.testInt64());
  // uint8_t
  EXPECT_EQ(0, req.testUInt8());
  // uint16_t
  EXPECT_EQ(0, req.testUInt16());
  // uint32_t
  EXPECT_EQ(0, req.testUInt32());
  // uint64_t
  EXPECT_EQ(0, req.testUInt64());

  // float
  EXPECT_EQ(0.0, req.testFloat());
  // double
  EXPECT_EQ(0.0, req.testDouble());

  // string
  EXPECT_TRUE(req.testShortString().empty());
  EXPECT_TRUE(req.testLongString().empty());
  // IOBuf
  EXPECT_TRUE(req.testIobuf().empty());

  // Mixed-in member functions
  EXPECT_EQ(0, req.int32Member());
  EXPECT_TRUE(req.stringMember().empty());
  EXPECT_EQ(SimpleEnum::Twenty, req.enumMember());
  EXPECT_EQ(0, req.baseInt64Member());

  // Member struct
  EXPECT_EQ(0, req.testStruct().int32Member());
  EXPECT_TRUE(req.testStruct().stringMember().empty());
  EXPECT_EQ(SimpleEnum::Twenty, req.testStruct().enumMember());

  // List of strings
  EXPECT_TRUE(req.testList().empty());

  // Vector of enums
  EXPECT_TRUE(req.testEnumVec().empty());

  // Vector of vectors
  EXPECT_TRUE(req.testNestedVec().empty());

  // folly::Optional fields
  EXPECT_FALSE(req.testOptionalString());
  EXPECT_FALSE(req.testOptionalIobuf());

  // optional fields
  EXPECT_FALSE(req.testOptionalKeywordString());
  EXPECT_FALSE(req.testOptionalKeywordIobuf());
  EXPECT_FALSE(req.testOptionalKeywordBool());

  // optional fields field_ref
  EXPECT_FALSE(req.testOptionalKeywordString_ref());
  EXPECT_FALSE(req.testOptionalKeywordIobuf_ref());
  EXPECT_FALSE(req.testOptionalKeywordBool_ref());

  // Unordered map
  EXPECT_TRUE(req.testUMap().empty());

  // Ordered map
  EXPECT_TRUE(req.testMap().empty());

  // Complex map
  EXPECT_TRUE(req.testComplexMap().empty());

  // Unordered set
  EXPECT_TRUE(req.testUSet().empty());

  // Ordered set
  EXPECT_TRUE(req.testSet().empty());

  // User Type
  EXPECT_TRUE(carbon::SerializationTraits<carbon::test::UserType>::isEmpty(
      req.testType()));

  // fields generated for every request (will likely be removed in the future)
  EXPECT_EQ(0, facebook::memcache::getExptimeIfExist(req));
  EXPECT_EQ(0, facebook::memcache::getFlagsIfExist(req));
}

TEST(CarbonBasic, setAndGet) {
  TestRequest req(kKeyLiteral);
  TestRequestStringKey req2(kKeyLiteral);

  // key
  const auto reqKeyPiece = req.key_ref()->fullKey();
  EXPECT_EQ(kKeyLiteral, reqKeyPiece);
  EXPECT_EQ(kKeyLiteral, req.key_ref()->fullKey());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", req.key_ref()->routingKey().str());
  EXPECT_EQ("/region/cluster/", req.key_ref()->routingPrefix().str());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop",
      req.key_ref()->keyWithoutRoute().str());

  const auto reqKeyPiece2 = req2.key_ref()->fullKey();
  EXPECT_EQ(kKeyLiteral, reqKeyPiece2);
  EXPECT_EQ(kKeyLiteral, req2.key_ref()->fullKey());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", req2.key_ref()->routingKey().str());
  EXPECT_EQ("/region/cluster/", req2.key_ref()->routingPrefix().str());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop",
      req2.key_ref()->keyWithoutRoute().str());

  // bool
  req.testBool() = true;
  EXPECT_TRUE(req.testBool());
  // char
  req.testChar() = 'A';
  EXPECT_EQ('A', req.testChar());
  // enum member
  req.testEnum() = SimpleEnum::Negative;
  EXPECT_EQ(SimpleEnum::Negative, req.testEnum());
  EXPECT_EQ(-92233, static_cast<int64_t>(req.testEnum()));

  // int8_t
  req.testInt8() = kMinInt8;
  EXPECT_EQ(kMinInt8, req.testInt8());
  // int16_t
  req.testInt16() = kMinInt16;
  EXPECT_EQ(kMinInt16, req.testInt16());
  // int32_t
  req.testInt32() = kMinInt32;
  EXPECT_EQ(kMinInt32, req.testInt32());
  // int64_t
  req.testInt64() = kMinInt64;
  EXPECT_EQ(kMinInt64, req.testInt64());
  // uint8_t
  req.testUInt8() = kMaxUInt8;
  EXPECT_EQ(kMaxUInt8, req.testUInt8());
  // uint16_t
  req.testUInt16() = kMaxUInt16;
  EXPECT_EQ(kMaxUInt16, req.testUInt16());
  // uint32_t
  req.testUInt32() = kMaxUInt32;
  EXPECT_EQ(kMaxUInt32, req.testUInt32());
  // uint64_t
  req.testUInt64() = kMaxUInt64;
  EXPECT_EQ(kMaxUInt64, req.testUInt64());

  // float
  req.testFloat() = 12345.789f;
  EXPECT_FLOAT_EQ(12345.789f, req.testFloat());
  // double
  req.testDouble() = 12345.789;
  EXPECT_DOUBLE_EQ(12345.789, req.testDouble());

  // string
  req.testShortString() = kShortString.str();
  EXPECT_EQ(kShortString, req.testShortString());
  req.testLongString() = longString();
  EXPECT_EQ(longString(), req.testLongString());
  // IOBuf
  folly::IOBuf iobuf(folly::IOBuf::COPY_BUFFER, longString());
  req.testIobuf() = iobuf;
  EXPECT_EQ(
      coalesceAndGetRange(iobuf).str(),
      coalesceAndGetRange(req.testIobuf()).str());

  std::vector<std::string> strings = {
      "abcdefg", "xyz", kShortString.str(), longString()};
  req.testList() = strings;
  EXPECT_EQ(strings, req.testList());

  // Vector of enums
  std::vector<SimpleEnum> enums = {
      SimpleEnum::One,
      SimpleEnum::Zero,
      SimpleEnum::Twenty,
      SimpleEnum::Negative};
  req.testEnumVec() = enums;
  EXPECT_EQ(enums, req.testEnumVec());

  // Union
  req.testUnion().emplace<2>(true);
  bool b = req.testUnion().get<2>();
  EXPECT_TRUE(b);
  req.testUnion().emplace<1>(123);
  EXPECT_EQ(123, req.testUnion().get<1>());
  req.testUnion().emplace<3>("a");
  EXPECT_EQ("a", req.testUnion().get<3>());

  // Vector of vectors
  std::vector<std::vector<uint64_t>> vectors = {{1, 1, 1}, {2, 2}};
  req.testNestedVec() = vectors;
  EXPECT_EQ(vectors, req.testNestedVec());

  // folly::Optional fields
  const auto s = longString();
  req.testOptionalString() = s;
  EXPECT_EQ(s, *req.testOptionalString());
  req.testOptionalIobuf() = folly::IOBuf(folly::IOBuf::COPY_BUFFER, s);
  EXPECT_EQ(s, coalesceAndGetRange(req.testOptionalIobuf()));
  req.testOptionalBool() = false;
  EXPECT_EQ(false, *req.testOptionalBool());
  std::vector<folly::Optional<std::string>> ovec;
  ovec.emplace_back(folly::Optional<std::string>("hello"));
  req.testOptionalVec() = ovec;
  EXPECT_EQ(ovec, req.testOptionalVec());

  // optional fields
  const auto lstring = longString();
  req.testOptionalKeywordString() = lstring;
  EXPECT_EQ(lstring, *req.testOptionalKeywordString());
  req.testOptionalKeywordIobuf() =
      folly::IOBuf(folly::IOBuf::COPY_BUFFER, lstring);
  EXPECT_EQ(lstring, coalesceAndGetRange(req.testOptionalKeywordIobuf()));
  req.testOptionalKeywordBool() = false;
  EXPECT_EQ(false, *req.testOptionalKeywordBool());

  // optional fields ref api
  const auto lstringRef = longString();
  req.testOptionalKeywordString_ref() = lstringRef;
  EXPECT_EQ(lstringRef, *req.testOptionalKeywordString_ref());
  req.testOptionalKeywordIobuf_ref() =
      folly::IOBuf(folly::IOBuf::COPY_BUFFER, lstringRef);
  EXPECT_EQ(
      lstringRef, coalesceAndGetRange(req.testOptionalKeywordIobuf_ref()));
  req.testOptionalKeywordBool_ref() = false;
  EXPECT_EQ(false, *req.testOptionalKeywordBool_ref());

  // Unordered map
  std::unordered_map<std::string, std::string> stringmap;
  stringmap.insert({"key", "value"});
  req.testUMap() = stringmap;
  EXPECT_EQ(stringmap, req.testUMap());

  // Ordered map
  std::map<double, double> doublemap;
  doublemap.insert({1.08, 8.3});
  req.testMap() = doublemap;
  EXPECT_EQ(doublemap, req.testMap());

  // Complex map
  std::map<std::string, std::vector<uint16_t>> complexmap;
  complexmap.insert({"key", {1, 2}});
  req.testComplexMap() = complexmap;
  EXPECT_EQ(complexmap, req.testComplexMap());

  // Unordered set
  std::unordered_set<std::string> stringset;
  stringset.insert("hello");
  stringset.insert("world");
  req.testUSet() = stringset;
  EXPECT_EQ(stringset, req.testUSet());

  // Ordered set
  std::set<uint64_t> intset;
  intset.insert(1);
  intset.insert(2);
  req.testSet() = intset;
  EXPECT_EQ(intset, req.testSet());

  // User type
  carbon::test::UserType testType = {"blah", {1, 2, 3}};
  req.testType() = testType;
  EXPECT_EQ(testType.name, req.testType().name);
  EXPECT_EQ(testType.points, req.testType().points);
}

TEST(CarbonTest, serializeDeserialize) {
  // Fill in a request
  TestRequest outRequest("abcdefghijklmnopqrstuvwxyz");
  outRequest.testBool() = true;
  outRequest.testChar() = 'A';
  outRequest.testEnum() = SimpleEnum::Negative;
  outRequest.testInt8() = kMinInt8;
  outRequest.testInt16() = kMinInt16;
  outRequest.testInt32() = kMinInt32;
  outRequest.testInt64() = kMinInt64;
  outRequest.testUInt8() = kMaxUInt8;
  outRequest.testUInt16() = kMaxUInt16;
  outRequest.testUInt32() = kMaxUInt32;
  outRequest.testUInt64() = kMaxUInt64;
  outRequest.testFloat() = 12345.678f;
  outRequest.testDouble() = 12345.678;
  outRequest.testShortString() = kShortString.str();
  outRequest.testLongString() = longString();
  outRequest.testIobuf() =
      folly::IOBuf(folly::IOBuf::COPY_BUFFER, kShortString);
  // Member struct
  outRequest.testStruct().int32Member() = 12345;
  outRequest.testStruct().stringMember() = kShortString.str();
  outRequest.testStruct().enumMember() = SimpleEnum::One;
  // Mixed-in structure accessors
  outRequest.int32Member() = 12345;
  outRequest.stringMember() = kShortString.str();
  outRequest.enumMember() = SimpleEnum::One;
  outRequest.baseInt64Member() = 12345;
  // List of strings
  outRequest.testList() = {"abcdefg", "xyz", kShortString.str(), longString()};
  // Force one optional field to not be serialized on the wire
  EXPECT_FALSE(outRequest.testOptionalString().has_value());
  // Other optional field gets a value of zero length
  outRequest.testOptionalIobuf() = folly::IOBuf(folly::IOBuf::COPY_BUFFER, "");
  // Union
  outRequest.testUnion().emplace<2>(true);

  outRequest.testEnumVec().push_back(carbon::test2::util::SimpleEnum::Twenty);

  outRequest.testNestedVec().push_back({100, 2000});

  outRequest.testUMap().insert({"hello", "world"});
  outRequest.testMap().insert({1.08, 8.3});
  outRequest.testF14FastMap().insert({"hello", "F14FastMap"});
  outRequest.testF14NodeMap().insert({"hello", "F14NodeMap"});
  outRequest.testF14ValueMap().insert({"hello", "F14ValueMap"});
  outRequest.testF14VectorMap().insert({"hello", "F14VectorMap"});
  outRequest.testComplexMap().insert({"key", {1, 2}});

  outRequest.testUSet().insert("hello");
  outRequest.testSet().insert(123);
  outRequest.testF14FastSet().insert("hello F14FastSet");
  outRequest.testF14NodeSet().insert("hello F14NodeSet");
  outRequest.testF14ValueSet().insert("hello F14ValueSet");
  outRequest.testF14VectorSet().insert("hello F14VectorSet");

  outRequest.testType() = {"blah", {1, 2, 3}};

  outRequest.testOptionalBool() = false;

  outRequest.testOptionalVec().emplace_back(folly::Optional<std::string>(""));
  outRequest.testOptionalVec().emplace_back(folly::Optional<std::string>());
  outRequest.testOptionalVec().emplace_back(
      folly::Optional<std::string>("hello"));

  outRequest.testIOBufList().emplace_back(folly::IOBuf());

  const auto inRequest = serializeAndDeserialize(outRequest);
  expectEqTestRequest(outRequest, inRequest);
}

TEST(CarbonTest, unionZeroSerialization) {
  TestRequest outRequest;
  outRequest.testUnion().emplace<1>(0);
  auto inRequest = serializeAndDeserialize(outRequest);
  EXPECT_EQ(0, inRequest.testUnion().get<1>());

  outRequest.testUnion().emplace<3>("");
  inRequest = serializeAndDeserialize(outRequest);
  EXPECT_EQ("", inRequest.testUnion().get<3>());
}

TEST(CarbonTest, OptionalUnionSerialization) {
  carbon::test::TestOptionalUnion testOpt;
  testOpt.emplace<1>(1);
  auto inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER1, inOpt.which());
  EXPECT_EQ(testOpt.umember1().has_value(), inOpt.umember1().has_value());
  EXPECT_EQ(1, inOpt.umember1().value());

  testOpt.emplace<TestOptionalUnion::ValueType::UMEMBER1>(
      folly::Optional<int64_t>());
  inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER1, inOpt.which());
  EXPECT_EQ(testOpt.umember1().has_value(), inOpt.umember1().has_value());

  testOpt.emplace<TestOptionalUnion::ValueType::UMEMBER2>(false);
  inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER2, inOpt.which());
  EXPECT_EQ(testOpt.umember2().has_value(), inOpt.umember2().has_value());
  EXPECT_EQ(false, inOpt.umember2().value());

  testOpt.emplace<TestOptionalUnion::ValueType::UMEMBER2>(
      folly::Optional<bool>());
  inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER2, inOpt.which());
  EXPECT_EQ(testOpt.umember2().has_value(), inOpt.umember2().has_value());

  testOpt.emplace<TestOptionalUnion::ValueType::UMEMBER3>("test");
  inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER3, inOpt.which());
  EXPECT_EQ(testOpt.umember3().has_value(), inOpt.umember3().has_value());
  EXPECT_EQ("test", inOpt.umember3().value());

  testOpt.emplace<TestOptionalUnion::ValueType::UMEMBER3>(
      folly::Optional<std::string>());
  inOpt = serializeAndDeserialize(testOpt);
  ASSERT_EQ(TestOptionalUnion::ValueType::UMEMBER3, inOpt.which());
  EXPECT_EQ(testOpt.umember3().has_value(), inOpt.umember3().has_value());
}

TEST(CarbonTest, ForeachMemberTest) {
  carbon::test::TestUnion testUnion;
  TestUnionBuilder testUnionBuilder("a", 1);
  testUnion.foreachMember(testUnionBuilder);
  ASSERT_EQ(carbon::test::TestUnion::ValueType::A, testUnion.which());
  EXPECT_EQ(1, testUnion.a());
}

TEST(CarbonTest, OptionalBoolSerializationBytesWritten) {
  carbon::test::TestOptionalBool testOpt;
  size_t bytesWritten;
  folly::Optional<bool> opt;
  testOpt.optionalBool() = opt;
  auto inOpt = serializeAndDeserialize(testOpt, bytesWritten);
  EXPECT_EQ(testOpt.optionalBool(), inOpt.optionalBool());
  EXPECT_EQ(1, bytesWritten); // One byte written for FieldType::Stop

  bytesWritten = 0;
  testOpt.optionalBool() = true;
  inOpt = serializeAndDeserialize(testOpt, bytesWritten);
  EXPECT_EQ(testOpt.optionalBool(), inOpt.optionalBool());
  EXPECT_EQ(2, bytesWritten);

  bytesWritten = 0;
  testOpt.optionalBool() = false;
  inOpt = serializeAndDeserialize(testOpt, bytesWritten);
  EXPECT_EQ(testOpt.optionalBool(), inOpt.optionalBool());
  EXPECT_EQ(2, bytesWritten);
}

TEST(CarbonTest, mixins) {
  TestRequest request;
  EXPECT_EQ(0, request.asBase().asBaseStruct().baseInt64Member());

  request.asBase().asBaseStruct().baseInt64Member() = 12345;
  // Exercise the different ways we can access the mixed-in baseInt64Member
  EXPECT_EQ(12345, request.asBase().asBaseStruct().baseInt64Member());
  EXPECT_EQ(12345, request.asBase().baseInt64Member());
  EXPECT_EQ(12345, request.asBaseStruct().baseInt64Member());
  EXPECT_EQ(12345, request.baseInt64Member());
}

TEST(CarbonTest, veryLongString) {
  constexpr uint32_t kVeryLongStringSize = 1 << 30;
  std::string veryLongString(kVeryLongStringSize, 'x');

  TestRequest outRequest(longString());
  outRequest.testLongString() = std::move(veryLongString);
  const auto inRequest = serializeAndDeserialize(outRequest);
  expectEqTestRequest(outRequest, inRequest);
  EXPECT_EQ(kVeryLongStringSize, inRequest.testLongString().length());
}

TEST(CarbonTest, repeatStorageUsage) {
  std::string testStr(longString());

  carbon::CarbonQueueAppenderStorage storage;
  carbon::CarbonProtocolWriter writer(storage);

  TestRequest outRequest(longString());
  outRequest.testLongString() = std::move(testStr);

  for (int i = 0; i < 100; i++) {
    outRequest.serialize(writer);
    storage.reset();
  }
}

TEST(CarbonTest, veryLongIobuf) {
  constexpr uint32_t kVeryLongIobufSize = 1 << 30;
  folly::IOBuf veryLongIobuf(folly::IOBuf::CREATE, kVeryLongIobufSize);
  std::memset(veryLongIobuf.writableTail(), 'x', kVeryLongIobufSize);
  veryLongIobuf.append(kVeryLongIobufSize);

  TestRequest outRequest(longString());
  outRequest.testIobuf() = std::move(veryLongIobuf);
  const auto inRequest = serializeAndDeserialize(outRequest);
  expectEqTestRequest(outRequest, inRequest);
  EXPECT_EQ(kVeryLongIobufSize, inRequest.testIobuf().length());
}

TEST(CarbonTest, keysIobuf) {
  {
    TestRequest req;
    checkKeyEmpty(*req.key_ref());
  }
  {
    TestRequest req;

    const folly::IOBuf keyCopy(folly::IOBuf::CopyBufferOp(), kKeyLiteral);
    req.key_ref() = keyCopy;
    checkKeyFilledProperly(*req.key_ref());

    req.key_ref() = "";
    checkKeyEmpty(*req.key_ref());
  }
  {
    TestRequest req;
    checkKeyEmpty(*req.key_ref());

    req.key_ref() = folly::IOBuf(folly::IOBuf::CopyBufferOp(), kKeyLiteral);
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequest req(kKeyLiteral);
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequest req{folly::StringPiece(kKeyLiteral)};
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequest req(folly::IOBuf(folly::IOBuf::CopyBufferOp(), kKeyLiteral));
    checkKeyFilledProperly(*req.key_ref());
  }
}

TEST(CarbonTest, keysString) {
  {
    TestRequestStringKey req;
    checkKeyEmpty(*req.key_ref());
  }
  {
    TestRequestStringKey req;

    const std::string keyCopy(kKeyLiteral);
    req.key_ref() = keyCopy;
    checkKeyFilledProperly(*req.key_ref());

    req.key_ref() = "";
    checkKeyEmpty(*req.key_ref());
  }
  {
    TestRequestStringKey req;
    checkKeyEmpty(*req.key_ref());

    req.key_ref() = kKeyLiteral;
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequestStringKey req(kKeyLiteral);
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequest req{folly::StringPiece(kKeyLiteral)};
    checkKeyFilledProperly(*req.key_ref());
  }
  {
    TestRequest req{std::string(kKeyLiteral)};
    checkKeyFilledProperly(*req.key_ref());
  }
}

TEST(CarbonTest, unionWhich) {
  TestOptionalUnion un;

  EXPECT_EQ(TestOptionalUnion::ValueType::EMPTY, un.which());

  un.umember1() = 10;
  EXPECT_EQ(TestOptionalUnion::ValueType::UMEMBER1, un.which());

  un.emplace<TestOptionalUnion::ValueType::UMEMBER2>(true);
  EXPECT_EQ(TestOptionalUnion::ValueType::UMEMBER2, un.which());

  un.emplace<TestOptionalUnion::ValueType::UMEMBER3>("abc");
  EXPECT_EQ(TestOptionalUnion::ValueType::UMEMBER3, un.which());
}

TEST(CarbonTest, f14NodeMapToStdUnorderedMap) {
  carbon::test::TestF14Containers f14;
  f14.nodeMap().emplace("node", 1);
  f14.nodeMap().emplace("node2", 2);
  f14.fastMap().emplace("fast", 3);
  f14.valueMap().emplace("value", 4);
  f14.vectorMap().emplace("vector", 5);
  f14.nodeSet().emplace(1);
  f14.nodeSet().emplace(2);
  f14.fastSet().emplace(3);
  f14.valueSet().emplace(4);
  f14.vectorSet().emplace(5);
  auto std = carbon::test::util::serializeAndDeserialize<
      carbon::test::TestF14Containers,
      carbon::test::TestStdContainers>(f14);
  ASSERT_EQ(std.nodeMap().size(), 2);
  ASSERT_EQ(std.fastMap().size(), 1);
  ASSERT_EQ(std.valueMap().size(), 1);
  ASSERT_EQ(std.vectorMap().size(), 1);
  EXPECT_EQ(std.nodeMap().at("node"), 1);
  EXPECT_EQ(std.nodeMap().at("node2"), 2);
  EXPECT_EQ(std.fastMap().at("fast"), 3);
  EXPECT_EQ(std.valueMap().at("value"), 4);
  EXPECT_EQ(std.vectorMap().at("vector"), 5);

  ASSERT_EQ(std.nodeSet().size(), 2);
  ASSERT_EQ(std.fastSet().size(), 1);
  ASSERT_EQ(std.valueSet().size(), 1);
  ASSERT_EQ(std.vectorSet().size(), 1);
  EXPECT_FALSE(std.nodeSet().find(1) == std.nodeSet().end());
  EXPECT_FALSE(std.nodeSet().find(2) == std.nodeSet().end());
  EXPECT_FALSE(std.fastSet().find(3) == std.fastSet().end());
  EXPECT_FALSE(std.valueSet().find(4) == std.valueSet().end());
  EXPECT_FALSE(std.vectorSet().find(5) == std.vectorSet().end());
}

TEST(CarbonBasic, defaultConstructedFieldRefAPI) {
  TestRequest req;
  TestRequestStringKey req2;

  // key
  checkKeyEmpty(*req.key_ref());
  checkKeyEmpty(*req2.key_ref());

  // bool
  EXPECT_FALSE(*req.testBool_ref());
  // char
  EXPECT_EQ('\0', *req.testChar_ref());
  // enum member
  EXPECT_EQ(SimpleEnum::Twenty, *req.testEnum_ref());

  // int8_t
  EXPECT_EQ(0, *req.testInt8_ref());
  // int16_t
  EXPECT_EQ(0, *req.testInt16_ref());
  // int32_t
  EXPECT_EQ(0, *req.testInt32_ref());
  // int64_t
  EXPECT_EQ(0, *req.testInt64_ref());
  // uint8_t
  EXPECT_EQ(0, *req.testUInt8_ref());
  // uint16_t
  EXPECT_EQ(0, *req.testUInt16_ref());
  // uint32_t
  EXPECT_EQ(0, *req.testUInt32_ref());
  // uint64_t
  EXPECT_EQ(0, *req.testUInt64_ref());

  // float
  EXPECT_EQ(0.0, *req.testFloat_ref());
  // double
  EXPECT_EQ(0.0, *req.testDouble_ref());

  // string
  EXPECT_TRUE(req.testShortString_ref()->empty());
  EXPECT_TRUE(req.testLongString_ref()->empty());
  // IOBuf
  EXPECT_TRUE(req.testIobuf_ref()->empty());

  // List of strings
  EXPECT_TRUE(req.testList_ref()->empty());

  // Vector of enums
  EXPECT_TRUE(req.testEnumVec_ref()->empty());

  // Vector of vectors
  EXPECT_TRUE(req.testNestedVec_ref()->empty());

  // Unordered map
  EXPECT_TRUE(req.testUMap_ref()->empty());

  // Ordered map
  EXPECT_TRUE(req.testMap_ref()->empty());

  // Complex map
  EXPECT_TRUE(req.testComplexMap_ref()->empty());

  // Unordered set
  EXPECT_TRUE(req.testUSet_ref()->empty());

  // Ordered set
  EXPECT_TRUE(req.testSet_ref()->empty());

  // User Type
  EXPECT_TRUE(carbon::SerializationTraits<carbon::test::UserType>::isEmpty(
      *req.testType_ref()));

  // fields generated for every request (will likely be removed in the future)
  EXPECT_EQ(0, facebook::memcache::getExptimeIfExist(req));
  EXPECT_EQ(0, facebook::memcache::getFlagsIfExist(req));
}

TEST(CarbonBasic, setAndGetFieldRefAPI) {
  TestRequest req(kKeyLiteral);
  TestRequestStringKey req2(kKeyLiteral);

  // key
  const auto reqKeyPiece = req.key_ref()->fullKey();
  EXPECT_EQ(kKeyLiteral, reqKeyPiece);
  EXPECT_EQ(kKeyLiteral, req.key_ref()->fullKey());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", req.key_ref()->routingKey().str());
  EXPECT_EQ("/region/cluster/", req.key_ref()->routingPrefix().str());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop",
      req.key_ref()->keyWithoutRoute().str());

  const auto reqKeyPiece2 = req2.key_ref()->fullKey();
  EXPECT_EQ(kKeyLiteral, reqKeyPiece2);
  EXPECT_EQ(kKeyLiteral, req2.key_ref()->fullKey());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", req2.key_ref()->routingKey().str());
  EXPECT_EQ("/region/cluster/", req2.key_ref()->routingPrefix().str());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop",
      req2.key_ref()->keyWithoutRoute().str());

  // bool
  req.testBool_ref() = true;
  EXPECT_TRUE(*req.testBool_ref());
  // char
  req.testChar_ref() = 'A';
  EXPECT_EQ('A', *req.testChar_ref());
  // enum member
  req.testEnum_ref() = SimpleEnum::Negative;
  EXPECT_EQ(SimpleEnum::Negative, *req.testEnum_ref());
  EXPECT_EQ(-92233, static_cast<int64_t>(*req.testEnum_ref()));

  // int8_t
  req.testInt8_ref() = kMinInt8;
  EXPECT_EQ(kMinInt8, *req.testInt8_ref());
  // int16_t
  req.testInt16_ref() = kMinInt16;
  EXPECT_EQ(kMinInt16, *req.testInt16_ref());
  // int32_t
  req.testInt32_ref() = kMinInt32;
  EXPECT_EQ(kMinInt32, *req.testInt32_ref());
  // int64_t
  req.testInt64_ref() = kMinInt64;
  EXPECT_EQ(kMinInt64, *req.testInt64_ref());
  // uint8_t
  req.testUInt8_ref() = kMaxUInt8;
  EXPECT_EQ(kMaxUInt8, *req.testUInt8_ref());
  // uint16_t
  req.testUInt16_ref() = kMaxUInt16;
  EXPECT_EQ(kMaxUInt16, *req.testUInt16_ref());
  // uint32_t
  req.testUInt32_ref() = kMaxUInt32;
  EXPECT_EQ(kMaxUInt32, *req.testUInt32_ref());
  // uint64_t
  req.testUInt64_ref() = kMaxUInt64;
  EXPECT_EQ(kMaxUInt64, *req.testUInt64_ref());

  // float
  req.testFloat_ref() = 12345.789f;
  EXPECT_FLOAT_EQ(12345.789f, *req.testFloat_ref());
  // double
  req.testDouble_ref() = 12345.789;
  EXPECT_DOUBLE_EQ(12345.789, *req.testDouble_ref());

  // string
  req.testShortString_ref() = kShortString.str();
  EXPECT_EQ(kShortString, *req.testShortString_ref());
  req.testLongString_ref() = longString();
  EXPECT_EQ(longString(), *req.testLongString_ref());
  // IOBuf
  folly::IOBuf iobuf(folly::IOBuf::COPY_BUFFER, longString());
  req.testIobuf_ref() = iobuf;
  EXPECT_EQ(
      coalesceAndGetRange(iobuf).str(),
      coalesceAndGetRange(req.testIobuf_ref()).str());

  std::vector<std::string> strings = {
      "abcdefg", "xyz", kShortString.str(), longString()};
  req.testList_ref() = strings;
  EXPECT_EQ(strings, *req.testList_ref());

  // optionals
  EXPECT_FALSE(req.testOptionalKeywordString());
  EXPECT_FALSE(req.testOptionalKeywordIobuf());
  EXPECT_FALSE(req.testOptionalKeywordBool());

  // optionals field_ref
  EXPECT_FALSE(req.testOptionalKeywordString_ref());
  EXPECT_FALSE(req.testOptionalKeywordIobuf_ref());
  EXPECT_FALSE(req.testOptionalKeywordBool_ref());

  // Vector of enums
  std::vector<SimpleEnum> enums = {
      SimpleEnum::One,
      SimpleEnum::Zero,
      SimpleEnum::Twenty,
      SimpleEnum::Negative};
  req.testEnumVec_ref() = enums;
  EXPECT_EQ(enums, *req.testEnumVec_ref());

  // Vector of vectors
  std::vector<std::vector<uint64_t>> vectors = {{1, 1, 1}, {2, 2}};
  req.testNestedVec_ref() = vectors;
  EXPECT_EQ(vectors, *req.testNestedVec_ref());

  // Unordered map
  std::unordered_map<std::string, std::string> stringmap;
  stringmap.insert({"key", "value"});
  req.testUMap_ref() = stringmap;
  EXPECT_EQ(stringmap, *req.testUMap_ref());

  // Ordered map
  std::map<double, double> doublemap;
  doublemap.insert({1.08, 8.3});
  req.testMap_ref() = doublemap;
  EXPECT_EQ(doublemap, *req.testMap_ref());

  // Complex map
  std::map<std::string, std::vector<uint16_t>> complexmap;
  complexmap.insert({"key", {1, 2}});
  req.testComplexMap_ref() = complexmap;
  EXPECT_EQ(complexmap, *req.testComplexMap_ref());

  // Unordered set
  std::unordered_set<std::string> stringset;
  stringset.insert("hello");
  stringset.insert("world");
  req.testUSet_ref() = stringset;
  EXPECT_EQ(stringset, *req.testUSet_ref());

  // Ordered set
  std::set<uint64_t> intset;
  intset.insert(1);
  intset.insert(2);
  req.testSet_ref() = intset;
  EXPECT_EQ(intset, *req.testSet_ref());

  // User type
  carbon::test::UserType testType = {"blah", {1, 2, 3}};
  req.testType_ref() = testType;
  EXPECT_EQ(testType.name, req.testType_ref()->name);
  EXPECT_EQ(testType.points, req.testType_ref()->points);
}

TEST(CarbonBasic, setAndGetFieldRefAPIThrift) {
  DummyThriftRequest req(kKeyLiteral);

  // key
  const auto reqKeyPiece = req.key_ref()->fullKey();
  EXPECT_EQ(kKeyLiteral, reqKeyPiece);
  EXPECT_EQ(kKeyLiteral, req.key_ref()->fullKey());
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", req.key_ref()->routingKey().str());
  EXPECT_EQ("/region/cluster/", req.key_ref()->routingPrefix().str());
  EXPECT_EQ(
      "abcdefghijklmnopqrstuvwxyz|#|afterhashstop",
      req.key_ref()->keyWithoutRoute().str());

  // bool
  req.testBool_ref() = true;
  EXPECT_TRUE(*(req.testBool_ref()));

  // int8_t
  req.testInt8_ref() = kMinInt8;
  EXPECT_EQ(kMinInt8, *(req.testInt8_ref()));
  // int16_t
  req.testInt16_ref() = kMinInt16;
  EXPECT_EQ(kMinInt16, *(req.testInt16_ref()));
  // int32_t
  req.testInt32_ref() = kMinInt32;
  EXPECT_EQ(kMinInt32, *(req.testInt32_ref()));
  // int64_t
  req.testInt64_ref() = kMinInt64;
  EXPECT_EQ(kMinInt64, *(req.testInt64_ref()));
  // uint8_t
  req.testUInt8_ref() = kMaxUInt8;
  EXPECT_EQ(kMaxUInt8, *(req.testUInt8_ref()));
  // uint16_t
  req.testUInt16_ref() = kMaxUInt16;
  EXPECT_EQ(kMaxUInt16, *(req.testUInt16_ref()));
  // uint32_t
  req.testUInt32_ref() = kMaxUInt32;
  EXPECT_EQ(kMaxUInt32, *(req.testUInt32_ref()));
  // uint64_t
  req.testUInt64_ref() = kMaxUInt64;
  EXPECT_EQ(kMaxUInt64, *(req.testUInt64_ref()));

  // float
  req.testFloat_ref() = 12345.789f;
  EXPECT_FLOAT_EQ(12345.789f, *(req.testFloat_ref()));
  // double
  req.testDouble_ref() = 12345.789;
  EXPECT_DOUBLE_EQ(12345.789, *(req.testDouble_ref()));

  // optionals field_ref
  const auto lstringRef = longString();
  req.testOptionalKeywordString_ref() = lstringRef;
  EXPECT_EQ(lstringRef, *req.testOptionalKeywordString_ref());
  req.testOptionalKeywordIobuf_ref() =
      folly::IOBuf(folly::IOBuf::COPY_BUFFER, lstringRef);
  EXPECT_EQ(
      lstringRef, coalesceAndGetRange(req.testOptionalKeywordIobuf_ref()));
  req.testOptionalKeywordBool_ref() = false;
  EXPECT_EQ(false, *req.testOptionalKeywordBool_ref());

  // string
  req.testShortString_ref() = kShortString.str();
  EXPECT_EQ(kShortString, *(req.testShortString_ref()));
  req.testLongString_ref() = longString();
  EXPECT_EQ(longString(), *(req.testLongString_ref()));
  // IOBuf
  folly::IOBuf iobuf(folly::IOBuf::COPY_BUFFER, longString());
  req.testIobuf_ref() = iobuf;
  EXPECT_EQ(
      coalesceAndGetRange(iobuf).str(),
      coalesceAndGetRange(req.testIobuf_ref()).str());

  std::vector<std::string> strings = {
      "abcdefg", "xyz", kShortString.str(), longString()};
  req.testList_ref() = strings;
  EXPECT_EQ(strings, *(req.testList_ref()));
}

TEST(CarbonBasic, defaultConstructedMixinFieldRefAPI) {
  TestRequest req;

  // Mixed-in member functions
  EXPECT_EQ(0, *req.int32Member_ref());
  EXPECT_TRUE(req.stringMember_ref()->empty());
  EXPECT_EQ(SimpleEnum::Twenty, *req.enumMember_ref());
  EXPECT_EQ(0, *req.baseInt64Member_ref());

  // Member struct
  EXPECT_EQ(0, *req.testStruct_ref()->int32Member_ref());
  EXPECT_TRUE(req.testStruct_ref()->stringMember_ref()->empty());
  EXPECT_EQ(SimpleEnum::Twenty, *req.testStruct_ref()->enumMember_ref());
}

TEST(CarbonBasic, mixinsFieldRefAPI) {
  TestRequest request;
  EXPECT_EQ(0, *request.base_ref()->baseStruct_ref()->baseInt64Member_ref());

  request.base_ref()->baseStruct_ref()->baseInt64Member_ref() = 12345;
  // Exercise the different ways we can access the mixed-in baseInt64Member
  EXPECT_EQ(
      12345, *request.base_ref()->baseStruct_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *request.base_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *request.baseStruct_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *request.baseInt64Member_ref());
}

TEST(CarbonBasic, enumIntCompatibility) {
  testEnumCompatibility<
      carbon::test::StructWithEnumUInt16,
      carbon::test::StructWithEnumUInt32>(true);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumUInt16,
      carbon::test::StructWithOptionalEnumUInt32>(true);

  testEnumCompatibility<
      carbon::test::StructWithEnumUInt64,
      carbon::test::StructWithEnumUInt32>(true);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumUInt64,
      carbon::test::StructWithOptionalEnumUInt32>(true);

  testEnumCompatibility<
      carbon::test::StructWithEnumInt16,
      carbon::test::StructWithEnumInt32>(true);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumInt16,
      carbon::test::StructWithOptionalEnumInt32>(true);

  testEnumCompatibility<
      carbon::test::StructWithEnumInt64,
      carbon::test::StructWithEnumInt32>(true);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumInt64,
      carbon::test::StructWithOptionalEnumInt32>(true);

  // uint8_t/int8_t are incompatible with uint32_t/int32_t.
  testEnumCompatibility<
      carbon::test::StructWithEnumUInt8,
      carbon::test::StructWithEnumUInt32>(false);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumUInt8,
      carbon::test::StructWithOptionalEnumUInt32>(false);

  testEnumCompatibility<
      carbon::test::StructWithEnumInt8,
      carbon::test::StructWithEnumInt32>(false);
  testOptionalEnumCompatibility<
      carbon::test::StructWithOptionalEnumInt8,
      carbon::test::StructWithOptionalEnumInt32>(false);
}

TEST(CarbonBasic, defaultConstructedMixinFieldRefAPIThrift) {
  ThriftTestRequest req;

  // Mixed-in member functions
  EXPECT_EQ(0, *req.int32Member_ref());
  EXPECT_TRUE(req.stringMember_ref()->empty());
  EXPECT_EQ(carbon::test::MyEnum::A, *req.enumMember_ref());
  EXPECT_EQ(0, *req.baseInt64Member_ref());
}

TEST(CarbonBasic, mixinsFieldRefAPIThrift) {
  ThriftTestRequest req;
  EXPECT_EQ(0, *req.base_ref()->myBaseStruct_ref()->baseInt64Member_ref());

  req.base_ref()->myBaseStruct_ref()->baseInt64Member_ref() = 12345;
  // Exercise the different ways we can access the mixed-in baseInt64Member
  EXPECT_EQ(12345, *req.base_ref()->myBaseStruct_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *req.base_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *req.myBaseStruct_ref()->baseInt64Member_ref());
  EXPECT_EQ(12345, *req.baseInt64Member_ref());
}

TEST(CarbonTest, ForeachMemberTestThrift) {
  carbon::test::TestUnionThrift testUnion;
  TestUnionBuilder testUnionBuilder("a", 1);
  testUnion.foreachMember(testUnionBuilder);
  ASSERT_EQ(carbon::test::TestUnionThrift::Type::a, testUnion.getType());
  EXPECT_EQ(1, testUnion.get_a());
  EXPECT_TRUE(carbon::IsCarbonStruct<carbon::test::TestUnionThrift>::value);
}
