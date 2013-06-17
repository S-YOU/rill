//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <memory>

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
//
// expressions
//
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
struct expression;
typedef std::shared_ptr<expression> expression_ptr;

struct binary_operator_expression;
typedef std::shared_ptr<binary_operator_expression> binary_operator_expression_ptr;

struct call_expression;
typedef std::shared_ptr<call_expression> call_expression_ptr;

struct embedded_function_call_expression;
typedef std::shared_ptr<embedded_function_call_expression> embedded_function_call_expression_ptr;

struct term_expression;
typedef std::shared_ptr<term_expression> term_expression_ptr;