; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc"

%main.struct = type <{ i1 }>

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 1 }>, section "main.symbol_table"

define i16 @AddNumbers(ptr %0, i16 %1, i16 %2) {
entry:
  %AddNumbers.alloca = alloca i16, align 2
  %b.alloca = alloca i16, align 2
  %a.alloca = alloca i16, align 2
  store i16 %1, ptr %a.alloca, align 2
  store i16 %2, ptr %b.alloca, align 2
  store i16 0, ptr %AddNumbers.alloca, align 2
  %a = load i16, ptr %a.alloca, align 2
  %b = load i16, ptr %b.alloca, align 2
  %3 = add i16 %a, %b
  store i16 %3, ptr %AddNumbers.alloca, align 2
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load i16, ptr %AddNumbers.alloca, align 2
  ret i16 %result
}

define i16 @AddAndModify(ptr %0, i16 %1, i16 %2, ptr %3, ptr %4) {
entry:
  %AddAndModify.alloca = alloca i16, align 2
  %sum.alloca = alloca i16, align 2
  %modifier.alloca = alloca i16, align 2
  %b.alloca = alloca i16, align 2
  %a.alloca = alloca i16, align 2
  store i16 %1, ptr %a.alloca, align 2
  store i16 %2, ptr %b.alloca, align 2
  %5 = icmp eq ptr %3, null
  br i1 %5, label %if_pointer_null, label %if_pointer_not_null

if_pointer_null:                                  ; preds = %entry
  br label %if_merge

if_pointer_not_null:                              ; preds = %entry
  %6 = load i16, ptr %3, align 2
  br label %if_merge

if_merge:                                         ; preds = %if_pointer_not_null, %if_pointer_null
  %in_out_value = phi i16 [ %6, %if_pointer_not_null ], [ 0, %if_pointer_null ]
  store i16 %in_out_value, ptr %modifier.alloca, align 2
  store i16 0, ptr %sum.alloca, align 2
  store i16 0, ptr %AddAndModify.alloca, align 2
  %a = load i16, ptr %a.alloca, align 2
  %b = load i16, ptr %b.alloca, align 2
  %7 = add i16 %a, %b
  store i16 %7, ptr %sum.alloca, align 2
  %modifier = load i16, ptr %modifier.alloca, align 2
  %8 = add i16 %modifier, 1
  store i16 %8, ptr %modifier.alloca, align 2
  %sum = load i16, ptr %sum.alloca, align 2
  %modifier1 = load i16, ptr %modifier.alloca, align 2
  %9 = add i16 %sum, %modifier1
  store i16 %9, ptr %AddAndModify.alloca, align 2
  br label %return_block

return_block:                                     ; preds = %if_merge
  %is_not_null = icmp ne ptr %3, null
  br i1 %is_not_null, label %if_pointer_notnull, label %if_merge2

if_pointer_notnull:                               ; preds = %return_block
  %10 = load i16, ptr %modifier.alloca, align 2
  store i16 %10, ptr %3, align 2
  br label %if_merge2

if_merge2:                                        ; preds = %if_pointer_notnull, %return_block
  %is_not_null5 = icmp ne ptr %4, null
  br i1 %is_not_null5, label %if_pointer_notnull3, label %if_merge4

if_pointer_notnull3:                              ; preds = %if_merge2
  %11 = load i16, ptr %sum.alloca, align 2
  store i16 %11, ptr %4, align 2
  br label %if_merge4

if_merge4:                                        ; preds = %if_pointer_notnull3, %if_merge2
  %result = load i16, ptr %AddAndModify.alloca, align 2
  ret i16 %result
}

define i16 @ModifyAndOutput(ptr %0, ptr %1, ptr %2) {
entry:
  %ModifyAndOutput.alloca = alloca i16, align 2
  %result.alloca = alloca i16, align 2
  %value.alloca = alloca i16, align 2
  %3 = icmp eq ptr %1, null
  br i1 %3, label %if_pointer_null, label %if_pointer_not_null

if_pointer_null:                                  ; preds = %entry
  br label %if_merge

if_pointer_not_null:                              ; preds = %entry
  %4 = load i16, ptr %1, align 2
  br label %if_merge

if_merge:                                         ; preds = %if_pointer_not_null, %if_pointer_null
  %in_out_value = phi i16 [ %4, %if_pointer_not_null ], [ 0, %if_pointer_null ]
  store i16 %in_out_value, ptr %value.alloca, align 2
  store i16 0, ptr %result.alloca, align 2
  store i16 0, ptr %ModifyAndOutput.alloca, align 2
  store i16 10, ptr %value.alloca, align 2
  store i16 10, ptr %result.alloca, align 2
  store i16 10, ptr %ModifyAndOutput.alloca, align 2
  br label %return_block

return_block:                                     ; preds = %if_merge
  %is_not_null = icmp ne ptr %1, null
  br i1 %is_not_null, label %if_pointer_notnull, label %if_merge1

if_pointer_notnull:                               ; preds = %return_block
  %5 = load i16, ptr %value.alloca, align 2
  store i16 %5, ptr %1, align 2
  br label %if_merge1

if_merge1:                                        ; preds = %if_pointer_notnull, %return_block
  %is_not_null4 = icmp ne ptr %2, null
  br i1 %is_not_null4, label %if_pointer_notnull2, label %if_merge3

if_pointer_notnull2:                              ; preds = %if_merge1
  %6 = load i16, ptr %result.alloca, align 2
  store i16 %6, ptr %2, align 2
  br label %if_merge3

if_merge3:                                        ; preds = %if_pointer_notnull2, %if_merge1
  %result = load i16, ptr %ModifyAndOutput.alloca, align 2
  ret i16 %result
}

define void @main.init(ptr %0, ptr %1) {
entry:
  %Variable = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  store i1 false, ptr %Variable, align 1
  ret void
}

define void @main(ptr %0, ptr %1) {
entry:
  %Variable = getelementptr inbounds %main.struct, ptr %1, i32 0, i32 0
  %"%QX0.0.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 1, i32 0, i32 0
  %"%QX0.0.0_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %"%QX0.0.0_value_8bit" = and i8 %"%QX0.0.0_value_tmp_8bit", 1
  %"%QX0.0.0_value" = icmp ne i8 %"%QX0.0.0_value_8bit", 0
  %"%MX0.0" = getelementptr <{ [5 x [64 x i8]], [5 x [64 x i8]], [1024 x i8] }>, ptr %0, i32 0, i32 2, i32 0
  %"%MX0.0_value_tmp_8bit" = load i8, ptr %"%MX0.0", align 1
  %2 = and i8 %"%MX0.0_value_tmp_8bit", -2
  %3 = zext i1 %"%QX0.0.0_value" to i8
  %4 = shl i8 %3, 0
  %5 = or i8 %2, %4
  store i8 %5, ptr %"%MX0.0", align 1
  ret void
}
