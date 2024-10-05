#include <R.h>
#include <Rinternals.h>

#include "smaz.h"

/* Wrapper for smaz_compress */
SEXP smaz_compress_R(SEXP input) {
  if (TYPEOF(input) != STRSXP || LENGTH(input) != 1) {
    error("Input must be a single string.");
  }

  const char *in_str = CHAR(STRING_ELT(input, 0));
  int inlen = strlen(in_str);

  int max_outlen = inlen + 128;
  char *out = (char *)R_alloc(max_outlen, sizeof(char));

  int compressed_len = smaz_compress((char *)in_str, inlen, out, max_outlen);

  if (compressed_len >= max_outlen) {
    error("Compression failed due to insufficient output buffer size.");
  }

  SEXP output = PROTECT(allocVector(RAWSXP, compressed_len));
  memcpy(RAW(output), out, compressed_len);

  UNPROTECT(1);
  return output;
}

SEXP smaz_decompress_R(SEXP input) {
  if (TYPEOF(input) != RAWSXP) {
    error("Input must be a raw vector.");
  }

  const char *in_data = (const char *)RAW(input);
  int inlen = LENGTH(input);

  int max_outlen = inlen * 4;
  char *out = (char *)R_alloc(max_outlen, sizeof(char));

  int decompressed_len =
      smaz_decompress((char *)in_data, inlen, out, max_outlen);

  if (decompressed_len >= max_outlen) {
    error("Decompression failed due to insufficient output buffer size.");
  }

  SEXP output = PROTECT(ScalarString(mkCharLen(out, decompressed_len)));

  UNPROTECT(1);
  return output;
}
