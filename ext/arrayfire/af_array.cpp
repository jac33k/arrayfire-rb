#include "af_array.h"

// Constructor

AfArray::AfArray(array afarray) {
  this->set_c_array(afarray);
}

AfArray::AfArray(Array dimensions, Array elements, Symbol data_type) {
  af_array afarray = 0;
  dtype type = ruby_sym_to_dtype(data_type);

  dim4 tdims = ruby_array_to_dimensions(dimensions);

  switch (type) {
    case f32: create_internal_array<float>(afarray, elements, tdims, type); break;
    case c32: create_internal_array_complex<cfloat>(afarray, elements, tdims, type); break;
    case f64: create_internal_array<double>(afarray, elements, tdims, type); break;
    case c64: create_internal_array_complex<cdouble>(afarray, elements, tdims, type); break;
    case b8:  create_internal_array<char>(afarray, elements, tdims, type); break;
    case s32: create_internal_array<int>(afarray, elements, tdims, type); break;
    case u32: create_internal_array<uint>(afarray, elements, tdims, type); break;
    case s64: create_internal_array_long<intl>(afarray, elements, tdims, type); break;
    case u64: create_internal_array_long<uintl>(afarray, elements, tdims, type); break;
    case s16: create_internal_array<short>(afarray, elements, tdims, type); break;
    case u16: create_internal_array<ushort>(afarray, elements, tdims, type); break;
  }
}

// Public

void AfArray::print() {
  af_print(this->c_array);
}

