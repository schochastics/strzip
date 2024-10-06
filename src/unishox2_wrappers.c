#include <R.h>
#include <Rinternals.h>

#include "unishox2.h"  // Include Unishox2 header file

// Wrapper for compressing a single string using Unishox2
SEXP unishox2_compress_R(SEXP inputStr) {
  const char *input = CHAR(asChar(inputStr));  // Convert R string to C string
  int input_len = strlen(input);

  char compressed[1024];  // Create buffer for compressed output
  int compressed_len = unishox2_compress_simple(input, input_len, compressed);

  // Create R object with compressed data
  return mkCharLen(compressed, compressed_len);
}

// Wrapper for decompressing a single string using Unishox2
SEXP unishox2_decompress_R(SEXP inputStr) {
  const char *input = CHAR(asChar(inputStr));  // Convert R string to C string
  int input_len = strlen(input);

  char decompressed[1024];  // Create buffer for decompressed output
  int decompressed_len =
      unishox2_decompress_simple(input, input_len, decompressed);

  // Create R object with decompressed data
  return mkCharLen(decompressed, decompressed_len);
}

// Wrapper for compressing a vector of strings using Unishox2
SEXP unishox2_compress_vector_R(SEXP inputVec) {
  R_xlen_t n = XLENGTH(inputVec);
  SEXP outputVec =
      PROTECT(allocVector(STRSXP, n));  // Allocate space for output vector

  for (R_xlen_t i = 0; i < n; i++) {
    const char *input =
        CHAR(STRING_ELT(inputVec, i));  // Access each element of input vector
    int input_len = strlen(input);

    char compressed[1024];  // Buffer for compressed output
    int compressed_len = unishox2_compress_simple(input, input_len, compressed);

    // Store compressed string in output vector
    SET_STRING_ELT(outputVec, i, mkCharLen(compressed, compressed_len));
  }

  UNPROTECT(1);  // Release protected memory
  return outputVec;
}

// Wrapper for decompressing a vector of strings using Unishox2
SEXP unishox2_decompress_vector_R(SEXP inputVec) {
  R_xlen_t n = XLENGTH(inputVec);
  SEXP outputVec =
      PROTECT(allocVector(STRSXP, n));  // Allocate space for output vector

  for (R_xlen_t i = 0; i < n; i++) {
    const char *input =
        CHAR(STRING_ELT(inputVec, i));  // Access each element of input vector
    int input_len = strlen(input);

    char decompressed[1024];  // Buffer for decompressed output
    int decompressed_len =
        unishox2_decompress_simple(input, input_len, decompressed);

    // Store decompressed string in output vector
    SET_STRING_ELT(outputVec, i, mkCharLen(decompressed, decompressed_len));
  }

  UNPROTECT(1);  // Release protected memory
  return outputVec;
}
