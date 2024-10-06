#include <R.h>
#include <Rinternals.h>

#include "smaz.h"

SEXP smaz_compress_R(SEXP input) {
  if (!isString(input)) error("Input must be a character vector");

  int n = LENGTH(input);  // Length of the input vector
  SEXP result =
      PROTECT(allocVector(VECSXP, n));  // Allocate a list for the result

  for (int i = 0; i < n; i++) {
    const char *str = CHAR(STRING_ELT(input, i));  // Extract the ith string
    int str_len = strlen(str);

    // Allocate enough memory for the compressed result (estimated size)
    char compressed[2 * str_len];  // Can tune this based on expected
                                   // compression rate
    int compressed_len =
        smaz_compress((char *)str, str_len, compressed, sizeof(compressed));

    if (compressed_len > sizeof(compressed)) {
      error("Output buffer too small for compression");
    }

    // Create a raw vector in R for the compressed data
    SEXP compressed_raw = PROTECT(allocVector(RAWSXP, compressed_len));
    memcpy(RAW(compressed_raw), compressed,
           compressed_len);  // Copy compressed data

    SET_VECTOR_ELT(result, i,
                   compressed_raw);  // Store the compressed result in the list
    UNPROTECT(1);                    // compressed_raw
  }

  UNPROTECT(1);   // result
  return result;  // Return the list of raw vectors
}

SEXP smaz_decompress_R(SEXP input) {
  if (!isVector(input) || TYPEOF(input) != VECSXP)
    error("Input must be a list of raw vectors");

  int n = LENGTH(input);  // Length of the input list
  SEXP result = PROTECT(
      allocVector(STRSXP, n));  // Allocate a character vector for the result

  for (int i = 0; i < n; i++) {
    SEXP compressed_raw = VECTOR_ELT(input, i);
    if (TYPEOF(compressed_raw) != RAWSXP)
      error("Input must be a list of raw vectors");

    int compressed_len = LENGTH(compressed_raw);
    char *compressed_data = (char *)RAW(compressed_raw);

    // Allocate memory for the decompressed result (estimated size)
    char decompressed[2 * compressed_len];  // Can tune this based on expected
                                            // decompression rate
    int decompressed_len = smaz_decompress(compressed_data, compressed_len,
                                           decompressed, sizeof(decompressed));

    if (decompressed_len > sizeof(decompressed)) {
      error("Output buffer too small for decompression");
    }

    // Create an R string from the decompressed data
    SET_STRING_ELT(
        result, i,
        mkCharLen(decompressed,
                  decompressed_len));  // Store the decompressed result
  }

  UNPROTECT(1);   // result
  return result;  // Return the character vector of decompressed strings
}
