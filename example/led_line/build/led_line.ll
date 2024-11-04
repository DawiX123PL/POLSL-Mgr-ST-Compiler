; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 0 }>, section "main.symbol_table"

declare i1 @BOOL_TO_BOOL(ptr, i1)

declare i8 @BOOL_TO_SINT(ptr, i1)

declare i16 @BOOL_TO_INT(ptr, i1)

declare i32 @BOOL_TO_DINT(ptr, i1)

declare i64 @BOOL_TO_LINT(ptr, i1)

declare i8 @BOOL_TO_USINT(ptr, i1)

declare i16 @BOOL_TO_UINT(ptr, i1)

declare i32 @BOOL_TO_UDINT(ptr, i1)

declare i64 @BOOL_TO_ULINT(ptr, i1)

declare float @BOOL_TO_REAL(ptr, i1)

declare double @BOOL_TO_LREAL(ptr, i1)

declare i8 @BOOL_TO_BYTE(ptr, i1)

declare i16 @BOOL_TO_WORD(ptr, i1)

declare i32 @BOOL_TO_DWORD(ptr, i1)

declare i64 @BOOL_TO_LWORD(ptr, i1)

declare i1 @SINT_TO_BOOL(ptr, i8)

declare i8 @SINT_TO_SINT(ptr, i8)

declare i16 @SINT_TO_INT(ptr, i8)

declare i32 @SINT_TO_DINT(ptr, i8)

declare i64 @SINT_TO_LINT(ptr, i8)

declare i8 @SINT_TO_USINT(ptr, i8)

declare i16 @SINT_TO_UINT(ptr, i8)

declare i32 @SINT_TO_UDINT(ptr, i8)

declare i64 @SINT_TO_ULINT(ptr, i8)

declare float @SINT_TO_REAL(ptr, i8)

declare double @SINT_TO_LREAL(ptr, i8)

declare i8 @SINT_TO_BYTE(ptr, i8)

declare i16 @SINT_TO_WORD(ptr, i8)

declare i32 @SINT_TO_DWORD(ptr, i8)

declare i64 @SINT_TO_LWORD(ptr, i8)

declare i1 @INT_TO_BOOL(ptr, i16)

declare i8 @INT_TO_SINT(ptr, i16)

declare i16 @INT_TO_INT(ptr, i16)

declare i32 @INT_TO_DINT(ptr, i16)

declare i64 @INT_TO_LINT(ptr, i16)

declare i8 @INT_TO_USINT(ptr, i16)

declare i16 @INT_TO_UINT(ptr, i16)

declare i32 @INT_TO_UDINT(ptr, i16)

declare i64 @INT_TO_ULINT(ptr, i16)

declare float @INT_TO_REAL(ptr, i16)

declare double @INT_TO_LREAL(ptr, i16)

declare i8 @INT_TO_BYTE(ptr, i16)

declare i16 @INT_TO_WORD(ptr, i16)

declare i32 @INT_TO_DWORD(ptr, i16)

declare i64 @INT_TO_LWORD(ptr, i16)

declare i1 @DINT_TO_BOOL(ptr, i32)

declare i8 @DINT_TO_SINT(ptr, i32)

declare i16 @DINT_TO_INT(ptr, i32)

declare i32 @DINT_TO_DINT(ptr, i32)

declare i64 @DINT_TO_LINT(ptr, i32)

declare i8 @DINT_TO_USINT(ptr, i32)

declare i16 @DINT_TO_UINT(ptr, i32)

declare i32 @DINT_TO_UDINT(ptr, i32)

declare i64 @DINT_TO_ULINT(ptr, i32)

declare float @DINT_TO_REAL(ptr, i32)

declare double @DINT_TO_LREAL(ptr, i32)

declare i8 @DINT_TO_BYTE(ptr, i32)

declare i16 @DINT_TO_WORD(ptr, i32)

declare i32 @DINT_TO_DWORD(ptr, i32)

declare i64 @DINT_TO_LWORD(ptr, i32)

declare i1 @LINT_TO_BOOL(ptr, i64)

declare i8 @LINT_TO_SINT(ptr, i64)

declare i16 @LINT_TO_INT(ptr, i64)

declare i32 @LINT_TO_DINT(ptr, i64)

declare i64 @LINT_TO_LINT(ptr, i64)

