; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc"

%main.struct = type <{ i1, double, float, i16, i1 }>

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 16 }>, section "main.symbol_table"

define i1 @test_func(ptr %0, i16 %1, i16 %2, i16 %3, ptr %4, ptr %5) {
entry:
  %test_func.alloca = alloca i1, align 1
  %c.alloca = alloca i16, align 2
  %x.alloca = alloca i16, align 2
  %b1.alloca = alloca float, align 4
  %c1.alloca = alloca i16, align 2
  %b.alloca = alloca i16, align 2
  %aaa.alloca = alloca i16, align 2
  store i16 %1, ptr %aaa.alloca, align 2
  store i16 %2, ptr %b.alloca, align 2
  store i16 %3, ptr %c1.alloca, align 2
  %6 = icmp eq ptr %4, null
  br i1 %6, label %if_pointer_null, label %if_pointer_not_null

if_pointer_null:                                  ; preds = %entry
  br label %if_merge

if_pointer_not_null:                              ; preds = %entry
  %7 = load float, ptr %4, align 4
  br label %if_merge

if_merge:                                         ; preds = %if_pointer_not_null, %if_pointer_null
  %in_out_value = phi float [ %7, %if_pointer_not_null ], [ 0.000000e+00, %if_pointer_null ]
  store float %in_out_value, ptr %b1.alloca, align 4
  store i16 0, ptr %x.alloca, align 2
  store i16 -100, ptr %c.alloca, align 2
  store i1 false, ptr %test_func.alloca, align 1
  br label %while_condition

while_condition:                                  ; preds = %while_do, %if_merge
  %c = load i16, ptr %c.alloca, align 2
  %8 = add i16 %c, -1
  %9 = icmp sgt i16 %8, -1
  br i1 %9, label %while_do, label %end_while

while_do:                                         ; preds = %while_condition
  %aaa = load i16, ptr %aaa.alloca, align 2
  %10 = sub i16 0, %aaa
  %b = load i16, ptr %b.alloca, align 2
  %11 = add i16 %10, %b
  %c1 = load i16, ptr %c1.alloca, align 2
  %12 = add i16 %11, %c1
  store i16 %12, ptr %x.alloca, align 2
  br label %while_condition

end_while:                                        ; preds = %while_condition
  br label %return_block

return_block:                                     ; preds = %end_while
  %is_not_null = icmp ne ptr %4, null
  br i1 %is_not_null, label %if_pointer_notnull, label %if_merge1

if_pointer_notnull:                               ; preds = %return_block
  %13 = load float, ptr %b1.alloca, align 4
  store float %13, ptr %4, align 4
  br label %if_merge1

if_merge1:                                        ; preds = %if_pointer_notnull, %return_block
  %is_not_null4 = icmp ne ptr %5, null
  br i1 %is_not_null4, label %if_pointer_notnull2, label %if_merge3

if_pointer_notnull2:                              ; preds = %if_merge1
  %14 = load i16, ptr %x.alloca, align 2
  store i16 %14, ptr %5, align 2
  br label %if_merge3

if_merge3:                                        ; preds = %if_pointer_notnull2, %if_merge1
  %result = load i1, ptr %test_func.alloca, align 1
  ret i1 %result
}

define double @fahrenheit_to_celsius(ptr %0, double %1) {
entry:
  %fahrenheit_to_celsius.alloca = alloca double, align 8
  %f.alloca = alloca double, align 8
  store double %1, ptr %f.alloca, align 8
  store double 0.000000e+00, ptr %fahrenheit_to_celsius.alloca, align 8
  %f = load double, ptr %f.alloca, align 8
  %2 = fsub double %f, 3.200000e+01
  %3 = fdiv double %2, 1.800000e+00
  store double %3, ptr %fahrenheit_to_celsius.alloca, align 8
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load double, ptr %fahrenheit_to_celsius.alloca, align 8
  ret double %result
}

