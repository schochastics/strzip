#include <R.h>
#include <Rinternals.h>
#include <stdio.h>

#include "unishox2.h"

SEXP unishox2_compress_R(SEXP inputVec) {
  R_xlen_t n = XLENGTH(inputVec);
  SEXP outputVec = PROTECT(allocVector(STRSXP, n));

  for (R_xlen_t i = 0; i < n; i++) {
    const char *input = CHAR(STRING_ELT(inputVec, i));
    int input_len = strlen(input);

    char compressed[1024];  // Buffer for compressed output
    int compressed_len = unishox2_compress_simple(input, input_len, compressed);

    SET_STRING_ELT(outputVec, i, mkCharLen(compressed, compressed_len));
  }

  UNPROTECT(1);
  return outputVec;
}

SEXP unishox2_decompress_R(SEXP inputVec) {
  R_xlen_t n = XLENGTH(inputVec);
  SEXP outputVec = PROTECT(allocVector(STRSXP, n));

  for (R_xlen_t i = 0; i < n; i++) {
    const char *input = CHAR(STRING_ELT(inputVec, i));
    int input_len = strlen(input);

    char decompressed[1024];  // Buffer for decompressed output
    int decompressed_len =
        unishox2_decompress_simple(input, input_len, decompressed);

    SET_STRING_ELT(outputVec, i, mkCharLen(decompressed, decompressed_len));
  }

  UNPROTECT(1);
  return outputVec;
}

/***************************************************************************************
File I/O
****************************************************************************************/
void write_compressed_to_file(const char *filename, SEXP strVec) {
  FILE *file = fopen(filename, "wb");
  if (file != NULL) {
    R_xlen_t n = XLENGTH(strVec);

    for (R_xlen_t i = 0; i < n; i++) {
      const char *input = CHAR(STRING_ELT(strVec, i));
      int input_len = strlen(input);

      char compressed[1024];
      int compressed_len =
          unishox2_compress_simple(input, input_len, compressed);

      fwrite(&compressed_len, sizeof(int), 1, file);

      fwrite(compressed, 1, compressed_len, file);
    }

    fclose(file);
  } else {
    error("Error opening file for writing.");
  }
}

SEXP unishox2_compress_to_file_R(SEXP inputVec, SEXP filename) {
  const char *file = CHAR(asChar(filename));
  write_compressed_to_file(file, inputVec);

  return ScalarLogical(1);
}

SEXP read_compressed_from_file(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file != NULL) {
    SEXP result = PROTECT(allocVector(STRSXP, 0));
    R_xlen_t string_count = 0;

    while (!feof(file)) {
      int compressed_len;
      if (fread(&compressed_len, sizeof(int), 1, file) != 1) break;

      char compressed[1024];
      if (fread(compressed, 1, compressed_len, file) != compressed_len) break;

      char decompressed[1024];
      int decompressed_len =
          unishox2_decompress_simple(compressed, compressed_len, decompressed);

      result = PROTECT(lengthgets(result, string_count + 1));

      SET_STRING_ELT(result, string_count,
                     mkCharLen(decompressed, decompressed_len));

      string_count++;

      UNPROTECT(1);
    }

    fclose(file);

    UNPROTECT(1);
    return result;
  } else {
    error("Error opening file for reading.");
    return R_NilValue;
  }
}

SEXP unishox2_decompress_from_file_R(SEXP filename) {
  const char *file = CHAR(asChar(filename));

  return read_compressed_from_file(file);
}