declare i8 @LINT_TO_USINT(ptr, i64)

declare i16 @LINT_TO_UINT(ptr, i64)

declare i32 @LINT_TO_UDINT(ptr, i64)

declare i64 @LINT_TO_ULINT(ptr, i64)

declare float @LINT_TO_REAL(ptr, i64)

declare double @LINT_TO_LREAL(ptr, i64)

declare i8 @LINT_TO_BYTE(ptr, i64)

declare i16 @LINT_TO_WORD(ptr, i64)

declare i32 @LINT_TO_DWORD(ptr, i64)

declare i64 @LINT_TO_LWORD(ptr, i64)

declare i1 @USINT_TO_BOOL(ptr, i8)

declare i8 @USINT_TO_SINT(ptr, i8)

declare i16 @USINT_TO_INT(ptr, i8)

declare i32 @USINT_TO_DINT(ptr, i8)

declare i64 @USINT_TO_LINT(ptr, i8)

declare i8 @USINT_TO_USINT(ptr, i8)

declare i16 @USINT_TO_UINT(ptr, i8)

declare i32 @USINT_TO_UDINT(ptr, i8)

declare i64 @USINT_TO_ULINT(ptr, i8)

declare float @USINT_TO_REAL(ptr, i8)

declare double @USINT_TO_LREAL(ptr, i8)

declare i8 @USINT_TO_BYTE(ptr, i8)

declare i16 @USINT_TO_WORD(ptr, i8)

declare i32 @USINT_TO_DWORD(ptr, i8)

declare i64 @USINT_TO_LWORD(ptr, i8)

declare i1 @UINT_TO_BOOL(ptr, i16)

declare i8 @UINT_TO_SINT(ptr, i16)

declare i16 @UINT_TO_INT(ptr, i16)

declare i32 @UINT_TO_DINT(ptr, i16)

declare i64 @UINT_TO_LINT(ptr, i16)

declare i8 @UINT_TO_USINT(ptr, i16)

declare i16 @UINT_TO_UINT(ptr, i16)

declare i32 @UINT_TO_UDINT(ptr, i16)

declare i64 @UINT_TO_ULINT(ptr, i16)

declare float @UINT_TO_REAL(ptr, i16)

declare double @UINT_TO_LREAL(ptr, i16)

declare i8 @UINT_TO_BYTE(ptr, i16)

declare i16 @UINT_TO_WORD(ptr, i16)

declare i32 @UINT_TO_DWORD(ptr, i16)

declare i64 @UINT_TO_LWORD(ptr, i16)

declare i1 @UDINT_TO_BOOL(ptr, i32)

declare i8 @UDINT_TO_SINT(ptr, i32)

declare i16 @UDINT_TO_INT(ptr, i32)

declare i32 @UDINT_TO_DINT(ptr, i32)

declare i64 @UDINT_TO_LINT(ptr, i32)

declare i8 @UDINT_TO_USINT(ptr, i32)

declare i16 @UDINT_TO_UINT(ptr, i32)

declare i32 @UDINT_TO_UDINT(ptr, i32)

declare i64 @UDINT_TO_ULINT(ptr, i32)

declare float @UDINT_TO_REAL(ptr, i32)

declare double @UDINT_TO_LREAL(ptr, i32)

declare i8 @UDINT_TO_BYTE(ptr, i32)

declare i16 @UDINT_TO_WORD(ptr, i32)

declare i32 @UDINT_TO_DWORD(ptr, i32)

declare i64 @UDINT_TO_LWORD(ptr, i32)

declare i1 @ULINT_TO_BOOL(ptr, i64)

declare i8 @ULINT_TO_SINT(ptr, i64)

declare i16 @ULINT_TO_INT(ptr, i64)

declare i32 @ULINT_TO_DINT(ptr, i64)

declare i64 @ULINT_TO_LINT(ptr, i64)

declare i8 @ULINT_TO_USINT(ptr, i64)

declare i16 @ULINT_TO_UINT(ptr, i64)

declare i32 @ULINT_TO_UDINT(ptr, i64)

declare i64 @ULINT_TO_ULINT(ptr, i64)

declare float @ULINT_TO_REAL(ptr, i64)

declare double @ULINT_TO_LREAL(ptr, i64)