AfArray* AfArray::multiply(Object other) {
  try {
    return AfArray::multiply_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::multiply_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_internal(AfArray other) {
  array afarray = this->c_array * other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_internal(int value) {
  array afarray = this->c_array * value;
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_assign(Object other) {
  try {
    return AfArray::multiply_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::multiply_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_assign_internal(AfArray other) {
  this->c_array *= other.get_c_array();
  return this;
}

AfArray* AfArray::multiply_assign_internal(int value) {
  this->c_array *= value;
  return this;
}

AfArray* AfArray::add(Object other) {
  try {
    return AfArray::add_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::add_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_internal(AfArray other) {
  array afarray = this->c_array + other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::add_internal(int value) {
  array afarray = this->c_array + value;
  return new AfArray(afarray);
}

AfArray* AfArray::add_assign(Object other) {
  try {
    return AfArray::add_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::add_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_assign_internal(AfArray other) {
  this->c_array += other.get_c_array();
  return this;
}

AfArray* AfArray::add_assign_internal(int value) {
  this->c_array += value;
  return this;
}

AfArray* AfArray::div(Object other) {
  try {
    return AfArray::div_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::div_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_internal(AfArray other) {
  array afarray = this->c_array / other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::div_internal(int value) {
  array afarray = this->c_array / value;
  return new AfArray(afarray);
}

AfArray* AfArray::div_assign(Object other) {
  try {
    return AfArray::div_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::div_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_assign_internal(AfArray other) {
  this->c_array /= other.get_c_array();
  return this;
}

AfArray* AfArray::div_assign_internal(int value) {
  this->c_array /= value;
  return this;
}

AfArray* AfArray::sub(Object other) {
  try {
    return AfArray::sub_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::sub_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_internal(AfArray other) {
  array afarray = this->c_array - other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::sub_internal(int value) {
  array afarray = this->c_array - value;
  return new AfArray(afarray);
}

AfArray* AfArray::sub_assign(Object other) {
  try {
    return AfArray::sub_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::sub_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_assign_internal(AfArray other) {
  this->c_array -= other.get_c_array();
  return this;
}

AfArray* AfArray::sub_assign_internal(int value) {
  this->c_array -= value;
  return this;
}

AfArray* AfArray::randu(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  return new AfArray(afarray);
}

AfArray* AfArray::randn(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  return new AfArray(afarray);
}

AfArray* AfArray::constant(Object value, Array dimensions, Symbol data_type) {
  array afarray = 0;
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  switch (type) {
    case f32: afarray = af::constant(cast_ruby_to<float>(value), tdims, type); break;
    case c32: afarray = af::constant(cast_ruby_to_complex<cfloat>(value), tdims, type); break;
    case f64: afarray = af::constant(cast_ruby_to<double>(value), tdims, type); break;
    case c64: afarray = af::constant(cast_ruby_to_complex<cdouble>(value), tdims, type); break;
    case b8:  afarray = af::constant(cast_ruby_to<char>(value), tdims, type); break;
    case s32: afarray = af::constant(cast_ruby_to<int>(value), tdims, type); break;
    case u32: afarray = af::constant(cast_ruby_to<uint>(value), tdims, type); break;
    case s64: afarray = af::constant(cast_ruby_to_long<intl>(value), tdims, type); break;
    case u64: afarray = af::constant(cast_ruby_to_long<uintl>(value), tdims, type); break;
    case s16: afarray = af::constant(cast_ruby_to<short>(value), tdims, type); break;
    case u16: afarray = af::constant(cast_ruby_to<ushort>(value), tdims, type); break;
  }

  return new AfArray(afarray);
}

template<typename T>
T AfArray::cast_ruby_to(Object ruby_object) {
  return from_ruby<T>(ruby_object);
}

template<typename T>
T AfArray::cast_ruby_to_long(Object ruby_object) {
  return FIX2LONG(ruby_object.value());
}

template<typename T>
T AfArray::cast_ruby_to_complex(Object ruby_object) {
  double real = from_ruby<double>(ruby_object.call("real"));
  double imaginary = from_ruby<double>(ruby_object.call("imaginary"));
  return T(real, imaginary);
}

void AfArray::set_seed(int seed) {
  setSeed(NUM2ULL(seed));
}

int AfArray::get_seed() {
  return ULL2NUM(getSeed());
}

AfArray* AfArray::row(int index) {
  array afarray = this->c_array.row(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::rows(int first, int last) {
  array afarray = this->c_array.rows(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::col(int index) {
  array afarray = this->c_array.col(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cols(int first, int last) {
  array afarray = this->c_array.cols(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slice(int index) {
  array afarray = this->c_array.slice(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slices(int first, int last) {
  array afarray = this->c_array.slices(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lookup(Array idx) {
  af::array indices(idx.size(), ruby_array_to_ints(idx));
  array afarray = af::lookup(this->c_array, indices);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::real() {
  array afarray = af::real(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::imag() {
  array afarray = af::imag(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::conjg() {
  array afarray = af::conjg(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::diag(int num, bool extract) {
  array afarray = af::diag(this->c_array, num, extract);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::identity(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::identity(tdims, type);
  return new AfArray(afarray);
}

AfArray* AfArray::iota(Array dimensions, Array tile_dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  dim4 tile_dims = ruby_array_to_dimensions(tile_dimensions);
  array afarray = af::iota(tdims, tile_dims, type);
  return new AfArray(afarray);
}

// Private

array AfArray::get_c_array() {
  return this->c_array;
}

void AfArray::set_c_array(af_array afarray) {
  this->c_array = array(afarray);
}

void AfArray::set_c_array(const array& afarray) {
  this->c_array = afarray;
}

dim4 AfArray::ruby_array_to_dimensions(Array dimensions) {
  size_t count = dimensions.size();
  dim4 tdims = dim4(1, 1, 1, 1);
  for (size_t index = 0; index < count; index++) {
    tdims[index] = from_ruby<uint>(dimensions[index]);
  }
  return tdims;
}

int* AfArray::ruby_array_to_ints(Array rb_array) {
  size_t count = rb_array.size();
  int array[count];
  for (size_t index = 0; index < count; index++) {
    array[index] = from_ruby<int>(rb_array[index]);
  }
  return array;
}

template<typename T>
void AfArray::create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = from_ruby<T>(elements[i]);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_long(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    casted_elements[i] = FIX2LONG(element.value());
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    double real = from_ruby<double>(element.call("real"));
    double imaginary = from_ruby<double>(element.call("imaginary"));
    casted_elements[i] = T(real, imaginary);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}
