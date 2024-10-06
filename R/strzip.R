#' @title strzip
#' @name strzip
#' @useDynLib strzip, .registration=T
"_PACKAGE"

#' Compress a string using SMAZ algorithm
#'
#' @param x A character vector string to compress.
#' @return A list of raw vectors containing the compressed data.
#' @export
smaz_compress <- function(x) {
    if (!is.character(x)) stop("x must be a character vector")
    .Call("smaz_compress_R", x)
}

#' Decompress a raw vector using SMAZ algorithm
#'
#' @param x A list of raw vectors to decompress.
#' @return A character vector of strings containing the decompressed data.
#' @export
smaz_decompress <- function(x) {
    if (!is.list(x) || !all(sapply(x, is.raw))) stop("x must be a list of raw vectors")
    .Call("smaz_decompress_R", x)
}

#' Compress a vector of strings using Unishox2
#'
#' This function compresses each string in a vector using the Unishox2 compression algorithm.
#'
#' @param x A character vector of strings to be compressed.
#' @return A character vector of compressed strings.
#' @examples
#' compressed_vec <- unishox2_compress(c("Hello", "world", "Unishox2"))
#' print(compressed_vec)
#' @export
unishox2_compress <- function(x) {
    .Call("unishox2_compress_R", x)
}

#' Decompress a vector of strings using Unishox2
#'
#' This function decompresses each string in a compressed character vector that was compressed using Unishox2.
#'
#' @param x A character vector of compressed strings to be decompressed.
#' @return A character vector of decompressed strings.
#' @examples
#' compressed_vec <- unishox2_compress(c("Hello", "world", "Unishox2"))
#' decompressed_vec <- unishox2_decompress(compressed_vec)
#' print(decompressed_vec)
#' @export
unishox2_decompress <- function(x) {
    .Call("unishox2_decompress_R", x)
}