declare i8 @ULINT_TO_BYTE(ptr, i64)

declare i16 @ULINT_TO_WORD(ptr, i64)

declare i32 @ULINT_TO_DWORD(ptr, i64)

declare i64 @ULINT_TO_LWORD(ptr, i64)

declare i1 @REAL_TO_BOOL(ptr, float)

declare i8 @REAL_TO_SINT(ptr, float)

declare i16 @REAL_TO_INT(ptr, float)

declare i32 @REAL_TO_DINT(ptr, float)

declare i64 @REAL_TO_LINT(ptr, float)

declare i8 @REAL_TO_USINT(ptr, float)

declare i16 @REAL_TO_UINT(ptr, float)

declare i32 @REAL_TO_UDINT(ptr, float)

declare i64 @REAL_TO_ULINT(ptr, float)

declare float @REAL_TO_REAL(ptr, float)

declare double @REAL_TO_LREAL(ptr, float)

declare i8 @REAL_TO_BYTE(ptr, float)

declare i16 @REAL_TO_WORD(ptr, float)

declare i32 @REAL_TO_DWORD(ptr, float)

declare i64 @REAL_TO_LWORD(ptr, float)

declare i1 @LREAL_TO_BOOL(ptr, double)

declare i8 @LREAL_TO_SINT(ptr, double)

declare i16 @LREAL_TO_INT(ptr, double)

declare i32 @LREAL_TO_DINT(ptr, double)

declare i64 @LREAL_TO_LINT(ptr, double)

declare i8 @LREAL_TO_USINT(ptr, double)

declare i16 @LREAL_TO_UINT(ptr, double)

declare i32 @LREAL_TO_UDINT(ptr, double)

declare i64 @LREAL_TO_ULINT(ptr, double)

declare float @LREAL_TO_REAL(ptr, double)

declare double @LREAL_TO_LREAL(ptr, double)

declare i8 @LREAL_TO_BYTE(ptr, double)

declare i16 @LREAL_TO_WORD(ptr, double)

declare i32 @LREAL_TO_DWORD(ptr, double)

declare i64 @LREAL_TO_LWORD(ptr, double)

declare i1 @BYTE_TO_BOOL(ptr, i8)

declare i8 @BYTE_TO_SINT(ptr, i8)

declare i16 @BYTE_TO_INT(ptr, i8)

declare i32 @BYTE_TO_DINT(ptr, i8)

declare i64 @BYTE_TO_LINT(ptr, i8)

declare i8 @BYTE_TO_USINT(ptr, i8)

declare i16 @BYTE_TO_UINT(ptr, i8)

declare i32 @BYTE_TO_UDINT(ptr, i8)

declare i64 @BYTE_TO_ULINT(ptr, i8)

declare float @BYTE_TO_REAL(ptr, i8)

declare double @BYTE_TO_LREAL(ptr, i8)

declare i8 @BYTE_TO_BYTE(ptr, i8)

declare i16 @BYTE_TO_WORD(ptr, i8)

declare i32 @BYTE_TO_DWORD(ptr, i8)

declare i64 @BYTE_TO_LWORD(ptr, i8)

declare i1 @WORD_TO_BOOL(ptr, i16)

declare i8 @WORD_TO_SINT(ptr, i16)

declare i16 @WORD_TO_INT(ptr, i16)

declare i32 @WORD_TO_DINT(ptr, i16)

declare i64 @WORD_TO_LINT(ptr, i16)

declare i8 @WORD_TO_USINT(ptr, i16)

declare i16 @WORD_TO_UINT(ptr, i16)

declare i32 @WORD_TO_UDINT(ptr, i16)

declare i64 @WORD_TO_ULINT(ptr, i16)

declare float @WORD_TO_REAL(ptr, i16)

declare double @WORD_TO_LREAL(ptr, i16)

declare i8 @WORD_TO_BYTE(ptr, i16)

declare i16 @WORD_TO_WORD(ptr, i16)

declare i32 @WORD_TO_DWORD(ptr, i16)

declare i64 @WORD_TO_LWORD(ptr, i16)

declare i1 @DWORD_TO_BOOL(ptr, i32)

declare i8 @DWORD_TO_SINT(ptr, i32)

declare i16 @DWORD_TO_INT(ptr, i32)

declare i32 @DWORD_TO_DINT(ptr, i32)

