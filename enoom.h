#pragma once

namespace enoom
{

}

#define ENOOM_DECLARE(header_, seq_) namespace{} ENOOM_DECLARE_P(, header_, seq_)
#define ENOOM_DECLARE_IN_CLASS(header_, seq_) ENOOM_DECLARE_P(friend, header_, seq_)

#define ENOOM_DECLARE_P(prefix_, header_, seq_) IMPL_ENOOM_low(prefix_, header_, seq_, __COUNTER__)

#define IMPL_ENOOM_low(prefix_, header_, seq_, counter_) \
    header_ { IMPL_ENOOM_end(IMPL_ENOOM_decl_loop_a seq_) } \
    static constexpr IMPL_ENOOM_marker(counter_){}; \
    template <typename _enoom_T> prefix_ void _enoom_constants(_enoom_T &&_enoom_func) \
    { \
        using _enoom_enum = decltype(IMPL_ENOOM_marker(counter_)); \
        IMPL_ENOOM_end(IMPL_ENOOM_refl_loop_a seq_) \
    };


// The name of the marker variable we use to determine the enum type without parsing it with macros.
#define IMPL_ENOOM_marker(counter) IMPL_ENOOM_cat(_enoom_marker_, counter)

#define IMPL_ENOOM_null(...)
#define IMPL_ENOOM_str(...) IMPL_ENOOM_str_(__VA_ARGS__)
#define IMPL_ENOOM_str_(...) #__VA_ARGS__
#define IMPL_ENOOM_x_comma(...) x, // Just `,` doesn't work Clang with `-fms-compatibility`.
#define IMPL_ENOOM_cat(a, b) IMPL_ENOOM_cat_(a, b)
#define IMPL_ENOOM_cat_(a, b) a##b
#define IMPL_ENOOM_end(...) IMPL_ENOOM_end_(__VA_ARGS__)
#define IMPL_ENOOM_end_(...) __VA_ARGS__##_end
#define IMPL_ENOOM_end_front(...) IMPL_ENOOM_end_front_(__VA_ARGS__)
#define IMPL_ENOOM_end_front_(...) IMPL_ENOOM_end_##__VA_ARGS__

// Given `a`, expands to `a`. Or, given `(a)b`, expands to `b`.
#define IMPL_ENOOM_identifier(value) IMPL_ENOOM_end_front( IMPL_ENOOM_skip_name value )
#define IMPL_ENOOM_skip_name(name) IMPL_ENOOM_skipped_name
#define IMPL_ENOOM_end_IMPL_ENOOM_skip_name
#define IMPL_ENOOM_end_IMPL_ENOOM_skipped_name

// Given `a`, expands to `"a"`. Or, given `(a)b`, expands to `a` (without quotes).
#define IMPL_ENOOM_name_string(value) IMPL_ENOOM_end_front( IMPL_ENOOM_name_string_a value ) )
#define IMPL_ENOOM_name_string_a(value) IMPL_ENOOM_found(value)
#define IMPL_ENOOM_end_IMPL_ENOOM_name_string_a IMPL_ENOOM_str(
#define IMPL_ENOOM_end_IMPL_ENOOM_found(value) value IMPL_ENOOM_null(

// Given a sequence of `([("string")] name [, value])`, declares enum constants for it.
#define IMPL_ENOOM_decl_loop_a(...) IMPL_ENOOM_decl_loop_body(__VA_ARGS__) IMPL_ENOOM_decl_loop_b
#define IMPL_ENOOM_decl_loop_b(...) IMPL_ENOOM_decl_loop_body(__VA_ARGS__) IMPL_ENOOM_decl_loop_a
#define IMPL_ENOOM_decl_loop_a_end
#define IMPL_ENOOM_decl_loop_b_end
// Given `[("string")] name [, init]`, expands to `name [= init]`.
#define IMPL_ENOOM_decl_loop_body(...) IMPL_ENOOM_decl_loop_body_b(IMPL_ENOOM_decl_loop_body_a(__VA_ARGS__, IMPL_ENOOM_x_comma,))(__VA_ARGS__)
#define IMPL_ENOOM_decl_loop_body_a(a, b, ...) b()
#define IMPL_ENOOM_decl_loop_body_b(...) IMPL_ENOOM_decl_loop_body_c(__VA_ARGS__, IMPL_ENOOM_decl_loop_body_default, IMPL_ENOOM_decl_loop_body_custom,)
#define IMPL_ENOOM_decl_loop_body_c(a, b, c, ...) c
#define IMPL_ENOOM_decl_loop_body_default(name) name,
#define IMPL_ENOOM_decl_loop_body_custom(name, ...) IMPL_ENOOM_identifier(name) = __VA_ARGS__,

// Given a sequence of `([("string")] name [, value])`, expands to a sequence of `_enoom_func(...);` calls.
#define IMPL_ENOOM_refl_loop_a(...) IMPL_ENOOM_refl_loop_body(__VA_ARGS__,) IMPL_ENOOM_refl_loop_b
#define IMPL_ENOOM_refl_loop_b(...) IMPL_ENOOM_refl_loop_body(__VA_ARGS__,) IMPL_ENOOM_refl_loop_a
#define IMPL_ENOOM_refl_loop_a_end
#define IMPL_ENOOM_refl_loop_b_end
#define IMPL_ENOOM_refl_loop_body(name, ...) _enoom_func(_enoom_enum::IMPL_ENOOM_identifier(name), IMPL_ENOOM_name_string(name));




ENOOM_DECLARE(
    enum class A : int,
    (x)
    (y,2)
    (("z_custom")z,2)
)
