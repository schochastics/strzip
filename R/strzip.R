#' @title strzip
#' @name strzip
#' @useDynLib strzip, .registration=T
"_PACKAGE"

#' Compress a string using SMAZ algorithm
#'
#' @param x A character vector string to compress.
#' @return A list of raw vectors containing the compressed data.
#' @examples
#' str_compress_raw(c("Hello", "world", "smaz"))
#' @export
str_compress_raw <- function(x) {
    if (!is.character(x)) stop("x must be a character vector")
    .Call("smaz_compress_R", x)
}

#' Decompress a raw vector using SMAZ algorithm
#'
#' @param x A list of raw vectors to decompress.
#' @return A character vector of strings containing the decompressed data.
#' @examples
#' compressed_lst <- str_compress_raw(c("Hello", "world", "smaz"))
#' str_decompress_raw(compressed_lst)
#' @export
str_decompress_raw <- function(x) {
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
#' str_compress_uni(c("Hello", "world", "Unishox2"))
#'
#' @export
str_compress_uni <- function(x) {
    .Call("unishox2_compress_R", x)
}

#' Decompress a vector of strings using Unishox2
#'
#' This function decompresses each string in a compressed character vector that was compressed using Unishox2.
#'
#' @param x A character vector of compressed strings to be decompressed.
#' @return A character vector of decompressed strings.
#' @examples
#' compressed_vec <- str_compress_uni(c("Hello", "world", "Unishox2"))
#' str_decompress_uni(compressed_vec)
#' @export
str_decompress_uni <- function(x) {
    .Call("unishox2_decompress_R", x)
}
