#' @title strzip
#' @name strzip
#' @useDynLib strzip, .registration=T
"_PACKAGE"

#' Compress a string using SMAZ algorithm
#'
#' @param input A character vector string to compress.
#' @return A list of raw vectors containing the compressed data.
#' @export
smaz_compress <- function(input) {
    if (!is.character(input)) stop("Input must be a character vector")
    .Call("smaz_compress_R", input)
}

#' Decompress a raw vector using SMAZ algorithm
#'
#' @param input A list of raw vectors to decompress.
#' @return A character vector of strings containing the decompressed data.
#' @export
smaz_decompress <- function(input) {
    if (!is.list(input) || !all(sapply(input, is.raw))) stop("Input must be a list of raw vectors")
    .Call("smaz_decompress_R", input)
}
