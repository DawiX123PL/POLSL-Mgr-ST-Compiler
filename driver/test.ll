; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv7em-none-unknown-eabihf"

%main.struct = type { i1, float, float, i16 }

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 16 }>

define float @fahrenheit_to_celsius(float %0) {
entry:
  %fahrenheit_to_celsius.alloca = alloca float, align 4
  %f.alloca = alloca float, align 4
  store float %0, ptr %f.alloca, align 4
  store float 0.000000e+00, ptr %fahrenheit_to_celsius.alloca, align 4
  %f = load float, ptr %f.alloca, align 4
  %1 = fsub float %f, 0.000000e+00
  %2 = fdiv float %1, 0.000000e+00
  store float %2, ptr %fahrenheit_to_celsius.alloca, align 4
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load float, ptr %fahrenheit_to_celsius.alloca, align 4
  ret float %result
}

define void @main.init(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  store i1 false, ptr %v1, align 1
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %v2, align 4
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  store float 0.000000e+00, ptr %v3, align 4
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  store i16 0, ptr %v4, align 2
  ret void
}

define void @main(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  %v21 = load float, ptr %v2, align 4
  %v32 = load float, ptr %v3, align 4
  %1 = fcmp une float %v21, %v32
  store i1 %1, ptr %v1, align 1
  ret void
}