#include <R.h>
#include <Rinternals.h>

#include "smaz.h"

SEXP smaz_compress_R(SEXP input) {
  if (!isString(input)) error("Input must be a character vector");

  int n = LENGTH(input);
  SEXP result = PROTECT(allocVector(VECSXP, n));

  for (int i = 0; i < n; i++) {
    const char *str = CHAR(STRING_ELT(input, i));
    int str_len = strlen(str);

    char compressed[2 * str_len];
    int compressed_len =
        smaz_compress((char *)str, str_len, compressed, sizeof(compressed));

    if (compressed_len > sizeof(compressed)) {
      error("Output buffer too small for compression");
    }

    SEXP compressed_raw = PROTECT(allocVector(RAWSXP, compressed_len));
    memcpy(RAW(compressed_raw), compressed, compressed_len);

    SET_VECTOR_ELT(result, i, compressed_raw);
    UNPROTECT(1);
  }

  UNPROTECT(1);
  return result;
}

SEXP smaz_decompress_R(SEXP input) {
  if (!isVector(input) || TYPEOF(input) != VECSXP)
    error("Input must be a list of raw vectors");

  int n = LENGTH(input);
  SEXP result = PROTECT(allocVector(STRSXP, n));

  for (int i = 0; i < n; i++) {
    SEXP compressed_raw = VECTOR_ELT(input, i);
    if (TYPEOF(compressed_raw) != RAWSXP)
      error("Input must be a list of raw vectors");

    int compressed_len = LENGTH(compressed_raw);
    char *compressed_data = (char *)RAW(compressed_raw);

    char decompressed[2 * compressed_len];

    int decompressed_len = smaz_decompress(compressed_data, compressed_len,
                                           decompressed, sizeof(decompressed));

    if (decompressed_len > sizeof(decompressed)) {
      error("Output buffer too small for decompression");
    }

    SET_STRING_ELT(result, i, mkCharLen(decompressed, decompressed_len));
  }

  UNPROTECT(1);
  return result;
}
