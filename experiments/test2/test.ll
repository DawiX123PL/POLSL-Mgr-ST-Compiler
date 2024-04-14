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
  %1 = load i16, ptr %aaa_alloca, align 2
  %unary_minus_INT_result = sub i16 0, %1
  %2 = load i16, ptr %b_alloca, align 2
  %add_INT_result = add i16 %unary_minus_INT_result, %2
  %3 = load i16, ptr %c1_alloca, align 2
  %add_INT_result1 = add i16 %add_INT_result, %3
  store i16 %add_INT_result1, ptr %x_alloca, align 2
  %4 = load float, ptr %b1_alloca, align 4
  %add_REAL_result = fadd float %4, 0x3FB99999A0000000
  store float %add_REAL_result, ptr %b1_alloca, align 4
  %5 = load float, ptr %b1_alloca, align 4
  store float %5, ptr %b1, align 4
  %6 = load i16, ptr %x_alloca, align 2
  store i16 %6, ptr %x, align 2
  %7 = load i1, ptr %test_func_alloca, align 1
  store i1 %7, ptr %test_func, align 1
  ret void
}