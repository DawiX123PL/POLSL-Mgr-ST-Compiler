; ModuleID = 'test1.c'
source_filename = "test1.c"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @func1(i32 noundef %a, i32 noundef %b, ptr noundef %c) #0 {
entry:
  %c.addr = alloca ptr, align 8
  %b.addr = alloca i32, align 4
  %a.addr = alloca i32, align 4
  store ptr %c, ptr %c.addr, align 8
  store i32 %b, ptr %b.addr, align 4
  store i32 %a, ptr %a.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %1 = load i32, ptr %b.addr, align 4
  %add = add nsw i32 %0, %1
  %2 = load ptr, ptr %c.addr, align 8
  store i32 %add, ptr %2, align 4
  %3 = load i32, ptr %a.addr, align 4
  ret i32 %3
}

attributes #0 = { noinline nounwind optnone "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 2}
!1 = !{i32 1, !"MaxTLSAlign", i32 65536}
!2 = !{!"clang version 18.1.1"}
