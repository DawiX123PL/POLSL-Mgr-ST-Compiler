; ModuleID = 'test1.c'
source_filename = "test1.c"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc19.39.33523"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func1(i32 noundef %A, i32 noundef %B, ptr noundef %C, ptr noundef %D) #0 {

  ;; alokowanie stosu na zmienne (argumenty)
  %D_ALLOCA = alloca ptr, align 8
  %C_ALLOCA = alloca ptr, align 8
  %B_ALLOCA = alloca i32, align 4
  %A_ALLOCA = alloca i32, align 4

  ;; alokowanie stosu na zmienne lokalne
  %C1_ALLOCA = alloca i32, align 4
  %D1_ALLOCA = alloca i32, align 4

  ;; zapis argumentów do ich odpowiednikow na stosie
  store ptr %D, ptr %D_ALLOCA, align 8
  store ptr %C, ptr %C_ALLOCA, align 8
  store i32 %B, ptr %B_ALLOCA, align 4
  store i32 %A, ptr %A_ALLOCA, align 4

  ;;
  %11 = load ptr, ptr %C_ALLOCA, align 8 ;; pobranie wskaznika C do rejestru %11
  %12 = load i32, ptr %11, align 4       ;; pobranie zmiennej pod wskaznikiem %11 do rejestru %11
  store i32 %12, ptr %C1_ALLOCA, align 4 ;; zapisanie wyniku do %C1_ALLOCA

  %13 = load ptr, ptr %D_ALLOCA, align 8
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr %D1_ALLOCA, align 4

  ;; dodawanie
  %15 = load i32, ptr %A_ALLOCA, align 4 ;; pobranie zmiennej A do rejestru %15
  %16 = load i32, ptr %B_ALLOCA, align 4 ;; pobranie zmiennej B do rejestru %16
  %ADD_RESLUT = add nsw i32 %15, %16     ;; dodanie %ADD_RESLUT := %16 + %16
  
  ; zapisanie wyniku do pointera 
  %18 = load ptr, ptr %C_ALLOCA, align 8 ; 1) %18 := load c
  store i32 %ADD_RESLUT, ptr %18, align 4; 2) store %ADD_RESLUT -> %18

  ; zwrocenie wyniku
  %19 = load i32, ptr %A_ALLOCA, align 4
  ret i32 %19
}

attributes #0 = { noinline nounwind optnone uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 2}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 1, !"MaxTLSAlign", i32 65536}
!4 = !{!"clang version 18.1.1"}
