; ModuleID = 'output.ll'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

@"@ModuleDescription" = local_unnamed_addr constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 16 }>, section "main.symbol_table"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define noundef i1 @test_func(ptr nocapture readnone %0, i16 %1, i16 %2, i16 %3, ptr nocapture readnone %4, ptr writeonly %5) local_unnamed_addr #0 {
entry:
  %is_not_null4.not = icmp eq ptr %5, null
  br i1 %is_not_null4.not, label %if_merge3, label %if_pointer_notnull2

if_pointer_notnull2:                              ; preds = %entry
  store i16 0, ptr %5, align 2
  br label %if_merge3

if_merge3:                                        ; preds = %if_pointer_notnull2, %entry
  ret i1 false
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define double @fahrenheit_to_celsius(ptr nocapture readnone %0, double %1) local_unnamed_addr #1 {
entry:
  %2 = fadd double %1, -3.200000e+01
  %3 = fdiv double %2, 1.800000e+00
  ret double %3
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @main.init(ptr nocapture readnone %0, ptr nocapture writeonly %1) #0 {
entry:
  store i1 true, ptr %1, align 1
  %v2 = getelementptr inbounds i8, ptr %1, i32 1
  store double 1.100000e+00, ptr %v2, align 8
  %v3 = getelementptr inbounds i8, ptr %1, i32 9
  store double 2.137000e+03, ptr %v3, align 8
  %v4 = getelementptr inbounds i8, ptr %1, i32 13
  store i16 0, ptr %v4, align 2
  %v5 = getelementptr inbounds i8, ptr %1, i32 15
  store i1 false, ptr %v5, align 1
  ret void
}

define void @main(ptr %0, ptr nocapture readnone %1) {
entry:
  %"%QX0.1.0" = getelementptr i8, ptr %0, i32 321
  store i8 -1, ptr %"%QX0.1.0", align 1
  %"%IW1.2" = getelementptr i8, ptr %0, i32 66
  %"%IW1.2_value" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value")
  %2 = fcmp ugt float %FunctionCall, 0.000000e+00
  %"%QX0.0.0" = getelementptr i8, ptr %0, i32 320
  %"%QX0.0.0_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %3 = and i8 %"%QX0.0.0_value_tmp_8bit", -2
  %4 = zext i1 %2 to i8
  %5 = or disjoint i8 %3, %4
  store i8 %5, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value2" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall3 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value2")
  %6 = fcmp ugt float %FunctionCall3, 1.000000e+02
  %"%QX0.0.1_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %7 = and i8 %"%QX0.0.1_value_tmp_8bit", -3
  %8 = select i1 %6, i8 2, i8 0
  %9 = or disjoint i8 %7, %8
  store i8 %9, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value5" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall6 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value5")
  %10 = fcmp ugt float %FunctionCall6, 2.000000e+02
  %"%QX0.0.2_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %11 = and i8 %"%QX0.0.2_value_tmp_8bit", -5
  %12 = select i1 %10, i8 4, i8 0
  %13 = or disjoint i8 %11, %12
  store i8 %13, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value8" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall9 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value8")
  %14 = fcmp ugt float %FunctionCall9, 3.000000e+02
  %"%QX0.0.3_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %15 = and i8 %"%QX0.0.3_value_tmp_8bit", -9
  %16 = select i1 %14, i8 8, i8 0
  %17 = or disjoint i8 %15, %16
  store i8 %17, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value11" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall12 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value11")
  %18 = fcmp ugt float %FunctionCall12, 4.000000e+02
  %"%QX0.0.4_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %19 = and i8 %"%QX0.0.4_value_tmp_8bit", -17
  %20 = select i1 %18, i8 16, i8 0
  %21 = or disjoint i8 %19, %20
  store i8 %21, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value14" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall15 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value14")
  %22 = fcmp ugt float %FunctionCall15, 5.000000e+02
  %"%QX0.0.5_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %23 = and i8 %"%QX0.0.5_value_tmp_8bit", -33
  %24 = select i1 %22, i8 32, i8 0
  %25 = or disjoint i8 %23, %24
  store i8 %25, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value17" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall18 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value17")
  %26 = fcmp ugt float %FunctionCall18, 6.000000e+02
  %"%QX0.0.6_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %27 = and i8 %"%QX0.0.6_value_tmp_8bit", -65
  %28 = select i1 %26, i8 64, i8 0
  %29 = or disjoint i8 %27, %28
  store i8 %29, ptr %"%QX0.0.0", align 1
  %"%IW1.2_value20" = load i16, ptr %"%IW1.2", align 2
  %FunctionCall21 = tail call float @WORD_TO_REAL(ptr %0, i16 %"%IW1.2_value20")
  %30 = fcmp ugt float %FunctionCall21, 7.000000e+02
  %"%QX0.0.7_value_tmp_8bit" = load i8, ptr %"%QX0.0.0", align 1
  %31 = and i8 %"%QX0.0.7_value_tmp_8bit", 127
  %32 = select i1 %30, i8 -128, i8 0
  %33 = or disjoint i8 %31, %32
  store i8 %33, ptr %"%QX0.0.0", align 1
  ret void
}

declare float @WORD_TO_REAL(ptr, i16) local_unnamed_addr

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
