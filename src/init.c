#include <R.h>
#include <R_ext/Rdynload.h>
#include <Rinternals.h>

/* init */
SEXP smaz_compress_R(SEXP input);
SEXP smaz_decompress_R(SEXP input);
extern SEXP unishox2_compress_R(SEXP inputStr);
extern SEXP unishox2_decompress_R(SEXP inputStr);
extern SEXP unishox2_compress_vector_R(SEXP inputVec);
extern SEXP unishox2_decompress_vector_R(SEXP inputVec);

static const R_CallMethodDef CallEntries[] = {
    {"smaz_compress_R", (DL_FUNC)&smaz_compress_R, 1},
    {"smaz_decompress_R", (DL_FUNC)&smaz_decompress_R, 1},
    {"unishox2_compress_R", (DL_FUNC)&unishox2_compress_R, 1},
    {"unishox2_decompress_R", (DL_FUNC)&unishox2_decompress_R, 1},
    {"unishox2_compress_vector_R", (DL_FUNC)&unishox2_compress_vector_R, 1},
    {"unishox2_decompress_vector_R", (DL_FUNC)&unishox2_decompress_vector_R, 1},
    {NULL, NULL, 0}};

void R_init_strzip(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
