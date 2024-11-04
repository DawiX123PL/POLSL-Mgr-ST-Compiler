; ModuleID = '..\benchmark\build\empty-O3\output.ll'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabi"

@"@ModuleDescription" = local_unnamed_addr constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 0 }>, section "main.symbol_table"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define void @main.init(ptr nocapture readnone %0, ptr nocapture readnone %1) #0 {
entry:
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define void @main(ptr nocapture readnone %0, ptr nocapture readnone %1) #0 {
entry:
  ret void
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
