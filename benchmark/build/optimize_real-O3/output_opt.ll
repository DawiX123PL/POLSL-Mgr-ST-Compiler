; ModuleID = '..\benchmark\build\optimize_real-O3\output.ll'
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
  %4 = icmp sgt i16 %3, -1
  br i1 %4, label %while_do, label %end_while

while_do:                                         ; preds = %entry, %while_do
  %iter.alloca.010 = phi i16 [ %5, %while_do ], [ %3, %entry ]
  %x1.alloca.09 = phi float [ %40, %while_do ], [ %1, %entry ]
  %x2.alloca.08 = phi float [ %41, %while_do ], [ %2, %entry ]
  %5 = add nsw i16 %iter.alloca.010, -1
  %square.i = fmul float %x1.alloca.09, %x1.alloca.09
  %6 = fmul float %square.i, 6.000000e+00
  %7 = fmul float %x2.alloca.08, %6
  %8 = fsub float %square.i, %7
  %9 = fmul float %x1.alloca.09, 2.000000e+01
  %10 = fsub float %8, %9
  %square1.i = fmul float %x2.alloca.08, %x2.alloca.08
  %11 = fmul float %square1.i, 3.000000e+00
  %12 = fadd float %11, %10
  %13 = tail call float @llvm.pow.f32(float %x1.alloca.09, float 4.000000e+00)
  %14 = fmul float %13, 3.000000e+00
  %15 = fadd float %14, %12
  %16 = fadd float %15, 1.090000e+02
  %17 = fadd float %x1.alloca.09, 0x3F50624DE0000000
  %square.i2 = fmul float %17, %17
  %18 = fmul float %square.i2, 6.000000e+00
  %19 = fmul float %x2.alloca.08, %18
  %20 = fsub float %square.i2, %19
  %21 = fmul float %17, 2.000000e+01
  %22 = fsub float %20, %21
  %23 = fadd float %11, %22
  %24 = tail call float @llvm.pow.f32(float %17, float 4.000000e+00)
  %25 = fmul float %24, 3.000000e+00
  %26 = fadd float %25, %23
  %27 = fadd float %26, 1.090000e+02
  %28 = fadd float %x2.alloca.08, 0x3F50624DE0000000
  %29 = fmul float %28, %6
  %30 = fsub float %square.i, %29
  %31 = fsub float %30, %9
  %square1.i5 = fmul float %28, %28
  %32 = fmul float %square1.i5, 3.000000e+00
  %33 = fadd float %32, %31
  %34 = fadd float %14, %33
  %35 = fadd float %34, 1.090000e+02
  %36 = fsub float %27, %16
  %37 = fdiv float %36, 0x3F50624DE0000000
  %38 = fsub float %35, %16
  %39 = fdiv float %38, 0x3F50624DE0000000
  %40 = fsub float %x1.alloca.09, %37
  %41 = fsub float %x2.alloca.08, %39
  %.not = icmp eq i16 %iter.alloca.010, 0
  br i1 %.not, label %end_while, label %while_do

end_while:                                        ; preds = %while_do, %entry
  %x2.alloca.0.lcssa = phi float [ %2, %entry ], [ %41, %while_do ]
  %x1.alloca.0.lcssa = phi float [ %1, %entry ], [ %40, %while_do ]
  %square.i6 = fmul float %x1.alloca.0.lcssa, %x1.alloca.0.lcssa
  %42 = fmul float %square.i6, 6.000000e+00
  %43 = fmul float %x2.alloca.0.lcssa, %42
  %44 = fsub float %square.i6, %43
  %45 = fmul float %x1.alloca.0.lcssa, 2.000000e+01
  %46 = fsub float %44, %45
  %square1.i7 = fmul float %x2.alloca.0.lcssa, %x2.alloca.0.lcssa
  %47 = fmul float %square1.i7, 3.000000e+00
  %48 = fadd float %47, %46
  %49 = tail call float @llvm.pow.f32(float %x1.alloca.0.lcssa, float 4.000000e+00)
  %50 = fmul float %49, 3.000000e+00
  %51 = fadd float %50, %48
  %52 = fadd float %51, 1.090000e+02
  ret float %52
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
  br label %while_do.i