define void @main.init(ptr %0, ptr %1) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  store i1 true, ptr %v1, align 1
  %v2 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 1
  store double 1.100000e+00, ptr %v2, align 8
  %v3 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 2
  store double 2.137000e+03, ptr %v3, align 8
  %v4 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 3
  store i16 0, ptr %v4, align 2
  %v5 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 4
  store i1 false, ptr %v5, align 1
  ret void
}

define void @main(ptr %0, ptr %1) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  %v2 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 1
  %v3 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 2
  %v4 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 3
  %v5 = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 4
  %"%QX0.1.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.0_value_tmp_8bit" = load i8, ptr %"%QX0.1.0", align 1
  %2 = and i8 %"%QX0.1.0_value_tmp_8bit", -2
  %3 = or i8 %2, 1
  store i8 %3, ptr %"%QX0.1.0", align 1
  %"%QX0.1.1" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.1_value_tmp_8bit" = load i8, ptr %"%QX0.1.1", align 1
  %4 = and i8 %"%QX0.1.1_value_tmp_8bit", -3
  %5 = or i8 %4, 2
  store i8 %5, ptr %"%QX0.1.1", align 1
  %"%QX0.1.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.2_value_tmp_8bit" = load i8, ptr %"%QX0.1.2", align 1
  %6 = and i8 %"%QX0.1.2_value_tmp_8bit", -5
  %7 = or i8 %6, 4
  store i8 %7, ptr %"%QX0.1.2", align 1
  %"%QX0.1.3" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.3_value_tmp_8bit" = load i8, ptr %"%QX0.1.3", align 1
  %8 = and i8 %"%QX0.1.3_value_tmp_8bit", -9
  %9 = or i8 %8, 8
  store i8 %9, ptr %"%QX0.1.3", align 1
  %"%QX0.1.4" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.4_value_tmp_8bit" = load i8, ptr %"%QX0.1.4", align 1
  %10 = and i8 %"%QX0.1.4_value_tmp_8bit", -17
  %11 = or i8 %10, 16
  store i8 %11, ptr %"%QX0.1.4", align 1
  %"%QX0.1.5" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.5_value_tmp_8bit" = load i8, ptr %"%QX0.1.5", align 1
  %12 = and i8 %"%QX0.1.5_value_tmp_8bit", -33
  %13 = or i8 %12, 32
  store i8 %13, ptr %"%QX0.1.5", align 1
  %"%QX0.1.6" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.6_value_tmp_8bit" = load i8, ptr %"%QX0.1.6", align 1
  %14 = and i8 %"%QX0.1.6_value_tmp_8bit", -65
  %15 = or i8 %14, 64
  store i8 %15, ptr %"%QX0.1.6", align 1
  %"%QX0.1.7" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 1
  %"%QX0.1.7_value_tmp_8bit" = load i8, ptr %"%QX0.1.7", align 1
  %16 = and i8 %"%QX0.1.7_value_tmp_8bit", 127
  %17 = or i8 %16, -128
  store i8 %17, ptr %"%QX0.1.7", align 1
  %"%IW1.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value")
  %18 = fcmp ugt float %FunctionCall, 0.000000e+00
  %"%QX0.0.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.0_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %19 = and i8 %"%QX0.0.0_value_tmp_8bit", -2
  %20 = zext i1 %18 to i8
  %21 = shl i8 %20, 0
  %22 = or i8 %19, %21
  store i8 %22, ptr %"%QX0.0.0", align 1
  %"%IW1.21" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value2" = load i16, ptr %"%IW1.21", align 2
  %FunctionCall3 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value2")
  %23 = fcmp ugt float %FunctionCall3, 1.000000e+02
  %"%QX0.0.1" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.1_value_tmp_8bit" = load i8, ptr %"%QX0.0.1", align 1
  %24 = and i8 %"%QX0.0.1_value_tmp_8bit", -3
  %25 = zext i1 %23 to i8
  %26 = shl i8 %25, 1
  %27 = or i8 %24, %26
  store i8 %27, ptr %"%QX0.0.1", align 1
  %"%IW1.24" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value5" = load i16, ptr %"%IW1.24", align 2
  %FunctionCall6 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value5")
  %28 = fcmp ugt float %FunctionCall6, 2.000000e+02
  %"%QX0.0.2" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.2_value_tmp_8bit" = load i8, ptr %"%QX0.0.2", align 1
  %29 = and i8 %"%QX0.0.2_value_tmp_8bit", -5
  %30 = zext i1 %28 to i8
  %31 = shl i8 %30, 2
  %32 = or i8 %29, %31
  store i8 %32, ptr %"%QX0.0.2", align 1
  %"%IW1.27" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value8" = load i16, ptr %"%IW1.27", align 2
  %FunctionCall9 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value8")
  %33 = fcmp ugt float %FunctionCall9, 3.000000e+02
  %"%QX0.0.3" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.3_value_tmp_8bit" = load i8, ptr %"%QX0.0.3", align 1
  %34 = and i8 %"%QX0.0.3_value_tmp_8bit", -9
  %35 = zext i1 %33 to i8
  %36 = shl i8 %35, 3
  %37 = or i8 %34, %36
  store i8 %37, ptr %"%QX0.0.3", align 1
  %"%IW1.210" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value11" = load i16, ptr %"%IW1.210", align 2
  %FunctionCall12 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value11")
  %38 = fcmp ugt float %FunctionCall12, 4.000000e+02
  %"%QX0.0.4" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.4_value_tmp_8bit" = load i8, ptr %"%QX0.0.4", align 1
  %39 = and i8 %"%QX0.0.4_value_tmp_8bit", -17
  %40 = zext i1 %38 to i8
  %41 = shl i8 %40, 4
  %42 = or i8 %39, %41
  store i8 %42, ptr %"%QX0.0.4", align 1
  %"%IW1.213" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value14" = load i16, ptr %"%IW1.213", align 2
  %FunctionCall15 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value14")
  %43 = fcmp ugt float %FunctionCall15, 5.000000e+02
  %"%QX0.0.5" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.5_value_tmp_8bit" = load i8, ptr %"%QX0.0.5", align 1
  %44 = and i8 %"%QX0.0.5_value_tmp_8bit", -33
  %45 = zext i1 %43 to i8
  %46 = shl i8 %45, 5
  %47 = or i8 %44, %46
  store i8 %47, ptr %"%QX0.0.5", align 1
  %"%IW1.216" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value17" = load i16, ptr %"%IW1.216", align 2
  %FunctionCall18 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value17")
  %48 = fcmp ugt float %FunctionCall18, 6.000000e+02
  %"%QX0.0.6" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.6_value_tmp_8bit" = load i8, ptr %"%QX0.0.6", align 1
  %49 = and i8 %"%QX0.0.6_value_tmp_8bit", -65
  %50 = zext i1 %48 to i8
  %51 = shl i8 %50, 6
  %52 = or i8 %49, %51
  store i8 %52, ptr %"%QX0.0.6", align 1
  %"%IW1.219" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 0, i32 1, i32 2
  %"%IW1.2_value20" = load i16, ptr %"%IW1.219", align 2
  %FunctionCall21 = call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value20")
  %53 = fcmp ugt float %FunctionCall21, 7.000000e+02
  %"%QX0.0.7" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.7_value_tmp_8bit" = load i8, ptr %"%QX0.0.7", align 1
  %54 = and i8 %"%QX0.0.7_value_tmp_8bit", 127
  %55 = zext i1 %53 to i8
  %56 = shl i8 %55, 7
  %57 = or i8 %54, %56
  store i8 %57, ptr %"%QX0.0.7", align 1
  ret void
}

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
