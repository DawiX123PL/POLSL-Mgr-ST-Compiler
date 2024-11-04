; ModuleID = '..\benchmark\build\optimize_real-Oz\output.ll'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

@"@ModuleDescription" = local_unnamed_addr constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 4 }>, section "main.symbol_table"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define float @OptimizedFunction(ptr nocapture readnone %0, float %1, float %2) local_unnamed_addr #0 {
entry:
  %square = fmul float %1, %1
  %3 = fmul float %square, 6.000000e+00
  %4 = fmul float %3, %2
  %5 = fsub float %square, %4
  %6 = fmul float %1, 2.000000e+01
  %7 = fsub float %5, %6
  %square1 = fmul float %2, %2
  %8 = fmul float %square1, 3.000000e+00
  %9 = fadd float %8, %7
  %10 = tail call float @llvm.pow.f32(float %1, float 4.000000e+00)
  %11 = fmul float %10, 3.000000e+00
  %12 = fadd float %11, %9
  %13 = fadd float %12, 1.090000e+02
  ret float %13
}

; Function Attrs: nofree norecurse nosync nounwind memory(none)
define float @GradientSearchMin(ptr nocapture readnone %0, float %1, float %2, i16 %3) local_unnamed_addr #1 {
entry:
  br label %while_condition

while_condition:                                  ; preds = %while_do, %entry
  %x2.alloca.0 = phi float [ %2, %entry ], [ %13, %while_do ]
  %x1.alloca.0 = phi float [ %1, %entry ], [ %12, %while_do ]
  %iter.alloca.0 = phi i16 [ %3, %entry ], [ %5, %while_do ]
  %4 = icmp sgt i16 %iter.alloca.0, -1
  br i1 %4, label %while_do, label %end_while

while_do:                                         ; preds = %while_condition
  %5 = add nsw i16 %iter.alloca.0, -1
  %FunctionCall = tail call float @OptimizedFunction(ptr poison, float %x1.alloca.0, float %x2.alloca.0)
  %6 = fadd float %x1.alloca.0, 0x3F50624DE0000000
  %FunctionCall4 = tail call float @OptimizedFunction(ptr poison, float %6, float %x2.alloca.0)
  %7 = fadd float %x2.alloca.0, 0x3F50624DE0000000
  %FunctionCall8 = tail call float @OptimizedFunction(ptr poison, float %x1.alloca.0, float %7)
  %8 = fsub float %FunctionCall4, %FunctionCall
  %9 = fdiv float %8, 0x3F50624DE0000000
  %10 = fsub float %FunctionCall8, %FunctionCall
  %11 = fdiv float %10, 0x3F50624DE0000000
  %12 = fsub float %x1.alloca.0, %9
  %13 = fsub float %x2.alloca.0, %11
  br label %while_condition

end_while:                                        ; preds = %while_condition
  %FunctionCall17 = tail call float @OptimizedFunction(ptr poison, float %x1.alloca.0, float %x2.alloca.0)
  ret float %FunctionCall17
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @main.init(ptr nocapture readnone %0, ptr nocapture writeonly %1) #2 {
entry:
  store float 0.000000e+00, ptr %1, align 4
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: write)
define void @main(ptr nocapture readnone %0, ptr nocapture writeonly %1) #3 {
entry:
  %FunctionCall = tail call float @GradientSearchMin(ptr poison, float 1.000000e+02, float 1.000000e+02, i16 1000)
  store float %FunctionCall, ptr %1, align 4
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare float @llvm.pow.f32(float, float) #4

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
attributes #1 = { nofree norecurse nosync nounwind memory(none) }
attributes #2 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) }
attributes #3 = { nofree norecurse nosync nounwind memory(argmem: write) }
attributes #4 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
