; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"

define void @test_func(i16 %aaa, i16 %b, i16 %c1, ptr %b1, ptr %x, ptr %test_func) {
entry:
  %test_func_alloca = alloca i1, align 1
  %c_alloca = alloca i16, align 2
  %x_alloca = alloca i16, align 2
  %b1_alloca = alloca float, align 4
  %c1_alloca = alloca i16, align 2
  %b_alloca = alloca i16, align 2
  %aaa_alloca = alloca i16, align 2
  store i16 zeroinitializer, ptr %x_alloca, align 2
  store i16 256, ptr %c_alloca, align 2
  store i1 zeroinitializer, ptr %test_func_alloca, align 1
  store i16 %aaa, ptr %aaa_alloca, align 2
  store i16 %b, ptr %b_alloca, align 2
  store i16 %c1, ptr %c1_alloca, align 2
  %0 = load float, ptr %b1, align 4
  store float %0, ptr %b1_alloca, align 4
  store i1 true, ptr %test_func_alloca, align 1
  %1 = load float, ptr %b1_alloca, align 4
  store float %1, ptr %b1, align 4
  %2 = load i16, ptr %x_alloca, align 2
  store i16 %2, ptr %x, align 2
  %3 = load i1, ptr %test_func_alloca, align 1
  store i1 %3, ptr %test_func, align 1
  ret void
}
