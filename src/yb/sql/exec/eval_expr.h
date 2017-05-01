//--------------------------------------------------------------------------------------------------
// Copyright (c) YugaByte, Inc.
//
// Entry point for the evaluating expressions.
//--------------------------------------------------------------------------------------------------

#ifndef YB_SQL_EXEC_EVAL_EXPR_H_
#define YB_SQL_EXEC_EVAL_EXPR_H_

#include "yb/sql/ptree/pt_expr.h"
#include "yb/common/yql_value.h"

namespace yb {
namespace sql {

struct EvalValue {
  virtual ~EvalValue();
  virtual InternalType datatype() = 0;
  bool is_null() const {
    return is_null_;
  }
  void set_null() {
    is_null_ = true;
  }
  void set_not_null() {
    is_null_ = false;
  }
  bool is_null_ = false;
};

struct EvalIntValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kInt64Value;
  }

  int64_t value_;
};

// To avoid overflow, all integer expressions are resulted in varint.
struct EvalVarIntStringValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kVarintValue;
  }

  MCString::SharedPtr value_;
};

struct EvalDoubleValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kDoubleValue;
  }

  long double value_;
};

// All text expressions are resulted in std::string.
struct EvalStringValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kStringValue;
  }

  MCString::SharedPtr value_;
};

// To avoid overflow, all floating expressions are resulted in decimal.
struct EvalDecimalValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kDecimalValue;
  }

  bool encoded_ = false;
  MCString::SharedPtr value_;
};

// All boolean expressions are resulted in std::bool.
struct EvalBoolValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kBoolValue;
  }

  bool value_;
};

struct EvalTimestampValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kTimestampValue;
  }

  int64_t value_;
};

struct EvalInetaddressValue: public EvalValue {
  InternalType datatype() {
    return InternalType::kInetaddressValue;
  }

  InetAddress value_;
};

struct EvalUuidValue: public EvalValue {
  InternalType datatype() {
    return InternalType::kUuidValue;
  }

  Uuid value_;
};

struct EvalTimeUuidValue: public EvalValue {
  InternalType datatype() {
    return InternalType::kTimeuuidValue;
  }

  Uuid value_;
};

struct EvalBinaryValue : public EvalValue {
  InternalType datatype() {
    return InternalType::kBinaryValue;
  }

  MCString::SharedPtr value_;
};

}  // namespace sql
}  // namespace yb

#endif  // YB_SQL_EXEC_EVAL_EXPR_H_
