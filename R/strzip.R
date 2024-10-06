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


#' Compress a single string using Unishox2
#'
#' This function compresses a single string using the Unishox2 compression algorithm.
#'
#' @param x A character string to be compressed.
#' @return A compressed character string.
#' @examples
#' compressed <- unishox2_compress("Hello, world!")
#' print(compressed)
#' @export
unishox2_compress <- function(x) {
    .Call("unishox2_compress_R", x)
}

#' Decompress a single string using Unishox2
#'
#' This function decompresses a single compressed string that was compressed using Unishox2.
#'
#' @param x A compressed character string to be decompressed.
#' @return A decompressed character string.
#' @examples
#' compressed <- unishox2_compress("Hello, world!")
#' decompressed <- unishox2_decompress(compressed)
#' print(decompressed)
#' @export
unishox2_decompress <- function(x) {
    .Call("unishox2_decompress_R", x)
}

#' Compress a vector of strings using Unishox2
#'
#' This function compresses each string in a vector using the Unishox2 compression algorithm.
#'
#' @param x A character vector of strings to be compressed.
#' @return A character vector of compressed strings.
#' @examples
#' compressed_vec <- unishox2_compress_vector(c("Hello", "world", "Unishox2"))
#' print(compressed_vec)
#' @export
unishox2_compress_vector <- function(x) {
    .Call("unishox2_compress_vector_R", x)
}

#' Decompress a vector of strings using Unishox2
#'
#' This function decompresses each string in a compressed character vector that was compressed using Unishox2.
#'
#' @param x A character vector of compressed strings to be decompressed.
#' @return A character vector of decompressed strings.
#' @examples
#' compressed_vec <- unishox2_compress_vector(c("Hello", "world", "Unishox2"))
#' decompressed_vec <- unishox2_decompress_vector(compressed_vec)
#' print(decompressed_vec)
#' @export
unishox2_decompress_vector <- function(x) {
    .Call("unishox2_decompress_vector_R", x)
}
