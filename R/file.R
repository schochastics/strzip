#' Compress a vector of strings and write to a file
#'
#' This function compresses a string using Unishox2 and writes the compressed binary data to a file.
#'
#' @param x A character vector to be compressed.
#' @param file filename where the compressed data will be written.
#' @return The length of the compressed data written to the file (invisibly).
#' @export
str_compress_write <- function(x, file) {
    return(invisible(.Call("unishox2_compress_to_file_R", x, file)))
}

#' Decompress a character vector from a file
#'
#' This function reads compressed binary data from a file and decompresses it using Unishox2.
#'
#' @param file The filename containing the compressed binary data.
#' @return A decompressed character string.
#' @export
str_compress_read <- function(file) {
    .Call("unishox2_decompress_from_file_R", file)
}
