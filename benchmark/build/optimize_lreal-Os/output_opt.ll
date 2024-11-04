; ModuleID = '..\benchmark\build\optimize_lreal-Os\output.ll'
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
  %iter.alloca.04 = phi i16 [ %5, %while_do ], [ %3, %entry ]
  %x1.alloca.03 = phi double [ %12, %while_do ], [ %1, %entry ]
  %x2.alloca.02 = phi double [ %13, %while_do ], [ %2, %entry ]
  %5 = add nsw i16 %iter.alloca.04, -1
  %FunctionCall = tail call double @OptimizedFunction(ptr poison, double %x1.alloca.03, double %x2.alloca.02)
  %6 = fadd double %x1.alloca.03, 1.000000e-03
  %FunctionCall4 = tail call double @OptimizedFunction(ptr poison, double %6, double %x2.alloca.02)
  %7 = fadd double %x2.alloca.02, 1.000000e-03
  %FunctionCall8 = tail call double @OptimizedFunction(ptr poison, double %x1.alloca.03, double %7)
  %8 = fsub double %FunctionCall4, %FunctionCall
  %9 = fdiv double %8, 1.000000e-03
  %10 = fsub double %FunctionCall8, %FunctionCall
  %11 = fdiv double %10, 1.000000e-03
  %12 = fsub double %x1.alloca.03, %9
  %13 = fsub double %x2.alloca.02, %11
  %.not = icmp eq i16 %iter.alloca.04, 0
  br i1 %.not, label %end_while, label %while_do

end_while:                                        ; preds = %while_do, %entry
  %x2.alloca.0.lcssa = phi double [ %2, %entry ], [ %13, %while_do ]
  %x1.alloca.0.lcssa = phi double [ %1, %entry ], [ %12, %while_do ]
  %FunctionCall17 = tail call double @OptimizedFunction(ptr poison, double %x1.alloca.0.lcssa, double %x2.alloca.0.lcssa)
  ret double %FunctionCall17
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
