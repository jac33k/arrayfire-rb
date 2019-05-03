#include "arrayfire_rb.h"

using namespace Rice;
using namespace af;

class AfArray {
  private:
    array c_array;

  public:
    AfArray(af_array afarray);
    AfArray(array afarray);
    AfArray(Array dimensions, Array elements, Symbol data_type);
    void print();
    AfArray* multiply(Object other);
    AfArray* multiply_assign(Object other);
    AfArray* add(Object other);
    AfArray* add_assign(Object other);
    AfArray* div(Object other);
    AfArray* div_assign(Object other);
    AfArray* sub(Object other);
    AfArray* sub_assign(Object other);
    static AfArray* randu(Array dimensions, Symbol data_type);
    static AfArray* randn(Array dimensions, Symbol data_type);
    static AfArray* constant(Object value, Array dimensions, Symbol data_type);
    static AfArray* range(int seq_dim, Array dimensions, Symbol data_type);
    static void set_seed(int seed);
    static int get_seed();
    AfArray* row(int index);
    AfArray* rows(int first, int last);
    AfArray* col(int index);
    AfArray* cols(int first, int last);
    AfArray* slice(int index);
    AfArray* slices(int first, int last);
    AfArray* lookup(Array idx);
    AfArray* real();
    AfArray* imag();
    AfArray* conjg();
    AfArray* diag(int num = 0, bool extract = true);
    AfArray* lower(bool is_unit_diag = false);
    AfArray* upper(bool is_unit_diag = false);
    AfArray* cast(Symbol data_type);
    AfArray* as(Symbol data_type);
    AfArray* is_nan();
    AfArray* is_inf();
    AfArray* is_zero();
    size_t allocated();
    size_t bytes();
    AfArray* copy();
    Array dims();
    int elements();
    int numdims();
    AfArray* H();
    AfArray* transposed();
    Symbol type();
    Object scalar();
    bool isbool();
    bool iscolumn();
    bool iscomplex();
    bool isdouble();
    bool isempty();
    bool isfloating();
    bool isinteger();
    bool isreal();
    bool isrealfloating();
    bool isrow();
    bool isscalar();
    bool issingle();
    bool issparse();
    bool isvector();
    AfArray* flat();
    AfArray* flip(uint dimension);
    AfArray* join(int dimension, Array arrays);
    AfArray* moddims(Array dimensions);
    AfArray* reorder(int x, int y = 1, int z = 2, int w = 3);
    AfArray* replace(AfArray conditions, Object replacement);
    AfArray* select(AfArray conditions, Object otherwise);
    AfArray* shift(int x, int y = 0, int z = 0, int w = 0);
    AfArray* tile(int x, int y = 1, int z = 1, int w = 1);
    AfArray* transpose(bool conjugate = false);
    float dot(AfArray other, Symbol opt_lhs = "mat_none", Symbol opt_rhs = "mat_none");
    AfArray* matmul(AfArray other, Symbol opt_lhs = "mat_none", Symbol opt_rhs = "mat_none");
    AfArray* solve(AfArray other, Symbol opts = "mat_none");
    static AfArray* solveLU(AfArray a, AfArray pivot, AfArray b, Symbol opts = "mat_none");
    AfArray* cholesky(bool is_upper = true);
    Array lu();
    Array qr();
    Array svd();
    Object det();
    AfArray* inverse(Symbol opts = "mat_none");
    double norm(double p, double q, Symbol norm_type = "norm_euclid");
    unsigned rank(double tolerance = 1E-5);
    AfArray* cbrt();
    AfArray* erf();
    AfArray* erfc();
    AfArray* exp();
    AfArray* expm1();
    AfArray* factorial();
    AfArray* lgamma();
    AfArray* tgamma();
    AfArray* log();
    AfArray* log10();
    AfArray* log1p();
    AfArray* pow(Object other);
    AfArray* pow2();
    AfArray* root(Object other);
    AfArray* sqrt();
    AfArray* acosh();
    AfArray* asinh();
    AfArray* atanh();
    AfArray* cosh();
    AfArray* sinh();
    AfArray* tanh();
    static AfArray* identity(Array dimensions, Symbol data_type);
    static AfArray* iota(Array dimensions, Array tile_dimensions, Symbol data_type);
    static AfArray* create_strided_array(Array elements, Array dimensions, int offset, Array strides, Symbol data_type, Symbol source);
    AfArray* bit_and(Object other);
    AfArray* bit_or(Object other);
    AfArray* bit_xor(Object other);
    AfArray* eq(Object other);
    AfArray* neq(Object other);
    AfArray* logical_and(Object other);
    AfArray* logical_or(Object other);
    AfArray* neg();
    AfArray* logical_not();
    AfArray* gt(Object other);
    AfArray* lt(Object other);
    AfArray* ge(Object other);
    AfArray* le(Object other);
    AfArray* abs();

  private:
    array get_c_array();
    static dim4 ruby_array_to_dimensions(Array dimensions);
    static int* ruby_array_to_ints(Array rb_array);
    Array dimensions_to_ruby_array(dim4 dimensions);
    void set_c_array(af_array afarray);
    void set_c_array(const array& afarray);
    AfArray* multiply_internal(AfArray other);
    AfArray* multiply_internal(int value);
    AfArray* multiply_assign_internal(AfArray other);
    AfArray* multiply_assign_internal(int value);
    AfArray* add_internal(AfArray other);
    AfArray* add_internal(int value);
    AfArray* add_assign_internal(AfArray other);
    AfArray* add_assign_internal(int value);
    AfArray* div_internal(AfArray other);
    AfArray* div_internal(int value);
    AfArray* div_assign_internal(AfArray other);
    AfArray* div_assign_internal(int value);
    AfArray* sub_internal(AfArray other);
    AfArray* sub_internal(int value);
    AfArray* sub_assign_internal(AfArray other);
    AfArray* sub_assign_internal(int value);
    AfArray* pow_internal(AfArray other);
    AfArray* pow_internal(double value);
    AfArray* root_internal(AfArray other);
    AfArray* root_internal(double value);
    template<typename T> void create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_long(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_short(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_ushort(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> static T cast_ruby_to(Object ruby_object);
    template<typename T> static T cast_ruby_to_long(Object ruby_object);
    template<typename T> static T cast_ruby_to_complex(Object ruby_object);
    template<typename T> static T cast_ruby_to_short(Object ruby_object);
    template<typename T> static T cast_ruby_to_ushort(Object ruby_object);
    template<typename T> static T* cast_ruby_array_to(Array elements);
    template<typename T> static T* cast_ruby_array_to_long(Array elements);
    template<typename T> static T* cast_ruby_array_to_complex(Array elements);
    template<typename T> static T* cast_ruby_array_to_short(Array elements);
    template<typename T> static T* cast_ruby_array_to_ushort(Array elements);
    template<typename T> VALUE complex_to_ruby(T complex);
};
