; ModuleID = '..\benchmark\build\optimize_lreal-O2\output.ll'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

@"@ModuleDescription" = local_unnamed_addr constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 8 }>, section "main.symbol_table"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define double @OptimizedFunction(ptr nocapture readnone %0, double %1, double %2) local_unnamed_addr #0 {
entry:
  %square = fmul double %1, %1
  %3 = fmul double %square, 6.000000e+00
  %4 = fmul double %3, %2
  %5 = fsub double %square, %4
  %6 = fmul double %1, 2.000000e+01
  %7 = fsub double %5, %6
  %square1 = fmul double %2, %2
  %8 = fmul double %square1, 3.000000e+00
  %9 = fadd double %8, %7
  %10 = tail call double @llvm.pow.f64(double %1, double 4.000000e+00)
  %11 = fmul double %10, 3.000000e+00
  %12 = fadd double %11, %9
  %13 = fadd double %12, 1.090000e+02
  ret double %13
}

; Function Attrs: nofree norecurse nosync nounwind memory(none)
define double @GradientSearchMin(ptr nocapture readnone %0, double %1, double %2, i16 %3) local_unnamed_addr #1 {
entry:
  %4 = icmp sgt i16 %3, -1
  br i1 %4, label %while_do, label %end_while

while_do:                                         ; preds = %entry, %while_do
  %iter.alloca.010 = phi i16 [ %5, %while_do ], [ %3, %entry ]
  %x1.alloca.09 = phi double [ %40, %while_do ], [ %1, %entry ]
  %x2.alloca.08 = phi double [ %41, %while_do ], [ %2, %entry ]
  %5 = add nsw i16 %iter.alloca.010, -1
  %square.i = fmul double %x1.alloca.09, %x1.alloca.09
  %6 = fmul double %square.i, 6.000000e+00
  %7 = fmul double %x2.alloca.08, %6
  %8 = fsub double %square.i, %7
  %9 = fmul double %x1.alloca.09, 2.000000e+01
  %10 = fsub double %8, %9
  %square1.i = fmul double %x2.alloca.08, %x2.alloca.08
  %11 = fmul double %square1.i, 3.000000e+00
  %12 = fadd double %11, %10
  %13 = tail call double @llvm.pow.f64(double %x1.alloca.09, double 4.000000e+00)
  %14 = fmul double %13, 3.000000e+00
  %15 = fadd double %14, %12
  %16 = fadd double %15, 1.090000e+02
  %17 = fadd double %x1.alloca.09, 1.000000e-03
  %square.i2 = fmul double %17, %17
  %18 = fmul double %square.i2, 6.000000e+00
  %19 = fmul double %x2.alloca.08, %18
  %20 = fsub double %square.i2, %19
  %21 = fmul double %17, 2.000000e+01
  %22 = fsub double %20, %21
  %23 = fadd double %11, %22
  %24 = tail call double @llvm.pow.f64(double %17, double 4.000000e+00)
  %25 = fmul double %24, 3.000000e+00
  %26 = fadd double %25, %23
  %27 = fadd double %26, 1.090000e+02
  %28 = fadd double %x2.alloca.08, 1.000000e-03
  %29 = fmul double %28, %6
  %30 = fsub double %square.i, %29
  %31 = fsub double %30, %9
  %square1.i5 = fmul double %28, %28
  %32 = fmul double %square1.i5, 3.000000e+00
  %33 = fadd double %32, %31
  %34 = fadd double %14, %33
  %35 = fadd double %34, 1.090000e+02
  %36 = fsub double %27, %16
  %37 = fdiv double %36, 1.000000e-03
  %38 = fsub double %35, %16
  %39 = fdiv double %38, 1.000000e-03
  %40 = fsub double %x1.alloca.09, %37
  %41 = fsub double %x2.alloca.08, %39
  %.not = icmp eq i16 %iter.alloca.010, 0
  br i1 %.not, label %end_while, label %while_do

end_while:                                        ; preds = %while_do, %entry
  %x2.alloca.0.lcssa = phi double [ %2, %entry ], [ %41, %while_do ]
  %x1.alloca.0.lcssa = phi double [ %1, %entry ], [ %40, %while_do ]
  %square.i6 = fmul double %x1.alloca.0.lcssa, %x1.alloca.0.lcssa
  %42 = fmul double %square.i6, 6.000000e+00
  %43 = fmul double %x2.alloca.0.lcssa, %42
  %44 = fsub double %square.i6, %43
  %45 = fmul double %x1.alloca.0.lcssa, 2.000000e+01
  %46 = fsub double %44, %45
  %square1.i7 = fmul double %x2.alloca.0.lcssa, %x2.alloca.0.lcssa
  %47 = fmul double %square1.i7, 3.000000e+00
  %48 = fadd double %47, %46
  %49 = tail call double @llvm.pow.f64(double %x1.alloca.0.lcssa, double 4.000000e+00)
  %50 = fmul double %49, 3.000000e+00
  %51 = fadd double %50, %48
  %52 = fadd double %51, 1.090000e+02
  ret double %52
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @main.init(ptr nocapture readnone %0, ptr nocapture writeonly %1) #2 {
entry:
  store double 0.000000e+00, ptr %1, align 8
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: write)
define void @main(ptr nocapture readnone %0, ptr nocapture writeonly %1) #3 {
entry:
  %FunctionCall = tail call double @GradientSearchMin(ptr poison, double 1.000000e+02, double 1.000000e+02, i16 1000)
  store double %FunctionCall, ptr %1, align 8
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #4

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
attributes #1 = { nofree norecurse nosync nounwind memory(none) }
attributes #2 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) }
attributes #3 = { nofree norecurse nosync nounwind memory(argmem: write) }
attributes #4 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