while_do.i:                                       ; preds = %while_do.i, %entry
  %iter.alloca.010.i = phi i16 [ %2, %while_do.i ], [ 1000, %entry ]
  %x1.alloca.09.i = phi float [ %37, %while_do.i ], [ 1.000000e+02, %entry ]
  %x2.alloca.08.i = phi float [ %38, %while_do.i ], [ 1.000000e+02, %entry ]
  %2 = add nsw i16 %iter.alloca.010.i, -1
  %square.i.i = fmul float %x1.alloca.09.i, %x1.alloca.09.i
  %3 = fmul float %square.i.i, 6.000000e+00
  %4 = fmul float %x2.alloca.08.i, %3
  %5 = fsub float %square.i.i, %4
  %6 = fmul float %x1.alloca.09.i, 2.000000e+01
  %7 = fsub float %5, %6
  %square1.i.i = fmul float %x2.alloca.08.i, %x2.alloca.08.i
  %8 = fmul float %square1.i.i, 3.000000e+00
  %9 = fadd float %8, %7
  %10 = tail call float @llvm.pow.f32(float %x1.alloca.09.i, float 4.000000e+00)
  %11 = fmul float %10, 3.000000e+00
  %12 = fadd float %11, %9
  %13 = fadd float %12, 1.090000e+02
  %14 = fadd float %x1.alloca.09.i, 0x3F50624DE0000000
  %square.i2.i = fmul float %14, %14
  %15 = fmul float %square.i2.i, 6.000000e+00
  %16 = fmul float %x2.alloca.08.i, %15
  %17 = fsub float %square.i2.i, %16
  %18 = fmul float %14, 2.000000e+01
  %19 = fsub float %17, %18
  %20 = fadd float %8, %19
  %21 = tail call float @llvm.pow.f32(float %14, float 4.000000e+00)
  %22 = fmul float %21, 3.000000e+00
  %23 = fadd float %22, %20
  %24 = fadd float %23, 1.090000e+02
  %25 = fadd float %x2.alloca.08.i, 0x3F50624DE0000000
  %26 = fmul float %25, %3
  %27 = fsub float %square.i.i, %26
  %28 = fsub float %27, %6
  %square1.i5.i = fmul float %25, %25
  %29 = fmul float %square1.i5.i, 3.000000e+00
  %30 = fadd float %29, %28
  %31 = fadd float %11, %30
  %32 = fadd float %31, 1.090000e+02
  %33 = fsub float %24, %13
  %34 = fdiv float %33, 0x3F50624DE0000000
  %35 = fsub float %32, %13
  %36 = fdiv float %35, 0x3F50624DE0000000
  %37 = fsub float %x1.alloca.09.i, %34
  %38 = fsub float %x2.alloca.08.i, %36
  %.not.i = icmp eq i16 %iter.alloca.010.i, 0
  br i1 %.not.i, label %GradientSearchMin.exit, label %while_do.i

GradientSearchMin.exit:                           ; preds = %while_do.i
  %square.i6.i = fmul float %37, %37
  %39 = fmul float %square.i6.i, 6.000000e+00
  %40 = fmul float %38, %39
  %41 = fsub float %square.i6.i, %40
  %42 = fmul float %37, 2.000000e+01
  %43 = fsub float %41, %42
  %square1.i7.i = fmul float %38, %38
  %44 = fmul float %square1.i7.i, 3.000000e+00
  %45 = fadd float %44, %43
  %46 = tail call float @llvm.pow.f32(float %37, float 4.000000e+00)
  %47 = fmul float %46, 3.000000e+00
  %48 = fadd float %47, %45
  %49 = fadd float %48, 1.090000e+02
  store float %49, ptr %1, align 4
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare float @llvm.pow.f32(float, float) #4

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
attributes #1 = { nofree norecurse nosync nounwind memory(none) }
attributes #2 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) }
attributes #3 = { nofree norecurse nosync nounwind memory(argmem: write) }
attributes #4 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
