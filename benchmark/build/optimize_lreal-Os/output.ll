; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

%main.struct = type <{ double }>

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 8 }>, section "main.symbol_table"

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

define double @OptimizedFunction(ptr %0, double %1, double %2) {
entry:
  %OptimizedFunction.alloca = alloca double, align 8
  %x2.alloca = alloca double, align 8
  %x1.alloca = alloca double, align 8
  store double %1, ptr %x1.alloca, align 8
  store double %2, ptr %x2.alloca, align 8
  store double 0.000000e+00, ptr %OptimizedFunction.alloca, align 8
  %x1 = load double, ptr %x1.alloca, align 8
  %3 = call double @llvm.pow.f64(double %x1, double 2.000000e+00)
  %x11 = load double, ptr %x1.alloca, align 8
  %4 = call double @llvm.pow.f64(double %x11, double 2.000000e+00)
  %5 = fmul double 6.000000e+00, %4
  %x2 = load double, ptr %x2.alloca, align 8
  %6 = fmul double %5, %x2
  %7 = fsub double %3, %6
  %x12 = load double, ptr %x1.alloca, align 8
  %8 = fmul double 2.000000e+01, %x12
  %9 = fsub double %7, %8
  %x23 = load double, ptr %x2.alloca, align 8
  %10 = call double @llvm.pow.f64(double %x23, double 2.000000e+00)
  %11 = fmul double 3.000000e+00, %10
  %12 = fadd double %9, %11
  %x14 = load double, ptr %x1.alloca, align 8
  %13 = call double @llvm.pow.f64(double %x14, double 4.000000e+00)
  %14 = fmul double 3.000000e+00, %13
  %15 = fadd double %12, %14
  %16 = fadd double %15, 1.090000e+02
  store double %16, ptr %OptimizedFunction.alloca, align 8
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load double, ptr %OptimizedFunction.alloca, align 8
  ret double %result
}

define double @GradientSearchMin(ptr %0, double %1, double %2, i16 %3) {
entry:
  %GradientSearchMin.alloca = alloca double, align 8
  %dy_dx2.alloca = alloca double, align 8
  %dy_dx1.alloca = alloca double, align 8
  %y2.alloca = alloca double, align 8
  %y1.alloca = alloca double, align 8
  %y.alloca = alloca double, align 8
  %alpha.alloca = alloca double, align 8
  %delta.alloca = alloca double, align 8
  %x2.alloca = alloca double, align 8
  %x1.alloca = alloca double, align 8
  %iter.alloca = alloca i16, align 2
  %x02.alloca = alloca double, align 8
  %x01.alloca = alloca double, align 8
  store double %1, ptr %x01.alloca, align 8
  store double %2, ptr %x02.alloca, align 8
  store i16 %3, ptr %iter.alloca, align 2
  store double 0.000000e+00, ptr %x1.alloca, align 8
  store double 0.000000e+00, ptr %x2.alloca, align 8
  store double 1.000000e-03, ptr %delta.alloca, align 8
  store double 1.000000e+00, ptr %alpha.alloca, align 8
  store double 0.000000e+00, ptr %y.alloca, align 8
  store double 0.000000e+00, ptr %y1.alloca, align 8
  store double 0.000000e+00, ptr %y2.alloca, align 8
  store double 0.000000e+00, ptr %dy_dx1.alloca, align 8
  store double 0.000000e+00, ptr %dy_dx2.alloca, align 8
  store double 0.000000e+00, ptr %GradientSearchMin.alloca, align 8
  %x01 = load double, ptr %x01.alloca, align 8
  store double %x01, ptr %x1.alloca, align 8
  %x02 = load double, ptr %x02.alloca, align 8
  store double %x02, ptr %x2.alloca, align 8
  br label %while_condition

while_condition:                                  ; preds = %while_do, %entry
  %iter = load i16, ptr %iter.alloca, align 2
  %4 = icmp sge i16 %iter, 0
  br i1 %4, label %while_do, label %end_while

while_do:                                         ; preds = %while_condition
  %iter1 = load i16, ptr %iter.alloca, align 2
  %5 = sub i16 %iter1, 1
  store i16 %5, ptr %iter.alloca, align 2
  %x1 = load double, ptr %x1.alloca, align 8
  %x2 = load double, ptr %x2.alloca, align 8
  %FunctionCall = call double @OptimizedFunction(ptr %0, double %x1, double %x2)
  store double %FunctionCall, ptr %y.alloca, align 8
  %x12 = load double, ptr %x1.alloca, align 8
  %delta = load double, ptr %delta.alloca, align 8
  %6 = fadd double %x12, %delta
  %x23 = load double, ptr %x2.alloca, align 8
  %FunctionCall4 = call double @OptimizedFunction(ptr %0, double %6, double %x23)
  store double %FunctionCall4, ptr %y1.alloca, align 8
  %x15 = load double, ptr %x1.alloca, align 8
  %x26 = load double, ptr %x2.alloca, align 8
  %delta7 = load double, ptr %delta.alloca, align 8
  %7 = fadd double %x26, %delta7
  %FunctionCall8 = call double @OptimizedFunction(ptr %0, double %x15, double %7)
  store double %FunctionCall8, ptr %y2.alloca, align 8
  %y1 = load double, ptr %y1.alloca, align 8
  %y = load double, ptr %y.alloca, align 8
  %8 = fsub double %y1, %y
  %delta9 = load double, ptr %delta.alloca, align 8
  %9 = fdiv double %8, %delta9
  store double %9, ptr %dy_dx1.alloca, align 8
  %y2 = load double, ptr %y2.alloca, align 8
  %y10 = load double, ptr %y.alloca, align 8
  %10 = fsub double %y2, %y10
  %delta11 = load double, ptr %delta.alloca, align 8
  %11 = fdiv double %10, %delta11
  store double %11, ptr %dy_dx2.alloca, align 8
  %x112 = load double, ptr %x1.alloca, align 8
  %alpha = load double, ptr %alpha.alloca, align 8
  %dy_dx1 = load double, ptr %dy_dx1.alloca, align 8
  %12 = fmul double %alpha, %dy_dx1
  %13 = fsub double %x112, %12
  store double %13, ptr %x1.alloca, align 8
  %x213 = load double, ptr %x2.alloca, align 8
  %alpha14 = load double, ptr %alpha.alloca, align 8
  %dy_dx2 = load double, ptr %dy_dx2.alloca, align 8
  %14 = fmul double %alpha14, %dy_dx2
  %15 = fsub double %x213, %14
  store double %15, ptr %x2.alloca, align 8
  br label %while_condition

end_while:                                        ; preds = %while_condition
  %x115 = load double, ptr %x1.alloca, align 8
  %x216 = load double, ptr %x2.alloca, align 8
  %FunctionCall17 = call double @OptimizedFunction(ptr %0, double %x115, double %x216)
  store double %FunctionCall17, ptr %GradientSearchMin.alloca, align 8
  br label %return_block

return_block:                                     ; preds = %end_while
  %result = load double, ptr %GradientSearchMin.alloca, align 8
  ret double %result
}

define void @main.init(ptr %0, ptr %1) {
entry:
  %minimum = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  store double 0.000000e+00, ptr %minimum, align 8
  ret void
}

define void @main(ptr %0, ptr %1) {
entry:
  %minimum = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  %FunctionCall = call double @GradientSearchMin(ptr %0, double 1.000000e+02, double 1.000000e+02, i16 1000)
  store double %FunctionCall, ptr %minimum, align 8
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #0

attributes #0 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
