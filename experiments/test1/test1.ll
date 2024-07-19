; ModuleID = 'test1.c'
source_filename = "test1.c"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc19.39.33523"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @fahrenheit_to_celsius(float noundef %0) #0 {
  %2 = alloca float, align 4
  %3 = alloca float, align 4
  store float %0, ptr %2, align 4
  %4 = load float, ptr %2, align 4
  %5 = fsub float %4, 3.200000e+01
  %6 = fpext float %5 to double
  %7 = fdiv double %6, 1.800000e+00
  %8 = fptrunc double %7 to float
  store float %8, ptr %3, align 4
  %9 = load float, ptr %3, align 4
  %10 = fptosi float %9 to i32
  ret i32 %10
}

attributes #0 = { noinline nounwind optnone uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 2}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 1, !"MaxTLSAlign", i32 65536}
!4 = !{!"clang version 18.1.1"}