declare i64 @DWORD_TO_LINT(ptr, i32)

declare i8 @DWORD_TO_USINT(ptr, i32)

declare i16 @DWORD_TO_UINT(ptr, i32)

declare i32 @DWORD_TO_UDINT(ptr, i32)

declare i64 @DWORD_TO_ULINT(ptr, i32)

declare float @DWORD_TO_REAL(ptr, i32)

declare double @DWORD_TO_LREAL(ptr, i32)

declare i8 @DWORD_TO_BYTE(ptr, i32)

declare i16 @DWORD_TO_WORD(ptr, i32)

declare i32 @DWORD_TO_DWORD(ptr, i32)

declare i64 @DWORD_TO_LWORD(ptr, i32)

declare i1 @LWORD_TO_BOOL(ptr, i64)

declare i8 @LWORD_TO_SINT(ptr, i64)

declare i16 @LWORD_TO_INT(ptr, i64)

declare i32 @LWORD_TO_DINT(ptr, i64)

declare i64 @LWORD_TO_LINT(ptr, i64)

declare i8 @LWORD_TO_USINT(ptr, i64)

declare i16 @LWORD_TO_UINT(ptr, i64)

declare i32 @LWORD_TO_UDINT(ptr, i64)

declare i64 @LWORD_TO_ULINT(ptr, i64)

declare float @LWORD_TO_REAL(ptr, i64)

declare double @LWORD_TO_LREAL(ptr, i64)

declare i8 @LWORD_TO_BYTE(ptr, i64)

declare i16 @LWORD_TO_WORD(ptr, i64)

declare i32 @LWORD_TO_DWORD(ptr, i64)

declare i64 @LWORD_TO_LWORD(ptr, i64)

define void @main.init(ptr %0, ptr %1) {
entry:
  ret void
}

