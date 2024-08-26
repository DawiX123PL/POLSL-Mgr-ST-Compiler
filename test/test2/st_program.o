; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc"

%main.struct = type <{ i1, double, double, i16 }>

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 19 }>, section "main.symbol_table"

define i1 @test_func(i16 %0, i16 %1, i16 %2, ptr %3, ptr %4) {
entry:
  %test_func.alloca = alloca i1, align 1
  %c.alloca = alloca i16, align 2
  %x.alloca = alloca i16, align 2
  %b1.alloca = alloca float, align 4
  %c1.alloca = alloca i16, align 2
  %b.alloca = alloca i16, align 2
  %aaa.alloca = alloca i16, align 2
  store i16 %0, ptr %aaa.alloca, align 2
  store i16 %1, ptr %b.alloca, align 2
  store i16 %2, ptr %c1.alloca, align 2
  %5 = icmp eq ptr %3, null
  br i1 %5, label %if_pointer_null, label %if_pointer_not_null

if_pointer_null:                                  ; preds = %entry
  br label %if_merge

if_pointer_not_null:                              ; preds = %entry
  %6 = load float, ptr %3, align 4
  br label %if_merge

if_merge:                                         ; preds = %if_pointer_not_null, %if_pointer_null
  %in_out_value = phi float [ %6, %if_pointer_not_null ], [ 0.000000e+00, %if_pointer_null ]
  store float %in_out_value, ptr %b1.alloca, align 4
  store i16 0, ptr %x.alloca, align 2
  store i16 0, ptr %c.alloca, align 2
  store i1 false, ptr %test_func.alloca, align 1
  br label %while_condition

while_condition:                                  ; preds = %while_do, %if_merge
  %c = load i16, ptr %c.alloca, align 2
  %7 = add i16 %c, 0
  %8 = icmp sgt i16 %7, 0
  br i1 %8, label %while_do, label %end_while

while_do:                                         ; preds = %while_condition
  %aaa = load i16, ptr %aaa.alloca, align 2
  %9 = sub i16 0, %aaa
  %b = load i16, ptr %b.alloca, align 2
  %10 = add i16 %9, %b
  %c1 = load i16, ptr %c1.alloca, align 2
  %11 = add i16 %10, %c1
  store i16 %11, ptr %x.alloca, align 2
  br label %while_condition

end_while:                                        ; preds = %while_condition
  br label %return_block

return_block:                                     ; preds = %end_while
  %is_not_null = icmp ne ptr %3, null
  br i1 %is_not_null, label %if_pointer_notnull, label %if_merge1

if_pointer_notnull:                               ; preds = %return_block
  %12 = load float, ptr %b1.alloca, align 4
  store float %12, ptr %3, align 4
  br label %if_merge1

if_merge1:                                        ; preds = %if_pointer_notnull, %return_block
  %is_not_null4 = icmp ne ptr %4, null
  br i1 %is_not_null4, label %if_pointer_notnull2, label %if_merge3

if_pointer_notnull2:                              ; preds = %if_merge1
  %13 = load i16, ptr %x.alloca, align 2
  store i16 %13, ptr %4, align 2
  br label %if_merge3

if_merge3:                                        ; preds = %if_pointer_notnull2, %if_merge1
  %result = load i1, ptr %test_func.alloca, align 1
  ret i1 %result
}

define double @fahrenheit_to_celsius(double %0) {
entry:
  %fahrenheit_to_celsius.alloca = alloca double, align 8
  %f.alloca = alloca double, align 8
  store double %0, ptr %f.alloca, align 8
  store double 0.000000e+00, ptr %fahrenheit_to_celsius.alloca, align 8
  %f = load double, ptr %f.alloca, align 8
  %1 = fsub double %f, 0.000000e+00
  %2 = fdiv double %1, 0.000000e+00
  store double %2, ptr %fahrenheit_to_celsius.alloca, align 8
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load double, ptr %fahrenheit_to_celsius.alloca, align 8
  ret double %result
}

define void @main.init(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  store i1 false, ptr %v1, align 1
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  store double 0.000000e+00, ptr %v2, align 8
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  store double 0.000000e+00, ptr %v3, align 8
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  store i16 0, ptr %v4, align 2
  ret void
}

define void @main(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  %v21 = load double, ptr %v2, align 8
  %v32 = load double, ptr %v3, align 8
  %1 = fcmp une double %v21, %v32
  store i1 %1, ptr %v1, align 1
  ret void
}
