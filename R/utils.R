#' Print a compressed string
#' @param x A compressed string object
#' @param ... additional arguments to print
#' @export
print.strzip <- function(x, ...) {
    n <- length(x)
    if (n == 1) {
        cat("<compressed string>\n")
    } else {
        cat("<compressed string of length ", n, ">\n", sep = "")
    }
}

#' strzip class
#' @param x character
#' @export
strzip <- function(x = character()) {
    if (!is.character(x)) stop("x must be a character vector")
    structure(x, class = c("strzip", "character"))
}

#' strzip class access vector
#' @param x character
#' @param i element
#' @export
`[.strzip` <- function(x, i) {
    result <- NextMethod("[")
    if (length(result) == 1) {
        result <- strzip(result)
    } else {
        class(result) <- "strzip"
    }
    return(result)
}

#' strzip class access list
#' @param x character
#' @param i element
#' @export
`[[.strzip` <- function(x, i) {
    result <- NextMethod("[")
    if (length(result) == 1) {
        result <- strzip(result)
    } else {
        class(result) <- "strzip"
    }
    return(result)
}

#' strzip class assign
#' @param x character
#' @param i element
#' @param value value
#' @export
`[<-.strzip` <- function(x, i, value) {
    if (!is.character(value)) stop("Replacement value must be a character vector")
    x <- NextMethod("[<-")
    return(x)
}

#' Encode strzip
#' @param x strzip object
#' @param ... urther arguments passed to or from other methods.
#' @export
format.strzip <- function(x, ...) {
    rep("<compressed string>", length(x))
}

#' Summary for strzip
#' @param object strzip object
#' @param type either "mean" for average compression rate, "all" for all
#' individual rates, "summary" for min/max/average rates
#' @param ... additional arguments affecting the summary produced.
#' @export
summary.strzip <- function(object, type = "mean", ...) {
    uncompressed <- str_decompress(object)
    rates <- sapply(object, .lraw, USE.NAMES = FALSE) / sapply(uncompressed, .lraw, USE.NAMES = FALSE)
    if (type == "all") {
        cat("Individual compression rates:\n")
        cat(round(rates, 2), "\n", sep = "\n")
    } else if (type == "mean") {
        cat("Average compression rate: ")
        cat(round(mean(rates), 2), "\n")
    } else if (type == "summary") {
        cat("Minimal compression rate: ")
        cat(round(min(rates), 2), "\n")
        cat("Maximal compression rate: ")
        cat(round(max(rates), 2), "\n")
        cat("Average compression rate: ")
        cat(round(mean(rates), 2), "\n")
    }
}

.lraw <- function(x) {
    length(charToRaw(x))
}