define void @main(ptr %0, ptr %1) {
entry:
  %"%IX0.0.1" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit" = load i8, ptr %"%IX0.0.1", align 1
  %"%IX0.0.1_value_8bit" = and i8 %"%IX0.0.1_value_tmp_8bit", 2
  %"%IX0.0.1_value" = icmp ne i8 %"%IX0.0.1_value_8bit", 0
  %"%QX1.1.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.0_value_tmp_8bit" = load i8, ptr %"%QX1.1.0", align 1
  %2 = and i8 %"%QX1.1.0_value_tmp_8bit", -2
  %3 = zext i1 %"%IX0.0.1_value" to i8
  %4 = shl i8 %3, 0
  %5 = or i8 %2, %4
  store i8 %5, ptr %"%QX1.1.0", align 1
  %"%IX0.0.11" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit2" = load i8, ptr %"%IX0.0.11", align 1
  %"%IX0.0.1_value_8bit3" = and i8 %"%IX0.0.1_value_tmp_8bit2", 2
  %"%IX0.0.1_value4" = icmp ne i8 %"%IX0.0.1_value_8bit3", 0
  %"%QX1.1.1" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.1_value_tmp_8bit" = load i8, ptr %"%QX1.1.1", align 1
  %6 = and i8 %"%QX1.1.1_value_tmp_8bit", -3
  %7 = zext i1 %"%IX0.0.1_value4" to i8
  %8 = shl i8 %7, 1
  %9 = or i8 %6, %8
  store i8 %9, ptr %"%QX1.1.1", align 1
  %"%IX0.0.15" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit6" = load i8, ptr %"%IX0.0.15", align 1
  %"%IX0.0.1_value_8bit7" = and i8 %"%IX0.0.1_value_tmp_8bit6", 2
  %"%IX0.0.1_value8" = icmp ne i8 %"%IX0.0.1_value_8bit7", 0
  %"%QX1.1.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.2_value_tmp_8bit" = load i8, ptr %"%QX1.1.2", align 1
  %10 = and i8 %"%QX1.1.2_value_tmp_8bit", -5
  %11 = zext i1 %"%IX0.0.1_value8" to i8
  %12 = shl i8 %11, 2
  %13 = or i8 %10, %12
  store i8 %13, ptr %"%QX1.1.2", align 1
  %"%IX0.0.19" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit10" = load i8, ptr %"%IX0.0.19", align 1
  %"%IX0.0.1_value_8bit11" = and i8 %"%IX0.0.1_value_tmp_8bit10", 2
  %"%IX0.0.1_value12" = icmp ne i8 %"%IX0.0.1_value_8bit11", 0
  %"%QX1.1.3" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.3_value_tmp_8bit" = load i8, ptr %"%QX1.1.3", align 1
  %14 = and i8 %"%QX1.1.3_value_tmp_8bit", -9
  %15 = zext i1 %"%IX0.0.1_value12" to i8
  %16 = shl i8 %15, 3
  %17 = or i8 %14, %16
  store i8 %17, ptr %"%QX1.1.3", align 1
  %"%IX0.0.113" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit14" = load i8, ptr %"%IX0.0.113", align 1
  %"%IX0.0.1_value_8bit15" = and i8 %"%IX0.0.1_value_tmp_8bit14", 2
  %"%IX0.0.1_value16" = icmp ne i8 %"%IX0.0.1_value_8bit15", 0
  %"%QX1.1.4" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.4_value_tmp_8bit" = load i8, ptr %"%QX1.1.4", align 1
  %18 = and i8 %"%QX1.1.4_value_tmp_8bit", -17
  %19 = zext i1 %"%IX0.0.1_value16" to i8
  %20 = shl i8 %19, 4
  %21 = or i8 %18, %20
  store i8 %21, ptr %"%QX1.1.4", align 1
  %"%IX0.0.117" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit18" = load i8, ptr %"%IX0.0.117", align 1
  %"%IX0.0.1_value_8bit19" = and i8 %"%IX0.0.1_value_tmp_8bit18", 2
  %"%IX0.0.1_value20" = icmp ne i8 %"%IX0.0.1_value_8bit19", 0
  %"%QX1.1.5" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.5_value_tmp_8bit" = load i8, ptr %"%QX1.1.5", align 1
  %22 = and i8 %"%QX1.1.5_value_tmp_8bit", -33
  %23 = zext i1 %"%IX0.0.1_value20" to i8
  %24 = shl i8 %23, 5
  %25 = or i8 %22, %24
  store i8 %25, ptr %"%QX1.1.5", align 1
  %"%IX0.0.121" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit22" = load i8, ptr %"%IX0.0.121", align 1
  %"%IX0.0.1_value_8bit23" = and i8 %"%IX0.0.1_value_tmp_8bit22", 2
  %"%IX0.0.1_value24" = icmp ne i8 %"%IX0.0.1_value_8bit23", 0
  %"%QX1.1.6" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.6_value_tmp_8bit" = load i8, ptr %"%QX1.1.6", align 1
  %26 = and i8 %"%QX1.1.6_value_tmp_8bit", -65
  %27 = zext i1 %"%IX0.0.1_value24" to i8
  %28 = shl i8 %27, 6
  %29 = or i8 %26, %28
  store i8 %29, ptr %"%QX1.1.6", align 1
  %"%IX0.0.125" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 0
  %"%IX0.0.1_value_tmp_8bit26" = load i8, ptr %"%IX0.0.125", align 1
  %"%IX0.0.1_value_8bit27" = and i8 %"%IX0.0.1_value_tmp_8bit26", 2
  %"%IX0.0.1_value28" = icmp ne i8 %"%IX0.0.1_value_8bit27", 0
  %"%QX1.1.7" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 1
  %"%QX1.1.7_value_tmp_8bit" = load i8, ptr %"%QX1.1.7", align 1
  %30 = and i8 %"%QX1.1.7_value_tmp_8bit", 127
  %31 = zext i1 %"%IX0.0.1_value28" to i8
  %32 = shl i8 %31, 7
  %33 = or i8 %30, %32
  store i8 %33, ptr %"%QX1.1.7", align 1
  %"%IW0.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value" = load i16, ptr %"%IW0.2", align 2
  %FunctionCall = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value")
  %34 = fcmp ugt float %FunctionCall, 1.000000e+02
  %"%QX1.0.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.0_value_tmp_8bit" = load i8, ptr %"%QX1.0.0", align 1
  %35 = and i8 %"%QX1.0.0_value_tmp_8bit", -2
  %36 = zext i1 %34 to i8
  %37 = shl i8 %36, 0
  %38 = or i8 %35, %37
  store i8 %38, ptr %"%QX1.0.0", align 1
  %"%IW0.229" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value30" = load i16, ptr %"%IW0.229", align 2
  %FunctionCall31 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value30")
  %39 = fcmp ugt float %FunctionCall31, 2.000000e+02
  %"%QX1.0.1" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.1_value_tmp_8bit" = load i8, ptr %"%QX1.0.1", align 1
  %40 = and i8 %"%QX1.0.1_value_tmp_8bit", -3
  %41 = zext i1 %39 to i8
  %42 = shl i8 %41, 1
  %43 = or i8 %40, %42
  store i8 %43, ptr %"%QX1.0.1", align 1
  %"%IW0.232" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value33" = load i16, ptr %"%IW0.232", align 2
  %FunctionCall34 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value33")
  %44 = fcmp ugt float %FunctionCall34, 3.000000e+02
  %"%QX1.0.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.2_value_tmp_8bit" = load i8, ptr %"%QX1.0.2", align 1
  %45 = and i8 %"%QX1.0.2_value_tmp_8bit", -5
  %46 = zext i1 %44 to i8
  %47 = shl i8 %46, 2
  %48 = or i8 %45, %47
  store i8 %48, ptr %"%QX1.0.2", align 1
  %"%IW0.235" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value36" = load i16, ptr %"%IW0.235", align 2
  %FunctionCall37 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value36")
  %49 = fcmp ugt float %FunctionCall37, 4.000000e+02
  %"%QX1.0.3" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.3_value_tmp_8bit" = load i8, ptr %"%QX1.0.3", align 1
  %50 = and i8 %"%QX1.0.3_value_tmp_8bit", -9
  %51 = zext i1 %49 to i8
  %52 = shl i8 %51, 3
  %53 = or i8 %50, %52
  store i8 %53, ptr %"%QX1.0.3", align 1
  %"%IW0.238" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value39" = load i16, ptr %"%IW0.238", align 2
  %FunctionCall40 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value39")
  %54 = fcmp ugt float %FunctionCall40, 5.000000e+02
  %"%QX1.0.4" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.4_value_tmp_8bit" = load i8, ptr %"%QX1.0.4", align 1
  %55 = and i8 %"%QX1.0.4_value_tmp_8bit", -17
  %56 = zext i1 %54 to i8
  %57 = shl i8 %56, 4
  %58 = or i8 %55, %57
  store i8 %58, ptr %"%QX1.0.4", align 1
  %"%IW0.241" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value42" = load i16, ptr %"%IW0.241", align 2
  %FunctionCall43 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value42")
  %59 = fcmp ugt float %FunctionCall43, 6.000000e+02
  %"%QX1.0.5" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.5_value_tmp_8bit" = load i8, ptr %"%QX1.0.5", align 1
  %60 = and i8 %"%QX1.0.5_value_tmp_8bit", -33
  %61 = zext i1 %59 to i8
  %62 = shl i8 %61, 5
  %63 = or i8 %60, %62
  store i8 %63, ptr %"%QX1.0.5", align 1
  %"%IW0.244" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value45" = load i16, ptr %"%IW0.244", align 2
  %FunctionCall46 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value45")
  %64 = fcmp ugt float %FunctionCall46, 7.000000e+02
  %"%QX1.0.6" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.6_value_tmp_8bit" = load i8, ptr %"%QX1.0.6", align 1
  %65 = and i8 %"%QX1.0.6_value_tmp_8bit", -65
  %66 = zext i1 %64 to i8
  %67 = shl i8 %66, 6
  %68 = or i8 %65, %67
  store i8 %68, ptr %"%QX1.0.6", align 1
  %"%IW0.247" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 0, i32 2
  %"%IW0.2_value48" = load i16, ptr %"%IW0.247", align 2
  %FunctionCall49 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW0.2_value48")
  %69 = fcmp ugt float %FunctionCall49, 8.000000e+02
  %"%QX1.0.7" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 1, i32 0
  %"%QX1.0.7_value_tmp_8bit" = load i8, ptr %"%QX1.0.7", align 1
  %70 = and i8 %"%QX1.0.7_value_tmp_8bit", 127
  %71 = zext i1 %69 to i8
  %72 = shl i8 %71, 7
  %73 = or i8 %70, %72
  store i8 %73, ptr %"%QX1.0.7", align 1
  ret void
}
