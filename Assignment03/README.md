# Assignment 03 - Question 22: Type Checker with Implicit Conversions

## Problem Statement

Build a type checker that handles implicit conversions safely. Design rules ensuring that implicit conversions do not cause data loss or semantic ambiguity. The task includes building a conversion matrix and integrating it into expression checking.

## Solution Overview

This program implements a type checker that:

1. Manages a type system with basic types: int, float, char, bool
2. Implements a conversion matrix that defines safe and unsafe conversions
3. Checks variable declarations and assignments
4. Validates expressions with automatic type conversion
5. Prevents unsafe conversions that cause data loss or ambiguity

## How It Works

### Conversion Matrix

The conversion matrix defines which type conversions are safe and which are unsafe.

Safe Conversions (Allowed):
- int to float - No data loss
- char to int - Character to integer
- char to float - Character to float

Unsafe Conversions (Rejected):
- float to int - Data loss because decimal part is lost

### Type Checking Rules

Variable Assignment:
- If types match exactly, it's OK
- If safe conversion exists, it's OK with conversion
- If unsafe conversion, it's an ERROR

Binary Expressions:
- Finds common type using conversion matrix
- Applies implicit conversions when safe
- Returns result type after conversions
- Rejects incompatible types

Expression Result Type:
- Arithmetic operations return the common type (usually float if mixing int/float)
- Comparison operations always return bool

### Safety Rules

1. No Data Loss: Conversions that lose precision are rejected
   Example: float to int is rejected because it loses the decimal part

2. Automatic Promotion: Smaller types safely convert to larger types
   Example: int + float converts int to float, result is float

## Code Structure

### Classes

1. ConversionMatrix: Manages safe/unsafe conversion rules
   - isSafe(): Checks if conversion is safe
   - isUnsafe(): Checks if conversion is unsafe
   - commonType(): Finds common type for binary operations

2. TypeChecker: Main type checking logic
   - declare(): Declares a variable with a type
   - checkAssign(): Checks if assignment is safe
   - checkExpr(): Validates expressions with conversions

## Compilation and Running

To compile:
g++ TypeChecker.cpp -o typechecker

To run:
./typechecker

On Windows:
g++ TypeChecker.cpp -o typechecker.exe
typechecker.exe

## Example Output

The program demonstrates:

1. Safe conversions: int assigned to float variable (OK)
2. Unsafe conversions: float assigned to int variable (ERROR)
3. Expression checking: int + float converts to float + float
4. Type validation: Invalid operations are rejected

## Test Cases Included

1. Variable declarations
2. Safe implicit conversions
3. Unsafe conversions (should fail)
4. Expression checking with conversions
5. Comparison operations

## Key Features

- Prevents data loss in conversions
- Prevents semantic ambiguity
- Automatic type promotion in expressions
- Clear error messages
- Conversion matrix clearly defined
- Integrated into expression checking

## Design Decisions

1. Conversion Matrix: Centralized rules make it easy to modify conversion rules
2. Common Type Resolution: Automatically finds the best type for binary operations
3. Explicit Error Reporting: Clear messages help identify type issues
4. Safety First: Defaults to rejecting conversions unless explicitly safe

This implementation ensures that implicit conversions are handled safely without data loss or ambiguity, as required by the assignment.
