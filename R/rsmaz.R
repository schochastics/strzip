#' @title SMAZ
#' @name Rsmaz
#' @useDynLib Rsmaz, .registration=T
"_PACKAGE"

#' Compress a string using SMAZ algorithm
#'
#' @param input A character string to compress.
#' @return A raw vector containing the compressed data.
#' @export
smaz_compress <- function(input) {
    if (!is.character(input)) stop("Input must be a character vector")
    .Call("smaz_compress_R", input)
}

#' Decompress a raw vector using SMAZ algorithm
#'
#' @param input A raw vector to decompress.
#' @return A character string containing the decompressed data.
#' @export
smaz_decompress <- function(input) {
    if (!is.list(input) || !all(sapply(input, is.raw))) stop("Input must be a list of raw vectors")
    .Call("smaz_decompress_R", input)
}
