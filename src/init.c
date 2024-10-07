#include <R.h>
#include <R_ext/Rdynload.h>
#include <Rinternals.h>

/* init */
extern SEXP smaz_compress_R(SEXP input);
extern SEXP smaz_decompress_R(SEXP input);
extern SEXP unishox2_compress_R(SEXP inputVec);
extern SEXP unishox2_decompress_R(SEXP inputVec);
extern SEXP unishox2_compress_to_file_R(SEXP inputVec, SEXP filename);
extern SEXP unishox2_decompress_from_file_R(SEXP filename);

static const R_CallMethodDef CallEntries[] = {
    {"smaz_compress_R", (DL_FUNC)&smaz_compress_R, 1},
    {"smaz_decompress_R", (DL_FUNC)&smaz_decompress_R, 1},
    {"unishox2_compress_R", (DL_FUNC)&unishox2_compress_R, 1},
    {"unishox2_decompress_R", (DL_FUNC)&unishox2_decompress_R, 1},
    {"unishox2_compress_to_file_R", (DL_FUNC)&unishox2_compress_to_file_R, 2},
    {"unishox2_decompress_from_file_R",
     (DL_FUNC)&unishox2_decompress_from_file_R, 1},
    {NULL, NULL, 0}};

void R_init_strzip(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
