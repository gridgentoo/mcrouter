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
#include "CompactTestMessages.h"

namespace carbon {
namespace test {

std::string enumSimpleEnumToString(SimpleEnum val) {
  switch (val) {
    case SimpleEnum::Twenty:
      return "Twenty";
    case SimpleEnum::Zero:
      return "Zero";
    case SimpleEnum::One:
      return "One";
    case SimpleEnum::Negative:
      return "Negative";
  }
  return "<INVALID_OPTION>";
}

constexpr const char* const TestCompactRequest::name;

void TestCompactRequest::deserialize(carbon::CarbonProtocolReader& reader) {
  reader.readStructBegin();
  while (true) {
    const auto pr = reader.readFieldHeader();
    const auto fieldType = pr.first;
    const auto fieldId = pr.second;

    if (fieldType == carbon::FieldType::Stop) {
      break;
    }

    switch (fieldId) {
      case 1: {
        reader.readField(key(), fieldType);
        break;
      }
      case 2: {
        reader.readField(testEnum(), fieldType);
        break;
      }
      case 3: {
        reader.readField(testBool(), fieldType);
        break;
      }
      case 4: {
        reader.readField(testChar(), fieldType);
        break;
      }
      case 5: {
        reader.readField(testInt8(), fieldType);
        break;
      }
      case 6: {
        reader.readField(testInt16(), fieldType);
        break;
      }
      case 7: {
        reader.readField(testInt32(), fieldType);
        break;
      }
      case 8: {
        reader.readField(testInt64(), fieldType);
        break;
      }
      case 9: {
        reader.readField(testUInt8(), fieldType);
        break;
      }
      case 10: {
        reader.readField(testUInt16(), fieldType);
        break;
      }
      case 11: {
        reader.readField(testUInt32(), fieldType);
        break;
      }
      case 12: {
        reader.readField(testUInt64(), fieldType);
        break;
      }
      case 13: {
        reader.readField(testShortString(), fieldType);
        break;
      }
      case 14: {
        reader.readField(testLongString(), fieldType);
        break;
      }
      case 15: {
        reader.readField(testIobuf(), fieldType);
        break;
      }
      case 16: {
        reader.readField(testList(), fieldType);
        break;
      }
      default: {
        reader.skip(fieldType);
        break;
      }
    }
  }
  reader.readStructEnd();
}

void TestCompactReply::deserialize(carbon::CarbonProtocolReader& reader) {
  reader.readStructBegin();
  while (true) {
    const auto pr = reader.readFieldHeader();
    const auto fieldType = pr.first;
    const auto fieldId = pr.second;

    if (fieldType == carbon::FieldType::Stop) {
      break;
    }

    switch (fieldId) {
      case 1: {
        reader.readField(result(), fieldType);
        break;
      }
      case 2: {
        reader.readField(valInt32(), fieldType);
        break;
      }
      case 3: {
        reader.readField(valInt64(), fieldType);
        break;
      }
      default: {
        reader.skip(fieldType);
        break;
      }
    }
  }
  reader.readStructEnd();
}
} // namespace test
} // namespace carbon
